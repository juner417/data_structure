#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "list.h"

// 일반적으로 실전에서는 구조체를 list로 연결하고 싶을때가 
// 대부분ㄴ입니다. 

struct People
{
	char name[32];
	int age;

	NODE link;
};

#define OFFSET_OF(TYPE, MEMBER) ((int)&(((TYPE*)0)->MEMBER))

void display(NODE** head)
{
	printf("[head]");
	NODE* cur = 0;

	for(cur = (*head)->next; cur != (*head); cur=cur->next)
	{
		// Peoplr구조체에서 link 멤버가 몇바이트 떨어져 있는지구함
		int offset = OFFSET_OF(People, link);
		People* p = (People*)((char*)cur - offset);
		printf("-> %s", p->name);
	}
}

int main()
{
	NODE* head = (NODE*)malloc(sizeof(NODE));
	init_list( &(head) );

	while(1)
	{
		printf("이름>> ");
		char s[32] = {0};
		scanf("%s", s);
		
		if (strcmp(s, "q") == 0) break;
	
		People* p = (People*)malloc(sizeof(People));
		
		strcpy(p->name, s);
		
		//list에 뒤에 추가합니다. 
		insert_back(&head, &(p->link));
	}
	display(&head);
}
