/********************************************************************
 * FileName:		int_enable_interrupts_lib.c
 * Dependencies:
 * Processor:		PIC32
 * Hardware:		N/A
 * Assembler:		N/A
 * Linker:		    N/A
 * Company:		    Microchip Technology Inc.
 *
 * Software License Agreement:
 * The software supplied herewith by Microchip Technology Incorporated
 * (the “Company”) for its PICmicro® Microcontroller is intended and
 * supplied to you, the Company’s customer, for use solely and
 * exclusively on Microchip PICmicro Microcontroller products. The
 * software is owned by the Company and/or its supplier, and is
 * protected under applicable copyright laws. All rights are reserved.
 * Any use in violation of the foregoing restrictions may subject the
 * user to criminal sanctions under applicable laws, as well as to
 * civil liability for the breach of the terms and conditions of this
 * license.
 *
 * THIS SOFTWARE IS PROVIDED IN AN “AS IS” CONDITION. NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 * TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 * IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 * $Id: int_enable_interrupts_lib.c 3048 2007-04-19 16:33:08Z rajbhartin $
 * $Name:  $

 ********************************************************************/

#include <xc.h>
#include <peripheral/int.h>

/*********************************************************************
 * Function:        mINTEnableInterrupts()
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    Interrupts are enabled
 *
 * Overview:        Interrupts are enabled by setting the IE bit
 *                  in the status register
 ********************************************************************/
unsigned int __attribute__((nomips16))  INTEnableInterrupts(void)
{
    unsigned int status = 0;

    asm volatile("ei    %0" : "=r"(status));

    return status;
}


/*********************************************************************
* Function:        void INTEnableSystemMultiVectoredInt(void)
*
* PreCondition:    EBASE and IntCtl.VS set up
*
* Input:           None
*
* Output:          None
*
* Side Effects:    System interrupts are turned on
*
* Overview:        Enables system wide multi-vectored interrupts
********************************************************************/
void __attribute__((nomips16)) INTEnableSystemMultiVectoredInt(void)
{
	unsigned int val;

	// set the CP0 cause IV bit high
	asm volatile("mfc0   %0,$13" : "=r"(val));
	val |= 0x00800000;
	asm volatile("mtc0   %0,$13" : "+r"(val));

	INTCONSET = _INTCON_MVEC_MASK;

	// set the CP0 status IE bit high to turn on interrupts
	INTEnableInterrupts();

}

/*********************************************************************
* Function:       void INTEnableSystemSingleVectoredInt(void)
*
* PreCondition:    EBASE and IntCtrl.VS set up (VS = 0)
*
* Input:           None
*
* Output:          None
*
* Side Effects:    Single vectored interrupts are turned on
*
* Overview:        Enables system wide single vectored interrupts
********************************************************************/
void __attribute__((nomips16)) INTEnableSystemSingleVectoredInt(void)
{
	unsigned int val;

	// set the CP0 cause IV bit high
	asm volatile("mfc0   %0,$13" : "=r"(val));
	val |= 0x00800000;
	asm volatile("mtc0   %0,$13" : "+r"(val));

	INTCONCLR = _INTCON_MVEC_MASK;

	// set the CP0 status IE bit high to turn on interrupts
	INTEnableInterrupts();
}