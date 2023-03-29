/*
 * Name: Ray Oh
 * Email: rayoh101@uw.edu
 * Copyright 2023 Ray Oh
 */

#include <iostream>
#include <cstdlib>
#include "Vector.h"

using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using vector333::Vector;

int main() {
  Vector vectorA;
  cout << "Testing Default Constructor\n Expected: (0,0,0)\n Actual: "
    << vectorA << endl;

  Vector vectorB(1, 2, 3);
  cout << "Testing 3-arg Constructor\n Expected: (1,2,3)\n Actual: "
    << vectorB << endl;

  Vector vectorC(vectorB);
  cout << "Testing Copy Constructor\n Expected: (1,2,3)\n Actual: "
    << vectorC << endl;

  Vector vectorD(5, 3, 8);
  vectorB += vectorD;
  cout << "Testing += Operator\n Expcted: (6,5,11)\n Actual: "
    << vectorB << endl;

  vectorB -= vectorD;
  cout << "Testing -= Operator\n Expcted: (1,2,3)\n Actual: "
    << vectorB << endl;

  Vector vectorE = vectorB + vectorD;
  cout << "Testing + Operator\n Expcted: (6,5,11)\n Actual: "
    << vectorE << endl;

  Vector vectorF = vectorB - vectorC;
  cout << "Testing - Operator\n Expcted: (0,0,0)\n Actual: "
    << vectorF << endl;

  float dot = vectorB * vectorD;
  if (!dot) {
    cerr << "Failed to return dot product" << endl;
    return EXIT_FAILURE;
  }
  cout << "Testing Dot Product\n Expected: 35\n Actual: "
    << dot << endl;

  Vector vectorG = vectorB * 4;
  cout << "Testing Scalar Product \n Expected: (4,8,12)\n Actual: "
    << vectorG << endl;

  Vector vectorH = 4 * vectorB;
  cout << "Testing Scalar Product \n Expected: (4,8,12)\n Actual: "
    << vectorH << endl;

  return EXIT_SUCCESS;
}

