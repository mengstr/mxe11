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
#include <board.h>

#if MCU < 9
/*

extern unsigned char islower(unsigned char);
extern unsigned char isspace(unsigned char);
extern unsigned char isdigit(unsigned char);
extern unsigned char isupper(unsigned char);
*/

typedef union
{
	unsigned char	byte[4];
	int		i;
	unsigned int	ui;
	const char	*ptr;
	long		l;
	unsigned long	ul;
	float		f;
} value_t;

extern void unilib_outchar(unsigned char c);

/*--------------------------------------------------------------------------*/

static void output_digit_long(unsigned char n)
{
	if(n>9) unilib_outchar(n+0x37);
	else unilib_outchar(n+0x30);
}

/*--------------------------------------------------------------------------*/

static void output_nk(int FracPart,int nk)
{
	char ch;

	if(nk > 0)
	{
		unilib_outchar('.');
		if(nk > 1000)
		{
			ch='0';
			while(FracPart > 999)
			{
				ch++;FracPart-=1000;
			}
			unilib_outchar(ch);
		}
		if(nk > 100)
		{
			ch='0';
			while(FracPart > 99)
			{
				ch++;FracPart-=100;
			}
			unilib_outchar(ch);
		}
		if(nk > 10)
		{
			ch='0';
			while(FracPart > 9)
			{
				ch++;FracPart-=10;
			}
			unilib_outchar(ch);
		}
		unilib_outchar(FracPart+0x30);
	}
}

/*--------------------------------------------------------------------------*/

static void output_decimal_part (unsigned int value,unsigned char mode)
{
	unsigned char nonzero=0;
	unsigned char ch;

	ch='0';
	while(value > 99)
	{
		ch++;
		value-=100;
	}
	if((ch == '0') && (nonzero == 0))
	{
		if(mode & 0x01)	unilib_outchar('0');	//leading zeroes
		if(mode & 0x02)	unilib_outchar(' ');	//leading spaces
	}
	else
	{
		nonzero=1;
		unilib_outchar(ch);
	}

	ch='0';
	while(value > 9)
	{
		ch++;
		value-=10;
	}
	if((ch == '0') && (nonzero == 0))
	{
		if(mode & 0x01)	unilib_outchar('0');	//leading zeroes
		if(mode & 0x02)	unilib_outchar(' ');	//leading spaces
	}
	else
	{
		nonzero=1;
			unilib_outchar(ch);
	}
	unilib_outchar(value+0x30);
}

/*--------------------------------------------------------------------------*/

static void output_decimal_exponent (int value,int mode)
{
	char ch;

	if(!(mode & 0x08))
	{
		unilib_outchar(' ');
		unilib_outchar('e');
		if(value < 0) 
		{
			unilib_outchar('-');
			value=-value;
		}
		else unilib_outchar('+');

		ch='0';
		while(value > 9)
		{
			ch++;
			value-=10;
		}
		unilib_outchar(ch);
		unilib_outchar(value+0x30);
	}
}

/*--------------------------------------------------------------------------*/

