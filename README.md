# compute_graph_toughness

A simple code to determine toughness of a given graph. Plainly spoken, the toughness is a property that quantifies how well a graph holds together (for details, see https://en.wikipedia.org/wiki/Graph_toughness). No fast algorithm is known since the problem is NP-hard. This naive algorithm checks all possible cut-sets. The only smart thing about it is that simplicial vertices are not included in the tested cut-sets.


## Algorithm description and runtime analysis

Given a graph G and the set N of all non-simplicial vertices of G, the algorithm considers all subsets of N. For each subset S considered, the algorithm test the graph graph G-S (obtained from G by removing all vertices of S) and determines the number of components of G-S. The number of coponents is computed using a DFS algorithm. After checking all subsets, the algorithm outpusts the minimum of the ratio of S over number of components of G-S and a set S for which the minimum was obtained.

Since the number of all subsets of N is 2^|N|, the time complexity is O(2^|N|). This means that for large graphs with many non-simplicial vertices, the program is very slow. However, I used the program to help me test decent sized constructions of graphs (with roughly 30 non-simplicial vertices) and the runtime was ok. The resulting constructions can be found at https://arxiv.org/pdf/1705.09475.pdf and https://arxiv.org/pdf/1707.08026.pdf. 


## Usage

INPUT: a graph given by a txt file, each line encodes a vertex (first number on the line) and its neighbours (the remainder of the line) 
OUTPUT: toughness, a relevant cut-set S, number of components of G-S, printed in console

change the input file to encode your graph, and compile and run main.cpp 
