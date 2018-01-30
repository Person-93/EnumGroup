/*MIT License

Copyright (c) 2018 Michael Tepfer

Permission is hereby granted, free of charge, to any person obtaining a copy
           of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
                                               to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
        copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

        The above copyright notice and this permission notice shall be included in all
                                                       copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
                                                         AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.*/

#ifndef ENUM_GROUP__ENUM_GROUP_H
#define ENUM_GROUP__ENUM_GROUP_H

#include "ForEachMacro.h"
#include <climits>
#include <boost/type_index.hpp>
#include <iostream>

// TODO add method to check if a EnumGroup::Item belongs to a specific group
// TODO Is there some way to document the generated classes with DoxyGen?
// TODO make boost dependency optional when not running test cases

namespace EnumGroup {
    /**
     * This is the base class that all of the Enum items extend from.
     * It can be used with the type_traits library to see if any type was defined by these macros.
     */
    class Item {};
}

//region helpers
#define __UNDERLYING_TYPE unsigned int
#define __INITIAL_VALUE UINT_MAX
#define __INITIAL_NAME "UNINITIALIZED"
#define __MAKE_MEMBER( NAME ) const Item NAME = __privateNamespace::makeListMember( #NAME );
#define __EXTRACT_MEMBER( ENUM_NAME, MEMBER_NAME ) const ENUM_NAME::Item &MEMBER_NAME = ENUM_NAME::MEMBER_NAME;
//endregion

//region ENUM_GROUP_START
#define ENUM_GROUP_START( GROUP_NAME ) \
namespace GROUP_NAME { \
    class Error : public std::runtime_error { \
    public: \
        template< typename T > \
        explicit Error( T message ) : std::runtime_error( std::move( message )) {} \
    }; \
    class Item : public EnumGroup::Item { \
    public: \
        Item &operator=( const Item &other ) { \
            value = other.getValue(); \
            name  = other.getName(); \
            return *this; \
        } \
        Item( const Item &other ) { \
            value = other.value; \
            name  = other.name; \
        } \
        bool operator==( const Item &other ) const {  return value == other.value; } \
        bool operator!=( const Item &other ) const { return value != other.value; } \
        bool operator<( const Item &other ) const { return value < other.value; } \
        bool operator>( const Item &other ) const { return value > other.value; } \
        const char *getName() const { return name; } \
        const unsigned int getValue() const { return value; } \
        explicit operator std::string() const { return getName(); } \
        Item() = default; \
        __UNDERLYING_TYPE value = __INITIAL_VALUE; \
        const char   *name = __INITIAL_NAME; \
    }; \
    std::ostream &operator<<( std::ostream &os, const Item &item ) { \
        os << item.getName(); \
        return os; \
    } \
    namespace __privateNamespaceOuter { \
        unsigned long counter = 0; \
        typedef Item Item; \
    }
//endregion

//region ADD_ENUM
#define ADD_ENUM( NAME, ... ) \
namespace NAME { \
    class Item; \
    namespace __privateNamespace { \
        static const Item makeListMember( const char *name ); \
    } \
    class Item : public __privateNamespaceOuter::Item { \
        friend const Item __privateNamespace ::makeListMember( const char *name ); \
        Item( unsigned int value, const char *name ); \
    public: \
        Item() = default; \
        Item( const __privateNamespaceOuter::Item &other ); \
    }; \
    namespace __privateNamespace { \
        static const Item makeListMember( const char *name ) { \
            return Item( __privateNamespaceOuter::counter++, name ); \
        } \
        static const unsigned int start = __privateNamespaceOuter::counter; \
    } \
    FOR_EACH(__MAKE_MEMBER, __VA_ARGS__) \
    namespace __privateNamespace { \
        static const unsigned int end = __privateNamespaceOuter::counter; \
    } \
    Item::Item( unsigned int value, const char *name ) { \
        this->value = value; \
        this->name  = name; \
    } \
    Item::Item( const __privateNamespaceOuter::Item &other ) { \
        auto otherValue = other.getValue(); \
        if ( otherValue != __INITIAL_VALUE && \
           ( otherValue < __privateNamespace::start || otherValue >= __privateNamespace::end )) \
            throw Error( std::string( "Value assigned to " ) + \
                         boost::typeindex::type_id<Item>().pretty_name() + " is out of range: " + \
                         other.getName()); \
        value = otherValue; \
        name  = other.getName(); \
    } \
} \
FOR_EACH_WITH_EXTRA(__EXTRACT_MEMBER, NAME, __VA_ARGS__)
//endregion

#define ENUM_GROUP_END() }

#endif //ENUM_GROUP__ENUM_GROUP_H
