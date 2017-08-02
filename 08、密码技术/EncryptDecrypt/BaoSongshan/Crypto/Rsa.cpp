#include"Rsa.h"
#include"Prime.h"


//�Զ��������������Կe��
void RandomE(Huge f,Huge &e)  
{
	int x,y,r;
	srand(time(0));
	while(1)
	{
		e=rand()%f;

		if(e>1)         
		{                
			y=e;
			x=f;      
			while(y!=1)
			{
				r=x%y; 
				x=y; 
				y=r;  
				if(y==1||y==0)    
					break;          
			}                   
			if(y==1)  
				break;   
		}
	}
}

// ����Ԫ�㷨
//����ŷ�������գ�n���͹�Կe��⹫Կd�����㣺��d��e��mod�գ�n��=1��
//��d��e�ĳ˻����Ԧգ�n������Ϊ1
Huge Inverses(Huge n, Huge e) 
{
    int x1, x2, x3, y1, y2, y3, t1, t2, t3, temp;
    x1=1;  x2=0;  x3=n;  y1=0;  y2=1;  y3=e;
    while(1)
	{
		if(y3==1)
		{
			if(y2>=0)   return y2;
			else   return (n+y2);
			break;
		}
		temp=x3/y3;
		t1=x1-temp*y1;
		t2=x2-temp*y2;
		t3=x3-temp*y3;
		x1=y1;  x2=y2;  x3=y3;
		y1=t1;  y2=t2;   y3=t3;
	}
}

//��ģ����
Huge ModExp(Huge a, Huge b, Huge n)
{
	Huge y = 1;
	while(b != 0)
	{
		if(b & 1)
			y = (y*a)%n;
		a = (a*a)%n;
		b = b>>1;
	}
	return y;
}

////////////////////////////////////////////

void Rsa()
{
	system("cls");
	printf("------ Rsa Crypt -----\n");
	int num;
	printf("������Ҫ����������λ��:>");
	scanf("%d",&num);
	Prime(num);

	Huge p,q;
	printf("��ѡ������p:>");
	scanf("%d",&p);
	printf("��ѡ������q:>");
	scanf("%d",&q);
	remove("prime.txt");
	///////////////////////////////////////
	RsaPK pk;
	RsaSK sk;
	PK(&pk,p,q);
	SK(&sk,pk.e,p,q);
	//////////////////////////////////////

	Huge ciphertext, plaintext;
	unsigned char ch;
	int select;
	while(1)
	{
		printf("[1] ����  [2] ����  [0] ����\n");
		printf("��ѡ��:>");
		scanf("%d",&select);
		if(select == 1)
		{
			FILE *fpin = fopen("./text/plaintext.txt","rb");
			FILE *fpout = fopen("./text/ciphertext.txt","wb");
			assert(fpin != NULL);
			fread(&ch,sizeof(char),1,fpin);
			while(!feof(fpin))
			{
				RsaEncrypt((Huge)ch,&ciphertext,&pk);
				fwrite(&ciphertext,sizeof(Huge),1,fpout);
				fread(&ch,sizeof(char),1,fpin);
			}
			fclose(fpin);
			fclose(fpout);
			printf("���ܽ���......\n");
		}
		else if(select == 2)
		{
			FILE *fpin = fopen("./text/ciphertext.txt","rb");
			FILE *fpout = fopen("./text/plaintext_1.txt","wb");
			assert(fpin != NULL);

			fread(&ciphertext,sizeof(Huge),1,fpin);
			while(!feof(fpin))
			{
				RsaDecrypt(ciphertext,&plaintext,&sk);
				fwrite(&plaintext,sizeof(char),1,fpout);
				fread(&ciphertext,sizeof(Huge),1,fpin);
			}
			
			fclose(fpin);
			fclose(fpout);
			printf("���ܽ���......\n");
		}
		else if(select == 0)
		{
			break;
		}
		else
		{
			printf("Error!\n");
		}
	}
}

void PK(RsaPK *pk, Huge p, Huge q)
{
	FILE *fp = fopen("./key/pk.txt","w");
	assert(fp != NULL);
	Huge n = p * q;
	Huge e;
	RandomE((p-1)*(q-1),e);

	pk->n = n;
	pk->e = e;
	fprintf(fp,"e=%d, n=%d",pk->e,pk->n);
	fclose(fp);
}
void SK(RsaSK *sk, Huge e, Huge p, Huge q)
{
	FILE *fp = fopen("./key/sk.txt","w");
	Huge n = p * q;
	Huge d = Inverses((p-1)*(q-1),e);
	sk->d = d;
	sk->n = n;
	fprintf(fp,"d=%d, n=%d",sk->d,sk->n);
	fclose(fp);
}

void RsaEncrypt(Huge plaintext, Huge *ciphertext, RsaPK *pk)
{
	//x = a^b%n;
	*ciphertext = ModExp(plaintext,pk->e,pk->n);
}
void RsaDecrypt(Huge ciphertext, Huge *plaintext, RsaSK *sk)
{
	*plaintext = ModExp(ciphertext,sk->d,sk->n);
}