//###############################################################################
//#										#
//# MXE11 PDP11-Unix Emulator for Mikrocontrollers				#
//#										#
//# copyright (c) 2017 Joerg Wolfram (joerg@jcwolfram.de)			#
//#										#
//#										#
//# This program is free software; you can redistribute it and/or		#
//# modify it under the terms of the GNU General Public License			#
//# as published by the Free Software Foundation; either version 3		#
//# of the License, or (at your option) any later version.			#
//#										#
//# This program is distributed in the hope that it will be useful,		#
//# but WITHOUT ANY WARRANTY; without even the implied warranty of		#
//# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the GNU		#
//# General Public License for more details.					#
//#										#
//# You should have received a copy of the GNU General Public			#
//# License along with this library// if not, write to the			#
//# Free Software Foundation, Inc., 59 Temple Place - Suite 330,		#
//# Boston, MA 02111-1307, USA.							#
//#										#
//###############################################################################
#if MCU == 2

#include "board.h"
#include "cpu.h"
#include "xvars.h"
#include "ctable_06_10.h"
#include "SDL.h"
#include <unistd.h>
#include <termios.h>
#include <stdio.h>


extern unsigned short tks8,tkb8,tps8,tpb8,cycle_type;
volatile unsigned short rx_wptr8,rx_rptr8,rx_cap8;
volatile unsigned short tx_wptr8,tx_rptr8,tx_cap8;

extern unsigned short tks9,tkb9,tps9,tpb9,cycle_type;
volatile unsigned short rx_wptr9,rx_rptr9,rx_cap9;
volatile unsigned short tx_wptr9,tx_rptr9,tx_cap9;

void terminal_char(unsigned char);
SDL_Event event;
SDL_Surface *screen;

unsigned char esc_buffer[4];
unsigned short esc_pointer;

unsigned char term_screen[24][64];
unsigned char term_screen_temp[24][64];
int terminal_x,terminal_y;
int terminal_sx,terminal_sy;
int sx,sy;
int terminal_dirty;
unsigned char ucur;
unsigned char terminal_state;

extern unsigned short system_state;

struct termios oldt,newt;


int kmode;
int wrapmode;
int inversemode;
int cursormode;
int tcount;

