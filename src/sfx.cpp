#include "sfx.h"

Sound clickTileSound;
Sound clickButtonSound;

void InitSfx() {
  InitAudioDevice();
  clickTileSound = LoadSound("click1.wav");
  clickButtonSound = LoadSound("click2.wav");
}

void UnloadSfx() {
  UnloadSound(clickTileSound);
  UnloadSound(clickButtonSound);
  CloseAudioDevice();
}
