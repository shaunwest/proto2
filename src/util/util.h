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
#include <vector>

#include "json/json.h"

// Equivalent to "new". Built-in part of C++14 (http://en.cppreference.com/w/cpp/memory/unique_ptr/make_unique)
template<typename T, typename ...Args>
std::unique_ptr<T> make_unique(Args&& ...args) {
  return std::unique_ptr<T>( new T( std::forward<Args>(args)... ) );
}

std::string time_now();
Json::Value get_json(std::string asset_path);

struct Size {
  int width;
  int height;
};

/*
struct Vector {
  int x;
  int y;
};
*/

// VECTOR2
template <typename T>
struct Vector2 {
  T x = 0;
  T y = 0;

  Vector2() {}

  Vector2(T x, T y) : x(x), y(y) {}

  // TODO Should these operators move out of the struct def?
  Vector2<T> operator +(const Vector2<T> &rhs) {
    return Vector2<T>(x + rhs.x, y + rhs.y);
  }

  Vector2<T> operator -(const Vector2<T> &rhs) {
    return Vector2<T>(x - rhs.x, y - rhs.y);
  }

  // should this be a standalone function?
  std::string print() {
    return to_string(x) + ", " + to_string(y);
  }

  // should this be a standalone function?
  bool is_zero() {
    return (x == 0 && y == 0);
  }
};

template <typename T>
Vector2<T> operator* (T lhs, const Vector2<T> &rhs) {
  return Vector2<T>(lhs * rhs.x, lhs * rhs.y);
}

template <typename T>
Vector2<T> operator* (const Vector2<T> &lhs, T rhs) {
  return Vector2<T>(lhs * rhs.x, lhs * rhs.y);
}

typedef Vector2<int> IntVector2;
typedef Vector2<float> FloatVector2;

typedef std::vector<IntVector2> IntVectorList;
typedef std::vector<FloatVector2> FloatVectorList;

// RECT
template <typename T>
struct Rect {
  T x = 0;
  T y = 0;
  T width = 0;
  T height = 0;
  T top = 0;
  T left = 0;
  T right = 0;
  T bottom = 0;

  Rect() {}

  Rect(T x, T y, T width, T height)
    : x(x), y(y), width(width), height(height), top(y),
      left(x), right(x + width), bottom(y + height) {}
};

typedef Rect<int> IntRect;
typedef Rect<float> FloatRect;

typedef std::vector<IntRect> IntRectList;
typedef std::vector<FloatRect> FloatRectList;

#endif /* util_h */
