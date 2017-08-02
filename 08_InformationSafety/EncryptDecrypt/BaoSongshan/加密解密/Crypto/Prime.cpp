#include"Prime.h"

//back = (a*b)%num      ( n <= 2^62)
lltype fMultiModular(const lltype &a, lltype b, const lltype &n)
{
    lltype back(0), temp(a % n);
    //b %= n;
    while ( b > 0 )
    {
        if ( b & 0x1 )
        {
            if ( (back = back + temp) > n )
				back -= n;
		}
        if ( (temp <<= 1) > n )
			temp -= n;
        b >>= 1;
    }
    return back;
}

lltype modular_exp(const lltype &a, lltype b, const lltype &n)
{
    lltype d(1), dTemp(a % n);//当前二进制位表示的是进制数值
    while ( b > 0 )
    {
        if ( b & 0x1 )
            d = fMultiModular(d, dTemp, n);//不直接 d*dTemp 是怕溢出
        dTemp = fMultiModular(dTemp, dTemp, n);
        b >>= 1;
    }
    return d;
}

bool fWitNess(const lltype &a, const lltype &n, char t, const lltype &u)
{
	//if n must not be prime return true, else return false
	lltype x, y;
	x = modular_exp(a, u, n);
	while ( t-- )
	{
		y = fMultiModular(x, x, n);
		if ( y == 1 && x != 1 && x != n-1 )
			return true; //must not
		x = y;
	}
	return y != 1;
}

//miller-rabin法测试素数, count 测试次数
bool miller_rabin(const lltype &n, int count) 
{
    if ( n == 1 )
        return false;
    if ( n == 2 )
		return true;
	if(n % 2 == 0)
		return false;

    lltype a, u;  
    char t(0); 
    for (u = n-1; !(u & 0x1); u>>=1)
		++t;
    for (int i = 1; i <= count; ++i)
    {
        a = rand() % (n-1) + 1;
        if ( fWitNess(a, n, t, u) )
			return false;
    }
    return true;
}

//////////////////////////////////////////////

bool TestPrime(UL value)
{
	return miller_rabin(value,MAX_COUNT);
}

void Prime(int num)
{
	FILE *fp = fopen("prime.txt","w");
	assert(fp != NULL);
	UL base = 1;
	UL top = 9;
	for(int i=0; i<num-1; ++i)
	{
		base = base * 10;  //100
		top = top * 10 + 9; //999
	}

	int k = 1;
	base++;
	while(base <= top)
	{
		if(TestPrime(base))
		{
			fprintf(fp,"%-5d: %-6d",k,base);
			if(k % 5 == 0)
				fprintf(fp,"\n");
			k++;
		}
		base += 2;
	}
	fclose(fp);
}