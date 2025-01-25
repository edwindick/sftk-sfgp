/** 
 * @file sftk/sfgp.h 
 * @author Edwin Dick
 * @date 15 Jan 2025
 * @brief C library header for all public data and procedures relating to SFGP.
 * core of the SFGP library that is accessed to users by project bindings.
 *  
 * Provides a simple way to access more features out of the FTC SDK's gamepad
 * classes, such as whether or not a button or trigger on a given gamepad was
 * just pressed or released. All functionality of this module depends on
 * receiving outside gamepad data in the form of a byte array from bindings
 * with the FTC SDK.
 * 
 * See the @ref bindings directory for more information on including this in
 * your project.
 */


// TODO: PS Support for buttons and triggers.


#ifndef __SFTK_SFGP_HEADER__
#define __SFTK_SFGP_HEADER__

#ifdef __cplusplus
    extern "C" {
#endif // __cplusplus


#include <stdint.h>


#if _WIN32
	#define SFGP_EXPORT __declspec(dllexport) // TODO: Test
#else
	#define SFGP_EXPORT extern
#endif // _WIN32


// ============================================================================
//
//      Error:
//      Error management for SFGP.
//      
// ============================================================================


/** 
 * @brief Possible errors returned by module procedures.
 */
typedef enum SFGP_Error {
    SFGP_ERROR_OK = 0,
    SFGP_ERROR_FAILED_ALLOCATION = -100
} SFGP_Error;


/** 
 * @brief Returns latest error reported by module.
 * 
 * Returns latest error reported by module before setting its internal error
 * state back to @ref SFGP_ERROR_OK.
 * 
 * @returns Latest error code.
 */
SFGP_EXPORT SFGP_Error SFGP_GetError(void);


// ============================================================================
//
//      Button:
//      Procedures handling extra button functionality for single buttons.
//      
// ============================================================================


/** 
 * @brief internally managed individual gamepad button state
 */
typedef struct SFGP_Button SFGP_Button;


/**
 * @brief 
 * @param self 
 * @return 
 */
SFGP_EXPORT int8_t SFGP_IsButtonPressed(const SFGP_Button *const self);
SFGP_EXPORT int8_t SFGP_IsButtonJustPressed(const SFGP_Button *const self);

SFGP_EXPORT int8_t SFGP_IsButtonReleased(const SFGP_Button *const self);
SFGP_EXPORT int8_t SFGP_IsButtonJustReleased(const SFGP_Button * const self);


// ============================================================================
//
//      Trigger:
//      Procedures handling extra button functionality for single buttons.
//      
// ============================================================================


/** 
 * @brief internally managed individual gamepad analog trigger state 
 */
typedef struct SFGP_Trigger SFGP_Trigger;


SFGP_EXPORT int8_t SFGP_IsTriggerPressed(const SFGP_Trigger *const self);
SFGP_EXPORT int8_t SFGP_IsTriggerJustPressed(const SFGP_Trigger *const self);

SFGP_EXPORT int8_t SFGP_IsTriggerReleased(const SFGP_Trigger *const self);
SFGP_EXPORT int8_t SFGP_IsTriggerJustReleased(const SFGP_Trigger *const self);

SFGP_EXPORT float SFGP_GetTriggerValue(const SFGP_Trigger *const self);
SFGP_EXPORT float SFGP_GetTriggerVelocity(const SFGP_Trigger *const self);


// ============================================================================
//
//      Joystick:
//      Procedures handling extra Joystick functionality.
//      
// ============================================================================


/** 
 * @brief internally managed individual gamepad joystick state 
 */
typedef struct SFGP_Joystick SFGP_Joystick;


SFGP_EXPORT int8_t SFGP_IsXAtMax(const SFGP_Joystick *const self);
SFGP_EXPORT int8_t SFGP_IsXJustAtMax(const SFGP_Joystick *const self);

SFGP_EXPORT int8_t SFGP_IsXAtMin(const SFGP_Joystick *const self);
SFGP_EXPORT int8_t SFGP_IsXJustAtMin(const SFGP_Joystick *const self);

SFGP_EXPORT int8_t SFGP_IsXAtZero(const SFGP_Joystick *const self);
SFGP_EXPORT int8_t SFGP_IsXJustAtZero(const SFGP_Joystick *const self);

SFGP_EXPORT float SFGP_GetXValue(const SFGP_Joystick *const self);
SFGP_EXPORT float SFGP_GetXVelocity(const SFGP_Joystick *const self);

SFGP_EXPORT int8_t SFGP_IsYAtMax(const SFGP_Joystick *const self);
SFGP_EXPORT int8_t SFGP_IsYJustAtMax(const SFGP_Joystick *const self);

SFGP_EXPORT int8_t SFGP_IsYAtMin(const SFGP_Joystick *const self);
SFGP_EXPORT int8_t SFGP_IsYJustAtMin(const SFGP_Joystick *const self);

SFGP_EXPORT int8_t SFGP_IsYAtZero(const SFGP_Joystick *const self);
SFGP_EXPORT int8_t SFGP_IsYJustAtZero(const SFGP_Joystick *const self);

SFGP_EXPORT float SFGP_GetYValue(const SFGP_Joystick *const self);
SFGP_EXPORT float SFGP_GetYVelocity(const SFGP_Joystick *const self);


// ============================================================================
//
//      Gamepad:
//      Structure containing all necessary buttons for driver input.
//      
// ============================================================================


/** 
 * @brief Joystick indexes for @ref SFGP_Gamepad joysticks array.
 * @note These are organized in order in which they should appear in the passed
 * gamepad data array.
 * 
 * @see SFGP_Gamepad
 * @see SFGP_UpdateGamepad()
 */
typedef enum SFGP_JoystickIndex {
    SFGP_JOYSTICK_LEFT,
    SFGP_JOYSTICK_RIGHT,

    SFGP_JOYSTICK_ELEM
} SFGP_JoystickIndex;

/** 
 * @brief Trigger indexes for @ref SFGP_Gamepad triggers array.
 * @note These are organized in order in which they should appear in the passed
 * gamepad data array.
 * 
 * @see SFGP_Gamepad
 * @see SFGP_UpdateGamepad()
 */
typedef enum SFGP_TriggerIndex {
    SFGP_TRIGGER_LEFT,
    SFGP_TRIGGER_RIGHT,

    SFGP_TRIGGER_ELEM
} SFGP_TriggerIndex;

/** 
 * @brief Button indexes for @ref SFGP_Gamepad buttons array.
 * @note These are organized in order of which bit they occupy in the passed
 * gamepad array data's button bit integer.
 * 
 * @see SFGP_Gamepad
 * @see SFGP_UpdateGamepad()
 */
typedef enum SFGP_ButtonIndex {
    SFGP_TOUCHPAD_FINGER_1,
    SFGP_TOUCHPAD_FINGER_2,
    SFGP_TOUCHPAD,

    SFGP_BUTTON_STICK_LEFT,
    SFGP_BUTTON_STICK_RIGHT,

    SFGP_BUTTON_DPAD_UP,
    SFGP_BUTTON_DPAD_DOWN,
    SFGP_BUTTON_DPAD_LEFT,
    SFGP_BUTTON_DPAD_RIGHT,
    
    SFGP_BUTTON_A,
    SFGP_BUTTON_B,
    SFGP_BUTTON_X,
    SFGP_BUTTON_Y,

    SFGP_BUTTON_GUIDE,
    SFGP_BUTTON_START,
    SFGP_BUTTON_BACK,

    SFGP_BUTTON_BUMPER_LEFT,
    SFGP_BUTTON_BUMPER_RIGHT,

    SFGP_BUTTON_ELEM
} SFGP_ButtonIndex;


/** 
 * @brief Gamepad data intended to be accessed by end user of SFGP.
 * 
 * This struct contains all Buttons, Triggers, and Joysticks found on the
 * minimum competition-compliant controllers.
 * 
 * @note PS Controller and rumble support has not been added as of current.
 * Please use respective bindings in order to access your gamepad directly to
 * access these features.
 */
typedef struct SFGP_Gamepad {
    // unions for easier initialization and updating values. Could also be used
    // for mapping PS buttons where original XBox ones are...

    union {
        SFGP_Joystick *joysticks[SFGP_JOYSTICK_ELEM];

        struct {
            SFGP_Joystick *left_stick;
            SFGP_Joystick *right_stick;
        };
    };

    union {
        SFGP_Trigger *triggers[SFGP_TRIGGER_ELEM];

        struct {
            SFGP_Trigger *left_trigger;
            SFGP_Trigger *right_trigger;
        };
    };

    union {
        SFGP_Button *buttons[SFGP_BUTTON_ELEM];

        struct {
            SFGP_Button *touchpad_finger_1;
            SFGP_Button *touchpad_finger_2;
            SFGP_Button *touchpad;

            SFGP_Button *left_stick_button;
            SFGP_Button *right_stick_button;

            SFGP_Button *dpad_up;
            SFGP_Button *dpad_down;
            SFGP_Button *dpad_left;
            SFGP_Button *dpad_right;

            SFGP_Button *a;
            SFGP_Button *b;
            SFGP_Button *x;
            SFGP_Button *y;

            SFGP_Button *guide;
            SFGP_Button *start;
            SFGP_Button *back;

            SFGP_Button *left_bumper;
            SFGP_Button *right_bumper;
        };
    };
} SFGP_Gamepad;


/**
 * @brief Initailizes internals of gamepad.
 * 
 * Allocates button, trigger, and joysticks arrays to be accessed directly by
 * end user. If an error does occur, its probably for the best that you end the
 * application prematurely.
 * 
 * @param[in]   pad: Pointer to gamepad object with members to be allocated
 *              and initialized.
 * 
 * @returns `SFGP_ERROR_OK` if everything goes ok, a negative error code if 
 * otherwise.
 * 
 * @note This function does not check for `NULL` pointers on release.
 */
SFGP_EXPORT SFGP_Error SFGP_InitGamepad(SFGP_Gamepad *const pad);
SFGP_EXPORT void SFGP_DeinitGamepad(const SFGP_Gamepad *const pad);

SFGP_EXPORT SFGP_Error SFGP_UpdateGamepad(SFGP_Gamepad *const pad, 
        const uint8_t *const byte_array);

#ifdef __cplusplus
    }
#endif // __cplusplus

#endif // __SFL_SFGP_GAMEPAD_HEADER__