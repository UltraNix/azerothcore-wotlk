#!/bin/bash

pushd
cd /server/sources
rev="$(git rev-parse HEAD)"
popd
realm="$(echo $REALM_NAME)"
date="$(date +\%Y_\%m_\%d_\%H_\%M_\%S)"
#    valgrindcmd="valgrind --tool=memcheck --leak-check=full --track-origins=yes --trace-children=yes --log-file=../logs/valgrind_$date.txt"
ulimit -c unlimited

export ASAN_SYMBOLIZER_PATH=/usr/bin/llvm-symbolizer
export ASAN_OPTIONS=symbolize=1,log_path=/server/crashlogs/asan,halt_on_error=false,disable_coredump=0,unmap_shadow_on_exit=1

$valgrindcmd ./hellgroundcore
rm core
rm core.*
    
date="$(date +\%Y_\%m_\%d_\%H_\%M_\%S)"
mv /server/logs/packetLog.bin /server/logs/packetLog.bin_$date

mv core.* core

if [ -f core ];
then
    date_dir="$(date +\%Y)/$(date +\%m)/$(date +\%d)"
    echo 'Running gdb'
    mkdir -p /server/crashlogs/$realm/$date_dir
    gdb hellgroundcore core --batch -x gdb.commands > /server/crashlogs/$realm/$date_dir/crash_$date.log
    rm core
    rm core.*
else
    echo 'Core file not exists. Skipping'
fi

sleep 2
