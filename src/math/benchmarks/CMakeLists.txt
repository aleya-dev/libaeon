# Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

include(Benchmark)

add_benchmark_suite(
    NO_BENCHMARK_MAIN
    AUTO_GLOB_SOURCES
    TARGET benchmark_libaeon_math
    INCLUDES
        ${CMAKE_CURRENT_BINARY_DIR}
    LIBRARIES aeon_math
    FOLDER dep/libaeon/benchmarks
)
