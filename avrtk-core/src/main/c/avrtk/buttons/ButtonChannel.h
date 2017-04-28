/**************************************************************************
 *
 * Copyright (c) 2014-2017 Jorge Nunes, All Rights Reserved.
 *
 **************************************************************************/

#ifndef BUTTONCHANNEL_H
#define BUTTONCHANNEL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#include <avrtk/buttons/ButtonListener.h>


    typedef struct ButtonChannelStruct ButtonChannel;

    struct ButtonChannelStruct {
        ButtonListener  *listenerListHead;
    };

    ButtonChannel *ButtonChannel_init(ButtonChannel *self);

    void ButtonChannel_addButtonListener(
            ButtonChannel  *self,
            ButtonListener *listener);

    bool ButtonChannel_isPressed(ButtonChannel *self);


#ifdef __cplusplus
}
#endif

#endif