static void output_decimal_long (unsigned long value,unsigned char mode,unsigned char vk)
{
	unsigned char nonzero=0;
	char ch;

	if(mode & 0x80)	//long
	{
		ch='0';
		while(value > 999999999)
		{
			ch++;
			value-=1000000000;
		}
		if(vk > 9)
		{
			if(ch == '0')
			{
				if(mode & 0x01)	unilib_outchar('0');	//leading zeroes
				if(mode & 0x02)	unilib_outchar(' ');	//leading spaces
			}
			else
			{
				nonzero=1;
				unilib_outchar(ch);
			}
		}

		ch='0';
		while(value > 99999999)
		{
			ch++;
			value-=100000000;
		}
		if(vk > 8)
		{
			if((ch == '0') && (nonzero == 0))
			{
				if(mode & 0x01)	unilib_outchar('0');	//leading zeroes
				if(mode & 0x02)	unilib_outchar(' ');	//leading spaces
			}
			else
			{
				nonzero=1;
				unilib_outchar(ch);
			}
		}

		ch='0';
		while(value > 9999999)
		{
			ch++;
			value-=10000000;
		}
		if(vk > 7)
		{
			if((ch == '0') && (nonzero == 0))
			{
				if(mode & 0x01)	unilib_outchar('0');	//leading zeroes
				if(mode & 0x02)	unilib_outchar(' ');	//leading spaces
			}
			else
			{
				nonzero=1;
				unilib_outchar(ch);
			}
		}

		ch='0';
		while(value > 999999)
		{
			ch++;
			value-=1000000;
		}
		if(vk > 6)
		{
			if((ch == '0') && (nonzero == 0))
			{
				if(mode & 0x01)	unilib_outchar('0');	//leading zeroes
					if(mode & 0x02)	unilib_outchar(' ');	//leading spaces
			}
			else
			{
				nonzero=1;
				unilib_outchar(ch);
			}
		}


		ch='0';
		while(value > 99999)
		{
			ch++;
			value-=100000;
		}
		if(vk > 5)
		{
			if((ch == '0') && (nonzero == 0))
			{
				if(mode & 0x01)	unilib_outchar('0');	//leading zeroes
				if(mode & 0x02)	unilib_outchar(' ');	//leading spaces
				}
			else
			{
				nonzero=1;
				unilib_outchar(ch);
			}
		}
	}
	else
	{
		value &= 0xffff;
	}


	if(mode & 0xc0)		//long + int
	{
		ch='0';
		while(value > 9999)
		{
			ch++;
			value-=10000;
		}
		if(vk > 4)
		{
			if((ch == '0') && (nonzero == 0))
			{
				if(mode & 0x01)	unilib_outchar('0');	//leading zeroes
				if(mode & 0x02)	unilib_outchar(' ');	//leading spaces
			}
				else
			{
				nonzero=1;
				unilib_outchar(ch);
			}
		}

		ch='0';
		while(value > 999)
		{
			ch++;
			value-=1000;
		}
		if(vk > 3)
		{
			if((ch == '0') && (nonzero == 0))
			{
				if(mode & 0x01)	unilib_outchar('0');	//leading zeroes
				if(mode & 0x02)	unilib_outchar(' ');	//leading spaces
				}
			else
			{
				nonzero=1;
				unilib_outchar(ch);
			}
		}
	}
	else
	{
		value &= 0xff;
	}

	ch='0';
	while(value > 99)
	{
		ch++;
		value-=100;
	}
	if(vk > 2)
	{
		if((ch == '0') && (nonzero == 0))
		{
			if(mode & 0x01)	unilib_outchar('0');	//leading zeroes
			if(mode & 0x02)	unilib_outchar(' ');	//leading spaces
		}
		else
		{
			nonzero=1;
			unilib_outchar(ch);
		}
	}
	
	ch='0';
	while(value > 9)
	{
		ch++;
		value-=10;
	}
	if(vk > 1)
	{
		if((ch == '0') && (nonzero == 0))
		{
			if(mode & 0x01)	unilib_outchar('0');	//leading zeroes
			if(mode & 0x02)	unilib_outchar(' ');	//leading spaces
		}
		else
		{
			nonzero=1;
			unilib_outchar(ch);
		}
	}
	unilib_outchar(value+0x30);
}


/*--------------------------------------------------------------------------*/

static void output_hex_long (unsigned long value,unsigned char mode,unsigned char vk)
{
	if(mode & 0x80)	//long
	{
		if(vk > 7) output_digit_long((value >> 28) & 0x0f);
		if(vk > 6) output_digit_long((value >> 24) & 0x0f);
		if(vk > 5) output_digit_long((value >> 20) & 0x0f);
		if(vk > 4) output_digit_long((value >> 16) & 0x0f);
	}
	if(mode & 0xc0)	//long + int
	{
		if(vk > 3) output_digit_long((value >> 12) & 0x0f);
		if(vk > 2) output_digit_long((value >> 8) & 0x0f);
	}

	if(vk > 1) output_digit_long((value >> 4) & 0x0f);
	output_digit_long((value) & 0x0f);
}

