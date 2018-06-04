#define	OLOOP	100

int	tickflg 0;
int	oloop OLOOP;


/* Hacky mips a la MIT V6+ Unix 'mips' (the source for which I cannot
 * find anywhere).
 * Inner object = 1000 instructions.
 * Loop is OLOOP*1000 --> OLOOP million instructions.
 */ 

int	main(argc, argv)
	int	argc;
	char	*argv[];

{	char		*arg;
	int		i, j;
	register	int k;
	int		extime;
	int		sttime[2], endtime[2];


	argv++;

	for (argc--; (argc > 0); argc--) {
		arg = *argv;
		if (*arg++ != '-')
			break;

		argv++;
		
		switch (*arg) {

		  case 'o':	oloop = atoi(*argv++);
				argc--;
				break;

		  case 't':	tickflg++;
				break;

		  default:	printf("Bad flag: %c", *arg);
				exit(1);
		  }
		}


	time(&sttime[0]);

	k = 0;
	for (i = 0; (i < oloop); i++) {
		for (j = 0; (j < 1000); j++) {
			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;
			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;
			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;
			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;
			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;
			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;
			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;
			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;
			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;
			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;

			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;
			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;
			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;
			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;
			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;
			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;
			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;
			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;
			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;
			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;

			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;
			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;
			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;
			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;
			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;
			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;
			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;
			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;
			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;
			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;

			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;
			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;
			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;
			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;
			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;
			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;
			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;
			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;
			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;
			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;

			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;
			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;
			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;
			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;
			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;
			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;
			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;
			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;
			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;
			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;

			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;
			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;
			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;
			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;
			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;
			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;
			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;
			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;
			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;
			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;

			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;
			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;
			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;
			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;
			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;
			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;
			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;
			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;
			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;
			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;

			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;
			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;
			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;
			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;
			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;
			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;
			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;
			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;
			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;
			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;

			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;
			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;
			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;
			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;
			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;
			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;
			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;
			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;
			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;
			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;

			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;
			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;
			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;
			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;
			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;
			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;
			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;
			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;
			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;
			k++; k++; k++; k++; k++; k++; k++; k++; k++; k++;
			}

		if (tickflg == 0)
			continue;

		printf("#");
		if ((i != 0) && ((i % 50) == 0))
			printf("\n");
		}

	time(&endtime[0]);
	extime = (endtime[1] - sttime[1]);

	if (tickflg != 0) printf("\n");
	printf("\nmips x 10: %d\n", ((oloop *10) / extime));
}
