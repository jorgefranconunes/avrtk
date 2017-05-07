/**************************************************************************
 *
 * Copyright (c) 2014-2017 Jorge Nunes, All Rights Reserved.
 *
 **************************************************************************/

#include <avrtk/adc/AdcService.h>


/**
 * @interface AdcService avrtk/adc/AdcService.h <avrtk/adc/AdcService.h>
 * @ingroup avrtk_adc
 *
 * @brief Used for receiving samples from the A/D converter ports.
 */


/**
 * Starts the AdcService.
 *
 * @public @memberof AdcService
 * @pure
 *
 * After this method returns the AdcService is ready to create channels.
 *
 * @param self Reference to the AdcService object being used.
 */
void AdcService_start(AdcService  *self) {

    self->vtable->start(self);
}


/**
 * Initializes a channel to receive ADC samples.
 *
 * @public @memberof AdcService
 *
 * @param self Reference to the AdcService object being used.
 *
 * @param channel Reference to the AdcChannel object to be
 * initialized.
 *
 * @param channelId The ID of the ADC channel for which sampels will
 * be obtained. This corresponds directly to one specific ADC port.
 */
AdcChannel *AdcService_initChannel(
        AdcService *self,
        AdcChannel *channel,
        int channelId) {

    return self->vtable->initChannel(self, channel, channelId);
}
