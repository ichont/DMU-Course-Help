#include<stdio.h>
#include<stdlib.h>
int wc(char argv[]){
	FILE *fp;
	if((fp = fopen(argv,"r")) == NULL ){
	printf("Cannot Open The File!\n");
	return -1;
	}
	int line = 1;
	int word = 0;
	int character= 0;
	char c;
	printf("FileName:%s\n",argv);
	while(!feof(fp)){
        int tmp = 0;
        while ((c = getc(fp)) != EOF)
        {
            if (c == '\n')
            {
                line++;
            }

            if (c != '\n' && c != '\t' && c != ' ')
            {
                tmp = 1;
            }
            else if (tmp == 1)
            {
                word++;
                tmp = 0;
            }
            character++;
        }
        if(tmp==1){
            word++;
        }
	}
	fclose(fp);
	printf("WordNumber:%d\n",word);
    printf("lineNumber:%d\n",line);
    printf("CharacterNumber:%d\n",character);
return 0;
}
