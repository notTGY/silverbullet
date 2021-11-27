#include"Debug.h"


#define MAX_TOTAL_FILES (65 * 1024)

char** recursive_import_calc(char* root) {
  debug("starting calc for %s\n", root);
  char** res = malloc(MAX_TOTAL_FILES * sizeof(char*));
  char** root_imports = find_imports(root);
  char** tmp;
  int cur = 0;

  res[cur] = root;
  cur++;

  for (int i = 0; root_imports[i]; i++) {
    debug("requesting calc for %s\n", root_imports[i]);
    char** tmp = recursive_import_calc(root_imports[i]);
    for (int j = 0; tmp[j]; j++)
      res[cur++] = tmp[j];
  }
  res[cur] = 0;

  return res;
}

