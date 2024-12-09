//
// Created by Mac on 24-12-9.
//

// gtest benchmark test for jianqiao_stl
#include <benchmark/benchmark.h>
#include <jianqiao/jianqiao_function.hpp>

static void BM_identity(benchmark::State &state) {
    Jianqiao::identity<int> identity;
    for (auto _ : state) {
        benchmark::DoNotOptimize(identity(1));
    }
}

BENCHMARK(BM_identity);

static void BM_negate(benchmark::State &state) {
    Jianqiao::negate<int> negate;
    for (auto _ : state) {
        benchmark::DoNotOptimize(negate(1));
    }
}

BENCHMARK(BM_negate);

static void BM_plus(benchmark::State &state) {
    Jianqiao::plus<int> plus;
    for (auto _ : state) {
        benchmark::DoNotOptimize(plus(1, 2));
    }
}

BENCHMARK(BM_plus);

static void BM_minus(benchmark::State &state) {
    Jianqiao::minus<int> minus;
    for (auto _ : state) {
        benchmark::DoNotOptimize(minus(1, 2));
    }
}

BENCHMARK(BM_minus);

static void BM_multiplies(benchmark::State &state) {
    Jianqiao::multiplies<int> multiplies;
    for (auto _ : state) {
        benchmark::DoNotOptimize(multiplies(1, 2));
    }
}

BENCHMARK(BM_multiplies);

static void BM_divides(benchmark::State &state) {
    Jianqiao::divides<int> divides;
    for (auto _ : state) {
        benchmark::DoNotOptimize(divides(1, 2));
    }
}

BENCHMARK(BM_divides);

static void BM_modulus(benchmark::State &state) {
    Jianqiao::modulus<int> modulus;
    for (auto _ : state) {
        benchmark::DoNotOptimize(modulus(1, 2));
    }
}

BENCHMARK(BM_modulus);

static void BM_logical_and(benchmark::State &state) {
    Jianqiao::logical_and<int> logical_and;
    for (auto _ : state) {
        benchmark::DoNotOptimize(logical_and(1, 2));
    }
}

BENCHMARK(BM_logical_and);

static void BM_logical_or(benchmark::State &state) {
    Jianqiao::logical_or<int> logical_or;
    for (auto _ : state) {
        benchmark::DoNotOptimize(logical_or(1, 2));
    }
}

BENCHMARK(BM_logical_or);

static void BM_logical_not(benchmark::State &state) {
    Jianqiao::logical_not<int> logical_not;
    for (auto _ : state) {
        benchmark::DoNotOptimize(logical_not(1));
    }
}

BENCHMARK(BM_logical_not);

BENCHMARK_MAIN();

