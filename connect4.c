#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "handle_arguments.h"
#include "file_utils.h"
#include <string.h>


int width;
int height;
int square;
int win_condit;
int turn_num = 0;
int is_complete = 0;

//Custom function declarations//
void Board_load(char * filename, char *board, int size);
int new_height(char *board, int size);
int new_width(char *board, int size);
void Board(char **board);
int place_piece(int *c, char **board, int turn_print_num);
void Board_update(char **board);
void Saved_update(char ** new_board, char *board, int height, int width, int size);
int print_turn(int t);
void check_win(char **board, int *c);


int main(int argc, char *argv[]){
    struct arguments* gameArgs = setup(argc, argv);
    
    width = gameArgs->width;
    height = gameArgs->height;
    square = gameArgs->square;
    win_condit = gameArgs->connect;
    
    if(square != 0){
        width = square;
        height = square;
        printf("\nYou passed a square value, this overrides any height or width values passed");
        printf("\nYour board values have been set to: %d",
               square);
    } else{
        square = 7;
    }
    if(width <= 2){
        width = 3;
        printf("\nMinimum allowable width size is 3. Width has been set to 3");
    }
    if(height <= 2){
        height = 3;
        printf("\nMinimum allowable height size is 3. Height has been set to 3");
    }
    if(win_condit > width || win_condit > height){
        width = 7;
        height = 7;
        win_condit = 4;
        printf("\nIncompatible game values entered.\nReverting to default game values...");
    }
    
    //input is for the piece placement
    //size is the size of the saved board
    int input = 0, size=0;
    //making a board **
    char **board = malloc(height * sizeof(char*));
    
    //starting by creating the board
    Board(board);
    
    //do while the board is not full
    while(is_complete == 0 ){
        
        //takes the loaded board
        if(load){
            
            //finds the size of the board
            size = board_size(load);
            
            //loads the actual board
            Board_load(load, *board, size);
            
            //finds height of new board
            int loaded_height = new_height(*board, size);
            
            //finds width of new board
            int loaded_width = new_width(*board, size);
            
            //creates new board
            char **new_board = malloc(loaded_height+1 * sizeof(char*));
            
            //loads file to new board
            Saved_update(new_board, *board, loaded_height, loaded_width, size);
            load = NULL;
            
            //updates the playing space
            Board_update(new_board);

        } else {
            
            //regular board, turns
            int turns = print_turn(turn_num);
            
            //gets user input
            scanf("%d", &input);
            
            //places a piece
            int temp = place_piece(&input, board, turns);
            
            //checks for valid move
            if(temp==1){
                turn_num++;
            }
            
            //updaes the board
            Board_update(board);
            
            //checks for a win
            check_win(board, &input);
            printf("\nIf you would like to save the board, type in -1\n");
            
            
            //saves the file if requested
            if(input == -1){
                
                //finds size
                size = save_board("saved.txt", board, width, height);
                
                //prints that it saved
                printf("\nsaved.txt has been saved!\n\n");
                exit(0);
                input=0;
            }
        }
    }
    
    return 0;
}

//loads the board from the saved file
void Board_load(char * filename, char *board, int size){
    //file to open/ attempt to open file
    FILE * file_to_read = fopen(filename, "r");
    
    if (file_to_read==NULL){
        fprintf(stderr, "Can't reserve memory for %s!\n\n", filename);
        
        exit(EXIT_FAILURE);
    }
    
    //file did in fact open, continue
    printf("%s is open!\n\n", filename);
    
    //give buffer a size allocation for memory
    char file_cursor;
    
    // input method found at https://www.tutorialspoint.com/cprogramming/c_file_io.htm
    for(int i = 0; i <= (size-1); i++) {
        //get character from file, one by one
        //incremented by size
        file_cursor=fgetc(file_to_read);
        board[i]=file_cursor;
    }
    fclose(file_to_read);
}

//takes in the board and finds the height
//by taking the number of new line characters
int new_height(char *board, int size){
    int loaded_height=0;
    for(int i = 0; i <= (size-1); i++) {
        if(board[i]=='\n'){
            loaded_height++;
        }
    }
    return loaded_height;
}

