/**************************************************************************
 *
 * Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
 *
 **************************************************************************/

#ifndef EVENTTYPE_H
#define EVENTTYPE_H

#ifdef __cplusplus
extern "C" {
#endif





    typedef struct EventTypeStruct EventType;
    struct EventTypeStruct {
        int id;
    };

    EventType *EventType_init(EventType *self);

    int  EventType_getId(EventType *self);





#ifdef __cplusplus
}
#endif

#endif
