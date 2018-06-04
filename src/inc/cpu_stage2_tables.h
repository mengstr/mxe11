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
void stage2_undf(void);

void stage2_0000(void);void stage2_0001(void);void stage2_0002(void);void stage2_0003(void);
void stage2_0004(void);void stage2_0005(void);void stage2_0006(void);void stage2_0007(void);
void stage2_0010(void);void stage2_0011(void);void stage2_0012(void);void stage2_0013(void);
void stage2_0014(void);void stage2_0015(void);void stage2_0016(void);void stage2_0017(void);
void stage2_0020(void);void stage2_0021(void);void stage2_0022(void);void stage2_0023(void);
void stage2_0024(void);void stage2_0025(void);void stage2_0026(void);void stage2_0027(void);
void stage2_0030(void);void stage2_0031(void);void stage2_0032(void);void stage2_0033(void);
void stage2_0034(void);void stage2_0035(void);void stage2_0036(void);void stage2_0037(void);
void stage2_0040(void);void stage2_0041(void);void stage2_0042(void);void stage2_0043(void);
void stage2_0044(void);void stage2_0045(void);void stage2_0046(void);void stage2_0047(void);
void stage2_0050(void);void stage2_0051(void);void stage2_0052(void);void stage2_0053(void);
void stage2_0054(void);void stage2_0055(void);void stage2_0056(void);void stage2_0057(void);
void stage2_0060(void);void stage2_0061(void);void stage2_0062(void);void stage2_0063(void);
void stage2_0064(void);void stage2_0067(void);
void stage2_0070(void);void stage2_0071(void);void stage2_0072(void);void stage2_0073(void);
void stage2_0074(void);void stage2_0075(void);void stage2_0076(void);void stage2_0077(void);
void stage2_0700(void);void stage2_0701(void);void stage2_0702(void);void stage2_0703(void);
void stage2_0704(void);void stage2_0705(void);void stage2_0706(void);void stage2_0707(void);
void stage2_0710(void);void stage2_0711(void);void stage2_0712(void);void stage2_0713(void);
void stage2_0714(void);void stage2_0715(void);void stage2_0716(void);void stage2_0717(void);
void stage2_0720(void);void stage2_0721(void);void stage2_0722(void);void stage2_0723(void);
void stage2_0724(void);void stage2_0725(void);void stage2_0726(void);void stage2_0727(void);
void stage2_0730(void);void stage2_0731(void);void stage2_0732(void);void stage2_0733(void);
void stage2_0734(void);void stage2_0735(void);void stage2_0736(void);void stage2_0737(void);
void stage2_0740(void);void stage2_0741(void);void stage2_0742(void);void stage2_0743(void);
void stage2_0744(void);void stage2_0745(void);void stage2_0746(void);void stage2_0747(void);
void stage2_0750(void);void stage2_0751(void);void stage2_0752(void);void stage2_0753(void);
void stage2_0754(void);void stage2_0755(void);void stage2_0756(void);void stage2_0757(void);
void stage2_0760(void);void stage2_0761(void);void stage2_0762(void);void stage2_0763(void);
void stage2_0764(void);void stage2_0765(void);void stage2_0766(void);void stage2_0767(void);
void stage2_0770(void);void stage2_0771(void);void stage2_0772(void);void stage2_0773(void);
void stage2_0774(void);void stage2_0775(void);void stage2_0776(void);void stage2_0777(void);

void stage2_1000(void);void stage2_1001(void);void stage2_1002(void);void stage2_1003(void);
void stage2_1004(void);void stage2_1005(void);void stage2_1006(void);void stage2_1007(void);
void stage2_1010(void);void stage2_1011(void);void stage2_1012(void);void stage2_1013(void);
void stage2_1014(void);void stage2_1015(void);void stage2_1016(void);void stage2_1017(void);
void stage2_1020(void);void stage2_1021(void);void stage2_1022(void);void stage2_1023(void);
void stage2_1024(void);void stage2_1025(void);void stage2_1026(void);void stage2_1027(void);
void stage2_1030(void);void stage2_1031(void);void stage2_1032(void);void stage2_1033(void);
void stage2_1034(void);void stage2_1035(void);void stage2_1036(void);void stage2_1037(void);
void stage2_1040(void);void stage2_1041(void);void stage2_1042(void);void stage2_1043(void);
void stage2_1044(void);void stage2_1045(void);void stage2_1046(void);void stage2_1047(void);
void stage2_1050(void);void stage2_1051(void);void stage2_1052(void);void stage2_1053(void);
void stage2_1054(void);void stage2_1055(void);void stage2_1056(void);void stage2_1057(void);
void stage2_1060(void);void stage2_1061(void);void stage2_1062(void);void stage2_1063(void);
void stage2_1064(void);void stage2_1067(void);
void stage2_1070(void);void stage2_1071(void);void stage2_1072(void);void stage2_1073(void);
void stage2_1074(void);void stage2_1075(void);void stage2_1076(void);void stage2_1077(void);

