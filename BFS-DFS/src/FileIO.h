#pragma once

#include <fstream>

/*
* Class for I/O processing
*/
class FileIO {
private:
	std::string m_InputFilePath;
	std::string m_OutputFilePath;
	std::ifstream m_Input;
	std::ofstream m_Output;
public:
	FileIO() {};
	FileIO(const std::string& ifp, const std::string& ofp);
	~FileIO();
	
	void InputOpen();
	void InputOpen(const std::string& ifp);

	void OutputOpen();
	void OutputOpen(const std::string& ofp);
	void OutputOpen(const std::string& ofp, const unsigned int& mode);

	void InputClose();
	void OutputClose();

	inline std::ifstream& GetInputStream() { return m_Input; }
	inline std::ofstream& GetOutputStream() { return m_Output; }
};