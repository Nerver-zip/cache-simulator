#pragma once

#include <iostream>
#include <cstdlib>
#include <utility>
#include "../../src/caches/ICache.h"
#include <chrono>

inline auto test_start_time = std::chrono::steady_clock::now();

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
// Logging helpers
// ======================================================

#define PRINT_FAIL(msg) \
    std::cerr << COLOR_RED << "[FAIL] " << COLOR_RESET << msg << "\n"

#define PRINT_PASS(msg) \
    std::cout << COLOR_GREEN << "[PASS] " << COLOR_RESET << msg << "\n"

#define PRINT_INFO(msg) \
    std::cout << COLOR_BLUE << "[INFO] " << COLOR_RESET << msg << "\n"

// ======================================================
// Pair printing
// ======================================================

template<typename A, typename B>
inline std::ostream&
operator<<(std::ostream& os, const std::pair<A, B>& p)
{
    return os << "(" << p.first << ", " << p.second << ")";
}

// ======================================================
// Cache config printing
// ======================================================

inline std::ostream& operator<<(std::ostream& os, const CacheConfig& c)
{
    return os << "{nsets=" << c.nsets
              << ", assoc=" << c.assoc
              << ", bsize=" << c.bsize << "}";
}

// ======================================================
// Variadic debug printer
// ======================================================

inline void print_args_impl(int) {}

template <typename T, typename... Rest>
inline void print_args_impl(int i, const T& first, const Rest&... rest)
{
    std::cerr << "  arg[" << i << "]: " << first << "\n";
    print_args_impl(i + 1, rest...);
}

template <typename... Args>
inline void print_args(const Args&... args)
{
    print_args_impl(0, args...);
}

// ======================================================
// ASSERT_EQUAL
// ======================================================

