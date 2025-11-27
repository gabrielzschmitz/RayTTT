#include "game.h"

float tilePressAnim[3][3] = {0};
bool tilePressedState[3][3] = {false};

int board[3][3];
int current = 1;
int winner = 0;

int scoreX = 0;
int scoreO = 0;
int scoreDraw = 0;

void ResetBoard() {
  for (int r = 0; r < 3; r++)
    for (int c = 0; c < 3; c++)
      board[r][c] = 0;

  current = 1;
  winner = 0;
}

int CheckWinner() {
  // Check rows
  for (int r = 0; r < 3; r++)
    if (board[r][0] > 0 && board[r][0] == board[r][1] &&
        board[r][1] == board[r][2])
      return board[r][0];

  // Check columns
  for (int c = 0; c < 3; c++)
    if (board[0][c] > 0 && board[0][c] == board[1][c] &&
        board[1][c] == board[2][c])
      return board[0][c];

  // Check diagonals
  if (board[0][0] > 0 && board[0][0] == board[1][1] &&
      board[1][1] == board[2][2])
    return board[0][0];

  if (board[0][2] > 0 && board[0][2] == board[1][1] &&
      board[1][1] == board[2][0])
    return board[0][2];

  // Check for draw (board full)
  bool full = true;
  for (int r = 0; r < 3; r++)
    for (int c = 0; c < 3; c++)
      if (board[r][c] == 0)
        full = false;

  return full ? 3 : 0;
}

void SetTilePressed(int row, int col, bool pressed) {
  tilePressedState[row][col] = pressed;
}

void UpdateTilePressAnim() {
  const float pressStep = 0.2f;

  for (int r = 0; r < 3; r++) {
    for (int c = 0; c < 3; c++) {
      float target = tilePressedState[r][c] ? 0.5f : 0.0f;

      if (tilePressAnim[r][c] < target) {
        tilePressAnim[r][c] += pressStep;
        if (tilePressAnim[r][c] > target)
          tilePressAnim[r][c] = target;
      } else if (tilePressAnim[r][c] > target) {
        tilePressAnim[r][c] -= pressStep;
        if (tilePressAnim[r][c] < target)
          tilePressAnim[r][c] = target;
      }
    }
  }
}
