#!/bin/bash

home_dir="/server"
sources_dir="$home_dir/sources"
server_dir="$home_dir/server"
realm="$(echo $REALM_NAME)"
crashlogs_dir="$home_dir/crashlogs"

cur_dir="$(pwd)"
date="$(date +\%Y_\%m_\%d_\%H_\%M_\%S)"
date_dir="$(date +\%Y)/$(date +\%m)/$(date +\%d)"
cd "$sources_dir"
rev="$(git rev-parse HEAD)"
echo "rev: $rev"
cd "$cur_dir"
echo 'Running gdb'
mkdir -p $crashlogs_dir/$realm/$date_dir

echo "pwd: $(pwd)"
# DUMP CORE FROM RUNNING APPLICATION
echo "Running: gdb hellgroundcore `cat $server_dir/core.pid` --batch -x gdb.commands > $crashlogs_dir/$realm/$date_dir/crash_$date.log"
gdb hellgroundcore `cat $server_dir/core.pid` --batch -x gdb.commands > $crashlogs_dir/$realm/$date_dir/crash_$date.log

# DUMP CORE FROM core FILE
#mv core.* core
#gdb hellgroundcore core --batch -x gdb.commands > ~/crashlogs/$realm/$date_dir/crash_$date.log

# mv $crashlogs_dir/$realm/asan/asan.* $crashlogs_dir/$realm/asan/$date_dir/asan_$date.log

#echo 'Switching to crashlogs dir'
#cd $crashlogs_dir
#echo 'Adding all logs to git and commiting'
#git pull
#git add './**/*.log' '*.log'
#git commit -m "$realm - MANUAL Core dump: $date | rev: $rev"
#echo 'Pushing all data'
#git push
#echo 'All data should be pushed'