void serve_console(void)
{
	unsigned char c;
	int i;

	//check if char available
	if (rx_cap8 > 0) 
	{
		c=rxbuffer8[rx_rptr8++];
		rx_rptr8 &= 0xff;
		rx_cap8-=1;

		tkb8=c;
		tks8 |= 0x80;

		if(tks8 & 0x40)
		{
			if(!(((rxint_queue & 0x000000FFul) == 0x00000001ul) ||
			     ((rxint_queue & 0x0000FF00ul) == 0x00000100ul) ||
			     ((rxint_queue & 0x00FF0000ul) == 0x00010000ul) ||
			     ((rxint_queue & 0xFF000000ul) == 0x01000000ul)))
			{
			 	cycle_type |= (2 << SHIFT_CYCLE);
			 	if ((rxint_queue & 0x000000FFul) == 0)
			 		rxint_queue |= 0x00000001ul;
			 		else if ((rxint_queue & 0x0000FF00ul) == 0)
				 		rxint_queue |= 0x00000100ul;
				 		else if ((rxint_queue & 0x00FF0000ul) == 0)
					 		rxint_queue |= 0x00010000ul;
			 				else rxint_queue |= 0x01000000ul;
			}
		}
	}


	if(((tps8 & 0x80) == 0) && (tx_cap8 > 0))
	{
//		printf("pchar: %02X\n",tpb8 & 0x7f);
		txbuffer8[tx_wptr8++]=tpb8 & 0x7f;
		tx_wptr8 &= 0xff;
		tx_cap8-=1;

		fflush(stdout);
		tps8 |= 0x80;

		if(tps8 & 0x40)
		{
			if(!(((txint_queue & 0x000000FFul) == 0x00000001ul) ||
			     ((txint_queue & 0x0000FF00ul) == 0x00000100ul) ||
			     ((txint_queue & 0x00FF0000ul) == 0x00010000ul) ||
			     ((txint_queue & 0xFF000000ul) == 0x01000000ul)))
			{
			 	cycle_type |= (1 << SHIFT_CYCLE);
			 	if ((txint_queue & 0x000000FFul) == 0)
			 		txint_queue |= 0x00000001ul;
			 		else if ((txint_queue & 0x0000FF00ul) == 0)
				 		txint_queue |= 0x00000100ul;
				 		else if ((txint_queue & 0x00FF0000ul) == 0)
					 		txint_queue |= 0x00010000ul;
			 				else txint_queue |= 0x01000000ul;
			}
		}


	}

	//check if char available
	if (rx_cap9 > 0) 
	{
		c=rxbuffer9[rx_rptr9++];
		rx_rptr9 &= 0xff;
		rx_cap9-=1;

		tkb9=c;
		tks9 |= 0x80;
		if(tks9 & 0x40)
		{
			if(!(((rxint_queue & 0x000000FFul) == 0x00000002ul) ||
			     ((rxint_queue & 0x0000FF00ul) == 0x00000200ul) ||
			     ((rxint_queue & 0x00FF0000ul) == 0x00020000ul) ||
			     ((rxint_queue & 0xFF000000ul) == 0x02000000ul)))
			{
			 	cycle_type |= (2 << SHIFT_CYCLE);
			 	if ((rxint_queue & 0x000000FFul) == 0)
			 		rxint_queue |= 0x00000002ul;
			 		else if ((rxint_queue & 0x0000FF00ul) == 0)
				 		rxint_queue |= 0x00000200ul;
				 		else if ((rxint_queue & 0x00FF0000ul) == 0)
					 		rxint_queue |= 0x00020000ul;
			 				else rxint_queue |= 0x02000000ul;
			}
		}

	}

	if(((tps9 & 0x80) == 0))
	{
		txbuffer9[tx_wptr9++]=tpb9 & 0x7f;
		tx_wptr9 &= 0xff;
		tx_cap9-=1;
		
		tps9 |= 0x80;
		if(tps9 & 0x40)
		{
			if(!(((txint_queue & 0x000000FFul) == 0x00000002ul) ||
			     ((txint_queue & 0x0000FF00ul) == 0x00000200ul) ||
			     ((txint_queue & 0x00FF0000ul) == 0x00020000ul) ||
			     ((txint_queue & 0xFF000000ul) == 0x02000000ul)))
			{
			 	cycle_type |= (1 << SHIFT_CYCLE);
			 	if ((txint_queue & 0x000000FFul) == 0)
			 		txint_queue |= 0x00000002ul;
			 		else if ((txint_queue & 0x0000FF00ul) == 0)
				 		txint_queue |= 0x00000200ul;
				 		else if ((txint_queue & 0x00FF0000ul) == 0)
					 		txint_queue |= 0x00020000ul;
			 				else txint_queue |= 0x02000000ul;
			}
		}
	}


	if(SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			system_state=0;
		}

		if (event.type == SDL_KEYUP)
		{
			if(event.key.keysym.sym == SDLK_LSHIFT) kmode &= 0xfe;
			if(event.key.keysym.sym == SDLK_LCTRL) kmode &= 0xfd;			
			if(event.key.keysym.sym == SDLK_LALT) kmode &= 0xfb;			
			if(event.key.keysym.sym == SDLK_RSHIFT) kmode &= 0xfe;
			if(event.key.keysym.sym == SDLK_RCTRL) kmode &= 0xfd;			
			if(event.key.keysym.sym == 0x0139) kmode &= 0xfb;			
		}

		if ((rx_cap8 < 253) && (event.type == SDL_KEYDOWN))
		{

			if(kmode == 0)
			{
//				printf("KEY EVENT\n");
				switch (event.key.keysym.sym)
				{
					case SDLK_LSHIFT:	kmode |= 1;break;
					case SDLK_LCTRL:	kmode |= 2;break;
					case SDLK_LALT:		kmode |= 4;break;
					case SDLK_RSHIFT:	kmode |= 1;break;
					case SDLK_RCTRL:	kmode |= 2;break;
					case 0x0139:		kmode |= 4;break;
					
					case SDLK_0: 	 	rxbuffer8[rx_wptr8++]='0';rx_cap8++; break;
					case SDLK_1:  		rxbuffer8[rx_wptr8++]='1';rx_cap8++; break;
					case SDLK_2:  		rxbuffer8[rx_wptr8++]='2';rx_cap8++; break;
					case SDLK_3: 	 	rxbuffer8[rx_wptr8++]='3';rx_cap8++; break;
					case SDLK_4:  		rxbuffer8[rx_wptr8++]='4';rx_cap8++; break;
					case SDLK_5:  		rxbuffer8[rx_wptr8++]='5';rx_cap8++; break;
					case SDLK_6: 	 	rxbuffer8[rx_wptr8++]='6';rx_cap8++; break;
					case SDLK_7:  		rxbuffer8[rx_wptr8++]='7';rx_cap8++; break;
					case SDLK_8:  		rxbuffer8[rx_wptr8++]='8';rx_cap8++; break;
					case SDLK_9: 	 	rxbuffer8[rx_wptr8++]='9';rx_cap8++; break;
					case SDLK_a:  		rxbuffer8[rx_wptr8++]='a';rx_cap8++; break;
					case SDLK_b:  		rxbuffer8[rx_wptr8++]='b';rx_cap8++; break;
					case SDLK_c:  		rxbuffer8[rx_wptr8++]='c';rx_cap8++; break;
					case SDLK_d:  		rxbuffer8[rx_wptr8++]='d';rx_cap8++; break;
					case SDLK_e:  		rxbuffer8[rx_wptr8++]='e';rx_cap8++; break;
					case SDLK_f:  		rxbuffer8[rx_wptr8++]='f';rx_cap8++; break;
					case SDLK_g:  		rxbuffer8[rx_wptr8++]='g';rx_cap8++; break;
					case SDLK_h:  		rxbuffer8[rx_wptr8++]='h';rx_cap8++; break;
					case SDLK_i:  		rxbuffer8[rx_wptr8++]='i';rx_cap8++; break;
					case SDLK_j:  		rxbuffer8[rx_wptr8++]='j';rx_cap8++; break;
					case SDLK_k:  		rxbuffer8[rx_wptr8++]='k';rx_cap8++; break;
					case SDLK_l:  		rxbuffer8[rx_wptr8++]='l';rx_cap8++; break;
					case SDLK_m:  		rxbuffer8[rx_wptr8++]='m';rx_cap8++; break;
					case SDLK_n:  		rxbuffer8[rx_wptr8++]='n';rx_cap8++; break;
					case SDLK_o:  		rxbuffer8[rx_wptr8++]='o';rx_cap8++; break;
					case SDLK_p:  		rxbuffer8[rx_wptr8++]='p';rx_cap8++; break;
					case SDLK_q:  		rxbuffer8[rx_wptr8++]='q';rx_cap8++; break;
					case SDLK_r:  		rxbuffer8[rx_wptr8++]='r';rx_cap8++; break;
					case SDLK_s:  		rxbuffer8[rx_wptr8++]='s';rx_cap8++; break;
					case SDLK_t:  		rxbuffer8[rx_wptr8++]='t';rx_cap8++; break;
					case SDLK_u:  		rxbuffer8[rx_wptr8++]='u';rx_cap8++; break;
					case SDLK_v:  		rxbuffer8[rx_wptr8++]='v';rx_cap8++; break;
					case SDLK_w:  		rxbuffer8[rx_wptr8++]='w';rx_cap8++; break;
					case SDLK_x:  		rxbuffer8[rx_wptr8++]='x';rx_cap8++; break;
					case SDLK_y:  		rxbuffer8[rx_wptr8++]='y';rx_cap8++; break;
					case SDLK_z:  		rxbuffer8[rx_wptr8++]='z';rx_cap8++; break;

					case SDLK_LESS:  	rxbuffer8[rx_wptr8++]='<';rx_cap8++; break;
					case SDLK_PLUS:  	rxbuffer8[rx_wptr8++]='+';rx_cap8++; break;
					case SDLK_MINUS:  	rxbuffer8[rx_wptr8++]='-';rx_cap8++; break;
					case SDLK_COMMA:  	rxbuffer8[rx_wptr8++]=',';rx_cap8++; break;
					case SDLK_PERIOD:  	rxbuffer8[rx_wptr8++]='.';rx_cap8++; break;
					case SDLK_HASH:  	rxbuffer8[rx_wptr8++]='#';rx_cap8++; break;
					case SDLK_CARET:  	rxbuffer8[rx_wptr8++]='^';rx_cap8++; break;
					case 0xDF:	  	rxbuffer8[rx_wptr8++]='\\';rx_cap8++;break;

					case SDLK_SPACE:  	rxbuffer8[rx_wptr8++]=' ';rx_cap8++; break;
					case SDLK_BACKSPACE:  	rxbuffer8[rx_wptr8++]=0x08;rx_cap8++;break;
					case SDLK_TAB:  	rxbuffer8[rx_wptr8++]=0x09;rx_cap8++;break;
					case SDLK_RETURN:  	rxbuffer8[rx_wptr8++]=0x0A;rx_cap8++;break;
					case SDLK_ESCAPE:  	rxbuffer8[rx_wptr8++]=0x1B;rx_cap8++;break;
					case SDLK_DELETE:  	rxbuffer8[rx_wptr8++]=0x7F;rx_cap8++;break;

					case SDLK_UP:  		rxbuffer8[rx_wptr8++]=0x1B;rx_cap8++;
								rxbuffer8[rx_wptr8++]='A';rx_cap8++;
								break;

					case SDLK_DOWN:  	rxbuffer8[rx_wptr8++]=0x1B;rx_cap8++;
								rxbuffer8[rx_wptr8++]='B';rx_cap8++;
								break;


					case SDLK_LEFT:  	rxbuffer8[rx_wptr8++]=0x1B;rx_cap8++;
								rxbuffer8[rx_wptr8++]='C';rx_cap8++;
								break;
								
					case SDLK_RIGHT:  	rxbuffer8[rx_wptr8++]=0x1B;rx_cap8++;
								rxbuffer8[rx_wptr8++]='D';rx_cap8++;
								break;

					case SDLK_F1:  		rxbuffer8[rx_wptr8++]=0x1B;rx_cap8++;
								rxbuffer8[rx_wptr8++]='O';rx_cap8++;
								rxbuffer8[rx_wptr8++]='P';rx_cap8++;
								break;


					case SDLK_F2:  		rxbuffer8[rx_wptr8++]=0x1B;rx_cap8++;
								rxbuffer8[rx_wptr8++]='O';rx_cap8++;
								rxbuffer8[rx_wptr8++]='Q';rx_cap8++;
								break;



					case SDLK_F3:  		rxbuffer8[rx_wptr8++]=0x1B;rx_cap8++;
								rxbuffer8[rx_wptr8++]='O';rx_cap8++;
								rxbuffer8[rx_wptr8++]='R';rx_cap8++;
								break;


					case SDLK_F4:  		rxbuffer8[rx_wptr8++]=0x1B;rx_cap8++;
								rxbuffer8[rx_wptr8++]='O';rx_cap8++;
								rxbuffer8[rx_wptr8++]='S';rx_cap8++;
								break;
								

/*
					case SDLK_HOME:  	rxbuffer8[rx_wptr8++]=0xE4;rx_cap8++;break;
					case SDLK_END:  	rxbuffer8[rx_wptr8++]=0xE5;rx_cap8++;break;
					case SDLK_INSERT:  	rxbuffer8[rx_wptr8++]=0xE6;rx_cap8++;break;
					case SDLK_DELETE:  	rxbuffer8[rx_wptr8++]=0xE7;rx_cap8++;break;
					case SDLK_PAGEUP:  	rxbuffer8[rx_wptr8++]=0xF0;rx_cap8++;break;
					case SDLK_PAGEDOWN:  	rxbuffer8[rx_wptr8++]=0xF1;rx_cap8++;break;
*/
					default:		printf("Unknown key: %04X\n",event.key.keysym.sym);
				}
			}
			if(kmode == 1)
			{
//				printf("SHIFTED KEY EVENT\n");
				switch (event.key.keysym.sym)
				{
					case SDLK_LSHIFT:	kmode |= 1;break;
					case SDLK_LCTRL:	kmode |= 2;break;
					case SDLK_LALT:		kmode |= 4;break;
					case SDLK_RSHIFT:	kmode |= 1;break;
					case SDLK_RCTRL:	kmode |= 2;break;
					case 0x0139:		kmode |= 4;break;
					
					case SDLK_0: 	 	rxbuffer8[rx_wptr8++]='=';rx_cap8++; break;
					case SDLK_1:  		rxbuffer8[rx_wptr8++]='!';rx_cap8++; break;
					case SDLK_2:  		rxbuffer8[rx_wptr8++]='"';rx_cap8++; break;
					case SDLK_3: 	 	rxbuffer8[rx_wptr8++]='@';rx_cap8++; break;
					case SDLK_4:  		rxbuffer8[rx_wptr8++]='$';rx_cap8++; break;
					case SDLK_5:  		rxbuffer8[rx_wptr8++]='%';rx_cap8++; break;
					case SDLK_6: 	 	rxbuffer8[rx_wptr8++]='&';rx_cap8++; break;
					case SDLK_7:  		rxbuffer8[rx_wptr8++]='/';rx_cap8++; break;
					case SDLK_8:  		rxbuffer8[rx_wptr8++]='(';rx_cap8++; break;
					case SDLK_9: 	 	rxbuffer8[rx_wptr8++]=')';rx_cap8++; break;
					case SDLK_a:  		rxbuffer8[rx_wptr8++]='A';rx_cap8++; break;
					case SDLK_b:  		rxbuffer8[rx_wptr8++]='B';rx_cap8++; break;
					case SDLK_c:  		rxbuffer8[rx_wptr8++]='C';rx_cap8++; break;
					case SDLK_d:  		rxbuffer8[rx_wptr8++]='D';rx_cap8++; break;
					case SDLK_e:  		rxbuffer8[rx_wptr8++]='E';rx_cap8++; break;
					case SDLK_f:  		rxbuffer8[rx_wptr8++]='F';rx_cap8++; break;
					case SDLK_g:  		rxbuffer8[rx_wptr8++]='G';rx_cap8++; break;
					case SDLK_h:  		rxbuffer8[rx_wptr8++]='H';rx_cap8++; break;
					case SDLK_i:  		rxbuffer8[rx_wptr8++]='I';rx_cap8++; break;
					case SDLK_j:  		rxbuffer8[rx_wptr8++]='J';rx_cap8++; break;
					case SDLK_k:  		rxbuffer8[rx_wptr8++]='K';rx_cap8++; break;
					case SDLK_l:  		rxbuffer8[rx_wptr8++]='L';rx_cap8++; break;
					case SDLK_m:  		rxbuffer8[rx_wptr8++]='M';rx_cap8++; break;
					case SDLK_n:  		rxbuffer8[rx_wptr8++]='N';rx_cap8++; break;
					case SDLK_o:  		rxbuffer8[rx_wptr8++]='O';rx_cap8++; break;
					case SDLK_p:  		rxbuffer8[rx_wptr8++]='P';rx_cap8++; break;
					case SDLK_q:  		rxbuffer8[rx_wptr8++]='Q';rx_cap8++; break;
					case SDLK_r:  		rxbuffer8[rx_wptr8++]='R';rx_cap8++; break;
					case SDLK_s:  		rxbuffer8[rx_wptr8++]='S';rx_cap8++; break;
					case SDLK_t:  		rxbuffer8[rx_wptr8++]='T';rx_cap8++; break;
					case SDLK_u:  		rxbuffer8[rx_wptr8++]='U';rx_cap8++; break;
					case SDLK_v:  		rxbuffer8[rx_wptr8++]='V';rx_cap8++; break;
					case SDLK_w:  		rxbuffer8[rx_wptr8++]='W';rx_cap8++; break;
					case SDLK_x:  		rxbuffer8[rx_wptr8++]='X';rx_cap8++; break;
					case SDLK_y:  		rxbuffer8[rx_wptr8++]='Y';rx_cap8++; break;
					case SDLK_z:  		rxbuffer8[rx_wptr8++]='Z';rx_cap8++; break;

					case SDLK_LESS:  	rxbuffer8[rx_wptr8++]='>';rx_cap8++; break;
					case SDLK_PLUS:  	rxbuffer8[rx_wptr8++]='*';rx_cap8++; break;
					case SDLK_MINUS:  	rxbuffer8[rx_wptr8++]='_';rx_cap8++; break;
					case SDLK_COMMA:  	rxbuffer8[rx_wptr8++]=';';rx_cap8++; break;
					case SDLK_PERIOD:  	rxbuffer8[rx_wptr8++]=':';rx_cap8++; break;
					case SDLK_HASH:  	rxbuffer8[rx_wptr8++]='\'';rx_cap8++; break;
					case 0xDF:	  	rxbuffer8[rx_wptr8++]='?';rx_cap8++; break;
					case SDLK_RETURN:  	rxbuffer8[rx_wptr8++]=0x0D;rx_cap8++;break;
					
					default:		printf("Unknown shifted key: %04X\n",event.key.keysym.sym);
				}
	
			}
			
			if(kmode == 4)
			{
//				printf("ALT KEY EVENT\n");
				switch (event.key.keysym.sym)
				{
					case SDLK_LSHIFT:	kmode |= 1;break;
					case SDLK_LCTRL:	kmode |= 2;break;
					case SDLK_LALT:		kmode |= 4;break;
					case SDLK_RSHIFT:	kmode |= 1;break;
					case SDLK_RCTRL:	kmode |= 2;break;
					case 0x0139:		kmode |= 4;break;
					
					case SDLK_q: 	 	rxbuffer8[rx_wptr8++]='@';rx_cap8++; break;
					case SDLK_LESS: 	 rxbuffer8[rx_wptr8++]='|';rx_cap8++; break;
					case SDLK_PLUS: 	 rxbuffer8[rx_wptr8++]='~';rx_cap8++; break;

					case SDLK_7:  		rxbuffer8[rx_wptr8++]='{';rx_cap8++; break;
					case SDLK_8:  		rxbuffer8[rx_wptr8++]='[';rx_cap8++; break;
					case SDLK_9: 	 	rxbuffer8[rx_wptr8++]=']';rx_cap8++; break;
					case SDLK_0:  		rxbuffer8[rx_wptr8++]='}';rx_cap8++; break;

					default:		printf("Unknown alt key: %04X\n",event.key.keysym.sym);
				}
			}

			if(kmode == 2)
			{
//				printf("CTRL KEY EVENT\n");
				switch (event.key.keysym.sym)
				{
					case SDLK_LSHIFT:	kmode |= 1;break;
					case SDLK_LCTRL:	kmode |= 2;break;
					case SDLK_LALT:		kmode |= 4;break;
					case SDLK_RSHIFT:	kmode |= 1;break;
					case SDLK_RCTRL:	kmode |= 2;break;
					case 0x0139:		kmode |= 4;break;


					case SDLK_SPACE:  	rxbuffer8[rx_wptr8++]=0x00;rx_cap8++; break;
					case SDLK_a:  		rxbuffer8[rx_wptr8++]=0x01;rx_cap8++; break;
					case SDLK_b:  		rxbuffer8[rx_wptr8++]=0x02;rx_cap8++; break;
					case SDLK_c:  		rxbuffer8[rx_wptr8++]=0x03;rx_cap8++; break;
					case SDLK_d:  		rxbuffer8[rx_wptr8++]=0x04;rx_cap8++; break;
					case SDLK_e:  		rxbuffer8[rx_wptr8++]=0x05;rx_cap8++; break;
					case SDLK_f:  		rxbuffer8[rx_wptr8++]=0x06;rx_cap8++; break;
					case SDLK_g:  		rxbuffer8[rx_wptr8++]=0x07;rx_cap8++; break;
					case SDLK_h:  		rxbuffer8[rx_wptr8++]=0x08;rx_cap8++; break;
					case SDLK_i:  		rxbuffer8[rx_wptr8++]=0x09;rx_cap8++; break;
					case SDLK_j:  		rxbuffer8[rx_wptr8++]=0x0A;rx_cap8++; break;
					case SDLK_k:  		rxbuffer8[rx_wptr8++]=0x0B;rx_cap8++; break;
					case SDLK_l:  		rxbuffer8[rx_wptr8++]=0x0C;rx_cap8++; break;
					case SDLK_m:  		rxbuffer8[rx_wptr8++]=0x0D;rx_cap8++; break;
					case SDLK_n:  		rxbuffer8[rx_wptr8++]=0x0E;rx_cap8++; break;
					case SDLK_o:  		rxbuffer8[rx_wptr8++]=0x0F;rx_cap8++; break;
					case SDLK_p:  		rxbuffer8[rx_wptr8++]=0x10;rx_cap8++; break;
					case SDLK_q:  		rxbuffer8[rx_wptr8++]=0x11;rx_cap8++; break;
					case SDLK_r:  		rxbuffer8[rx_wptr8++]=0x12;rx_cap8++; break;
					case SDLK_s:  		rxbuffer8[rx_wptr8++]=0x13;rx_cap8++; break;
					case SDLK_t:  		rxbuffer8[rx_wptr8++]=0x14;rx_cap8++; break;
					case SDLK_u:  		rxbuffer8[rx_wptr8++]=0x15;rx_cap8++; break;
					case SDLK_v:  		rxbuffer8[rx_wptr8++]=0x16;rx_cap8++; break;
					case SDLK_w:  		rxbuffer8[rx_wptr8++]=0x17;rx_cap8++; break;
					case SDLK_x:  		rxbuffer8[rx_wptr8++]=0x18;rx_cap8++; break;
					case SDLK_y:  		rxbuffer8[rx_wptr8++]=0x19;rx_cap8++; break;
					case SDLK_z:  		rxbuffer8[rx_wptr8++]=0x1A;rx_cap8++; break;
					
					default:		printf("Unknown ctrl key: %04X\n",event.key.keysym.sym);
				}
			}



			rx_wptr8 &= 0xff;
		}
		
	}	
	
	if(tx_cap8 < 255)
	{	
//		printf("kchar = %c\n",txbuffer8[tx_rptr8] & 0x7f);
		terminal_char(txbuffer8[tx_rptr8++] & 0x7f);
		tx_rptr8 &= 0xff;
		tx_cap8++;
	}


	i=read(0,&c,1);
	if ((rx_cap9 < 253) && (i==1))
	{
		rxbuffer9[rx_wptr9++]=c;
		rx_cap9++;
		rx_wptr9 &= 0xff;
	}

	if(tx_cap9 < 255)
	{	
		printf("%c",txbuffer9[tx_rptr9++] & 0x7f);
		tx_rptr9 &= 0xff;
		tx_cap9++;
		fflush(stdout);
	}
	
	if(++tcount == 100)
	{
		tcount = 0;
		if(terminal_dirty > 0)
		{
			SDL_Flip(screen);
			terminal_dirty=0;
		}
	
	}

}


