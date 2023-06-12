#include "IniLinux.h"
#include <iostream>

int main(int argc, char* argv[])
{
	CIniLinux*		m_ini = new CIniLinux();
	m_ini->setINIFileName("tester.ini");
	//std::string		stemp = m_ini->getKeyValue(std::string("OMS"), std::string("ServerIP"));
	m_ini->setKey("ADMIN", "USERNAME", "DATABASE");
	m_ini->setKey("*****", "PASSWORD", "DATABASE");
	std::string stemp = m_ini->getKey("USERNAME", "DATABASE");
	std::cout << "database user name is: " << stemp << std::endl;
	delete			m_ini;
	return			0;
}

