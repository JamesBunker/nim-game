/*
 * Student ID: bunkerj
 * Student Number: 1130246
 * Class: CIS2520 F21
 * Assignment 7
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct move {
    int row;
    int matches;
    int hash;
};

struct node {
    int nimsum;
    int*board;
    int moves;
    struct move *move;
};

int*new_board(int board_size);
struct node *mk_nim_hash(int max_hash, int board_size, int*start_board);
void free_board(int*board);
void free_nim_hash(int max_hash, struct node *nim_hash);
int*board_from_argv(int board_size, char**argv);
int*copy_board(int board_size, int*board);
int game_over(int board_size, int*board);
void join_graph(struct node *nim_hash, int hash, int board_size, int*start_board);

//helper
void print_board(int board_size, int *board);
int compute_max_hash(int board_size, int *start_board);
int board2hash(int board_size, int *start_board, int *current_board);
int *hash2board(int board_size, int *start_board, int hash);

//20%
int compute_nimsum(int board_size, int*board);
