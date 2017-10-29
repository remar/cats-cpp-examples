#include "Cats.h"
#include <SDL.h>

const int screenWidth = 640;
const int screenHeight = 480;

int main() {
  Cats::Init(screenWidth, screenHeight);
  Cats::SetBackgroundColor(0xff, 0, 0);
  Cats::LoadSprite("../data/sprite.json");
  int spriteId = Cats::CreateSpriteInstance("sprite");
  Cats::RemoveSpriteInstance(spriteId);
  spriteId = Cats::CreateSpriteInstance("sprite");
  Cats::LoadTileset("../data/tiles.json");
  Cats::SetupTileLayer(20, 15, 32, 32);
  Cats::SetTile(0, 0, "tiles", 0, 0);

  int lastFrameTime = SDL_GetTicks();
  bool running = true;
  bool visible = true;
  SDL_Event event;
  float x = 0;
  float dx = 100;
  float maxX = screenWidth - 16;
  float minX = 0;

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

    x += dx * delta;
    if(x >= maxX) {
      dx = -dx;
      x = maxX;
      Cats::SetAnimation(spriteId, "walk left");
    } else if(x <= minX) {
      dx = -dx;
      x = minX;
      Cats::SetAnimation(spriteId, "walk right");
    }

    Cats::SetSpritePosition(spriteId, x, screenHeight / 2);
    Cats::Redraw(delta);
  }

  return 0;
}
