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
void stage3_rts00(void);
void stage3_rts01(void);
void stage3_rts02(void);
void stage3_rts03(void);
void stage3_rts04(void);
void stage3_rts05(void);
void stage3_rts06(void);
void stage3_rts07(void);

void stage3_ctrl00(void);
void stage3_ctrl01(void);
void stage3_ctrl02(void);
void stage3_ctrl03(void);
void stage3_ctrl04(void);
void stage3_ctrl05(void);
void stage3_ctrl06(void);

void stage3_undef(void);


decode_stage_t	decode_stage3_rts[64]=
{
stage3_rts00,	stage3_rts01,	stage3_rts02,	stage3_rts03,	stage3_rts04,	stage3_rts05,	stage3_rts06,	stage3_rts07,
stage3_undef,	stage3_undef,	stage3_undef,	stage3_undef,	stage3_undef,	stage3_undef,	stage3_undef,	stage3_undef,
stage3_undef,	stage3_undef,	stage3_undef,	stage3_undef,	stage3_undef,	stage3_undef,	stage3_undef,	stage3_undef,
stage3_undef,	stage3_undef,	stage3_undef,	stage3_undef,	stage3_undef,	stage3_undef,	stage3_undef,	stage3_undef,
stage3_undef,	stage3_undef,	stage3_undef,	stage3_undef,	stage3_undef,	stage3_undef,	stage3_undef,	stage3_undef,
stage3_undef,	stage3_undef,	stage3_undef,	stage3_undef,	stage3_undef,	stage3_undef,	stage3_undef,	stage3_undef,
stage3_undef,	stage3_undef,	stage3_undef,	stage3_undef,	stage3_undef,	stage3_undef,	stage3_undef,	stage3_undef,
stage3_undef,	stage3_undef,	stage3_undef,	stage3_undef,	stage3_undef,	stage3_undef,	stage3_undef,	stage3_undef
};

decode_stage_t	decode_stage3_ctrl[64]=
{
stage3_ctrl00,	stage3_ctrl01,	stage3_ctrl02,	stage3_ctrl03,	stage3_ctrl04,	stage3_ctrl05,	stage3_ctrl06,	stage3_undef,
stage3_undef,	stage3_undef,	stage3_undef,	stage3_undef,	stage3_undef,	stage3_undef,	stage3_undef,	stage3_undef,
stage3_undef,	stage3_undef,	stage3_undef,	stage3_undef,	stage3_undef,	stage3_undef,	stage3_undef,	stage3_undef,
stage3_undef,	stage3_undef,	stage3_undef,	stage3_undef,	stage3_undef,	stage3_undef,	stage3_undef,	stage3_undef,
stage3_undef,	stage3_undef,	stage3_undef,	stage3_undef,	stage3_undef,	stage3_undef,	stage3_undef,	stage3_undef,
stage3_undef,	stage3_undef,	stage3_undef,	stage3_undef,	stage3_undef,	stage3_undef,	stage3_undef,	stage3_undef,
stage3_undef,	stage3_undef,	stage3_undef,	stage3_undef,	stage3_undef,	stage3_undef,	stage3_undef,	stage3_undef,
stage3_undef,	stage3_undef,	stage3_undef,	stage3_undef,	stage3_undef,	stage3_undef,	stage3_undef,	stage3_undef
};
