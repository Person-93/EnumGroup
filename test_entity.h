#ifndef ENUMGROUP_TESTING_H
#define ENUMGROUP_TESTING_H
#define BOOST_TEST_MODULE enum_group_test_module

#include "EnumGroup.h"

ENUM_GROUP_START( TestGroup )
    ADD_ENUM( Enum0, ITEM00, ITEM01 )
    ADD_ENUM( Enum1, ITEM10, ITEM11 )
ENUM_GROUP_END()

#include <boost/test/unit_test.hpp>

#endif //ENUMGROUP_TESTING_H
