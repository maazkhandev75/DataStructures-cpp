#include<iostream>
#include<vector>
#include<list>
#include<queue>

using namespace std;
//writing std before list like (   std::list<int>  ) is related 
// to using namspace std not STL (standard template library) library
// and it is compulsory to write even before cin  
// , cout like std :: cout if we donot write using namespace std; ...

//In Adjacency List, we use an array of a list to represent the graph.
//The size of the list's array is equal to the number of vertex(n).
//Adjlist[0] will have all the nodes which are connected to vertex 0. 
//Adjlist[1] will have all the nodes which are connected to vertex 1 and so on.

class graphs
{
	int V;
	list<int>* adj_list;  //ptr of list<int> whcih will be used to dynamically obtain an array of size v of lists ....
public:
	graphs(int v = 0)
	{
		if (v)
		{
			V = v;
			adj_list = new list<int>[v];
		}
		else
		{
			V = 0;
			adj_list = 0;   //points to NULL..
		}
	}
	void insertEdge(int v, int w)
	{
		if (v < V && v >= 0)
			adj_list[v].push_back(w);   //push_back() is the func. of STL list which push elements in the list from back....
		else
			cout << "\nInvalid Graph Index.";
	}

	void BFSearch(int s)
	{
		vector<bool> visited(V, false);   //declared a vector of size V and initialize all entries of vector as false...
		queue<int> stock;
		stock.push(s);

		while (!stock.empty())
		{
			int cur = stock.front();
			stock.pop();
			if (visited[cur] == false)
			{
				cout << cur << endl;
				visited[cur] = true;
				for (list<int> ::iterator itr = adj_list[cur].begin(); itr != adj_list[cur].end(); ++itr)    
					stock.push(*itr);
			}
		}
	}

	void DFSRec(int s, vector<bool>& visited)   //Depth First Search Recursive
	{
		visited[s] = true;
		cout << s << endl;
		for (list<int>::iterator itr = adj_list[s].begin(); itr != adj_list[s].end(); itr++)
			if (visited[*itr] == false)
			{
				DFSRec(*itr, visited);
			}
	}

	void DFSearch(int s)
	{  
		vector<bool> visited(V, false);
		DFSRec(s, visited);     //actually we have to recursively call that func. 
	}

	~graphs()
	{
		delete[] adj_list;
		adj_list = 0;   //basically in this case, it an extra instruction for the processor 
	}
};
int main()
{
	graphs g(4);  //  0-3 indices of array
	g.insertEdge(0, 1);
	g.insertEdge(0, 2);
	g.insertEdge(0, 3);
	g.insertEdge(1, 0);
	g.insertEdge(2, 1);
	g.insertEdge(2, 3);
	g.insertEdge(1, 3);

	///the starting vertex is given to the func to start traversing from that vertex..  (we can also give zero or some other vertex)
	cout << "BFS:\n";
	g.BFSearch(0);        //breath first search  
	cout << "\n\nDFS:\n";
	g.DFSearch(0);        //depth first search

}
