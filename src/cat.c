#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void do_cat(const int fd, const char* path);
static void die(const char* s);

int main(int argc, char** argv) {
  int fd;
  if (argc < 2) {
    fd = STDIN_FILENO;
    do_cat(fd, "<STDOUT>");
  } else {
    for (int i = 1; i < argc; i++) {
      fd = open(argv[1], O_RDONLY);
      if (fd < 0) die(argv[1]);
      do_cat(fd, argv[i]);
    }
  }
  exit(0);
}

#define BUFFER_SIZE 2048

static void do_cat(const int fd, const char* path) {
  unsigned char buf[BUFFER_SIZE];

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
