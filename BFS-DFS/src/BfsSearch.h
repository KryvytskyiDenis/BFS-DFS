#pragma once

#include <queue>
#include <list>
#include "Graph.h"
#include "FileIO.h"

/*
* Class which contain all information about breadth-first search
* and all methods for searches unsing adjency and incidence matices
*/
class BFS_Search
{
private:
	int m_BfsIndex;
	std::queue<int> m_Queue;
	std::list<int> m_VerticesList;
	std::map<int, bool> m_BfsIndexMap;
public:
	BFS_Search();
	~BFS_Search();

	void AdjencyMatrix(Graph& graph, FileIO& fileIO, std::string graphType);
	void IncidenceMatrix(Graph& graph, FileIO& fileIO, std::string graphType);

	void Clear();
	void ClearQueue();
	void ClearList();
	void ClearBfsIndexMap();
};