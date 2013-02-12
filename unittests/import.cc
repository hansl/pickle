#include "pickle.h"

int main() {
  pickle_parser_t p = pickle_create_parser();
  pickle_load_source(p, "import.pcl");

  assert(pickle_query(p, "param2") == "HELLO WORLD");
}