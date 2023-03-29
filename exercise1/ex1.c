// Copyright 2023 Amal Jacob
// Performs Nilakantha's algorithm to estimate pi, given a number n terms to use
// Name: Amal Jacob
// Email: amalj3@cs.washington.edu

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// On invalid input, prints error message and exits with failure
void HandleInvalidInput(void);
// Performs the Nilakantha calculations, given an input n for
// number of terms in series to use
double PerformNilakantha(int n);

int main(int argc, char* argv[]) {
  // If less or more than 1 user input, user's input format
  // is invalid.
  if (argc != 2) {
    HandleInvalidInput();
  }

  // Check that each char in input is valid digit, so overall
  // input is a valid positive integer
  char* input = argv[1];
  while (*input != '\0') {
    if (!isdigit(*input)) {
      HandleInvalidInput();
    }
    input++;
  }

  // Calculate and print Nilakantha's approximation for pi and
  // exit with success
  int n = atoi(argv[1]);
  printf("Pi approx:  %.20lf\n", PerformNilakantha(n));
  return EXIT_SUCCESS;
}

double PerformNilakantha(int n) {
  int curr = 0;
  double ans = 3.0;
  double term_number;
  double term;

  // Nilakantha algorithm
  while (curr < n) {
    term_number = curr + 1;
    term = 4 / ((2 * term_number) * (2 * term_number + 1)
           * (2 * term_number + 2));
    if (curr % 2 == 0) {
      ans += term;
    } else {
      ans -= term;
    }

    curr++;
  }

  return ans;
}

void HandleInvalidInput(void) {
  printf("Invalid input. Please input exactly one integer.\n");
  exit(EXIT_FAILURE);
}
