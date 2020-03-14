#ifndef _LINE_H_
#define _LINE_H_

#include "boolean.h" //提供boolean
#include "userType.h" //提供 USER_TYPE

typedef struct Node {
	USER_TYPE data;
	struct Node *next;
}Node;

typedef struct LINK_LIST {
	Node *head;
	Node *tail;
	int count;
}List;

typedef boolean (*EQUAL)(USER_TYPE, USER_TYPE);


Node* CreatOneNode(USER_TYPE data);
void DestoryLink(List **plist);
boolean Insert(List *plist, USER_TYPE insertAt, USER_TYPE data);
boolean Remove(List *plist, USER_TYPE data);
boolean Add(List *plist, USER_TYPE data);
boolean InitList(List **plist);
int GetLinkCount(List *plist);


#endif
 