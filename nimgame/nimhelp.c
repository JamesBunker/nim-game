/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: Colvin
 *
 * Created on November 22, 2021, 3:18 p.m.
 */


#include "nim.h"

void print_board(int board_size, int *board)
/* print board file in human readable format
 */ {
    for (int i = 0; i < board_size; i++) {
        printf("[%2d]: ", i);
        for (int j = 0; j < board[i]; j++)
            printf("|");
        printf("\n");
    }
}

int compute_max_hash(int board_size, int *start_board)
/* compute the total number of possible boards that could
 * occur in a game given the start_board
 */ {
    int max;
    max = 1;

    for (int i = 0; i < board_size; i++) {
        max *= (start_board[i] + 1);
    }

    return max;
}

int board2hash(int board_size, int *start_board, int *current_board)
/* compute a perfect hash for the current board
 */ {
    int hash = 0;
    int mult = 1; // row multiplier

    for (int i = 0; i < board_size; i++) {
        hash += current_board[i] * mult; // add pieces time row mult
        mult *= (start_board[i] + 1);
    }
    return hash;
}

int *hash2board(int board_size, int *start_board, int hash)
/* invert the perfect hash function
 * allocate a board
 */ {
    int *board;

    board = new_board(board_size); // this includes malloc

    for (int i = 0; i < board_size; i++) {
        board[i] = hash % (start_board[i] + 1);
        // extract pieces from hash
        //
        hash /= (start_board[i] + 1);
    }

    return board;
}

