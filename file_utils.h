//
//  file_utils.h
//  Connect 4
//
//  Created by Amanda Malaric on 2/2/17.
//  Copyright © 2017 Amanda Malaric. All rights reserved.
//

#ifndef file_utils_h
#define file_utils_h

//takes a file, buffer, width, and height and assigns buffer
int save_board( char* filename, char **buffer, int width, int height);

//takes in file and returns size
int board_size(char *filename);
#endif /* file_utils_h */
