#pragma once

#include <map>
#include <fstream>

// Graph types
static enum GraphTypesEnum { undirected, directed, weighted }; 

static std::map<GraphTypesEnum, std::string> graphTypes = {
	{ undirected, "undirected" },
	{ directed, "directed" },
	{ weighted, "weighted" }
};

/* 
 * Class which contain all information about every graph for searches
 */
class Graph {
private:
	int m_VerticesCount; // vertices
	int m_EdgesCount; // edges
	int** m_GraphMatrix;

	/* 
	* 0 - unvisited, 1 - visited element 
	* Element - vertex or edge depending on the matrix
	*/
	std::map<int, bool> m_VisitedElements; 
public:
	Graph(std::ifstream& input);
	~Graph();

	
	void PushToVisited(const unsigned int& index, const bool& value);
	void SetGraphMatrix(std::ifstream& input, const std::string& mode);
	void DisplayMatrix(const std::string& mode) const;

	void Clear();
	void ClearGraphMatrix();
	void ClearVisitedElementMap();

	inline int GetVertexFromMatrix(const unsigned int& row, const unsigned column) { return m_GraphMatrix[row][column]; }
	inline int IsElementVisited(const unsigned int& index)  { return m_VisitedElements[index]; }
	inline int GetVerticesCount() { return m_VerticesCount; }
	inline int GetEdgesCount() { return m_EdgesCount; }
};