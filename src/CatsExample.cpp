#include "Cats.h"
#include <list>
#include <SDL.h>
#include <memory>

const int screenWidth = 640;
const int screenHeight = 480;

class CaptainGood {
  public:
    CaptainGood(int y) : x(0), y(y), pause(false) {
      spriteId = Cats::CreateSpriteInstance("sprite");
    }

    ~CaptainGood() {
      Cats::RemoveSpriteInstance(spriteId);
    }

    void update(float delta) {
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
      Cats::SetSpritePosition(spriteId, x, y);
    }

    void setVisible(bool show) {
      Cats::ShowSprite(spriteId, show);
    }

    void togglePause() {
      pause = !pause;
      Cats::PauseAnimation(spriteId, pause);
    }

  private:
    int spriteId;
    float x;
    int y;
    float dx = 100;
    float maxX = screenWidth - 16;
    float minX = 0;
    bool pause;
};

int main() {
  std::list<std::unique_ptr<CaptainGood>> goods;

  Cats::Init(screenWidth, screenHeight);
  Cats::ShowPointer(false);
  Cats::SetWindowTitle("CatsExample!");
  Cats::SetBackgroundColor(0xff, 0, 0);
  Cats::LoadSprite("../data/sprite.json");
  int spriteId = Cats::CreateSpriteInstance("sprite");
  Cats::RemoveSpriteInstance(spriteId);
  Cats::LoadTileset("../data/tiles.json");
  Cats::SetupTileLayer(20, 15, 32, 32);

  for(int i = 0;i < 10;i++) {
    Cats::SetTile(i, 0, "tiles", 0, 0);
    Cats::SetTile(i, 9, "tiles", 0, 0);
    Cats::SetTile(0, i, "tiles", 0, 0);
    Cats::SetTile(9, i, "tiles", 0, 0);
  }

  int lastFrameTime = SDL_GetTicks();
  bool running = true;
  bool visible = true;
  SDL_Event event;
  bool pauseAll = false;
  bool fullscreen = false;

  int startY = 0;
  float scrollx = 0;
  float scrolldx = 200;

  int relativeMoveSprite = Cats::CreateSpriteInstance("sprite");
  Cats::SetSpritePosition(relativeMoveSprite, 100, 100);

  goods.push_back(std::unique_ptr<CaptainGood>(new CaptainGood(screenHeight / 2)));

  while(running) {
    while(SDL_PollEvent(&event)) {
      if(event.type == SDL_QUIT) {
        running = false;
      } else if(event.type == SDL_KEYDOWN && event.key.repeat == 0) {
        switch(event.key.keysym.sym) {
	case SDLK_ESCAPE:
	  running = false;
	  break;
	case SDLK_h:
	  visible = !visible;
	  for(auto &good : goods) {
	    good->setVisible(visible);
	  }
	  break;
	case SDLK_c:
	  goods.push_back(std::unique_ptr<CaptainGood>(new CaptainGood(startY)));
	  startY = (startY + 24) % screenHeight;
	  break;
	case SDLK_d:
	  if(!goods.empty()) {
	    goods.pop_back();
	  }
	  break;
	case SDLK_o:
	  pauseAll = !pauseAll;
	  Cats::PauseAnimations(pauseAll);
	  break;
	case SDLK_p:
	  if(goods.size() > 0) {
	    (goods.front())->togglePause();
	  }
	  break;
	case SDLK_f:
	  fullscreen = !fullscreen;
	  Cats::SetFullscreen(fullscreen);
	  break;
	case SDLK_LEFT:
	  Cats::MoveSprite(relativeMoveSprite, -10, 0);
	  break;
	case SDLK_RIGHT:
	  Cats::MoveSprite(relativeMoveSprite, 10, 0);
	  break;
        }
      } else if(event.type == SDL_KEYUP) {
      }
    }

    float delta = (SDL_GetTicks() - lastFrameTime) / 1000.0f;
    lastFrameTime = SDL_GetTicks();

    for(auto &good : goods) {
      good->update(delta);
    }

    scrollx += delta * scrolldx;
    if(scrollx >= 200) {
      scrollx = 200;
      scrolldx = -scrolldx;
    } else if(scrollx <= 0) {
      scrollx = 0;
      scrolldx = -scrolldx;
    }
    Cats::SetScroll(scrollx, 0);

    Cats::Redraw(delta);
  }

  return 0;
}
