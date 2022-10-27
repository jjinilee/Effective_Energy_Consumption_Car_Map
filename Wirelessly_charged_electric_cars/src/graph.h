#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
#include "list.h"


// Structure to represent the road in the graph
struct Road
{
	int Source;
	int destination;
	int energyUsed;
};


// Structure to represent a weighted graph
struct Graph
{
	int NumberofCities;
	int NumberofRoads;

	// Graph is represented as an array of roads
	struct Road* road;
};


// Construct a Road using the city index information
struct Road roadConstructor(int Source, int End, int Energy);


// Construct a graph with roads and cities
struct Graph* graphConstructor(struct List* list, struct CityList* cities);


// The function that finds the shortest path from the source to destination cities
// using Bellman-Ford algorithm, and leads to least energy loss
void BellmanFordGraph(FILE* fp_out, struct Graph* thegraph, struct CityList* cities, char* SourceCity, char* DestCity);


#endif // GRAPH_H_INCLUDED
