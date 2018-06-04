//###############################################################################
//#										#
//# MXE11 PDP11-Unix Emulator for Mikrocontrollers				#
//#										#
//# copyright (c) 2017-2018 Joerg Wolfram (joerg@jcwolfram.de)			#
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
const unsigned char sysfont[2560]={

	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0xe0,0xe0,0xe0,0xe0,0xe0,0x00,0x00,0x00,0x00,0x00,
	0x1c,0x1c,0x1c,0x1c,0x1c,0x00,0x00,0x00,0x00,0x00,
	0xfc,0xfc,0xfc,0xfc,0xfc,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0xe0,0xe0,0xe0,0xe0,0xe0,
	0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,
	0x1c,0x1c,0x1c,0x1c,0x1c,0xe0,0xe0,0xe0,0xe0,0xe0,
	0xfc,0xfc,0xfc,0xfc,0xfc,0xe0,0xe0,0xe0,0xe0,0xe0,
	0x00,0x00,0x00,0x00,0x00,0x1c,0x1c,0x1c,0x1c,0x1c,
	0xe0,0xe0,0xe0,0xe0,0xe0,0x1c,0x1c,0x1c,0x1c,0x1c,
	0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,
	0xfc,0xfc,0xfc,0xfc,0xfc,0x1c,0x1c,0x1c,0x1c,0x1c,
	0x00,0x00,0x00,0x00,0x00,0xfc,0xfc,0xfc,0xfc,0xfc,
	0xe0,0xe0,0xe0,0xe0,0xe0,0xfc,0xfc,0xfc,0xfc,0xfc,
	0x1c,0x1c,0x1c,0x1c,0x1c,0xfc,0xfc,0xfc,0xfc,0xfc,
	0xfc,0xfc,0xfc,0xfc,0xfc,0xfc,0xfc,0xfc,0xfc,0xfc,
	0xa8,0x54,0xa8,0x54,0xa8,0x54,0xa8,0x54,0xa8,0x54,
	0x30,0x78,0x78,0xfc,0xfc,0xfc,0xfc,0x78,0x78,0x30,
	0x30,0x78,0x78,0xfc,0xfc,0xfc,0xfc,0xfc,0xfc,0xfc,
	0xfc,0xfc,0xfc,0xfc,0xfc,0xfc,0xfc,0x78,0x78,0x30,
	0x04,0xcc,0xfc,0xfc,0xdc,0x1c,0x1c,0x18,0x18,0x18,
	0x80,0xcc,0xfc,0xfc,0xec,0xe0,0xe0,0x60,0x60,0x60,
	0x18,0x18,0x18,0x1c,0x1c,0xdc,0xfc,0xfc,0xcc,0x1c,
	0x60,0x60,0x60,0xe0,0xe0,0xec,0xfc,0xfc,0xcc,0xe0,
	0x30,0x70,0x78,0xf8,0xfc,0x7c,0xf8,0x78,0x7c,0xfc,
	0x00,0x38,0x44,0x44,0x78,0x44,0x44,0x78,0x40,0x40,
	0x00,0x30,0x30,0x00,0x78,0x00,0x30,0x30,0x00,0x00,
	0x00,0x00,0x04,0x78,0x28,0x28,0x28,0x28,0x00,0x00,
	0x00,0x38,0x28,0x38,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x10,0x28,0x7c,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x24,0x24,0x24,0x24,0x38,0x20,0x40,
	0x00,0x00,0x00,0x38,0x44,0x44,0x28,0x6c,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x10,0x10,0x10,0x10,0x10,0x00,0x10,0x00,0x00,
	0x00,0x28,0x28,0x28,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x28,0x28,0x7c,0x28,0x7c,0x28,0x28,0x00,0x00,
	0x00,0x10,0x3c,0x50,0x38,0x14,0x78,0x10,0x00,0x00,
	0x00,0x60,0x64,0x08,0x10,0x20,0x4c,0x0c,0x00,0x00,
	0x00,0x30,0x48,0x50,0x20,0x50,0x48,0x34,0x00,0x00,
	0x00,0x30,0x10,0x20,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x08,0x10,0x20,0x20,0x20,0x10,0x08,0x00,0x00,
	0x00,0x20,0x10,0x08,0x08,0x08,0x10,0x20,0x00,0x00,
	0x00,0x00,0x10,0x54,0x38,0x54,0x10,0x00,0x00,0x00,
	0x00,0x00,0x10,0x10,0x7c,0x10,0x10,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x30,0x10,0x20,0x00,0x00,
	0x00,0x00,0x00,0x00,0x7c,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x30,0x00,0x00,
	0x00,0x00,0x04,0x08,0x10,0x20,0x40,0x00,0x00,0x00,
	0x00,0x38,0x44,0x4c,0x54,0x64,0x44,0x38,0x00,0x00,
	0x00,0x10,0x30,0x10,0x10,0x10,0x10,0x38,0x00,0x00,
	0x00,0x38,0x44,0x04,0x08,0x10,0x20,0x7c,0x00,0x00,
	0x00,0x7c,0x08,0x10,0x08,0x04,0x44,0x38,0x00,0x00,
	0x00,0x08,0x18,0x28,0x48,0x7c,0x08,0x08,0x00,0x00,
	0x00,0x7c,0x40,0x78,0x04,0x04,0x44,0x38,0x00,0x00,
	0x00,0x18,0x20,0x40,0x78,0x44,0x44,0x38,0x00,0x00,
	0x00,0x7c,0x44,0x08,0x10,0x10,0x20,0x20,0x00,0x00,
	0x00,0x38,0x44,0x44,0x38,0x44,0x44,0x38,0x00,0x00,
	0x00,0x38,0x44,0x44,0x3c,0x04,0x08,0x30,0x00,0x00,
	0x00,0x00,0x30,0x30,0x00,0x30,0x30,0x00,0x00,0x00,
	0x00,0x00,0x30,0x30,0x00,0x30,0x10,0x20,0x00,0x00,
	0x00,0x08,0x10,0x20,0x40,0x20,0x10,0x08,0x00,0x00,
	0x00,0x00,0x00,0x7c,0x00,0x7c,0x00,0x00,0x00,0x00,
	0x00,0x20,0x10,0x08,0x04,0x08,0x10,0x20,0x00,0x00,
	0x00,0x38,0x44,0x04,0x08,0x10,0x00,0x10,0x00,0x00,
	0x00,0x38,0x44,0x04,0x34,0x54,0x54,0x38,0x00,0x00,
	0x00,0x38,0x44,0x44,0x44,0x7c,0x44,0x44,0x00,0x00,
	0x00,0x78,0x44,0x44,0x78,0x44,0x44,0x78,0x00,0x00,
	0x00,0x38,0x44,0x40,0x40,0x40,0x44,0x38,0x00,0x00,
	0x00,0x78,0x44,0x44,0x44,0x44,0x44,0x78,0x00,0x00,
	0x00,0x7c,0x40,0x40,0x78,0x40,0x40,0x7c,0x00,0x00,
	0x00,0x7c,0x40,0x40,0x78,0x40,0x40,0x40,0x00,0x00,
	0x00,0x38,0x44,0x40,0x5c,0x44,0x44,0x38,0x00,0x00,
	0x00,0x44,0x44,0x44,0x7c,0x44,0x44,0x44,0x00,0x00,
	0x00,0x38,0x10,0x10,0x10,0x10,0x10,0x38,0x00,0x00,
	0x00,0x1c,0x08,0x08,0x08,0x08,0x48,0x30,0x00,0x00,
	0x00,0x44,0x48,0x50,0x60,0x50,0x48,0x44,0x00,0x00,
	0x00,0x40,0x40,0x40,0x40,0x40,0x40,0x7c,0x00,0x00,
	0x00,0x44,0x6c,0x54,0x54,0x44,0x44,0x44,0x00,0x00,
	0x00,0x44,0x44,0x64,0x54,0x4c,0x44,0x44,0x00,0x00,
	0x00,0x38,0x44,0x44,0x44,0x44,0x44,0x38,0x00,0x00,
	0x00,0x78,0x44,0x44,0x78,0x40,0x40,0x40,0x00,0x00,
	0x00,0x38,0x44,0x44,0x44,0x54,0x4c,0x34,0x00,0x00,
	0x00,0x78,0x44,0x44,0x78,0x50,0x48,0x44,0x00,0x00,
	0x00,0x38,0x44,0x40,0x38,0x04,0x44,0x38,0x00,0x00,
	0x00,0x7c,0x10,0x10,0x10,0x10,0x10,0x10,0x00,0x00,
	0x00,0x44,0x44,0x44,0x44,0x44,0x44,0x38,0x00,0x00,
	0x00,0x44,0x44,0x44,0x44,0x28,0x28,0x10,0x00,0x00,
	0x00,0x44,0x44,0x44,0x44,0x54,0x54,0x38,0x00,0x00,
	0x00,0x44,0x44,0x28,0x10,0x28,0x44,0x44,0x00,0x00,
	0x00,0x44,0x44,0x44,0x28,0x10,0x10,0x10,0x00,0x00,
	0x00,0x7c,0x04,0x08,0x10,0x20,0x40,0x7c,0x00,0x00,
	0x00,0x30,0x20,0x20,0x20,0x20,0x20,0x30,0x00,0x00,
	0x00,0x40,0x40,0x20,0x10,0x08,0x04,0x04,0x00,0x00,
	0x00,0x30,0x10,0x10,0x10,0x10,0x10,0x30,0x00,0x00,
	0x00,0x10,0x28,0x44,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7c,0x00,0x00,
	0x00,0x20,0x10,0x08,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x38,0x04,0x3c,0x44,0x3c,0x00,0x00,
	0x00,0x40,0x40,0x78,0x44,0x44,0x44,0x78,0x00,0x00,
	0x00,0x00,0x00,0x38,0x40,0x40,0x44,0x38,0x00,0x00,
	0x00,0x04,0x04,0x34,0x4c,0x44,0x44,0x38,0x00,0x00,
	0x00,0x00,0x00,0x38,0x44,0x7c,0x40,0x38,0x00,0x00,
	0x00,0x18,0x24,0x20,0x70,0x20,0x20,0x20,0x00,0x00,
	0x00,0x00,0x00,0x3c,0x44,0x44,0x3c,0x04,0x38,0x00,
	0x00,0x40,0x40,0x58,0x64,0x44,0x44,0x44,0x00,0x00,
	0x00,0x10,0x00,0x30,0x10,0x10,0x10,0x38,0x00,0x00,
	0x00,0x08,0x00,0x18,0x08,0x08,0x08,0x48,0x30,0x00,
	0x00,0x40,0x40,0x48,0x50,0x60,0x50,0x48,0x00,0x00,
	0x00,0x30,0x10,0x10,0x10,0x10,0x10,0x38,0x00,0x00,
	0x00,0x00,0x00,0x68,0x54,0x54,0x44,0x44,0x00,0x00,
	0x00,0x00,0x00,0x58,0x64,0x44,0x44,0x44,0x00,0x00,
	0x00,0x00,0x00,0x38,0x44,0x44,0x44,0x38,0x00,0x00,
	0x00,0x00,0x00,0x70,0x48,0x48,0x70,0x40,0x40,0x00,
	0x00,0x00,0x00,0x38,0x48,0x48,0x38,0x08,0x0c,0x00,
	0x00,0x00,0x00,0x58,0x64,0x40,0x40,0x40,0x00,0x00,
	0x00,0x00,0x00,0x38,0x40,0x38,0x04,0x78,0x00,0x00,
	0x00,0x20,0x20,0x70,0x20,0x20,0x28,0x10,0x00,0x00,
	0x00,0x00,0x00,0x44,0x44,0x44,0x4c,0x34,0x00,0x00,
	0x00,0x00,0x00,0x44,0x44,0x44,0x28,0x10,0x00,0x00,
	0x00,0x00,0x00,0x44,0x44,0x44,0x54,0x28,0x00,0x00,
	0x00,0x00,0x00,0x44,0x28,0x10,0x28,0x44,0x00,0x00,
	0x00,0x00,0x00,0x44,0x44,0x34,0x0c,0x04,0x38,0x00,
	0x00,0x00,0x00,0x7c,0x08,0x10,0x20,0x7c,0x00,0x00,
	0x00,0x08,0x10,0x10,0x20,0x10,0x10,0x08,0x00,0x00,
	0x00,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x00,0x00,
	0x00,0x20,0x10,0x10,0x08,0x10,0x10,0x20,0x00,0x00,
	0x00,0x00,0x00,0x20,0x54,0x08,0x00,0x00,0x00,0x00,
	0x00,0x00,0x10,0x08,0xfc,0x08,0x10,0x00,0x00,0x00,
	0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	0x1f,0x1f,0x1f,0x1f,0x1f,0xff,0xff,0xff,0xff,0xff,
	0xe3,0xe3,0xe3,0xe3,0xe3,0xff,0xff,0xff,0xff,0xff,
	0x03,0x03,0x03,0x03,0x03,0xff,0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0xff,0x1f,0x1f,0x1f,0x1f,0x1f,
	0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,
	0xe3,0xe3,0xe3,0xe3,0xe3,0x1f,0x1f,0x1f,0x1f,0x1f,
	0x03,0x03,0x03,0x03,0x03,0x1f,0x1f,0x1f,0x1f,0x1f,
	0xff,0xff,0xff,0xff,0xff,0xe3,0xe3,0xe3,0xe3,0xe3,
	0x1f,0x1f,0x1f,0x1f,0x1f,0xe3,0xe3,0xe3,0xe3,0xe3,
	0xe3,0xe3,0xe3,0xe3,0xe3,0xe3,0xe3,0xe3,0xe3,0xe3,
	0x03,0x03,0x03,0x03,0x03,0xe3,0xe3,0xe3,0xe3,0xe3,
	0xff,0xff,0xff,0xff,0xff,0x03,0x03,0x03,0x03,0x03,
	0x1f,0x1f,0x1f,0x1f,0x1f,0x03,0x03,0x03,0x03,0x03,
	0xe3,0xe3,0xe3,0xe3,0xe3,0x03,0x03,0x03,0x03,0x03,
	0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,
	0x57,0xab,0x57,0xab,0x57,0xab,0x57,0xab,0x57,0xab,
	0xcf,0x87,0x87,0x03,0x03,0x03,0x03,0x87,0x87,0xcf,
	0xcf,0x87,0x87,0x03,0x03,0x03,0x03,0x03,0x03,0x03,
	0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x87,0x87,0xcf,
	0xfb,0x33,0x03,0x03,0x23,0xe3,0xe3,0xe7,0xe7,0xe7,
	0x7f,0x33,0x03,0x03,0x13,0x1f,0x1f,0x9f,0x9f,0x9f,
	0xe7,0xe7,0xe7,0xe3,0xe3,0x23,0x03,0x03,0x33,0xe3,
	0x9f,0x9f,0x9f,0x1f,0x1f,0x13,0x03,0x03,0x33,0x1f,
	0xcf,0x8f,0x87,0x07,0x03,0x83,0x07,0x87,0x83,0x03,
	0xff,0xc7,0xbb,0xbb,0x87,0xbb,0xbb,0x87,0xbf,0xbf,
	0xff,0xcf,0xcf,0xff,0x87,0xff,0xcf,0xcf,0xff,0xff,
	0xff,0xff,0xfb,0x87,0xd7,0xd7,0xd7,0xd7,0xff,0xff,
	0xff,0xc7,0xd7,0xc7,0xff,0xff,0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xef,0xd7,0x83,0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xdb,0xdb,0xdb,0xdb,0xc7,0xdf,0xbf,
	0xff,0xff,0xff,0xc7,0xbb,0xbb,0xd7,0x93,0xff,0xff,
	0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	0xff,0xef,0xef,0xef,0xef,0xef,0xff,0xef,0xff,0xff,
	0xff,0xd7,0xd7,0xd7,0xff,0xff,0xff,0xff,0xff,0xff,
	0xff,0xd7,0xd7,0x83,0xd7,0x83,0xd7,0xd7,0xff,0xff,
	0xff,0xef,0xc3,0xaf,0xc7,0xeb,0x87,0xef,0xff,0xff,
	0xff,0x9f,0x9b,0xf7,0xef,0xdf,0xb3,0xf3,0xff,0xff,
	0xff,0xcf,0xb7,0xaf,0xdf,0xaf,0xb7,0xcb,0xff,0xff,
	0xff,0xcf,0xef,0xdf,0xff,0xff,0xff,0xff,0xff,0xff,
	0xff,0xf7,0xef,0xdf,0xdf,0xdf,0xef,0xf7,0xff,0xff,
	0xff,0xdf,0xef,0xf7,0xf7,0xf7,0xef,0xdf,0xff,0xff,
	0xff,0xff,0xef,0xab,0xc7,0xab,0xef,0xff,0xff,0xff,
	0xff,0xff,0xef,0xef,0x83,0xef,0xef,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0xff,0xcf,0xef,0xdf,0xff,0xff,
	0xff,0xff,0xff,0xff,0x83,0xff,0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0xff,0xff,0xcf,0xcf,0xff,0xff,
	0xff,0xff,0xfb,0xf7,0xef,0xdf,0xbf,0xff,0xff,0xff,
	0xff,0xc7,0xbb,0xb3,0xab,0x9b,0xbb,0xc7,0xff,0xff,
	0xff,0xef,0xcf,0xef,0xef,0xef,0xef,0xc7,0xff,0xff,
	0xff,0xc7,0xbb,0xfb,0xf7,0xef,0xdf,0x83,0xff,0xff,
	0xff,0x83,0xf7,0xef,0xf7,0xfb,0xbb,0xc7,0xff,0xff,
	0xff,0xf7,0xe7,0xd7,0xb7,0x83,0xf7,0xf7,0xff,0xff,
	0xff,0x83,0xbf,0x87,0xfb,0xfb,0xbb,0xc7,0xff,0xff,
	0xff,0xe7,0xdf,0xbf,0x87,0xbb,0xbb,0xc7,0xff,0xff,
	0xff,0x83,0xbb,0xf7,0xef,0xef,0xdf,0xdf,0xff,0xff,
	0xff,0xc7,0xbb,0xbb,0xc7,0xbb,0xbb,0xc7,0xff,0xff,
	0xff,0xc7,0xbb,0xbb,0xc3,0xfb,0xf7,0xcf,0xff,0xff,
	0xff,0xff,0xcf,0xcf,0xff,0xcf,0xcf,0xff,0xff,0xff,
	0xff,0xff,0xcf,0xcf,0xff,0xcf,0xef,0xdf,0xff,0xff,
	0xff,0xf7,0xef,0xdf,0xbf,0xdf,0xef,0xf7,0xff,0xff,
	0xff,0xff,0xff,0x83,0xff,0x83,0xff,0xff,0xff,0xff,
	0xff,0xdf,0xef,0xf7,0xfb,0xf7,0xef,0xdf,0xff,0xff,
	0xff,0xc7,0xbb,0xfb,0xf7,0xef,0xff,0xef,0xff,0xff,
	0xff,0xc7,0xbb,0xfb,0xcb,0xab,0xab,0xc7,0xff,0xff,
	0xff,0xc7,0xbb,0xbb,0xbb,0x83,0xbb,0xbb,0xff,0xff,
	0xff,0x87,0xbb,0xbb,0x87,0xbb,0xbb,0x87,0xff,0xff,
	0xff,0xc7,0xbb,0xbf,0xbf,0xbf,0xbb,0xc7,0xff,0xff,
	0xff,0x87,0xbb,0xbb,0xbb,0xbb,0xbb,0x87,0xff,0xff,
	0xff,0x83,0xbf,0xbf,0x87,0xbf,0xbf,0x83,0xff,0xff,
	0xff,0x83,0xbf,0xbf,0x87,0xbf,0xbf,0xbf,0xff,0xff,
	0xff,0xc7,0xbb,0xbf,0xa3,0xbb,0xbb,0xc7,0xff,0xff,
	0xff,0xbb,0xbb,0xbb,0x83,0xbb,0xbb,0xbb,0xff,0xff,
	0xff,0xc7,0xef,0xef,0xef,0xef,0xef,0xc7,0xff,0xff,
	0xff,0xe3,0xf7,0xf7,0xf7,0xf7,0xb7,0xcf,0xff,0xff,
	0xff,0xbb,0xb7,0xaf,0x9f,0xaf,0xb7,0xbb,0xff,0xff,
	0xff,0xbf,0xbf,0xbf,0xbf,0xbf,0xbf,0x83,0xff,0xff,
	0xff,0xbb,0x93,0xab,0xab,0xbb,0xbb,0xbb,0xff,0xff,
	0xff,0xbb,0xbb,0x9b,0xab,0xb3,0xbb,0xbb,0xff,0xff,
	0xff,0xc7,0xbb,0xbb,0xbb,0xbb,0xbb,0xc7,0xff,0xff,
	0xff,0x87,0xbb,0xbb,0x87,0xbf,0xbf,0xbf,0xff,0xff,
	0xff,0xc7,0xbb,0xbb,0xbb,0xab,0xb3,0xcb,0xff,0xff,
	0xff,0x87,0xbb,0xbb,0x87,0xaf,0xb7,0xbb,0xff,0xff,
	0xff,0xc7,0xbb,0xbf,0xc7,0xfb,0xbb,0xc7,0xff,0xff,
	0xff,0x83,0xef,0xef,0xef,0xef,0xef,0xef,0xff,0xff,
	0xff,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xc7,0xff,0xff,
	0xff,0xbb,0xbb,0xbb,0xbb,0xd7,0xd7,0xef,0xff,0xff,
	0xff,0xbb,0xbb,0xbb,0xbb,0xab,0xab,0xc7,0xff,0xff,
	0xff,0xbb,0xbb,0xd7,0xef,0xd7,0xbb,0xbb,0xff,0xff,
	0xff,0xbb,0xbb,0xbb,0xd7,0xef,0xef,0xef,0xff,0xff,
	0xff,0x83,0xfb,0xf7,0xef,0xdf,0xbf,0x83,0xff,0xff,
	0xff,0xcf,0xdf,0xdf,0xdf,0xdf,0xdf,0xcf,0xff,0xff,
	0xff,0xbf,0xbf,0xdf,0xef,0xf7,0xfb,0xfb,0xff,0xff,
	0xff,0xcf,0xef,0xef,0xef,0xef,0xef,0xcf,0xff,0xff,
	0xff,0xef,0xd7,0xbb,0xff,0xff,0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x83,0xff,0xff,
	0xff,0xdf,0xef,0xf7,0xff,0xff,0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xc7,0xfb,0xc3,0xbb,0xc3,0xff,0xff,
	0xff,0xbf,0xbf,0x87,0xbb,0xbb,0xbb,0x87,0xff,0xff,
	0xff,0xff,0xff,0xc7,0xbf,0xbf,0xbb,0xc7,0xff,0xff,
	0xff,0xfb,0xfb,0xcb,0xb3,0xbb,0xbb,0xc7,0xff,0xff,
	0xff,0xff,0xff,0xc7,0xbb,0x83,0xbf,0xc7,0xff,0xff,
	0xff,0xe7,0xdb,0xdf,0x8f,0xdf,0xdf,0xdf,0xff,0xff,
	0xff,0xff,0xff,0xc3,0xbb,0xbb,0xc3,0xfb,0xc7,0xff,
	0xff,0xbf,0xbf,0xa7,0x9b,0xbb,0xbb,0xbb,0xff,0xff,
	0xff,0xef,0xff,0xcf,0xef,0xef,0xef,0xc7,0xff,0xff,
	0xff,0xf7,0xff,0xe7,0xf7,0xf7,0xf7,0xb7,0xcf,0xff,
	0xff,0xbf,0xbf,0xb7,0xaf,0x9f,0xaf,0xb7,0xff,0xff,
	0xff,0xcf,0xef,0xef,0xef,0xef,0xef,0xc7,0xff,0xff,
	0xff,0xff,0xff,0x97,0xab,0xab,0xbb,0xbb,0xff,0xff,
	0xff,0xff,0xff,0xa7,0x9b,0xbb,0xbb,0xbb,0xff,0xff,
	0xff,0xff,0xff,0xc7,0xbb,0xbb,0xbb,0xc7,0xff,0xff,
	0xff,0xff,0xff,0x8f,0xb7,0xb7,0x8f,0xbf,0xbf,0xff,
	0xff,0xff,0xff,0xc7,0xb7,0xb7,0xc7,0xf7,0xf3,0xff,
	0xff,0xff,0xff,0xa7,0x9b,0xbf,0xbf,0xbf,0xff,0xff,
	0xff,0xff,0xff,0xc7,0xbf,0xc7,0xfb,0x87,0xff,0xff,
	0xff,0xdf,0xdf,0x8f,0xdf,0xdf,0xd7,0xef,0xff,0xff,
	0xff,0xff,0xff,0xbb,0xbb,0xbb,0xb3,0xcb,0xff,0xff,
	0xff,0xff,0xff,0xbb,0xbb,0xbb,0xd7,0xef,0xff,0xff,
	0xff,0xff,0xff,0xbb,0xbb,0xbb,0xab,0xd7,0xff,0xff,
	0xff,0xff,0xff,0xbb,0xd7,0xef,0xd7,0xbb,0xff,0xff,
	0xff,0xff,0xff,0xbb,0xbb,0xcb,0xf3,0xfb,0xc7,0xff,
	0xff,0xff,0xff,0x83,0xf7,0xef,0xdf,0x83,0xff,0xff,
	0xff,0xf7,0xef,0xef,0xdf,0xef,0xef,0xf7,0xff,0xff,
	0xff,0xef,0xef,0xef,0xef,0xef,0xef,0xef,0xff,0xff,
	0xff,0xdf,0xef,0xef,0xf7,0xef,0xef,0xdf,0xff,0xff,
	0xff,0xff,0xff,0xdf,0xab,0xf7,0xff,0xff,0xff,0xff,
	0xff,0xff,0xef,0xf7,0x03,0xf7,0xef,0xff,0xff,0xff,
};
