#ifndef HEXBOARD_H
#define HEXBOARD_H

#include "graph.h"

#include <utility>
#include <vector>

// This class represents a Hex game board
class HexBoard {
public:
    // Constructs a HexBoard object with the specified size.
    // Initializes the graph with additional vertices for virtual walls.
    HexBoard(const int size) : size(size), graph(size * size + 4), red_moves(0), blue_moves(0),
                               board(size, std::vector<Color>(size, Color::EMPTY)) {initialize();}

    // Copy constructor. Creates a deep copy of the HexBoard.
    HexBoard(const HexBoard& other);

    // Copy assignment operator. Performs a deep copy of the other HexBoard.
    HexBoard& operator=(const HexBoard& other);

    // Returns true if the Red player has won the game.
    bool red_wins();

    // Returns true if the Blue player has won the game.
    bool blue_wins();

    // Enters a move for the specified player at the given coordinates.
    void enter_move(const int i, const int j, const Color color);

    // Gets a move for the computer player.
    void get_pc_move(const Color color_pc);

    // Prints the Hex board to the console using ASCII characters.
    void print_board();

    // Checks if the cell at the given coordinates is empty.
    bool is_empty(const int i, const int j) const { return board[i][j] == Color::EMPTY; }

private:
    int size;               // The size of the Hex board.
    int left_blue_wall;     // Index of the left blue virtual wall vertex in the graph.
    int right_blue_wall;    // Index of the right blue virtual wall vertex in the graph.
    int bottom_red_wall;    // Index of the bottom red virtual wall vertex in the graph.
    int top_red_wall;       // Index of the top red virtual wall vertex in the graph.
    int red_moves;          // The number of moves made by the Red player.
    int blue_moves;         // The number of moves made by the Blue player.
    Graph graph;            // The graph representing the Hex board connections.
    std::vector<std::vector<Color>> board; // 2D vector representing the board state.

    // Initializes the graph with edges representing the Hex board connections.
    void initialize();

    // Converts board coordinates (i, j) to a graph vertex index.
    int get_index(const int i, const int j) const;

    // Converts a graph vertex index to board coordinates (i, j).
    std::pair<int, int> get_coordinates(const int index) const;

    // Prints spaces for formatting the Hex board output.
    void print_spaces(const int k);

    // Prints a separator line for formatting the Hex board output.
    void print_separator(const int k);

    // Performs one Monte Carlo simulation to evaluate a move.
    void monte_carlo_sim(const Color player_color, std::vector<int>& possible_moves,
        std::vector<std::vector<int>>& wins, std::vector<std::vector<int>>& trials);
};

#endif