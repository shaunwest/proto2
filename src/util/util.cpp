//
//  util.cpp
//  Proto2
//
//  Created by Shaun West on 6/19/17.
//
//

#include "util.h"

#include <fstream>

// Get the current time as a string formatted like 2017-06-19 21:32:38
std::string time_now() {
  std::chrono::time_point<std::chrono::system_clock> now;
  now = std::chrono::system_clock::now();
  std::time_t now_t = std::chrono::system_clock::to_time_t(now);

  char mbstr[20];
  if (std::strftime(mbstr, sizeof(mbstr), "%F %T", std::localtime(&now_t))) {
    return mbstr;
  }

  return "";
}

// TODO some kind of error reporting...
Json::Value get_json(std::string asset_path) {
  Json::Value root;
  std::ifstream config(asset_path, std::ifstream::binary);
  config >> root;

  return root;
}
