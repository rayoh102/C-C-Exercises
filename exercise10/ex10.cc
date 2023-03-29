/*
 * Name: Ray Oh
 * Email: rayoh101@uw.edu
 * Copyright 2023 Ray Oh
i*/

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include "SocketUtil.h"

using std::cerr;
using std::endl;

#define BUF 256

// Prints usage information about this program and exits with EXIT_FAILURE.
void Usage(char* progname);

// Open a local file, open a socket to a remote process,
// and send the file to other process.
int main(int argc, char** argv) {
  if (argc != 4) {
    Usage(argv[0]);
  }

  int file_fd = open(argv[3], O_RDONLY);
  if (file_fd  == -1) {
    Usage(argv[0]);
  }

  unsigned short port = 0;
  if (sscanf(argv[2], "%hu", &port) != 1) {
    close(file_fd);
    Usage(argv[0]);
  }

  // Get an appropriate sockaddr structure
  struct sockaddr_storage addr;
  size_t addrlen;
  if (!LookupName(argv[1], port, &addr, &addrlen)) {
    close(file_fd);
    Usage(argv[0]);
  }

  // Connect to the remote host
  int socket_fd;
  if (!Connect(addr, addrlen, &socket_fd)) {
    close(file_fd);
    Usage(argv[0]);
  }

  // Read and write from remote host
  unsigned char readbuf[BUF];
  int res;
  int wres;
  while (1) {
    res = WrappedRead(file_fd, readbuf, BUF);
    if (res == 0) {
      break;
    }
    if (res == -1) {  // error
      std::cerr << "socket read failure: " << strerror(errno) << std::endl;
      close(socket_fd);
      close(file_fd);
      return EXIT_FAILURE;
    }

    wres = WrappedWrite(socket_fd, readbuf, res);
    if (wres != res) {
      close(socket_fd);
      close(file_fd);
      return EXIT_FAILURE;
    }
  }

  // clean up
  close(socket_fd);
  close(file_fd);
  return EXIT_SUCCESS;
}

void Usage(char* progname) {
  std::cerr << "usage: " << progname << " hostname port" << std::endl;
  exit(EXIT_FAILURE);
}
