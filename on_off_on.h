////////////////////////////////////////////////////////////////////////////////
//!
//! @file             on_off_on.h
//!
//! @author           michaelchiasson
//!
////////////////////////////////////////////////////////////////////////////////

#ifndef ON_OFF_ON_H__
#define ON_OFF_ON_H__


///////////////////////////////////////////////////////////////////////////////
//  Includes
///////////////////////////////////////////////////////////////////////////////

#include <stdint.h>


///////////////////////////////////////////////////////////////////////////////
//  Public Macros
///////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////
//  Public Types
///////////////////////////////////////////////////////////////////////////////

typedef enum
{
    ON_OFF_ON_STATE_STEADY_STATE,
    ON_OFF_ON_STATE_FORWARD,
    ON_OFF_ON_STATE_BACKWARD
} on_off_on_state_e;

typedef struct
{
    on_off_on_state_e state;

    float hysteresis;
    float setpoint;
} on_off_on_t;

typedef struct
{
    float hysteresis;
} on_off_on_config_t;


///////////////////////////////////////////////////////////////////////////////
//  Public Data Declarations
///////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////
//  Public Functions Prototypes
///////////////////////////////////////////////////////////////////////////////

/**
 * Initializes the controller
 *
 * @param[out] controller Controller to be initialized
 * @param[in] config Configuration for initialization
 */
void init_on_off_on(on_off_on_t *controller, const on_off_on_config_t *config);

/**
 * Helper to set the Controller's Setpoint
 *
 * @param[in] controller
 * @param[in] setpoint
 */
void set_on_off_on_setpoint(on_off_on_t *controller, float setpoint);

/**
 * Computes the state of the controller
 *
 * @param[in] controller
 * @param[in] input Process Variable
 * @returns Controller state after computation
 */
on_off_on_state_e compute_on_off_on(on_off_on_t *on_off_on, float input);

/**
 * Helper to set the Controller's hysteresis
 *
 * @param[in]  controller
 * @param[in]  hysteresis
 */
void set_on_off_on_hysteresis(on_off_on_t *controller, float hysteresis);

/**
 * Helper to get the Controller's current state
 *
 * @param[in]  controller
 * @returns Controller state before a computation
 */
on_off_on_state_e get_on_off_on_state(on_off_on_t *controller);


#endif // end of include guard: ON_OFF_ON_H__


