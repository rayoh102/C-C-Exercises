// Copyright 2023 Amal Jacob, Ray Oh
// Ray Oh, Amal Jacob
// rayoh101@uw.edu, amalj3@uw.edu

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "Point3d.h"

// Define x, y, and z values of point to begin tests with
#define X -1
#define Y 0
#define Z 2

// Define scale factor to test
#define SCALE_FACTOR -2

int main(int argc, char* argv[]) {
  // Test Point3d_Allocate
  Point3d* point = Point3d_Allocate(X, Y, Z);
  if (point == NULL) {
    printf("Allocation failure in Point3d_Allocate\n");
    return EXIT_FAILURE;
  }

  if (point->x != X || point->y != Y || point->z != Z) {
    printf("Incorrect value(s) set for point\n");
    return EXIT_FAILURE;
  }

  // Test Point3d_Scale
  Point3d_Scale(point, SCALE_FACTOR);
  if (point->x != X * SCALE_FACTOR || point->y != Y * SCALE_FACTOR
      || point->z != Z * SCALE_FACTOR) {
    printf("Incorrect point value(s) after scaling\n");
    return EXIT_FAILURE;
  }

  // Test Point3d_GetOrigin
  free(point);
  point = Point3d_GetOrigin();
  if (point->x != 0 || point->y != 0 || point->z != 0) {
    printf("Incorrect value(s) set for origin point\n");
    return EXIT_FAILURE;
  }

  // Passed all tests, free remaining resources and exit
  printf("Passed all tests!\n");
  free(point);
  return EXIT_SUCCESS;
}
