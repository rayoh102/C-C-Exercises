/*
 * Name: Ray Oh
 * Email: rayoh101@uw.edu
 * Copyright 2023 Ray Oh
 */

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>

#include "SocketUtil.h"

using std::cerr;
using std::endl;
using std::cout;

#define BUFSIZE 1024

// Prints usage information about this program and exits with EXIT_FAILURE.
void Usage(char* progname);

// Create a listening socket, accept a connection from a client,
// and write all the data the client sends to stdout.
int main(int argc, char** argv) {
  if (argc != 2) {
    Usage(argv[0]);
  }

  // Create listening socket
  int sock_family, listen_fd;
  listen_fd = Listen(argv[1], &sock_family);
  if (listen_fd == -1) {
    cerr << "Failed to created listening socket on port " << argv[1] << endl;
  }

  // Waiting for client
  int client_fd;
  while (1) {
    struct sockaddr_storage caddr;
    socklen_t caddr_len = sizeof(caddr);
    client_fd = accept(listen_fd, reinterpret_cast<struct sockaddr*>(&caddr),
      &caddr_len);

    if (client_fd < 0) {
      if ((errno == EAGAIN) || (errno == EINTR))
        continue;
      cerr << "Failure on accept: " << strerror(errno) << endl;
      close(listen_fd);
      Usage(argv[0]);
    }
    break;
  }

  // Read data from client and write to output
  while (1) {
    unsigned char buf[BUFSIZE];
    int res = WrappedRead(client_fd, buf, BUFSIZE);
    if (res == 0)
      break;
    if (res < 0) {
      close(client_fd);
      close(listen_fd);
      return EXIT_FAILURE;
    }

    std::string out(reinterpret_cast<char*>(buf), res);
    cout << out;
  }

  // Clean up
  close(client_fd);
  close(listen_fd);
  return EXIT_SUCCESS;
}

void Usage(char* progname) {
  cerr << "usage: " << progname << " port" << endl;
  exit(EXIT_FAILURE);
}
