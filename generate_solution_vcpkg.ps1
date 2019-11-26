
# create build folder
if(!(test-path -path build ))
{
    new-item build -itemtype directory
}

set-location build

$vcpkg_dir = (get-item -path ".\" -verbose).FullName + "\vcpkg"
if (Test-Path $env:VCPKG_ROOT)
{
    $vcpkg_dir = $env:VCPKG_ROOT
}

if(!(test-path -path $vcpkg_dir ))
{
    # clone vcpkg repository
    git clone https://github.com/Microsoft/vcpkg.git vcpkg

    invoke-expression "$vcpkg_dir\bootstrap-vcpkg.bat"
}

invoke-expression "$vcpkg_dir\vcpkg install boost openssl libmariadb --triplet x64-windows --featurepackages"

if( test-path -path CMakeCache.txt )
{
    remove-item CMakeCache.txt
}

$generator = "Visual Studio 15 Win64"
$toolchain = "$vcpkg_dir/scripts/buildsystems/vcpkg.cmake"

$mysql_include_dir = "$vcpkg_dir/installed/x64-windows/include/mysql/"
$mysql_library = "$vcpkg_dir/installed/x64-windows/lib/libmariadb.lib"

$boost_root_dir = "$vcpkg_dir/installed/x64-windows"

Write-Host "Executing: cmake -G `"$generator`" -DCMAKE_TOOLCHAIN_FILE=`"$toolchain`" -DMYSQL_INCLUDE_DIR=`"$mysql_include_dir`" -DMYSQL_LIBRARY=`"$mysql_library`" -DBOOST_ROOT=`"$boost_root_dir`" ../"
& cmake -G "$generator" -DCMAKE_TOOLCHAIN_FILE="$toolchain" -DMYSQL_INCLUDE_DIR="$mysql_include_dir" -DMYSQL_LIBRARY="$mysql_library" -DBOOST_ROOT="$boost_root_dir" ../ 