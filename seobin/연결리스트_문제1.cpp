#include <stdio.h>
#include <string.h>
#pragma warning(disable:4996)
struct scheduled {
	char work[20];
	int year;
	int month;
	int day;
	struct scheduled* next;

};
void stringsort(struct scheduled*);
int main(void) {
	int num = 0;
	struct scheduled a[100];
	struct scheduled res;
	struct scheduled* sp;
	struct scheduled* tail = NULL;

	sp = a;
	sp->next = tail;
	scanf("%d", &num);

	for (int i = 0; i < num; i++) {
		scanf("%s %d %d %d", &(sp + i)->work, &(sp + i)->year, &(sp + i)->month, &(sp + i)->day);
		if ((sp + i)->year <= 0 || (sp + i)->month <= 0 || (sp + i)->month >= 13 || (sp + i)->day <= 0 || (sp + i)->day >= 32) {
			i--;
			continue;
		}
		else {
			if (i == num - 1) {
				(sp + i)->next = tail;
				break;
			}
			(sp + i)->next = sp + i + 1;
		}
	}
	/*printf("\n");
	for (int i = 0; i < num; i++) {
		printf("%s %d %d %d\n", (sp + i).work, ((sp+i)).year, (sp + i).month, (sp + i).day);
	}
	printf("\n");*/
	for (int j = num - 1; j > 0; j--) {
		for (int i = 0; i < j; i++) {
			if ((sp + i)->year > (sp + i + 1)->year) {
				/*(sp + i - 1)->next = sp + i + 1;
				(sp + i + 1)->next = sp + i;
				(sp + i)->next = sp + i + 2;*/
				res = a[i];
				a[i] = a[i + 1];
				a[i + 1] = res;

			}
			else if ((sp + i)->year == (sp + i + 1)->year) {
				if ((sp + i)->month > (sp + i + 1)->month) {
					/*(sp + i - 1)->next = sp + i + 1;
					(sp + i + 1)->next = sp + i;
					(sp + i)->next = sp + i + 2;*/
					res = a[i];
					a[i] = a[i + 1];
					a[i + 1] = res;
				}
				else if ((sp + i)->month == (sp + i + 1)->month) {
					if ((sp + i)->day > (sp + i + 1)->day) {
						/*(sp + i - 1)->next = sp + i + 1;
						(sp + i + 1)->next = sp + i;
						(sp + i)->next = sp + i + 2;*/
						res = a[i];
						a[i] = a[i + 1];
						a[i + 1] = res;
					}
					else if (((sp + i))->day == (sp + i + 1)->day) {
						stringsort(sp); 
					}
				}
			}
		}
	}

	printf("\n");
	for (int i = 0; i < num; i++) {
		printf("%s %d %d %d\n", (sp + i)->work, (sp + i)->year, (sp + i)->month, (sp + i)->day);
	}
	printf("\n");

	for (int i = 0; i < num; i++) {
		printf("%s\n", ((sp + i))->work);
	}
	return 0;
}

void stringsort(struct scheduled* p) {
	int n;
	struct scheduled res;
	for (int j = 0; j < 19; j++) {
		for (int i = 0; i < 19; i++) {
			n = strcmp((p + i)->work, (p + i + 1)->work);
			if (n > 0) {
				res = p[i];
				p[i] = p[i + 1];
				p[i + 1] = res;
			}
		}
	}
}
