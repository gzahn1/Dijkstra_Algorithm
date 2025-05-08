#include "Edge.h"
#include "Vertex.h"
#include <iostream>
#include <climits>

int closestVertex(bool* visited, int* distance, int numVerts) {
    int closestIndex = -1;
    int shortestDist = INT_MAX;

    for(int i = 0; i < numVerts; i++) { // go through each node that isnt visited, and find the min distance
        if(distance[i] <= shortestDist && !visited[i]) {
            shortestDist = distance[i];
            closestIndex = i;
        }
    }
    return closestIndex;
}

void updateDistances(int** adjMatrix, int* distance, bool* visited, int numVerts) {
    // establish array of distances from source
    for(int i = 0; i < numVerts-1; i++) {      // relax edges numVrts-1 times
        int start = closestVertex(visited, distance, numVerts);
        if(0 <= start) {
            for(int j = 0; j < numVerts; j++) {
                if(adjMatrix[start][j]!=0 && (distance[start] + adjMatrix[start][j]) < distance[j] && distance[start]<INT_MAX && !visited[j]) {
                    distance[j] = distance[start] + adjMatrix[start][j]; //update neighbor dist
                }
            }
            visited[start] = true;
        }
    }
}

void dijkstra(int** adjMatrix, int sourceIndex, int* distance, bool* visited, int numVerts) {
    distance[sourceIndex] = 0;
    updateDistances(adjMatrix, distance, visited, numVerts);

    // output SSSP
    std::cout << "Single source shortest path lengths from node " << sourceIndex + 1 << std::endl;
    for(int i = 0; i < numVerts; i++) {
        std::cout << i+1 << ": " << distance[i] << std::endl;
    }
}

int main(){

    // start of the initial pipeline that loads the test case file stream from std::cin

    int numOfVertices;
    int numOfEdges;

    if(!std::cin.eof()){
        std::cin >> numOfVertices;
        std::cin >> numOfEdges;
    }
    else{
        std::cout<<"Input not found!"<<std::endl;
        return -1;
    }

    int** adjMatrix = new int*[numOfVertices];   // build adjMatrix for graph
    for(int i = 0; i < numOfVertices; i++) {
        adjMatrix[i] = new int[numOfVertices];
    }

    for(int i = 0; i < numOfVertices; i++) {     // initialize to 0
        for(int j = 0; j < numOfVertices; j++) {
            adjMatrix[i][j] = 0;
        }
    }

    while(!std::cin.eof()){
        int startVertice;
        int endVertice;
        std::cin >> startVertice;
        std::cin >> endVertice;
        Edge* newEdge = new Edge(startVertice, endVertice);
        // Here is where you load up the Graph object
        adjMatrix[startVertice-1][endVertice-1] = 1;  // subtract 1 to get index
        adjMatrix[endVertice-1][startVertice-1] = 1;      // add opposite since its undirected
    }

    // And here is where you start working on the three tasks

    // print adjMatrix
    std::cout << "The adjacency matrix of G:" << std::endl;
    for(int i = 0; i < numOfVertices; i++) {     
        for(int j = 0; j < numOfVertices; j++) {
            std::cout << adjMatrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    // find odd degree vertices
    std::cout << "The odd degree vertices in G:" << std::endl;
    std::cout << "O = { ";
    int numOdd = 0;
    for (int i = 0; i < numOfVertices; i++)
    {
        int sum = 0;
        for (int j = 0; j < numOfVertices; j++)
        {
            sum+= adjMatrix[i][j];
        }
        if (sum % 2 == 1) {
           std::cout << i+1 << " ";
           numOdd++;
        }
        
    }
    std::cout << "}" << std::endl;
    std::cout << std::endl;
    

    // put odd degrees in array "oddVertices"
    int* oddVertices = new int[numOdd];
    int oddIndex = 0;
    for (int i = 0; i < numOfVertices; i++)
    {
        int sum = 0;
        for (int j = 0; j < numOfVertices; j++)
        {
            sum+= adjMatrix[i][j];
        }
        if (sum % 2 == 1) {
           oddVertices[oddIndex] = i;
           oddIndex++;
        }
        
    }


    // build distance array, initialize to INT_MAX
    int* distance = new int[numOfVertices];
    

    // build visited array, initialize to false
    bool* visited = new bool[numOfVertices];
    

    // call dijkstra on all odd vertices
    for (int i = 0; i < numOdd; i++) {
        int sourceIndex = oddVertices[i];
        for(int j = 0; j < numOfVertices; j++) {
            visited[j] = false;
            distance[j] = INT_MAX;
        }
        dijkstra(adjMatrix, sourceIndex, distance, visited, numOfVertices);
    }


    // delete 
    for (int i = 0; i < numOfVertices; i++)
    {
        delete[] adjMatrix[i];
    }
    delete[] adjMatrix; 

    // delete distance
    delete[] distance;
    // delete visited
    delete[] visited;

    return 0;
}