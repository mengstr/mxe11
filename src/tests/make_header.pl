#!/usr/bin/perl
#################################################################################
#										#
# rom data generator/patcher for AX81						#
# copyright (c) 2010-2011 Joerg Wolfram (joerg@jcwolfram.de)			#
#										#
# This program is free software; you can redistribute it and/or			#
# modify it under the terms of the GNU General Public License			#
# as published by the Free Software Foundation; either version 3		#
# of the License, or (at your option) any later version.			#
#										#
# This program is distributed in the hope that it will be useful,		#
# but WITHOUT ANY WARRANTY; without even the implied warranty of		#
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the GNU		#
# General Public License for more details.					#
#										#
# You should have received a copy of the GNU General Public			#
# License along with this library; if not, write to the				#
# Free Software Foundation, Inc., 59 Temple Place - Suite 330,			#
# Boston, MA 02111-1307, USA.							#
#										#
#################################################################################
use POSIX;
use Fcntl;

$binfile="itest1";
$binhead=$binfile."_data";
$binhead=~ s/\.o\_/\_o\_/g;
$binhead=~ s/\.a\_/\_a\_/g;
$datfile=">../inc/".$binhead.".h";


&gencode;

print "SRC = $binfile \n";
print "DST = $datfile \n";

sub gencode
{
	for($i=0;$i<65536;$i++)
	{
		$romdata[$i]=chr(0);
	}
	$dlen = -s $binfile;
	open (BREAD, $binfile);
	binmode(BREAD);
	for($i=0;$i<$dlen;$i++)
	{
		read(BREAD,$romdata[$i],1);
	}
	close(BREAD);

	$dlen+=1039;
	$dlen&= 0xFC00;
	$hlen=$dlen/2;

	print "FILE SIZE = $dlen\n";

	open (DWRITE,$datfile);
	
	print DWRITE "const unsigned short ".$binhead."[".$hlen."]". "= {";

	for($i=0;$i<$hlen;$i++)
	{
		if(($i%16)==0)
		{
			printf DWRITE "\n",$i;
		}
		$ibyte=$romdata[2*$i];
		$iwert=ord($ibyte);
		$ibyte=$romdata[2*$i+1];
		$iwert+=(ord($ibyte) << 8);
		if($iwert==0)
		{
			print DWRITE "0x0000";
		}
		else
		{
			printf DWRITE "%#4.4x",$iwert;
		}
		if($i<($dlen-1))
		{
			print DWRITE ",";
		}
	}
	print DWRITE "};\n";

	close(DWRITE);
}

