#ifndef UI_H
#define UI_H

#include "raylib.h"

// Scoreboard & Buttons
void DrawScoreboard(int screenW);
void DrawResetButton(Rectangle btn, int screenW);
void DrawPlayAgainButton(Rectangle btn, int screenW);
Color MixColors(Color c1, Color c2);

// Reset button UI
void SetResetButtonPressed(bool pressed);
void UpdateResetButtonAnim(bool pressed);
float GetResetButtonPressAmount();

// Play Again button UI
void SetPlayAgainButtonPressed(bool pressed);
void UpdatePlayAgainButtonAnim(bool pressed);
float GetPlayAgainButtonPressAmount();

#endif // UI_H
