/**************************************************************************
 *
 * Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
 *
 **************************************************************************/

#ifndef ADCSOURCECHANNEL_H
#define ADCSOURCECHANNEL_H

#ifdef __cplusplus
extern "C" {
#endif





    typedef struct AdcSourceChannelStruct AdcSourceChannel;

    struct AdcSourceChannelStruct {
        int               channelId;
        AdcSourceChannel *next;
    };

    AdcSourceChannel *AdcSourceChannel_init(AdcSourceChannel *self,
                                            int               channelId);

    int AdcSourceChannel_getChannelId(AdcSourceChannel *self);





#ifdef __cplusplus
}
#endif

#endif
