#include <gn_ref.h>
#include <modules.h>
#include "audioprocess.h"

#if AUDIOPROCESS_NUM_CHANNELS_TX_IN!=AUDIOPROCESS_NUM_CHANNELS_TX_OUT || AUDIOPROCESS_NUM_CHANNELS_RX_IN!=AUDIOPROCESS_NUM_CHANNELS_RX_OUT || AUDIOPROCESS_DOWNRATE_TX_IN!=AUDIOPROCESS_DOWNRATE_TX_OUT || AUDIOPROCESS_DOWNRATE_RX_IN!=AUDIOPROCESS_DOWNRATE_RX_OUT
    #error "Passthrough example violated"
#endif

void audioprocess_init() {

}

void audioprocess_run(float *in_tx, float *out_tx, float *in_rx, float *out_rx) {

}

void audioprocess_destroy() {

}
