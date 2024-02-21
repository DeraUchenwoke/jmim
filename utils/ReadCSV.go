//go:build linux || darwin || windows

package utils

import (
	"fmt"
	"golang.org/x/sys/windows"
	"log"
	"runtime"
)

func GetFileInfo(filePath string) {

	hasAccess, err := WindowsFilePermissions(windows.StringToUTF16Ptr(filePath))
	if err != nil {
		panic(err)
	} else {
		log.Println(hasAccess)
	}

	switch os := runtime.GOOS; os {
	case "darwin":
		// PLaceholders
		fmt.Println("mac")
	case "windows":
		fmt.Println("win")
	case "linux":
		fmt.Println("linux")
	default:
		log.Fatalf("This version and below does not have support for the %s operating system", os)
	}
}

func WindowsFilePermissions(fileNamePtr *uint16) (bool, error) {
	/*
		Creates a file handle. While it is open, the security information for the file is retrieved
		and used to check if the current user has read access to the file:

		CreateFile: https://learn.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-createfile
		GetSecurityInfo: https://learn.microsoft.com/en-us/windows/win32/api/aclapi/nf-aclapi-getsecurityinfo
	*/
	const (
		desiredAcesss    = windows.GENERIC_READ
		shareMode        = windows.FILE_SHARE_READ
		creationMode     = windows.OPEN_EXISTING
		fileAttribute    = windows.FILE_FLAG_SEQUENTIAL_SCAN
		fileObjectType   = windows.SE_FILE_OBJECT
		securityInfoType = windows.DACL_SECURITY_INFORMATION
	)

	fileHandle, err := windows.CreateFile(
		fileNamePtr,
		desiredAcesss,
		shareMode,
		nil,
		creationMode,
		fileAttribute,
		0,
	)
	if err != nil {
		return false, err
	}
	defer windows.CloseHandle(fileHandle)

	fileSecurityInfo, err := windows.GetSecurityInfo(
		fileHandle,
		fileObjectType,
		securityInfoType,
	)
	if err != nil {
		return false, err
	}
	fmt.Println(fileHandle, fileSecurityInfoe)

	// TODO: Iterate through fileSecurityInfo and Access Control Entries to see if there is a match.

	return true, nil
}
