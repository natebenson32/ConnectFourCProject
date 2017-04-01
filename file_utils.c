//
//  file_utils.c
//  Connect 4
//
//  Created by Amanda Malaric on 2/2/17.
//  Copyright © 2017 Amanda Malaric. All rights reserved.
//
//Description: This source file has two functions that are
//supported by file_utils.h.
//save_board takes in a pointer for filename and a double pointer for a buffer. It then reads the file in in read mode, checks to see if the file isnt null, then reads its contents and counts a size, inputting the contents into a buffer, then closing the file.

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "file_utils.h"
#include <ctype.h>

int save_board( char* filename, char **buffer, int width, int height){
    
    //take in second filename as output file
    FILE* write_to_file=fopen(filename, "w");
    
    //can not write to file, print error
    if(!write_to_file){
        fprintf(stderr, "Can't reserve memory for %s!\n\n", filename);
        
        exit(EXIT_FAILURE);
    }
    
    //else the file did open and you can begin to write to it
    printf("\n%s is being written to!\n\n", filename);
    
    //put method found at https://www.tutorialspoint.com/cprogramming/c_file_io.htm
    
    for(int i = 0; i <=height-1; i++) {
        for(int j = 0; j <=width-1; j++) {
            //writes from the buffer to the file
            fputc(buffer[i][j], write_to_file);
            printf("%c", buffer[i][j]);
        }
        printf("\n");
        fputs("\n", write_to_file);
        
    }
    
    //close the write file
    fclose(write_to_file);
    struct stat ts;
    stat(filename, &ts);
    long size_to_write = ts.st_size;
    
    return (int)size_to_write;

}

int board_size(char *filename){
    
    struct stat ts;
    stat(filename, &ts);
    long size_to_write = ts.st_size;
    
    return (int)size_to_write;
}

