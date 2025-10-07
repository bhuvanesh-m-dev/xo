#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Game board (3x3)
char board[3][3];
int scores[3] = {0, 0, 0}; // X wins, O wins, draws

// Function prototypes
void initializeBoard();
void displayBoard();
void displayMenu();
int checkWin();
int checkDraw();
int getPlayerMove(char player);
void getBotMove(int difficulty);
int getEasyBotMove();
int getMediumBotMove();
int getHardBotMove();
int minimax(char board[3][3], int depth, int isMaximizing);
void resetGame();
int isValidMove(int row, int col);

int main() {
    srand(time(NULL)); // Seed random number generator
    
    int gameMode = 0; // 1 = two players, 2 = single player
    int difficulty = 2; // 1 = easy, 2 = medium, 3 = hard
    char currentPlayer = 'X';
    int gameOver = 0;
    
    printf("========================================\n");
    printf("         TIC TAC TOE GAME\n");
    printf("========================================\n\n");
    
    while (1) {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &gameMode);
        
        if (gameMode == 1 || gameMode == 2) {
            break;
        } else {
            printf("\nInvalid choice. Please try again.\n");
        }
    }
    
    if (gameMode == 2) {
        printf("\nSelect bot difficulty:\n");
        printf("1. Easy\n");
        printf("2. Medium\n");
        printf("3. Hard\n");
        printf("Enter your choice: ");
        scanf("%d", &difficulty);
        if (difficulty < 1 || difficulty > 3) {
            difficulty = 2; // Default to medium
        }
    }
    
    initializeBoard();
    
    // Game loop
    while (!gameOver) {
        displayBoard();
        
        printf("\nCurrent scores - X: %d | O: %d | Draws: %d\n", 
               scores[0], scores[1], scores[2]);
        
        printf("\nPlayer %c's turn\n", currentPlayer);
        
        if (gameMode == 1 || (gameMode == 2 && currentPlayer == 'X')) {
            // Human player's turn
            getPlayerMove(currentPlayer);
        } else {
            // Bot's turn
            printf("\nBot is making a move...\n");
            getBotMove(difficulty);
        }
        
        // Check for win
        if (checkWin()) {
            displayBoard();
            printf("\nPlayer %c wins!\n", currentPlayer);
            
            if (currentPlayer == 'X') {
                scores[0]++;
            } else {
                scores[1]++;
            }
            
            gameOver = 1;
        } 
        // Check for draw
        else if (checkDraw()) {
            displayBoard();
            printf("\nIt's a draw!\n");
            scores[2]++;
            gameOver = 1;
        } 
        // Switch player
        else {
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        }
        
        // Ask to play again if game ended
        if (gameOver) {
            char choice;
            printf("\nPlay again? (Y/N): ");
            scanf(" %c", &choice);
            
            if (choice == 'Y' || choice == 'y') {
                resetGame();
                gameOver = 0;
                currentPlayer = 'X';
            } else {
                printf("\nThanks for playing!\n");
                break;
            }
        }
    }
    
    return 0;
}

void initializeBoard() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }
}

void displayBoard() {
    printf("\n");
    printf(" %c | %c | %c \n", board[0][0], board[0][1], board[0][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", board[1][0], board[1][1], board[1][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", board[2][0], board[2][1], board[2][2]);
    printf("\n");
}

void displayMenu() {
    printf("========================================\n");
    printf("           TIC TAC TOE MENU\n");
    printf("========================================\n");
    printf("1. Two Players\n");
    printf("2. Single Player (vs Bot)\n");
    printf("========================================\n");
}

int checkWin() {
    // Check rows
    for (int i = 0; i < 3; i++) {
        if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][0] == board[i][2]) {
            return 1;
        }
    }
    
    // Check columns
    for (int i = 0; i < 3; i++) {
        if (board[0][i] != ' ' && board[0][i] == board[1][i] && board[0][i] == board[2][i]) {
            return 1;
        }
    }
    
    // Check diagonals
    if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[0][0] == board[2][2]) {
        return 1;
    }
    
    if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[0][2] == board[2][0]) {
        return 1;
    }
    
    return 0;
}

