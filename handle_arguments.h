#ifndef H_HANDLE_ARGUMENTS
#define H_HANDLE_ARGUMENTS

#include <argp.h>

// Define the arguments struct that will hold the values
// for flags that provide arguments.

struct arguments {
  int width;
  int height;
  int square;
  int connect;
  char *load;
};

// Function to setup values once they are parsed.
error_t parse_opt(int key, char* arg, struct argp_state *state);

// Function to begin the parsing process.
struct arguments* setup(int argc, char** argv);

#endif
