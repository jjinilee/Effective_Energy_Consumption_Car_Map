#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED


// Data structure stores a starting point, destination,
// integer 'Energy' and pointers to their neighbouring cities,
struct ListNode
{
    //Pointers to character Array
	char* Source;
	char* destination;
	int Energy;

	// the addresses of the next and previous nodes.
	struct ListNode* next;
	struct ListNode* prev;
};


//List structure for managing ListNode structure
struct List
{
    // A running count of the number of nodes in the list.
	int size;

	// The addresses of the first and last nodes in the list.
	struct ListNode* head;
	struct ListNode* tail;
};


// Data structure corresponding to city information entered from graphFile
// List of strings of the name of cities
struct City
{
	char* NameofCity;
	struct City* next;
	struct City* prev;
};


//List structure for managing City structure
struct CityList
{
	int size;
	struct City* head;
	struct City* tail;
};


// Create a list/listnode data structure.
struct List* listConstructor();
struct ListNode* listNodeConstructor(char* Source, char* destination, int Energy);


// Construct a data node and add it to the end of the List
// Return the number of data in the current list
int AddList(struct List* list, char* Source, char* destination, int Energy);


// Create and destroy a city data structure.
struct City* cityConstructor(char* Cityname);
struct CityList* cityListConstructor();
void cityListDestructor(struct CityList* list);


// Construct a city node and add it to the end of the Citylist
// Return 0 if the name of the city is already in the list
int AddCity(struct CityList* list, char* Cityname);


// Returns the first index of a city whose name is equal to the requested entity.
int citySearch(struct CityList* list, char* entity);


// Search for the name of the city using it's index value
char* cityNameSearch(struct CityList* list, int index);


// Copy the list 2 to list 1
struct CityList*  CopyCityList(struct CityList* list1, struct CityList* list2);


// Prints the contents of the list
void DisplayCityList(FILE* fp_out, struct CityList* list, char *destination);


// Read the data from the energy file
void LoadMapData(struct List* list, char* filename, struct CityList* cities);

#endif // LIST_H_INCLUDED
