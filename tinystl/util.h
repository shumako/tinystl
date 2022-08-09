#ifndef TINYSTL_UTIL_H_
#define TINYSTL_UTIL_H_

// Util functions such as: move, forward, swap etc.
#include <cstddef>

#include "type_traits.h"

namespace tinystl{
    // move
    template <class T>
    typename std::remove_reference<T>::type&& move(T&& arg) noexcept {
        return static_cast<typename std::remove_reference<T>::type&&>(arg);
    }

    // forward
    template <class T>
    T&& forward(typename std::remove_reference<T>::type& arg) noexcept {
        return static_cast<T&&>(arg);
    }

    // swap
    template <class Tp>
    void swap(Tp& lhs, Tp& rhs) {
        auto tmp(tinystl::move(lhs));
        lhs = tinystl::move(rhs);
        rhs = tinystl::move(tmp);
    }

    template <class ForwardIter1, class ForwardIter2>
    ForwardIter2 swap_range(ForwardIter1 first1, ForwardIter1 last1, ForwardIter2 first2) {
        for (; first1 != last1; ++first1, (void) ++first2) tinystl::swap(*first1, *first2);
        return first2;
    }

    template <class Tp, size_t N>
    void swap(Tp(&a)[N], Tp(&b)[N]) {
        tinystl::swap_range(a, a + N, b);
    }

    // pair
    template <class Ty1, class Ty2>
    struct pair {
        typedef Ty1 first_type;
        typedef Ty2 second_type;

        first_type first;
        second_type second;

        template <class Other1 = Ty1, class Other2 = Ty2, typename = typename std::enable_if<
            std::is_default_constructible<Other1>::value &&
            std::is_default_constructible<Other2>::value, void>::type>
        constexpr pair() : first(), second() {}

        template <class U1 = Ty1, class U2 = Ty2, typename std::enable_if<
            std::is_copy_constructible<U1>::value &&
            std::is_copy_constructible<U2>::value &&
            std::is_convertible<const U1&, Ty1>::value ||
            std::is_convertible<const U2&, Ty2>::value, int>::type = 0>
        constexpr pair(const Ty1& a, const Ty2& b) : first(a), second(b) {}

        template <class U1 = Ty1, class U2 = Ty2, typename std::enable_if<
            std::is_copy_constructible<U1>::value &&
            std::is_copy_constructible<U2>::value &&
            (!std::is_convertible<const U1&, Ty1>::value &&
            !std::is_convertible<const U2&, Ty2>::value), int>::type = 0>
        explicit constexpr pair(const Ty1& a, const Ty2& b) : first(a), second(b) {}

        pair(const pair& rhs) = default;
        pair(pair&& rhs) = default;

        template <class Other1, class Other2, typename std::enable_if<
            std::is_constructible<Ty1, Other1>::value &&
            std::is_constructible<Ty2, Other2>::value &&
            std::is_convertible<Other1&&, Ty1>::value &&
            std::is_convertible<Other2&&, Ty2>::value, int>::type = 0>
        constexpr pair(Other1&& a, Other2&& b) : first(tinystl::forward<Other1>(a)), second(tinystl::forward<Other2>(b)) {}

        template <class Other1, class Other2, typename std::enable_if<
            std::is_constructible<Ty1, Other1>::value &&
            std::is_constructible<Ty2, Other2>::value &&
            (!std::is_convertible<Other1&&, Ty1>::value ||
            !std::is_convertible<Other2&&, Ty2>::value), int>::type = 0>
        explicit constexpr pair(Other1&& a, Other2&& b) : first(tinystl::forward<Other1>(a)), second(tinystl::forward<Other2>(b)) {}
    };
}

#endif