function Find-CMake {
    Get-Command cmake -ErrorAction SilentlyContinue | Out-Null 
    $cmakeExists = $?
    if (!($cmakeExists)) {
        Write-Output "CMake is not installed on this machine..."
        return $cmakeExists
    }
    return $cmakeExists
}

function Install-CMake {
    param {
        $cmakeMissing
    }
    if ($cmakeMissing) {
        Write-Ouput "CMake already exists..."
        return
    }
}

$res = Find-CMake
Write-Output $res

# Given it is installed create build directory from CMakeListsCache.txt
function Initialize_Build {
    param (
        $cmakeFound
    )
    if (($cmakeFound)) {

    }
}

# Use build to create .exe and return current path

# Add the executable to bin PATH