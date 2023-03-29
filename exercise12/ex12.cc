/*
 * Copyright ©2023 Justin Hsia.  All rights reserved.  Permission is
 * hereby granted to students registered for University of Washington
 * CSE 333 for use solely during Winter Quarter 2023 for purposes of
 * the course.  No other use, copying, distribution, or modification
 * is permitted without prior written consent. Copyrights for
 * third-party components of this work must be honored.  Instructors
 * interested in reusing these course materials should contact the
 * author.
 */

#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <string>
#include <ctime>

#include "SimpleQueue.h"

using std::cout;
using std::endl;
using std::string;
using std::thread;
using std::cerr;

static constexpr int kNumSnacks = 6;
static SimpleQueue queue;
static unsigned int seed = time(nullptr);
static pthread_mutex_t write_lock;


// Thread safe print that prints the given str on a line
void thread_safe_print(const string& str);

// Produces kNumSnacks snacks of the given type
void producer(const string& snack_type);

// Eats 2 * kNumSnacks snacks
void consumer();

// Wrapper for producer method
void* producer_wrapper(void* arg_ptr);

// Wrapper for consumer method
void* consumer_wrapper(void* arg_ptr);

int main(int argc, char** argv) {
  pthread_mutex_init(&write_lock, nullptr);
  // Your task: Make the two producers and the single consumer
  // all run concurrently (hint: use pthreads)

  pthread_t thd_array[3];
  string snack1 = "piroshki";
  string snack2 = "nalysnyky";

  if (pthread_create(&thd_array[0], nullptr, producer_wrapper, &snack1) != 0) {
    cerr << "pthread_create failed for first producer" << endl;
  }

  if (pthread_create(&thd_array[1], nullptr, producer_wrapper, &snack2) != 0) {
    cerr << "pthread_create failed for second producer" << endl;
  }

  if (pthread_create(&thd_array[2], nullptr, consumer_wrapper, nullptr) != 0) {
    cerr << "pthread_create failed for consumer" << endl;
  }

  for (unsigned int i = 0; i < 3; i++) {
    void *res;
    if (pthread_join(thd_array[i], &res) != 0) {
      std::cerr << "pthread_join() failed." << std::endl;
    }
  }

  pthread_mutex_destroy(&write_lock);
  return EXIT_SUCCESS;
}

void thread_safe_print(const string& str) {
  cout << str << endl;
  pthread_mutex_unlock(&write_lock);
}

void producer(const string& snack_type) {
  for (int i = 0; i < kNumSnacks; i++) {
    queue.Enqueue(snack_type);
    thread_safe_print(snack_type + " ready!");
    int sleep_time = rand_r(&seed) % 500 + 1;
    std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
  }
}

void consumer() {
  for (int i = 0; i < kNumSnacks * 2; i++) {
    bool successful = false;
    string snack_type;
    while (!successful) {
      while (queue.IsEmpty()) {
        int sleep_time = rand_r(&seed) % 800 + 1;
        std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
      }
      successful = queue.Dequeue(&snack_type);
    }
    thread_safe_print(snack_type + " eaten!");
  }
}

void* producer_wrapper(void* arg_ptr) {
  string* snack = reinterpret_cast<string*>(arg_ptr);
  producer(*snack);
  pthread_exit(nullptr);
  return nullptr;
}

void* consumer_wrapper(void* arg_ptr) {
  consumer();
  pthread_exit(nullptr);
  return nullptr;
}
