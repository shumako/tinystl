#ifndef TINYSTL_MEMORY_H_
#define TINYSTL_MEMORY_H_

#include <cstddef>
#include <cstdlib>
#include <climits>

#include "algobase.h"
#include "allocator.h"
#include "construct.h"
#include "uninitialized.h"

namespace tinystl {

    // address
    template <class Tp>
    constexpr Tp* address_of(Tp& value) noexcept { return &value; }

    // get & release buffer
    template <class T>
    pair<T*, ptrdiff_t> get_buffer_helper(ptrdiff_t len, T*) {
        if (len > static_cast<ptrdiff_t>(INT_MAX / sizeof(T))) len = INT_MAX / sizeof(T);
        while (len > 0) {
            T* tmp = static_cast<T*>(malloc(static_cast<size_t>(len) * sizeof(T)));
            if (tmp) return pair<T*, ptrdiff_t>(tmp, len);
            len /= 2;
        }
        return pair<T*, ptrdiff_t>(nullptr, 0);
    }

    template <class T>
    pair<T*, ptrdiff_t> get_temporary_buffer(ptrdiff_t len) {
        return get_buffer_helper(len, static_cast<T*>(0));
    }
    template <class T>
    pair<T*, ptrdiff_t> get_temporary_buffer(ptrdiff_t len, T*) {
    return get_buffer_helper(len, static_cast<T*>(0));
    }
    template <class T>
    void release_temporary_buffer(T* ptr) { free(ptr); }

    // class: temporary buffer
    template <class ForwardIterator, class T>
    class temporary_buffer {
    private:
        ptrdiff_t original_len;
        ptrdiff_t len;
        T* buffer;

    public:
        temporary_buffer(ForwardIterator first, ForwardIterator last);
        ~temporary_buffer() { tinystl::destroy(buffer, buffer + len); free(buffer); }

    public:
        ptrdiff_t size() const noexcept { return len; }
        ptrdiff_t requested_size() const noexcept { return original_len; }
        T* begin() noexcept { return buffer; }
        T* end() noexcept { return buffer + len; }

    private:
        void allocate_buffer();
        void initialize_buffer(const T&, std::true_type) {}
        void initialize_buffer(const T& value, std::false_type) { tinystl::uninitialized_fill_n(buffer, len, value); }

    private:
        temporary_buffer(const temporary_buffer&);
        void operator=(const temporary_buffer&);
    };

    // constructor
    template <class ForwardIterator, class T>
    temporary_buffer<ForwardIterator, T>::temporary_buffer(ForwardIterator first, ForwardIterator last) {
        try {
            len = tinystl::distance(first, last);
            allocate_buffer();
            if ( len > 0 ) { initialize_buffer(*first, std::is_trivially_default_constructible<T>()); }
        } catch (...) {
            free(buffer);
            buffer = nullptr;
            len = 0;
        }
    }

    // allocator_buffer function
    template <class ForwardIterator, class T>
    void temporary_buffer<ForwardIterator, T>::allocate_buffer() {
        original_len = len;
        if ( len > static_cast<ptrdiff_t>(INT_MAX / sizeof(T))) len = INT_MAX / sizeof(T);
        while ( len > 0 ) {
            buffer = static_cast<T*>(malloc(len * sizeof(T)));
            if (buffer) break;
            len /= 2;
        }
    }



}

#endif //TINYSTL_MEMORY_H_
