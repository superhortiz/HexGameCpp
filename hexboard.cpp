#include "hexboard.h"

#include <algorithm> // For std::shuffle, std::fill
#include <iomanip>
#include <ostream>
#include <random>  // For random number generation

// Define number of iterations
const int N_ITERATIONS = 10000;

// Seed for the random number engine
static std::random_device rd;
static std::default_random_engine eng(rd());

// Copy constructor. Creates a deep copy of the HexBoard.
HexBoard::HexBoard(const HexBoard& other) : size(other.size), left_blue_wall(other.left_blue_wall), right_blue_wall(other.right_blue_wall), 
        bottom_red_wall(other.bottom_red_wall), top_red_wall(other.top_red_wall), 
        red_moves(other.red_moves), blue_moves(other.blue_moves), graph(other.graph), 
        board(other.board) {}

// Copy assignment operator. Performs a deep copy of the other HexBoard.
HexBoard& HexBoard::operator=(const HexBoard& other) {
    if (this == &other) return *this;
    size = other.size;
    left_blue_wall = other.left_blue_wall;
    right_blue_wall = other.right_blue_wall;
    bottom_red_wall = other.bottom_red_wall;
    top_red_wall = other.top_red_wall;
    red_moves = other.red_moves;
    blue_moves = other.blue_moves;
    graph = other.graph;
    board = other.board;
    return *this;
}

// Initialize graph by connecting walls with vertices
void HexBoard::initialize(void) {
    // Define virtual vertices for walls
    left_blue_wall = size * size;
    right_blue_wall = size * size + 1;
    bottom_red_wall = size * size + 2;
    top_red_wall = size * size + 3;

    // Connect blue walls
    for (int i = 0; i < size; ++i) {
        graph.add_edge(get_index(i, 0), left_blue_wall, Color::BLUE);
        graph.add_edge(get_index(i, size - 1), right_blue_wall, Color::BLUE);
    }

    // Connect red walls
    for (int j = 0; j < size; ++j) {
        graph.add_edge(get_index(0, j), top_red_wall, Color::RED);
        graph.add_edge(get_index(size - 1, j), bottom_red_wall, Color::RED);
    }
}

// Returns true if the Red player has won the game.
bool HexBoard::red_wins() {
    if (red_moves < size) return false;
    else return graph.has_path_to(bottom_red_wall, top_red_wall, Color::RED);
}

// Returns true if the Blue player has won the game.
bool HexBoard::blue_wins() {
    if (blue_moves < size) return false;
    else return graph.has_path_to(left_blue_wall, right_blue_wall, Color::BLUE);
}

// Converts board coordinates (i, j) to a graph vertex index.
int HexBoard::get_index(const int i, const int j) const {
    return (i * size + j);
}

// Converts a graph vertex index to board coordinates (i, j).
std::pair<int, int> HexBoard::get_coordinates(const int index) const {
    int row = index / size;
    int col = index % size;
    return std::pair<int, int> {row, col};
}

// Prints spaces for formatting the Hex board output.
void HexBoard::print_spaces(const int k) {
    for (int i = 0; i < k; ++i)
        std::cout << ' ';
}

// Prints a separator line for formatting the Hex board output.
void HexBoard::print_separator(const int k) {
    std::cout << "\\";
    for (int i = 0; i < k; ++i)
        std::cout << " / \\";
}

// Prints the Hex board to the console using ASCII characters.
void HexBoard::print_board(void) {
    std::cout << "HEX BOARD:" << "\n ";
    for (int i = 0; i < size; ++i) std::cout << std::setw(2) << i << "  ";
    std::cout << std::endl;
    for (int i = 0; i < size; ++i) {
        print_spaces(2 * i);
        std::cout << std::setw(2) << i << " ";
        for (int j = 0; j < size; ++j) {
            if (board[i][j] == Color::BLUE)
                std::cout << 'X';
            else if (board[i][j] == Color::RED)
                std::cout << 'O';
            else
                std::cout << '.';
            if (j < size - 1)
                std::cout << " - ";
        }
        std::cout << std::endl;
        if (i < size - 1) {
            print_spaces(2 * i + 4);
            print_separator(size - 1);
            std::cout << std::endl;
        }
    }
}

