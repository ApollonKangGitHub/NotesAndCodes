// ConsoleApplication2.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#pragma warning(disable:4996)
//����4996����
//��������Ŀ->����->��������->C/C++->Ԥ������->Ԥ����������������һ����
//��_CRT_SECURE_NO_WARNINGS������

#define MAX_BUFFER_SIZE 1024
#define STRING_BUFFER 16

char strbuf[STRING_BUFFER] = { 0 };

int main(void)
{
	size_t num = 0, i = 0;

	FILE * fpr = fopen("F:\\new.dcm", "rb");//�Զ���������ȡ
	FILE * fpw = fopen("F:\\new.txt", "w");
	if (fpr == NULL || fpw == NULL){
		printf("open file failure at line:%d\n", __LINE__);
		exit(EXIT_FAILURE);
	}

	fseek(fpr, 0, SEEK_END);
	const size_t len_file = ftell(fpr);
	fseek(fpr, 0, SEEK_SET);

	printf("%d\n", len_file);

	fprintf(fpw, "%08X: ", num);
	while (num < len_file){
		unsigned char ch = fgetc(fpr);
		strbuf[num % STRING_BUFFER] = ch;
		fprintf(fpw, "%02X ", ch);
		num++;
		if (num % 16 == 0){
			fprintf(fpw, "; ");
			for (i = 0; i<STRING_BUFFER; i++){
				if (strbuf[i] > 31 && strbuf[i] < 127)
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