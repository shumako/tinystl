#ifndef TINYSTL_TYPE_TRAITS_H_
#define TINYSTL_TYPE_TRAITS_H_

#include <type_traits>
namespace tinystl{
    template <class T, T v>
    struct integral_constant { static constexpr T value = v; };

    template <bool b>
    using bool_constant = integral_constant<bool, b>;

    typedef bool_constant<true> true_type;
    typedef bool_constant<false> false_type;

    template <class T1, class T2> struct pair;
    template <class T>
    struct is_pair : tinystl::false_type{};
    template <class T1, class T2>
    struct is_pair<tinystl::pair<T1, T2>> : tinystl::true_type{};
}

#endif