#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
    short int points[7];    // array of evaluation scores
    struct Node* next[7];   // array of pointers to child nodes
} Node;
typedef Node * Tree;

typedef struct {
    int column; // the column index of the move(0-6)
    int score;  // evaluation score of the move
} Move;

// Recursively creates a tree up to the specified depth
Tree createTree(int depth) {
    if(depth == 0)  // base case
        return NULL;
    
    Tree node = malloc(sizeof(Node));   // memory allocation
    if(!node) { // check for insufficient memory
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    for(int i=0; i<7; i++) {    // initialize node fields and recursively create child nodes
        node->points[i] = 0;
        node->next[i] = createTree(depth-1);
    }
    
    return node;
}

void initializeBoard(char board[6][7]) {
    for(int i=0; i<6; i++)  // loop through each row
        for(int j=0; j<7; j++)  // loop through each column
            board[i][j] = ' ';  // set each cell to empty
}

void printBoard(char board[6][7]) {
    printf(" 1 2 3 4 5 6 7\n");    // print column labels
    for(int i=0; i<6; i++) {    //print each row of the board
        printf("|");
        for(int j =0; j<7; j++)
            printf("%c|", board[i][j]);
        printf("\n");
    }
    printf("---------------\n");    // print an horizontal separator
}

// check for an horizontal win in the game board
int checkHorizontal(char board[6][7]) {
    for(int i = 0; i<6; i++)    // iterate over all rows
        for(int j=0; j<4; j++) {    // iterate up to the last possible point for 4-in-a-row
            if(board[i][j] == 'X' && board[i][j+1] == 'X' && board[i][j+2] == 'X' && board[i][j+3] == 'X')
                return 1; // return that the winner is 'X'
            if(board[i][j] == 'O' && board[i][j+1] == 'O' && board[i][j+2] == 'O' && board[i][j+3] == 'O')
                return 2;   // return that the winner is 'O'
        }
    return 0;   // no win found
}

// check for a vertical win in the game board
int checkVertical(char board[6][7]) {
    for(int i = 0; i<3; i++)    // iterate over all columns
        for(int j=0; j<4; j++) {    // iterate up to the last possible point for 4-in-a-column
            if(board[i][j] == 'X' && board[i+1][j] == 'X' && board[i+2][j] == 'X' && board[i+3][j] == 'X')
                return 1;   // return that the winner is 'X'
            if(board[i][j] == 'O' && board[i+1][j] == 'O' && board[i+2][j] == 'O' && board[i+3][j] == 'O')
                return 2;   // return that the winner is 'O'
        }
    return 0;   // no win found
}

// check for a diagonal win from top-left to bottom-right in the game board
int checkDiagPrim(char m[6][7]) {
    for(int i=0; i<3; i++)  // iterate over starting rows
        for(int j=0; j<4; j++) {    // iterate over starting columns
            if(m[i][j] == 'X' && m[i+1][j+1] == 'X' && m[i+2][j+2] == 'X' && m[i+3][j+3] == 'X')
                return 1;   // return that the winner is 'X'
            if(m[i][j] == 'O' && m[i+1][j+1] == 'O' && m[i+2][j+2] == 'O' && m[i+3][j+3] == 'O')
                return 2;   // return that the winner is 'O'
        }
    return 0;   // no win found
}

// check for a diagonal win from top-right to bottom-left in the game board
int checkDiagSec(char board[6][7]) {
    for(int i = 3; i<6; i++)    // iterate over starting rows
        for(int j=0; j<4; j++) {    // iterate over starting columns
            if(board[i][j] == 'X' && board[i-1][j+1] == 'X' && board[i-2][j+2] == 'X' && board[i-3][j+3] == 'X')
                return 1;   // return that the winner is 'X'
            if(board[i][j] == 'O' && board[i-1][j+1] == 'O' && board[i-2][j+2] == 'O' && board[i-3][j+3] == 'O')
                return 2;   // return that the winner is 'O'
        }
    return 0;   // no win found
}

// check for a win in any direction
int check(char board[6][7]) {
    int result;
    
    result = checkHorizontal(board);
    if(result)
        return result;
    result = checkVertical(board);
    if(result)
        return result;
    result = checkDiagPrim(board);
    if(result)
        return result;
    result = checkDiagSec(board);
    if(result)
        return result;
    return 0;
}

// Evaluates horizontal patterns on the game board for a given player's symbol
// Calculates scores based on the number of consecutive pieces and empty spaces
int countOriz(char board[6][7], char symbol) {
    int score=0, count=0;
    for(int i=0; i<6; i++)
        for(int j=0; j<4; j++) {
            for(int l=0; l<4; l++)
                if(board[i][j+l] == symbol)
                    count++;
                else if(board[i][j+l] != ' ') {
                    count = 0;
                    break;
                }
            if(count == 2)
                score++;
            else if(count == 3)
                score += 10;
            else if(count == 4)
                score+= 1000;
            count = 0;
        }
    return score;
}

// Evaluates vertical patterns on the game board for a given player's symbol
// Calculates scores based on the number of consecutive pieces and empty spaces
int countVert(char board[6][7], char symbol) {
    int score=0, count = 0;
    for(int i=3; i<6; i++)
        for(int j=0; j<7; j++){
            for(int l=0; l<4; l++)
                if(board[i-l][j] == symbol)
                    count++;
                else if(board[i-l][j] != ' ') {
                    count = 0;
                    break;
                }
            if(count == 2)
                score++;
            else if(count == 3)
                score += 10;
            else if(count == 4)
                score+= 1000;
            count = 0;
        }
    return score;
}

// Evaluates diagonal patterns from top-left to bottom-right on the game board for a given player's symbol
// Calculates scores based on the number of consecutive pieces and empty spaces
int countDiagPrim(char board[6][7], char symbol) {
    int score=0, count = 0;
    for(int i=3; i<6; i++)
        for(int j=0; j<4; j++) {
            for(int l=0; l<4; l++)
                if(board[i-l][j+l] == symbol)
                    count++;
                else if(board[i-l][j+l] != ' ') {
                    count = 0;
                    break;
                }
            if(count == 2)
                score++;
            else if(count == 3)
                score += 10;
            else if(count == 4)
                score+= 1000;
            count = 0;
        }
    return score;
}

// Evaluates diagonal patterns from top-right to bottom-left on the game board for a given player's symbol
// Calculates scores based on the number of consecutive pieces and empty spaces
int countDiagSec(char board[6][7], char symbol) {
    int score=0, count = 0;
    for(int i=0; i<3; i++)
        for(int j=0; j<4; j++) {
            for(int l =0; l<4; l++)
                if(board[i+l][j+l] == symbol)
                    count++;
                else if(board[i+l][j+l] != ' ') {
                    count = 0;
                    break;
                }
            if(count == 2)
                score++;
            else if(count == 3)
                score += 10;
            else if(count == 4)
                score+= 1000;
            count = 0;
        }
    return score;
}

// Evaluates board and calculates scores based on the number of consecutive pieces and empty spaces
int count(char board[6][7], int depth) {
    int scoreO=0; // score for player 'O'
    int scoreX=0; // score for player 'X'
    int score;  // final score
    
    // Calculate scores for player 'O'
    scoreO += countOriz(board, 'O');
    scoreO += countVert(board, 'O');
    scoreO += countDiagPrim(board, 'O');
    scoreO += countDiagSec(board, 'O');
    
    // Calculate scores for player 'O'
    scoreX += countOriz(board, 'X');
    scoreX += countVert(board, 'X');
    scoreX += countDiagPrim(board, 'X');
    scoreX += countDiagSec(board, 'X');
    
    if(depth%2)
        score = scoreO - scoreX;
    else
        score = scoreX - scoreO;
    return score;
}

// Handles the player's move by prompting for a valid column and placing their piece 'X'
void playerMove(char board[6][7], int *flag) {
    int i,j;
    
    do{ // prompt the player until a valid move is made
        do{
            printf("Enter the column for your move (1-7): ");
            scanf("%d", &j);
        } while(j<1 && j>7);
        for(i=5; i>=0; i--)
            if(board[i][j-1] == ' ')
                break;
    } while(i== -1);
    
    *flag = 2;  // update the flag to indicate it's now AI turn
    board[i][j-1] = 'X';
}

// checks if the board has any empy spaces available
int checkBoard(char board[6][7]) {
    for(int i =0; i<6; i++)
        for(int j=0; j<7; j++)
            if(board[i][j] == ' ')
                return 1;
    return 0;
}

// finds the index of the maximum value in a given array of size 7
int findMaxIndex(short int v[7]) {
    int index = 0;
    for(int i=1; i<7; i++)
        if(v[index] < v[i])
            index = i;
    return index;
}

// Finds the best move from the given game tree
Move findBestMove(Tree tree) {
    Move bestMove;
    
    // if this is a leaf node, return the best move based on the score
    if(tree->next[0] == NULL) {
        bestMove.column = findMaxIndex(tree->points);
        bestMove.score = tree->points[bestMove.column];
        return bestMove;
    }
    
    // check for any immediate winning move
    for(int i=0; i<7; i++)
        if(tree->points[i] >= 899) {
            bestMove.column = findMaxIndex(tree->points);
            bestMove.score = tree->points[bestMove.column];
            return bestMove;
        }
    
    // Evaluate all possible moves
    Move subMoves[7];
    short int l[7] = {0};
    for(int i=0; i<7; i++) {
        if(tree->points[i] == -25000)
            l[i] = -30000;
        else {
            subMoves[i] = findBestMove(tree->next[i]);
            l[i] = tree->points[i] * 1.2 - subMoves[i].score;
        }
    }
    
    // select the move with the highest adjusted score
    bestMove.column = findMaxIndex(l);
    bestMove.score = subMoves[bestMove.column].score;
    return bestMove;
}

// Attempts to place a piece on the board in the specified column
int placePiece(int column, char board[6][7], int playerTurn) {
    int i=5;    // start at the bottom row
    
    // Find the first empty row
    while(i>=0) {
        if(board[i][column] == ' ')
            break;
        i--;
    }
    
    // If no empty space is found, the column is full
    if(i==-1)
        return -1;
    
    // Place the piece for the current player
    if(playerTurn%2==0)
        board[i][column] = 'X';
    else
        board[i][column] = 'O';
    return 0;
}

// Removes the topmost piece from the specified column on the game board.
void removePiece(int column, char board[6][7]) {
    int i;
    
    // Find the first non-empty row
    for(i=0; i<6; i++)
        if(board[i][column] != ' ')
            break;
    
    // Clear the piece from the found row
    board[i][column] = ' ';
}

// Insert the scores of any possible move in the tree evaluating all the possibilities
void insertValues(Tree t, char board[6][7], int depth) {
    // If this is a leaf node, calculate scores for all possible moves
    if(t->next[0] == NULL) {
        for(int i = 0; i<7; i++) {
            int k = placePiece(i, board,depth);
            if(k!=-1) {
                t->points[i] = count(board, depth);
                removePiece(i, board);
            }
            else
                t->points[i] = -25000;
        }
        return;
    }
    
    // Evaluate all possible moves and recurse for deeper nodes
    for(int i=0; i<7; i++) {
        int a = placePiece(i, board, depth);
        if(a==-1)
            t->points[i] = -25000;
        else{
            if(check(board) == 0)
                insertValues(t->next[i], board, depth-1);
            t->points[i] = count(board, depth);
            removePiece(i, board);
        }
    }
}

// Executes the AI's move by finding the best possible move from the game tree
void MossaAI(char board[6][7], Tree t, int *flag) {
    int i, depth=8;
    insertValues(t, board, depth);
    Move mossa = findBestMove(t);
    
    // Locate the first available row in the selected column for the AI's move
    for(i=5; i>=0; i--)
        if(board[i][mossa.column] == ' ')
            break;
    board[i][mossa.column] = 'O';   // Place the AI's piece ('O') in the determined position
    *flag = 1; // update the flag to indicate the player's turn
}


void game(char board[6][7]) {
    int flag = 2;
    Tree t = createTree(8);
    do {
        if(checkBoard(board) == 0) {
            printf("Draw");
            return;
        }
        if(flag == 1)
            playerMove(board, &flag);
        else
            MossaAI(board, t, &flag);
        printBoard(board);
    } while(check(board) == 0);
    if(check(board) == 1)
        printf("Player wins\n");
    else
        printf("AI wins\n");
}

int main(void){
    char board[6][7];       // Game board (6 rows x 7 columns)
    
    initializeBoard(board); // Set up the board with empty spaces
    printBoard(board);      // Display the initial state of the board
    game(board);            // Start the main game loop
    
    return 0;
}
