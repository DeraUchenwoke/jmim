#ifndef JMIM_INCLUDE_PARSE_CSV_H_
#define JMIM_INCLUDE_PARSE_CSV_H_

#include <fstream>
#include <iostream>
#include <string>

/*
    - Try to open file (in chunks if it is large)
    - If successful read file contents. This involves: 
    - Converting non-header strings into appropriate data types i.e., boolean, integer etc.
    - Encode discrete string data types (TBD which method of encoding is suitable). 
    - Discretise continuous variables (number of buckets is user-specified).
    - Populate processed data into an appropriate data structure (based on size of CSV?).
*/

bool FileExists(const std::string &path)
{
    std::ifstream fs(path); 
    return fs.is_open(); 
}

void ReadCSV(const std::string &path) 
{ 
    if (FileExists(path))
    {
        std::cout << "File exists: " << path << std::endl;
    }
    else {
        std::cout << "could not find file";
    }
}
#endif