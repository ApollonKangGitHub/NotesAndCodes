#include "rc4.h"

void rc4_algorithm(unsigned char * data, unsigned char * key)
{
	unsigned char s[256] = {0};
	size_t len_data = strlen((const char *)data);
	size_t len_key = strlen((const char *)key);

	vector_init(s, key, len_key);
	encrypt(s, data, len_data);
}

void vector_init(unsigned char *s, unsigned char *key, size_t len)
{
	int i = 0, j = 0;
	unsigned char k[256] = {0};
	for(i = 0; i < 256; i++){
		s[i] = i;
		k[i] = key[i % len];
	}

	for(i = 0; i < 256; i++){
		j = (j + s[i] + k[i]) % 256;
		swap(&s[i],&s[j]);
	}
}
void encrypt(unsigned char *s, unsigned char *data, size_t len)
{
	size_t i = 0, j = 0, n = 0, t = 0;
	for(n = 0; n < len; n++){
		i = (i + 1) % 256;
		j = (j + s[i]) % 256;
		swap(&s[i], &s[j]);
		t = (s[i] + s[j]) % 256;

		data[n] ^= s[t];
	}
}

void swap(unsigned char * a, unsigned char * b)
{
	unsigned char temp;
	temp = *a;
	*a = *b;
	*b = temp;
}
