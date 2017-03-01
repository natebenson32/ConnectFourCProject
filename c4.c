#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//#include "file_utils.h"
#define WIDTH 7 
#define HEIGHT 6

void drawBoard(int width, int height){

    char grid[WIDTH][HEIGHT];
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
           grid[i][j] = '*';
            printf("%c ", grid[i][j]);
        }
        printf("\n");
    }
}


int main(int argc, char **argv) {
   // if(arc == 
   drawBoard(WIDTH, HEIGHT);
}


