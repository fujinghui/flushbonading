#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#ifdef DEBUG
	#define debug(fmt, ...) printf(fmt, #__VA_ARGS__)
#else
	#define debug(fmt, ...)
#endif
void display_font_ascii(char *asc){
	int i, j;
	for(i = 0; i < 16; i ++)
	{
		for(j = 0; j < 8; j ++)
		{
			if(asc[i] & (0x80 >> j))
			{
				printf("*");
			}
			else
			{
				printf(" ");
			}
		}
		printf("\n");
	}
}
int main(void){
	int i;
	FILE *asc;
	unsigned char asciicode[] = "ABb";
	unsigned char ascii[16];
	int offset = 0;
	if((asc == fopen("ASC16", "rgb")) == NULL)
	{
		perror("Can't Open ASC16");
		return -1;
	}
	return 0;
	for(i = 0; i < sizeof(asciicode) - 1; i ++)
	{
		offset = asciicode[i] * 16;
		fseek(asc, offset, SEEK_SET);
		fread(ascii, 16, 1, asc);
		display_font_ascii(ascii);
	}
	return 0;
}

