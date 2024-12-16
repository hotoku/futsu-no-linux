#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void die(const char* s) {
  perror(s);
  exit(1);
}

#define BUFFER_SIZE 2048

static size_t doit(const char* path) {
  int fd = open(path, O_RDONLY);
  if (fd < 0) die(path);

  unsigned char buf[BUFFER_SIZE];
  size_t cnt = 0;
  for (;;) {
    int n = read(fd, buf, sizeof buf);
    if (n < 0) die(path);
    if (n == 0) break;
    for (int i = 0; i < n; i++) {
      if (buf[i] == '\n') {
        cnt++;
      }
    }
  }
  return cnt;
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <file>\n", argv[0]);
    exit(1);
  }
  const size_t ret = doit(argv[1]);
  printf("%zu\n", ret);
}
