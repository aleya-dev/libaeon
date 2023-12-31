// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#include <benchmark/benchmark.h>

#define AEON_DISABLE_SSE
#include <aeon/math/mat4.h>

using namespace aeon;

static void benchmark_mat4_multiply_identity(benchmark::State &state)
{
    const auto mat1 = math::mat4::identity();
    const auto mat2 = math::mat4::identity();

    benchmark::DoNotOptimize(mat1);
    benchmark::DoNotOptimize(mat2);

    for ([[maybe_unused]] auto _ : state)
        benchmark::DoNotOptimize(mat1 * mat2);
}

BENCHMARK(benchmark_mat4_multiply_identity);

static void benchmark_mat4_multiply_translation_with_identity(benchmark::State &state)
{
    const auto mat1 = math::mat4::identity();
    const auto mat2 = math::mat4::translate({10.0f, 20.0f, 30.0f});

    benchmark::DoNotOptimize(mat1);
    benchmark::DoNotOptimize(mat2);

    for ([[maybe_unused]] auto _ : state)
        benchmark::DoNotOptimize(mat1 * mat2);
}

BENCHMARK(benchmark_mat4_multiply_translation_with_identity);

static void benchmark_mat4_multiply_rotation_with_identity(benchmark::State &state)
{
    const auto mat1 = math::mat4::identity();
    const auto mat2 = math::mat4::rotate(45.0f, {1.0f, 0.0f, 1.0f});

    benchmark::DoNotOptimize(mat1);
    benchmark::DoNotOptimize(mat2);

    for ([[maybe_unused]] auto _ : state)
        benchmark::DoNotOptimize(mat1 * mat2);
}

BENCHMARK(benchmark_mat4_multiply_rotation_with_identity);
