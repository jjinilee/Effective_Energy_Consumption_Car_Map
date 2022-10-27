#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"


// Construct energy file's data node
// Each line becomes one node
struct ListNode* listNodeConstructor(char* Source, char* destination, int Energy)
{
    // The value to return. This will be the address of a ListNode structure.
	struct ListNode* newData;

	// Reserve memory for the node structure.
	newData = malloc(sizeof(struct ListNode));

	// Allocate enough memory to store a string
	newData->Source = malloc(strlen(Source) * sizeof(char));
	newData->destination = malloc(strlen(destination) * sizeof(char));

	// String is copied from source and destination inputs to new pointers.
	strcpy(newData->Source, Source);
	strcpy(newData->destination, destination);

	//Energy input, which is the energy consumed between two nodes
	newData->Energy = Energy;

	// Initialize previous and next pointers to NULL
	newData->next = NULL;
	newData->prev = NULL;

	// Generated node return
	return newData;
}


// Construct and initialize memory to manage data nodes in energy file
struct List* listConstructor()
{
	struct List* newList;

	// Allocate enough memory to store List structure
	newList = malloc(sizeof(struct List));

	//Initialize the List data
	newList->size = 0;
	newList->head = NULL;
	newList->tail = NULL;

	// Return the address of generated list
	return newList;
}


// Adding another node to another list
// Construct a data node and add it to the end of the List
// Returns 1 if successfully added
int AddList(struct List* list, char* Source, char* destination, int Energy)
{
	// Creates a newData with value of source, destination and energy from inputs
	struct ListNode* newData;
	newData = listNodeConstructor(Source, destination, Energy);

	// if the list is empty,
	// then the new Data node will be the only node and it becomes the head of the list
	if (list->head == NULL)
	{
		list->head = newData;
	}

	// if the list is not empty,
	// then the previous tail's next pointer will point to the new data node
	if (list->tail != NULL)
	{
		list->tail->next = newData;

		// Brings the new data node's 'previous' pointer to the previous tail of the list
        newData->prev = list->tail;
	}

	// The new data node added will become the new tail of the list
	list->tail = newData;

	// Add one to the list size
	list->size++;

    //Return 1 when the data is added (true)
    return 1;
}


// Construct City node for CityList
struct City* cityConstructor(char* Cityname)
{
	struct City* Node;

	// Allocate enough memory to store city
	Node = malloc(sizeof(struct City));

	// Allocate enough memory to store the Cityname of city string
	Node -> NameofCity = malloc(strlen(Cityname) * sizeof(char));

	// String is copied from 'Cityname' input to 'Node -> NameofCity'
	strcpy(Node -> NameofCity, Cityname);

	//next and prev initialized to Null
	Node->next = NULL;
	Node->prev = NULL;

	return Node;
}


// Construct City List
struct CityList* cityListConstructor()
{
    //Returns a pointer to CityList structure
	struct CityList* newList;

	//Reserve memory for the List structure
	newList = malloc(sizeof(struct List));

	// newList is initialized as empty
	newList->size = 0;
	newList->head = NULL;
	newList->tail = NULL;

	return newList;
}


//Release the memory allocated for list
void cityListDestructor(struct CityList* list)
{
	struct City *theCity;

    // While the list is not empty,
    // repeat this while loop until the head becomes null
	while (list->head != NULL)
	{
	    // Make theCity points the head of the list
		theCity = list -> head;
		// Make head pointer points the next one
		list -> head = list -> head -> next;
		// Free the memory allocated for theCity, which is the old head
		free(theCity);
		// Decreases size of list by 1
		list->size--;
	}
	//When all the cities are removed, we can free the memory for the list
	free(list);
}


// Construct a city node and add it to the end of the Citylist
// Return 0 if the name of the city is already in the list
// This is similar to AddList
int AddCity(struct CityList* list, char* Cityname)
{

	struct City* Node;

	// If the name of the city doesn't exist in the list
	if (citySearch(list, Cityname) == -1)
	{
		// Construct new node with given city name
		Node = cityConstructor(Cityname);

        // If the list is empty,
        // then the 'Node' will be the only node, and it becomes the head of the list
		if (list->head == NULL)
		{
			list->head = Node;
		}

		// If the list is not empty,
        // then the previous tail's next pointer will point to the node
		if (list->tail != NULL)
		{
			list->tail->next = Node;
            // Bring the node's 'previous' pointer to the previous tail of the list
			Node->prev = list->tail;
		}

		// The new data node added will become the new tail of the list
		list->tail = Node;

		//Add one to the list size
		list->size++;
	}
	// If it already exists in the list
	else
    {
        // Return False
        return 0;

    }
    // Return true
    return 1;
}


