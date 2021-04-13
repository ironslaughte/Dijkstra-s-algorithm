#include "pch.h"
#include "Func's.h"
#include <fstream>

List* graph = new List[4];
std::fstream stream;

// input file:
// SPb;Msk;5;2
// Msk;Smr;3;4
// SPb;Smr;11;6
// Msk;Ekb;14;7
// Smr;Ekb;8;1


TEST(TestCaseGraph, UnicCities) {
	ASSERT_EQ(4, number_cities(stream));
}


TEST(TestCaseGraph, BuildGraph) {
	read_file(stream, graph,"input.txt");
	// Graph vertices in the first dimension of the list array
	std::string correct_graph1[4] = { "SPb", "Msk", "Smr", "Ekb" }; 
	for (size_t i = 0; i < 4; i++) {
		ASSERT_EQ(correct_graph1[i], graph[i][0].city);
	}
	// Manually checking all adjacent edges of the graph
	// SPb
	ASSERT_EQ(graph[0][1].city, "Msk");
	ASSERT_EQ(graph[0][2].city, "Smr");
	//
	
	// Msk
	ASSERT_EQ(graph[1][1].city, "SPb");
	ASSERT_EQ(graph[1][2].city, "Smr");
	ASSERT_EQ(graph[1][3].city, "Ekb");
	//

	// Smr
	ASSERT_EQ(graph[2][1].city, "Msk");
	ASSERT_EQ(graph[2][2].city, "SPb");
	ASSERT_EQ(graph[2][3].city, "Ekb");
	//

	// Ekb
	ASSERT_EQ(graph[3][1].city, "Msk");
	ASSERT_EQ(graph[3][2].city, "Smr");
	//

}

TEST(TestCaseGraph, ExceptionCase) {
	ASSERT_ANY_THROW(read_file(stream, graph)); // File do not exist 
	ASSERT_ANY_THROW(Dijkstra(graph, "Saratov", "Msk")); // There are no routes from this city at all
}


TEST(TestCaseGraph, DijkstrasAlg) {
	ASSERT_EQ(2, Dijkstra(graph, "Msk", "SPb")); // Msk -> Spb
	ASSERT_EQ(8, Dijkstra(graph, "SPb", "Smr")); // Spb -> Msk -> Smr
	ASSERT_EQ(11, Dijkstra(graph, "Msk", "Ekb")); // Msk -> Smr -> Ekb
	ASSERT_EQ(5, Dijkstra(graph, "Ekb", "Msk")); // Ekb -> Smr -> Msk
	delete[] graph;
}
