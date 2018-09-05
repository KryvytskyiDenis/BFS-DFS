#include "DfsSearch.h"
#include "DfsSearch.h"

#include <iostream>
#include <string>
#include <iterator>

DFS_Search::DFS_Search()
	:m_DfsIndex(1)
{}

DFS_Search::~DFS_Search()
{
	ClearStack();
	ClearList();
	ClearDfsIndexMap();
}

void DFS_Search::AdjencyMatrix(Graph & graph, FileIO & fileIO, std::string graphType)
{
	
	std::cout << "\n\n________________________" << std::endl;
	std::cout << "DFS algorithm implementation using adjency matrix of " << graphType << " graph." << std::endl;
	std::cout << "Enter start vertex: ";

	int startVertex;
	std::cin >> startVertex;
	startVertex--;

	fileIO.OutputOpen("res/textFiles/output.txt", std::ios::app);

	// Display the matrix on the screen
	graph.DisplayMatrix("vertex");

	// DFS algorithm implementation
	m_Stack.push(startVertex);

	graph.ClearVisitedElementMap();
	graph.PushToVisited(startVertex, 1);

	std::cout << "\tSearch steps:\n";
	m_VerticesList.push_back(startVertex + 1);
	fileIO.GetOutputStream() << "DFS algorithm implementation using adjency matrix of " << graphType << " graph.";
	fileIO.GetOutputStream() << "\nVertices" << "\t\t" << "DFS-index" << "\t" << "Stack" << std::endl;
	fileIO.GetOutputStream() << startVertex + 1 << "\t\t" << m_DfsIndex << "\t\t" << m_VerticesList.front() << std::endl;
	while (!m_Stack.empty())
	{
		int v1 = m_Stack.top();

		for (int i = 0; i < graph.GetVerticesCount(); i++)
		{
			// We check all the vertices which we can get from the vertex v1
			if (graph.GetVertexFromMatrix(v1, i))
			{
				// If the vertex wasn't visited, visit it.
				if (!graph.IsElementVisited(i))
				{
					graph.PushToVisited(i, true);
					m_Stack.push(i);
					std::cout << v1 + 1 << " -> " << i + 1 << std::endl;
					m_VerticesList.push_back(i + 1);
					m_DfsIndex++;
					fileIO.GetOutputStream() << i + 1 << "\t\t" << m_DfsIndex << "\t\t";
					copy(m_VerticesList.begin(), m_VerticesList.end(), std::ostream_iterator<int>(fileIO.GetOutputStream(), " "));
					fileIO.GetOutputStream() << std::endl;
					break;
					// If unvisited vertex was found, go to it.
				}
				else if ((m_DfsIndexMap[i]) && (i == (graph.GetVerticesCount() - 1)))
				{
					m_Stack.pop();
					std::cout << "vertex " << v1 + 1 << " was deleted from stack.\n";
					fileIO.GetOutputStream() << "-" << "\t\t" << "-" << "\t\t";
					m_VerticesList.pop_back();
					copy(m_VerticesList.begin(), m_VerticesList.end(), std::ostream_iterator<int>(fileIO.GetOutputStream(), " "));
					fileIO.GetOutputStream() << std::endl;
					break;
				}
				else if (!m_DfsIndexMap[i] && (graph.IsElementVisited(i)))
				{
					std::cout << v1 + 1 << " ----> " << i + 1 << std::endl;
					m_DfsIndexMap[i] = true;
					continue;
				}
			}
			else if (i == (graph.GetVerticesCount() - 1)) {
				m_Stack.pop();
				std::cout << "vertex " << v1 + 1 << " was deleted from stack.\n";
				fileIO.GetOutputStream() << "-" << "\t\t" << "-" << "\t\t";
				m_VerticesList.pop_back();
				copy(m_VerticesList.begin(), m_VerticesList.end(), std::ostream_iterator<int>(fileIO.GetOutputStream(), " "));
				fileIO.GetOutputStream() << std::endl;
				break;
			}
		}
	}
	fileIO.GetOutputStream() << "_________________________________\n";
	fileIO.GetOutputStream().close();
}

