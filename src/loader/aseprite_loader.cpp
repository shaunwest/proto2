//
//  aseprite_loader.cpp
//  Proto2
//
//  Created by Shaun West on 7/25/17.
//
//

#include "aseprite_loader.h"

AsepriteLoader::AsepriteLoader() {}

SpriteFrameset AsepriteLoader::load(std::string json_path, VideoSDL &video) {
  Json::Value json_config = get_json(json_path);
  return get_frameset(json_config, video);
}

SpriteFrameset AsepriteLoader::get_frameset(Json::Value frameset_config, VideoSDL &video) {
  Json::Value meta_config = frameset_config["meta"];
  Json::Value frames_config = frameset_config["frames"];

  video.create_image(meta_config.get("image", "UTF-32" ).asString());

  // Assume dimensions of first frame apply to all frames
  SpriteFrameset frameset = {
    frames_config[0]["frame"]["w"].asInt(),
    frames_config[0]["frame"]["h"].asInt(),
    "default"
  };

  // TODO use newer C++11 loops?
  for (int index = 0; index < frames_config.size(); ++index) {
    Json::Value frame_config = frames_config[index];

    // We're using filename as an identifier string, not actually a file
    std::string name = frame_config["filename"].asString();
    frameset.frames[name].push_back(get_frame(frame_config));
  }

  return frameset;
}

SpriteFrame AsepriteLoader::get_frame(Json::Value frame_config) {
  Json::Value dims = frame_config["frame"];

  SpriteFrame frame = {
    dims["x"].asInt(),
    dims["y"].asInt(),
    frame_config["duration"].asFloat(),
    frame_config["rotated"].asBool()
  };

  return frame;
}
