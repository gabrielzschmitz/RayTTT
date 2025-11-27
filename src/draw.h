#ifndef DRAW_H
#define DRAW_H

#include "raylib.h"

// Text & UI Drawing
void DrawCenteredText(const char *txt, int y, int size, Color col, int screenW);
void DrawFancyBox(Rectangle rect, float pad, int outlineThick, int shadowOff,
                  int shadowExpand, Color shadowColor, Color outlineColor,
                  Color mainColor, float roundness, int seg);

// Game Drawing
void DrawBoard(Rectangle rect);
void DrawTitle(int screenW);
void DrawStatusText(int screenW);

#endif // DRAW_H
