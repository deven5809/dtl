/**
 * @file cache.hpp
 * @author Daniel Even
 * @brief This is my own implementation of a cache data structure for my own 
 * practice. The cache is implemented as a template and includes the ability to
 * set the size statically upon creation.
 * 
 */

#include <array>
#include <utility>
#include <algorithm>
#include <iostream>

namespace dtl {
template <typename T, typename U, int N>
class Cache {
public:
    // The underlying container is an array of tuples, each of which contains
    // a key-value pair which can be of separate types.
    std::array<std::pair<T, U>, N> elements; 

    /**
     * @brief Default constructor, takes no arguments.
     * 
     */
    Cache(void) {};

    /**
     * @brief Copy constructor
     * 
     * @param other - other Cache object to be copied.
     */
    Cache(const Cache& other) : elements(other.elements) {};

    /**
     * @brief Move constructor
     * 
     * @param other - other Cache object to move into this object.
     */
    Cache(const Cache&& other) : elements(other.elements) {};

    /**
     * @brief Insert a value into the cache. This counts as a read and so this
     * element will be considered the most recent. If the cache is full then the
     * element that was accessed least recently will be removed.
     * 
     * @param key - The key of the cache element.
     * @param value - The value of the cache element.
     */
    void put(const T& key, const U& value) {
        // Rotate all elements to the right to clear up the first location.
        std::rotate(elements.rbegin(), elements.rbegin() + 1, elements.rend());

        // Construct the key-value tuple in the now clear first location.
        elements[0] = std::pair<T, U>({key, value});
    }

    /**
     * @brief Insert a value into the cache. This counts as a read and so this
     * element will be considered the most recent. If the cache is full then the
     * element that was accessed least recently will be removed.
     * 
     * @param kv_pair 
     */
    void put(std::pair<T, U> kv_pair) {
        this->put(kv_pair.first, kv_pair.second);
    }

    /**
     * @brief The get() function accepts the key of a kv pair and returns the 
     * value, if possible. It will return uninitialized data and a flag stating
     * that the value was not found if this is the case. Also, reading this
     * value will count as an access.
     * 
     * @param key - This is the key of the kv pair.
     * @return std::pair<U, bool> - U is the value
     *                            - bool indicates success or failure of the
     *                              lookup.
     */
    std::pair<U, bool> get(const T& key) {
        bool success = false; // Indicates success or failure finding the key.
        U value; // The key to be returned, uninitialized.

        // Perform a linear search through the cache to attempt to find the 
        // element
        for (size_t i = 0; i < elements.size(); ++i)
        {
            if (elements[i].first == key)
            {
                success = true;
                value = elements[i].second;

                // Move the element to the front of the array.
                std::rotate(elements.begin(), elements.begin() + i,
                            elements.begin() + i + 1);
                break;
            }
        }
        
        return std::make_pair(value, success);
    }

    void print_cache(void) {
        for (auto element : elements) {
            std::cout << "Key: " << element.first << " Value: " << element.second
                << std::endl;
        }
        std::cout << std::endl;
    }

private:

};

}