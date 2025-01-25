#include <sftk/sfgp.h>
#include "sfgp_internal.h"

#include <stdint.h>
#include <stddef.h>
#include <assert.h>


void _SFGP_SetTrigger(SFGP_Trigger *const self, float value) {
    assert(self != NULL);
    assert(value <= 1.0f);  // No check for >= 0.0f as this function is accessed
                            // when setting joystick members.

    self->last = self->current;
    self->current = value;
}


int8_t SFGP_IsTriggerPressed(const SFGP_Trigger *const self) {
    assert(self != NULL);
    return self->current >= 1.0f;
}

int8_t SFGP_IsTriggerJustPressed(const SFGP_Trigger *const self) {
    assert(self != NULL);
    return self->current >= 1.0f && self->last < 1.0f;
}

int8_t SFGP_IsTriggerReleased(const SFGP_Trigger *const self) {
    assert(self != NULL);
    return self->current <= 0.0f;
}

int8_t SFGP_IsTriggerJustReleased(const SFGP_Trigger *const self) {
    assert(self != NULL);
    return self->current <= 0.0f && self->last > 0.0f;
}

float SFGP_GetTriggerValue(const SFGP_Trigger *const self) {
    assert(self != NULL);
    return self->current;
}

float SFGP_GetTriggerVelocity(const SFGP_Trigger *const self) {
    assert(self != NULL);
    return self->current - self->last;
}