// Copyright (c) 2012-2019 Robin Degen

#include <benchmark/benchmark.h>

int main(int argc, char **argv)
{
    benchmark::Initialize(&argc, argv);
    benchmark::RunSpecifiedBenchmarks();
}
