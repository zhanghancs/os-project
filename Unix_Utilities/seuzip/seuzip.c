#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int 
main(int argc, char* argv[]) {
	if (argc < 2) {
		fprintf(stdout, "seuzip: file1 [file2 ...]\n");
		exit(1);
	}
	char character = '0', writeBuf[5];
	int num = 0;
	for (int i=1; i<argc; ++i) {
		FILE* file = fopen(argv[i], "r");
		if (NULL == file) {
			fprintf(stderr, "zip: cannot open file %s\n", argv[i]);
			exit(1);
		}
		char* buf = NULL;
		size_t length = 0, len = 0;
		while ((len = getline(&buf, &length, file)) != -1) {
			for (int j=0; j<len; ++j) {
				if (character == '0') {
					character = buf[j];
					num = 1;
				}
				else if (buf[j] != character) {
					// 将int转换为字节流
					memcpy(writeBuf, &num, 4);
					writeBuf[4] = character;
					// 写入int和char
					fwrite(writeBuf, sizeof(writeBuf), 1, stdout);
					// fwrite(character, sizeof(character), 1, stdout);
					character = buf[j];
					num = 1;
				} else {
					++num;
				}
			}	
		}
		fclose(file);
	}
	memcpy(writeBuf, &num, 4);
  writeBuf[4] = character;
	fwrite(writeBuf, sizeof(writeBuf), 1, stdout);
	exit(0);
}