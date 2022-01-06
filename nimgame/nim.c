#include "nim.h"

int*new_board(int board_size) {
    /*
     * Creating board ptr array that allocates board_size integers.
     * board_size: size of array
     * return: array pointer
     */
    int *boardIntPtr = malloc(board_size * sizeof (int));
    //memory not malloced properly
    if (boardIntPtr == NULL) {
        fprintf(stdout, "ERROR: boardIntPtr malloc failed");
        abort();
    }
    return boardIntPtr;
}

struct node *mk_nim_hash(int max_hash, int board_size, int*start_board) {
    /*
     * Creating array of nodes and initializing them.
     * max_hash: number of nodes for array
     * board_size: size of array
     * start_board: starting board array
     * return: node array pointer
     */
    struct node* nodeArray = malloc(max_hash * sizeof (struct node));
    //memory not malloced properly
    if (nodeArray == NULL) {
        fprintf(stdout, "ERROR: nodeArray malloc failed");
        abort();
    }

    //initialzing variables
    for (int i = 0; i < max_hash; i++) {
        nodeArray[i].moves = -1;
        nodeArray[i].move = NULL;
        nodeArray[i].nimsum = -1;
        nodeArray[i].board = hash2board(board_size, start_board, i);
    }

    return (nodeArray);
}

void free_board(int*board) {
    /*
     * Frees the board array.
     * board: nim board array
     * return: void
     */
    free(board);
}

void free_nim_hash(int max_hash, struct node *nim_hash) {
    /*
     * Freeing the array of nodes.
     * max_hash: number of nodes for array
     * nim_hash: array of nodes
     * return: void
     */
     //freeing malloced boards
    for (int i = 0; i < max_hash; ++i) {
        free(nim_hash[i].board);
    }
    free(nim_hash);
}

int*board_from_argv(int board_size, char**argv) {
    /*
     * Creating new board from command line inputs.
     * board_size: size of board
     * argv: command line inputs
     * return: new board array
     */
    int argvInt = 0;
    //mallocing to boardsize of integers
    int * boardArray = malloc(board_size * sizeof (int));
    for (int i = 0; i < board_size; i++) {
        argvInt += atoi(argv[i]);
    }

    //newboard of size of total matches
    boardArray = new_board(argvInt);
    for (int i = 0; i < board_size; i++) {
        //setting up board based on command line inputs
        boardArray[i] = atoi(argv[i]);
    }

    return boardArray;

}

int*copy_board(int board_size, int*board) {
    /*
     * Copying existing board into new int array.
     * board_size: size of board
     * board: board to copy
     * return: copy of old board
     */
    int*newBoard = malloc(sizeof (int)*board_size);
	//int * newBoard = new_board(board_size);
    int temp = 0;
    for (int i = 0; i < board_size; i++) {
        temp = board[i];
        newBoard[i] = temp;
	//newBoard[i] = board[i];
    }
    return newBoard;
}

int game_over(int board_size, int*board) {
    /*
     * If 1 match is left game is over.
     * board_size: size of board
     * board: current board array
     * return: 1 for game over and 0 otherwise
     */
    int matchesLeft = 0;
    for (int i = 0; i < board_size; i++) {
        //total matches left
        matchesLeft += board[i];
    }
    if (matchesLeft == 1) {
        //someone has to take last match and loses
        return 1;
    }
    return 0;
}

void join_graph(struct node *nim_hash, int hash, int board_size, int*start_board) {
    /*
     * Recursively joining the nodes on graph from index hash, exits if move is -1.
     * nim_hash: array of nodes
     * hash: index to join at
     * board_size: size of board
     * start_board: starting board array
     */
    int moveSum = 0;
    //base case, moves initialized already
    if (nim_hash[hash].moves != -1) {
        return;
    }

    for (int i = 0; i < board_size; i++) {
        moveSum += start_board[i];
    }
    //allocating moveSum of move structs
    nim_hash[hash].moves = moveSum;
    nim_hash[hash].move = malloc(moveSum * sizeof (struct move));


    int *tmpBoard;//copy of board
    int moveNum = 0;

    //going through all possiblilitys 
    for (int j = 0; j < board_size; j++) {
        for (int k = 1; k <= nim_hash[hash].board[j]; k++) {
            
            nim_hash[hash].move[moveNum].row = j;
            nim_hash[hash].move[moveNum].matches = k;
            tmpBoard = copy_board(board_size, nim_hash[hash].board);
            tmpBoard[j] -= k;
	
            nim_hash[hash].move[moveNum].hash = board2hash(board_size, start_board, tmpBoard);

            free(tmpBoard);
            
            
	    nim_hash[hash].nimsum = compute_nimsum(board_size, nim_hash[hash].board);
	
	    //recursive call
        join_graph(nim_hash, nim_hash[hash].move[moveNum].hash, board_size, start_board);
	    moveNum++;

            
        }
    }

    

}

int compute_nimsum(int board_size, int*board) {
    /*
     * Calculating XOR of all integer values in board, if no values >1 then
     * negations of nimsum returned.
     * board_size: size of board
     * board: current board array
     * return: calculated nimsum
     */
    int validNimSum = 0;
    //must have value greater than 1
    for (int i = 0; i < board_size; i++) {
        if (board[i] > 1) {
            validNimSum = 1;
        }
    }

    int nimsum = board[0];
    for (int i = 1; i < board_size; i++) {
        //^ XOR operator
        nimsum = nimsum ^ board[i];
    }

    if (validNimSum == 1) {
        return (nimsum);
    }
    //! negation operator
    return (!nimsum);
}
