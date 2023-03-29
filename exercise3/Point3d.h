// Copyright 2023 Amal Jacob, Ray Oh
// Ray Oh, Amal Jacob
// rayoh101@uw.edu, amalj3@uw.edu

#ifndef POINT3D_H_
#define POINT3D_H_

#include <stdint.h>

// Represents a point with three dimensions: x, y, z
typedef struct point3d_st {
  int32_t x;
  int32_t y;
  int32_t z;
} Point3d;

// Accepts three int32_t arguments and allocates space for a 3D point,
// and returns a pointer to it. Returns NULL if unable to allocate space.
Point3d* Point3d_Allocate(int32_t x, int32_t y, int32_t z);

// Accepts a Point3d* and a int32_t value
// Scales the x, y, and z fields of the point by the given int32_t value
// Ignores if given point is NULL
void Point3d_Scale(Point3d* point, int32_t scale);

// Creates a Point3d with x, y, and z fields equal to 0
// Returns a copy of the struct
Point3d* Point3d_GetOrigin();

#endif  // POINT3D_H_
