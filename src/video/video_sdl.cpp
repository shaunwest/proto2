//
//  vido_sdl.cpp
//  Proto2
//
//  Created by Shaun West on 5/29/17.
//
//

#include "video_sdl.h"

// Initialize all of the important SDL stuff
VideoSDL::VideoSDL(const WindowSpec &window_spec) {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    LOG(LOG_ERROR) << "Failed to init SDL";
    return;
  }

  // Init image formats (PNG & JPG supported only)
  int imageFormats = IMG_INIT_PNG | IMG_INIT_JPG;
  int imageFormatsInitialized = IMG_Init(imageFormats);
  if ((imageFormatsInitialized & imageFormats) != imageFormats) {
    LOG(LOG_ERROR) << "Failed to init SDL Image";
    return;
  }

  font = FontTTF("assets/fonts/FreeSans.ttf");

  init_window(window_spec);
}

VideoSDL::~VideoSDL() {
  LOG(LOG_INFO) << "video_sdl destroyed";
  IMG_Quit();
  SDL_Quit();
}

void VideoSDL::init_window(const WindowSpec &window_spec) {
  window = create_window(window_spec);
  renderer = create_renderer(window.get());

  int display_index = SDL_GetWindowDisplayIndex(window.get());
  SDL_DisplayMode current;
  if (SDL_GetCurrentDisplayMode(display_index, &current) != 0) {
    LOG(LOG_ERROR) << "Failed to get display mode";
    return;
  }

  SDL_SetRenderDrawColor(renderer.get(), 64, 64, 64, 255);
  SDL_RenderSetLogicalSize(
    renderer.get(),
    window_spec.resolution.width,
    window_spec.resolution.height
  );

  LOG(LOG_INFO) << "Video initialized";
}

UniqueWindow VideoSDL::create_window(const WindowSpec &window_spec) const {
  auto flags = 0;

  if (window_spec.fullscreen) {
    flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
  }

  // Create the main game window
  UniqueWindow new_window(SDL_CreateWindow(
    window_spec.title.c_str(),
    SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED,
    window_spec.size.width,
    window_spec.size.height,
    flags
  ));

  // Check that the window was successfully created
  if (new_window == nullptr) {
    LOG(LOG_ERROR) << "Could not create window: " << SDL_GetError();
    return nullptr;
  }

  LOG(LOG_INFO) << "Window initialized";

  return new_window;
}

UniqueRenderer VideoSDL::create_renderer(SDL_Window * window) const {
  // NOTE: In non-tech demo games VSYNC should be configurable by user
  UniqueRenderer new_renderer(SDL_CreateRenderer(window, -1,
    SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));

  // Check that renderer was successfully created
  if (new_renderer == nullptr) {
    LOG(LOG_ERROR) << "SDL_CreateRenderer Error: " << SDL_GetError();
    return nullptr;
  }

  return new_renderer;
}

UniqueTexture VideoSDL::create_image(std::string image_path) {
  UniqueSurface surface = UniqueSurface(IMG_Load(image_path.c_str()));

  if (surface == nullptr) {
    LOG(LOG_ERROR) << "Error loading surface " << SDL_GetError();
    return nullptr;
  }

  // TODO should check if image was created
  UniqueTexture texture = UniqueTexture(SDL_CreateTextureFromSurface(
    renderer.get(),
    surface.get())
  );

  return texture;
}

// Must be called before rendering
void VideoSDL::render_begin() const {
  SDL_RenderClear(renderer.get());
}

// Must be called when ready to render
void VideoSDL::render_end() const {
  SDL_RenderPresent(renderer.get());
}

void VideoSDL::render_string(std::string str, Vector2i position) const {
  SDL_Surface* stats_surface = font.get_font(str.c_str());
  SDL_Texture* stats_texture = SDL_CreateTextureFromSurface(renderer.get(), stats_surface);
  SDL_Rect rect = { position.x, position.y, 0, 0 };
  SDL_QueryTexture(stats_texture, nullptr, nullptr, &rect.w, &rect.h);
  SDL_FreeSurface(stats_surface);
  SDL_RenderCopy(renderer.get(), stats_texture, nullptr, &rect);
  SDL_DestroyTexture(stats_texture);
}

void VideoSDL::render_texture(SDL_Texture *texture) const {
  SDL_RenderCopy(renderer.get(), texture, nullptr, nullptr);
}

void VideoSDL::render_texture(SDL_Texture *texture, Recti src, Recti dest, bool flip) const {
  SDL_Rect src_rect = {src.x, src.y, src.width, src.height};
  SDL_Rect dest_rect = {dest.x, dest.y, dest.width, dest.height};
  SDL_RenderCopyEx(
      renderer.get(),
      texture,
      &src_rect,
      &dest_rect,
      0.0,
      nullptr,
      flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE
  );
}

// TODO not sure if this is really necessary
void VideoSDL::get_display_mode() {
  SDL_DisplayMode current;

  // Get current display mode of all displays.
  for(int i = 0; i < SDL_GetNumVideoDisplays(); ++i){
    int should_be_zero = SDL_GetCurrentDisplayMode(i, &current);

    if(should_be_zero != 0) {
      std::cout << "Could not get display mode for video display " << i
      << " " << SDL_GetError() << std::endl;
    } else {
      // On success, print the current display mode.
      std::cout << "W " << current.w << " H " << current.h
      << " RR " << current.refresh_rate << std::endl;
    }
  }
}
