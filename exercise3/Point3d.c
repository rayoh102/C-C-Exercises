// Copyright 2023 Amal Jacob, Ray Oh
// Ray Oh, Amal Jacobs
// rayoh101@uw.edu, amalj3@uw.edu

#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include "Point3d.h"

Point3d* Point3d_Allocate(int32_t x, int32_t y, int32_t z) {
  Point3d* point = (Point3d*) malloc(sizeof(Point3d));
  if (point == NULL) {
    // Malloc failed
    return NULL;
  }

  // Assign given values to point
  point->x = x;
  point->y = y;
  point->z = z;

  return point;
}

void Point3d_Scale(Point3d* point, int32_t scale) {
  if (point != NULL) {
    point->x *= scale;
    point->y *= scale;
    point->z *= scale;
  }
}

Point3d* Point3d_GetOrigin() {
  return Point3d_Allocate(0, 0, 0);
}

