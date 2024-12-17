// stdio版のcat

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
  FILE* f = stdin;
  int c;

  while ((c = fgetc(f)) != EOF) {
    if (putchar(c) < 0) {
      exit(1);
    }
  }

  exit(0);
}
