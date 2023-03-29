/*
 * Name: Ray Oh
 * Email: rayoh101@uw.edu
 * Copyright 2023 Ray Oh
 */

#include <iostream>
#include <cstdlib>
#include <map>
#include <fstream>
#include <string>
#include <algorithm>

using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::map;
using std::pair;
using std::ifstream;
using std::string;


template <typename T> bool ReadValue(ifstream& in, T* const output);

int main(int argc, char** argv) {
  // Check input
  if (argc != 2) {
    cerr << "Please enter one .txt file as an argument" << endl;
    exit(EXIT_FAILURE);
  }

  string filename = argv[1];
  ifstream inputFile;
  inputFile.open(filename);

  string data;
  map<string, int> word_count;

  // Check if file can be opened
  if (!inputFile.is_open() || !inputFile.good()) {
    cerr << "Error opening the file" << endl;
    exit(EXIT_FAILURE);
  }

  while (!inputFile.eof()) {
    bool res = ReadValue(inputFile, &data);
    if (!res) {
      cerr << "Error reading the file" << endl;
      exit(EXIT_FAILURE);
    }

    // Increment vlaue if key already exists
    // Insert new pair if key doesn't already exist
    if (word_count.count(data)) {
      word_count[data]++;
    } else {
      word_count.insert(pair<string, int>(data, 1));
    }
  }

  // Close the file
  inputFile.close();

  // Print results
  for (auto i = word_count.begin(); i != word_count.end(); i++) {
    cout << i->first << " " << i->second << endl;
  }

  return EXIT_SUCCESS;
}

template <typename T> bool ReadValue(ifstream& in, T* const output) {
  T data;
  in >> data;

  if (in.bad()) {
    return false;
  }

  *output = data;
  return true;
}


