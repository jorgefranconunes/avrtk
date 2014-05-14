/**************************************************************************
 *
 * Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
 *
 **************************************************************************/

#include <CppUTest/TestHarness.h>

#include <avrtk/ticks/TickEventType.h>





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

TEST_GROUP(TickEventType) {
};





TEST(TickEventType, itExists) {

    CHECK( NULL != TickEventType_get() );
}





TEST(TickEventType, isConstant) {

    EventType *evType1 = TickEventType_get();
    EventType *evType2 = TickEventType_get();

    POINTERS_EQUAL( evType1, evType2 );
    CHECK_EQUAL(EventType_getId(evType1), EventType_getId(evType2));
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

