#
/*
 * This routine converts time as follows.
 * The epoch is 0000 Jan 1 1970 GMT.
 * The argument time is in seconds since then.
 * The localtime(t) entry returns a pointer to an array
 * containing
 *  seconds (0-59)
 *  minutes (0-59)
 *  hours (0-23)
 *  day of month (1-31)
 *  month (0-11)
 *  year-1970
 *  weekday (0-6, Sun is 0)
 *  day of the year
 *  daylight savings flag
 *
 * The routine corrects for daylight saving
 * time and will work in any time zone provided
 * "timezone" is adjusted to the difference between
 * Greenwich and local standard time (measured in seconds).
 * In places like Michigan "daylight" must
 * be initialized to 0 to prevent the conversion
 * to daylight time.
 * There is a table which accounts for the peculiarities
 * undergone by daylight time in 1974-1975.
 *
 * The routine does not work
 * in Saudi Arabia which runs on Solar time.
 *
 * asctime(tvec))
 * where tvec is produced by localtime
 * returns a ptr to a character string
 * that has the ascii time in the form
 *	Thu Jan 01 00:00:00 1970n\\
 *	01234567890123456789012345
 *	0	  1	    2
 *
 * ctime(t) just calls localtime, then asctime.
 */
char	cbuf[26];
int	dmsize[12]
{
	31,
	28,
	31,
	30,
	31,
	30,
	31,
	31,
	30,
	31,
	30,
	31
};

int timezone	0*60*60;
int tzname[]
{
	"UTC",
	"UTC",
};
int	daylight 0;	/* Allow daylight conversion */

#define	SEC	0
#define	MIN	1
#define	HOUR	2
#define	MDAY	3
#define	MON	4
#define	YEAR	5
#define	WDAY	6
#define	YDAY	7
#define	ISDAY	8

ctime(at)
int *at;
{
	return(asctime(localtime(at)));
}

localtime(tim)
int tim[];
{
	register int *t, *ct, dayno;
	int daylbegin, daylend;
	int copyt[2];

	t = copyt;
	t[0] = tim[0];
	t[1] = tim[1];
	dpadd(t, -timezone);
	ct = gmtime(t);
	return(ct);
}

/* Convert a Unix time in a long (which is GMT) to separate fields.
 *
 * Note check for (and hack handle of) overflow into negative numbers
 * of the number of 8-hour units since the epoch. This hack fix will also
 * break, in 2029 or so (when the number of 8-hour periods overflows 16
 * bits).
 *
 * The hack separates a number like 100001 (in octal, i.e. 32769.), into two
 * parts - 32767 (the largest positive integer which one can express in 15
 * bits), and a remainder (x - 32767); the latter is calculated by and'ing out
 * the high bi-t (i.e. subtracting 32768 - which one too many, have to add one
 * back). It then calculates remainder(d0, 3) - which is the number of 8-hour
 * periods in the given date - and quotient(d0, 3) - the number of days - in
 * two parts, and then combines them.
 *
 * (Only d0 has this problem; since d1 is the remainder mod 28800, the number
 * of seconds in 8 hours, it can never overflow into negative numbers.)
 */

gmtime(tim)
int tim[];
{
	register int d0, d1;
	int d2;
	int d0e, d0r;
	register *tp;
	static xtime[9];
	extern int ldivr;

	/*
	 * break initial number into
	 * multiples of 8 hours.
	 * (28800 = 60*60*8)
	 */

	d0 = ldiv(tim[0], tim[1], 28800);
	d1 = ldivr;
	tp = &xtime[0];

	/* Check for (and handle) overflow into negative numbers */
	if (d0 < 0) {
		d0 = ((d0 & 077777) + 1);
		d0e = 32767;
		}
	  else
		d0e = 0;

	d0r = ((d0 % 3) + (d0e % 3));
	d0 = ((d0 / 3) + (d0e / 3));
	while (d0r >= 3) {
		d0r =- 3;
		d0++;
		}

	/*
	 * generate hours:minutes:seconds
	 */

	*tp++ = d1%60;
	d1 =/ 60;
	*tp++ = d1%60;
	d1 =/ 60;
	d1 =+ d0r*8;
	*tp++ = d1;

	/*
	 * d0 is the day number.
	 * generate day of the week.
	 */

	xtime[WDAY] = (d0+4)%7;

	/*
	 * year number
	 */

	for (d1=70; d0 >= (d2 = dysize(d1)); d1++)
		d0 =- d2;
	xtime[YEAR] = d1;
	xtime[YDAY] = d0;

	/*
	 * generate month
	 */

	if (dysize(d1)==366)
		dmsize[1] = 29;
	for(d1=0; d0 >= dmsize[d1]; d1++)
		d0 =- dmsize[d1];
	dmsize[1] = 28;
	*tp++ = d0+1;
	*tp++ = d1;
	xtime[ISDAY] = 0;

	return(xtime);
}

asctime(t)
int *t;
{
	register char *cp, *ncp;
	register int *tp;

	cp = cbuf;
	for (ncp = "Day Mon 00 00:00:00 1900\n"; *cp++ = *ncp++;);
	ncp = &"SunMonTueWedThuFriSat"[3*t[6]];
	cp = cbuf;
	*cp++ = *ncp++;
	*cp++ = *ncp++;
	*cp++ = *ncp++;
	cp++;
	tp = &t[4];
	ncp = &"JanFebMarAprMayJunJulAugSepOctNovDec"[(*tp)*3];
	*cp++ = *ncp++;
	*cp++ = *ncp++;
	*cp++ = *ncp++;
	cp = ct_numb(cp, *--tp);
	cp = ct_numb(cp, *--tp+100);
	cp = ct_numb(cp, *--tp+100);
	cp = ct_numb(cp, *--tp+100);
	cp = ct_year(cp, t[YEAR]);
	return(cbuf);
}

/* Leap year rule: there is a leap year every year whose number is perfectly
 * divisible by four - except for years which are both divisible by 100 and
 * not divisible by 400.
 *
 * This code a hack, and it will break in 2100, but since the Unix long
 * date/time will roll over in 2036 or so, who cares? :-)
 *
 * Plus to which, doing it this way means we can keep the calling sequence
 * (it is called with a 1900-based year number, e.g. 114 for 2014) the same.
 */

dysize(y)
{
	if((y%4) == 0)
		return(366);
	return(365);
}

ct_numb(acp, n)
{
	register char *cp;

	cp = acp;
	cp++;
	if (n>=10)
		*cp++ = (n/10)%10 + '0';
	else
		*cp++ = ' ';
	*cp++ = n%10 + '0';
	return(cp);
}

ct_year(acp, n)
{
	register char *cp;
	int	cent, dec, yr;

	n =+ 1900;
	yr = n%10;
	n =/ 10;
	dec = n%10;
	n =/ 10;
	cent = n%10;
	n =/ 10;
	
	cp = acp;
	cp++;
	*cp++ = n + '0';
	*cp++ = cent + '0';
	*cp++ = dec + '0';
	*cp++ = yr + '0';
	return(cp);
}
