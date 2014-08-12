/**************************************************************************
 *
 * Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
 *
 *//**
 *
 * @file avrtk/buttons/ButtonListener.h
 *
 * @brief Definition of the ButtonListener interface methods.
 *
 **************************************************************************/

#include <avrtk/buttons/ButtonListener.h>





/**********************************************************************//**
 *
 * @interface ButtonListener avrtk/buttons/ButtonListener.h <avrtk/buttons/ButtonListener.h>
 * @ingroup avrtk_buttons
 *
 * @brief Defines the API for objects interested in being notified of
 * events related with one specific button.
 *
 **************************************************************************/





/**********************************************************************//**
 *
 * Called when the button is pressed.
 *
 * @public @memberof ButtonListener
 * @pure
 *
 * @param self 
 *
 * @param button The Button being passed to this ButtonListener.
 *
 * @param buttonId The ID of the button that was pressed.
 *
 **************************************************************************/

void ButtonListener_onPress(ButtonListener *self,
                            int             buttonId) {

    self->vtable->onPress(self, buttonId);
}





/**********************************************************************//**
 *
 * Called when the button is released.
 *
 * @public @memberof ButtonListener
 * @pure
 *
 * @param self 
 *
 * @param button The Button being passed to this ButtonListener.
 *
 * @param buttonId The ID of the button that was pressed.
 *
 **************************************************************************/

void ButtonListener_onRelease(ButtonListener *self,
                              int             buttonId) {

    self->vtable->onRelease(self, buttonId);
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

