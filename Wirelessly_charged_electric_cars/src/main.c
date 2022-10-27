#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "graph.h"

// import the text files using pointers
char* EnergyFilename = "energy.txt";
char* CitypairsFilename = "citypairs.txt";
char* OutputFilename = "output.txt";

int main(void)
{
    //Limit the strings to be 31 unit long to save memory
    //Name of the file we import, name of starting and destination city
	char NameofFile[31];
	char SourceCity[31];
	char DestCity[31];

	// Construct List and Citylist
	struct CityList* cities = cityListConstructor();
	struct List* list = listConstructor();

	// Read the data from the energy file
	LoadMapData(list, EnergyFilename, cities);

	// Construct a graph with roads and cities
	struct Graph* thegraph = graphConstructor(list, cities);

    //Declare a pointer of type file
    // r : open for reading
    // w : open for writing
	FILE* fp_in = fopen(CitypairsFilename, "r");
	FILE* fp_out = fopen(OutputFilename, "w");

    //if we cannot find citypairs file
	if (fp_in == NULL)
	{
		printf("Oh no! Sadly you've missed out 'cityPairs.txt' file! Please Check it again :)");
		exit(1);
		//return;
	}
	else
	{
		printf("Hello! I'm gonna give you the best path to spend the least energy consumption traveling between two cities!\n");

		//Writing to the Output text file.
		fprintf(fp_out, "Hello! I'm gonna give you the best path to spend the least energy consumption traveling between two cities!\n");

        // Read each line of citypairs file till the end
		while (fgets(NameofFile, sizeof(NameofFile), fp_in) != NULL)
		{
			sscanf(NameofFile, "%s\t%s\t", SourceCity, DestCity);
			BellmanFordGraph(fp_out, thegraph, cities, SourceCity, DestCity);
		}

		//Closing a file
		//fp_in is a file pointer associated with the file to be closed
		fclose(fp_in);
	}

	return 0;
}
