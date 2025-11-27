#include "draw.h"
#include "game.h"
#include "input.h"
#include "raylib.h"
#include "resource_dir.h" // utility header for SearchAndSetResourceDir
#include "ui.h"

int main() {
  const int W = 600;
  const int H = 850;

  InitWindow(W, H, "Tic-Tac-Toe Neon Retro");
  SetTargetFPS(60);

  ResetBoard();

  Rectangle boardRect = {100, 250, 400, 400};
  Rectangle boxRect = {100, 250, 400, 480};
  Rectangle resetBtn = {(float)W / 2 - 90, 785, 180, 30};
  Rectangle playAgainBtn = {(float)W / 2 - 65, 700, 130, 20};

  while (!WindowShouldClose()) {
    // INPUT
    HandleBoardClick(boardRect);
    if (IsKeyPressed(KEY_R))
      ResetBoard();
    Vector2 mousePos = GetMousePosition();

    // Reset Button input
    bool mouseOverReset = CheckCollisionPointRec(mousePos, resetBtn);
    bool mouseDown = IsMouseButtonDown(MOUSE_LEFT_BUTTON);
    SetResetButtonPressed(mouseOverReset && mouseDown);
    UpdateResetButtonAnim(mouseOverReset && mouseDown);
    HandleResetButton(resetBtn);

    // Play Again Button input
    bool mouseOverPlayAgain = CheckCollisionPointRec(mousePos, playAgainBtn);
    SetPlayAgainButtonPressed(mouseOverPlayAgain && mouseDown);
    UpdatePlayAgainButtonAnim(mouseOverPlayAgain && mouseDown);
    HandlePlayAgainButton(playAgainBtn);

    UpdateTilePressAnim();

    // DRAW
    BeginDrawing();
    ClearBackground((Color){20, 22, 34, 255});

    DrawTitle(W);
    DrawScoreboard(W);

    DrawFancyBox(boxRect, 12, 4, 10, 4, (Color){9, 10, 16, 255},
                 (Color){52, 58, 75, 255}, (Color){28, 33, 48, 255}, 0.01f, 10);

    DrawBoard(boardRect);
    DrawStatusText(W);
    DrawResetButton(resetBtn, W);
    if (winner != 0)
      DrawPlayAgainButton(playAgainBtn, W);

    EndDrawing();
  }

  CloseWindow();
  return 0;
}
