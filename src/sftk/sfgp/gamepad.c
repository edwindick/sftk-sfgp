#include <sftk/sfgp.h>
#include "sfgp_internal.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


// TODO: Document
static SFGP_Error _SFGP_InitGamepadArray(void **array, size_t nmemb, size_t size) {
    assert(array != NULL);
    assert(nmemb > 0);
    assert(size > 0);

    void *buffer = calloc(nmemb, size);
    if (buffer == NULL) return _SFGP_SetError(SFGP_ERROR_FAILED_ALLOCATION);

    for (int i = 0; i < nmemb; i++) {
        // This may be evil and bad and especially evil.
        array[i] = buffer + (size * i);
    }

    return SFGP_ERROR_OK;
}


SFGP_Error SFGP_InitGamepad(SFGP_Gamepad *const pad) {
    assert(pad != NULL);

    if (_SFGP_InitGamepadArray((void **) pad->buttons, SFGP_BUTTON_ELEM, sizeof (*pad->buttons)) != SFGP_ERROR_OK)
        goto error;
    if (_SFGP_InitGamepadArray((void **) pad->triggers, SFGP_BUTTON_ELEM, sizeof (*pad->triggers)) != SFGP_ERROR_OK)
        goto error;
    if (_SFGP_InitGamepadArray((void **) pad->joysticks, SFGP_BUTTON_ELEM, sizeof (*pad->joysticks)) != SFGP_ERROR_OK)
        goto error;

    return SFGP_ERROR_OK;

error:
    SFGP_DeinitGamepad(pad);
    // SFGP error state already set.
    return SFGP_ERROR_FAILED_ALLOCATION;
}

void SFGP_DeinitGamepad(const SFGP_Gamepad *const pad) {
    assert(pad != NULL);

    free(pad->buttons[0]);
    free(pad->triggers[0]);
    free(pad->joysticks[0]); // TODO: Test the work.
}

SFGP_Error SFGP_UpdateGamepad(SFGP_Gamepad *const pad, 
        const uint8_t *const byte_array) {
    assert(pad != NULL);
    assert(byte_array != NULL);

    // It is assumed that byte_array contains the required size to querry for
    // all button states, if this is not the case (it never should be
    // considering how you should be passing gamepad state in bindings), expect
    // a segmentation fault!
    
    // All operations are based on those found in Gamepad class within the 
    // FTC SDK.

    // NOTE: we could also check for version but we are currently only
    // searching for buttons available in version 1, so theres no need. THIS
    // WILL NOT BE THE CASE IN THE FUTURE.

    // 4 bytes store gamepad ID, 8 bytes store the current timestamp.
    const size_t joystick_offset = 4 + 8;

    
    float stick_x_buf = 0.0f, stick_y_buf = 0.0f;
    for (int i = 0; i < SFGP_JOYSTICK_ELEM; ++i) {
        size_t elem = joystick_offset + (sizeof (float) * i * 2);

        memcpy(&stick_x_buf, &byte_array[elem], sizeof (stick_x_buf));
        memcpy(&stick_y_buf, &byte_array[elem + sizeof (float)], sizeof (stick_y_buf));

        _SFGP_SetJoystick(pad->joysticks[i], stick_x_buf, stick_y_buf);
    }

    const size_t trigger_offset = joystick_offset 
        + (SFGP_JOYSTICK_ELEM * sizeof (float) * 2);

    float trigger_buf = 0.0f;
    for (int i = 0; i < SFGP_TRIGGER_ELEM; ++i) {
        size_t elem = trigger_offset + (sizeof (float) * i);

        memcpy(&trigger_buf, &byte_array[elem], sizeof(trigger_buf));
        _SFGP_SetTrigger(pad->triggers[i], trigger_buf);
    }

    const size_t button_offset = joystick_offset
        + (SFGP_TRIGGER_ELEM * sizeof(float));

    uint32_t button_data = 0x0;
    memcpy(&button_data, &byte_array[button_offset], sizeof (button_data));

    for (int i = 0; i < SFGP_BUTTON_ELEM; ++i) {
        int8_t value = (button_data << i) & 1u;
        _SFGP_SetButton(pad->buttons[i], value);
    }

    // No errors currently, but I expect there to be at least some in the 
    // future.
    return SFGP_ERROR_OK;
}