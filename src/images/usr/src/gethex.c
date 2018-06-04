/*
 * gethex output
 *
 * create the specified file
 */

/* single-character decode */

int out;
char buffer[256];
char binbuf[24576];
int max_addr;
int addr,bytes;

main(argc, argv)
char **argv;
{
	int i;
	int j;
	char c;

	for(i=0;i<24576;i++)
		binbuf[i]=97;

	if (argc != 2)
	{
		printf("Usage: gethex outfile\n");
		exit(2);
	}

	out=creat(argv[1],0444);

	if (out < 0)
	{
		printf("Error: cannot write outfile\n");
		exit(2);
	}

	max_addr=0;

	printf("SEND NOW SRECORD FILE\n");

	do{
		j=read_line();
		if(j > 1)
		{
			if ((buffer[0]==83) && (buffer[1]==48))
			{
				bytes=get_hex(&buffer[2]);
				addr=16*get_hex(&buffer[4]);
				addr=addr+get_hex(&buffer[6]);
				for(i=0;i<bytes;i++)
				{
					if(addr < 24576)
					{
						if(max_addr < addr) max_addr=addr;
						binbuf[addr++]=get_hex(&buffer[8+2*i]);
					}
				}
			}
			if ((buffer[0]==83) && (buffer[1]==49))
			{
				bytes=get_hex(&buffer[2]);
				addr=16*get_hex(&buffer[6]);
				addr=addr+get_hex(&buffer[8]);
				for(i=0;i<bytes;i++)
				{
					if(addr < 24576)
					{
						if(max_addr < addr) max_addr=addr;
						binbuf[addr++]=get_hex(&buffer[10+2*i]);
					}
				}
			}
			if ((buffer[0]==83) && (buffer[1]==51))
			{
				bytes=get_hex(&buffer[2]);
				addr=16*get_hex(&buffer[8]);
				addr=addr+get_hex(&buffer[10]);
				for(i=0;i<bytes;i++)
				{
					if(addr < 24576)
					{
						if(max_addr < addr) max_addr=addr;
						binbuf[addr++]=get_hex(&buffer[12+2*i]);
					}
				}
			}

		}

	}while(j>1);

	if(max_addr > 0)
		write(out,binbuf,max_addr+1);
		
	return(0);
}

/* read a single line */
read_line()
{
	int i,j,ab;
	i=0;

	do
	{
		ab=0;
		j=read(0,&buffer[i],1);
		if(j != 1) ab=1;
		if(buffer[i] < 31) ab=1;
		if(j==1) i++;
	}while((ab== 0) && (i< 100));
	return(i);
}

/* read a single line */
get_hex(ptr)
char *ptr;
{
	int res;
	char c;

	res=(-1);

	c= *ptr;
	if((c > 47) && (c < 58)) res=16*(c-48);
	if((c > 64) && (c < 71)) res=16*(c-55);
	ptr++;

	c= *ptr;
	if((c > 47) && (c < 58)) res=res+(c-48);
	if((c > 64) && (c < 71)) res=res+(c-55);
	ptr++;

	return(res);
}

