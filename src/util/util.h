//
//  util.h
//  Proto2
//
//  Created by Shaun West on 6/10/17.
//
//

#ifndef util_h
#define util_h

#include <iostream>
#include <chrono>
#include <ctime>

#include "json/json.h"

// Equivalent to "new". Built-in part of C++14 (http://en.cppreference.com/w/cpp/memory/unique_ptr/make_unique)
template<typename T, typename ...Args>
std::unique_ptr<T> make_unique(Args&& ...args) {
  return std::unique_ptr<T>( new T( std::forward<Args>(args)... ) );
}

std::string time_now();
Json::Value get_json(std::string asset_path);

#endif /* util_h */
