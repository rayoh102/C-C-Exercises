/*
 * Name: Ray Oh
 * Email: rayoh101@uw.edu
 * Copyright 2023 Ray Oh
 */

#include <iostream>
#include "Vector.h"

namespace vector333 {

  Vector::Vector() {
    x_ = 0.0;
    y_ = 0.0;
    z_ = 0.0;
  }

  Vector::Vector(const float x, const float y, const float z) {
    x_ = x;
    y_ = y;
    z_ = z;
  }

  Vector::Vector(const Vector& v) {
    x_ = v.x_;
    y_ = v.y_;
    z_ = v.z_;
  }

  Vector& Vector::operator=(const Vector& v) {
    if (this != &v) {
      x_ = v.x_;
      y_ = v.y_;
      z_ = v.z_;
    }
    return *this;
  }

  Vector& Vector::operator+=(const Vector& v) {
    x_ += v.x_;
    y_ += v.y_;
    z_ += v.z_;
    return *this;
  }

  Vector& Vector::operator-=(const Vector& v) {
    x_ -= v.x_;
    y_ -= v.y_;
    z_ -= v.z_;
    return *this;
  }

  Vector Vector::operator+(const Vector& v) const {
    Vector res(x_ + v.x_, y_ + v.y_, z_ + v.z_);
    return res;
  }

  Vector Vector::operator-(const Vector& v) const {
    Vector res(x_ - v.x_, y_ - v.y_, z_ - v.z_);
    return res;
  }

  float operator*(const Vector& v1, const Vector& v2) {
    return v1.x_ * v2.x_ + v1.y_ * v2.y_ + v1.z_ * v2.z_;
  }

  Vector operator*(const Vector& v, const float k) {
    Vector res(v.x_ * k, v.y_ * k, v.z_ * k);
    return res;
  }

  Vector operator*(const float k, const Vector& v) {
    Vector res(v.x_ * k, v.y_ * k, v.z_ * k);
    return res;
  }

  std::ostream& operator<<(std::ostream& s, const Vector& v) {
    s << "(" << v.x_ << "," << v.y_ << "," << v.z_ << ")";
    return s;
  }

}  // namespace vector333
