#pragma once

#include "vec3.h"
#include <cmath>

class ray {
public:
  ray() {}
  ray(const point3 &origin, const vec3 &direction)
      : orig(origin), dir(direction) {}

  point3 origin() const { return orig; }
  vec3 direction() const { return dir; }

  point3 at(double t) const { return orig + dir * t; }

  static double hit_sphere(const point3 &center, double radius, const ray &r);

private:
  point3 orig;
  vec3 dir;

  static inline color beginColor = color(1, 1, 1);
  static inline color endColor = color(1, 1, 0.3);
};

inline double ray::hit_sphere(const point3 &center, double radius,
                              const ray &r) {
  vec3 oc = r.origin() - center;
  auto a = dot(r.direction(), r.direction());
  auto b = 2.0 * dot(oc, r.direction());
  auto c = dot(oc, oc) - radius * radius;
  auto discriminant = b * b - 4 * a * c;
  if (discriminant < 0) {
    return -1.0f;
  }
  return (-b - sqrt(discriminant)) / (2.0 * a);
}