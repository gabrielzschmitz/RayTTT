#ifndef INPUT_H
#define INPUT_H

#include "raylib.h"

const int GAMEPAD = 0;

void HandleBoardClick(Rectangle boardRect);
void HandleResetButton(Rectangle btn);
void HandlePlayAgainButton(Rectangle btn);

void HandleGamepadInput(void);
void DrawGamepadSelector(Rectangle boardRect, Rectangle playAgainBtn,
                         Rectangle resetScoresBtn);

#endif // INPUT_H
