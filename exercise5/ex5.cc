/*
 * Name: Ray Oh
 * Email: rayoh101@uw.ed
 * Copyright 2022 Ray Oh
 */

#include <iostream>
#include <cstdlib>

using std::cerr;
using std::endl;
using std::cout;
using std::cin;

// Given an int num, print all of its factors
void factor(int num);

int main(int argc, char** argv) {
  int num;

  cout << "Which positive integer would you like me to factorize? ";
  cin >> num;

  if (num <= 0) {
    cerr << "Please input a valid positive integer\n";
    return EXIT_FAILURE;
  }

  factor(num);
  return EXIT_SUCCESS;
}

void factor(int num) {
  for (int i = 1; i < num; i++) {
    if (num % i == 0) {
      cout << i << " ";
    }
  }
  cout << num << endl;
}
