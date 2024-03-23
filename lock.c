/*******************************************************
This program was created by the
CodeWizardAVR V3.12 Advanced
Automatic Program Generator
© Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : 
Version : 
Date    : 12/16/2022
Author  : 
Company : 
Comments: 


Chip type               : ATmega32A
Program type            : Application
AVR Core Clock frequency: 8.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 512
*******************************************************/

#include <mega32a.h>
#include <string.h>
#include <delay.h>
// Alphanumeric LCD functions
#include <alcd.h>

#define DELETE  10
#define ENTER   11
#define LOCK    PORTC.0


char getkey();

char sys_code[]="112256";
char user_code[sizeof(sys_code)]="";
char user_code_idx=0;
int x;


void main(void)
{

char k ;

DDRC.0=1;
DDRD = 0xF0;

lcd_init(16) ;


while (1)
    {
    // Please write your code here
        LOCK = 0;
        lcd_clear();
        lcd_gotoxy(0,0) ;
        lcd_putsf("lock:off");
        lcd_gotoxy(0,1);
        lcd_putsf("waiting for pass: ");
        
        
 GET_KEY_1:
        
    do
      {  
       k=getkey();
      }
      while ( k==0xFF );  
      delay_ms(100)  ; 
      
      while(getkey() != 0xFF);

    if(k == DELETE)
     {
      strcpyf(user_code,"")  ;
      user_code_idx = 0 ;  
      }
      else if(k == ENTER)
       {
        user_code[user_code_idx] = '\0' ; 
        if(strcmp(user_code, sys_code)==0)
         {
          LOCK = 1;
          lcd_clear();
          lcd_gotoxy(2,0);
          lcd_putsf("lock: ") ;
          lcd_gotoxy(0,1);
          lcd_putsf(" ON ") ;
          while(getkey() != DELETE);
          }
        else
          {
          lcd_clear();
          lcd_putsf("invalid password");
          delay_ms(200);
          }   
       strcpyf(user_code, "");
       user_code_idx=0; 
       }  
       
       
       else
        {       

         if(user_code_idx < sizeof(sys_code) - 1 )
          { 
          user_code[user_code_idx] = k + 0x30 ; 
          x=user_code_idx + 9;
          user_code_idx++;
           

            lcd_gotoxy(0,0);
            lcd_putsf("password:");
            lcd_gotoxy(x,0); 
            lcd_putchar('*');
           
          }
          goto GET_KEY_1;
           }
        }   
     }
                 

char getkey()
{
unsigned char key_code = 0xFF;
unsigned char columns;

PORTD.4 = 0;
columns = PIND & 0x07;
if(columns != 0x07)
  {
  switch(columns)
    {
    case 0b110 : key_code = 1; break;
    case 0b101 : key_code = 2; break;
    case 0b011 : key_code = 3; break;
    }
  }  
PORTD.4 = 1;

PORTD.5 = 0;
columns = PIND & 0x07;
if(columns != 0x07)
  {
  switch(columns)
    {
    case 0b110 : key_code = 4; break;
    case 0b101 : key_code = 5; break;
    case 0b011 : key_code = 6; break;
    }
  }  
PORTD.5 = 1;

PORTD.6 = 0;
columns = PIND & 0x07;
if(columns != 0x07)
  {
  switch(columns)
    {
    case 0b110 : key_code = 7; break;
    case 0b101 : key_code = 8; break;
    case 0b011 : key_code = 9; break;
    }
  }  
PORTD.6 = 1;

PORTD.7 = 0;
columns = PIND & 0x07;
if(columns != 0x07)
  {
  switch(columns)
    {
    case 0b110 : key_code = DELETE; break;
    case 0b101 : key_code = 0; break;
    case 0b011 : key_code = ENTER; break;
    }
  }  
PORTD.7 = 1;

PORTD = 0xFF; 
return key_code;
}