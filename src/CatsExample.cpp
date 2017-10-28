#include "Cats.h"
#include <SDL.h>

int main() {
  Cats::Init(640, 480);
  Cats::SetBackgroundColor(0xff, 0, 0);
  Cats::LoadSprite("../data/sprite.json");
  int spriteId = Cats::CreateSpriteInstance("sprite");
  Cats::RemoveSpriteInstance(spriteId);
  spriteId = Cats::CreateSpriteInstance("sprite");

  int lastFrameTime = SDL_GetTicks();
  bool running = true;
  bool visible = true;
  SDL_Event event;

  while(running) {
    while(SDL_PollEvent(&event)) {
      if(event.type == SDL_QUIT) {
	running = false;
      } else if(event.type == SDL_KEYDOWN && event.key.repeat == 0) {
	if(event.key.keysym.sym == SDLK_ESCAPE) {
	  running = false;
	} else if(event.key.keysym.sym == SDLK_h) {
	  visible = !visible;
	  Cats::ShowSprite(spriteId, visible);
	}
      } else if(event.type == SDL_KEYUP) {
      }
    }

    float delta = (SDL_GetTicks() - lastFrameTime) / 1000.0f;
    lastFrameTime = SDL_GetTicks();
    Cats::Redraw(delta);
  }

  return 0;
}
