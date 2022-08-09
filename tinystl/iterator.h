#ifndef TINYSTL_ITERATOR_H_
#define TINYSTL_ITERATOR_H_

#include <cstddef>

#include "type_traits.h"

namespace tinystl {
    // 5 kinds of iterator
    struct input_iterator_tag {};
    struct output_iterator_tag {};
    struct forward_iterator_tag : public input_iterator_tag {};
    struct bidirectional_iterator_tag : public forward_iterator_tag {};
    struct random_access_iterator_tag : public bidirectional_iterator_tag {};


}

#endif