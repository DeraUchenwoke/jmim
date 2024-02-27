#include <filesystem>
#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_map>


bool HasReadAccess(const unsigned short &current_os, const std::string &file_name) {
    /* Switch case for Windows,Unix-like -> pass by reference since value is not modified. */

    if (!std::filesystem::exists(file_name)) {
        throw std::filesystem::filesystem_error();
    }
    
    switch (current_os) {
        case 1:
            // Func to check if user has read perms for Windows 64 bit systems.
        case 2: 
            // Func to heck if user has read perms for Unix/Unix-like systems.
        default:
            std::cout << "Unsupport operating system, unable to execute CLI tool.\n";
            return false;
    }
}

bool UnixReadAccess() {

}

bool WindowsReadAccess() {

}

const unsigned short GetCurrentOS() {
    /* Get current user OS at compile-time using C++ preprocessor directives and compiler macros. 
    List of compiler macros: https://sourceforge.net/p/predef/wiki/OperatingSystems/ */
    
    #ifdef _WIN64
    return 1;
    #elif __linux__ || __APPLE__ || __MACH__
    return 2;
    #else 
    return 0;
    #endif
}

