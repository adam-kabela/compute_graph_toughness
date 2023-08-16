// C++ program to detrmine toughness of a graph
#include<iostream>
#include <list>
#include <math.h>
#include <bitset>

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <sstream>
#include <cstdio>
using namespace std;
 
// Graph class represents a undirected graph
// using adjacency list representation
class Graph
{
    int V;    // number of vertices
 
    // pointer to an array containing adjacency lists
    list<int> *adj;
 
    // DFS recurrent search
    void DFSUtil(int v, bool visited[]);
	
	public:
    Graph(int V);   // Constructor
    void addEdge(int v, int w);
    void determineToughness(int N);
};
 
// a naive algorithm to determine toughness 
void Graph::determineToughness(int N)
{
	
	float min = 1000;
	int s = 0;
	int c = 0;
	int mins = 0;
	int minc = 0;
	
    bool *visited = new bool[V];

    for(int v = 0; v < N; v++) // set all the vertices as not visited
	{
		visited[v] = false;
	}
	DFSUtil(0, visited); // brovse from vertex 0
        
	for (int v=0; v<V; v++) // test t = 0
    {
    	if (visited[v] == false)
        {
        	cout << "t = 0 \n";
        	return;
        }
	}
	
	for (long int b=1; b<pow(2,N); b++) //components of G - X, for all subsets X // N at most 64 (long int)
    {
    	c = 0;
    	s = 0;
    	
		for(int v = 0; v < V; v++)
		{
			visited[v] = (((b >> v) & 1) == 1); // the binary of b represents a subset of vertices
		
			if (visited[v] == true)
	        {
	        	s++; // size of the set
	        	//cout << v << ", ";
	        }
		}
		
	    for (int v=0; v<V; v++) // counting components
	    {
	        if (visited[v] == false)
	        {
	            DFSUtil(v, visited);
	            c++;
	        }
	    }
	    if (c >= 2) // separating?
        {
        	if (c * min >= s)//new min
 			{
				min = (float)s / (float)c;
 				mins = s;
 				minc = c;
 				cout << "mins = " << mins << " minc = " << minc << " min = " << min << "\n";
				for(int v = 0; v < V; v++) // print separating set
				{
					if(((b >> v) & 1) == 1) 
					{
						cout << v << ", ";
					} 
				}
				cout << "\n";
 			}
        }
	}
	cout << "t = " << mins << "/" << minc << " = " << min << "\n";
}
 
void Graph::DFSUtil(int v, bool visited[])
{
    // Mark the current node as visited and print it
    visited[v] = true;
    // cout << v << " ";
 
    // Recur for all the vertices
    // adjacent to this vertex
    list<int>::iterator i;
    for(i = adj[v].begin(); i != adj[v].end(); ++i)
        if(!visited[*i])
            DFSUtil(*i, visited);
}
 
Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];
}
 
// add an edge
void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w);
    adj[w].push_back(v);
}
 
int main()
{   
    std::ifstream infile("r3p.txt");
	std::string line;
	int v = 0;
	
    Graph g(35); // 5 vertices numbered from 0 to 4
    
	while (std::getline(infile, line))
	{
		std::istringstream iss(line);
		int n;
		std::vector<int> vect;
	
		while (iss >> n)
		{
	    	vect.push_back(n);
	  	}
		v = vect[0];
	  	for (int i = 1; i < vect.size(); i++)
		{
			g.addEdge(v, vect[i]);
			cout << v << " " << vect[i] << ", ";
    	}
    	cout << "\n";
	}
    
 	int N = 24; //last non-simplicial vertex // at most 64 (long int)
    g.determineToughness(N);
    
    return 0;
}
