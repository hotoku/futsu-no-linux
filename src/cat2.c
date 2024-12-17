// stdio版のcat

#include <stdio.h>
#include <stdlib.h>

static void do_cat(FILE* f) {
  int c;

  while ((c = fgetc(f)) != EOF) {
    if (putchar(c) < 0) {
      exit(1);
    }
  }
}

int main(int argc, char* argv[]) {
  FILE* f = stdin;
  int c;

  if (argc < 2) {
    do_cat(f);
    exit(0);
  } else {
    for (int i = 1; i < argc; i++) {
      f = fopen(argv[i], "r");
      if (!f) {
        perror(argv[i]);
        exit(1);
      }
      do_cat(f);
    }
  }

  exit(0);
}
