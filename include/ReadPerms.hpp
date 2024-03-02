#ifndef JMIM_INCLUDE_READ_PERMS_H_
#define JMIM_INCLUDE_READ_PERMS_H_
#pragma comment(lib, "netapi32.lib")

#include <accctrl.h>
#include <aclapi.h>
#include <iostream>
#include <lm.h>
#include <Lmcons.h>
#include <memory>
#include <ostream>
#include <string>
#include <unordered_map>
#include <windows.h>

/* ------------------------------------------ Behind the scences functions ----------------------------------------- */

void FormatErrorMsg(DWORD error)
{
    std::unique_ptr<LPWSTR> last_error_buffer = nullptr;  
    LPWSTR *last_error_msg = last_error_buffer.get();

    FormatMessageW(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | 
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        error,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPWSTR) &last_error_buffer,
        0, 
        NULL );

    std::cerr << last_error_msg << std::endl;
    ExitProcess(error); 
}

std::wstring GetCurrentUsername()
{
    DWORD username_buffer = UNLEN + 1;
    std::unique_ptr<WCHAR[]> username(new WCHAR[username_buffer]);

    if (!GetUserNameW(username.get(), &username_buffer))
    {
        FormatErrorMsg(GetLastError());
    }
    return username.get();
}

std::wstring GetDomainName()
{
    std::unique_ptr<WKSTA_INFO_100> local_workstation_info = nullptr; 

    NET_API_STATUS local_workstation_status = NetWkstaGetInfo(
        NULL,
        100,
        (LPBYTE *) &local_workstation_info
    );
    if (local_workstation_status != NERR_Success)
    {
        FormatErrorMsg(GetLastError());
    }
    return local_workstation_info->wki100_langroup;
}

std::wstring CreateQualifiedAccountName(std::wstring &username, std::wstring &domain_name) {
    std::wstring qualified_account_name;
    WCHAR escaped_backward_slash = '\\';
    qualified_account_name.reserve(sizeof(username) + sizeof(domain_name) + sizeof(escaped_backward_slash)); 

    qualified_account_name = domain_name + escaped_backward_slash + username;
    return qualified_account_name;
}

/* ------------------------------------------------- Main functions ------------------------------------------------ */

// bool HasReadAccessWindows(const wchar_t *file_path)
// {
//     HANDLE file_handle = CreateFileW(
//         file_path,
//         GENERIC_READ,
//         0,
//         NULL,
//         OPEN_EXISTING,
//         FILE_ATTRIBUTE_NORMAL,
//         NULL);
//     if (file_handle != S_OK)
//     {
//         FormatErrorMsg(GetLastError());
//     }

//     unsigned int num_security_descriptors = 1;
//     std::unique_ptr<PSECURITY_DESCRIPTOR> security_descriptor_size = std::make_unique<PSECURITY_DESCRIPTOR>(
//         num_security_descriptors);
//     PSECURITY_DESCRIPTOR security_descriptor = security_descriptor_size.get();

//     DWORD file_security_info = GetSecurityInfo(
//         file_handle,
//         SE_FILE_OBJECT,
//         DACL_SECURITY_INFORMATION,
//         NULL,
//         NULL,
//         NULL,
//         NULL,
//         &security_descriptor);
//     if (file_security_info != ERROR_SUCCESS)
//     {
//         FormatErrorMsg(GetLastError());
//     }

//     // TODO: Get domain name [DONE]
//     // TODO: Create qualified account name [DONE]
//     // TODO: Use username to get current user's SID 
//     // TODO: User user's SID to create trustee struct (EXPLICIT_ACCESS)
//     // TODO: Return DACL if DACL for file is present
//     // TODO: Check if trustee struct exists in DACL (given it is present)

//     // https://learn.microsoft.com/en-us/windows/win32/api/accctrl/ns-accctrl-explicit_access_a

//     bool closed = CloseHandle(file_handle);
//     if (!closed)
//     {
//         FormatErrorMsg(GetLastError());
//     }
//     return false;
// }

/*
The DACL contains a list of Access Control Entries (ACE).
Each ACE specifies who is allowed to access this object and what kind of access certain users or groups have on the object.
Therefore, the idea behind this implementation is to get hold of the DACL of an object and then check if particular
user’s access rights exists in the DACL or not. */
#endif