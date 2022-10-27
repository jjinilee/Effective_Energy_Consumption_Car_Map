#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "graph.h"


// Construct a Road using the city index information
struct Road roadConstructor(int Source, int End, int Energy)
{
	struct Road* newRoad;

	// allocates enough memory for newRoad
	newRoad = malloc(sizeof(struct Road));

	newRoad -> Source = Source;
	newRoad -> destination = End;
	newRoad -> energyUsed = Energy;

	return *newRoad;
};


// Construct a graph with roads and cities
struct Graph* graphConstructor(struct List* list, struct CityList* cities)
{
    // Reserve memory for the graph structure.
	struct Graph* thegraph = malloc(sizeof(struct Graph));

	// Save the number of cities and road to the graph
	thegraph -> NumberofCities = cities -> size;
	thegraph -> NumberofRoads = list -> size;

	// Allocate the memory to store the number of roads
	thegraph -> road = malloc(thegraph -> NumberofRoads * sizeof(struct Road));

	// This index variable keeps track of the index so that we can report it.
	int index = 0;

	struct ListNode* currentNode;

	// Construct a road for each line with given source, destination and energy
	// When currentNode points the head of the list,
	// index is initialized to 0,
	// the current node get the address of next struct in the list
	for (currentNode = list->head, index = 0; currentNode != NULL; currentNode = currentNode->next, index++)
	{
		(thegraph -> road[index] = roadConstructor(citySearch(cities, currentNode -> Source), citySearch(cities, currentNode -> destination), currentNode -> Energy));
	}

	return thegraph;
};

// The function that finds the shortest path from the source to destination cities
// using Bellman-Ford algorithm, and leads to least energy loss
void BellmanFordGraph(FILE* fp_out, struct Graph* thegraph, struct CityList* cities, char* SourceCity, char* DestCity)
{
	// Assign values for integers
	int NumberofCities = thegraph -> NumberofCities;
	int NumberofRoads = thegraph -> NumberofRoads;
	int Source = citySearch(cities, SourceCity);
	int destination = citySearch(cities, DestCity);

	// Keeps the track of the energy loss and passed cities so that we can report it.

	// A large (4(size of int)*Number of cities) memory is dynamically allocated to energy
	// By allocating data of int size as many as NumberofCities,
	// the starting address (address is int* type) is returned and allocated to the energyloss variable.
	int *energy = (int*)malloc(sizeof(int)*NumberofCities);

	// A large (citylist*Number of cities) memory is dynamically allocated to passedCities
	// Allocates the (struct CityList*) type as many as NumberofCities, returns the starting address
	//(second pointer(struct CityList**) is used to store the address of (struct CityList*)) and assign it to the passedCities
	struct CityList** passedCities = (struct CityList**)malloc(sizeof(struct CityList*)*NumberofCities);

	// initialise distances from source to other nodes as infinite
	for (int i = 0; i < NumberofCities; i++)
	{
		energy[i] = INT_MAX;
		passedCities[i] = cityListConstructor();

	}

	// Initialise source to zero
	energy[Source] = 0;

	// Find the shortest distance between source and destination while updating the information of the trunk lines as many as numberofcities-1.
	for (int i = 1; i < NumberofCities; i++)
	{
		for (int j = 0; j < NumberofRoads; j++)
		{
            // Bring source city to the city index j
			int s = thegraph -> road[j].Source;
			// Bring the destination to the city at index j
			int d = thegraph -> road[j].destination;
			int energyUsed = thegraph -> road[j].energyUsed;

			// If the road with minimal energy consumption is found, replace it with the current road
			// and that route will be added to the passed city list and will never be able to pass again.
			if (energy[s] != INT_MAX && energy[d] > energy[s] + energyUsed)
			{
				// Skip if the source node exists in the passed city list where d is the destination
				// You can never pass by the same city twice once you've already done it
				if (citySearch(passedCities[d], cityNameSearch(cities, s)) != -1) {
					continue;
				}

				// Skip if destination node exists in the passed city list where s is the destination
				// You can never pass by the same city twice once you've already done it
				// This is basically the a road that has been passed in the other direction
				if (citySearch(passedCities[s], cityNameSearch(cities, d)) != -1) {
					continue;
				}

				// Update the route from the source to the current node
				passedCities[d] = CopyCityList(passedCities[d], passedCities[s]);


				// Add city 's' to the route 'passedcities[d]'

				AddCity(passedCities[d], cityNameSearch(cities, s));

				// Update the energy consumption while travelling from source to destination
				energy[d] = energy[s] + energyUsed;
			}
		}
	}

	// Prints out the results
	printf("------------------------\n");
	// This fprintf function prints out the results to the Output text file
	fprintf(fp_out, "------------------------\n");

    // Print the name of source city and destination city
	printf("Source:\t%s\nDestination:\t%s\n", cityNameSearch(cities, Source), cityNameSearch(cities, destination));
	fprintf(fp_out, "Source:\t%s\nDestination:\t%s\n", cityNameSearch(cities, Source), cityNameSearch(cities, destination));

    // Print the contents of the list
	DisplayCityList(fp_out, passedCities[destination], cityNameSearch(cities, destination));

    // Print to show the number of cities that we passed by
	printf("we have gone through %d cities this time\n", passedCities[destination]->size - 1);
	fprintf(fp_out, "we have gone through %d cities this time\n", passedCities[destination]->size - 1);

    // Print the overall energy spent traveling between source and destination
	printf("The overall energy spent : %d\n", energy[destination]);
	fprintf(fp_out, "The overall energy spent : %d\n", energy[destination]);

	printf("------------------------\n");
	fprintf(fp_out, "------------------------\n");

}

