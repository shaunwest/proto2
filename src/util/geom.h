//
//  geom.h
//  Proto2
//
//  Created by Shaun West on 8/12/17.
//

#ifndef geom_h
#define geom_h

#include <iostream>
#include <vector>

struct Size {
  int width;
  int height;
};

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
  std::string print() const {
    return std::to_string(x) + ", " + std::to_string(y);
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

typedef Vector2<int> Vector2i;
typedef Vector2<float> Vector2f;

typedef std::vector<Vector2i> IntVectorList;
typedef std::vector<Vector2i> VectorListi;
typedef std::vector<Vector2f> FloatVectorList;
typedef std::vector<Vector2f> VectorListf;


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

  std::string print() const {
    return std::to_string(x) + ", " + std::to_string(y) + "; " +
      std::to_string(width) + ", " + std::to_string(height);
  }
};

typedef Rect<int> Recti;
typedef Rect<float> Rectf;

typedef std::vector<Recti> RectListi;
typedef std::vector<Rectf> RectListf;


// LINES
template <typename T>
struct LineSegment {
  T p1;
  T p2;
  T dist;
  float length = 0.0;
  float angle = 0.0;
  //int id;

  bool operator==(const LineSegment& rhs) {
    return (p1.x == rhs.p1.x && p1.y == rhs.p1.y && p2.x == rhs.p2.x && p2.y == rhs.p2.y);
  }
};

typedef LineSegment<Vector2i> LineSegmenti;
typedef LineSegment<Vector2f> LineSegmentf;


// FUNCTIONS
bool intersects(Recti rect1, Recti rect2);

#endif
