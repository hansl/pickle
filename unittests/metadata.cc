#include "pickle.h"

int acc = 0;

pickle_param_t accumulator(pickle_param_t p) {
  acc++;
  return p;
}

pickle_param_t translator(pickle_param_t p, pickle_number_t id,
                          pickle_string_t lang) {
  if (pickle_is_null_value(lang)) {
    // Lang was ommitted
    assert(pickle_as_integer(id) == 123);
    pickle_value_t v = pickle_value_from_cstring("Hello World Translated");
    pickle_set_value(p, v);
    pickle_release_value(v);
  } else {
    assert(strcmp(pickle_as_cstring(lan), "fr") == 0);
    pickle_value_t v = pickle_value_from_cstring("Hello Monde");
    pickle_set_value(p, v);
    pickle_release_value(v);
  }
  return p;
}

int main() {
  pickle_parser_t p = pickle_create_parser();
  pickle_add_meta("accumulator", accumulator);
  pickle_add_meta("translate", translator);
  assert(pickle_load_source(p, "import.pcl") == 0);

  assert(pickle_query(p, "param2") == "Hello World Translated");
  assert(pickle_query(p, "param3") == "Hello Monde");
}