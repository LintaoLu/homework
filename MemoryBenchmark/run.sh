#!/bin/sh

echo "Memory Benchmark\n"
make
./MemBenchmark << MemBenchmark.txt
echo "Latency Test\n"
./Latency << Latency.txt

exit(0);
