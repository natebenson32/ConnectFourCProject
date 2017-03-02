#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
//#include "handle_arguments.h"
//#include "file_utils.h"
#define ROWS 7
#define COLUMNS 6

//custom functions//
void Board(char *board);
void placePiece(int position, int turn_num);
void turn(int turn_num);
void save_board();
void load_board();



int main(int argc, char **argv) {
    
    //take in user input here//
    //start with the piece type, X or O//
    char player_one_piece, player_two_piece;
    int win_condit;
    char board[ROWS * COLUMNS];
    memset(board, '*', ROWS * COLUMNS);
    
    
    printf("--------------------------------------------------------------------\n");
    printf("Enter either X or O for player 1: ");
    scanf("%c", &player_one_piece);
    player_one_piece = toupper(player_one_piece);
    
    
    if(player_one_piece == 'X' ){
        player_two_piece = 'O';
        
        printf("Player 1: %c\n", player_one_piece);
        printf("Player 2: %c\n", player_two_piece);
        printf("--------------------------------------------------------------------\n");
        
        
    }else if(player_one_piece == 'O' ){
        player_two_piece = 'X';
        
        printf("Player 1: %c\n", player_one_piece);
        printf("Player 2: %c\n", player_two_piece);
        printf("--------------------------------------------------------------------\n");
        
        
    }else{
        printf("\nInvalid input!\n Assigned player 1 to X, player 2 to O!\n");
        printf("Board is generating...\n");
        
        player_one_piece = 'X';
        player_two_piece = 'O';
        
        printf("Player 1: %c\n", player_one_piece);
        printf("Player 2: %c\n", player_two_piece);
        printf("--------------------------------------------------------------------\n");
        
    }
    printf("--------------------------------------------------------------------\n");
    printf("Enter your win condition(#):");
    scanf("%d", &win_condit);
    
    
    if(isdigit(win_condit) || win_condit <= 0){
        printf("Incorrect input!\n");
        printf("Assigning default win condition of 4! Happy playing!\n");
        printf("--------------------------------------------------------------------\n");
        
        win_condit = 4;
    }
    
    printf("It will take %d touching pieces of the same type to win! Good Luck!\n", win_condit);
    printf("--------------------------------------------------------------------\n");
    
    
    
    int turn_num = 0;
    
    Board(board);
    turn(turn_num);
    
    
    
    //call placePiece here//
    
    
}

/**
 * Initilizes the board
 * @param board created board
 */
void Board(char *board){
    int row, col;
    for(row = 0; row < ROWS; row++){
        for(col = 0; col < COLUMNS; col++){
            printf(" %c ",  board[COLUMNS * row + col]);
        }
        printf("\n");
    }
}


/**
 *Keep track and print out the current players turn.
 *@param turn_num turn for the current player
 */
void turn(int turn_num){
    
    int position_two, position_one;
    
    if(turn_num == 0){
        printf("Player 1! Your turn!\n");
        printf("Enter position to place piece: ");
        scanf("%d", &position_one);
        placePiece(position_one, turn_num);
    }else if (turn_num % 2 == 0){
        printf("Player 2! Your turn!\n");
        printf("Enter position to place piece: ");
        scanf("%d", &position_two);
        placePiece(position_two, turn_num);
    }
}

/**
 * Save the board state to a file
 *
 */
void save_board(){
    //todo
    
    
}


/**
 * Load the board that was saved to file
 *
 */
void load_board(){
    //todo
    
}

