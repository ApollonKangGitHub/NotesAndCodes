/*
 *����������a^3 = b^3 + c^3 + d^3
 *����N(N<=100)�����������Ԫ�飨a,b,c,d��������������Ҫ��
 *����a\b\c\d������1(����¼����)��С�ڵ���N����b<=c<=d
*/

#include <stdio.h>
int main(void)
{
	int a, b, c, d, num;
	int a_cube, b_cube, c_cube, d_cube;
	printf("please input num(1<num<=100):");
	scanf("%d",&num);

	for(a=2; a<=num; a++){
		a_cube = a*a*a;
		for(b=2; b<=num; b++){
			b_cube = b*b*b;
			for(c=b; c<=num; c++){//c>=b
				c_cube = c*c*c;
				for(d=c; d<=num; d++){//d>=c
					d_cube = d*d*d;
					if(a_cube == b_cube + c_cube + d_cube){
						printf("Cube = %d,",a);
						printf("Triple = (%d,%d,%d)\n",b,c,d);
					}
				}
			}
		}
	}

	return 0;
}