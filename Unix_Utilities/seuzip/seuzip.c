#include <stdio.h>
#include <stdlib.h>

int 
main(int argc, char* argv[]) {
	if (argc < 2) {
		fprintf(stdout, "seuzip: file1 [file2 ...]\n");
		exit(1);
	}
	char character[1] = {'0'}, intBuf[4];
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
				if (character[0] == '0') {
					character[0] = buf[j];
					num = 1;
				}
				else if (buf[j] != character[0]) {
					// 将int转换为字节流
					intBuf[0] = num & 0xff;
					intBuf[1] = (num >> 8) & 0xff;
					intBuf[2] = (num >> 16) & 0xff;
					intBuf[3] = (num >> 24) & 0xff;
					// 写入int和char
					fwrite(intBuf, sizeof(intBuf), 1, stdout);
					fwrite(character, sizeof(character), 1, stdout);
					character[0] = buf[j];
					num = 1;
				} else {
					++num;
				}
			}	
		}
		fclose(file);
	}
	intBuf[0] = num & 0xff;
	intBuf[1] = (num >> 8) & 0xff;
	intBuf[2] = (num >> 16) & 0xff;
	intBuf[3] = (num >> 24) & 0xff;
	fwrite(intBuf, sizeof(intBuf), 1, stdout);
	fwrite(character, sizeof(character), 1, stdout);
	exit(0);
}