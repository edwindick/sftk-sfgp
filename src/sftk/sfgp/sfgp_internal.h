/** @cond INTERNAL */

#ifndef __SFTK_SFGP_INTERNAL_HEADER__
#define __SFTK_SFGP_INTERNAL_HEADER__


// ============================================================================
//
//      Error:
//      Error management for SFGP.
//      
// ============================================================================ 


/**
 * @brief Sets error state of module and returns the same value.
 * @param[in]   code: error code
 * @return
 */
extern SFGP_Error _SFGP_SetError(SFGP_Error code);


// ============================================================================
//
//      Button:
//      Procedures handling extra button functionality for single buttons.
//      
// ============================================================================


/**
 * @brief Update button values.
 * 
 * updates button members according to \p value supplied to function. .last
 * will be set to .current, and .current will be set to \p value.
 * 
 * @param[in]   self: The button whos values to set.
 * @param[in]   value: Value to set current button state to.
 */
extern void _SFGP_SetButton(SFGP_Button *const self, int8_t value);


// ============================================================================
//
//      Trigger:
//      Procedures handling extra button functionality for single buttons.
//      
// ============================================================================


/**
 * @brief Data required to perform checks on an individual trigger.
 * 
 * @note Placed in sfgp_internal.h as joystick objects reference trigger 
 * members.
 */
struct SFGP_Trigger {
    float last;     /**< Last known value of trigger. */
    float current;  /**< Latest known value of trigger. */
};


/**
 * @brief Update trigger values.
 * 
 * updates trigger members according to \p value supplied to function. .last
 * will be set to .current, and .current will be set to \p value.
 * 
 * @param[in]   self: The trigger whos values to set.
 * @param[in]   value: Value to set current trigger state to.
 */
extern void _SFGP_SetTrigger(SFGP_Trigger *const self, float value);


// ============================================================================
//
//      Joystick:
//      Procedures handling extra Joystick functionality.
//      
// ============================================================================


extern void _SFGP_SetJoystick(SFGP_Joystick *const self, 
        float curr_x, float curr_y);


#endif // __SFTK_SFGP_INTERNAL_HEADER__

/** @endcond */ // INTERNAL