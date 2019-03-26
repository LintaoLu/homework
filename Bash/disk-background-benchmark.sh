#!/bin/sh

screen -dm time dd if=/dev/zero of=ddoutput.img count=5120 bs=1048576 >> disk-benchmark-background-log.txt
