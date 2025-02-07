#ifndef GRAPH_H
#define GRAPH_H

#include "colored_edge.h"

#include <vector>
#include <list>

// Represents a graph with colored edges, implemented using adjacency lists.
class Graph {
public:
    // Constructs a Graph object with the specified number of vertices.
    Graph(const int n_vertices) : n_vertices(n_vertices), n_edges(0), adjacency_lists(n_vertices), marked(n_vertices, false) {}

    // Copy constructor. Creates a deep copy of the graph.
    Graph(const Graph& other);

    // Copy assignment operator. Performs a deep copy of the other graph.
    Graph& operator=(const Graph& other);

    // Returns the number of vertices in the graph.
    int V() const { return n_vertices; }
    
    // Returns the number of edges in the graph.
    int E() const { return n_edges; }

    // Returns a list of edges adjacent to the given vertex.
    std::list<ColoredEdge> adjacents(int vertex) const { return adjacency_lists[vertex]; }

    // Adds a colored edge to the graph.  Assumes an undirected graph; 
    // adds edges in both directions.
    void add_edge(const int vertex_v, const int vertex_w, const Color color);

    // Checks if there exists a path from 'source' to 'vertex' using only
    // edges of the specified 'color'.
    bool has_path_to(const int source, const int vertex, const Color color);

private:
    int n_vertices;             // The number of vertices in the graph.
    int n_edges;                // The number of edges in the graph.
    std::vector<std::list<ColoredEdge>> adjacency_lists; // Adjacency lists for each vertex.
    std::vector<bool> marked;   // Used for graph traversal algorithms (DFS).

    // Performs a Depth-First Search (DFS) starting from 'source' and
    // considering only edges of the specified 'color'.
    void dfs(int const source, Color const color);
};

#endif