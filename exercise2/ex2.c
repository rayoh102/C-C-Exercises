/* 
 * Copyright ©2023 Amal Jacob
 * Name: Amal Jacob, Ray Oh
 * Email: amalj3@uw.edu, rayoh101@uw.edu
 */

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

// Prints bytes of array pData, given its length in bytes byteLen
void DumpBytes(void* pData, int32_t byteLen);
// Prints bytes of first array and copies contents of first
// array into second in nondescending order, given their equal
// length len of first and second array
void CopyAndSort(uint8_t* first, uint8_t* second, int32_t len);
// Copies all elements of first array into second given their equal
// length len
void Copy(uint8_t* first, uint8_t* second, int32_t len);
// Sorts the values of array arr in non-descending order given its
// length len
void Sort(uint8_t* arr, int32_t len);

int main(int argc, char* argv[]) {
  int32_t int_val = 1;
  float   float_val = 1.0f;
  uint8_t arr_unsorted[] = {3, 2, 0, 8, 17, 6, 10, 7, 8, 1, 12};
  uint8_t arr_sorted[]   = {0, 0, 0, 0,  0, 0,  0, 0, 0, 0,  0};

  DumpBytes(&int_val, sizeof(int_val));
  DumpBytes(&float_val, sizeof(float_val));
  DumpBytes(arr_unsorted, sizeof(arr_unsorted) / sizeof(arr_unsorted[0]));
  CopyAndSort(arr_unsorted, arr_sorted,
              sizeof(arr_unsorted) / sizeof(arr_unsorted[0]));
  DumpBytes(arr_sorted, sizeof(arr_sorted) / sizeof(arr_sorted[0]));

  return EXIT_SUCCESS;
}

void DumpBytes(void* pData, int32_t byteLen) {
  printf("The %d bytes starting at %p are:", byteLen, pData);

  // Starting from first byte, iterate and print each byte
  uint8_t* byte = (unsigned char*) pData;
  for (int i = 0; i < byteLen; i++) {
    printf(" %02" PRIx8, *(byte + i));
  }

  printf("\n");
}

void CopyAndSort(uint8_t* first, uint8_t* second, int32_t len) {
  DumpBytes(first, len);
  Sort(first, len);
  Copy(first, second, len);
}

void Copy(uint8_t* first, uint8_t* second, int32_t len) {
  for (int i = 0; i < len; i++) {
    second[i] = first[i];
  }
}

void Sort(uint8_t* arr, int32_t len) {
  // Perform insertion sort on arr
  uint8_t curr = 0;
  for (int i = 0; i < len; i++) {
    curr = arr[i];

    // Swaps until element at i reaches its sorted order
    int j = i;
    while (j >= 1 && arr[j - 1] > curr) {
      arr[j] = arr[j - 1];
      j--;
    }

    arr[j] = curr;
  }
}
