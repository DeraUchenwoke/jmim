#ifndef JMIM_INCLUDE_READ_PERMS_H_
#define JMIM_INCLUDE_READ_PERMS_H_

#include <accctrl.h>
#include <aclapi.h>
#include <iostream>
#include <string>
#include <unordered_map>
#include <windows.h>

bool HasReadAccessWindows(const char *file_path)
{
    HANDLE file_handle = CreateFileA(
        file_path,
        GENERIC_READ,
        0,
        NULL,
        OPEN_EXISTING,
        FILE_FLAG_SEQUENTIAL_SCAN,
        NULL);

    if (file_handle != S_OK)
    {
        FileHandleError();
    }

    // https://learn.microsoft.com/en-us/windows/win32/secauthz/access-control-lists
    // https://learn.microsoft.com/en-us/windows/win32/api/aclapi/nf-aclapi-getsecurityinfo
    unsigned int num_security_descriptors = 1;
    std::unique_ptr<PSECURITY_DESCRIPTOR> buffer = std::make_unique<PSECURITY_DESCRIPTOR>(num_security_descriptors);
    PSECURITY_DESCRIPTOR security_descriptor = buffer.get();
    DWORD file_security_info = GetSecurityInfo(
        file_handle,
        SE_FILE_OBJECT,
        DACL_SECURITY_INFORMATION,
        NULL,
        NULL,
        NULL,
        NULL,
        &security_descriptor);
    if (!file_security_info) 
    {
        std::cerr << "Failed to get file security information: " << GetLastError() << std::endl;
        return false; 
    }

    // TODO: Get current user's username (seperate function)
    // TODO: Use username to get current user's SID
    // TODO: User user's SID to create trustee struct (EXPLICIT_ACCESS)
    // TODO: Return DACL if DACL for file is present
    // TODO: Check if trustee struct exists in DACL (given it is present)


    // https://learn.microsoft.com/en-us/windows/win32/api/accctrl/ns-accctrl-explicit_access_a

    bool closed = CloseHandle(file_handle);
    if (!closed)
    {
        FileHandleError();
    }
    return false;
}


void FileHandleError()
{
    // https://learn.microsoft.com/en-us/windows/win32/seccrypto/common-hresult-values
    std::unordered_map<HRESULT, const std::string> BadHandleErrorMsg{
        {E_ABORT, "Operation aborted."},
        {E_ACCESSDENIED, "Access denied."},
        {E_FAIL, "Unspecified failure."},
        {E_HANDLE, "File handle is not valid."},
        {E_INVALIDARG, "One or more arguments are not valid."},
        {E_NOINTERFACE, "No such interface supported."},
        {E_NOTIMPL, "File handle not implemented."},
        {E_OUTOFMEMORY, "Failed to allocate necessary memory"},
        {E_POINTER, "Pointer is not valid."},
        {E_UNEXPECTED, "Unexpected failure"}};

    DWORD err = GetLastError();
    if (BadHandleErrorMsg.count(err))
    {
        std::cerr << BadHandleErrorMsg[err] << std::endl;
    }
    std::exit(err);
}

#endif