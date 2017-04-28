/**************************************************************************
 *
 * Copyright (c) 2017 Jorge Nunes, All Rights Reserved.
 *
 *//**
 *
 * @file avrtk/buttons/ButtonService.h
 *
 * @brief Definition of ButtonService interface methods.
 *
 **************************************************************************/

#include <avrtk/buttons/ButtonService.h>


/**
 * @interface ButtonService avrtk/buttons/ButtonService.h <avrtk/buttons/ButtonService.h>
 * @ingroup avrtk_buttons
 *
 * @brief Provides access to events for button press and button
 * release.
 */


/**
 * Initializes a button channel for use.
 *
 * @param self Reference to the ButtonService object where this method
 * is being called.
 *
 * @param buttonChannel Reference to the ButtonChannel to be
 * initialized.
 *
 * @param buttonId The ID of the button to be associated with the
 * given ButtonChannel.
 *
 * @return A reference to the same ButtonChannel passed in the
 * buttonChannel argument.
 */
ButtonChannel *ButtonService_initButtonChannel(
        ButtonService *self,
        ButtonChannel *buttonChannel,
        int buttonId) {

    return self->vtable->initButtonChannel(self, buttonChannel, buttonId);
}

