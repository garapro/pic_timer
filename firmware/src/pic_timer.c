/*******************************************************************************
  MPLAB Harmony Application Source File
  
  Company:
    Microchip Technology Inc.
  
  File Name:
    pic_timer.c

  Summary:
    This file contains the source code for the MPLAB Harmony application.

  Description:
    This file contains the source code for the MPLAB Harmony application.  It 
    implements the logic of the application's state machine and it may call 
    API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware.  However, it does not call any of the
    system interfaces (such as the "Initialize" and "Tasks" functions) of any of
    the modules in the system or make any assumptions about when those functions
    are called.  That is the responsibility of the configuration-specific system
    files.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013-2014 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 *******************************************************************************/
// DOM-IGNORE-END


// *****************************************************************************
// *****************************************************************************
// Section: Included Files 
// *****************************************************************************
// *****************************************************************************

#include "pic_timer.h"

// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the APP_Initialize function.
    
    Application strings and buffers are be defined outside this structure.
*/

PIC_TIMER_DATA pic_timerData;

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

/* TODO:  Add any necessary callback functions.
*/

// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************


/* TODO:  Add any necessary local functions.
*/
/*** add ***/
static void callbackTimer( uintptr_t context, uint32_t currTick );
/*** add ***/

// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void PIC_TIMER_Initialize ( void )

  Remarks:
    See prototype in pic_timer.h.
 */

void PIC_TIMER_Initialize ( void )
{
    /* Place the App state machine in its initial state. */
    pic_timerData.state = PIC_TIMER_STATE_INIT;

    
    /* TODO: Initialize your application's state machine and other
     * parameters.
     */
}


/******************************************************************************
  Function:
    void PIC_TIMER_Tasks ( void )

  Remarks:
    See prototype in pic_timer.h.
 */

void PIC_TIMER_Tasks ( void )
{

    /* Check the application's current state. */
    switch ( pic_timerData.state )
    {
        /* Application's initial state. */
        case PIC_TIMER_STATE_INIT:
        {
            bool appInitialized = true;
       
            /*** add ***/
            pic_timerData.ledStatus = false;
            
            // 2秒間隔の周期タイマー設定
            pic_timerData.tmrHandle = SYS_TMR_ObjectCreate( 2000, NULL, callbackTimer, SYS_TMR_FLAG_PERIODIC );
            /*** add ***/
            if (appInitialized)
            {
            
                pic_timerData.state = PIC_TIMER_STATE_SERVICE_TASKS;
            }
            break;
        }

        case PIC_TIMER_STATE_SERVICE_TASKS:
        {
        
            break;
        }

        /* TODO: implement your application state machine.*/
        

        /* The default state should never be executed. */
        default:
        {
            /* TODO: Handle error in application's state machine. */
            break;
        }
    }
}

/*** add ***/
static void callbackTimer( uintptr_t context, uint32_t currTick ){
    // 2秒間隔で呼ばれる
    if(pic_timerData.ledStatus){
        // LED ON 状態
        LEDOff();
        pic_timerData.ledStatus = false;
    }
    else
    {
        // LED OFF 状態
        LEDOn();
        pic_timerData.ledStatus = true;
    }
    return;
}
/*** add ***/

/*******************************************************************************
 End of File
 */
