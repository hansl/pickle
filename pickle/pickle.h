// TODO: Add MIT license
#ifndef PICKLE_H__
#define PICKLE_H__



typedef void* pickle_param_t;
typedef void* pickle_value_t;

////////////////////////////////////////////////////////////////////////////////
// Values and Value Types.

// There are 5 types of values.
enum pickle_value_type_e {
  PICKLE_NULL_VALUE = 0,
  PICKLE_NUMBER_VALUE = 1,
  PICKLE_STRING_VALUE = 2,
  PICKLE_TUPLE_VALUE = 3,
  PICKLE_DICTIONARY_VALUE = 4
};

int pickle_is_null(pickle_value_t value);
int pickle_is_string(pickle_value_t value);
int pickle_is_number(pickle_value_t value);
int pickle_is_tuple(pickle_value_t value);
int pickle_is_dictionary(pickle_value_t value);

pickle_value_type_e pickle_type_of(pickle_value_t value);

const char* pickle_as_cstring(pickle_value_t value);
const int* pickle_as_int(pickle_value_t value);
const double* pickle_as_double(pickle_value_t value);

const pickle_value_t pickle_value_at_index(pickle_value_t tuple, )

#endif  // PICKLE_H__