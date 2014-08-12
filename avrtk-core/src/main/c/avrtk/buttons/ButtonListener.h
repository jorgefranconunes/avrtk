/**************************************************************************
 *
 * Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
 *
 **************************************************************************/

#ifndef BUTTONLISTENER_H
#define BUTTONLISTENER_H

#ifdef __cplusplus
extern "C" {
#endif





    typedef struct ButtonListenerStruct ButtonListener;

    typedef struct ButtonListenerInterfaceStruct ButtonListenerInterface;
    struct ButtonListenerInterfaceStruct {
        void (*onPress)(ButtonListener *self,
                        int             buttonId);
        void (*onRelease)(ButtonListener *self,
                          int             buttonId);
    };

    struct ButtonListenerStruct {
        ButtonListenerInterface *vtable;
        ButtonListener          *next;
    };

    void ButtonListener_onPress(ButtonListener *self,
                                int             buttonId);

    void ButtonListener_onRelease(ButtonListener *self,
                                  int             buttonId);





#ifdef __cplusplus
}
#endif

#endif
