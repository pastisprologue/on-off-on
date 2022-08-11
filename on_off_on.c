////////////////////////////////////////////////////////////////////////////////
//!
//! @file             on_off_on.c
//!
//! @author           michaelchiasson
//!
////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
//  Includes
///////////////////////////////////////////////////////////////////////////////

// Interface to this file
#include "on_off_on.h" 


///////////////////////////////////////////////////////////////////////////////
//  Private Macros
///////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////
//  Private Types
///////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////
//  Private Function Prototypes
///////////////////////////////////////////////////////////////////////////////

on_off_on_state_e set_on_off_on_state(on_off_on_t *controller, 
    on_off_on_state_e new_state);


///////////////////////////////////////////////////////////////////////////////
//  Public Data
///////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////
//  Private Data
///////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////
//  Public Function Implementations
///////////////////////////////////////////////////////////////////////////////

void init_on_off_on(on_off_on_t *controller, const on_off_on_config_t *config)
{
    controller->state = ON_OFF_ON_STATE_STEADY_STATE;
    controller->hysteresis = config->hysteresis;
}

on_off_on_state_e compute_on_off_on(on_off_on_t *controller, float input)
{
    switch (controller->state)
    {
        case ON_OFF_ON_STATE_FORWARD:
            if (input > (controller->setpoint))
            {
                return set_on_off_on_state(
                    controller,
                    ON_OFF_ON_STATE_STEADY_STATE
                );
            } 
            break;

        case ON_OFF_ON_STATE_BACKWARD:
            if (input < (controller->setpoint))
            {
                return set_on_off_on_state(
                    controller,
                    ON_OFF_ON_STATE_STEADY_STATE
                );
            }
            break;

        case ON_OFF_ON_STATE_STEADY_STATE:
            if (input < (controller->setpoint - controller->hysteresis))
            {
                return set_on_off_on_state(
                    controller,
                    ON_OFF_ON_STATE_FORWARD
                );
            } 

            if (input > (controller->setpoint + controller->hysteresis))
            {
                return set_on_off_on_state(
                    controller,
                    ON_OFF_ON_STATE_BACKWARD
                );
            }
            break;
    }

    return controller->state;
}

void set_on_off_on_setpoint(on_off_on_t *controller, float setpoint)
{
    controller->setpoint = setpoint;
}

void set_on_off_on_hysteresis(on_off_on_t *controller, float hysteresis)
{
    controller->hysteresis = hysteresis;
}

on_off_on_state_e get_on_off_on_state(on_off_on_t *controller)
{
    return controller->state;
}


///////////////////////////////////////////////////////////////////////////////
//  Private Function Implementations
///////////////////////////////////////////////////////////////////////////////

on_off_on_state_e set_on_off_on_state(on_off_on_t *controller,
    on_off_on_state_e new_state)
{
    controller->state = new_state;

    return controller->state;
}




