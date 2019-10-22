#pragma once

#include <algorithm>
#include <math.h>

#include "Vector3.h"

// Axis Aligned Bounding Box
struct AABB
{
  Vector3<double> min;
  Vector3<double> max;

  AABB()
    : min(std::numeric_limits<double>::max())
    , max(-std::numeric_limits<double>::max())
  {}

  AABB(Vector3<double> min, Vector3<double> max)
    : min(min)
    , max(max)
  {}

  Vector3<double> extent() const { return max - min; }

  bool isInside(const Vector3<double>& p) const
  {
    return (p.x >= min.x && p.x <= max.x && p.y >= min.y && p.y <= max.y && p.z >= min.z &&
            p.z <= max.z);
  }

  void update(const Vector3<double>& point)
  {
    min.x = std::min(min.x, point.x);
    min.y = std::min(min.y, point.y);
    min.z = std::min(min.z, point.z);

    max.x = std::max(max.x, point.x);
    max.y = std::max(max.y, point.y);
    max.z = std::max(max.z, point.z);
  }

  void update(const AABB& aabb)
  {
    update(aabb.min);
    update(aabb.max);
  }

  void makeCubic() { max = min + extent().maxValue(); }

  Vector3<double> getCenter() const { return min + extent() / 2; }

  bool operator==(const AABB& other) const { return min == other.min && max == other.max; }

  friend std::ostream& operator<<(std::ostream& output, const AABB& value)
  {
    output << "min: " << value.min << std::endl;
    output << "max: " << value.max << std::endl;
    output << "size: " << value.extent() << std::endl;
    return output;
  }
};