void stage2_1700(void);void stage2_1701(void);void stage2_1702(void);void stage2_1703(void);
void stage2_1704(void);void stage2_1705(void);void stage2_1706(void);void stage2_1707(void);
void stage2_1710(void);void stage2_1711(void);void stage2_1712(void);void stage2_1713(void);
void stage2_1714(void);void stage2_1715(void);void stage2_1716(void);void stage2_1717(void);
void stage2_1720(void);void stage2_1721(void);void stage2_1722(void);void stage2_1723(void);
void stage2_1724(void);void stage2_1725(void);void stage2_1726(void);void stage2_1727(void);
void stage2_1730(void);void stage2_1731(void);void stage2_1732(void);void stage2_1733(void);
void stage2_1734(void);void stage2_1735(void);void stage2_1736(void);void stage2_1737(void);
void stage2_1740(void);void stage2_1741(void);void stage2_1742(void);void stage2_1743(void);
void stage2_1744(void);void stage2_1745(void);void stage2_1746(void);void stage2_1747(void);
void stage2_1750(void);void stage2_1751(void);void stage2_1752(void);void stage2_1753(void);
void stage2_1754(void);void stage2_1755(void);void stage2_1756(void);void stage2_1757(void);
void stage2_1760(void);void stage2_1761(void);void stage2_1762(void);void stage2_1763(void);
void stage2_1764(void);void stage2_1765(void);void stage2_1766(void);void stage2_1767(void);
void stage2_1770(void);void stage2_1771(void);void stage2_1772(void);void stage2_1773(void);
void stage2_1774(void);void stage2_1775(void);void stage2_1776(void);void stage2_1777(void);


decode_stage_t	decode_stage2_00[64]=
{
	stage2_0000,	stage2_0001,	// 0000 0001
	stage2_0002,	stage2_0003,	// 0002 0003
	stage2_0004,	stage2_0004,	// 0004 0005
	stage2_0006,	stage2_0006,	// 0006 0007
	stage2_0010,	stage2_0010,	// 0010 0011
	stage2_0012,	stage2_0012,	// 0012 0013
	stage2_0014,	stage2_0014,	// 0014 0015
	stage2_0016,	stage2_0016,	// 0016 0017
	stage2_0020,	stage2_0020,	// 0020 0021
	stage2_0022,	stage2_0022,	// 0022 0023
	stage2_0024,	stage2_0024,	// 0024 0025
	stage2_0026,	stage2_0026,	// 0026 0027
	stage2_0030,	stage2_0030,	// 0030 0031
	stage2_0032,	stage2_0032,	// 0032 0033
	stage2_0034,	stage2_0034,	// 0034 0035
	stage2_0036,	stage2_0036,	// 0036 0037
	stage2_0040,	stage2_0041,	// 0040 0041
	stage2_0042,	stage2_0043,	// 0042 0043
	stage2_0044,	stage2_0045,	// 0044 0045
	stage2_0046,	stage2_0047,	// 0046 0047
	stage2_0050,	stage2_0051,	// 0050 0051
	stage2_0052,	stage2_0053,	// 0052 0053
	stage2_0054,	stage2_0055,	// 0054 0055
	stage2_0056,	stage2_0057,	// 0056 0057
	stage2_0060,	stage2_0061,	// 0060 0061
	stage2_0062,	stage2_0063,	// 0062 0063
	stage2_0064,	stage2_undf,	// 0064 0065
	stage2_undf,	stage2_0067,	// 0066 0067
	stage2_undf,	stage2_undf,	// 0070 0071
	stage2_undf,	stage2_undf,	// 0072 0073
	stage2_undf,	stage2_undf,	// 0074 0075
	stage2_undf,	stage2_undf	// 0076 0077
};

decode_stage_t	decode_stage2_10[64]=
{
	stage2_1000,	stage2_1000,	// 1000 1001
	stage2_1002,	stage2_1002,	// 1002 1003
	stage2_1004,	stage2_1004,	// 1004 1005
	stage2_1006,	stage2_1006,	// 1006 1007
	stage2_1010,	stage2_1010,	// 1010 1011
	stage2_1012,	stage2_1012,	// 1012 1013
	stage2_1014,	stage2_1014,	// 1014 1015
	stage2_1016,	stage2_1016,	// 1016 1017
	stage2_1020,	stage2_1020,	// 1020 1021
	stage2_1022,	stage2_1022,	// 1022 1023
	stage2_1024,	stage2_1024,	// 1024 1025
	stage2_1026,	stage2_1026,	// 1026 1027
	stage2_1030,	stage2_1030,	// 1030 1031
	stage2_1032,	stage2_1032,	// 1032 1033
	stage2_1034,	stage2_1034,	// 1034 1035
	stage2_1036,	stage2_1036,	// 1036 1037
	stage2_1040,	stage2_1040,	// 1040 1041
	stage2_1040,	stage2_1040,	// 1042 1043
	stage2_1044,	stage2_1044,	// 1044 1045
	stage2_1044,	stage2_1044,	// 1046 1047
	stage2_1050,	stage2_1051,	// 1050 1051
	stage2_1052,	stage2_1053,	// 1052 1053
	stage2_1054,	stage2_1055,	// 1054 1055
	stage2_1056,	stage2_1057,	// 1056 1057
	stage2_1060,	stage2_1061,	// 1060 1061
	stage2_1062,	stage2_1063,	// 1062 1063
	stage2_1064,	stage2_undf,	// 1064 1065
	stage2_undf,	stage2_1067,	// 1066 1067
	stage2_undf,	stage2_undf,	// 1070 1071
	stage2_undf,	stage2_undf,	// 1072 1073
	stage2_undf,	stage2_undf,	// 1074 1075
	stage2_undf,	stage2_undf};	// 1076 1077

