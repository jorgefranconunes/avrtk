/**************************************************************************
 *
 * Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
 *
 **************************************************************************/

#ifndef CLOCK_H
#define CLOCK_H

#ifdef __cplusplus
extern "C" {
#endif





    typedef struct ClockStruct Clock;


    typedef struct ClockInterfaceStruct ClockInterface;
    struct ClockInterfaceStruct {
        long (*currentTimeMillis)(Clock *);
    };


    struct ClockStruct {
        ClockInterface *vtable;
    };

    long Clock_currentTimeMillis(Clock *self);





#ifdef __cplusplus
}
#endif

#endif
