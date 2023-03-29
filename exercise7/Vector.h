/*
 * Name: Ray Oh
 * Email: rayoh101@uw.edu
 * Copyright 2023 Ray Oh
 */

#ifndef VECTOR_H_
#define VECTOR_H_

#include <iostream>

// namespace vector333
namespace vector333 {

class Vector {
 public:
    // Default Constructor that initialzes a vector to (0,0,0)
    Vector();

    // Construct which creates a vector given 3 floats x, y, and z
    Vector(const float x, const float y, const float z);

    // Copy constructor which copies values of Vector "v" into new Vector
    Vector(const Vector& v);

    // Destructor
    ~Vector() { }

    // Assignment operator on vectors
    Vector& operator=(const Vector& v);

    // Updating assignment on vectors that perform addition
    Vector& operator+=(const Vector& v);

    // Addition Operator that returns sum as a new Vector
    Vector operator+(const Vector& v) const;

    // Updating assignment on vectors that perform  subtraction
    Vector& operator-=(const Vector& v);

    // Subtraction Operator that returns difference as a new Vector
    Vector operator-(const Vector& v) const;

    // * operator that computes the dot product of two vectors
    friend float operator*(const Vector& v1, const Vector& v2);

    // * operator that returns a Vector with components of v multiplied by k
    friend Vector operator*(const Vector& v, const float k);

    // * operator that returns a Vector with components of v multiplied by k
    friend Vector operator*(const float k, const Vector& v);

    friend std::ostream& operator<<(std::ostream& s, const Vector& v);

 private:
    float x_, y_, z_;
};

}  // namespace vector333

#endif  // VECTOR_H_
