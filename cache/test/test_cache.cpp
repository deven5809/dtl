#include <catch2/catch_test_macros.hpp>
#include "cache.hpp"
#include <string>
#include <iostream>

template <int N>
void load_cache(dtl::Cache<int, int, N>& c, int num_elements) {
    for (int i = 0; i < num_elements * 2; i+=2) {
        c.put(i, i + 1);
    }
}

TEST_CASE("Test Basic Functions") {
    dtl::Cache<std::string, std::string, 3> cache;
    cache.put("key", "value");

    const auto [lookup_value, success] = cache.get("key");
    REQUIRE(success);
    REQUIRE(lookup_value == "value");
}

TEST_CASE("Test FIFO") {
    // Create our cache of size 3.
    dtl::Cache<int, int, 3> cache;

    // Add 4 elements. This function will load in n pairs of (a, a + 1)
    load_cache(cache, 4);

    // Check for all elements. The first element (0, 1) should have been kicked
    // out.
    {
        const auto [lookup_value, success] = cache.get(0);
        REQUIRE(!success);
    }
    {
        auto [lookup_value, success] = cache.get(2);
        REQUIRE(success);
        REQUIRE(lookup_value == 3);
    }
    {
        auto [lookup_value, success] = cache.get(4);
        REQUIRE(success);
        REQUIRE(lookup_value == 5);
    }
    {
        auto [lookup_value, success] = cache.get(6);
        REQUIRE(success);
        REQUIRE(lookup_value == 7);
    }
    
}

TEST_CASE("Test FIFO with accesses") {
    // Create our cache of size 3.
    dtl::Cache<int, int, 3> cache;

    // Add 3 elements. This function will load in n pairs of (a, a + 1)
    load_cache(cache, 3);

    // Access pair (0, 1). This should bump it up to the most current slot.
    {
        const auto [lookup_value, success] = cache.get(0);
        REQUIRE(success);
        REQUIRE(lookup_value == 1);
    }

    // Insert a 4th element, kicking out (2, 3).
    cache.print_cache();
    cache.put(6, 7);
    cache.print_cache();

    // Check for all elements. The second element (0, 1) should have been kicked
    // out.
    {
        // Pair (2, 3) should no longer be present.
        const auto [lookup_value, success] = cache.get(2);
        cache.print_cache();
        REQUIRE(!success);
    }
    {
        auto [lookup_value, success] = cache.get(0);
        REQUIRE(success);
        REQUIRE(lookup_value == 1);
    }
    {
        auto [lookup_value, success] = cache.get(4);
        REQUIRE(success);
        REQUIRE(lookup_value == 5);
    }
    {
        auto [lookup_value, success] = cache.get(6);
        REQUIRE(success);
        REQUIRE(lookup_value == 7);
    }
    
}