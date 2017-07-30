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
  image_id = 0;

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

  if (images.size() > 0) {
    recreate_images();
  }

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

// TODO this needs to save the path as well, so if called again with the same
// path, it won't be loaded from disk again
int VideoSDL::create_image(std::string image_path) {
  std::string full_image_path = image_path;
  image_id++;
  surfaces[image_id] = UniqueSurface(IMG_Load(full_image_path.c_str()));

  if (surfaces[image_id] == nullptr) {
    LOG(LOG_ERROR) << "Image not found: " << full_image_path;
  }
  else {
    images[image_id] = UniqueTexture(SDL_CreateTextureFromSurface(
      renderer.get(),
      surfaces[image_id].get())
    );
  }

  return image_id;
}

void VideoSDL::create_image(int image_id, SDL_Surface *surface) {
  images[image_id] = UniqueTexture(SDL_CreateTextureFromSurface(
    renderer.get(),
    surfaces[image_id].get())
  );
}

// Create images from all stored surfaces
// Note: surfaces are stored in regular RAM and textures in VRAM
void VideoSDL::recreate_images() {
  for (auto const &kv : surfaces) {
    create_image(kv.first, kv.second.get());
  }
}

// Must be called before rendering
void VideoSDL::render_begin() const {
  SDL_RenderClear(renderer.get());
}

// Must be called when ready to render
void VideoSDL::render_end() const {
  SDL_RenderPresent(renderer.get());
}

void VideoSDL::render_string(std::string str, IntVector2 position) const {
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

void VideoSDL::render_texture(SDL_Texture *texture, IntRect src, IntRect dest) const {
  SDL_Rect src_rect = {src.x, src.y, src.width, src.height};
  SDL_Rect dest_rect = {dest.x, dest.y, dest.width, dest.height};
  SDL_RenderCopy(renderer.get(), texture, &src_rect, &dest_rect);
}

void VideoSDL::render_image(int image_id) const {
  render_texture(images.at(image_id).get());
}

void VideoSDL::render_image(int image_id, IntRect src, IntRect dest) const {
  render_texture(images.at(image_id).get(), src, dest);
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
