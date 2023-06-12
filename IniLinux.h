#pragma once
#include <string>
#include <map>
#include <set>

#define		SUCCESS			 0
#define		FAILURE			-1

#define 	LINE_LENGTH 	512

typedef std::set<std::string>::iterator					setIterator;
typedef std::map<std::string, std::string>::iterator	mapIterator;

class CIniLinux
{
public:
										CIniLinux();
										~CIniLinux();
	void								setINIFileName(std::string strINIFile);
	std::string							getKey(std::string strKey, std::string strSection);
	long								setKey(std::string strValue, std::string strKey, std::string strSection);
private:
	std::set<std::string>				m_set;
	std::string							trim(const char* input);
	std::string							m_strFileName;
	std::string							m_currentSection;
	std::map<std::string, std::string>  m_content;
	void								ProcessSection(char *buffer);
	void								ProcessKey(char* buffer);
	int									Save();
};
