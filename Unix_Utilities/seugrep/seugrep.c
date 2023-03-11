#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// int matching(char* a, char* b) {
// 	int len = strlen(a);
// 	if (len == 0) return 1;
// 	int* prefix = (int*)malloc(len);
// 	prefix[0] = 0;
// 	for (int i=1; i<len; ++i) {
// 		int j = prefix[i-1];
// 		while (a[i] != a[j]) j = prefix[j-1];
// 		if (a[i] == prefix[i-1]) ++j;
// 		prefix[i] = j;
// 	}
// 	int i=0, j=0;
// 	while (j < strlen(b)) {
// 		if (a[i] == a[j]) {
// 			++i; ++j;
// 		}
// 		else if (i == 0) {
// 			j++;
// 		}
// 		else {
// 			i = prefix[i-1];
// 		}
// 		if (i >= len) {
// 			free(prefix);
// 			return 1;
// 		}
// 	}
// 	free(prefix);
// 	return 0;
// }

int
main(int argc, char* argv[]) {
	if (argc == 1) {
		fprintf(stdout, "searchterm [file ...]\n");
		exit(1);
	}
	char* buf = NULL;
	size_t length = 0;
	if (argc == 2) {
		while(getline(&buf, &length, stdin) != -1) {
			if (strstr(buf, argv[1]) != NULL) {
					fprintf(stdout, "%s", buf);
				}
			}
	}
	if (argc >= 3) {
		for (int i=2; i<argc; ++i) {
			FILE* file = fopen(argv[i], "r");
			if (NULL == file) {
				fprintf(stdout, "cannot open file\n");
				exit(1);
			}
			while(getline(&buf, &length, file) != -1) {
				if (strstr(buf, argv[1]) != NULL) {
					fprintf(stdout, "%s", buf);
				}
			}
		}
	}
	free(buf);
	exit(0);
}