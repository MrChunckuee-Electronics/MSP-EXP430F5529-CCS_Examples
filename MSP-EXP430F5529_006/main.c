#include <msp430.h> 
#include <stdlib.h>
#include "HAL_Dogs102x6.h"
#include "imagenes.h"

/********** P R O T O T Y P E S *************/
void MCU_Init(void);
void MCU_Delayms(int16_t time);
void hallowen_animation(void);

/**
 * main.c
 */
void main(void){
    MCU_Init();
    // Display MrChunckuee Logo
    Dogs102x6_imageDraw(mrchunckueeLogo, 0, 0);
    MCU_Delayms(2000);
    Dogs102x6_clearScreen();
    hallowen_animation();
	// Main loop
	while (1){
	    Dogs102x6_setInverseDisplay();
	    Dogs102x6_imageDraw(happy_halloween, 0, 0);
	    MCU_Delayms(200);
	    Dogs102x6_clearInverseDisplay();
	    Dogs102x6_imageDraw(happy_halloween, 0, 0);
	    MCU_Delayms(200);
	}
}

void hallowen_animation(void){
    // Display hallowen animation
            Dogs102x6_imageDraw(halloween1, 0, 0);
            MCU_Delayms(1000);
            Dogs102x6_clearScreen();
            Dogs102x6_imageDraw(halloween2, 0, 0);
            MCU_Delayms(1000);
            Dogs102x6_clearScreen();
            Dogs102x6_imageDraw(halloween3, 0, 0);
            Dogs102x6_stringDraw(7, 0, "!MrChunckuee!", DOGS102x6_DRAW_NORMAL);
            MCU_Delayms(1000);
            Dogs102x6_clearScreen();
            Dogs102x6_imageDraw(halloween4, 0, 0);
            Dogs102x6_stringDraw(7, 0, " !MrChunckuee!", DOGS102x6_DRAW_NORMAL);
            MCU_Delayms(1000);
            Dogs102x6_clearScreen();
            Dogs102x6_imageDraw(halloween5, 0, 0);
            Dogs102x6_stringDraw(7, 0, "  !MrChunckuee!", DOGS102x6_DRAW_NORMAL);
            MCU_Delayms(1000);
            Dogs102x6_clearScreen();
            Dogs102x6_imageDraw(halloween6, 0, 0);
            MCU_Delayms(1000);
            Dogs102x6_clearScreen();
            Dogs102x6_imageDraw(halloween7, 0, 0);
            MCU_Delayms(1000);
            Dogs102x6_clearScreen();
            Dogs102x6_imageDraw(halloween8, 0, 0);
            MCU_Delayms(1000);
            Dogs102x6_clearScreen();
            Dogs102x6_imageDraw(halloween9, 0, 0);
            MCU_Delayms(1000);
            Dogs102x6_clearScreen();
            Dogs102x6_imageDraw(halloween10, 0, 0);
            MCU_Delayms(1000);
            Dogs102x6_clearScreen();
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
