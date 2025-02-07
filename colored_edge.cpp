#include "colored_edge.h"

// Overloads the stream insertion operator (<<) to enable printing of 
// ColoredEdge objects to output streams.
std::ostream& operator<<(std::ostream& out, const ColoredEdge &edge) {
    out << edge.vertex_v << " - " << edge.vertex_w << ", color = " << static_cast<int>(edge.color);
    return out;
}