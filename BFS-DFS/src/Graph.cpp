#include "Graph.h"
#include <iostream>

Graph::Graph(std::ifstream& input)
	:m_VerticesCount(0)
{
	input >> m_VerticesCount;
	input >> m_EdgesCount;
}

Graph::~Graph()
{
	for (int i = 0; i < m_VerticesCount; i++)
	{
		delete[] m_GraphMatrix[i];
	}

	delete[] m_GraphMatrix;
}

void Graph::PushToVisited(const unsigned int& index, const bool& value)
{
	m_VisitedElements[index] = value;
}

void Graph::SetGraphMatrix(std::ifstream& input, const std::string& mode)
{
	m_GraphMatrix = new int* [m_VerticesCount];

	for (int i = 0; i < m_VerticesCount; i++)
		m_GraphMatrix[i] = new int[m_VerticesCount];


	const unsigned int elementCount = (mode == "vertex") ? m_VerticesCount : m_EdgesCount;

	for (int i = 0; i < m_VerticesCount; i++)
		for (int j = 0; j < elementCount; j++)
		{
			input >> m_GraphMatrix[i][j];
		}
}

void Graph::DisplayMatrix(const std::string& mode) const
{
	if (mode == "vertex")
		std::cout << "   v1 v2 v3 v4 v5";
	else
		std::cout << " e1 e2 e3 e4 e5 e6 e7";

	std::cout << std::endl;

	const unsigned int elementCount = (mode == "vertex") ? m_VerticesCount : m_EdgesCount;

	for (int i = 0; i < m_VerticesCount; i++) {
		std::cout << "v" << i + 1 << "  ";
		for (int j = 0; j < elementCount; j++)
		{
			std::cout << m_GraphMatrix[i][j] << "  ";
		}
		std::cout << std::endl;
	}
}

void Graph::Clear()
{
	ClearVisitedElementMap();
	ClearGraphMatrix();
}

void Graph::ClearGraphMatrix()
{
	m_GraphMatrix = nullptr;
}

void Graph::ClearVisitedElementMap()
{
	std::map<int, bool>().swap(m_VisitedElements);
}