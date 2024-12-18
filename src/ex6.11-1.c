// stdio版のcat

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

static void do_cat(FILE* f) {
  int c;
  char* tab = "\\t";
  char* newline = "$\n";
  char letter[2];
  letter[1] = '\0';
  char* out = NULL;

  while ((c = fgetc(f)) != EOF) {
    if (c == '\t') {
      out = tab;
    } else if (c == '\n') {
      out = newline;
    } else {
      letter[0] = (char)c;
      out = letter;
    }
    errno = 0;
    if (fputs(out, stdout) == EOF) {
      if (errno) {
        perror("fputs");
        exit(1);
      }
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
