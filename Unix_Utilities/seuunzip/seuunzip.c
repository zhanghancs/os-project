#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int 
main(int argc, char* argv[]) {
	if (argc < 2) {
		fprintf(stdout, "seuunzip: file1 [file2 ...]\n");
		exit(1);
	}
	char buf[5];
	int num = 0;
	char character;
	for (int i=1; i<argc; ++i) {
		FILE* file = fopen(argv[i], "r");
		if (NULL == file) {
			fprintf(stderr, "unzip: cannot open file '%s'\n", argv[i]);
			exit(1);
		}
		while (fread(buf,sizeof(buf),1,file) == 1) {
			character = buf[4];
			memcpy(&num, buf, 4);
			char* fileBuf = (char*)malloc(num+1);
			for (int i=0; i<num; ++i) {
				fileBuf[i] = character;
			}
			fileBuf[num] = '\0';
			printf("%s", fileBuf);
			//fwrite(character, sizeof(character), num, stdout);
		}
		fclose(file);
	}
	exit(0);
}