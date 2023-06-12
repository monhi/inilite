#include "IniLinux.h"
#include <stdio.h>
#include <set>
#include <string.h>

std::string CIniLinux::trim(const char* input)
{
	std::string stemp;
	bool seen = false;
	unsigned int i, j;
	char output[LINE_LENGTH];
	memset(output, 0, LINE_LENGTH);
	for (i = 0, j = 0; i<strlen(input); i++)
	{
		if (input[i] != ' ' &&  input[i] != '\n')
		{
			output[j++] = input[i];
			seen = true;
		}
		else if (seen == true)
		{
			output[j++] = input[i]; // middle space characters
		}
	}
	output[j] = 0;
	if (strlen(output))
	{
		while (output[j - 1] == ' ' || output[j - 1] == '\n')
		{
			output[j - 1] = 0;
			j--;
		}
	}
	stemp = output;
	return stemp;
}

CIniLinux::CIniLinux()
{
}

CIniLinux::~CIniLinux()
{
}

void CIniLinux::setINIFileName(std::string strINIFile)
{
	char buffer[LINE_LENGTH];
	m_strFileName = strINIFile;
	FILE* f = fopen(strINIFile.c_str(), "r");
	if (f != NULL)
	{
		// read all the contents from file and put it to dedicated data structures.
		while (!feof(f))
		{
			memset(buffer, 0, LINE_LENGTH);
			fgets(buffer, LINE_LENGTH, f);
			std::string stemp = trim(buffer); // remove space characters from the beginning and end of buffer, but keep other space characters
			if (strlen(buffer) > 0)
			{
				if (buffer[0] == '[')
				{
					ProcessSection((char*)stemp.c_str());
				}
				else
				{
					ProcessKey((char*)stemp.c_str());
				}
			}
		}
		fclose(f);
	}
}

void CIniLinux::ProcessKey(char* buffer)
{
	std::string stemp = buffer;
	if (stemp.find('=') != std::string::npos)
	{
		std::string key = stemp.substr(0, stemp.find('='));
		std::string value = stemp.substr(stemp.find('=')+1);

		if (m_currentSection.length())
		{
			std::string newKey = m_currentSection + "+" + key;
			m_content[newKey] = value;
		}
		else
		{
			// do nothing yet.
		}
	}
}

void CIniLinux::ProcessSection(char *buffer)
{
	int idx = 0;
	char sectionName[LINE_LENGTH];
	memset(sectionName, 0, LINE_LENGTH);
	bool seen = false;
	for (unsigned int i = 0; i < strlen(buffer); i++)
	{
		if (buffer[i] == '[')
		{
			seen = true;
		}
		else if (buffer[i] == ']')
		{
			seen = false;
		}		
		else if (seen)
		{
			sectionName[idx++] = buffer[i];
		}
	}
	if (seen == false)
	{
		m_currentSection = sectionName;
		m_set.insert(m_currentSection);
	}
	else
	{
		m_currentSection = ""; // problematic section name;
	}
}

std::string CIniLinux::getKey(std::string strKey, std::string strSection)
{
	std::string stemp = strSection + "+" + strKey;
	if (m_content.find(stemp) != m_content.end())
	{
		return m_content[stemp];
	}
	return std::string("");
}

// Used to add or set a key value pair to a section
long CIniLinux::setKey(std::string strValue, std::string strKey, std::string strSection)
{
	std::string stemp = trim(strSection.c_str()) + "+" + trim(strKey.c_str());
	m_content[stemp] = strValue;
	m_set.insert(strSection);
	Save();
	return 0;
}

int CIniLinux::Save()
{
	//////////////////////////////////
	std::string		stemp;
	std::string		skey;
	std::string		mkey;
	std::string		mvalue;
	std::string		data;
	//////////////////////////////////
	if (m_strFileName.length())
	{
		FILE* f = fopen(m_strFileName.c_str(), "w");
		if (f)
		{			
			for (setIterator it = m_set.begin(); it != m_set.end(); ++it)
			{
				skey = *it; // key name.
				stemp = "["+skey+"]"+"\n";
				fwrite(stemp.c_str(), 1, stemp.length(), f);
				for (mapIterator mit = m_content.begin(); mit != m_content.end(); mit++)
				{
					mkey = mit->first;
					mvalue = mit->second;
					stemp = skey + "+";
					std::size_t found = mkey.find(stemp);
					if ( found == 0)
					{
						if (mkey.find('+') != std::string::npos)
						{
							data  = mkey.substr(mkey.find('+')+1);
							data += "=";
							data += mvalue;
							data += "\n";
							fwrite(data.c_str(), 1, data.length(), f);
						}						
					}
				}
			}
			fclose(f);
			return SUCCESS;
		}
		return FAILURE;		
	}
	return FAILURE;
}
