#include "gb2312code.h"
#include <stdio.h>
#include <stdlib.h>

GB2312code::GB2312code()
{
    //AsciiToCodeCalc();
}
void GB2312code::AsciiToCodeCalc()
{
    FILE * fp = fopen("../GB2312/GB2312Tabel.txt","w");
    if(NULL == fp){
        printf("open file error!\n");
        exit(EXIT_FAILURE);
    }
    char ascii[3] = {0};
    unsigned int i, j, num = 0;
    for(i=0XA1; i<=0XFE; i++){
        num = 0;
        fprintf(fp,"Area Number:%u\tArea Coding:%02X\n", i-0XA0,i);
        for(j=0XA1; j<=0XFE; j++){
            ascii[0] = i;
            ascii[1] = j;
            num ++;
            fprintf(fp,"%s\t", ascii, j);
            if(num % 8 == 0)
                fprintf(fp,"\n");
        }
        fprintf(fp,"\n\n");
    }
    fclose(fp);
}

