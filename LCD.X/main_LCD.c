/*
 * File:   main_LCD.c
 * Author: Microchip
 *
 * Created on 04 October 2017, 20:48
 */

#define _XTAL_FREQ 8000000UL

#include <xc.h>
#include "Fuses.h"
#include <string.h>
#include <stdlib.h>


#define RS  0x10
#define E   0x20
#define LCD_Port    PORTD



void Init(void){
    OSCCON = 0x71;
    ANSEL = 0x00;
    ANSELH = 0x00;
    PORTA = PORTB = PORTD = PORTD = PORTE = 0x00;
    TRISA = TRISB = TRISC = TRISD = TRISE = 0x00;
}



void lcd_reset()
{
LCD_Port = 0xFF;
__delay_ms(20);
LCD_Port = 0x03 + E;
LCD_Port = 0x03;
__delay_ms(10);
LCD_Port = 0x03 + E;
LCD_Port = 0x03;
__delay_ms(1);
LCD_Port = 0x03 + E;
LCD_Port = 0x03;
__delay_ms(1);
LCD_Port = 0x02 + E;
LCD_Port = 0x02;
__delay_ms(1);
}



void lcd_cmd (int cmd)
{
LCD_Port = (unsigned)((cmd >> 4) & 0x000F) | E;
LCD_Port = (unsigned)((cmd >> 4) & 0x000F);
LCD_Port = (unsigned)(cmd & 0x000F) | E;
LCD_Port = (unsigned)(cmd & 0x000F);
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



void lcd_data ( char dat)
{
LCD_Port = (unsigned)(((dat >> 4) & 0x0F) | E |RS);
LCD_Port = (unsigned)(((dat >> 4) & 0x0F) | RS);
LCD_Port = (unsigned)((dat & 0x0F)|E|RS);
LCD_Port = (unsigned)((dat & 0x0F)|RS);
__delay_us(200);
__delay_us(200);
}



void lcd_send_string1(char *str)
{
    char length = strlen(str);
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



int lcd_cursor_position(int position)
{
    int result = 1;
    if (position >= 0 && position < 80) lcd_cmd((unsigned char)(position + 0x80));
    else result = 0;
    return result;
}



void lcd_out(char row,  char column,  char *str)
{
    char result = 1, position = 0;
    
    if(row >= 1 && row <= 4){
        if(column >= 1 && column <=20){
            if(row == 1) position = column;
            else if (row == 2) position = (unsigned char) (0x40 + column);
            else if (row == 3) position = (unsigned char) (0x14 + column);
            else if (row == 4) position = (unsigned char) (0x54 + column);
            lcd_cmd((unsigned char)(position + 0x80 - 1));                   // Set address
        }
    }
    lcd_send_string1(str);
}



void lcd_entry_mode_set(char inc, char shift)
{
    if(inc) inc = 1;
    if(shift) shift = 1;
    lcd_cmd((0x04) | (inc << 1) | shift);
}



void main(void) {
    int i = 32767;
    const char text1[] = "L1 - Czesc Kuba!";
    const char text2[] = "L2 - Czesc Kuba!";
    const char text3[] = "L3 - Czesc Kuba!";
    const char text4[] = "L4 - Czesc Kuba!";
    const char text5[] = "11111111112222222222333333333344444444445555555555666666666677777777778888888888";
    char text[];
    Init();
    lcd_init();
    lcd_clear();
    __delay_ms(500);
    itoa(text, i, 10);
    lcd_out(1,1,text);        
  
    while(1);
    return;
}
