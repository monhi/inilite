This is a lite implementation of ini configuration files for Linux OS.
It uses C++ 11 features. 
following templates are used:
1. std::map
2. std::string
3. std::mutex
4. std::set 

it is the first time that I use std::set in a project. 

Just, setKey and getkey functions are implemented to handle string values. 
Other types can be converted to string and saved inside ini file. 

Notes:
- each line can have maximum or 512 characters. you can change it in `IniLinux.h` header file.
- lines are sorted alphabetically before saving.