// Returns the first index of a city whose name is equal to the requested entity.
int citySearch(struct CityList* list, char* entity)
{
    // This is used to traverse the list
	struct City* Node = list->head;

    // Initialise the index to 0
	int index = 0;

	// While the list is not empty
	while (Node != NULL)
	{
		// If the entity and Nameofcity is same
		if (strcmp(entity, Node->NameofCity) == 0)
		{
            // Returns the index at which the city was found
			return index;
		}

        // Get the address of the next struct in the list
		Node = Node->next;
		index++;
	}
	// If the city name is not found, return -1.
	return -1;
}


// Search for the name of the city using it's index value
char* cityNameSearch(struct CityList* list, int index)
{
	struct City* Node;
	// Make node points the head of the list
	Node = list->head;

    // When node gets to the name of the city
	for (int i = 0; i < index; i++)
	{
	    // Get the address of the next struct in the list
		Node = Node->next;
	}
	// Return the name of the city
	return Node->NameofCity;
}


// Copy the list 2 to list 1
struct CityList* CopyCityList(struct CityList* list1, struct CityList* list2)
{
	struct City * iter;

	// Frees the existing list1 memory
	cityListDestructor(list1);
	// Construct another cityList
	struct CityList* anotherList = cityListConstructor();

	// Copy the data of list2 into anotherlist
	for (iter = list2->head; iter != NULL; iter = iter->next)
	{
	    // Construct a city node
		AddCity(anotherList, iter->NameofCity);
	}
    // Return the another list
	return anotherList;
}


// Prints the contents of the list
void DisplayCityList(FILE* fp_out, struct CityList* list, char *destination)
{
    // This is used to traverse the list
	struct City* Node = list->head;
	// This index variable keeps track of the index so that we can report it.
	int index = 0;

    // If there is no nodes in the list
	if (Node == NULL)
	{
		printf("The list is Empty\n");
		fprintf(fp_out, "The list is Empty\n");
	}
	else
	{
		printf("Route:\t\n");
		fprintf(fp_out, "Route:\t\n");
	}

	// Output all the city names in the list
	while (Node != NULL)
	{
	    // Prints out the first node in the list
		if (Node == list->head)
		{
			printf("\t- %s\n", Node->NameofCity);
			fprintf(fp_out, "\t- %s\n", Node->NameofCity);
		}
		// Then prints out the following nodes
		else
		{
			printf("\t-> %s\n", Node->NameofCity);
			fprintf(fp_out, "\t-> %s\n", Node->NameofCity);
		}
        // Move to the next node
		Node = Node->next;
		index++;
	}

	// Prints the name of the destination
	printf("\t-> %s\n", destination);
	//Prints the name of the destination on output file
	fprintf(fp_out, "\t-> %s\n", destination);
}


// Read the data from the energy file
void LoadMapData(struct List* list, char* filename, struct CityList* cities)
{
	char NameofFile[31];
	char SourceCity[31];
	char DestCity[31];
	int Energy;

    //Declare a pointer of type file
    // r : open for reading
	FILE* fp_energy;
	fp_energy = fopen(filename, "r");

	// If the energy file doesn't exist, print the error message and exit
	if (fp_energy == NULL)
	{
		printf("Oh no! Where is your energy file? Please Check it again :)");
		exit(1);
		//return 0;
	}
	// Else, the file exists and can be read
	else
	{
		// Read each line of energy file till the end
		while (fgets(NameofFile, sizeof(NameofFile), fp_energy) != NULL)
		{
		    // Reads the data from NameofFile and stores value into variables
			sscanf(NameofFile, "%s\t%s\t%d", SourceCity, DestCity, &Energy); //데이터 추출

			// Adds the data gotten from above into the list
			// All the road connecting source and destination is two way roads
			// So that the car can go both ways
			AddList(list, SourceCity, DestCity, Energy);
			AddList(list, DestCity, SourceCity, Energy);

			// Values are stored in citylist as well
			AddCity(cities, SourceCity);
			AddCity(cities,  DestCity);
		}
        // End reading the file and close it
		fclose(fp_energy);
	}

}
