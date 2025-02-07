#ifndef COLORED_EDGE_H
#define COLORED_EDGE_H

#include <iostream>

// Represents the color of an edge: BLUE for the first player ('X'), RED for the second ('O').
enum class Color: short { EMPTY, BLUE, RED }; 

// Represents a colored edge in a directed graph.
struct ColoredEdge {
    // Represents a colored edge in a directed graph.
    int vertex_v;  // The starting vertex of the edge.
    int vertex_w;  // The ending vertex of the edge.
    Color color;   // The color of the edge.

    // Constructor
    ColoredEdge(const int v, const int w, const Color color) : vertex_v(v), vertex_w(w), color(color) {}

    // Overloads the stream insertion operator (<<).
    friend std::ostream& operator<<(std::ostream& out, const ColoredEdge &edge);
};

#endif