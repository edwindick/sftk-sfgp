/** 
 * @file TODO
 */


#include <sftk/sfgp.h>
#include "sfgp_internal.h"


/**
 * @brief For storing SFGP's current error state.
 */
static SFGP_Error _SFGP_error = SFGP_ERROR_OK;



SFGP_Error _SFGP_SetError(SFGP_Error code) {
    _SFGP_error = code;
    return code;
}


SFGP_Error SFGP_GetError() {
    SFGP_Error error = _SFGP_error;
    _SFGP_error = SFGP_ERROR_OK;
    return error;
}