/*******************************************************************************
 *
 *      MSP-EXP430F5529_008: Temperature sensor using LM35
 *
 *******************************************************************************
 * FileName:        main.c
 * Processor:       MSP430F5529
 * Complier:        CCS 7.2.0.00013
 * Author:          Pedro Sánchez Ramírez (MrChunckuee)
 * Blog:            http://mrchunckuee.blogspot.com/
 * Email:           mrchunckuee.psr@gmail.com
 * Description:     Basic temperature sensor using the LM35
 *******************************************************************************
 * Rev.     Date        Comment
 *  v0.00   16/104/2018  - Firmware creation
 ******************************************************************************/
#include <msp430.h> 
#include <stdlib.h>
#include "HAL_Dogs102x6.h"
#include "special.h"
#include "imagenes.h"

char temperatureLCD[20];
int adcValue;
uint8_t barTemperatureLevel;
double temperature;
unsigned char muestras, overTemperature;

/********** P R O T O T Y P E S *************/
void MCU_Init(void);
void MCU_Delayms(int16_t time);
void ADC_Init(void);
int16_t ADC_Get(void);
void GUI_Init(void);
void GUI_WelcomeMessage(void);
void GUI_SetTemperature(void);

void main(void){
    MCU_Init();
    GUI_WelcomeMessage();
    GUI_Init();

	// Main loop
	while (1){
	    adcValue += ADC_Get();
	    muestras++;
	    if(muestras==32){
	        P1OUT ^= BIT0;  // XOR P1.0
	        muestras=0;
	        adcValue=adcValue>>5;
	        temperature = adcValue*0.08;
	        if(temperature>45)
	            overTemperature=0xFF;
	        else
	            overTemperature=0x00;
	        barTemperatureLevel=(uint8_t)(temperature-10);
	        barTemperatureLevel=35-barTemperatureLevel;
	        SPECIAL_ftoa(temperature, 1, temperatureLCD);
	        GUI_SetTemperature();
	    }
	    if(overTemperature==0xFF)
	        P1OUT ^= BIT0;  // XOR P1.0
	    MCU_Delayms(32);
	}
}

void GUI_Init(void){
    // Set default values on LCD
    Dogs102x6_clearScreen();
    Dogs102x6_imageDraw(barTemp, 0, 0);
    Dogs102x6_stringDraw(0, 0, " MSP-EXP430F5529 ", DOGS102x6_DRAW_NORMAL);
    Dogs102x6_stringDraw(2, 4, "Temperature", DOGS102x6_DRAW_NORMAL);
    Dogs102x6_stringDraw(4, 4, "       C", DOGS102x6_DRAW_NORMAL);
    Dogs102x6_stringDrawXY(40, 28, ".", DOGS102x6_DRAW_NORMAL);
    Dogs102x6_stringDrawXY(78, 42, "10", DOGS102x6_DRAW_NORMAL);
    Dogs102x6_stringDrawXY(78, 32, "20", DOGS102x6_DRAW_NORMAL);
    Dogs102x6_stringDrawXY(78, 22, "30", DOGS102x6_DRAW_NORMAL);
    Dogs102x6_stringDrawXY(78, 12, "40", DOGS102x6_DRAW_NORMAL);
}

void GUI_WelcomeMessage(void){
    // Display MrChunckuee Logo
    // and welcome message
    Dogs102x6_imageDraw(mrchunckueeLogo, 0, 0);
    MCU_Delayms(2000);
    Dogs102x6_clearScreen();
    Dogs102x6_stringDraw(1, 0, " MSP-EXP430F5529 ", DOGS102x6_DRAW_NORMAL);
    Dogs102x6_stringDraw(3, 0, "   Thermometer   ", DOGS102x6_DRAW_NORMAL);
    Dogs102x6_stringDraw(5, 0, "  @MrChunckuee   ", DOGS102x6_DRAW_NORMAL);
    Dogs102x6_stringDraw(7, 0, "http://e2e.ti.com", DOGS102x6_DRAW_NORMAL);
    MCU_Delayms(2000);
}

void GUI_SetTemperature(void){
    // Set temperature on LCD
    Dogs102x6_stringDraw(4, 15, &temperatureLCD[0], DOGS102x6_DRAW_NORMAL);
    // Set bar temperature on LCD
    if(barTemperatureLevel>35){
        Dogs102x6_rectangleDraw(92, 15, 93, 50, 1, DOGS102x6_DRAW_NORMAL);
    }
    else{
        Dogs102x6_rectangleDraw(92, 15, 93, 15+barTemperatureLevel, 1, DOGS102x6_DRAW_INVERT);
        Dogs102x6_rectangleDraw(92, 15+barTemperatureLevel, 93, 50, 1, DOGS102x6_DRAW_NORMAL);
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

    // ADC Init
    ADC_Init();

    //Clear values
    adcValue = 0;
    barTemperatureLevel = 0;
    overTemperature = 0x00;
    temperature = 0;
    muestras = 0;
}

void MCU_Delayms(int16_t time){
    int16_t delayCount;
    for (delayCount=0; delayCount<time; ++delayCount)
        __delay_cycles(1000); // 1ms = 1000 clocks at 1MHz

    return;
}

void ADC_Init(void){
    ADC12CTL0 = ADC12SHT02 + ADC12ON; // Sampling time, ADC12 on
    ADC12CTL1 = ADC12SHP;             // Use sampling timer
    ADC12MCTL0 = ADC12INCH_6;//5;     // Use A6  as input
    ADC12CTL0 |= ADC12ENC;            // Enable conversions
    P6SEL |= BIT6;//BIT5;             // P6.6 ADC option select (A6)
    //P8DIR |= BIT0;                    // P8.0 output
    //P8OUT |= BIT0;                    // Set P8.0 high
}

int16_t ADC_Get(void){
    ADC12CTL0 |= ADC12SC;       // Start reading
    while (ADC12CTL0 & BUSY);   // Waiting to read
    return ADC12MEM0;           // Return value on adc
}

