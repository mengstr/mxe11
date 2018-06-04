
struct	Record{
	struct Record	*PtrComp;
	int		Discr;
	int		Enc;
	int		Inc;
	char		Snc[31];
};

main()
{
	Proc0();
	exit(0);
}

/*
 * Package 1
 */
int		IntGl;
int		BoolGl;
char		C1Gl;
char		Char2Gl;
int		A1Gl[51];
int		A2Gl[51][51];
Record		*Pgl;
Record		*PglNext;

Proc0()
{
	int		IntLoc1;
	int		IntLoc2;
	int		IntLoc3;
	char		CharLoc;
	char		CharIndex;
	int	 	EnumLoc;
	char		String1Loc[31];
	char		String2Loc[31];
	extern char		*malloc();

	register 	i;


	PglNext = (*Record) malloc(sizeof(Record));
	Pgl = (*Record) malloc(sizeof(Record));
	Pgl->PtrComp = PglNext;
	Pgl->Discr = 1;
	Pgl->Enc = 3;
	Pgl->Inc = 40;
	strcpy(Pgl->Snc, "DHRYSTONE PROGRAM, SOME STRING");
	strcpy(String1Loc, "DHRYSTONE PROGRAM, 1'ST STRING");	/*GOOF*/
	A2Gl[8][7] = 10;	/* Was missing in published program */

/*****************
-- Start Timer --
*****************/
	for (i = 0; i < 5000; ++i)
	{

		Proc5();
		Proc4();
		IntLoc1 = 2;
		IntLoc2 = 3;
		strcpy(String2Loc, "DHRYSTONE PROGRAM, 2'ND STRING");
		EnumLoc = 2;
		BoolGl = ! Func2(String1Loc, String2Loc);
		while (IntLoc1 < IntLoc2)
		{
			IntLoc3 = 5 * IntLoc1 - IntLoc2;
			Proc7(IntLoc1, IntLoc2, &IntLoc3);
			++IntLoc1;
		}
		Proc8(A1Gl, A2Gl, IntLoc1, IntLoc3);
		Proc1(Pgl);
		for (CharIndex = 'A'; CharIndex <= Char2Gl; ++CharIndex)
			if (EnumLoc == Func1(CharIndex, 'C'))
				Proc6(1, &EnumLoc);
		IntLoc3 = IntLoc2 * IntLoc1;
		IntLoc2 = IntLoc3 / IntLoc1;
		IntLoc2 = 7 * (IntLoc3 - IntLoc2) - IntLoc1;
		Proc2(&IntLoc1);
	}

/*****************
-- Stop Timer --
*****************/
}

Proc1(PtrParIn)
*Record	PtrParIn;
{
	memcpy(((PtrParIn->PtrComp)), Pgl, sizeof (*(PtrParIn->PtrComp)));
	PtrParIn->Inc = 5;
	(*(PtrParIn->PtrComp)).Inc = PtrParIn->Inc;
	(*(PtrParIn->PtrComp)).PtrComp = PtrParIn->PtrComp;
	Proc3((*(PtrParIn->PtrComp)).PtrComp);
	if ((*(PtrParIn->PtrComp)).Discr == 1)
	{
		(*(PtrParIn->PtrComp)).Inc = 6;
		Proc6(PtrParIn->Enc, &(*(PtrParIn->PtrComp)).Enc);
		(*(PtrParIn->PtrComp)).PtrComp = Pgl->PtrComp;
		Proc7((*(PtrParIn->PtrComp)).Inc, 10, &(*(PtrParIn->PtrComp)).Inc);
	}
	else
		memcpy(PtrParIn, ((PtrParIn->PtrComp)), sizeof(*PtrParIn));
}

Proc2(IpIO)
int	*IpIO;
{
	int		IntLoc;
	int		EnumLoc;

	IntLoc = *IpIO + 10;
	for(;;)
	{
		if (C1Gl == 'A')
		{
			--IntLoc;
			*IpIO = IntLoc - IntGl;
			EnumLoc = 1;
		}
		if (EnumLoc == 1)
			break;
	}
}

Proc3(PtrParOut)
Record	*PtrParOut;
{
	if (Pgl != 0)
		*PtrParOut = Pgl->PtrComp;
	else
		IntGl = 100;
	Proc7(10, IntGl, &Pgl->Inc);
}

Proc4()
{
	int	BoolLoc;

	BoolLoc = C1Gl == 'A';
	BoolLoc =| BoolGl;
	Char2Gl = 'B';
}

Proc5()
{
	C1Gl = 'A';
	BoolGl = 0;
}


extern int Func3();

Proc6(EnumParIn, EnumParOut)
int	EnumParIn;
int	*EnumParOut;
{
	*EnumParOut = EnumParIn;
	if (! Func3(EnumParIn) )
		*EnumParOut = 4;
	switch (EnumParIn)
	{
	case 1:	*EnumParOut = 1; break;
	case 2:	if (IntGl > 100) *EnumParOut = 1;
			else *EnumParOut = 4;
			break;
	case 3:	*EnumParOut = 2; break;
	case 4:	break;
	case 5:	*EnumParOut = 3;
	}
}

Proc7(IpI1, IpI2, IpOut)
int	IpI1;
int	IpI2;
int	*IpOut;
{
	int	IntLoc;

	IntLoc = IpI1 + 2;
	*IpOut = IpI2 + IntLoc;
}

Proc8(A1Par, A2Par, IpI1, IpI2)
int	A1Par[51];
int	A2Par[51][51];
int	IpI1;
int	IpI2;
{
	int	IntLoc;
	int	IntIndex;

	IntLoc = IpI1 + 5;
	A1Par[IntLoc] = IpI2;
	A1Par[IntLoc+1] = A1Par[IntLoc];
	A1Par[IntLoc+30] = IntLoc;
	for (IntIndex = IntLoc; IntIndex <= (IntLoc+1); ++IntIndex)
		A2Par[IntLoc][IntIndex] = IntLoc;
	++A2Par[IntLoc][IntLoc-1];
	A2Par[IntLoc+20][IntLoc] = A1Par[IntLoc];
	IntGl = 5;
}

int Func1(Cpar1, Cpar2)
char	Cpar1;
char	Cpar2;
{
	char	Cloc1;
	char	Cloc2;

	Cloc1 = Cpar1;
	Cloc2 = Cloc1;
	if (Cloc2 != Cpar2)
		return (1);
	else
		return (2);
}

int Func2(StrParI1, StrParI2)
char	StrParI1[31];
char	StrParI2[31];
{
	int	IntLoc;
	char	Cloc;

	IntLoc = 1;
	while (IntLoc <= 1)
		if (Func1(StrParI1[IntLoc], StrParI2[IntLoc+1]) == 1)
		{
			Cloc = 'A';
			++IntLoc;
		}
	if (Cloc >= 'W' && Cloc <= 'Z')
		IntLoc = 7;
	if (Cloc == 'X')
		return(1);
	else
	{
		if (strcmp(StrParI1, StrParI2) > 0)
		{
			IntLoc =+ 7;
			return (1);
		}
		else
			return (0);
	}
}

int Func3(Epi)
int	Epi;
{
	int	ELoc;

	ELoc = Epi;
	if (ELoc == 3) return (1);
	return (0);
}

