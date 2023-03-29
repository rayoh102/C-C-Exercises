/*
 * Name: Ray Oh
 * Email: rayoh101@uw.ed
 * Copyright 2022 Ray Oh
 */


#include <iostream>
#include <string>
#include "Vector.h"

static const float x1 = 3;
static const float y1 = 2;
static const float z1 = 4;

static const float x2 = 3.5;
static const float y2 = 0;
static const float z2 = -2;

using std::cout;
using std::cerr;
using std::endl;
using std::string;

// Function that tests if the vector correctly contains the given values
static void TestVector(const Vector& v, const float x, const float y,
  const float z, const string& msg);

// Function that accepts a vector and increments its values by 1
static void Increment(Vector v);

// Function that accepts a Vector reference and a void* as arguments
// Returns true if the address of v matches the address inside ptr
static bool VerifyAddress(const Vector& v, void* ptr);

int main() {
  // testing default constructor
  Vector vectorA;
  TestVector(vectorA, 0, 0, 0, "Testing Default Constructor: ");

  // testing constructor with 3 arguments
  Vector vectorB(x1, y1, z1);
  TestVector(vectorB, x1, y1, z1, "Testing Constructor: ");

  // testing copy constructor
  Vector vectorC(vectorB);
  TestVector(vectorC, x1, y1, z1, "Testing Copy Consructor: ");

  // testing assignment on vectors
  Vector vectorD(x2, y2, z2);
  vectorC = vectorD;
  TestVector(vectorC, x2, y2, z2, "Testing = Operator: ");

  // testing updating assignment on vectors that perform addition of
  // vector components
  vectorC += vectorB;
  TestVector(vectorC, x1+x2, y1+y2, z1+z2, "Testing += Operator: ");

  // testing updating assignment on vectors that perform subtraction
  // of vector components
  vectorC -= vectorB;
  TestVector(vectorC, x2, y2, z2, "Testing -= Operator: ");

  // testing dot product
  float dot_product = vectorB * vectorC;
  cout << "Testing Dot Product: " << endl;
  if (dot_product != x1 * x2 + y1 * y2 + z1 * z2) {
    cerr << "Failed" << endl;
    return EXIT_FAILURE;
  } else {
    cout << "Passed" << endl;
  }

  // Testing pass-by-value or pass-by-reference
  Vector vectorE;
  Increment(vectorE);
  if (vectorE.get_x() == 1 && vectorE.get_y() == 1 && vectorE.get_z() == 1) {
    cout << "Vector: pass-by-reference" << endl;
  } else {
    cout << "Vector: pass-by-value" << endl;
  }

  // Testing if two addresses have the same numeric value passed in
  if (VerifyAddress(vectorE, &vectorE)) {
    cout << "Ref: same Address" << endl;
  } else {
    cout << "Ref: different Address" << endl;
  }

  return EXIT_SUCCESS;
}

// Helper function definitions
static void TestVector(const Vector& v, const float x, const float y,
  const float z, const string& msg) {
  if (v.get_x() != x || v.get_y() != y || v.get_z() != z) {
    cerr << msg << "Failed" << endl;
    exit(EXIT_FAILURE);
  } else {
    cout << msg << "Passed" << endl;
  }
}

void Increment(Vector v) {
  Vector unitVector(1, 1, 1);
  v += unitVector;
}

bool VerifyAddress(const Vector& v, void* ptr) {
  return &v == reinterpret_cast<Vector *>(ptr);
}
