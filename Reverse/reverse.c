#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

typedef struct ListNode{
	struct ListNode* next;
	char* buf;
}ListNode;

// ListNode* reverse(ListNode* head) {
// 	ListNode* pre = NULL;
// 	while(head->next) {
// 		ListNode* next = head->next;
// 		head->next = pre;
// 		pre = head;
// 		head = next;
// 	}
// 	return head;
// }

int
main(int argc, char* argv[]) {
	if (argc > 3) {
		fprintf(stderr, "usage: reverse <input> <output>\n");
		exit(1);
	}
	// 链表的头，从文件中读取的信息
	ListNode* head = NULL;
	char* buf = NULL;
	size_t length = 0;
	size_t len = 0;
	// 第一种情况
	if (argc == 1) {
		while ((len = getline(&buf, &length, stdin)) != -1) {
			ListNode* temp = (ListNode*)malloc(sizeof(ListNode));
			temp->next = head;
			temp->buf = (char*)malloc(strlen(buf) + 1);
			strcpy(temp->buf,buf);
			head = temp;
			// free(buf);
		}
		// head = reverse(head);
		while (head) {
			fprintf(stdout, "%s", head->buf);
			ListNode* temp = head;
			head = head->next;
			free(temp);
		}
	} else if (argc == 2) {
		FILE* input = fopen(argv[1], "r");
		if (input == NULL) {
			fprintf(stderr, "reverse: cannot open file '%s'\n",argv[1]);
			exit(1);
		}
		while ((len = getline(&buf, &length, input)) != -1) {
			ListNode* temp = (ListNode*)malloc(sizeof(ListNode));
			temp->next = head;
			temp->buf = (char*)malloc(strlen(buf) + 1);
			strcpy(temp->buf,buf);
			head = temp;
			// free(buf);
		}
		// head = reverse(head);
		fclose(input);
		while (head) {
			fprintf(stdout, "%s", head->buf);
			ListNode* temp = head;
			head = head->next;
			free(temp);
		}
	}
	else if (argc == 3) {
		FILE* input = fopen(argv[1], "r");
		if (input == NULL) {
			fprintf(stderr, "reverse: cannot open file '%s'\n",argv[1]);
			exit(1);
		}
		FILE* output = fopen(argv[2], "w");
		if (output == NULL) {
			fprintf(stderr, "reverse: cannot open file '%s'\n",argv[2]);
			exit(1);
		}
		// 获取文件信息
		struct stat in, out;
		stat(argv[1], &in);
		stat(argv[2], &out);
		if (in.st_ino == out.st_ino && in.st_dev == out.st_dev) {
			fprintf(stderr, "reverse: input and output file must differ\n");
			exit(1);
		}

		while ((len = getline(&buf, &length, input)) != -1) {
			ListNode* temp = (ListNode*)malloc(sizeof(ListNode));
			temp->next = head;
			temp->buf = (char*)malloc(strlen(buf) + 1);
			strcpy(temp->buf,buf);
			head = temp;
			// free(buf);
		}
		fclose(input);
		while (head) {
			fprintf(output, "%s", head->buf);
			ListNode* temp = head;
			head = head->next;
			free(temp);
		}
		fclose(output);
	}
	free(buf);
	exit(0);
}