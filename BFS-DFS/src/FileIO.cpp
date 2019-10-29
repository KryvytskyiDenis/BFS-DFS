#include "FileIO.h"
#include <stdarg.h> 

FileIO::FileIO(const std::string& ifp, const std::string& ofp)
	:m_InputFilePath(ifp), m_OutputFilePath(ofp) {}

FileIO::~FileIO()
{
	InputClose();
	OutputClose();
}

void FileIO::InputOpen()
{
	m_Input.open(m_InputFilePath);
}

void FileIO::InputOpen(const std::string& ifp)
{
	m_InputFilePath = ifp;
	m_Input.open(m_InputFilePath);
}

void FileIO::OutputOpen()
{
	m_Output.open(m_OutputFilePath);
}

void FileIO::OutputOpen(const std::string& ofp)
{
	m_OutputFilePath = ofp;
	m_Output.open(ofp);
}

void FileIO::OutputOpen(const std::string& ofp, const unsigned int& mode)
{
	m_OutputFilePath = ofp;
	m_Output.open(ofp, mode);
}

void FileIO::InputClose()
{
	m_Input.close();
}

void FileIO::OutputClose()
{
	m_Output.close();
}