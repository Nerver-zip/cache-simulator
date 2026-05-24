#pragma once

#include <iostream>
#include <cstdlib>
#include <utility>

// ======================================================
// Counters
// ======================================================

inline int tests = 0;
inline int passed = 0;

inline int asserts = 0;
inline int asserts_passed = 0;

// ======================================================
// ANSI Colors
// ======================================================

#define COLOR_RED     "\033[31m"
#define COLOR_GREEN   "\033[32m"
#define COLOR_YELLOW  "\033[33m"
#define COLOR_BLUE    "\033[34m"
#define COLOR_RESET   "\033[0m"

// ======================================================
// Pair printing
// ======================================================

template<typename A, typename B>
inline std::ostream&
operator<<(std::ostream& os,
           const std::pair<A, B>& p)
{
    return os
        << "("
        << p.first
        << ", "
        << p.second
        << ")";
}

// ======================================================
// Assertions
// ======================================================

#define ASSERT_EQUAL(a, b) do { \
    asserts++; \
    auto _a = (a); \
    auto _b = (b); \
    \
    if (!(_a == _b)) { \
        std::cerr \
            << COLOR_RED \
            << "[FAIL] " \
            << COLOR_RESET \
            << #a << " == " << #b \
            << "\n" \
            << "  expected: " << _a << "\n" \
            << "  got:      " << _b << "\n" \
            << "  location: " \
            << __FILE__ << ":" << __LINE__ \
            << "\n"; \
        std::exit(1); \
    } \
    \
    asserts_passed++; \
    std::cout \
        << COLOR_GREEN \
        << "[PASS] " \
        << COLOR_RESET \
        << #a << " == " << #b << "\n"; \
} while (0)

#define ASSERT_NOT_EQUAL(a, b) do { \
    asserts++; \
    auto _a = (a); \
    auto _b = (b); \
    \
    if (_a == _b) { \
        std::cerr \
            << COLOR_RED \
            << "[FAIL] " \
            << COLOR_RESET \
            << #a << " != " << #b \
            << "\n" \
            << "  both values: " << _a << "\n" \
            << "  location: " \
            << __FILE__ << ":" << __LINE__ \
            << "\n"; \
        std::exit(1); \
    } \
    \
    asserts_passed++; \
    std::cout \
        << COLOR_GREEN \
        << "[PASS] " \
        << COLOR_RESET \
        << #a << " != " << #b << "\n"; \
} while (0)

#define ASSERT_TRUE(expr) do { \
    asserts++; \
    \
    if (!(expr)) { \
        std::cerr \
            << COLOR_RED \
            << "[FAIL] " \
            << COLOR_RESET \
            << "expected true: " << #expr \
            << "\n" \
            << "  location: " \
            << __FILE__ << ":" << __LINE__ \
            << "\n"; \
        std::exit(1); \
    } \
    \
    asserts_passed++; \
    std::cout \
        << COLOR_GREEN \
        << "[PASS] " \
        << COLOR_RESET \
        << #expr << "\n"; \
} while (0)

#define ASSERT_FALSE(expr) do { \
    asserts++; \
    \
    if (expr) { \
        std::cerr \
            << COLOR_RED \
            << "[FAIL] " \
            << COLOR_RESET \
            << "expected false: " << #expr \
            << "\n" \
            << "  location: " \
            << __FILE__ << ":" << __LINE__ \
            << "\n"; \
        std::exit(1); \
    } \
    \
    asserts_passed++; \
    std::cout \
        << COLOR_GREEN \
        << "[PASS] " \
        << COLOR_RESET \
        << "!" << #expr << "\n"; \
} while (0)

// ======================================================
// Test runner
// ======================================================

#define TEST(name) void name()

#define RUN_TEST(name) do { \
    tests++; \
    \
    std::cout \
        << COLOR_BLUE \
        << "\n[RUNNING] " \
        << COLOR_RESET \
        << #name << "\n"; \
    \
    name(); \
    \
    passed++; \
    \
    std::cout \
        << COLOR_GREEN \
        << "[OK] " \
        << COLOR_RESET \
        << #name << "\n"; \
} while (0)

// ======================================================
// Summary
// ======================================================

#define TEST_SUMMARY() do { \
    std::cout \
        << COLOR_YELLOW \
        << "\n========== TEST SUMMARY ==========\n" \
        << COLOR_RESET \
        << passed << "/" << tests \
        << " tests passed\n" \
        << asserts_passed << "/" << asserts \
        << " assertions passed\n"; \
} while (0)
