/**
 * @file cache.hpp
 * @author Daniel Even
 * @brief This is my own implementation of a cache data structure for my own 
 * practice. The cache is implemented as a template and includes the ability to
 * set the size statically upon creation.
 * 
 */

 #include <array>

template <typename T, int N>
class Cache {
public:
    std::array<T, N> arr;

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
    Cache(const Cache& other) : arr(other.arr) {};

    /**
     * @brief Move constructor
     * 
     * @param other - other Cache object to move into this object.
     */
    Cache(const Cache&& other) : arr(other.arr) {};

    

private:

};