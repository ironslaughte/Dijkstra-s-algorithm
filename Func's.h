#pragma once
#include <fstream>
#include "List.h"
#include"Set.h"
#include "Queue.h"

size_t find_top_idx_in_graph(List* graph, size_t idx_start,size_t idx) {
	size_t len = _msize(graph) / sizeof(List);
	for (size_t i = 0; i < len; i++) {
		if (graph[idx_start][idx].city == graph[i][0].city) return i;
	}
}


int Dijkstra(List* graph, std::string start, std::string end) {
	size_t length = _msize(graph) / sizeof(List);

	size_t idx_start = INF, idx_end = INF;
	int* D = new int[length];
	bool* visited = new bool[length];

	// Init an array of distances and an array of visited vertices
	for (size_t i = 0; i < length; i++) {
		D[i] = INF;
		visited[i] = false;
	}

	// Find start_top in graph
	for (size_t i = 0; i < length; i++) {
		if (graph[i][0].city == start) {
			idx_start = i;
		}
		if (graph[i][0].city == end) {
			idx_end = i;
		}
	}
	// if not found city
	if (idx_start == INF) {
		delete[] D;
		delete[] visited;
		throw std::invalid_argument("There is no route from the entered city\n");
	}
	else {
		D[idx_start] = 0;

		// Dijkstra's algorithm
		for (int i = 0; i < length; ++i) {
			int v = -1;
			for (int j = 0; j < length; ++j)
				if (!visited[j] && (v == -1 || D[j] < D[v]))
					v = j;
			if (D[v] == INF)
				break;
			visited[v] = true;

			for (size_t j = 0; j < graph[v].GetSize(); ++j) {
				int to = find_top_idx_in_graph(graph, v, j);
				int price = graph[v][j].price;
				if (D[v] +  price < D[to]) {
					D[to] = D[v] + price;					
				}
			}
		}		

		int price = D[idx_end];
		delete[] D;
		delete[] visited;
		if (price == INF) {
			// std::cout << "It is not possible to get to the city you selected. Price: ";
			price = -1;
			
		}
		else {
			// std::cout << "The cheapest flight will cost: ";
		}
		return price;
	}	
}

void Print_graph(List* graph) {
	// The output is implemented using a depth-first crawl
	Queue queue;
	List visited_tops;
	size_t len = _msize(graph) / sizeof(List);
	//Elem* cur_top = head;
	for (size_t i = 0; i < len; i++) {
		if (!queue.contains(graph[i][0])) {
			queue.push_back(graph[i][0]);
		}
		for (size_t j = 1; j < graph[i].GetSize(); j++) {
			if (!queue.contains(graph[i][j]) && !visited_tops.Contains(graph[i][j])) {
				queue.push_back(graph[i][j]);
			}
		}
		Top top = queue.Dequeue();
		if (!visited_tops.Contains(top.city)) {
			visited_tops.Push_back(top);
		}
	}

	while (queue.getSize() > 0) {
		Top top = queue.Dequeue();
		if (!visited_tops.Contains(top)) {
			visited_tops.Push_back(top);
		}
	}
	for (size_t i = 0; i < visited_tops.GetSize(); i++) {
		std::cout << visited_tops[i].city << " ";
	}
	std::cout << std::endl << std::endl;
	visited_tops.Clear();
	queue.clear();
}


// Time O(n)
int find_in_graph(List* list, std::string city) {
	size_t len = _msize(list) / sizeof(List);
	for (size_t i = 0; i < len; i++) {
		if (list[i][0].city == city) return i;
	}
	return -1;
}


// Time O(n)
// Counting the number of unique cities
size_t number_cities(std::fstream& stream) {
	stream.open("input.txt", std::ios::in);	
	stream >> std::noskipws;
	Set set_cities;
	while (!stream.eof()) {
		size_t count = 0;
		char s = ' ';
		std::string str = "";
		while (count < 2) {
			stream >> s;
			if (s == ';') {
				count++;
				set_cities.Insert(str);
				str = "";
			}
			else {
				str += s;
			}
		}
		while (s != '\n' && !stream.eof()) {
			stream >> s;
		}
	}
	stream.close();
	return set_cities.GetSize();
}

// Time: mnogo
bool read_file(std::fstream& stream, List* city_graph,std::string file_name = "notEx.txt") {
	stream.open(file_name, std::ios::in);
	if (!stream.good()) {
		throw std::invalid_argument("File do not exist\n");
	}
	stream >> std::noskipws;
	int price = 0;
	size_t i = 0;
	while (!stream.eof()) {
		char s = ' ';
		std::string str = ""; 
		// Read str
		while (s != '\n' && !stream.eof()) {
			stream >> s;
			if(s != '\n' && !stream.eof()) str += s;
		}

		// Parse first city
		size_t idx_semicolon = str.find(';', 0);
		std::string city_1 = "";
		for (size_t i = 0; i < idx_semicolon; i++) {
			city_1 += str[i];
		}

		// Parse second city
		size_t old_idx = idx_semicolon + 1;
		idx_semicolon = str.find(';', old_idx);
		std::string city_2 = "";
		for (size_t i = old_idx; i < idx_semicolon; i++) {
			city_2 += str[i];
		}

		// Parse first price 
		int price_1 = 0;
	    old_idx = idx_semicolon + 1;
		idx_semicolon = str.find(';', old_idx);
		if (str[old_idx] != 'N') {	// if N/A
			for (size_t i = old_idx, rate = 1; i < idx_semicolon; i++,rate *= 10) {
				price_1 *= rate;
				price_1 += (str[i] - '0');
			}
		}
		else {
			price_1 = INF;
		}

		// Parse second price 
		int price_2 = 0;
		old_idx = idx_semicolon + 1;
		if (str[old_idx] != 'N') {	// If N/A
			for (size_t i = old_idx, rate = 1; i < str.length(); i++, rate += 10) {
				price_2 *= rate;
				price_2 += (str[i] - '0');			
			}
		}
		else {
			price_2 = INF;
		}


		// Build graph
		int idx = find_in_graph(city_graph, city_1);
		if (idx == -1) {
			city_graph[i].Push_back(Top(city_1));
			city_graph[i++].Push_back(Top(city_2, price_1));
		}
		else {
			city_graph[idx].Push_back(Top(city_2,price_1));
		}

		idx = find_in_graph(city_graph, city_2);
		if (idx == -1) {
			city_graph[i].Push_back(Top(city_2));
			city_graph[i++].Push_back(Top(city_1, price_2));
		}
		else {
			city_graph[idx].Push_back(Top(city_1, price_2));
		}
	}

	// If file is empty
	if ((_msize(city_graph) / sizeof(List)) == 0) {
		return false;
	}
	else {
		return true;
	}
}