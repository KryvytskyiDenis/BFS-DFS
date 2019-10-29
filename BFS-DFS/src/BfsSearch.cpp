#include "BfsSearch.h"

#include <iostream>
#include <queue>
#include <string>
#include <iterator>

BFS_Search::BFS_Search()
	:m_BfsIndex(1)
{}

BFS_Search::~BFS_Search()
{
	ClearQueue();
	ClearList();
}

void BFS_Search::AdjencyMatrix(Graph& graph, FileIO& fileIO, std::string graphType)
{
	std::cout << "\n\n________________________" << std::endl;
	std::cout << "BFS algorithm implementation using adjency matrix of " << graphType << " graph." << std::endl;

	std::cout << "Enter start vertex: ";

	int startVertex;
	std::cin >> startVertex;
	startVertex--;

	fileIO.OutputOpen("res/textFiles/output.txt", std::ios::app);

	// Display the matrix on the screen
	graph.DisplayMatrix("vertex");

	// Start vertex was visited
	graph.PushToVisited(startVertex, true);

	// Create queue for vertices
	m_Queue.push(startVertex);;

	// BFS implementation
	std::cout << "Search steps:" << std::endl;
	m_VerticesList.push_back(startVertex + 1);
	fileIO.GetOutputStream() << "BFS algorithm implementation using adjency matrix of " << graphType << " graph." << std::endl;
	fileIO.GetOutputStream() << "Vertices" << "\t" << "BFS-index" << "\t" << "Queue" << std::endl;
	fileIO.GetOutputStream() << startVertex + 1 << "\t\t" << m_BfsIndex << "\t\t" << m_VerticesList.front() << std::endl;

	while (!m_Queue.empty())
	{
		int v1 = m_Queue.front();
		m_Queue.pop();

		// Check all the vertices which we can get from the vertex v1
		for (int i = 0; i < graph.GetVerticesCount(); i++)
		{
			if (graph.GetVertexFromMatrix(v1, i)) {
				// If the vertex wasn't visited, visit it
				if (!graph.IsElementVisited(i))
				{
					graph.PushToVisited(i, true);
					m_Queue.push(i); // Add vertex to queue
					m_VerticesList.push_back(i + 1);
					std::cout << v1 + 1 << " -> " << i + 1 << std::endl;
					m_BfsIndex++;
					fileIO.GetOutputStream() << i + 1 << "\t\t" << m_BfsIndex << "\t\t";
					copy(m_VerticesList.begin(), m_VerticesList.end(), std::ostream_iterator<int>(fileIO.GetOutputStream(), " "));
					fileIO.GetOutputStream() << std::endl;

				}
				else std::cout << v1 + 1 << " ----> " << i + 1 << std::endl;
			}
		}
		std::cout << "Vertex " << v1 + 1 << " was removed form queue!\n";
		fileIO.GetOutputStream() << "-" << "\t\t" << "-" << "\t\t";
		m_VerticesList.pop_front();
		copy(m_VerticesList.begin(), m_VerticesList.end(), std::ostream_iterator<int>(fileIO.GetOutputStream(), " "));
		fileIO.GetOutputStream() << std::endl;
	}
	fileIO.GetOutputStream() << "______________________________________" << std::endl;
	fileIO.GetOutputStream().close();
}

void BFS_Search::IncidenceMatrix(Graph& graph, FileIO& fileIO, std::string graphType)
{

	std::cout << "\n\n________________________" << std::endl;
	std::cout << "BFS algorithm implementation using incidence matrix of " << graphType << " graph." << std::endl;

	std::cout << "Enter start vertex: ";

	int startVertex;
	std::cin >> startVertex;
	startVertex--;

	fileIO.OutputOpen("res/textfiles/output.txt", std::ios::app);

	graph.DisplayMatrix("edge");

	// BFS indices
	m_BfsIndexMap[startVertex] = 1;

	m_Queue.push(startVertex);

	// BFS implementation
	std::cout << "Search steps:" << std::endl;
	m_VerticesList.push_back(++startVertex);
	fileIO.GetOutputStream() << "BFS algorithm implementation using incidence matrix of " << graphType << " graph." << std::endl;
	fileIO.GetOutputStream() << "Vertices" << "\t" << "BFS-index" << "\t" << "Queue" << std::endl;
	fileIO.GetOutputStream() << startVertex + 1 << "\t\t" << m_BfsIndex << "\t\t" << m_VerticesList.front() << std::endl;
	while (!m_Queue.empty())
	{
		int v1 = m_Queue.front();
		m_Queue.pop();
		// Check all edges which go from the vertex v1
		for (int i = 0; i < graph.GetEdgesCount(); i++)
		{
			if (graph.GetVertexFromMatrix(v1, i))
			{
				// If the edge wasn't visited, visit it
				if (!graph.IsElementVisited(i))
				{
					// Denote the edge i as visited
					graph.PushToVisited(i, true);
					for (int j = 0; j < graph.GetVerticesCount(); j++)
					{
						if ((graph.GetVertexFromMatrix(j, i)) && (!m_BfsIndexMap[j]))
						{
							m_BfsIndexMap[j] = true;
							m_Queue.push(j);
							m_VerticesList.push_back(j + 1);
							std::cout << v1 + 1 << " -> " << j + 1 << std::endl;
							std::cout << "edge " << v1 + 1 << "-" << j + 1 << " was visited!" << std::endl;
							m_BfsIndex++;
							fileIO.GetOutputStream() << j + 1 << "\t\t" << m_BfsIndex << "\t\t";
							copy(m_VerticesList.begin(), m_VerticesList.end(), std::ostream_iterator<int>(fileIO.GetOutputStream(), " "));
							fileIO.GetOutputStream() << std::endl;
						}
					}
				}
				else {
					for (int j = 0; j < graph.GetVerticesCount(); j++)
					{
						if ((graph.GetVertexFromMatrix(j, i)) && (j != v1))
						{
							std::cout << v1 + 1 << " ----> " << j + 1 << std::endl;
						}
					}
				}
			}
		}
		std::cout << "vertex " << v1 + 1 << " was deleted form queue." << std::endl;
		fileIO.GetOutputStream() << "-" << "\t\t" << "-" << "\t\t";
		m_VerticesList.pop_front();
		copy(m_VerticesList.begin(), m_VerticesList.end(), std::ostream_iterator<int>(fileIO.GetOutputStream(), " "));
		fileIO.GetOutputStream() << std::endl;
	}
	fileIO.GetOutputStream() << "_________________________________" << std::endl;
	fileIO.GetOutputStream().close();
}

void BFS_Search::Clear()
{
	m_BfsIndex = 1;
	ClearQueue();
	ClearList();
}

void BFS_Search::ClearQueue()
{
	std::queue<int> empty;
	std::swap(m_Queue, empty);
}

void BFS_Search::ClearList()
{
	std::list<int> empty;
	std::swap(m_VerticesList, empty);
}

void BFS_Search::ClearBfsIndexMap()
{
	std::map<int, bool> empty;
	std::swap(m_BfsIndexMap, empty);
}
