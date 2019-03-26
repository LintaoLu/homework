#!/bin/sh

file="network-test-machine-list.txt"
count=0

while read -r line
if [ -z "$line" ]
then
  break
fi
do
  echo "ping $line..."
  echo -n "$line " >> network-test-latency.txt
  ping -c 3 $line | tail -1 | awk '{print $4}' | cut -d '/' -f 2 >> network-test-latency.txt
  echo "$line is saved!"
  count=$((count + 1))
done < $file

if (($count < 10))
then
  echo "Tested less than 10 websites!!"
  exit -1
fi

exit 0
