#include "ui.h"
#include "draw.h"
#include "game.h"

static float resetButtonPressAnim = 0.0f;
static bool resetButtonPressed = false;
static float playAgainButtonPressAnim = 0.0f;
static bool playAgainButtonPressed = false;

void DrawScoreboard(int screenW) {
  Rectangle content = {110, 140, 380, 40};

  DrawFancyBox(content, 12, 4, 10, 4, (Color){9, 10, 16, 255},
               (Color){52, 58, 75, 255}, (Color){28, 33, 48, 255}, 0.01f, 10);

  DrawCenteredText("PLAYER X       DRAWS       PLAYER O", 135, 20, GRAY,
                   screenW);

  int f = 30;
  int y = 160;

  DrawText(TextFormat("%d", scoreX), 185, y, f, (Color){255, 0, 200, 255});
  DrawText(TextFormat("%d", scoreDraw), 285, y, f, (Color){251, 113, 0, 255});
  DrawText(TextFormat("%d", scoreO), 395, y, f, (Color){0, 255, 100, 255});
}

void DrawResetButton(Rectangle btn, int screenW) {
  Vector2 mousePos = GetMousePosition();

  bool hover = CheckCollisionPointRec(mousePos, btn);
  float pressAmount = GetResetButtonPressAmount();

  float maxPressOffset = 6.0f;
  float pressOffset = pressAmount * maxPressOffset;

  int baseShadowOff = 6;
  int baseShadowExpand = 3;

  int shadowOff = baseShadowOff - (int)(pressAmount * baseShadowOff);
  int shadowExpand = baseShadowExpand - (int)(pressAmount * baseShadowExpand);

  Color mainCol = hover ? (Color){52, 58, 75, 255} : (Color){28, 33, 48, 255};
  Color outlineCol = (Color){52, 58, 75, 255};
  Color shadowCol = (Color){9, 10, 16, 255};

  Rectangle pressedRect = {btn.x, btn.y + pressOffset, btn.width, btn.height};

  DrawFancyBox(pressedRect, 8, 4, shadowOff, shadowExpand, shadowCol,
               outlineCol, mainCol, 0.1f, 10);

  Color textCol = hover ? (Color){9, 10, 16, 255} : WHITE;
  DrawCenteredText("RESET SCORES", pressedRect.y + 5, 20, textCol, screenW);
}

void SetResetButtonPressed(bool pressed) { resetButtonPressed = pressed; }

void UpdateResetButtonAnim(bool pressed) {
  float speed = 0.2f;
  float target = pressed ? 1.0f : 0.0f;

  if (resetButtonPressAnim < target) {
    resetButtonPressAnim += speed;
    if (resetButtonPressAnim > target)
      resetButtonPressAnim = target;
  } else if (resetButtonPressAnim > target) {
    resetButtonPressAnim -= speed;
    if (resetButtonPressAnim < target)
      resetButtonPressAnim = target;
  }
}

float GetResetButtonPressAmount() { return resetButtonPressAnim; }

Color MixColors(Color c1, Color c2) {
  Color result;
  result.r = (c1.r + c2.r) / 2;
  result.g = (c1.g + c2.g) / 2;
  result.b = (c1.b + c2.b) / 2;
  result.a = (c1.a + c2.a) / 2;
  return result;
}

void DrawPlayAgainButton(Rectangle btn, int screenW) {
  Vector2 mousePos = GetMousePosition();

  bool hover = CheckCollisionPointRec(mousePos, btn);
  float pressAmount = GetPlayAgainButtonPressAmount();

  float maxPressOffset = 6.0f;
  float pressOffset = pressAmount * maxPressOffset;

  int baseShadowOff = 6;
  int baseShadowExpand = 3;

  int shadowOff = baseShadowOff - (int)(pressAmount * baseShadowOff);
  int shadowExpand = baseShadowExpand - (int)(pressAmount * baseShadowExpand);

  Color mainCol =
      hover ? (Color){52, 58, 75, 255}
            : MixColors((Color){255, 0, 200, 255}, (Color){0, 255, 100, 255});
  Color outlineCol = (Color){52, 58, 75, 255};
  Color shadowCol = (Color){9, 10, 16, 255};

  Rectangle pressedRect = {btn.x, btn.y + pressOffset, btn.width, btn.height};

  DrawFancyBox(pressedRect, 8, 4, shadowOff, shadowExpand, shadowCol,
               outlineCol, mainCol, 0.1f, 10);

  Color textCol = hover ? (Color){9, 10, 16, 255} : WHITE;
  DrawCenteredText("PLAY AGAIN", pressedRect.y, 20, textCol, screenW);
}

void SetPlayAgainButtonPressed(bool pressed) {
  playAgainButtonPressed = pressed;
}

void UpdatePlayAgainButtonAnim(bool pressed) {
  float speed = 0.2f;
  float target = pressed ? 1.0f : 0.0f;

  if (playAgainButtonPressAnim < target) {
    playAgainButtonPressAnim += speed;
    if (playAgainButtonPressAnim > target)
      playAgainButtonPressAnim = target;
  } else if (playAgainButtonPressAnim > target) {
    playAgainButtonPressAnim -= speed;
    if (playAgainButtonPressAnim < target)
      playAgainButtonPressAnim = target;
  }
}

float GetPlayAgainButtonPressAmount() { return playAgainButtonPressAnim; }
