/**************************************************************************
 *
 * Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
 *
 **************************************************************************/

#ifndef ADCSOURCE_H
#define ADCSOURCE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <avrtk/events/EventSource.h>
#include <avrtk/adc/AdcSourceChannel.h>





    typedef struct AdcSourceStruct AdcSource;

    typedef struct AdcSourceInterfaceStruct AdcSourceInterface;
    struct AdcSourceInterfaceStruct {
        void (*addSourceChannel)(AdcSource *, AdcSourceChannel *);
    };

    struct AdcSourceStruct {
        EventSource         base;
        AdcSourceInterface *vtable;
    };

    void AdcSource_addSourceChannel(AdcSource        *self,
                                    AdcSourceChannel *channel);

    EventSource *AdcSource_asEventSource(AdcSource *self);





#ifdef __cplusplus
}
#endif

#endif
