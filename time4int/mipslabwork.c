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
    if (IFS(0) & 0x100) {
        IFSCLR(0) = 0x100;
        timeoutcounter++;
        if(timeoutcounter == 10){ //10 * 100ms = 1sec
            time2string( textstring, mytime );
            display_string( 3, textstring );
            display_update();
            tick( &mytime );
            timeoutcounter = 0;
        }
    }
    
    //SW2
    if (IFS(0) & 0x8000) {
        PORTE++;            //Increase Port E
        IFSCLR(0) = 0x8000; //Reset Flag
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
    T2CONSET = 0x8000; //Starts clock
    
    IEC(0) = IEC(0) | 0x100;
    IPC(2) = IPC(2) | 0x1F;
    
    IEC(0) = IEC(0) | 0x8000;       //Enable S for interrupts
    IPC(3) = IPC(3) | 0x1c000000;   //
    
    
    enable_interrupt();
    
    return;
}

/* This function is called repetitively from the main program */
void labwork( void )
{
    prime = nextprime( prime );
    display_string( 0, itoaconv( prime ));
    display_update();
}