int checkDraw() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                return 0;
            }
        }
    }
    return 1;
}

int getPlayerMove(char player) {
    int row, col;
    
    while (1) {
        printf("Enter row (1-3) and column (1-3) separated by space: ");
        scanf("%d %d", &row, &col);
        
        // Adjust for 0-based indexing
        row--;
        col--;
        
        if (isValidMove(row, col)) {
            board[row][col] = player;
            return 1;
        } else {
            printf("Invalid move! Try again.\n");
        }
    }
}

int isValidMove(int row, int col) {
    if (row < 0 || row >= 3 || col < 0 || col >= 3) {
        return 0;
    }
    if (board[row][col] != ' ') {
        return 0;
    }
    return 1;
}

void getBotMove(int difficulty) {
    int row, col;
    
    switch (difficulty) {
        case 1: // Easy - random move
            row = getEasyBotMove();
            break;
        case 2: // Medium - sometimes smart, sometimes random
            if (rand() % 2 == 0) {
                row = getHardBotMove();
            } else {
                row = getEasyBotMove();
            }
            break;
        case 3: // Hard - always smart
            row = getHardBotMove();
            break;
        default:
            row = getEasyBotMove();
    }
    
    // Convert the linear index to row and column
    int r = row / 3;
    int c = row % 3;
    board[r][c] = 'O';
}

int getEasyBotMove() {
    // Find all available moves
    int availableMoves[9];
    int count = 0;
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                availableMoves[count++] = i * 3 + j;
            }
        }
    }
    
    // If no moves available (shouldn't happen), return 0
    if (count == 0) return 0;
    
    // Return a random available move
    return availableMoves[rand() % count];
}

int getHardBotMove() {
    int bestScore = -1000;
    int bestMove = 0;
    
    // Try all possible moves and choose the best one
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            // Check if spot is available
            if (board[i][j] == ' ') {
                board[i][j] = 'O';
                int score = minimax(board, 0, 0); // 0 = false
                board[i][j] = ' ';
                
                if (score > bestScore) {
                    bestScore = score;
                    bestMove = i * 3 + j;
                }
            }
        }
    }
    
    return bestMove;
}

int minimax(char board[3][3], int depth, int isMaximizing) {
    // Check for terminal states
    if (checkWin()) {
        if (isMaximizing) {
            return -10 + depth;
        } else {
            return 10 - depth;
        }
    }
    
    if (checkDraw()) {
        return 0;
    }
    
    if (isMaximizing) {
        int bestScore = -1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'O';
                    int score = minimax(board, depth + 1, 0); // 0 = false
                    board[i][j] = ' ';
                    bestScore = (score > bestScore) ? score : bestScore;
                }
            }
        }
        return bestScore;
    } else {
        int bestScore = 1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'X';
                    int score = minimax(board, depth + 1, 1); // 1 = true
                    board[i][j] = ' ';
                    bestScore = (score < bestScore) ? score : bestScore;
                }
            }
        }
        return bestScore;
    }
}

void resetGame() {
    initializeBoard();
}

// Helper function to check win for minimax
int checkWinForMinimax() {
    // Check rows
    for (int i = 0; i < 3; i++) {
        if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][0] == board[i][2]) {
            return (board[i][0] == 'O') ? 1 : -1;
        }
    }
    
    // Check columns
    for (int i = 0; i < 3; i++) {
        if (board[0][i] != ' ' && board[0][i] == board[1][i] && board[0][i] == board[2][i]) {
            return (board[0][i] == 'O') ? 1 : -1;
        }
    }
    
    // Check diagonals
    if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[0][0] == board[2][2]) {
        return (board[0][0] == 'O') ? 1 : -1;
    }
    
    if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[0][2] == board[2][0]) {
        return (board[0][2] == 'O') ? 1 : -1;
    }
    
    return 0;
}
