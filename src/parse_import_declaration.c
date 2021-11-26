#include<stdlib.h>
#include<string.h>

#include"Debug.h"

#define IMPORT_STRING "import"

char* parse_import_declaration(char** import_start) {
  char *quote1_start, *quote2_start, *quote_end, *ret;

  quote1_start = strchr(*import_start, '"');
  quote2_start = strchr(*import_start, '\'');

  if (quote1_start && quote2_start) {
    if (quote1_start < quote2_start)
      quote2_start = 0;
    else
      quote1_start = 0;
  }

  if (quote1_start) {
    quote_end = strchr(quote1_start + 1, '"');

    quote_end[0] = '\0';
    debug("%s\n", quote1_start + 1);

    ret = malloc(quote_end - quote1_start);
    strcpy(ret, quote1_start + 1);

    quote_end[0] = '\'';
  } else if (quote2_start) {
    quote_end = strchr(quote2_start + 1, '\'');

    quote_end[0] = '\0';
    debug("%s", quote2_start + 1);

    ret = malloc(quote_end - quote2_start);
    strcpy(ret, quote2_start + 1);

    quote_end[0] = '"';
  } else {
    printf(
      "Couldn't resolve associated filename, make sure to surround it with \" or '\n"
    );
  }

  *import_start = strstr(quote_end, IMPORT_STRING);

  return ret;
}

