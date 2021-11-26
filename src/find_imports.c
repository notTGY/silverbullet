#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<errno.h>

#include"Debug.h"

#include"parse_import_declaration.c"

#define BUF_SIZE (64 * 1024)
#define IMPORT_STRING "import"
#define FILE_MAX_NUM 100

/**
 * function that returns list of filenames, imported
 * from the file given as param
 */
char** find_imports(char* filename) {
  char *import_start, *buf = malloc(BUF_SIZE);
  int fd, length, found;

  char **ret = malloc(FILE_MAX_NUM * sizeof(char*));

  if ((fd = open(filename, O_RDONLY)) < 0) {
    perror("failed to open file");
    exit(errno);
  }

  if ((length = read(fd, buf, BUF_SIZE)) < 0) {
    perror("failed to read file");
    exit(errno);
  }
  /**
   * stack overflow
   */
  buf[length] = '\0';

  debug("Read file %s:\n%s\n", filename, buf);

  import_start = strstr(buf, IMPORT_STRING);

  found = 0;
  while (import_start) {
    debug("Found match:\n-->%s\n", import_start);
    ret[found] = parse_import_declaration(
      &import_start
    );

    found++;
    if (found > FILE_MAX_NUM + 1)
      printf(
        "You included > 100 imports in signle file"
      );
  }

  free(buf);
  if (close(fd) < 0) {
    perror("failed to close file");
    exit(errno);
  }
  ret[found] = NULL;
  return ret;
}

