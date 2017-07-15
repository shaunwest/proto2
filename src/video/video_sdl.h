//
//  video_sdl.h
//  Proto2
//
//  Created by Shaun West on 5/29/17.
//
//

#ifndef video_sdl_h
#define video_sdl_h

#include <iostream>
#include <map>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

#include "util/util.h"
#include "font_ttf.h"

struct Rect {
  int x, y;
  int w, h;
};

struct SDLDeleter
{
  void operator()(SDL_Surface *p) const {
    SDL_FreeSurface(p);
    std::cout << "SDL Surface freed" << std::endl;
  }
  void operator()(SDL_Texture *p) const {
    SDL_DestroyTexture(p);
    std::cout << "SDL Texture destroyed" << std::endl;
  }
  void operator()(SDL_Renderer *r) const {
    SDL_DestroyRenderer(r);
    std::cout << "SDL Renderer destroyed" << std::endl;
  }
  void operator()(SDL_Window *w) const {
    SDL_DestroyWindow(w);
    std::cout << "SDL Window destroyed" << std::endl;
  }
};

typedef std::unique_ptr<SDL_Surface, SDLDeleter> UniqueSurface;
typedef std::unique_ptr<SDL_Texture, SDLDeleter> UniqueTexture;
typedef std::unique_ptr<SDL_Renderer, SDLDeleter> UniqueRenderer;
typedef std::unique_ptr<SDL_Window, SDLDeleter> UniqueWindow;

// TODO can some of these properties be const?
struct WindowSpec
{
  std::string title;
  Size size;
  Size resolution;
  bool fullscreen;
};

struct AssetPaths {
  std::string imagesPath;
  std::string fontsPath;
};

class VideoSDL
{
public:
  VideoSDL(const WindowSpec &window_spec, const AssetPaths &asset_paths);
  ~VideoSDL();
  void init_window(const WindowSpec &window_spec);
  void create_image(std::string image_name);
  void create_image(std::string image_name, SDL_Surface *surface);
  void recreate_images();
  UniqueWindow create_window(const WindowSpec &window_spec) const;
  UniqueRenderer create_renderer(SDL_Window * window) const;
  void render_begin() const;
  void render_end() const;
  void render_texture(SDL_Texture *texture) const;
  void render_image(std::string image_name) const;
  void render_string(std::string str, Vector position) const;
  void get_display_mode();
private:
  UniqueRenderer renderer;
  UniqueWindow window;
  FontTTF font;
  const AssetPaths &asset_paths;
  std::map<std::string, UniqueSurface> surfaces;
  std::map<std::string, UniqueTexture> images;
};

#endif /* video_sdl_h */