void setpixel(SDL_Surface *screen, int x, int y, unsigned char red, unsigned char green, unsigned char blue)
{
	unsigned char *pixel_memory;

	pixel_memory = (unsigned char *) screen->pixels + 1280 * y + x * 2;
	*pixel_memory++ = (SDL_MapRGB(screen->format, red, green, blue)) & 0xff;
	*pixel_memory = (SDL_MapRGB(screen->format, red, green, blue)) >> 8;
}


void terminal_redraw(void)
{
	int x,y,l,bm,pix,sx,sy,mask;
	unsigned char c,ct;

	for(y=0;y<24;y++)					//row
	{
		for(x=0;x<53;x++)				//volumn
		{
			c=term_screen[y][x];			//get char
			ct=term_screen_temp[y][x];		//get char
			if(c != ct)
			{
				term_screen_temp[y][x]=term_screen[y][x];
				terminal_dirty=1;
				for(l=0;l<10;l++)			//pixline
				{
					sy=20*y+2*l;			//y-pos of pixline
					bm=sysfont[l+10*c];
					mask=0x80;			//bitmask
					for(pix=0;pix<6;pix++)
					{
						sx=12*x+2*pix;
						if((bm & mask) != 0)
						{
							setpixel(screen,sx+0,sy+0,0,255,0);
							setpixel(screen,sx+1,sy+0,0,255,0);
							setpixel(screen,sx+0,sy+1,0,255,0);
							setpixel(screen,sx+1,sy+1,0,255,0);
						}
						else
						{		
							setpixel(screen,sx+0,sy+0,0,0,0);
							setpixel(screen,sx+1,sy+0,0,0,0);
							setpixel(screen,sx+0,sy+1,0,0,0);
							setpixel(screen,sx+1,sy+1,0,0,0);
						}
						mask >>= 1;
					}
				
				}
			}
		}
	}
//	SDL_Flip(screen);
}