#define ASSERT_EQUAL(a, b, ...) do { \
    asserts++; \
    auto _a = (a); \
    auto _b = (b); \
    \
    if (!(_a == _b)) { \
        PRINT_FAIL(#a " == " #b); \
        std::cerr << "  expected: " << _a << "\n"; \
        std::cerr << "  got:      " << _b << "\n"; \
        std::cerr << "  location: " << __FILE__ << ":" << __LINE__ << "\n"; \
        print_args(__VA_ARGS__); \
        std::exit(1); \
    } \
    \
    asserts_passed++; \
    PRINT_PASS(#a " == " #b); \
} while (0)

// ---------------- VERBOSE ----------------

#define ASSERT_EQUAL_VERBOSE(a, b, ...) do { \
    asserts++; \
    auto _a = (a); \
    auto _b = (b); \
    PRINT_INFO("ASSERT_EQUAL " #a " == " #b); \
    print_args(__VA_ARGS__); \
    \
    if (!(_a == _b)) { \
        PRINT_FAIL(#a " == " #b); \
        std::cerr << "  expected: " << _a << "\n"; \
        std::cerr << "  got:      " << _b << "\n"; \
        std::cerr << "  location: " << __FILE__ << ":" << __LINE__ << "\n"; \
        std::exit(1); \
    } \
    \
    asserts_passed++; \
    PRINT_PASS(#a " == " #b); \
} while (0)

// ---------------- SILENT ---------------- 

#define ASSERT_EQUAL_SILENT(a, b, ...) do { \
    asserts++; \
    auto _a = (a); \
    auto _b = (b); \
    \
    if (!(_a == _b)) { \
        PRINT_FAIL(#a " == " #b); \
        std::cerr << "  expected: " << _a << "\n"; \
        std::cerr << "  got:      " << _b << "\n"; \
        std::cerr << "  location: " << __FILE__ << ":" << __LINE__ << "\n"; \
        print_args(__VA_ARGS__); \
        std::exit(1); \
    } \
    \
    asserts_passed++; \
} while (0)

// ======================================================
// ASSERT_NOT_EQUAL
// ======================================================

#define ASSERT_NOT_EQUAL(a, b, ...) do { \
    asserts++; \
    auto _a = (a); \
    auto _b = (b); \
    \
    if (_a == _b) { \
        PRINT_FAIL(#a " != " #b); \
        std::cerr << "  both values: " << _a << "\n"; \
        std::cerr << "  location: " << __FILE__ << ":" << __LINE__ << "\n"; \
        print_args(__VA_ARGS__); \
        std::exit(1); \
    } \
    \
    asserts_passed++; \
    PRINT_PASS(#a " != " #b); \
} while (0)

// ---------------- VERBOSE ----------------

#define ASSERT_NOT_EQUAL_VERBOSE(a, b, ...) do { \
    asserts++; \
    auto _a = (a); \
    auto _b = (b); \
    PRINT_INFO("ASSERT_NOT_EQUAL " #a " != " #b); \
    print_args(__VA_ARGS__); \
    \
    if (_a == _b) { \
        PRINT_FAIL(#a " != " #b); \
        std::cerr << "  both values: " << _a << "\n"; \
        std::cerr << "  location: " << __FILE__ << ":" << __LINE__ << "\n"; \
        std::exit(1); \
    } \
    \
    asserts_passed++; \
    PRINT_PASS(#a " != " #b); \
} while (0)

// ---------------- SILENT ---------------- 

#define ASSERT_NOT_EQUAL_SILENT(a, b, ...) do { \
    asserts++; \
    auto _a = (a); \
    auto _b = (b); \
    \
    if (_a == _b) { \
        PRINT_FAIL(#a " != " #b); \
        std::cerr << "  both values: " << _a << "\n"; \
        std::cerr << "  location: " << __FILE__ << ":" << __LINE__ << "\n"; \
        print_args(__VA_ARGS__); \
        std::exit(1); \
    } \
    \
    asserts_passed++; \
} while (0)

// ======================================================
// ASSERT_TRUE
// ======================================================

#define ASSERT_TRUE(expr, ...) do { \
    asserts++; \
    if (!(expr)) { \
        PRINT_FAIL("expected true: " #expr); \
        std::cerr << "  location: " << __FILE__ << ":" << __LINE__ << "\n"; \
        print_args(__VA_ARGS__); \
        std::exit(1); \
    } \
    asserts_passed++; \
    PRINT_PASS(#expr); \
} while (0)

// ---------------- VERBOSE ----------------

#define ASSERT_TRUE_VERBOSE(expr, ...) do { \
    asserts++; \
    PRINT_INFO("ASSERT_TRUE " #expr); \
    print_args(__VA_ARGS__); \
    if (!(expr)) { \
        PRINT_FAIL("expected true: " #expr); \
        std::cerr << "  location: " << __FILE__ << ":" << __LINE__ << "\n"; \
        std::exit(1); \
    } \
    asserts_passed++; \
    PRINT_PASS(#expr); \
} while (0)

// ---------------- SILENT ---------------- 

#define ASSERT_TRUE_SILENT(expr, ...) do { \
    asserts++; \
    if (!(expr)) { \
        PRINT_FAIL("expected true: " #expr); \
        std::cerr << "  location: " << __FILE__ << ":" << __LINE__ << "\n"; \
        print_args(__VA_ARGS__); \
        std::exit(1); \
    } \
    asserts_passed++; \
} while (0)

// ======================================================
// ASSERT_FALSE
// ======================================================

#define ASSERT_FALSE(expr, ...) do { \
    asserts++; \
    if (expr) { \
        PRINT_FAIL("expected false: " #expr); \
        std::cerr << "  location: " << __FILE__ << ":" << __LINE__ << "\n"; \
        print_args(__VA_ARGS__); \
        std::exit(1); \
    } \
    asserts_passed++; \
    PRINT_PASS("!" #expr); \
} while (0)

// ---------------- VERBOSE ----------------

#define ASSERT_FALSE_VERBOSE(expr, ...) do { \
    asserts++; \
    PRINT_INFO("ASSERT_FALSE " #expr); \
    print_args(__VA_ARGS__); \
    if (expr) { \
        PRINT_FAIL("expected false: " #expr); \
        std::cerr << "  location: " << __FILE__ << ":" << __LINE__ << "\n"; \
        std::exit(1); \
    } \
    asserts_passed++; \
    PRINT_PASS("!" #expr); \
} while (0)

// ---------------- SILENT ---------------- 

#define ASSERT_FALSE_SILENT(expr, ...) do { \
    asserts++; \
    if (expr) { \
        PRINT_FAIL("expected false: " #expr); \
        std::cerr << "  location: " << __FILE__ << ":" << __LINE__ << "\n"; \
        print_args(__VA_ARGS__); \
        std::exit(1); \
    } \
    asserts_passed++; \
} while (0)

// ======================================================
// ASSERT_ANY_THROW
// ======================================================

#define ASSERT_ANY_THROW(expr, ...) do { \
    asserts++; \
    bool _thrown = false; \
    std::string _msg; \
    \
    try { \
        (expr); \
    } catch (const std::exception& e) { \
        _thrown = true; \
        _msg = e.what(); \
    } catch (...) { \
        _thrown = true; \
        _msg = "<non-std exception>"; \
    } \
    \
    if (!_thrown) { \
        PRINT_FAIL("expected exception in: " #expr); \
        std::cerr << "  location: " << __FILE__ << ":" << __LINE__ << "\n"; \
        print_args(__VA_ARGS__); \
        std::exit(1); \
    } \
    \
    asserts_passed++; \
    PRINT_PASS("threw exception in " #expr); \
    std::cout << "  message: " << _msg << "\n"; \
} while (0)

// ---------------- VERBOSE ----------------

#define ASSERT_ANY_THROW_VERBOSE(expr, ...) do { \
    asserts++; \
    PRINT_INFO("ASSERT_ANY_THROW " #expr); \
    print_args(__VA_ARGS__); \
    \
    bool _thrown = false; \
    std::string _msg; \
    \
    try { \
        (expr); \
    } catch (const std::exception& e) { \
        _thrown = true; \
        _msg = e.what(); \
    } catch (...) { \
        _thrown = true; \
        _msg = "<non-std exception>"; \
    } \
    \
    if (!_thrown) { \
        PRINT_FAIL("expected exception in: " #expr); \
        std::cerr << "  location: " << __FILE__ << ":" << __LINE__ << "\n"; \
        std::exit(1); \
    } \
    \
    asserts_passed++; \
    PRINT_PASS("threw exception in " #expr); \
    std::cout << "  message: " << _msg << "\n"; \
} while (0)

// ---------------- SILENT ---------------- 

#define ASSERT_ANY_THROW_SILENT(expr, ...) do { \
    asserts++; \
    bool _thrown = false; \
    try { (expr); } catch (...) { _thrown = true; } \
    \
    if (!_thrown) { \
        PRINT_FAIL("expected exception in: " #expr); \
        std::cerr << "  location: " << __FILE__ << ":" << __LINE__ << "\n"; \
        print_args(__VA_ARGS__); \
        std::exit(1); \
    } \
    \
    asserts_passed++; \
} while (0)

// ======================================================
// ASSERT_NO_THROW
// ======================================================

#define ASSERT_NO_THROW(expr, ...) do { \
    asserts++; \
    bool _thrown = false; \
    \
    try { (expr); } catch (...) { _thrown = true; } \
    \
    if (_thrown) { \
        PRINT_FAIL("unexpected exception in: " #expr); \
        std::cerr << "  location: " << __FILE__ << ":" << __LINE__ << "\n"; \
        print_args(__VA_ARGS__); \
        std::exit(1); \
    } \
    \
    asserts_passed++; \
    PRINT_PASS("no exception in " #expr); \
} while (0)

// ---------------- VERBOSE ----------------

#define ASSERT_NO_THROW_VERBOSE(expr, ...) do { \
    asserts++; \
    PRINT_INFO("ASSERT_NO_THROW " #expr); \
    print_args(__VA_ARGS__); \
    bool _thrown = false; \
    try { (expr); } catch (...) { _thrown = true; } \
    if (_thrown) { \
        PRINT_FAIL("unexpected exception in: " #expr); \
        std::cerr << "  location: " << __FILE__ << ":" << __LINE__ << "\n"; \
        std::exit(1); \
    } \
    asserts_passed++; \
    PRINT_PASS("no exception in " #expr); \
} while (0)

// ---------------- SILENT ---------------- 

#define ASSERT_NO_THROW_SILENT(expr, ...) do { \
    asserts++; \
    bool _thrown = false; \
    try { (expr); } catch (...) { _thrown = true; } \
    \
    if (_thrown) { \
        PRINT_FAIL("unexpected exception in: " #expr); \
        std::cerr << "  location: " << __FILE__ << ":" << __LINE__ << "\n"; \
        print_args(__VA_ARGS__); \
        std::exit(1); \
    } \
    \
    asserts_passed++; \
} while (0)

// ======================================================
// TEST RUNNER
// ======================================================

#define RUN_TEST(name) do { \
    tests++; \
    std::cout << COLOR_BLUE << "\n[RUNNING] " << COLOR_RESET << #name << "\n"; \
    \
    int _asserts_before = asserts; \
    int _passed_before = asserts_passed; \
    \
    name(); \
    \
    int _asserts_after = asserts; \
    int _passed_after = asserts_passed; \
    \
    int _delta_asserts = _asserts_after - _asserts_before; \
    int _delta_passed = _passed_after - _passed_before; \
    \
    passed++; \
    std::cout << COLOR_GREEN << "[OK] " << COLOR_RESET << #name \
              << " | asserts: " << _delta_passed \
              << "/" << _delta_asserts << "\n"; \
} while (0)


// ======================================================
// SUMMARY
// ======================================================

#define TEST_SUMMARY() do { \
    auto _end = std::chrono::steady_clock::now(); \
    auto _elapsed = std::chrono::duration_cast<std::chrono::milliseconds>( \
        _end - test_start_time \
    ); \
    \
    std::cout << COLOR_YELLOW \
        << "\n========== TEST SUMMARY ==========\n" \
        << COLOR_RESET \
        << passed << "/" << tests << " tests passed\n" \
        << asserts_passed << "/" << asserts << " assertions passed\n" \
        << "time: " << _elapsed.count() << " ms\n"; \
} while (0)
