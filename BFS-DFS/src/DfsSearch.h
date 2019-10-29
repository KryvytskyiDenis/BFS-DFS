#pragma once

#include <stack>
#include <list>
#include "Graph.h"
#include "FileIO.h"

/*
* Class which contain all information about depth-first search
* and all methods for searches unsing adjency and incidence matices
*/
class DFS_Search
{
private:
	int m_DfsIndex;
	std::stack <int> m_Stack;
	std::list<int> m_VerticesList;
	std::map<int, bool> m_DfsIndexMap; // 0 - unvisited, 1 - visited
	std::map<int, bool> m_VisitedEdges;
public:
	DFS_Search();
	~DFS_Search();

	void AdjencyMatrix(Graph& graph, FileIO& fileIO, std::string graphType);
	void IncidenceMatrix(Graph& graph, FileIO& fileIO, std::string graphType);

	void Clear();
	void ClearStack();
	void ClearList();
	void ClearDfsIndexMap();
};