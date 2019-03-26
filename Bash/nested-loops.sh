#!/bin/sh

if [ -z "$1" ] || [ -z "$2" ] || [ -z "$3" ];
then
  echo "Parameter missing! Need 3!"
  exit -1
fi

if [[ ! $1 =~ ^-?[0-9]+$ ]] || [[ ! $2 =~ ^-?[0-9]+$ ]] || [[ ! $3 =~ ^-?[0-9]+$ ]]
then
  echo "All parameters must be integers!"
  exit -1
fi

for (( I=$(($1)); I>0; I-=1 ))
do
  for (( J=$(($2)); J>0; J-=1 ))
  do
    for (( K=$(($3)); K>0; K-=1 ))
    do
      echo "I="$I "J="$J "K="$K
    done
  done  
done

exit 0;


