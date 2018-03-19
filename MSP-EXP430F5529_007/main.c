/*******************************************************************************
 *
 *      MSP-EXP430F5529_007: Rectangle function test
 *
 *******************************************************************************
 * FileName:        main.c
 * Processor:       MSP430F5529
 * Complier:        CCS 7.2.0.00013
 * Author:          Pedro Sánchez Ramírez (MrChunckuee)
 * Blog:            http://mrchunckuee.blogspot.com/
 * Email:           mrchunckuee.psr@gmail.com
 * Description:     Pequeño ejemplo  para mostrar el funcionamiento de la funcion
 *                  rectangle, agregada recientemente a la libreria HAL_Dogs102x6
 *******************************************************************************
 * Rev.     Date        Comment
 *  v0.01   18/03/2018  - Creación del firmware
 ******************************************************************************/
#include <msp430.h> 
#include <stdlib.h>
#include "HAL_Dogs102x6.h"
#include "imagenes.h"

unsigned char countLine = 0;

/********** P R O T O T Y P E S *************/
void MCU_Init(void);
void MCU_Delayms(int16_t time);

void main(void){
    MCU_Init();

    // Display MrChunckuee Logo
    // and welcome message
    Dogs102x6_imageDraw(mrchunckueeLogo, 0, 0);
    MCU_Delayms(2000);
	Dogs102x6_clearScreen();
	Dogs102x6_stringDraw(1, 0, " MSP-EXP430F5529 ", DOGS102x6_DRAW_NORMAL);
    Dogs102x6_stringDraw(3, 0, "    Welcome!!    ", DOGS102x6_DRAW_NORMAL);
    Dogs102x6_stringDraw(4, 0, "  @MrChunckuee   ", DOGS102x6_DRAW_NORMAL);
    Dogs102x6_stringDraw(6, 0, "http://e2e.ti.com", DOGS102x6_DRAW_NORMAL);
    MCU_Delayms(2000);
    Dogs102x6_clearScreen();

	// Main loop
	while (1){
	    P1OUT ^= BIT0;  // XOR P1.0
        Dogs102x6_rectangleDraw(0, 0, 101, 63, 0, DOGS102x6_DRAW_NORMAL);
        Dogs102x6_rectangleDraw(5, 5, 96, 58, 0, DOGS102x6_DRAW_NORMAL);
        Dogs102x6_rectangleDraw(10, 12, 42, 17, 1, DOGS102x6_DRAW_NORMAL);
        Dogs102x6_rectangleDraw(10, 19, 42, 24, 0, DOGS102x6_DRAW_NORMAL);
        Dogs102x6_rectangleDraw(46, 10, 51, 42, 1, DOGS102x6_DRAW_NORMAL);
        Dogs102x6_rectangleDraw(53, 10, 58, 42, 0, DOGS102x6_DRAW_NORMAL);
        Dogs102x6_lineDraw(10, 10, countLine+10, 10, DOGS102x6_DRAW_NORMAL);
        Dogs102x6_rectangleDraw(10, 26, countLine+10, 31, 1, DOGS102x6_DRAW_NORMAL);
        Dogs102x6_lineDraw(44, 10, 44, countLine+10, DOGS102x6_DRAW_NORMAL);
        Dogs102x6_rectangleDraw(60, 10, 65, countLine+10, 1, DOGS102x6_DRAW_NORMAL);
        countLine++;
        if (countLine==33){
            countLine = 0;
            Dogs102x6_lineDraw(10, 10, 42, 10, DOGS102x6_DRAW_INVERT);
            Dogs102x6_rectangleDraw(10, 26, 42, 31, 1, DOGS102x6_DRAW_INVERT);
            Dogs102x6_lineDraw(44, 10, 44, 42, DOGS102x6_DRAW_INVERT);
            Dogs102x6_rectangleDraw(60, 10, 65, 42, 1, DOGS102x6_DRAW_INVERT);
        }
	    MCU_Delayms(100);
	}
}

void MCU_Init(void){
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    // Basic GPIO initialization
    // Configure Dogs102x6 ports
    P5OUT &= ~(BIT6 + BIT7);        // LCD_C/D, LCD_RST
    P5DIR |= BIT6 + BIT7;
    P7OUT &= ~(BIT4 + BIT6);        // LCD_CS, LCD_BL_EN
    P7DIR |= BIT4 + BIT6;
    P4OUT &= ~(BIT1 + BIT3);        // SIMO, SCK
    P4DIR &= ~BIT2;                 // SOMI pin is input
    P4DIR |= BIT1 + BIT3;

    //General GPIOs initialization
    P1DIR |= BIT0;      // P1.0 output
    P1OUT &= ~BIT0;     //Clear LED1

    // Set up LCD
    Dogs102x6_init();
    Dogs102x6_backlightInit();
    Dogs102x6_setBacklight(11);
    Dogs102x6_setContrast(11);
    Dogs102x6_clearScreen();
}

void MCU_Delayms(int16_t time){
    int16_t delayCount;
    for (delayCount=0; delayCount<time; ++delayCount)
        __delay_cycles(1000); // 1ms = 1000 clocks at 1MHz

    return;
}
