#ifndef TINYSTL_FUNCTIONAL_H_
#define TINYSTL_FUNCTIONAL_H_

#include <cstddef>

namespace tinystl{
    // unary function
    template <class Arg, class Result>
    struct unary_function {
        typedef Arg argument_type;
        typedef Result result_type;
    };

    // binary function
    template <class Arg1, class Arg2, class Result>
    struct binary_function {
        typedef Arg1 first_argument_type;
        typedef Arg2 second_argument_type;
        typedef Result result_type;
    };

    // operators
    template <class T>
    struct plus : public binary_function<T, T, T> {
        T operator()(const T& x, const T& y) const { return x + y; }
    };
    template <class T>
    struct minus : public binary_function<T, T, T> {
        T operator()(const T& x, const T& y) const { return x - y; }
    };
    template <class T>
    struct multiplies : public binary_function<T, T, T> {
        T operator()(const T& x, const T& y) const { return x * y; }
    };
    template <class T>
    struct divides : public binary_function<T, T, T> {
        T operator()(const T& x, const T& y) const { return x / y; }
    };
    template <class T>
    struct modulus : public binary_function<T, T, T> {
        T operator()(const T& x, const T& y) const { return x % y; }
    };
    template <class T>
    struct negate : public unary_function<T, T> {
        T operator()(const T& x) const { return -x; }
    };

    template <class T> T identity_element(plus<T>) { return T(0); }
    template <class T> T identity_element(multiplies<T>) { return T(1); }

    template <class T>
    struct equal_to : public binary_function<T, T, bool> {
        bool operator()(const T& x, const T& y) const { return x == y; }
    };
    template <class T>
    struct not_equal_to : public binary_function<T, T, bool> {
        bool operator()(const T& x, const T& y) const { return x != y; }
    };
    template <class T>
    struct greater : public binary_function<T, T, bool> {
        bool operator()(const T& x, const T& y) const { return x > y; }
    };
    template <class T>
    struct less : public binary_function<T, T, bool> {
        bool operator()(const T& x, const T& y) const { return x < y; }
    };
    template <class T>
    struct greater_equal : public binary_function<T, T, bool> {
        bool operator()(const T& x, const T& y) const { return x >= y; }
    };
    template <class T>
    struct less_equal : public binary_function<T, T, bool> {
        bool operator()(const T& x, const T& y) const { return x <= y; }
    };
    template <class T>
    struct logical_and : public binary_function<T, T, bool> {
        bool operator()(const T& x, const T& y) const { return x && y; }
    };
    template <class T>
    struct logical_or : public binary_function<T, T, bool> {
        bool operator()(const T& x, const T& y) const { return x || y; }
    };
    template <class T>
    struct logical_not : public unary_function<T, bool> {
        bool operator()(const T& x) const { return !x; }
    };

    template <class T>
    struct identity : public unary_function<T, bool> {
        const T& operator()(const T& x) const { return x; }
    };

    template <class Pair>
    struct selectfirst : public unary_function<Pair, typename Pair::first_type> {
        const typename Pair::first_type& operator()(const Pair& x) const { return x.first; }
    };
    template <class Pair>
    struct selectsecond : public unary_function<Pair, typename Pair::second_type> {
        const typename Pair::second_type& operator()(const Pair& x) const { return x.second; }
    };

    // project function
    template <class Arg1, class Arg2>
    struct projectfirst : public binary_function<Arg1, Arg2, Arg1> {
        Arg1 operator()(const Arg1& x, const Arg2&) const { return x; }
    };
    template <class Arg1, class Arg2>
    struct projectsecond : public binary_function<Arg1, Arg2, Arg1> {
        Arg2 operator()(const Arg1&, const Arg2& y) const { return y; }
    };


    // hash function
    template <class Key> struct hash {};
    template <class T>
    struct hash<T*> { size_t operator()(T* p) const noexcept { return reinterpret_cast<size_t>(p); }};

    #define TINYSTL_TRIVIAL_HASH_FCN(Type) template <> struct hash<Type> { size_t operator()(Type val) const noexcept { return static_cast<size_t>(val); } };

    TINYSTL_TRIVIAL_HASH_FCN(bool)

    TINYSTL_TRIVIAL_HASH_FCN(char)

    TINYSTL_TRIVIAL_HASH_FCN(signed char)

    TINYSTL_TRIVIAL_HASH_FCN(unsigned char)

    TINYSTL_TRIVIAL_HASH_FCN(wchar_t)

    TINYSTL_TRIVIAL_HASH_FCN(char16_t)

    TINYSTL_TRIVIAL_HASH_FCN(char32_t)

    TINYSTL_TRIVIAL_HASH_FCN(short)

    TINYSTL_TRIVIAL_HASH_FCN(unsigned short)

    TINYSTL_TRIVIAL_HASH_FCN(int)

    TINYSTL_TRIVIAL_HASH_FCN(unsigned int)

    TINYSTL_TRIVIAL_HASH_FCN(long)

    TINYSTL_TRIVIAL_HASH_FCN(unsigned long)

    TINYSTL_TRIVIAL_HASH_FCN(long long)

    TINYSTL_TRIVIAL_HASH_FCN(unsigned long long)

    #undef TINYSTL_TRIVIAL_HASH_FCN

    inline size_t bitwise_hash(const unsigned char* first, size_t count) {
    #if (_MSC_VER && _WIN64) || ((__GNUC__ || __clang__) && __SIZEOF_POINTER__ == 8))
        const size_t fnv_offset = 14695981039346656037ull;
        const size_t fnv_prime = 1099511628211ull;
    #else
        const size_t fnv_offset = 2166136261u;
        const size_t fnv_prime = 16777619u;
    #endif
        size_t result = fnv_offset;
        for (size_t i = 0; i < count; ++i) {
            result ^= (size_t)first[i];
            result *= fnv_prime;
        }
        return result;
    }

    template <>
    struct hash<float> { size_t operator()(const float& val) { return val == 0.0f ? 0 : bitwise_hash((const unsigned char *)&val,sizeof(float));}};
    template <>
    struct hash<double> { size_t operator()(const double& val) { return val == 0.0f ? 0 : bitwise_hash((const unsigned char *)&val, sizeof(double));}};
    template <>
    struct hash<long double> { size_t operator()(const long double& val) { return val == 0.0f ? 0 : bitwise_hash((const unsigned char *)&val,sizeof(long double));}};
}

#endif
