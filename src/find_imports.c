#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<errno.h>

#define BUF_SIZE (64 * 1024)
#define IMPORT_STRING "import"

/**
 * function that returns list of filenames, imported
 * from the file given as param
 */
char** find_imports(char* filename) {
  char *import_start, *quote1_start, *quote2_start,
    *quote_end, *buf = malloc(BUF_SIZE);
  int fd, length;

  if (buf == NULL) {
    perror("can't allocate memory");
    exit(errno);
  }

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

  printf("Read file %s:\n%s\n", filename, buf);

  import_start = strstr(buf, IMPORT_STRING);

  while (import_start) {
    printf("Found match:\n-->%s\n", import_start);
    quote1_start = strchr(import_start, '"');
    quote2_start = strchr(import_start, '\'');

    if (quote1_start && quote2_start) {
      if (quote1_start < quote2_start)
        quote2_start = 0;
      else
        quote1_start = 0;
    }
    if (quote1_start) {
      quote_end = strchr(quote1_start + 1, '"');

      quote_end[0] = '\0';
      printf("__%s__\n", quote1_start + 1);
      quote_end[0] = '\'';
    } else if (quote2_start) {
      quote_end = strchr(quote2_start + 1, '\'');

      quote_end[0] = '\0';
      printf("__%s__", quote2_start + 1);
      quote_end[0] = '"';
    } else {
      printf(
        "Couldn't resolve associated filename, make sure to surround it with \" or '\n"
      );
      goto CLEAR;
    }


    /**
     * next iteration (do not repeat same entry)
     */
    import_start = strstr(quote_end, IMPORT_STRING);
  }

CLEAR:
  free(buf);
  if (close(fd) < 0) {
    perror("failed to close file");
    exit(errno);
  }
}