//finds the width by counting the height and not
//new line characters then divides them
int new_width(char *board, int size){
    int loaded_width=0, loaded_height=0, var=0;
    for(int i = 0; i <= (size-1); i++) {
        if(board[i]!='\n'){
            var++;
        }
        if(board[i]=='\n'){
            loaded_height++;
        }
    }
    loaded_width = var/loaded_height;
    return loaded_width;
}

//creates a board given height and width
void Board(char **board){
    printf("%s", "\n\nCreating board...\n");
    for(int i=0; i<height; i++){
        board[i] = malloc(width * sizeof(char));
    }
    
    //assigns each element as an astrick
    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            *(*(board+i)+j) = '*';
        }
    }
    
    //prints the board to the user
    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            printf("%c ", board[i][j]);
            if(j == (width-1))
                printf("%s", "\n\n");
        }
    }
    
    printf("%s", "\nBoard created!");
    printf("%s", "\nAssigning player characters . . . \n");;
    printf("%s", "Player one will print 'X's and \nPlayer two will print 'O's\n");
    printf("%s", "\n\nBegin!");
}

//updates the board when a piece is placed
void Board_update(char **board){
    
    printf("\nBoard Updated!!\n\n");
    
    //prints the board to the user
    for(int i=0; i<=height-1; i++){
        for(int j=0; j<=width-1; j++){
            printf("%c ", board[i][j]);
        }
        printf("\n\n");
    }
}

//updates the board with the saved board
void Saved_update(char **new_board, char *board, int height, int width, int size){

    int k=0;
    printf("Board Loaded from file\n\n");
    
    //creates new board allocating memory
    for(int i=0; i<height; i++){
        new_board[i] = malloc(width * sizeof(char));
    }
    
    //my attempt here did not go well
    //assigns contents of old board to new board
    char temp[size-1];
    for( k = 0; k <= (size-1); k++) {
        temp[k]=board[k];
        if(board[k]=='\n'){
            temp[k]='\0';
            printf("\n");
        }
        printf("%c", temp[k]);
    }

}

/**
    Takes in variable t
    if t is even, its player 1's turn
    if t is odd, player 2 goes
 */
int print_turn(int t){
    if(t%2 == 0){
        printf("\nPlayer 1! Your Turn!");
        printf("Enter a column\n");
        return 0;
    }
    else{
        printf("\nPlayer 2! Your turn!");
        printf("Enter a column\n");
        return 1;
    }
}

/**
    places piece on the board
    takes the turn in as either x or o
 */
int place_piece(int *c, char **board, int turn_print_num){
    // offset for computer science counting
    // w is our new variable for our column
    int w = *c-1;
    // iterate through board but only in specified column (w is constant)
    for(int i =0; i<height; i++){
        // immediate check that the column value passed
        // is within the board, if not, return 0
        if(w < 0 || w >= width){
            return 0;
        }
        // if iterator finds a piece at [i][w]
        if(board[i][w]== 'X' || board[i][w] == 'O'){
            // if we found one at the top row, we can't place a piece because rules
            if(i==0){
                //we cant place a piece in this column so return 0
                return 0;
            }
            // otherwise place a piece above the piece we found
            // check for placing an X
            if(print_turn(turn_num)==0){
                board[i-1][w] = 'X';
                return 1;
            }
            // check for placing an O
            else {board[i-1][w] = 'O';return 1;}
        }
        // otherwise if we're at the bottom, place a piece there
        else if(i == height-1){
            if(print_turn(turn_num) == 0){
                board[i][w] = 'X';
                return 1;		
            }
            else {board[i][w] = 'O';return 1;}
        }
    }
    printf("\nSome place_piece error ocurred");
    return 0;

}

