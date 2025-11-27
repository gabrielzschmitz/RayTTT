#include "input.h"
#include "game.h"
#include "raylib.h"
#include "sfx.h"
#include "ui.h"
#include <math.h>

static int selectedRow = 0;
static int selectedCol = 0;
static int selectedOption = 0; // 0 = Play Again, 1 = Reset Scores
static float gamepadMoveCooldown = 0.0f;
const float gamepadMoveDelay = 0.15f;

float lastGamepadActivityTime = 0.0f;
bool selectorVisible = false;
const float GAMEPAD_SELECTOR_TIMEOUT = 3.0f; // seconds

void HandleGamepadInput(void) {
  if (!IsGamepadAvailable(GAMEPAD))
    return;

  bool anyInput =
      IsGamepadButtonDown(GAMEPAD, GAMEPAD_BUTTON_LEFT_FACE_UP) ||
      IsGamepadButtonDown(GAMEPAD, GAMEPAD_BUTTON_LEFT_FACE_DOWN) ||
      IsGamepadButtonDown(GAMEPAD, GAMEPAD_BUTTON_LEFT_FACE_LEFT) ||
      IsGamepadButtonDown(GAMEPAD, GAMEPAD_BUTTON_LEFT_FACE_RIGHT) ||
      IsGamepadButtonDown(GAMEPAD, GAMEPAD_BUTTON_RIGHT_FACE_UP) ||
      IsGamepadButtonDown(GAMEPAD, GAMEPAD_BUTTON_RIGHT_FACE_DOWN) ||
      IsGamepadButtonDown(GAMEPAD, GAMEPAD_BUTTON_RIGHT_FACE_LEFT) ||
      IsGamepadButtonDown(GAMEPAD, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT) ||
      fabs(GetGamepadAxisMovement(GAMEPAD, GAMEPAD_AXIS_LEFT_X)) > 0.2f ||
      fabs(GetGamepadAxisMovement(GAMEPAD, GAMEPAD_AXIS_LEFT_Y)) > 0.2f;

  if (anyInput) {
    lastGamepadActivityTime = GetTime();
    selectorVisible = true;
  }

  if (selectorVisible) {
    if (GetTime() - lastGamepadActivityTime > GAMEPAD_SELECTOR_TIMEOUT) {
      selectorVisible = false;
    }
  }

  gamepadMoveCooldown -= GetFrameTime();

  if (winner == 0) {
    // Get directional input from D-pad buttons or left stick
    bool up = IsGamepadButtonPressed(GAMEPAD, GAMEPAD_BUTTON_LEFT_FACE_UP);
    bool down = IsGamepadButtonPressed(GAMEPAD, GAMEPAD_BUTTON_LEFT_FACE_DOWN);
    bool left = IsGamepadButtonPressed(GAMEPAD, GAMEPAD_BUTTON_LEFT_FACE_LEFT);
    bool right =
        IsGamepadButtonPressed(GAMEPAD, GAMEPAD_BUTTON_LEFT_FACE_RIGHT);

    // Also check left stick with a deadzone
    float leftStickX = GetGamepadAxisMovement(GAMEPAD, GAMEPAD_AXIS_LEFT_X);
    float leftStickY = GetGamepadAxisMovement(GAMEPAD, GAMEPAD_AXIS_LEFT_Y);
    const float deadzone = 0.5f;

    if (leftStickY < -deadzone)
      up = true;
    if (leftStickY > deadzone)
      down = true;
    if (leftStickX < -deadzone)
      left = true;
    if (leftStickX > deadzone)
      right = true;

    if (gamepadMoveCooldown <= 0) {
      if (up) {
        selectedRow = (selectedRow + 2) % 3; // move up, wrap around
        gamepadMoveCooldown = gamepadMoveDelay;
      } else if (down) {
        selectedRow = (selectedRow + 1) % 3; // move down
        gamepadMoveCooldown = gamepadMoveDelay;
      } else if (left) {
        selectedCol = (selectedCol + 2) % 3; // move left
        gamepadMoveCooldown = gamepadMoveDelay;
      } else if (right) {
        selectedCol = (selectedCol + 1) % 3; // move right
        gamepadMoveCooldown = gamepadMoveDelay;
      }
    }

    // Press A button to select tile
    bool padDown = IsGamepadButtonDown(GAMEPAD, GAMEPAD_BUTTON_RIGHT_FACE_DOWN);
    SetTilePressed(selectedRow, selectedCol, padDown);

    if (padDown)
      selectorPressed = true;

    // If button *just* pressed and tile is empty → place piece
    if (padDown && board[selectedRow][selectedCol] == 0 &&
        IsGamepadButtonPressed(GAMEPAD, GAMEPAD_BUTTON_RIGHT_FACE_DOWN)) {

      board[selectedRow][selectedCol] = current;
      winner = CheckWinner();
      PlaySound(clickTileSound);

      if (winner == 0)
        current = (current == 1) ? 2 : 1;

      if (winner != 0)
        ResetTiles();
      if (winner == 1)
        scoreX++;
      else if (winner == 2)
        scoreO++;
      else if (winner == 3)
        scoreDraw++;
    }
  } else {
    // Winner exists, navigate menu options instead
    bool up = IsGamepadButtonPressed(GAMEPAD, GAMEPAD_BUTTON_LEFT_FACE_UP);
    bool down = IsGamepadButtonPressed(GAMEPAD, GAMEPAD_BUTTON_LEFT_FACE_DOWN);

    float leftStickY = GetGamepadAxisMovement(GAMEPAD, GAMEPAD_AXIS_LEFT_Y);
    const float deadzone = 0.5f;
    if (leftStickY < -deadzone)
      up = true;
    if (leftStickY > deadzone)
      down = true;

    if (gamepadMoveCooldown <= 0) {
      if (up) {
        selectedOption = (selectedOption + 1) % 2; // wrap between 0 and 1
        gamepadMoveCooldown = gamepadMoveDelay;
      } else if (down) {
        selectedOption = (selectedOption + 1) % 2;
        gamepadMoveCooldown = gamepadMoveDelay;
      }
    }

    // A button held (for animation)
    bool aHeld = IsGamepadButtonDown(GAMEPAD, GAMEPAD_BUTTON_RIGHT_FACE_DOWN);

    // Apply press animation like tiles
    if (selectedOption == 0) {
      SetResetButtonPressed(false);
      SetPlayAgainButtonPressed(aHeld);
    } else {
      SetPlayAgainButtonPressed(false);
      SetResetButtonPressed(aHeld);
    }

    // Update animations every frame
    UpdatePlayAgainButtonAnim(aHeld);
    UpdateResetButtonAnim(aHeld);

    // A button pressed (one-time activation)
    if (IsGamepadButtonPressed(GAMEPAD, GAMEPAD_BUTTON_RIGHT_FACE_DOWN)) {
      PlaySound(clickButtonSound);

      if (selectedOption == 0) {
        // Play Again
        ResetBoard();
        winner = 0;
      } else if (selectedOption == 1) {
        // Reset Scores
        scoreX = 0;
        scoreO = 0;
        scoreDraw = 0;
        ResetBoard();
        winner = 0;
      }
    }
  }
}

