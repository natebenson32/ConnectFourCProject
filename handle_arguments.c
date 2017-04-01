#include <stdlib.h>
#include "handle_arguments.h"

// Documentation strings.
char doc[] = "A program to parse arguments for connect four.";
char args_doc[] = "Width, Height, Square, Connect, Load.";

// This option struct is for any optional arguments.
struct argp_option options[] = {
  {"width",'w',"WIDTH",0,"Width of the board" },
  {"height",'h',"HEIGHT",0,"Height of the board" },
  {"square",'s',"SQUARE",0,"Square board" },
  {"connect",'c',"CONNECT", 0, "Number of connections to win" },
  {"load",'l',"LOAD",0, "Loads a board" },
  { 0 }
};

// Argp requires us to pass these values in via the argp struct
struct argp argp = { options, parse_opt, args_doc, doc };
// Declare a variable called arguments that is also an
// arguments struct.  Remeber - we can't use the struct
// by just describing it.  We also need to make one.  Sort
// of similar to how we instantiate an object in Java.
struct arguments arguments;

// Our custom function for setting up values once they
// have been parsed from the command line args.
error_t parse_opt(int key, char* arg, struct argp_state *state){
  struct arguments *arguments = state->input;
  switch(key){
  case 'w':
          //width contraint
    arguments->width = atoi(arg);
    break;
  case 'h':
          //height constraint
    arguments->height = atoi(arg);
    break;
  case 's':
          //square constraint
    arguments->square = atoi(arg);
    break;
  case 'c':
          //win constraint
    arguments->connect = atoi(arg);
    break;
  case 'l':
          //load board constraint
    arguments->load = arg;
  default:
          //not known argument
    return ARGP_ERR_UNKNOWN;
  }
  return 0;
}

// Here we setup some default values and override them
// if we get new values from the commandline.
struct arguments* setup(int argc, char** argv){
  // Default of first, second, and load_file
  arguments.width = 7;
  arguments.height = 7;
  arguments.square = 7;
  arguments.connect = 4;
  arguments.load = NULL;
  // Call argp to do its thing.
  argp_parse(&argp, argc, argv, 0, 0, &arguments);
  // Return values are in the arguments struct.  Pull
  // them out if they are there.
  int width = arguments.width;
  int height = arguments.height;
  int square = arguments.square;
  int connect = arguments.connect;
  printf("Width: %d\nHeight: %d\nSquare: %d\nConnect: %d\n\n", width, height, square, connect);
  if(arguments.load != NULL){
    printf("Load file: %s\n\n", arguments.load);
  }
  return &arguments;
}
