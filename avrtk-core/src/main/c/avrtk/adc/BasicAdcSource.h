/**************************************************************************
 *
 * Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
 *
 **************************************************************************/

#ifndef BASICADCSOURCE_H
#define BASICADCSOURCE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include <avrtk/adc/AdcEvent.h>
#include <avrtk/adc/AdcSource.h>





    typedef struct BasicAdcSourceStruct BasicAdcSource;

    struct BasicAdcSourceStruct {
        AdcSource         base;
        AdcSourceChannel *channelListHead;
        AdcSourceChannel *currentChannel;
        AdcEvent          eventData;
        bool            (*startAdc)(int);
        bool            (*isAdcCompleted)(void);
        uint16_t        (*getLatestAdcValue)(void);
    };

    BasicAdcSource *
    BasicAdcSource_init(BasicAdcSource *self,
                        bool          (*startAdc)(int),
                        bool          (*isAdcCompleted)(void),
                        uint16_t      (*getLatestAdcValue)(void));

    void BasicAdcSource_addSourceChannel(AdcSource        *self,
                                         AdcSourceChannel *channel);

    Event *BasicAdcSource_poll(EventSource *self);

    AdcSource *BasicAdcSource_asAdcSource(BasicAdcSource *self);

    EventSource *BasicAdcSource_asEventSource(BasicAdcSource *self);





#ifdef __cplusplus
}
#endif

#endif
