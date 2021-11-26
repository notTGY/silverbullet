#include<stdio.h>

#include"Debug.h"

#include"find_imports.c"

int main(int argc, char** argv) {
  char* input_filename;
  char* output_filename;
  if (argc < 2) {
    input_filename = "./index.js";
    output_filename = "./index.sb.js";
  }

  if (argc == 2) {
    input_filename = argv[1];
    output_filename = "./index.sb.js";
  }

  if (argc == 3) {
    input_filename = argv[1];
    output_filename = argv[2];
  }

  debug(
    "input: %s, output: %s\n",
    input_filename,
    output_filename
  );

  char** res = find_imports(input_filename);
  int i = 0;
  while (res[i]) {
    printf("%d: %s\n", i, res[i]);
    i++;
  }
}