// Enters a move for the specified player at the given coordinates.
void HexBoard::enter_move(const int i, const int j, const Color color) {
    if (0 <= i && i < size && 0 <= j && j < size && is_empty(i, j)) {
        board[i][j] = color;
        if (color == Color::BLUE) blue_moves++;
        else red_moves++;

        std::vector<std::pair<int, int>> neighbors = {
            {0, -1},  // Left
            {0, 1},   // Right
            {1, -1}, // Bottom-left
            {1, 0},  // Bottom-right
            {-1, 0},   // Top-left
            {-1, 1}    // Top-right
        };

        for (const auto& [dx, dy] : neighbors) {
            int x = i + dx, y = j + dy;
            if (0 <= x && x < size && 0 <= y && y < size && board[x][y] == color)
                graph.add_edge(get_index(i, j), get_index(x, y), color);
        }
    }
}

// Gets a move for the computer player using Monte Carlo simulation.
void HexBoard::get_pc_move(const Color color_pc) {
    // Initialize vectors. Declare them static, to reuse their resources.
    static std::vector<int> possible_moves;
    static std::vector<std::vector<int>> wins(size, std::vector<int>(size));
    static std::vector<std::vector<int>> trials(size, std::vector<int>(size));

    // Create a temporal board to generate simulations. Declare it static, to reuse its resources.
    static HexBoard temp_board(size);

    // Clear vectors to ensure results from previous calls don't affect 
    // the current move calculation.
    possible_moves.clear();
    for (auto& row : wins)
        std::fill(row.begin(), row.end(), 0);

    for (auto& row : trials)
        std::fill(row.begin(), row.end(), 0);

    // Get all the empty positions in the current board
    for (int index = 0; index < size * size; ++index) {
        std::pair coord = get_coordinates(index);
        if (board[coord.first][coord.second] == Color::EMPTY)
            possible_moves.push_back(index);
    }

    // Generate Monte Carlo simulations to evaluate potential moves.
    for (int i = 0; i < N_ITERATIONS; ++i) {
        temp_board = *this;
        temp_board.monte_carlo_sim(color_pc, possible_moves, wins, trials);
    }

    // Iterate through all cells and calculate the win rate (wins[i][j] / trials[i][j])
    // for each cell. Select the cell with the highest win rate.
    float win_rate, max_rate = -1.0;
    int row = -1, col = -1;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (trials[i][j] != 0) {
                win_rate = static_cast<float>(wins[i][j]) / trials[i][j];
                if (win_rate > max_rate) {
                    max_rate = win_rate;
                    row = i;
                    col = j;
                }
            }
        }
    }
    
    // Execute the chosen move.
    enter_move(row, col, color_pc);
    std::cout << "PC moves: row = " << row << ", col = " << col << std::endl;
}


// Performs one Monte Carlo simulation to evaluate a move.
void HexBoard::monte_carlo_sim(const Color color_pc, std::vector<int>& possible_moves,
                               std::vector<std::vector<int>>& wins, std::vector<std::vector<int>>& trials) {
    
    // Shuffle the possible moves to randomize the order in which moves are tried.
    std::shuffle(possible_moves.begin(), possible_moves.end(), eng);

    // Calculate the number of moves the PC will make in this simulation.
    int n_next_moves = (possible_moves.size() + 1) / 2;

    // Incorporate in the graph the pc moves simulated.
    for (int i = 0; i < n_next_moves; ++i) {
        int index = possible_moves[i];
        std::pair coord = get_coordinates(index);
        enter_move(coord.first, coord.second, color_pc);  // Simulate the move
        ++trials[coord.first][coord.second];  // Increment the trial count for this cell
    }

    // Determine if the PC won the simulated game.
    bool pc_wins = (color_pc == Color::BLUE)? blue_wins() : red_wins();

    // If the PC won the simulation, increment the win count for each cell
    // where the PC made a move.
    if (pc_wins)
        for (int i = 0; i < n_next_moves; ++i) {
            int index = possible_moves[i];
            std::pair coord = get_coordinates(index);
            ++wins[coord.first][coord.second];  // Increment the win count
        }
}