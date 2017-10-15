/*
 * File:   main_LCD.c
 * Author: Microchip
 *
 * Created on 04 October 2017, 20:48
 */

#define _XTAL_FREQ 8000000UL

#include <xc.h>
#include "Fuses.h"

#define RS  0x10
#define E   0x20



void Init(void){
    OSCCON = 0x71;
    ANSEL = 0x00;
    ANSELH = 0x00;
    PORTA = PORTB = PORTD = PORTD = PORTE = 0x00;
    TRISA = TRISB = TRISC = TRISD = TRISE = 0x00;
}





void lcd_reset()
{
PORTD = 0xFF;
__delay_ms(20);
PORTD = 0x03 + E;
PORTD = 0x03;
__delay_ms(10);
PORTD = 0x03 + E;
PORTD = 0x03;
__delay_ms(1);
PORTD = 0x03 + E;
PORTD = 0x03;
__delay_ms(1);
PORTD = 0x02 + E;
PORTD = 0x02;
__delay_ms(1);
}

void lcd_cmd (char cmd)
{
PORTD = (unsigned)((cmd >> 4) & 0x0F) | E;
PORTD = (unsigned)((cmd >> 4) & 0x0F);
PORTD = (unsigned)(cmd & 0x0F) | E;
PORTD = (unsigned)(cmd & 0x0F);
__delay_us(200);
__delay_us(200);
}



void lcd_init ()
{
lcd_reset(); // Call LCD reset
lcd_cmd(0x28); // 4-bit mode - 2 line - 5x7 font.
lcd_cmd(0x0C); // Display no cursor - no blink.
lcd_cmd(0x06); // Automatic Increment - No Display shift.
lcd_cmd(0x80); // Address DDRAM with 0 offset 80h.
}





void lcd_data (unsigned char dat)
{
PORTD = (unsigned)(((dat >> 4) & 0x0F) | E |RS);
PORTD = (unsigned)(((dat >> 4) & 0x0F) | RS);
PORTD = (unsigned)((dat & 0x0F)|E|RS);
PORTD = (unsigned)((dat & 0x0F)|RS);
__delay_us(200);
__delay_us(200);
}


void lcd_send_string(unsigned char *str, char length)
{
    while(length--) lcd_data(*str++);
}

void lcd_clear()
{
    lcd_cmd(0x01);
    __delay_us(1200);
}

void lcd_return_home()
{
    lcd_cmd(0x02);
}

char lcd_cursor_position(unsigned char position)
{
    char result = 1;
    if (position >= 0 && position <= 80) lcd_cmd(position + 0x80);
    else result = 0;
    return result;
}

void lcd_out(unsigned char row, unsigned char column, unsigned char *str, unsigned char length)
{
    char result = 1, position = 0;
    
    if(row >= 1 && row <= 4){
        if(column >= 1 && column <=20){
            if(row == 1) position = column;
            else if (row == 2) position = 40 + column;
            else if (row == 3) position = 20 + column;
            else if (row == 4) position = 60 + column;
            lcd_cmd(position + 0x80 - 1);                   // Set address
        }
    }
    lcd_send_string(str, length);
}

void lcd_entry_mode_set(char inc, char shift)
{
    if(inc) inc = 1;
    if(shift) shift = 1;
    lcd_cmd((0x04) | (inc << 1) | shift);
}

void main(void) {
    char i = 0;
    unsigned char text[] = "L";
    unsigned char text1[] = "L2 - Czesc Kuba!";
    unsigned char text2[] = "L3 - Czesc Kuba!";
    unsigned char text3[] = "L4 - Czesc Kuba!";
    Init();
    lcd_init();
    lcd_clear();
    lcd_out(2,10,text,1);

//    lcd_cursor_position(0x40);
//    lcd_send_string(text1,16);    
//    __delay_ms(1500);
//    lcd_clear();
//    lcd_cursor_position(0x14);
//    lcd_send_string(text2,16);    
//    __delay_ms(1500);
//    lcd_clear();
//    lcd_cursor_position(40);
//    lcd_send_string(text3,16);    
//    __delay_ms(1500);
    
   
    
    
//    lcd_entry_mode_set(0,0);
//    lcd_data(0x41); 
//    lcd_data(0x42);
//    lcd_data(0x43);
//    __delay_ms(1500);
//    lcd_clear();
    while(1);
    return;
}
