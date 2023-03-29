#include "Vector.h"
#include <iostream>

using std::ostream;

Vector& Vector::operator=(const Vector& rhs) {
  if (this != &rhs) {
    x_ = rhs.x_;
    y_ = rhs.y_;
    z_ = rhs.z_;
  }

  return *this;
}

Vector& Vector::operator+=(const Vector& rhs) {
  x_ += rhs.x_;
  y_ += rhs.y_;
  z_ += rhs.z_;

  return *this;
}

Vector& Vector::operator-=(const Vector& rhs) {
  x_ -= rhs.x_;
  y_ -= rhs.y_;
  z_ -= rhs.z_;

  return *this;
}

float Vector::operator*(const Vector& rhs) const {
  return x_ * rhs.x_ + y_ * rhs.y_ + z_ * rhs.z_;
}

