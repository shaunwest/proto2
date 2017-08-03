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
#include "util/log.h"
#include "font_ttf.h"

struct WindowSpec
{
  std::string title;
  Size size;
  Size resolution;
  bool fullscreen;
};

struct SDLDeleter
{
  void operator()(SDL_Surface *p) const {
    SDL_FreeSurface(p);
    LOG(LOG_INFO) << "SDL Surface freed";
  }
  void operator()(SDL_Texture *p) const {
    SDL_DestroyTexture(p);
    LOG(LOG_INFO) << "SDL Texture destroyed";
  }
  void operator()(SDL_Renderer *r) const {
    SDL_DestroyRenderer(r);
    LOG(LOG_INFO) << "SDL Renderer destroyed";
  }
  void operator()(SDL_Window *w) const {
    SDL_DestroyWindow(w);
    LOG(LOG_INFO) << "SDL Window destroyed";
  }
};

typedef std::unique_ptr<SDL_Surface, SDLDeleter> UniqueSurface;
typedef std::unique_ptr<SDL_Texture, SDLDeleter> UniqueTexture;
typedef std::unique_ptr<SDL_Renderer, SDLDeleter> UniqueRenderer;
typedef std::unique_ptr<SDL_Window, SDLDeleter> UniqueWindow;

class VideoSDL
{
public:
  VideoSDL(const WindowSpec &window_spec);
  ~VideoSDL();
  void init_window(const WindowSpec &window_spec);
  int create_image(std::string image_path);
  void create_image(int image_id, SDL_Surface *surface);
  UniqueTexture create_image2(std::string image_path);
  void recreate_images();
  void clear_images();
  UniqueWindow create_window(const WindowSpec &window_spec) const;
  UniqueRenderer create_renderer(SDL_Window * window) const;
  void render_begin() const;
  void render_end() const;
  void render_texture(SDL_Texture *texture) const;
  void render_texture(SDL_Texture *texture, IntRect src, IntRect dest) const;
  void render_image(int image_id) const;
  void render_image(int image_id, IntRect src, IntRect dest) const;
  void render_string(std::string str, IntVector2 position) const;
  void get_display_mode();
  UniqueRenderer renderer;
private:
  //UniqueRenderer renderer;
  UniqueWindow window;
  FontTTF font;
  std::map<int, UniqueSurface> surfaces;
  std::map<int, UniqueTexture> images;
  int image_id;
};

#endif /* video_sdl_h */
