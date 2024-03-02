#include "../include/ReadPerms.hpp"

int main() {
    std::cout << '\n';
    std::wstring username = GetCurrentUsername(); 
    std::wstring domain_name = GetDomainName(); 
    std::wcout << CreateQualifiedAccountName(username, domain_name) << std::endl;
}