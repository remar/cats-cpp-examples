#include "Cats.h"
#include <SDL.h>

int main() {
  Cats::Init(640, 480);
  Cats::Redraw(0);
  SDL_Delay(3000);
  return 0;
}
