#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void do_cat(const char* path);
static void die(const char* s);

int main(int argc, char** argv) {
  if (argc < 2) {
    /* 標準エラーへの吐き方 */
    fprintf(stderr, "Usage: %s <file>\n", argv[0]);
    exit(1);
  }
  for (int i = 1; i < argc; i++) {
    do_cat(argv[i]);
  }
  exit(0);
}

#define BUFFER_SIZE 2048

static void do_cat(const char* path) {
  int fd = open(path, O_RDONLY);
  unsigned char buf[BUFFER_SIZE];
  if (fd < 0) die(path);

  for (;;) {
    int n = read(fd, buf, sizeof buf);
    if (n < 0) die(path);
    if (n == 0) break;
    if (write(STDOUT_FILENO, buf, n) < 0) die(path);
  }

  if (close(fd) < 0) die(path);
}

static void die(const char* s) {
  /* 便利なperror関数 */
  perror(s);
  exit(1);
}