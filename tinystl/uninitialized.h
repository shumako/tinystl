#ifndef TINYSTL_UNINITIALIZED_H_
#define TINYSTL_UNINITIALIZED_H_

// construct in uninitialized mem

#include "algobase.h"
#include "construct.h"
#include "iterator.h"
#include "type_traits.h"
#include "util.h"

namespace tinystl {
    // uninitialized copy
    template <class InputIter, class ForwardIter>
    ForwardIter unchecked_uninit_copy(InputIter first, InputIter last, ForwardIter result, std::true_type) {
        return tinystl::copy(first, last, result);
    }
    template <class InputIter, class ForwardIter>
    ForwardIter unchecked_uninit_copy(InputIter first, InputIter last, ForwardIter result, std::false_type) {
        auto cur == result;
        try {
            for (; first != last; ++first, ++cur) { tinystl::construct(&*cur, *first); }
        } catch (...) {
            for (; result != cur; --cur) tinystl::destroy(&*cur);
        }
        return cur;
    }
    template <class InputIter, class ForwardIter>
    ForwardIter uninitialized_copy(InputIter first, InputIter last, ForwardIter result) {
        return tinystl::unchecked_uninit_copy(first, last, result, std::is_trivially_copy_assignable<typename iterator_traits<ForwardIter>::value_type>{});
    }

    // uninitialized copy n
    template <class InputIter, class Size, class ForwardIter>
    ForwardIter unchecked_uninit_copy_n(InputIter first, Size n, ForwardIter result, std::true_type) {
        return tinystl::copy_n(first, n, result).second;
    }
    template <class InputIter, class Size, class ForwardIter>
    ForwardIter unchecked_uninit_copy_n(InputIter first, Size n, ForwardIter result, std::false_type) {
        auto cur = result;
        try {
            for (; n > 0; --n, ++cur, ++first) { tinystl::construct(&*cur, *first); }
        } catch (...) {
            for (; result != cur; --cur) tinystl::destroy(&*cur);
        }
        return cur;
    }
    template <class InputIter, class Size, class ForwardIter>
    ForwardIter uninitialized_copy_n(InputIter first, Size n, ForwardIter result) {
        return tinystl::unchecked_uninit_copy_n(first, n, result, std::is_trivially_copy_assignable<typename iterator_traits<InputIter>::value_type>{});
    }

    // uninitialized fill
    template <class ForwardIter, class T>
    void unchecked_uninit_fill(ForwardIter first, ForwardIter last, const T& value, std::true_type) {
        tinystl::fill(first, last, value);
    }
    template <class ForwardIter, class T>
    void unchecked_uninit_fill(ForwardIter first, ForwardIter last, const T& value, std::false_type) {
        auto cur = first;
        try {
            for (; cur != last; ++cur) { tinystl::construct(&*cur, value); }
        } catch (...) {
            for (; first != cur; ++first) tinystl::destroy(&*first);
        }
    }
    template <class ForwardIter, class T>
    void uninitialized_fill(ForwardIter first, ForwardIter last, const T& value) {
        tinystl::unchecked_uninit_fill(first, last, value, std::is_trivially_copy_assignable<typename iterator_traits<ForwardIter>::value_type>{});
    }

    // uninitialized fill n
    template <class ForwardIter, class Size, class T>
    ForwardIter unchecked_uninit_fill_n(ForwardIter first, Size n, const T& value, std::true_type) {
        return tinystl::fill_n(first, n, value);
    }
    template <class ForwardIter, class Size, class T>
    ForwardIter unchecked_uninit_fill_n(ForwardIter first, Size n, const T& value, std::false_type) {
        auto cur = first;
        try {
            for (; n > 0; --n, ++cur) { tinystl::construct(&*cur, value); }
        } catch (...) {
            for (; first != cur; ++first) tinystl::destroy(&*first);
        }
        return cur;
    }
    template <class ForwardIter, class Size, class T>
    ForwardIter uninitialized_fill_n(ForwardIter first, Size n, const T& value) {
        return tinystl::unchecked_uninit_fill_n(first, n, value, std::is_trivially_copy_assignable<typename iterator_traits<ForwardIter>::value_type>{});
    }

    // uninitialized move
    template <class InputIter, class ForwardIter>
    ForwardIter unchecked_uninit_move(InputIter first, InputIter last, ForwardIter result, std::true_type) {
        return tinystl::move(first, last, result);
    }
    template <class InputIter, class ForwardIter>
    ForwardIter unchecked_uninit_move(InputIter first, InputIter last, ForwardIter result, std::false_type) {
        ForwardIter cur = result;
        try {
            for (; first != last; ++first, ++cur) { tinystl::construct(&*cur, tinystl::move(*first)); }
        } catch (...) {
            tinystl::destroy(result, cur);
        }
        return cur;
    }
    template <class InputIter, class ForwardIter>
    ForwardIter uninitialized_move(InputIter first, InputIter last, ForwardIter result) {
        return tinystl::unchecked_uninit_move(first, last, result, std::is_trivially_move_assignable<typename iterator_traits<InputIter>::value_type>{});
    }

    // uninitialized move n
    template <class InputIter, class Size, class ForwardIter>
    ForwardIter unchecked_uninit_move_n(InputIter first, Size n, ForwardIter result, std::true_type) {
        return tinystl::move(first, first + n, result);
    }
    template <class InputIter, class Size, class ForwardIter>
    ForwardIter unchecked_uninit_move_n(InputIter first, Size n, ForwardIter result, std::false_type) {
        auto cur = result;
        try {
            for (; n > 0; --n, ++first, ++cur) { tinystl::construct(&*cur, tinystl::move(*first)); }
        } catch (...) {
            for (; result != cur; ++result) tinystl::destroy(&*result);
            throw ;
        }
        return cur;
    }
    template <class InputIter, class Size, class ForwardIter>
    ForwardIter uninitialized_move_n(InputIter first, Size n, ForwardIter result) {
        return tinystl::unchecked_uninit_move_n(first, n, result, std::is_trivially_move_assignable<typename iterator_traits<InputIter>::value_type>{});
    }
}

#endif //TINYSTL_UNINITIALIZED_H_
