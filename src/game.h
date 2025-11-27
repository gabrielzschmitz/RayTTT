#ifndef GAME_H
#define GAME_H

#include "raylib.h"

// Board and game state
extern int board[3][3];
extern int current;
extern int winner;

extern int scoreX;
extern int scoreO;
extern int scoreDraw;

// Tile press animation states
extern float tilePressAnim[3][3]; // 0.0f to 1.0f
extern bool tilePressedState[3][3];
extern float selectorPressAnim;
extern bool selectorPressed;

void ResetBoard();
int CheckWinner();

void ResetTiles();
void SetTilePressed(int row, int col, bool pressed);
void UpdateTilePressAnim();
void UpdateSelectorPressAnim();

#endif // GAME_H