static void output_octal_long (unsigned long value,unsigned char mode,unsigned char vk)
{
	if((mode & 0xc0) == 0x80)	//long
	{
		if(vk > 10) output_digit_long((value >> 30) & 0x07);
		if(vk > 9) output_digit_long((value >> 27) & 0x07);
		if(vk > 8) output_digit_long((value >> 24) & 0x07);
		if(vk > 7) output_digit_long((value >> 21) & 0x07);
		if(vk > 6) output_digit_long((value >> 18) & 0x07);
		if(vk > 5) output_digit_long((value >> 15) & 0x07);
		if(vk > 4) output_digit_long((value >> 12) & 0x07);
		if(vk > 3) output_digit_long((value >> 9) & 0x07);
		if(vk > 2) output_digit_long((value >> 6) & 0x07);
		if(vk > 1) output_digit_long((value >> 3) & 0x07);
		output_digit_long((value) & 0x0f);
	}
	else if((mode & 0xc0) == 0x40)	//int
	{
		value &= 0xFFFF;
		if(vk > 5) output_digit_long((value >> 15) & 0x07);
		if(vk > 4) output_digit_long((value >> 12) & 0x07);
		if(vk > 3) output_digit_long((value >> 9) & 0x07);
		if(vk > 2) output_digit_long((value >> 6) & 0x07);
		if(vk > 1) output_digit_long((value >> 3) & 0x07);
		output_digit_long((value) & 0x0f);
	}
	else		//byte
	{
		value &= 0xFF;
		if(vk > 2) output_digit_long((value >> 6) & 0x07);
		if(vk > 1) output_digit_long((value >> 3) & 0x07);
		output_digit_long((value) & 0x0f);
	}
}



/*--------------------------------------------------------------------------*/

static void output_float_long (	float f,unsigned char mode, int nk,unsigned char vk)
{
	unsigned long IntPart=0;
	unsigned int FracPart=0;

	//calculate the integer part
	IntPart = (unsigned long)f;
	f-=IntPart;

	//calculate the fractional part
	f=f*nk+0.5;	//round
	FracPart = (unsigned int)f;

	output_decimal_long(IntPart,mode,vk);
	output_nk(FracPart,nk);
}

static void output_floatex_long (float f,unsigned char mode, int nk,unsigned char vk)
{
	unsigned int IntPart=0;
	unsigned int FracPart=0;
	signed char exp = 0;

	if( f!=0 )
	{
		while(f >= 1000)
		{
			f*=0.001;exp+=3;
		}
		while(f < 1)
		{
			f*=1000;exp-=3;
		}
	}

	//calculate the integer part
	IntPart = (unsigned int)f;
	f-=IntPart;

	//calculate the fractional part
	f=f*nk+0.5;	//round
	FracPart = (unsigned int)f;

	output_decimal_part(IntPart,mode);
	output_nk(FracPart,nk);
	output_decimal_exponent(exp,mode);
}


/*--------------------------------------------------------------------------*/

