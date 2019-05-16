#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#define MAX_BUFFER_SIZE 1024
#define STRING_BUFFER 16

char strbuf[STRING_BUFFER] = {0};

int main(void)
{
    size_t num = 0, i = 0;

    FILE * fpr = fopen("F:\\new.dcm", "rb");//以二进制流读取
    FILE * fpw = fopen("F:\\new.hex", "w");
    if(fpr == NULL || fpw == NULL){
        printf("open file failure at line:%d\n", __LINE__);
        exit(EXIT_FAILURE);
    }

    fprintf(fpw, "%08X: ", num);
    while(!feof(fpr)){
        unsigned char ch = fgetc(fpr);
        strbuf[num % STRING_BUFFER] = ch;
        fprintf(fpw, "%02X ", ch);
        num++;
        if(num % 16 == 0){
            fprintf(fpw, "; ");
            for(i = 0; i<STRING_BUFFER; i++){
                if(strbuf[i] > 31 && strbuf[i] < 127)
                    fprintf(fpw, "%c", strbuf[i]);
                else
                    fprintf(fpw, ".");
            }
            fprintf(fpw, "\n%08X: ", num);
            memset(strbuf, 0, STRING_BUFFER);
        }
    }

    fclose(fpr);
    fclose(fpw);

    printf("Complete!\n");
    return 0;
}

#if 0
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#define MAX_BUFFER_SIZE 1024
#define STRING_BUFFER 16

char strbuf[STRING_BUFFER] = {0};

int main(void)
{
    size_t num = 0, i = 0;

    FILE * fpr = fopen("F:\\new.dcm", "r");//以非二进制流读取
    FILE * fpw = fopen("F:\\new.hex", "w");
    if(fpr == NULL || fpw == NULL){
        printf("open file failure at line:%d\n", __LINE__);
        exit(EXIT_FAILURE);
    }

    fseek(fpr, 0, SEEK_END);
    const size_t len_file = ftell(fpr);
    fseek(fpr, 0, SEEK_SET);

    printf("%d\n", len_file);

    fprintf(fpw, "%08X: ", num);
    while(num < len_file){
        unsigned char ch = fgetc(fpr);
        if((unsigned char)ch == 0XFF){
            strbuf[num % STRING_BUFFER] = 0X1A;
            fprintf(fpw, "1A ");
            fseek(fpr, num+1, SEEK_SET);
            //不能用fseek(fpr, 1, SEEK_CUR);或fseek(fpr, ftell(fpr)+1, SEEK_SET);
            //因为如果是遇到结束符EOF或0X1A时，ftell()的值即SEEK_CUR会变成4096的倍数
        }
        else{
            strbuf[num % STRING_BUFFER] = ch;
            fprintf(fpw, "%02X ", ch);
        }
        num++;
        if(num % 16 == 0){
            fprintf(fpw, "; ");
            for(i = 0; i<STRING_BUFFER; i++){
                if(strbuf[i] > 31 && strbuf[i] < 127)
                    fprintf(fpw, "%c", strbuf[i]);
                else
                    fprintf(fpw, ".");
            }
            fprintf(fpw, "\n%08X: ", num);
            memset(strbuf, 0, STRING_BUFFER);
        }
    }

    fclose(fpr);
    fclose(fpw);

    printf("Complete!\n");
    return 0;
}
#endif
