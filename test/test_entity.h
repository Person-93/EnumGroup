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

#ifndef ENUMGROUP_TESTING_H
#define ENUMGROUP_TESTING_H
#define BOOST_TEST_MODULE enum_group_test_module

#include "../src/EnumGroup.h"

ENUM_GROUP_START( TestGroup )
    ADD_ENUM( Enum0, ITEM00, ITEM01 )
    ADD_ENUM( Enum1, ITEM10, ITEM11 )
ENUM_GROUP_END()

#include <boost/test/unit_test.hpp>

#endif //ENUMGROUP_TESTING_H
