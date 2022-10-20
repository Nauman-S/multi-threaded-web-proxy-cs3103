param (
    [bool]$gui = $true,
    [string]$autotester_file = "..\Code34\Debug\AutoTester.exe"
)

Write-Output "AutoTester Script has begun"
$condition = Test-Path -Path $autotester_file -PathType Leaf
$port = 2333

if ($condition) {
    Write-Output "AutoTester binary is found"
} else {
    Write-Output "AutoTester binary is not found"
    Exit
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
    }
}

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

if ($gui) {
    Start-Process "http://localhost:2333"
    & python -m http.server $port
}
