#include "BfsSearch.h"
#include "DfsSearch.h"

void ClearAll(Graph & graph, BFS_Search& bfs, DFS_Search& dfs);

/*
* My implementation of BFS and DFS algorithms
* using adjacency and incidence matrices for undirected, directed and weighted graphs
*/
int main()
{
	{
		FileIO fileIO("res/textFiles/input.txt", "res/textFiles/output.txt");
		fileIO.InputOpen();
		fileIO.OutputOpen("res/textFiles/output.txt", std::ios::trunc);
		fileIO.OutputClose();

		Graph graph(fileIO.GetInputStream());

		BFS_Search Bfs;
		DFS_Search Dfs;
		std::string elementMode = "vertex";

		// Set up new matrix
		graph.SetGraphMatrix(fileIO.GetInputStream(), elementMode);

		// BFS and DFS using adjacency matrix for the undirected graph
		Bfs.AdjencyMatrix(graph, fileIO, graphTypes[GraphTypesEnum::undirected]);
		Dfs.AdjencyMatrix(graph, fileIO, graphTypes[GraphTypesEnum::undirected]);

		// Set up new matrix
		ClearAll(graph, Bfs, Dfs);
		graph.SetGraphMatrix(fileIO.GetInputStream(), elementMode);
		// BFS and DFS using adjacency matrix for the directed graph
		Bfs.AdjencyMatrix(graph, fileIO, graphTypes[GraphTypesEnum::directed]);
		Dfs.AdjencyMatrix(graph, fileIO, graphTypes[GraphTypesEnum::directed]);

		// BFS and DFS using incidence matrix for the directed graph
		elementMode = "edge";
		ClearAll(graph, Bfs, Dfs);
		graph.SetGraphMatrix(fileIO.GetInputStream(), elementMode);
		Bfs.IncidenceMatrix(graph, fileIO, graphTypes[GraphTypesEnum::directed]);
		graph.ClearVisitedElementMap();
		Dfs.IncidenceMatrix(graph, fileIO, graphTypes[GraphTypesEnum::directed]);

		// Set up new matrix
		elementMode = "vertex";
		ClearAll(graph, Bfs, Dfs);
		graph.SetGraphMatrix(fileIO.GetInputStream(), elementMode);
		// BFS and DFS using adjacency matrix for the weighted graph
		Bfs.AdjencyMatrix(graph, fileIO, graphTypes[GraphTypesEnum::weighted]);
		Dfs.AdjencyMatrix(graph, fileIO, graphTypes[GraphTypesEnum::weighted]);
		ClearAll(graph, Bfs, Dfs);
	}

	system("pause");

	return 0;
}

void ClearAll(Graph & graph, BFS_Search & bfs, DFS_Search & dfs)
{
	graph.Clear();
	bfs.Clear();
	dfs.Clear();
}