void DrawGamepadSelector(Rectangle boardRect, Rectangle playAgainBtn,
                         Rectangle resetScoresBtn) {
  if (!IsGamepadAvailable(GAMEPAD))
    return;
  if (!selectorVisible)
    return;

  const float pad = 10.0f;
  const float tileShrinkPixels = 6.0f; // same as maxPressOffset used for tiles
  const float buttonShrinkPixels = 6.0f; // same as you used for buttons

  if (winner == 0) {
    // Board selector: position matches the tile (including pad)
    float cell = boardRect.width / 3.0f;
    float tilePad = 10.0f;

    // base selector rect (matches DrawBoard tile layout)
    Rectangle selector = {boardRect.x + selectedCol * cell + tilePad,
                          boardRect.y + selectedRow * cell + tilePad,
                          cell - tilePad * 2, cell - tilePad * 2};

    // Derive shrink from the selected tile's press animation
    float pressAmount =
        tilePressAnim[selectedRow][selectedCol]; // 0..0.5 (your current system)
    float maxPressOffset = 6.0f;
    float pressOffset = pressAmount * maxPressOffset;

    // Draw the shrinking outline (inset by shrink)
    DrawRectangleLines(
        selector.x, selector.y + pressOffset, selector.width, selector.height,
        MixColors((Color){255, 0, 200, 255}, (Color){0, 255, 100, 255}));
  } else {
    const int outlineThick = 4;

    Rectangle selector;

    if (selectedOption == 0) {
      // Selector on Play Again button
      selector.x = playAgainBtn.x - pad - outlineThick;
      selector.y = playAgainBtn.y - pad - outlineThick;
      selector.width = playAgainBtn.width + 2 * (pad + outlineThick);
      selector.height = playAgainBtn.height + 2 * (pad + outlineThick);
    } else {
      // Selector on Reset Scores button
      selector.x = resetScoresBtn.x - pad - outlineThick;
      selector.y = resetScoresBtn.y - pad - outlineThick;
      selector.width = resetScoresBtn.width + 2 * (pad + outlineThick);
      selector.height = resetScoresBtn.height + 2 * (pad + outlineThick);
    }

    DrawRectangleLines(
        selector.x, selector.y, selector.width, selector.height,
        MixColors((Color){255, 0, 200, 255}, (Color){0, 255, 100, 255}));
  }
}

void HandleBoardClick(Rectangle rect) {
  if (winner != 0)
    return;

  Vector2 m = GetMousePosition();
  float cell = rect.width / 3.0f;

  for (int r = 0; r < 3; r++) {
    for (int c = 0; c < 3; c++) {
      Rectangle t = {rect.x + c * cell, rect.y + r * cell, cell, cell};
      bool mouseInTile = CheckCollisionPointRec(m, t);
      bool mouseDown = IsMouseButtonDown(MOUSE_LEFT_BUTTON);

      SetTilePressed(r, c, mouseInTile && mouseDown);

      if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && mouseInTile &&
          board[r][c] == 0) {
        board[r][c] = current;
        winner = CheckWinner();
        PlaySound(clickTileSound);

        if (winner == 0)
          current = (current == 1) ? 2 : 1;

        if (winner != 0)
          ResetTiles();
        if (winner == 1)
          scoreX++;
        else if (winner == 2)
          scoreO++;
        else if (winner == 3)
          scoreDraw++;
      }
    }
  }
}

void HandleResetButton(Rectangle btn) {
  if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
      CheckCollisionPointRec(GetMousePosition(), btn)) {
    PlaySound(clickButtonSound);
    scoreX = 0;
    scoreO = 0;
    scoreDraw = 0;
    ResetBoard();
  }
}

void HandlePlayAgainButton(Rectangle btn) {
  if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
      CheckCollisionPointRec(GetMousePosition(), btn)) {
    PlaySound(clickButtonSound);
    ResetBoard();
  }
}
