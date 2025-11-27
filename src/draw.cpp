#include "draw.h"
#include "game.h"

void DrawCenteredText(const char *txt, int y, int size, Color col,
                      int screenW) {
  int w = MeasureText(txt, size);
  DrawText(txt, (screenW - w) / 2, y, size, col);
}

void DrawFancyBox(Rectangle content, float pad, int outlineThick, int shadowOff,
                  int shadowExpand, Color shadowCol, Color outlineCol,
                  Color mainCol, float round, int seg) {
  Rectangle mainBox = {content.x - pad, content.y - pad,
                       content.width + pad * 2, content.height + pad * 2};

  Rectangle outlineBox = {mainBox.x - outlineThick, mainBox.y - outlineThick,
                          mainBox.width + outlineThick * 2,
                          mainBox.height + outlineThick * 2};

  Rectangle shadowBox = {mainBox.x + shadowOff - shadowExpand,
                         mainBox.y + shadowOff - shadowExpand,
                         mainBox.width + shadowExpand * 2,
                         mainBox.height + shadowExpand * 2};

  DrawRectangleRounded(shadowBox, round, seg, shadowCol);
  DrawRectangleRounded(outlineBox, round, seg, outlineCol);
  DrawRectangleRounded(mainBox, round, seg, mainCol);
}

void DrawBoard(Rectangle rect) {
  float cell = rect.width / 3.0f;
  float pad = 10;

  Color tileNormal = {50, 55, 70, 255};
  Color tileHover = {60, 65, 80, 255};
  Color shadowCol = {12, 14, 20, 180};
  Color outlineCol = {52, 58, 75, 255};

  Vector2 mousePos = GetMousePosition();

  for (int r = 0; r < 3; r++) {
    for (int c = 0; c < 3; c++) {
      Rectangle tileRect = {rect.x + c * cell + pad, rect.y + r * cell + pad,
                            cell - pad * 2, cell - pad * 2};

      float pressAmount = tilePressAnim[r][c]; // 0..1
      float maxPressOffset = 6.0f;
      float pressOffset = pressAmount * maxPressOffset;

      // Adjust shadow offset based on press amount
      int baseShadowOff = 4;
      int baseShadowExpand = 0;

      int shadowOff = baseShadowOff - (int)(pressAmount * baseShadowOff);
      int shadowExpand =
          baseShadowExpand - (int)(pressAmount * baseShadowExpand);

      if (shadowOff < 0)
        shadowOff = 0;
      if (shadowExpand < 0)
        shadowExpand = 0;

      bool hover = CheckCollisionPointRec(mousePos, tileRect);
      Color mainCol = hover ? tileHover : tileNormal;

      Rectangle pressedRect = {tileRect.x, tileRect.y + pressOffset,
                               tileRect.width, tileRect.height};

      DrawFancyBox(pressedRect, 0.0f, 0, shadowOff, shadowExpand, shadowCol,
                   outlineCol, mainCol, 0.0f, 10);

      if (board[r][c] == 1) {
        DrawText("X", pressedRect.x + pressedRect.width / 2 - 22,
                 pressedRect.y + pressedRect.height / 2 - 30, 70,
                 (Color){255, 0, 200, 255});
      } else if (board[r][c] == 2) {
        DrawText("O", pressedRect.x + pressedRect.width / 2 - 22,
                 pressedRect.y + pressedRect.height / 2 - 30, 70,
                 (Color){0, 255, 100, 255});
      }
    }
  }
}

void DrawTitle(int screenW) {
  DrawCenteredText("RAY TTT", 30, 60, (Color){255, 0, 200, 255}, screenW);
  DrawCenteredText("a c++ tictactoe", 90, 20, GRAY, screenW);
}

void DrawStatusText(int screenW) {
  if (winner == 0)
    DrawCenteredText(current == 1 ? "PLAYER X'S TURN" : "PLAYER O'S TURN", 682,
                     25, WHITE, screenW);
  else if (winner == 1)
    DrawCenteredText("X WINS! PRESS R", 662, 25, (Color){255, 0, 200, 255},
                     screenW);
  else if (winner == 2)
    DrawCenteredText("O WINS! PRESS R", 662, 25, (Color){0, 255, 100, 255},
                     screenW);
  else
    DrawCenteredText("DRAW! PRESS R", 662, 25, (Color){251, 113, 0, 255},
                     screenW);
}
