// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#include <benchmark/benchmark.h>

int main(int argc, char **argv)
{
    benchmark::Initialize(&argc, argv);
    benchmark::RunSpecifiedBenchmarks();
    return 0;
}
