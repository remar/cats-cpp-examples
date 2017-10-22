#include "Cats.h"
#include <SDL.h>

int main() {
  Cats::Init(640, 480);
  Cats::SetBackgroundColor(0xff, 0, 0);
  Cats::LoadSprite("../data/sprite.json");
  Cats::CreateSpriteInstance("sprite");

  int startTime = SDL_GetTicks();
  int lastFrameTime = SDL_GetTicks();
  bool running = true;

  while(running) {
    float delta = (SDL_GetTicks() - lastFrameTime) / 1000.0f;
    lastFrameTime = SDL_GetTicks();
    Cats::Redraw(delta);
    if(SDL_GetTicks() - startTime > 3000) {
      running = false;
    }
  }

  return 0;
}