void terminal_clear(void)
{
	int x,y;

	for(y=0;y<24;y++)
	{
		for(x=0;x<53;x++)
		{
			term_screen[y][x]=0x20;	//space
			term_screen_temp[y][x]='#';
		}
	}		
	terminal_x=0;
	terminal_y=0;
	terminal_sx=0;
	terminal_sy=0;
	esc_pointer=0;
	terminal_redraw();
}


void terminal_char(unsigned char c)
{

	if(cursormode) term_screen[terminal_y][terminal_x] ^=0x80;

	if(esc_pointer == 3)
	{
		terminal_x=c-32;
		terminal_y=sy;
		if(terminal_x > 52) terminal_x=52;
		if(terminal_y > 23) terminal_y=23;
		esc_pointer=8;
	}

	
	if(esc_pointer == 2)
	{
		sy=c-32;
		esc_pointer=3;
	}

		
	if(esc_pointer == 1)
	{
		switch(c)
		{
			//A = up
			case 'A':	if(terminal_y > 0) terminal_y--;
					esc_pointer=8;
					break;
			
			//B = down
			case 'B':	if(terminal_y < 23) terminal_y++;
					esc_pointer=8;
					break;

			//C = right
			case 'C':	if(terminal_x < 52) terminal_x++;
					esc_pointer=8;
					break;

			//D = left
			case 'D':	if(terminal_x > 0) terminal_x--;
					esc_pointer=8;
					break;

			//E = clear terminal
			case 'E':	terminal_clear(); break;


			//H = home
			case 'H':	terminal_x=0;
					terminal_y=0;
					esc_pointer=8;
					break;


			//I = reverse line feed
			case 'I':	if(terminal_y > 0)
					{
						terminal_y--;
						for(sy=0;sy<terminal_y;sy++)
						{
							for(sx=0;sx<53;sx++)
							{
								term_screen[sy][sx]=term_screen[sy+1][sx];
							}
						}
						for(sx=0;sx<53;sx++) term_screen[terminal_y][sx]=0x20;
					}
					else
					{
						for(sy=23;sy>terminal_y;sy--)
						{
							for(sx=0;sx<53;sx++)
							{
								term_screen[sy][sx]=term_screen[sy-1][sx];
							}
						}
						for(sx=0;sx<53;sx++) term_screen[terminal_y][sx]=0x20;
					}
					terminal_x=0;
					esc_pointer=8;
					break;


			//J = clear screen from cursor
			case 'J':	sx=terminal_x;sy=terminal_y;
			
					while((sy < 24) && (sx < 53))
					{
						term_screen[sy][sx++]=0x20;	
						if(sx == 53)
						{
							sx = 0;
							sy++;
						}
					}
					esc_pointer=8;
					break;
			
					

			//K = clear line from cursor
			case 'K':	sx=terminal_x;sy=terminal_y;
			
					while((sy < 24) && (sx < 53))
					{
						term_screen[sy][sx++]=0x20;	
					}
					esc_pointer=8;
					break;


			//L = insert line
			case 'L':	if(terminal_y > 0)
					{
						for(sy=0;sy<terminal_y;sy++)
						{
							for(sx=0;sx<53;sx++)
							{
								term_screen[sy][sx]=term_screen[sy+1][sx];
							}
						}
					}
					for(sx=0;sx<53;sx++) term_screen[terminal_y][sx]=0x20;
					esc_pointer=8;
					break;

			//M = delete line
			case 'M':	if(terminal_y < 23)
					{
						for(sy=terminal_y;sy<23;sy++)
						{
							for(sx=0;sx<53;sx++)
							{
								term_screen[sy][sx]=term_screen[sy+1][sx];
							}
						}
					}
					else
					{
						for(sx=0;sx<53;sx++)
						{
							term_screen[terminal_y][sx]=0x20;
						}
					}
					esc_pointer=8;
					break;

			//Y = set position
			case 'Y':	esc_pointer=2;
					break;

			//e = enable cursor
			case 'e':	cursormode=1;
					esc_pointer=8;
					break;


			//f = disable cursor
			case 'f':	cursormode=0;
					esc_pointer=8;
					break;

			//j = save cursor	
			case 'j':	terminal_sx=terminal_x;terminal_sy=terminal_y;break;
					break;

			//k = restore cursor	
			case 'k':	terminal_x=terminal_sx;terminal_y=terminal_sy;break;
					break;

			//p = inverse video
			case 'p':	inversemode=1;
					esc_pointer=8;
					break;

			//q = normal video
			case 'q':	inversemode=0;
					esc_pointer=8;
					break;


			//w = dsiable line wrap
			case 'w':	wrapmode=0;
					esc_pointer=8;
					break;

			//q = normal video
			case 'v':	wrapmode=1;
					esc_pointer=8;
					break;

					
			default:	esc_pointer = 0;
		}
	}

	if(esc_pointer == 0)
	{
		switch(c)
		{
			case 0x00:
			case 0x01:
			case 0x02:
			case 0x03:
			case 0x04:
			case 0x05:
			case 0x06:
			case 0x07:	sx=0;break;
		
			//BACKSPACE
			case 0x08:	term_screen[terminal_y][--terminal_x]=0x20;break;	
	
			//TAB
			case 0x09:	do
					{
						term_screen[terminal_y][terminal_x++]=0x20;
					}
					while((terminal_x % 4) && (terminal_x<52));break;	

			//NEWLINE
			case 0x0A:	terminal_x=0;terminal_y++;break;			

			case 0x0B:	sx=0;break;
			//FORM FEED
			case 0x0C:	terminal_clear();break;
			//CARRIAGE RETURN
			case 0x0D:	terminal_x=0;break;
			
			case 0x0E:
			case 0x0F:

			case 0x10:	//these chars are invisible (reserved)
			case 0x11:
			case 0x12:
			case 0x13:
			case 0x14:
			case 0x15:
			case 0x16:
			case 0x17:
			case 0x18:
			case 0x19:
			case 0x1A:	sx=0;break;
			case 0x1B:	esc_pointer++;
//					printf("ESC\n"); 
					break;
			case 0x1C:
			case 0x1D:
			case 0x1E:
			case 0x1F:	sx=0;break;


			default:	term_screen[terminal_y][terminal_x]=(c & 0x7f)+128*inversemode;	//set char
					terminal_x++;

		}
	}		

	if(esc_pointer == 8) esc_pointer=0;

	//x is out of screen
	if(terminal_x > 52)
	{
		if(wrapmode == 1)
		{
			terminal_y++;
			terminal_x=0;
		}
		else	terminal_x=52;
	}
					
	if(terminal_x < 0)
	{
		terminal_y--;
		terminal_x=52;
	}

	//y is out of screen
	if(terminal_y < 0)
	{
		terminal_y=0;
		terminal_x=0;
	}

	if(terminal_y > 23)
	{
		for(sy=0;sy<23;sy++)
		{
			for(sx=0;sx<53;sx++)
			{
				term_screen[sy][sx]=term_screen[sy+1][sx];
			}
		}
		for(sx=0;sx<53;sx++)
		{
			term_screen[23][sx]=0x20;
		}
		terminal_y=23;
		terminal_sy--;
	}
		
	if(cursormode) term_screen[terminal_y][terminal_x] ^=0x80;
	terminal_redraw();
}


//###############################################################################
// init + exit console
//###############################################################################
void console_init()
{
	rx_wptr8=0;
	rx_rptr8=0;
	tx_wptr8=0;
	tx_rptr8=0;
	rx_cap8=0;
	tx_cap8=255;

	rx_wptr9=0;
	rx_rptr9=0;
	tx_wptr9=0;
	tx_rptr9=0;
	rx_cap9=0;
	tx_cap9=255;

	tcgetattr(STDIN_FILENO,&oldt);
	
	newt=oldt;
	
	newt.c_lflag &= ~(ICANON);
	newt.c_lflag &= ~(ECHO);
	
	tcsetattr(STDIN_FILENO,TCSANOW,&newt);	


	kmode=0;
	wrapmode=1;
	inversemode=0;
	cursormode=1;
	terminal_state=0;	//wait for first char

	terminal_clear();	
	term_screen[terminal_y][terminal_x]=0x10;		//set cursor
	terminal_redraw();
	SDL_EnableKeyRepeat(500,150);
	KPRINTF(INTRO); 
}			 

void console_exit()
{
	tcsetattr(STDIN_FILENO,TCSANOW,&oldt);	
	SDL_Quit();
}



#endif

	
