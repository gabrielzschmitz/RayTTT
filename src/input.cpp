#include "input.h"
#include "game.h"
#include "sfx.h"

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
