# include<stdio.h>
# include<string.h>
# include<stdlib.h>
# include<sys/socket.h>
# include<netdb.h>

void error_print(char * ptr)
{
	perror(ptr);
	exit(EXIT_FAILURE);
}

int getlocalip(char * ip)
{
	char host[100] = {0};
	if( (gethostname(host, sizeof(host))) < 0)
		return -1;

	struct hostent * hp;
	if((hp = gethostbyname(host)) == NULL)
		return -1;
	strcpy(ip, inet_ntoa(*(struct in_addr *)hp->h_addr));	

	return 0;
}
int main(void)
{
	char host[100] = {0};
	if( (gethostname(host, sizeof(host))) < 0)
		error_print("gethostname");

	struct hostent * hp;
	if((hp = gethostbyname(host)) == NULL)
		error_print("gethostbyname");

	int i = 0;
	while(hp->h_addr_list[i] != NULL){
		printf("%s\n",inet_ntoa(*(struct in_addr *)hp->h_addr_list[i]));
		i++;
	}
	char ip[16] = {0};
	getlocalip(ip);
	printf("%s\n",ip);
	
	return 0;
}