//#######################################################################
//#									#
//#	get printf channel						#
//#									#
//#######################################################################
void uxprintf (const char *format, ...)
{
	va_list		pointer;
	value_t		value;
	unsigned char	signed_argument;
	unsigned char	mode;
	char		c;
	int		nachkomma;
	unsigned char	vorkomma;

	va_start(pointer,format);

	while(c = *format++)	//loop
	{
		if ( c=='\\' )
		{
			c = *format++;
			switch(c)
			{
				case 'n':	unilib_outchar(0x0a);		//newline
						break;
				case 't':	unilib_outchar(0x09);		//tabulator
						break;
				case 'r':	unilib_outchar(0x0d);		//carriage return
						break;
				case 'f':	unilib_outchar(0x0c);		//form feed
						break;
				default:	unilib_outchar(c);		//escaped char
			}
		}
		else if ( c=='%' )
		{
			signed_argument		= 0;
			mode			= 0x40;		//int
			nachkomma		= 20000;	//default nachkomma
			vorkomma		= 20;		//default vorkomma
get_next_char:
			c = *format++;
			//single char
			if (c=='%')
			{
				unilib_outchar(c);
				continue;
			}

			switch(c)
			{
				case '0':	mode |= 1;		//leading zeroes
						goto get_next_char;

				case '1':	if(nachkomma < 20000) nachkomma=10; else vorkomma=1;
						goto get_next_char;

				case '2':	if(nachkomma < 20000) nachkomma=100; else vorkomma=2;
						goto get_next_char;

				case '3':	if(nachkomma < 20000) nachkomma=1000; else vorkomma=3;
						goto get_next_char;

				case '4':	if(nachkomma < 20000) nachkomma=10000; else vorkomma=4;
						goto get_next_char;

				case '5':	if(nachkomma==20000) vorkomma=5;
						goto get_next_char;

				case '6':	if(nachkomma==20000) vorkomma=6;
						goto get_next_char;

				case '7':	if(nachkomma==20000) vorkomma=7;
						goto get_next_char;

				case '8':	if(nachkomma==20000) vorkomma=8;
						goto get_next_char;

				case '9':	if(nachkomma==20000) vorkomma=9;
						goto get_next_char;

				case '.':	nachkomma=19999;
						goto get_next_char;

				case ' ':	mode |= 2;		//leading spaces
						goto get_next_char;

				case '+':	signed_argument=1;	//signed value
						goto get_next_char;

				case 'b':	mode &= 0x3f;		//byte value
						goto get_next_char;

				case 'l':	mode &= 0x3f;		//byte value
						mode |= 0x80;		//long value
						goto get_next_char;

				//single char
				case 'c':	value.i = (va_arg(pointer, int) & 0xff);
						unilib_outchar(value.i);
						break;

				//a string
				case 's':	value.ptr = va_arg(pointer,const char *);
						while (c = *value.ptr) 
						{
							unilib_outchar(c);
							value.ptr++;
						}
						break;

				case 'd':
				case 'i':	if(mode & 0x80)	//long
						{
							value.l = va_arg(pointer, long);
							if(value.l < 0)
							{
								unilib_outchar('-');
								value.l = -value.l;
							}
							else if(signed_argument == 1)
							{
								unilib_outchar('+');
							}
							output_decimal_long(value.l,mode,vorkomma);
						}
						else if(mode & 0x40) //word
						{
							value.i = va_arg(pointer, int);
							if(value.i < 0)
							{
								unilib_outchar('-');
								value.i = -value.i;
							}
							else if(signed_argument == 1)
							{
								unilib_outchar('+');
							}
							output_decimal_long(value.i,mode,vorkomma);
						}
						else	//byte
						{
							value.i = (va_arg(pointer, int) & 0xff);
							if(value.i > 127)
							{
								unilib_outchar('-');
								value.i = -value.i;
							}
							else if(signed_argument == 1)
							{
								unilib_outchar('+');
							}
							output_decimal_long(value.i,mode,vorkomma);
						}
						break;

				case 'u':	if(mode & 0x80)
						{
							value.ul = va_arg(pointer, unsigned long);
							output_decimal_long(value.ul,mode,vorkomma);
						}
						else
						{
							value.ui = va_arg(pointer, unsigned int);
							output_decimal_long(value.ui,mode,vorkomma);
						}
						break;

				case 'X':
				case 'x':	if(mode & 0x80)
						{
							value.ul = va_arg(pointer, unsigned long);
							output_hex_long(value.ul,mode,vorkomma);
						}
						else
						{
							value.ui = va_arg(pointer, unsigned int);
							output_hex_long(value.ui,mode,vorkomma);
						}
						break;

				case 'o':	if(mode & 0x80)
						{
							value.ul = va_arg(pointer, unsigned long);
							output_octal_long(value.ul,mode,vorkomma);
						}
						else
						{
							value.ui = va_arg(pointer, unsigned int);
							output_octal_long(value.ui,mode,vorkomma);
						}
						break;

				case 'f':	value.f = va_arg(pointer, double);
						if(value.f < 0)
						{
							unilib_outchar('-');
							value.f = -value.f;
						}
						else if(signed_argument == 1)
						{
							unilib_outchar('+');
						}
						output_float_long(value.f,mode,nachkomma,vorkomma);
						break;

				case 'e':	value.f = va_arg(pointer, double);
						if(value.f < 0)
						{
							unilib_outchar('-');
							value.f = -value.f;
						}
						else if(signed_argument == 1)
						{
							unilib_outchar('+');
						}
						output_floatex_long(value.f,mode,nachkomma,vorkomma);
						break;

				default:	break;
			}
		}
		else	unilib_outchar(c);
	}
}

#endif