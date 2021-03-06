/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall

   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):

   This file modified 2017-04-31 by Ture Teknolog 

   For copyright and licensing, see file COPYING */
#include <stdio.h>
#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */
int prime = 1234567;
int mytime = 0x5957;
static int timeoutcounter = 0;

volatile int *led = (volatile int*) 0xbf886100;
volatile int *port = (volatile int*) 0xbf886110;
int c = 0;


char textstring[] = "text, more text, and even more text!";

/* Interrupt Service Routine */
void user_isr( void )
{
    if (IFS(0) == 0x100) {
        timeoutcounter++;
        if(timeoutcounter == 10){ //10 * 100ms = 1sec
            time2string( textstring, mytime );
            display_string( 3, textstring );
            display_update();
            tick( &mytime );
            //display_image(96, icon); doge
            timeoutcounter = 0;
        }
        IFSCLR(0) = 0x100;
    }
}

/* Lab-specific initialization goes here */
void labinit( void )
{
    //initialize led to zero
    *led &= 0xffffff00;
    
    //initialize port to zero
    *port &= 0xffffff00;
    
    //11->5 = 1
    TRISD &= 0xfe0;
    
    //TimerIntz
    T2CON = 0x0;    //Stops Timer2 and clear control register
    TMR2 = 0x0;     //Clear contents of TMR2
    PR2 = 0x7a12;   //Load PR2 register
    T2CONSET = 0x70;//
    
    IFSCLR(0);      //Clear the interuption flag
    
    IEC(0) = IEC(0) | 0x100;
    IPC(2) = IPC(2) | 0x1F;
    
    enable_interrupt()	;
    
    return;
}

/* This function is called repetitively from the main program */
void mainGame( void )
{
    display_clear();
    if(DIFFICULTY == 1)
        display_string(1, "DIFF = 1");
    if(DIFFICULTY == 2)
        display_string(1, "DIFF = 2");
    display_update();
}
