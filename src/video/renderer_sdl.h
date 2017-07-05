//
//  renderer_sdl.h
//  Proto2
//
//  Created by Shaun West on 5/29/17.
//
//

#ifndef renderer_sdl_h
#define renderer_sdl_h

#include <iostream>
#include <sstream>

#include "SDL.h"
#include "SDL_image.h"

#include "lib/SDL_FontCache.h"
#include "util/util.h"

struct Rect {
  int x, y;
  int w, h;
};

struct SDLDeleter
{
  void operator()(SDL_Surface *p) const { SDL_FreeSurface(p); }
  void operator()(SDL_Texture *p) const { SDL_DestroyTexture(p); }
  void operator()(SDL_Renderer *r) const {
    SDL_DestroyRenderer(r);
    std::cout << "SDL Renderer destroyed" << std::endl;
  }
  void operator()(SDL_Window *w) const {
    SDL_DestroyWindow(w);
    std::cout << "SDL Window destroyed" << std::endl;
  }
  void operator()(FC_Font *f) const {
    FC_FreeFont(f);
    std::cout << "FC Font Freed" << std::endl;
  }
};

typedef std::unique_ptr<SDL_Surface, SDLDeleter> UniqueSurface;
typedef std::unique_ptr<SDL_Texture, SDLDeleter> UniqueTexture;
typedef std::unique_ptr<SDL_Renderer, SDLDeleter> UniqueRenderer;
typedef std::unique_ptr<SDL_Window, SDLDeleter> UniqueWindow;
typedef std::unique_ptr<FC_Font, SDLDeleter> UniqueFont;

struct WindowSpec
{
  std::string title;
  Size size;
  Size resolution;
};

class RendererSDL
{
public:
  RendererSDL(const WindowSpec &window_spec, const AssetPaths &asset_paths);
  ~RendererSDL();
  UniqueTexture create_texture(std::string image_name) const;
  void create_window(const WindowSpec &window_spec);
  void render_begin() const;
  void render_end();
  void render_texture(SDL_Texture *texture, SDL_Rect src, SDL_Rect dest) const;
  void get_display_mode();
  std::ostringstream & render_string();
public:
  bool ready = false;
private:
  UniqueRenderer renderer;
  UniqueWindow window;
  UniqueFont font;
  std::ostringstream os;
  const AssetPaths &asset_paths;
};

#endif /* renderer_sdl_h */