decode_stage_t	decode_stage2_07[64]=
{
	stage2_0700,	stage2_0701,	// 0700 0701
	stage2_0702,	stage2_0703,	// 0702 0703
	stage2_0704,	stage2_0705,	// 0704 0705
	stage2_0706,	stage2_0707,	// 0706 0707
	stage2_0710,	stage2_undf,	// 0710 0711
	stage2_0712,	stage2_undf,	// 0712 0713
	stage2_0714,	stage2_undf,	// 0714 0715
	stage2_0716,	stage2_undf,	// 0716 0717
	stage2_0720,	stage2_0721,	// 0720 0721
	stage2_0722,	stage2_0723,	// 0722 0723
	stage2_0724,	stage2_0725,	// 0724 0725
	stage2_0726,	stage2_0727,	// 0726 0727
	stage2_0730,	stage2_0731,	// 0730 0731
	stage2_0732,	stage2_0733,	// 0732 0733
	stage2_0734,	stage2_0735,	// 0734 0735
	stage2_undf,	stage2_undf,	// 0736 0737
	stage2_0740,	stage2_0741,	// 0740 0741
	stage2_0742,	stage2_0743,	// 0742 0743
	stage2_0744,	stage2_0745,	// 0744 0745
	stage2_0746,	stage2_0747,	// 0746 0747
	stage2_undf,	stage2_undf,	// 0750 0751
	stage2_undf,	stage2_undf,	// 0752 0753
	stage2_undf,	stage2_undf,	// 0754 0755
	stage2_undf,	stage2_undf,	// 0756 0757
	stage2_undf,	stage2_undf,	// 0760 0761
	stage2_undf,	stage2_undf,	// 0762 0763
	stage2_undf,	stage2_undf,	// 0764 0765
	stage2_undf,	stage2_undf,	// 0766 0767
	stage2_0770,	stage2_0771,	// 0770 0771
	stage2_0772,	stage2_0773,	// 0772 0773
	stage2_0774,	stage2_0775,	// 0774 0775
	stage2_undf,	stage2_undf	// 0776 0777
};

//FPU is not present
decode_stage_t	decode_stage2_17[64]=
{
	stage2_undf,	stage2_undf,	// 1700 1701
	stage2_undf,	stage2_undf,	// 1702 1703
	stage2_undf,	stage2_undf,	// 1704 1705
	stage2_undf,	stage2_undf,	// 1706 1707
	stage2_undf,	stage2_undf,	// 1710 1711
	stage2_undf,	stage2_undf,	// 1712 1713
	stage2_undf,	stage2_undf,	// 1714 1715
	stage2_undf,	stage2_undf,	// 1716 1717
	stage2_undf,	stage2_undf,	// 1720 1721
	stage2_undf,	stage2_undf,	// 1722 1723
	stage2_undf,	stage2_undf,	// 1724 1725
	stage2_undf,	stage2_undf,	// 1726 1727
	stage2_undf,	stage2_undf,	// 1730 1731
	stage2_undf,	stage2_undf,	// 1732 1733
	stage2_undf,	stage2_undf,	// 1734 1735
	stage2_undf,	stage2_undf,	// 1736 1737
	stage2_undf,	stage2_undf,	// 1740 1741
	stage2_undf,	stage2_undf,	// 1742 1743
	stage2_undf,	stage2_undf,	// 1744 1745
	stage2_undf,	stage2_undf,	// 1746 1747
	stage2_undf,	stage2_undf,	// 1750 1751
	stage2_undf,	stage2_undf,	// 1752 1753
	stage2_undf,	stage2_undf,	// 1754 1755
	stage2_undf,	stage2_undf,	// 1756 1757
	stage2_undf,	stage2_undf,	// 1760 1761
	stage2_undf,	stage2_undf,	// 1762 1763
	stage2_undf,	stage2_undf,	// 1764 1765
	stage2_undf,	stage2_undf,	// 1766 1767
	stage2_undf,	stage2_undf,	// 1770 1771
	stage2_undf,	stage2_undf,	// 1772 1773
	stage2_undf,	stage2_undf,	// 1774 1775
	stage2_undf,	stage2_undf	// 1776 1777
};

