#include "toplev.h"

int main(int argc, char **argv) {
  toplev v;
  int r = v.main(argc, argv);
  v.finalize();
  return r;
}
