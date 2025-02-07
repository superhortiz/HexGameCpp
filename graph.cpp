#include "graph.h"

// Copy constructor
Graph::Graph(const Graph& other) : Graph(other.n_vertices) {
    adjacency_lists = other.adjacency_lists;
    n_edges = other.n_edges;
}

// Copy assignment operator
Graph& Graph::operator=(const Graph& other) {
    if (this == &other) return *this;
    n_edges = other.n_edges;
    n_vertices = other.n_vertices;
    adjacency_lists = other.adjacency_lists;
    marked = other.marked;
    return *this;
}

// Adds a colored edge to the graph.  Assumes an undirected graph; 
// adds edges in both directions.
void Graph::add_edge(const int vertex_v, const int vertex_w, const Color color) {
    // Create a new edge and add to the adjacency list
    ColoredEdge new_edge = ColoredEdge(vertex_v, vertex_w, color);
    adjacency_lists[vertex_v].push_back(new_edge);

    // To make the graph undirected
    new_edge = ColoredEdge(vertex_w, vertex_v, color);
    adjacency_lists[vertex_w].push_back(new_edge);

    // Update the number of edges
    n_edges++;
}

// Checks if there exists a path from 'source' to 'vertex' using only
// edges of the specified 'color'.
bool Graph::has_path_to(const int source, const int vertex, const Color color) {
    marked = std::vector(n_vertices, false);
    dfs(source, color);
    return marked[vertex];
}

// Performs a Depth-First Search (DFS) starting from 'source' and
// considering only edges of the specified 'color'.
void Graph::dfs(const int source, const Color color) {
    marked[source] = true;
    for (auto const& edge : adjacency_lists[source]) {
        if (edge.color == color && !marked[edge.vertex_w])
            dfs(edge.vertex_w, color);
    }
}