void DFS_Search::IncidenceMatrix(Graph & graph, FileIO & fileIO, std::string graphType)
{
		std::cout << "\n\n________________________\nDFS algorithm implementation using incidence matrix of " << graphType << " graph." << std::endl;
		std::cout << "Enter start vertex: ";

		int startVertex;
		std::cin >> startVertex;
		startVertex--;

		// Display the matrix on the screen
		graph.DisplayMatrix("edge");
	
		fileIO.OutputOpen("res/textFiles/output.txt", std::ios::app);

		m_Stack.push(startVertex);
		graph.PushToVisited(startVertex, 1);

		std::cout << "\Search steps:\n";
		m_VerticesList.push_back(startVertex + 1);
		fileIO.GetOutputStream() << "DFS algorithm using incidence matrix of " << graphType << " graph.";
		fileIO.GetOutputStream() << "\nVertices" << "\t\t" << "DFS-index" << "\t" << "Stack" << std::endl;
		fileIO.GetOutputStream() << startVertex + 1 << "\t\t" << m_DfsIndex << "\t\t" << m_VerticesList.front() << std::endl;
	
		while (!m_Stack.empty())
		{
		stop:
			int v1 = m_Stack.top();
			for (int i = 0; i < graph.GetEdgesCount(); i++)
			{
				// Check all edges along which we can get to some vertex
				if (graph.GetVertexFromMatrix(v1, i))
				{
					for (int j = 0; j < graph.GetVerticesCount(); j++)
					{
						// If the vertex wasn't visited, visit it
						if ((graph.GetVertexFromMatrix(j, i)) && (!m_VisitedEdges[i]) && (!graph.IsElementVisited(j)))
						{
							graph.PushToVisited(j, true); // denote the vertex as visited
							m_VisitedEdges[i] = true;     // denote the edge as visited 
							m_Stack.push(j);
							m_VerticesList.push_back(j + 1);
							std::cout << v1 + 1 << " -> " << j + 1 << std::endl;
							std::cout << "edge " << v1 + 1 << "-" << j + 1 << " was visited!\n";
							m_DfsIndex++;
							fileIO.GetOutputStream() << j + 1 << "\t\t" << m_DfsIndex << "\t\t";
							copy(m_VerticesList.begin(), m_VerticesList.end(), std::ostream_iterator<int>(fileIO.GetOutputStream(), " "));
							fileIO.GetOutputStream() << std::endl;
							// If edge was visited, go to the next vertex (the end of the edge v1-j);
							goto stop;
						}
						else if ((graph.GetVertexFromMatrix(j, i)) && (m_DfsIndexMap[j]) && (i == (graph.GetEdgesCount() - 1)))
						{
							m_Stack.pop();
							std::cout << "vertex " << v1 + 1 << " was deleted from stack." << std::endl;
							fileIO.GetOutputStream() << "-" << "\t\t" << "-" << "\t\t";
							m_VerticesList.pop_back();
							copy(m_VerticesList.begin(), m_VerticesList.end(), std::ostream_iterator<int>(fileIO.GetOutputStream(), " "));
							fileIO.GetOutputStream() << std::endl;
							break;
						}
						else if ((graph.GetVertexFromMatrix(j, i)) && (!m_DfsIndexMap[j]) && (v1 != j))
						{
							std::cout << v1 + 1 << " ----> " << j + 1 << std::endl;
							m_DfsIndexMap[j] = true;
							continue;
						}
					}
				}
				else if (i == (graph.GetEdgesCount() - 1)) {
					m_Stack.pop();
					std::cout << "vertex " << v1 + 1 << " was deleted from stack" << std::endl;
					fileIO.GetOutputStream() << "-" << "\t\t" << "-" << "\t\t";
					m_VerticesList.pop_back();
					copy(m_VerticesList.begin(), m_VerticesList.end(), std::ostream_iterator<int>(fileIO.GetOutputStream(), " "));
					fileIO.GetOutputStream() << std::endl;
					break;
				}
			}
		}
		fileIO.GetOutputStream() << "_________________________________\n";
		fileIO.GetOutputStream().close();
}

void DFS_Search::Clear()
{
	m_DfsIndex = 1;
	ClearStack();
	ClearList();
	ClearDfsIndexMap();
}

void DFS_Search::ClearStack()
{
	std::stack<int> empty;
	std::swap(m_Stack, empty);
}

void DFS_Search::ClearList()
{
	std::list<int> empty;
	std::swap(m_VerticesList, empty);
}

void DFS_Search::ClearDfsIndexMap()
{
	std::map<int, bool> empty;
	std::swap(m_DfsIndexMap, empty);
}


