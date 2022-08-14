#ifndef TINYSTL_HEAP_ALGO_H_
#define TINYSTL_HEAP_ALGO_H_

#include "iterator.h"

namespace tinystl {

    // push heap
    template <class RandomIter, class Distance, class T>
    void push_heap_aux(RandomIter first, Distance holeIndex, Distance topIndex, T value) {
        auto parent = (holeIndex - 1) / 2;
        while (holeIndex > topIndex && *(first + parent) < value) {
            *(first + holeIndex) = *(first + parent);
            holeIndex = parent;
            parent = (holeIndex - 1) / 2;
        }
        *(first + holeIndex) = value;
    }

    template <class RandomIter, class Distance>
    void push_heap_d(RandomIter first, RandomIter last, Distance*) {
        tinystl::push_heap_aux(first, (last - first) - 1, static_cast<Distance>(0), *(last - 1));
    }

    template <class RandomIter>
    void push_heap(RandomIter first, RandomIter last) {
        tinystl::push_heap_d(first, last, distance_type(first));
    }

    template <class RandomIter, class Distance, class T, class Compared>
    void push_heap_aux(RandomIter first, Distance holeIndex, Distance topIndex, T value, Compared comp) {
        auto parent = (holeIndex - 1) / 2;
        while (holeIndex > topIndex && comp(*(first + parent), value)) {
            *(first + holeIndex) = *(first + parent);
            holeIndex = parent;
            parent = (holeIndex - 1) / 2;
        }
        *(first + holeIndex) = value;
    }

    template <class RandomIter, class Compared, class Distance>
    void push_heap_d(RandomIter first, RandomIter last, Distance*, Compared comp) {
        tinystl::push_heap_aux(first, (last - first) - 1, static_cast<Distance>(0), *(last - 1), comp);
    }

    template <class RandomIter, class Compared>
    void push_heap(RandomIter first, RandomIter last, Compared comp) {
        tinystl::push_heap_d(first, last, distance_type(first), comp);
    }

    // pop heap
    template <class RandomIter, class T, class Distance>
    void adjust_heap(RandomIter first, Distance holeIndex, Distance len, T value) {
        auto topIndex = holeIndex;
        auto rchild = 2 * holeIndex + 2;
        while (rchild < len) {
            if (*(first + rchild) < *(first + rchild - 1)) --rchild;
            *(first + holeIndex) = *(first + rchild);
            holeIndex = rchild;
            rchild = 2 * (rchild + 1);
        }
        if (rchild == len) {
            *(first + holeIndex) = *(first + (rchild - 1));
            holeIndex = rchild - 1;
        }
        tinystl::push_heap_aux(first, holeIndex, topIndex, value);
    }

    template <class RandomIter, class T, class Distance>
    void pop_heap_aux(RandomIter first, RandomIter last, RandomIter result, T value, Distance*) {
        *result = *first;
        tinystl::adjust_heap(first, static_cast<Distance>(0), last - first, value);
    }

    template <class RandomIter>
    void pop_heap(RandomIter first, RandomIter last) {
        tinystl::pop_heap_aux(first, last - 1, last - 1, *(last -1), distance_type(first));
    }

    template <class RandomIter, class T, class Distance, class Compared>
    void adjust_heap(RandomIter first, Distance holeIndex, Distance len, T value, Compared comp) {
        auto topIndex = holeIndex;
        auto rchild = 2 * holeIndex + 2;
        while (rchild < len) {
            if (comp(*(first + rchild) < *(first + rchild - 1))) --rchild;
            *(first + holeIndex) = *(first + rchild);
            holeIndex = rchild;
            rchild = 2 * (rchild + 1);
        }
        if (rchild == len) {
            *(first + holeIndex) = *(first + (rchild - 1));
            holeIndex = rchild - 1;
        }
        tinystl::push_heap_aux(first, holeIndex, topIndex, value, comp);
    }

    template <class RandomIter, class T, class Distance, class Compared>
    void pop_heap_aux(RandomIter first, RandomIter last, RandomIter result, T value, Distance*, Compared comp) {
        *result = *first;
        tinystl::adjust_heap(first, static_cast<Distance>(0), last - first, value, comp);
    }

    template <class RandomIter, class Compared>
    void pop_heap(RandomIter first, RandomIter last, Compared comp) {
        tinystl::pop_heap_aux(first, last - 1, last - 1, *(last -1), distance_type(first), comp);
    }

    // sort heap
    template <class RandomIter>
    void sort_heap(RandomIter first, RandomIter last) {
        while (last - first > 1) { tinystl::pop_heap(first, last--); }
    }

    template <class RandomIter, class Compared>
    void sort_heap(RandomIter first, RandomIter last, Compared comp) {
        while (last - first > 1) { tinystl::pop_heap(first, last--, comp); }
    }

    // make heap
    template <class RandomIter, class Distance>
    void make_heap_aux(RandomIter first, RandomIter last, Distance*) {
        if (last - first < 2) return;
        auto len = last - first;
        auto holeIndex = (len - 2) / 2;
        while (true) {
            tinystl::adjust_heap(first, holeIndex, len, *(first + holeIndex));
            if (holeIndex == 0) return;
            holeIndex--;
        }
    }

    template <class RandomIter>
    void make_heap(RandomIter first, RandomIter last) {
        tinystl::make_heap_aux(first, last, distance_type(first));
    }

    template <class RandomIter, class Distance, class Compared>
    void make_heap_aux(RandomIter first, RandomIter last, Distance*, Compared comp) {
        if (last - first < 2) return;
        auto len = last - first;
        auto holeIndex = (len - 2) / 2;
        while (true) {
            tinystl::adjust_heap(first, holeIndex, len, *(first + holeIndex), comp);
            if (holeIndex == 0) return;
            holeIndex--;
        }
    }

    template <class RandomIter, class Compared>
    void make_heap(RandomIter first, RandomIter last, Compared comp) {
        tinystl::make_heap_aux(first, last, distance_type(first), comp);
    }


}

#endif //TINYSTL_HEAP_ALGO_H_
