//
//  sdl_renderer.cpp
//  Proto2
//
//  Created by Shaun West on 5/29/17.
//
//

#include "renderer_sdl.h"

#include "util/log.h"

// Initialize all of the important SDL stuff
RendererSDL::RendererSDL(const WindowSpec &window_spec, const AssetPaths &asset_paths) : asset_paths(asset_paths) {
  
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
  
  create_window(window_spec);
  get_display_mode();
  
  // Create renderer
  // TODO: explain options
  // TODO: VSYNC should be configurable by user?
  renderer = UniqueRenderer(SDL_CreateRenderer(window.get(), -1,
    SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));

  // Check that renderer was successfully created
  if (renderer == nullptr) {
    std::cout << "SDL_CreateRenderer Error" << std::endl;
    return;
  }
  
  int display_index = SDL_GetWindowDisplayIndex(window.get());
  SDL_DisplayMode current;
  if (SDL_GetCurrentDisplayMode(display_index, &current) != 0) {
    LOG(LOG_ERROR) << "Failed to get display mode";
    return;
  }
  
  SDL_Rect viewport = {0, 0, 512, 480};
  
  /*float scale;
  if (current.h <= current.w) {
    scale = current.h / 240;
  }
  else {
    scale = current.w / 256;
  }*/
  
  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, 0);
  SDL_SetRenderDrawColor(renderer.get(), 64, 64, 64, 255);
  
  /*if (SDL_RenderSetViewport(renderer.get(), &viewport) != 0) {
    LOG(LOG_ERROR) << "Failed to set viewport";
    return;
  }*/
  
  SDL_RenderSetScale(renderer.get(), 2.0f, 2.0f);
  
  // uh... how does this work with viewport??
  //SDL_RenderSetLogicalSize(renderer.get(), 256, 240);
  
  // Init font
  font = UniqueFont(FC_CreateFont());
  
  FC_LoadFont(
    font.get(),
    renderer.get(),
    (asset_paths.fontsPath + "/joystix.ttf").c_str(),
    12,
    FC_MakeColor(255,255,255,255),
    TTF_STYLE_NORMAL
  );
  
  ready = true;
  LOG(LOG_INFO) << "Renderer_SDL initialized" << std::endl;
}

RendererSDL::~RendererSDL() {
  LOG(LOG_INFO) << "Renderer_SDL destroyed" << std::endl;
  IMG_Quit();
  SDL_Quit();
}

void RendererSDL::create_window(const WindowSpec &window_spec) {
  Uint32 flags = 0;
  
  if (window_spec.size.width == 0 || window_spec.size.height == 0) {
    flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
  }
  
  // Create the main game window
  window = UniqueWindow(SDL_CreateWindow(
    window_spec.title.c_str(),
    SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED,
    window_spec.size.width,
    window_spec.size.height,
    flags
  ));
  
  // Check that the window was successfully created
  if (window == nullptr) {
    std::cout << "Could not create window: " << SDL_GetError() << std::endl;
    return;
  }
}

void RendererSDL::get_display_mode() {
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

UniqueTexture RendererSDL::create_texture(std::string image_name) const {
  SDL_Surface *temp_surface = IMG_Load((asset_paths.imagesPath + "/" + image_name).c_str());
  
  if (temp_surface == NULL) {
    std::cout << "Image not found: " << image_name << std::endl;
  }
  
  UniqueTexture texture = UniqueTexture(SDL_CreateTextureFromSurface(renderer.get(), temp_surface));
  
  SDL_FreeSurface(temp_surface);
  
  return texture;
}

// Must be called before rendering
void RendererSDL::render_begin() const {
  SDL_RenderClear(renderer.get());
}

// Must be called when ready to render
void RendererSDL::render_end() {
  std::string os_string = os.str();
  
  if (os_string.size() > 0) {
    FC_Draw(font.get(), renderer.get(), 0, 0, os_string.c_str());
    os.clear();
    os.str("");
  }
  
  SDL_RenderPresent(renderer.get());
}

void RendererSDL::render_texture(SDL_Texture *texture, SDL_Rect src, SDL_Rect dest) const {
  SDL_RenderCopy(renderer.get(), texture, nullptr, &dest);
}

std::ostringstream & RendererSDL::render_string() {
  return os;
}
