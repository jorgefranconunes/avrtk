/**************************************************************************
 *
 * Copyright (c) 2014-2017 Jorge Nunes, All Rights Reserved.
 *
 **************************************************************************/

#ifndef BUTTONSERVICE_H
#define BUTTONSERVICE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <avrtk/buttons/ButtonChannel.h>


    typedef struct ButtonServiceStruct ButtonService;

    typedef struct ButtonServiceInterfaceStruct ButtonServiceInterface;
    struct ButtonServiceInterfaceStruct {
        ButtonChannel *(*initButtonChannel)(
                ButtonService *self,
                ButtonChannel *buttonChannel,
                int buttonId);
    };

    struct ButtonServiceStruct {
        ButtonServiceInterface *vtable;
    };

    ButtonChannel *ButtonService_initButtonChannel(
            ButtonService *self,
            ButtonChannel *buttonChannel,
            int buttonId);


#ifdef __cplusplus
}
#endif

#endif

