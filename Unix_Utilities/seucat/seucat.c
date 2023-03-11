#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char* argv[]) {
	if (argc == 1) {
		exit(0);
	}
	int i;
	for (i=1; i<argc; ++i) {
		FILE* file = fopen(argv[i], "r");
		if (NULL == file) {
			fprintf(stdout, "cannot open file\n");
			exit(1);
		}
		char buf[255];
		while (fgets(buf, 255, file) != NULL) {
			fprintf(stdout, "%s", buf);
		}
	}
	exit(0);
}