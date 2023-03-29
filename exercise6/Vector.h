#ifndef VECTOR_H_
#define VECTOR_H_
#include <iostream>

class Vector {
  public:
    // Default Constructor that initialzes a vector to (0,0,0)
    Vector() : x_(0.0), y_(0.0), z_(0.0) { }

    // Construct which creates a vector given 3 floats x, y, and z
    Vector(const float x, const float y, const float z) : x_(x), y_(y), z_(z) { }

    // Copy constructor which copies values of Vector "v" into new Vector 
    Vector(const Vector& v) : x_(v.x_), y_(v.y_), z_(v.z_) { }

    // Destructor
    ~Vector() { }

    // Assignment operator on vectors
    Vector& operator=(const Vector& rhs);

    // Getter get_x
    float get_x() const { return x_; }
    // Getter get_y
    float get_y() const { return y_; }
    // Getter get_z
    float get_z() const { return z_; }

    // Updating assignment on vectors that perform element-by-element addition
    Vector& operator+=(const Vector& rhs);
    
    // Updating assignment on vectors that perform element-by-element subtraction
    Vector& operator-=(const Vector& rhs);
    
    // Operator that computes the tot product of two Vectors
    float operator*(const Vector& rhs) const;
  
  private:
    // Vector is represented as three floating point numbers which each represent the x, y, and z values 
    float x_, y_, z_;    
};

#endif
