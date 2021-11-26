#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<errno.h>

#define BUF_SIZE (64 * 1024)
#define IMPORT_STRING "import"

char** findImports(char* filename) {
  char *import_start, *quote1_start, *quote2_start,
    *buf = malloc(BUF_SIZE);
  int input_fd, length;

  if (buf == NULL) {
    perror("can't allocate memory");
    exit(errno);
  }

  if ((input_fd = open(filename, O_RDONLY)) < 0) {
    perror("failed to open file");
    exit(errno);
  }

  if ((length = read(input_fd, buf, BUF_SIZE)) < 0) {
    perror("failed to read file");
    exit(errno);
  }
  /**
   * stack overflow
   */
  buf[length] = '\0';

  printf("Read file %s:\n%s\n", filename, buf);

  import_start = strstr(buf, IMPORT_STRING);

  while (import_start) {
    printf("Found match:\n-->%s\n", import_start);
    /**
     * next iteration (do not repeat same entry)
     */
    import_start = strstr(
      import_start + 1, IMPORT_STRING
    );
  }

  free(buf);
}


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

  printf("input: %s, output: %s\n", input_filename, output_filename);

  char** res = findImports(input_filename);
}
