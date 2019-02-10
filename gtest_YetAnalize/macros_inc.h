#ifndef MACROS_INC_H
#define MACROS_INC_H

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <gmock/gmock-matchers.h>

using namespace testing;

#define DEBUG_GTEST_STR(str)\
    std::cerr << str << std::endl

#define DEBUG_GTEST(a)\
    std::cerr << "dbg gtest: "#a" = " <<  a << std::endl

#define DEBUG_GTEST2(a, a2)\
    std::cerr << "dbg gtest: "#a" = " <<  a << " "#a2" = " << a2 << std::endl

#define ASSERT_STREQ_QT(a, b) ASSERT_STREQ(qPrintable(a), qPrintable(b))


template <typename ObjectType, typename ContainerType>
struct ObjectContainer{
    const ObjectType *object = 0;
    const ContainerType *objectContainer = 0;
    static const size_t sizeOfObjectInBytes = sizeof(ObjectType);
    static const size_t sizeOfContainerElementInBytes = sizeof(ContainerType);
    static const size_t sizeOfObjectInWords = sizeOfObjectInBytes / sizeOfContainerElementInBytes;

    using value_type = ContainerType;

    // copy-past from std::array:
    typedef value_type*			      pointer;
    typedef const value_type*         const_pointer;
    typedef value_type&               reference;
    typedef const value_type&         const_reference;
    typedef value_type*          	  iterator;
    typedef const value_type*		  const_iterator;
    typedef std::size_t               size_type;
    typedef std::ptrdiff_t            difference_type;
    typedef std::reverse_iterator<iterator>         reverse_iterator;
    typedef std::reverse_iterator<const_iterator>   const_reverse_iterator;

    ObjectContainer(const ObjectType *object)
    {
        static_assert((sizeOfObjectInWords * sizeOfContainerElementInBytes) == sizeOfObjectInBytes,
                      "the container is not aligned with the object");
        this->object = object;
        objectContainer = reinterpret_cast<const ContainerType*>(object);
    }

    const ContainerType* begin() const{
        return objectContainer;
    }

    const ContainerType* end() const {
        return objectContainer + sizeOfObjectInWords;
    }
};

#endif // MACROS_INC_H
