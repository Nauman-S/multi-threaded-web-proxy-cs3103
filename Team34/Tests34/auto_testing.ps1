param (
    [bool]$gui = $true,
    [string]$autotester_file = "..\Code34\Debug\AutoTester.exe",
    [int]$port = 2333
)


function has_errors {
    param (
        $output_file
    )

    $file_data = Get-Content $output_file
    if ($file_data -contains "<failed>") {
        return $true
    }
    return $false
}

[System.Collections.ArrayList]$failedTestSuites = @()
$exit_code = 0

Write-Output "AutoTester Script has begun"

if (Test-Path -Path $autotester_file -PathType Leaf) {
    Write-Output "AutoTester binary is found"
} else {
    Write-Output "AutoTester binary is not found"
    Exit 1
}


$directories = Get-ChildItem -Directory

foreach($folder in $directories) {
    $files = Get-ChildItem $folder -File
    $source_file = $null
    $query_file = $null
        foreach ($file in $files) {
            if ($file.FullName -like "*source.txt") {
                $source_file = $file.FullName
            } elseif ($file.FullName -like "*queries.txt") {
                $query_file = $file.FullName
            }
        }
    if (!$source_file) {
        Write-Output "Source file not found in folder $($folder), skipping folder"
    } elseif(!$query_file) {
        Write-Output "Query file not found int folder $($folder), skipping folder"
    } else {
        $output_folder = "$($folder.FullName)\out.xml"
        & $autotester_file $source_file $query_file $output_folder
        if (has_errors($output_folder)) {
            $failedTestSuites.Add($folder.Name)
        }
    }
}

if ($failedTestSuites.Length -gt 0) {
    $exit_code = 1
    Write-Output "FAILURES WERE FOUND IN FOLDERS:"
    for ($i = 0; $i -lt $failedTestSuites.Count ; $i++)
    {
        Write-output $failedTestSuites[$i]
    }
}

if ($gui) {
    $foundProcesses = netstat -ano | findstr :$port
    $activePortPattern = ":$port\s.+LISTENING\s+\d+$"
    $pidNumberPattern = "\d+$"

    while ($foundProcesses | Select-String -Pattern $activePortPattern -Quiet) {
    $matchesInfo = $foundProcesses | Select-String -Pattern $activePortPattern
    $firstMatch = $matchesInfo.Matches.Get(0).Value

    $pidNumber = [regex]::match($firstMatch, $pidNumberPattern).Value

    taskkill /pid $pidNumber /f
    $foundProcesses = netstat -ano | findstr :$port
    }
    Start-Process "http://localhost:2333"
    & python -m http.server $port
}

Exit $exit_code
