#include <stdio.h>
#include <stdlib.h>

ssize_t mygetline(char ** lineptr, size_t *n, FILE *stream)
{
	ssize_t count = 0;
	int ch;
	*lineptr = (char *)malloc((*n + 2)*sizeof(char));
	while((ch = fgetc(stream)) != '\n' && ch != EOF){
		count++;
		if(count+1 >= *n){
			*n = *n + 10;
			*lineptr = realloc(*lineptr,(*n)*sizeof(char));
		}
		*(*lineptr + count - 1) = ch;
	}
	if(ch == EOF && count == 0)
		return -1;
	if(ch == '\n'){
		*(*lineptr+count) = '\n';
		*(*lineptr + count + 1) = '\0';
	}
	return count+1;
}

int main()
{
	 FILE * fp;
            char * line = NULL;
            size_t len = 0;
            ssize_t read;
            fp = fopen("a.txt", "r");
            if (fp == NULL)
                 exit(EXIT_FAILURE);
            while ((read = getline(&line, &len, fp)) != -1) {
                 printf("Retrieved line of length %u", read);
                 printf("%s", line);
		 printf("len: %d\n", len);
            }
            if (line)
                 free(line);
            return EXIT_SUCCESS;

}
