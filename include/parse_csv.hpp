#ifndef JMIM_INCLUDE_PARSE_CSV_H_
#define JMIM_INCLUDE_PARSE_CSV_H_

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

/*
    - Try to open file (in chunks if it is large)
    - If successful read file contents. This involves: 
    - Converting non-header strings into appropriate data types i.e., boolean, integer etc.
    - Encode discrete string data types (TBD which method of encoding is suitable). 
    - Discretise continuous variables (number of buckets is user-specified).
    - Populate processed data into an appropriate data structure (based on size of CSV?).
*/

std::string GetLineCSV(const std::string &path) 
{  
    std::ifstream fs(path);
    std::string raw_file_contents; 

    if (fs.is_open())
    {
        std::string elem; 
        while(std::getline(fs, elem)) 
        {
            raw_file_contents += elem;
        }
        fs.close();
    }
    else 
    {
        std::cerr << "File does not exist." << std::endl;
        return raw_file_contents;
    }
    return raw_file_contents; 
}

std::string StreamCSV(const std::string &path)
{
    std::ifstream fs(path);
    std::ostringstream sstr; 

    if (fs.is_open())
    {
        sstr << fs.rdbuf();
    }
    else 
    {
        std::cerr << "File again does not exist." << std::endl;
        return "";
    }
    return sstr.str(); 
}
#endif