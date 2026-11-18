
#include <stdio.h>
#include <string.h>

int main() {
  unsigned char src[] = {0x10, 0x00, 0x20, 0x30, 0x40};
  unsigned char des[5];

  // 2. memcpy()
  memset(des, 0, sizeof(des));
  memcpy(des, src, sizeof(src));

  printf("After memcpy: ");
  for (int i = 0; i < 5; i++) {
    printf("%02X ", des[i]);
  }
  printf("\n");

  // 3. strcpy()
  memset(des, 0, sizeof(des));
  strcpy((char *)des, (char *)src);

  printf("After strcpy: ");
  for (int i = 0; i < 5; i++) {
    printf("%02X ", des[i]);
  }
  printf("\n");

  return 0;
}
