/* 
 * Copyright ©2023 Amal Jacob
 * Name: Amal Jacob
 * Email: amalj3@uw.edu
 */

#include "ro_file.h"

#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

/*** INTERNAL DATA TYPES AND CONSTANTS **************************************/

static const int RO_FILE_BUF_LEN = 512;  // do not modify

struct ro_file_st {
  int fd;         // The file descriptor we are currently managing.

  char* buf;      // Pointer to our internal buffer for this file.

  off_t buf_pos;  // The position in the file that the beginning of our
                  // internal buffer currently corresponds to.

  int buf_index;  // The index in our internal buffer that corresponds to the
                  // user's current position in the file.

  int buf_end;    // How many bytes currently in our internal buffer are
                  // actually from the file.
                  // To understand why this is important to track, consider
                  // the case when the file length is < RO_FILE_BUF_LEN.
};

/*** STATIC HELPER FUNCTION DECLARATIONS ************************************/

// Copy up to 'amount' bytes from the RO_FILE's internal buffer to 'out'.
// Returns the number of bytes copied.
static size_t flush_buffer(RO_FILE* file, char* out, int amount);

// Fill in the RO_FILE's internal buffer with as many bytes as can be read
// from the file.
// Returns the number of bytes copied into the buffer, or -1 on any error.
static ssize_t fill_buffer(RO_FILE* file);


/*** FUNCTION DEFINITIONS ***************************************************/

RO_FILE* ro_open(char* filename) {
  // 1. Allocate a new RO_FILE
  RO_FILE* rofile = (RO_FILE*) malloc(sizeof(RO_FILE));
  if (rofile == NULL) {
    return NULL;
  }
  // 2. Get the file descriptor for the file
  rofile->fd = open(filename, O_RDONLY);
  if (rofile->fd == -1) {
    free(rofile);
    return NULL;
  }
  // 3. Allocate the internal buffer
  rofile->buf = (char*) malloc(sizeof(char) * (RO_FILE_BUF_LEN));
  // 4. Initialize the other fields (no reading done yet)
  rofile->buf_pos = 0;
  rofile->buf_index = 0;
  rofile->buf_end = 0;

  return rofile;
}

ssize_t ro_read(char* ptr, size_t len, RO_FILE* file) {
  // 1. If we have bytes in our internal buffer, flush as many as we can to
  //    'ptr'.
  size_t num_copied_out = flush_buffer(file, ptr, len);
  int loops_started = 0;

  while (num_copied_out != len) {
    // 2. If we haven't provided the bytes requested, repopulate our buffer
    //    with bytes from the file.
    loops_started++;
    ssize_t num_filled = fill_buffer(file);
    if (num_filled == 0) {
      // reached EOF; no more bytes to copy
      break;
    } else if (num_filled < 0) {
      // pass error back to client
      return num_filled;
    }

    // 3. Copy filled bytes into 'ptr'.
    num_copied_out += flush_buffer(file, ptr+num_copied_out,
                                   len-num_copied_out);
    // 4. Repeat steps 2-3 until request is fulfilled.
  }

  return num_copied_out;
}

off_t ro_tell(RO_FILE* file) {
  if (file == NULL) {
    return -1;
  }
  return file->buf_pos + file->buf_index;
}

int ro_seek(RO_FILE* file, off_t offset, int whence) {
  // 1. Check validity of arguments, where applicable.
  if (file == NULL) {
    fprintf(stderr, "ro_seek given null file");
    return -1;
  }

  if (whence != SEEK_SET && whence != SEEK_CUR && whence != SEEK_END) {
    fprintf(stderr, "ro_seek givn invalid whence");
    return -1;
  }

  // 2. Seek to specified offset from specified whence using lseek.
  //    No need to check if new position is already in our buffer.
  off_t new_pos = lseek(file->fd, offset, whence);
  if (new_pos == -1) {
    perror("failed lseek\n");
    return -1;
  }

  // 3. Update our buffer indicators

  file->buf_pos = new_pos;
  file->buf_index = 0;
  file->buf_end = 0;

  return 0;
}

int ro_close(RO_FILE* file) {
  // Clean up all RO_FILE resources, returns non-zero on error
  if (file == NULL) {
    fprintf(stderr, "file is null\n");
    return -1;
  }

  if (close(file->fd) == -1) {
    fprintf(stderr, "close file failed\n");
    return -1;
  }

  free(file->buf);
  free(file);
  return 0;
}


/*** STATIC HELPER FUNCTION DEFINITIONS *************************************/

size_t flush_buffer(RO_FILE* file, char* out, int amount) {
  // 1. Copy/flush bytes to 'out' starting from the buffer index. The amount
  //    flushed should be the min of 'amount' and the remaining unflushed bytes
  //    in the buffer.
  int flushed;

  int remaining = file->buf_end - file->buf_index;
  if (amount < remaining) {
    flushed = amount;
  } else {
    flushed = remaining;
  }

  for (int i = 0; i < flushed; i++) {
    out[i] = file->buf[file->buf_index + i];
  }

  // 2. Advance buffer index by the number of bytes flushed.
  file->buf_index += flushed;
  // 3. Return the number of bytes flushed.
  return flushed;
}

ssize_t fill_buffer(RO_FILE* file) {
  // NOTES:
  // - For maximum buffering benefit, we are "resetting" the buffer and then
  //   filling it with as much file data as possible, starting from the current
  //   file position -- how does this change the buffer indicators?
  // - For simplicity, you should ignore any unflushed bytes that started in
  //   the buffer (i.e., it's okay to re-read them from the file).
  // - You will need to implement a POSIX read loop with all appropriate
  //   return value checking.
  int bytes_left = RO_FILE_BUF_LEN;
  int result;

  while (bytes_left > 0) {
    result = read(file->fd, file->buf + (RO_FILE_BUF_LEN - bytes_left),
                  bytes_left);
    if (result == -1) {
      if (errno != EINTR) {
        // a real error happened, so return an error result
        return -1;
      }
      // EINTR happened, so do nothing and try again
      continue;
    } else if (result == 0) {
      // EOF reached, so stop reading
      break;
    }
    bytes_left -= result;
  }

  int filled_bytes = RO_FILE_BUF_LEN - bytes_left;

  // Only change buf_pos after buffer has already been filled
  // at least once before this
  if (file->buf_end > 0) {
    file->buf_pos += filled_bytes;
  }
  file->buf_end = filled_bytes;
  file->buf_index = 0;
  return file->buf_end;
}
