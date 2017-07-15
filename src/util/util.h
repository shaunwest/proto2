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

/*
struct AssetPaths {
  std::string imagesPath;
  std::string fontsPath;
};
*/

// Equivalent to "new". Built-in part of C++14 (http://en.cppreference.com/w/cpp/memory/unique_ptr/make_unique)
template<typename T, typename ...Args>
std::unique_ptr<T> make_unique(Args&& ...args) {
  return std::unique_ptr<T>( new T( std::forward<Args>(args)... ) );
}

std::string time_now();

struct Size {
  int width;
  int height;
};

struct Vector {
  int x;
  int y;
};

#endif /* util_h */
