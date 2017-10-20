#include "Cats.h"
#include <SDL.h>

int main() {
  Cats::Init(640, 480);
  Cats::SetBackgroundColor(0xff, 0, 0);
  Cats::Redraw(0);
  Cats::LoadSprite("../data/sprite.json");
  SDL_Delay(3000);
  return 0;
}
