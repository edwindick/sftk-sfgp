/**
 * @file TODO
 */


#include <sftk/sfgp.h>
#include "sfgp_internal.h"

#include <stdint.h>
#include <stddef.h>
#include <assert.h>


/**
 * @brief Data required to perform checks on an individual button
 */
struct SFGP_Button {
    uint8_t last            : 1; /**< Last known value of button.   */
    uint8_t current         : 1; /**< Latest known value of button. */
};


void _SFGP_SetButton(SFGP_Button *const self, int8_t value) {
    assert(value == 1 || value == 0);

    self->last = self->current;
    self->current = value;
}


int8_t SFGP_IsButtonPressed(const SFGP_Button *const self) {
    assert(self != NULL);
    return self->current;
}

int8_t SFGP_IsButtonJustPressed(const SFGP_Button *const self) {
    assert(self != NULL);
    return self->current && !self->last;
}

int8_t SFGP_IsButtonReleased(const SFGP_Button *const self) {
    assert(self != NULL);
    return !self->current;
}

int8_t SFGP_IsButtonJustReleased(const SFGP_Button *const self) {
    assert(self != NULL);
    return !self->current && self->last;
}