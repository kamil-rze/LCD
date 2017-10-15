/*
 * File:   mess.c
 * Author: Microchip
 *
 * Created on 04 October 2017, 22:03
 */


#include <xc.h>


void LCD_Init(){
    // Power up delay
    __delay_ms(100);
    
    // Function set 8-bit interface
    PORTD = 0x03;

    // 5ms delay
    __delay_ms(5);

    // Function set 8-bit interface
    PORTD = 0x03;
    
    // MOre than 100us delay
    __delay_us(150);

    // Function set 8-bit interface
    PORTD = 0x03;

    // Function set to 4-bit operation.
    PORTD = 0x02;
    __delay_us(150);

    // Step 8
    PORTD = 0x02;   // Function set to 4-bit operation.
    PORTD = 0x04;   // Number of lines(N) and font (F)
    __delay_us(150);

    // Step 9
    PORTD = 0x00;   // Display On
    PORTD = 0x04;   // Number of lines(N) and font (F)
    __delay_us(150);

    // Step 10
    PORTD = 0x00;   // Display On
    PORTD = 0x01;
    __delay_ms(5);

    // Step 11
    PORTD = 0x00;   // Display On
    PORTD = 0x06;   // Increment and no shift
    __delay_us(150);

    // Step 12
//    PORTD = 0x00;   // Display On
//    PORTD = 0b11110000;
//    __delay_us(150);
}
