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

//##############################################################################
//# prototypes
//##############################################################################
extern void stage1_00(void);
extern void stage1_01(void);
extern void stage1_02(void);
extern void stage1_03(void);
extern void stage1_04(void);
extern void stage1_05(void);
extern void stage1_06(void);
extern void stage1_07(void);
extern void stage1_10(void);
extern void stage1_11(void);
extern void stage1_12(void);
extern void stage1_13(void);
extern void stage1_14(void);
extern void stage1_15(void);
extern void stage1_16(void);
extern void stage1_17(void);

decode_stage_t	decode_estage1[16]=
{
stage1_00,	stage1_01,	stage1_02,	stage1_03,	stage1_04,	stage1_05,	stage1_06,	stage1_07,
stage1_10,	stage1_11,	stage1_12,	stage1_13,	stage1_14,	stage1_15,	stage1_16,	stage1_17
};
