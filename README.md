# on-off-on
On-Off-On Controller.  Could also be called a symmetrical, bi-directional, bang-bang controller.  In this case, symmetrical means the hysteresis is the shared for both on conditions.

## Usage
```C
static on_off_on_t controller;
static const on_off_on_config_t controller_config = { .hysteresis = 10 };

static void controller_task(void)
{
    init_on_off_on(&controller, &controller_config);

    set_on_off_on_setpoint(&controller, DEFAULT_SETPOINT);

    while(true)
    {
        float input = get_input();

        on_off_on_state_e state = compute_on_off_on(&controller, input);

        switch(state)
        {
            case ON_OFF_ON_STATE_STEADY_STATE:
                turn_plant_off();
                break;

            case ON_OFF_ON_STATE_FORWARD:
                turn_plant_on(FORWARD);
                break;

            case ON_OFF_ON_STATE_BACKWARD:
                turn_plant_on(BACKWARD);
                break;
        }
    }
}
```

## State Diagram

```
                          ┌──────────────┐                          
                          │              │                          
             ┌────────────▶   FORWARD    ├────────────┐             
             │            │              │            │             
             │            └──────────────┘            │             
             │                                 input rises above    
             │                                     setpoint         
     input falls below                                │             
  (setpoint - hysteresis)         ┌───────────────────┘             
             │            ┌───────▼──────┐                          
             │            │              │                          
             └────────────┤ STEADY STATE ├────────────┐             
                          │              │            │             
                          └───────▲──────┘            │             
             ┌────────────────────┘           input rises above     
             │                             (setpoint + hysteresis)  
    input falls below                                 │             
        setpoint                                      │             
             │            ┌──────────────┐            │             
             │            │              │            │             
             └────────────┤   BACKWARD   ◀────────────┘             
                          │              │                          
                          └──────────────┘                          
```


## State Behavior

```
       ▲                                                                   
       │                                      ┏━━━━┓                       
SP + HY├     ─     ─     ─     ─     ─     ─  ┃  ─ ┗━┓ ─     ─     ─       
       │                                ┏━━━━━┛      ┗━┓                   
       │                            ┏━━━┛              ┗━┓                 
       │                     ┏━━━━━━┛                    ┗━┓               
    SP ├ ─ ─ ─ ─ ─ ─ ─ ─ ─┏━━┻ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ┻━┳ ─ ─ ─ ─ ─   
       │               ┏━━┛                                  ┗━━━━━━━━━    
       │           ┏━━━┛                                                   
       │       ┏━━━┛                                                       
SP + HY├   ┏━━━┛   ─     ─     ─     ─     ─     ─     ─     ─     ─       
       │━━━┛                                                               
       /                                                                   
       /                                                                   
   ◀───┼───────────────────────────────────────────────────────────────▶   
       ├─────────────────────┬────────────────┬──────────────┬────────────┐
       ▼       FORWARD       │  STEADY STATE  │   BACKWARD   │STEADY STATE│
       └─────────────────────┴────────────────┴──────────────┴────────────┘
```
