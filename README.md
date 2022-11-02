# The map of the effective energy consumption of electric cars


Imagine we are now in the future where electric cars are the norm and they can be charged when the car passes over certain roads as there will be wireless chargers under the roads. We will not have to go to the petrol station anymore to fill up with petrol but instead, we want to travel in the best possible path where we spend the least energy while travelling from one city to the other. 



# Summary of the contents

This project is to design and test a program that implements a graph of cities and roads and then calculates the minimum energy consumption between pairs of given source and destination cities.

We will be using 3 text files in this program – Energy, Citypairs and Output.

“Energy” is the provided text file where each line in the file lists the energy loss incurred when travelling between two cities. For example, if we move from ‘York -> Hull’ or ‘Hull -> York’, we will be losing 60J while travelling between them.

"Citypairs" is the provided text file where each line consists of the start and end cities to be calculated. This can be changed by the user by putting in the name of the city as much as they want. However, those cities' names need to be present in the energy file and in this case, these 6 cities have been entered :

York -> Perth

Hull -> Bristol

Northampton -> Carlisle

Since you cannot go directly from source to destination, you will be going through other cities in the energy file. Even that path should be a route that consumes the least energy from the origin to the destination via another city. The road has to be in both directions so that the cars can travel both ways, but you cannot pass by the same city twice. 

“Output” text file is the file that we are creating to write the output results.


# Description of the project

When you want to load the energy file into the graph, you are going to first load that file into the list first and from this list node, you get a data from name of the source and destination cities, energy needed to go between them and the address of the next and previous nodes. Then you are going to input that node as your road. Then we will construct a road using city index information and a graph with roads and cities.

‘Bellman-Ford Algorithm’ has been used to find the shortest path between the source and destination which leads to the least energy loss. To put it simply, imagine city is the vertex, road is the edge and weight is the energy loss.

# Technical Specification

If the program cannot find the energy text file, it will print out :

![image](https://user-images.githubusercontent.com/116571508/198331419-f73c6f97-9b4d-4d8d-8f0e-84c36e83bf28.png)

If the program cannot find the citypairs text file, it will print out :

![image](https://user-images.githubusercontent.com/116571508/198331779-bc9837bf-be7a-4d2e-b08b-a634d53873a7.png)

Output of this program will look like this :

![Screenshot (1)](https://user-images.githubusercontent.com/116571508/198332339-96da288a-6c6d-4336-93ea-131d389cee05.png)


Libraries used : <stdio.h>, <stdlib.h>, <string.h>, <limits.h>
