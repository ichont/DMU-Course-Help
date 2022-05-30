#include <stdio.h>
int cat( char * argv){
	FILE *fp = fopen(argv,"r");
	int read_ret;
	while(!feof(fp)){
		read_ret = fgetc(fp);
		fputc(read_ret,stdout);
	}
	return 0;
}
