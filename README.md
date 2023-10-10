# INI Lite
This is a lite implementation of INI configuration files for Linux OS.
It uses C++ 11 features. 
The following templates are used:
1. std::map
2. std::string
3. std::mutex
4. std::set 

It is the first time that I have used std::set in a project. 

Just, setKey and getkey functions are implemented to handle string values. 
Other types can be converted to a string and saved inside INI file. 

Notes:
- Each line can have a maximum of 512 characters. But you can change it in the `IniLinux.h` header file.
- Lines are sorted alphabetically before saving.
- Comment lines are deleted automatically. do not save any comment.




