#include "hexboard.h"
#include <iostream>

// Function to perform the game loop
void game_loop(HexBoard& board, const int size, const Color color_player, const Color color_pc) {
    while (!board.blue_wins() && !board.red_wins()) {
        std::cout << std::endl;
        board.print_board();

        // Ask the player for a move
        int i, j;
        std::cout << "Enter your move (row, col): ";
        std::cin >> i >> j;

        // Check if the player's move is valid
        while (i < 0 || i >= size || j < 0 || j >= size || !board.is_empty(i, j)) {
            std::cout << "Invalid move! Please enter again: ";
            std::cin >> i >> j;
        }
        board.enter_move(i, j, color_player);

        // Check if someone has won
        if (board.blue_wins() || board.red_wins()) break;

        // Computer's move
        board.get_pc_move(color_pc);
    }
}

int main() {
    // Ask the user for the board size, I consider size >= 2
    int size = 0;
    while (size < 2) {
        std::cout << "Define the size of the board (size >= 2): ";
        std::cin >> size;
        std::cout << std::endl;
    }
    HexBoard board(size);

    // Ask the user to select a color to play
    char color;
    Color color_player = Color::BLUE, color_pc = Color::RED;
    std::cout << "Select your color ('b' for blue, 'r' for red, blue is the default): ";
    std::cin >> color;
    std::cout << std::endl;

    if (color == 'r') {
        color_player = Color::RED;
        color_pc = Color::BLUE;
        std::cout << "PC starts..." << std::endl;
        std::cout << "Try to connect horizontal walls with a vertical path." << std::endl;
        board.get_pc_move(color_pc);
    } else { 
        std::cout << "Try to connect vertical walls with a horizontal path." << std::endl;
    }

    // Game loop
    game_loop(board, size, color_player, color_pc);

    // Print final board
    board.print_board();

    // Print the winner
    if (board.blue_wins()) {
        std::cout << "Blue wins!" << std::endl;
    }
    else {
        std::cout << "Red wins!" << std::endl;
    }
}