#ifndef TINYSTL_SET_ALGO_H_
#define TINYSTL_SET_ALGO_H_

#include "algobase.h"
#include "iterator.h"

namespace tinystl {

    // union
    template <class InputIter1, class InputIter2, class OutputIter>
    OutputIter set_union(InputIter1 first1, InputIter1 last1, InputIter2 first2, InputIter2 last2, OutputIter result) {
        while (first1 != last1 && first2 != last2) {
            if (*first1 < *first2) { *result = *first1; ++first1; }
            else if (*first2 < *first1) { *result = *first2; ++first2; }
            else { *result = *first1; ++first1; ++first2; }
            ++result;
        }
        return tinystl::copy(first2, last2, tinystl::copy(first1, last1, result));
    }

    template <class InputIter1, class InputIter2, class OutputIter, class Compared>
    OutputIter set_union(InputIter1 first1, InputIter1 last1, InputIter2 first2, InputIter2 last2, OutputIter result, Compared comp) {
        while (first1 != last1 && first2 != last2) {
            if (comp(*first1, *first2)) { *result = *first1; ++first1; }
            else if (comp(*first2, *first1)) { *result = *first2; ++first2; }
            else { *result = *first1; ++first1; ++first2; }
            ++result;
        }
        return tinystl::copy(first2, last2, tinystl::copy(first1, last1, result));
    }


    // intersection
    template <class InputIter1, class InputIter2, class OutputIter>
    OutputIter set_intersection(InputIter1 first1, InputIter1 last1, InputIter2 first2, InputIter2 last2, OutputIter result) {
        while (first1 != last1 && first2 != last2) {
            if (*first1 < *first2) { ++first1; }
            else if (*first2 < *first1) { ++first2; }
            else { *result = *first1; ++first1; ++first2; ++result; }
        }
        return result;
    }

    template <class InputIter1, class InputIter2, class OutputIter, class Compared>
    OutputIter set_intersection(InputIter1 first1, InputIter1 last1, InputIter2 first2, InputIter2 last2, OutputIter result, Compared comp) {
        while (first1 != last1 && first2 != last2) {
            if (comp(*first1, *first2)) { ++first1; }
            else if (comp(*first2, *first1)) { ++first2; }
            else { *result = *first1; ++first1; ++first2; ++result; }
        }
        return result;
    }

    // difference
    template <class InputIter1, class InputIter2, class OutputIter>
    OutputIter set_difference(InputIter1 first1, InputIter1 last1, InputIter2 first2, InputIter2 last2, OutputIter result) {
        while (first1 != last1 && first2 != last2) {
            if (*first1 < *first2) { *result = *first1; ++first1; ++result; }
            else if (*first2 < *first1) { ++first2; }
            else { ++first1; ++first2; }
        }
        return tinystl::copy(first1, last1, result);
    }

    template <class InputIter1, class InputIter2, class OutputIter, class Compared>
    OutputIter set_difference(InputIter1 first1, InputIter1 last1, InputIter2 first2, InputIter2 last2, OutputIter result, Compared comp) {
        while (first1 != last1 && first2 != last2) {
            if (comp(*first1, *first2)) { *result = *first1; ++first1; ++result; }
            else if (comp(*first2 < *first1)) { ++first2; }
            else { ++first1; ++first2; }
        }
        return tinystl::copy(first1, last1, result);
    }

    // symmetric difference
    template <class InputIter1, class InputIter2, class OutputIter>
    OutputIter set_symmetric_difference(InputIter1 first1, InputIter1 last1, InputIter2 first2, InputIter2 last2, OutputIter result) {
        while (first1 != last1 && first2 != last2) {
            if (*first1 < *first2) { *result = *first1; ++first1; ++result; }
            else if (*first2 < *first1) { *result = *first2; ++first2; ++result; }
            else { ++first1; ++first2; }
        }
        return tinystl::copy(first2, last2, tinystl::copy(first1, last1, result));
    }

    template <class InputIter1, class InputIter2, class OutputIter, class Compared>
    OutputIter set_symmetric_difference(InputIter1 first1, InputIter1 last1, InputIter2 first2, InputIter2 last2, OutputIter result, Compared comp) {
        while (first1 != last1 && first2 != last2) {
            if (comp(*first1 < *first2)) { *result = *first1; ++first1; ++result; }
            else if (comp(*first2 < *first1)) { *result = *first2; ++first2; ++result; }
            else { ++first1; ++first2; }
        }
        return tinystl::copy(first2, last2, tinystl::copy(first1, last1, result));
    }
}

#endif //TINYSTL_SET_ALGO_H_
