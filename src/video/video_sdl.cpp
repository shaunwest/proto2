//
//  sdl_renderer.cpp
//  Proto2
//
//  Created by Shaun West on 5/29/17.
//
//

#include "video_sdl.h"

#include "util/log.h"

// Initialize all of the important SDL stuff
VideoSDL::VideoSDL(const WindowSpec &window_spec, const AssetPaths &asset_paths) : asset_paths(asset_paths) {
  
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    LOG(LOG_ERROR) << "Failed to init SDL";
    return;
  }
  
  // Init image formats (PNG & JPG supported only)
  int imageFormats = IMG_INIT_PNG | IMG_INIT_JPG;
  int imageFormatsInitialized = IMG_Init(imageFormats);
  if ((imageFormatsInitialized & imageFormats) != imageFormats) {
    std::cout << "Failed to init SDL Image" << std::endl;
    return;
  }
  
  font = FontTTF(asset_paths.fontsPath + "/FreeSans.ttf");
  
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
  
  LOG(LOG_INFO) << "video_sdl initialized";
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
    std::cout << "Could not create window: " << SDL_GetError() << std::endl;
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
    std::cout << "SDL_CreateRenderer Error" << std::endl;
    return nullptr;
  }
  
  return new_renderer;
}

void VideoSDL::create_image(std::string image_name) {
  std::string image_path = asset_paths.imagesPath + "/" + image_name;
  surfaces[image_name] = UniqueSurface(IMG_Load(image_path.c_str()));
  
  if (surfaces[image_name] == nullptr) {
    std::cout << "Image not found: " << image_name << std::endl;
  }
  
  images[image_name] = UniqueTexture(SDL_CreateTextureFromSurface(
    renderer.get(),
    surfaces[image_name].get())
  );
  
  //SDL_FreeSurface(temp_surface);
}

void VideoSDL::create_image(std::string image_name, SDL_Surface *surface) {
  images[image_name] = UniqueTexture(SDL_CreateTextureFromSurface(
    renderer.get(),
    surfaces[image_name].get())
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

void VideoSDL::render_string(std::string str, Vector position) const {
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

void VideoSDL::render_image(std::string image_name) const {
  render_texture(images.at(image_name).get());
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
