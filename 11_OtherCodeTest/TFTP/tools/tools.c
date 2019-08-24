#include <tools.h>
#include <tftpType.h>
#include <string.h>
#include <stdlib.h>

/* INT32整数value转十进制字符串str，并返回字符串首地址，如1235，转成"1235" */
EXTERN CHAR * uitoa(UINT32 value, CHAR * str)
{
	INT32 high = value;
	INT32 low = 0;
	INT32 i = 0, j = 0, temp = 0;

	if(!value){
		str[0] = '0';
		return str;
	}
	
	/* 余数对应的ASCII码依次存放在数组中 */
	while(high){
		low = high % 10;
		high = high / 10;
		str[i++] = low + '0';
	}
	--i;
	/* 反转，高低位调换字符串顺序 */
	while(i > j){
		temp = str[i];
		str[i--] = str[j];
		str[j++] = temp;
	}
	return str;
}

/* 十进制的字符串表示形式，转换为十进制数值，只支持无符号UINT3232 */
EXTERN UINT32 atoui(const CHAR * str)
{
	const CHAR *s = str;
	UINT32 value = 0;
	while(*s){
		if(*s < '0' || *s > '9'){
			return -1;
		}
		value = (value << 3) + (value << 1);	/* 即value = value x 10 */
		value += (*s - '0');
		//SOC_DEBUG_PRINT32(SOC_DBG_LOG, "value = %d\r\n", value);
		s++;
	}
	return value;
}

/* INT32整数value转十六进制字符串str，并返回字符串首地址，如1235，转成"0X000004D3" */
EXTERN CHAR * uitoxa(UINT32 value, CHAR * str)
{
	CHAR * s = str;
	CHAR base[] = "0123456789ABCDEF";
	INT32 high = value, low = 0;
	/* 32bit十六进制，0xFFFFFFFF，占10Byte， 倒序填充index从9开始 */
	INT32 i = 9; 

	while(high){
		low = high % 16;
		high = high / 16;
		s[i--] = base[low];
	}
	while(i > 1){
		s[i--] = '0';
	}
	s[1] = 'X';
	s[0] = '0';
	
	return str;
}

/* 清除字符串str中多余的空格，两个单词之间只有一个空格 */
EXTERN CHAR * clear_more_space(CHAR * str) 
{
	INT32 i = 0;
	INT32 j = 0;
	CHAR * target = NULL;
	INT32 len = 0;
	
	if (NULL == str) {
		return NULL;
	}
	
	len = strlen(str);
	target = malloc(len);
	memset(target, 0, len);

	while ((i < len) && (str[i] == 0x20)) {
		i++;
	}
	
	while(i < len) {
		if ((str[i] == 0x20) && (str[i+1] == 0x20)) {
			i++;
		}
		else {
			target[j++] = str[i++];
		}
	}

	memcpy(str, target, len);
	free(target);

	return str;
}
