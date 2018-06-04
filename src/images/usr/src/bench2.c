main() 
{
  int a,b,c;
  b=1000;
  for(c=500;c<2500;c++)
  {
    for(a=500;a<1000;a++)
    {
    	if(b & 2)
    	{
    		b = (b + a) / 2;
    	}
    	else
    	{
    		b = (b+a+c) / 3;
    	}
    }
  }
    printf("RES: %d\n", b);
}
