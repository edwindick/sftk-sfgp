#include <sftk/sfgp.h>
#include "sfgp_internal.h"

#include <stdint.h>
#include <stddef.h>
#include <assert.h>


/**
 * @brief Data required to perform checks on an individual joystick.
 */
struct SFGP_Joystick {
    struct SFGP_Trigger x; /**< Trigger data representing joysticks x axis. */
    struct SFGP_Trigger y; /**< Trigger data representing joysticks y axis. */
};


void _SFGP_SetJoystick(SFGP_Joystick *const self, float curr_x, float curr_y) {
    assert(self != NULL);
    assert(curr_x <= 1.0f && curr_x >= -1.0f);
    assert(curr_y <= 1.0f && curr_y >= -1.0f);

    _SFGP_SetTrigger(&self->x, curr_x);
    _SFGP_SetTrigger(&self->y, curr_y);
}


// A lot of the following function calls could be replaced by referencing an
// axis to a respective trigger, however I believe that would reduce
// readability for the "improvement" from a single line of code to a single
// line of code with a function call in it. 

// x-axis

int8_t SFGP_IsXAtMax(const SFGP_Joystick *const self) {
    assert(self != NULL);
    return self->x.current >= 1.0f;
}

int8_t SFGP_IsXJustAtMax(const SFGP_Joystick *const self) {
    assert(self != NULL);
    return self->x.current >= 1.0f && self->x.last < 1.0f;
}

int8_t SFGP_IsXAtMin(const SFGP_Joystick *const self) {
    assert(self != NULL);
    return self->x.current <= -1.0f;
}

int8_t SFGP_IsXJustAtMin(const SFGP_Joystick *const self) {
    assert(self != NULL);
    return self->x.current <= -1.0f && self->x.last > -1.0f;
}

int8_t SFGP_IsXAtZero(const SFGP_Joystick *const self) {
    assert(self != NULL);
    return self->x.current == 0.0f;
}

int8_t SFGP_IsXJustAtZero(const SFGP_Joystick *const self) {
    assert(self != NULL);
    return self->x.current == 0.0f && self->y.last != 0.0f;
}

float SFGP_GetXValue(const SFGP_Joystick *const self) {
    assert(self != NULL);
    return self->x.current;
}

float SFGP_GetXVelocity(const SFGP_Joystick *const self) {
    assert(self != NULL);
    return self->x.current - self->y.last;
}

// y-axis

int8_t SFGP_IsYAtMax(const SFGP_Joystick *const self) {
    assert(self != NULL);
    return self->y.current >= 1.0f;
}

int8_t SFGP_IsYJustAtMax(const SFGP_Joystick *const self) {
    assert(self != NULL);
    return self->y.current >= 1.0f && self->y.last < 1.0f;
}

int8_t SFGP_IsYAtMin(const SFGP_Joystick *const self) {
    assert(self != NULL);
    return self->y.current <= -1.0f;
}

int8_t SFGP_IsYJustAtMin(const SFGP_Joystick *const self) {
    assert(self != NULL);
    return self->y.current <= -1.0f && self->y.last > -1.0f;
}

int8_t SFGP_IsYAtZero(const SFGP_Joystick *const self) {
    assert(self != NULL);
    return self->y.current == 0.0f;
}

int8_t SFGP_IsYJustAtZero(const SFGP_Joystick *const self) {
    assert(self != NULL);
    return self->y.current == 0.0f && self->y.last != 0.0f;
}

float SFGP_GetYValue(const SFGP_Joystick *const self) {
    assert(self != NULL);
    return self->y.current;
}

float SFGP_GetYVelocity(const SFGP_Joystick *const self) {
    assert(self != NULL);
    return self->y.current - self->y.last;
}