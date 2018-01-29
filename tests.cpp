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

#include "test_entity.h"

using namespace boost::unit_test_framework;

//region ComparisonOperators
BOOST_AUTO_TEST_SUITE( ComparisonOperators ) // NOLINT

    BOOST_AUTO_TEST_CASE( BasicUsage ) { // NOLINT
        BOOST_CHECK_EQUAL( TestGroup::Enum0::ITEM00, TestGroup::Enum0::ITEM00 );
        BOOST_CHECK_NE( TestGroup::Enum0::ITEM00, TestGroup::Enum0::ITEM01 );
        BOOST_CHECK_GT( TestGroup::Enum0::ITEM01, TestGroup::Enum0::ITEM00 );
        BOOST_CHECK_LT( TestGroup::ITEM00, TestGroup::ITEM01 );
    }

    BOOST_AUTO_TEST_CASE( DifferentEnums ) { //NOLINT
        BOOST_CHECK_NE( TestGroup::Enum0::ITEM00, TestGroup::Enum1::ITEM10 );
    }

    BOOST_AUTO_TEST_CASE( GroupTypeWithSpecificType ) { // NOLINT
        BOOST_CHECK_EQUAL( TestGroup::ITEM00, TestGroup::Enum0::ITEM00 );
        BOOST_CHECK_GT( TestGroup::ITEM01, TestGroup::Enum0::ITEM00 );
        BOOST_CHECK_GT( TestGroup::ITEM11, TestGroup::Enum0::ITEM00 );
    }

BOOST_AUTO_TEST_SUITE_END(); // NOLINT
//endregion

//region Assignment
BOOST_AUTO_TEST_SUITE( Assignment, *depends_on( "ComparisonOperators" )) // NOLINT

    BOOST_AUTO_TEST_CASE( SpecificToGeneral ) { // NOLINT
        TestGroup::Enum0::Item specificItem = TestGroup::Enum0::ITEM00;
        TestGroup::Item        generalItem  = specificItem;
        BOOST_CHECK_EQUAL( generalItem, specificItem );
    }

    //region GeneralToSpecific
    BOOST_AUTO_TEST_SUITE( GeneralToSpecific ) // NOLINT

        BOOST_AUTO_TEST_CASE( InRange ) { // NOLINT
            TestGroup::Item        generalItem  = TestGroup::Enum0::ITEM00;
            TestGroup::Enum0::Item specificItem = generalItem;
            BOOST_CHECK_EQUAL( generalItem, specificItem );
        }

        BOOST_AUTO_TEST_CASE( OutOfRange ) { // NOLINT
            TestGroup::Item        generalItem = TestGroup::Enum1::ITEM10;
            TestGroup::Enum0::Item specificItem;
            BOOST_CHECK_THROW( { specificItem = generalItem; }, TestGroup::Error );
        }

    BOOST_AUTO_TEST_SUITE_END(); // NOLINT
    //endregion

    BOOST_AUTO_TEST_CASE( SpecificToOtherSpecific ) { // NOLINT
        TestGroup::Enum0::Item specific;
        TestGroup::Enum1::Item otherSpecific = TestGroup::Enum0::ITEM00;
        BOOST_CHECK_THROW( { specific = otherSpecific; }, TestGroup::Error );
    }

BOOST_AUTO_TEST_SUITE_END(); // NOLINT
//endregion

//region Uninitialized
BOOST_AUTO_TEST_SUITE( Uninitialized ) // NOLINT
    //region Uninitialized
    BOOST_AUTO_TEST_SUITE( ComparisonOperators ) // NOLINT

        BOOST_AUTO_TEST_CASE( Equality ) { // NOLINT
            BOOST_CHECK_EQUAL( TestGroup::Item(), TestGroup::Item());
            BOOST_CHECK_EQUAL( TestGroup::Enum0::Item(), TestGroup::Item());
            BOOST_CHECK_EQUAL( TestGroup::Item(), TestGroup::Enum0::Item());
            BOOST_CHECK_EQUAL( TestGroup::Enum0::Item(), TestGroup::Enum0::Item());
            BOOST_CHECK_EQUAL( TestGroup::Enum0::Item(), TestGroup::Enum1::Item());
        }

        BOOST_AUTO_TEST_CASE( Inequality ) { // NOLINT
            BOOST_CHECK_NE( TestGroup::Item(), TestGroup::ITEM00 );
            BOOST_CHECK_NE( TestGroup::Enum0::Item(), TestGroup::Enum0::ITEM00 );
        }

    BOOST_AUTO_TEST_SUITE_END(); // NOLINT
    //endregion

    //region Assignment
    BOOST_AUTO_TEST_SUITE( Assignment, *depends_on( "ComparisonOperators" )
                         ) // NOLINT

        BOOST_AUTO_TEST_CASE( SpecificToGeneral ) { // NOLINT
            TestGroup::Enum0::Item specificItem;
            TestGroup::Item        generalItem = specificItem;
            BOOST_CHECK_EQUAL( generalItem, specificItem );
        }

        BOOST_AUTO_TEST_CASE( GeneralToSpecific ) { // NOLINT
            TestGroup::Item        general;
            TestGroup::Enum0::Item item0 = general;
            BOOST_CHECK_EQUAL( item0, general );
        }

        BOOST_AUTO_TEST_CASE( SpecificToOtherSpecific ) { // NOLINT
            TestGroup::Enum0::Item otherSpecific;
            TestGroup::Enum1::Item specific = otherSpecific;
            BOOST_CHECK_EQUAL( otherSpecific, specific );
        }

    BOOST_AUTO_TEST_SUITE_END(); // NOLINT
    //endregion
BOOST_AUTO_TEST_SUITE_END(); // NOLINT
//endregion