/**
    checks the win 
    with horizontal, vertical,
    and diagnonal conditions
    on the current board
    Implemented off of some old java code
*/
void check_win(char **board, int *c){
    // Checks for horizontal win
    for(int x=0; x<height; x++){
        for(int y=0; y<width; y++){
            int count_x = 0;
            int count_o = 0;
            
            if(board[x][y] == 'X'){
                if(y <= width-win_condit){
                    for(int i=0; i<win_condit; i++){
                        if(board[x][y+i] == 'X')
                            count_x++;
                    }
                } else {
                    for(int i=y; i<width-1; i++){
                        if(board[x][y+i] == 'X')
                            count_x++;
                    }
                }
                if(count_x >= win_condit){
                    printf("Player X wins!\n");
                    exit(0);
                }
            }
            if(board[x][y] == 'O'){
                if(y <= width-win_condit){
                    for(int i=0; i<win_condit; i++){
                        if(board[x][y+i] == 'O')
                            count_o++;
                    }
                } else {
                    for(int i=y; i<width-1; i++){
                        if(board[x][y+i] == 'O')
                            count_o++;
                    }
                }
                if(count_o >= win_condit){
                    printf("Player O wins!\n");
                    exit(0);
                }
            }
        }
    }
    // Checks for vertical win
    for(int x=0; x<height; x++){
        for(int y=0; y<width; y++){
            int count_x = 0;
            int count_o = 0;
            
            if(board[x][y] == 'X'){
                if(x <= height-win_condit){
                    for(int i=0; i<win_condit; i++){
                        if(board[x+i][y] == 'X')
                            count_x++;
                    }
                } else {
                    for(int i=0; i<height-x; i++){
                        if(board[x+i][y] == 'X')
                            count_x++;
                    }
                }
                if(count_x >= win_condit){
                    printf("Player X wins!\n");
                    exit(0);
                }
            }
            if(board[x][y] == 'O'){
                if(x <= height-win_condit){
                    for(int i=0; i<win_condit; i++){
                        if(board[x+i][y] == 'O')
                            count_o++;
                    }
                } else {
                    for(int i=0; i<height-x; i++){
                        if(board[x+i][y] == 'O')
                            count_o++;
                    }
                }
                if(count_o >= win_condit){
                    printf("Player O wins!\n");
                    exit(0);
                }
            }
        }
    }
    
    //check diagonal wins with win condition
    // Go diagonally right downwards
    
    for(int x=0; x<height; x++){
        for(int y=0; y<width; y++){
            if(board[x][y] == 'X'){
                int count_x = 0;
                
                // Finds Down-Left 'X'
                if(x <= height-win_condit){
                    for(int i=0; i<win_condit; i++){
                        if(board[x+i][y-i] == 'X')
                            count_x++;
                    }
                } else {
                    for(int i=0; i<height-x; i++){
                        if(board[x+i][y-i] == 'O')
                            count_x++;
                    }
                }
                if(count_x>=win_condit){
                    printf("Player X wins!\n");
                    exit(0);
                }
                count_x = 0;
                
                // Finds Down-Right 'X'
                if(x <= height-win_condit){
                    for(int i=0; i<win_condit; i++){
                        if(board[x+i][y+i] == 'X')
                            count_x++;
                    }
                } else {
                    for(int i=0; i<height-x; i++){
                        if(board[x+i][y+i] == 'X')
                            count_x++;
                    }
                }
                if(count_x >= win_condit){
                    printf("Player X wins!\n");
                    exit(0);
                }
            }
            
            // Finds Down-Left 'O'
            if(board[x][y] == 'O'){
                int count_o = 0;
                
                // Finds Down-Left 'O'
                if(x <= height-win_condit){
                    for(int i=0; i<win_condit; i++){
                        if(board[x+i][y-i] == 'O')
                            count_o++;
                    }
                } else {
                    for(int i=0; i<height-x; i++){
                        if(board[x+i][y-i] == 'O')
                            count_o++;
                    }
                }
                if(count_o>=win_condit){
                    printf("Player O wins!\n");
                    exit(0);
                }
                count_o = 0;
                
                // Finds Down-Right 'O'
                if(x <= height-win_condit){
                    for(int i=0; i<win_condit; i++){
                        if(board[x+i][y+i] == 'O')
                            count_o++;
                    }
                } else {
                    for(int i=0; i<height-x; i++){
                        if(board[x+i][y+i] == 'O')
                            count_o++;
                    }
                }
                if(count_o >= win_condit){
                    printf("Player O wins!\n");
                    exit(0);
                } 
            }
        }
    }
}
