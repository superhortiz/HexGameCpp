hexgame: main.o colored_edge.o graph.o hexboard.o
	g++ main.o colored_edge.o graph.o hexboard.o -o hexgame

main.o: main.cpp hexboard.h graph.h colored_edge.h
	g++ -c main.cpp

colored_edge.o: colored_edge.cpp colored_edge.h
	g++ -c colored_edge.cpp

graph.o: graph.cpp graph.h colored_edge.h
	g++ -c graph.cpp

hexboard.o: hexboard.cpp hexboard.h graph.h colored_edge.h
	g++ -c hexboard.cpp

clean:
	rm -f hexgame main.o colored_edge.o graph.o hexboard.o