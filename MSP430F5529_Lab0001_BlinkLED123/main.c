/* --COPYRIGHT--,BSD
 * Copyright (c) 2017, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * --/COPYRIGHT--*/

/*******************************************************************************
 *
 *      MSP-EXP430F5529_Lab0001: BlinkLED123
 *
 *******************************************************************************
 * FileName:        main.c
 * Processor:       MSP430F5529
 * Complier:        CCS 20.5.0.28
 * Author:          Pedro Sánchez Ramírez (MrChunckuee)
 * Blog:            http://mrchunckuee.blogspot.com/
 * Email:           mrchunckuee.electronics@gmail.com
 * Description:     Testing a example, toggle LEDs on pin P1.0, P8.0 and P8.2
 *******************************************************************************
 * Rev.     Date        Comment
 *  v0.0.1  26/08/2017  Testing using MSP-EXP430f5529 USB Experimental Board.
 *  v0.0.2  28/03/2026  Compiled on CCS 20.5.0.28 and test on board.  
 *                      Used more LEDs (1, 2 and 3)
 ******************************************************************************/

#include <msp430.h>

void main(void){
  volatile unsigned int i;

  WDTCTL = WDTPW + WDTHOLD; // Stop WDT
  P1DIR |= BIT0;            // P1.0 set as output
  P8DIR |= (BIT2 + BIT1);     // P8.2 and P8.1 as outputs
  
  P1OUT &= ~BIT0; // LED1 = Off
  P8OUT |= BIT1;  // LED2 = On
  P8OUT &= ~BIT2; // LED3 = Off      
 
  while(1){                 
    P1OUT ^= BIT0;          // XOR P1.0
    P8OUT ^= (BIT2 + BIT1); // XOR P8.2 & P8.1
    for(i=50000; i>0; i--);   // Delay
  }
} 
