#ifndef _MY_LINE_
#define _MY_LINE_

#include<stdio.h>

#include "boolean.h" //提供boolean
#include "userType.h" //提供 USER_TYPE



#define NOT_FOUND NULL

typedef struct MY_LINK {
	USER_TYPE data;
	struct MY_LINK *next;
}link;

typedef struct LINK_LIST {
	link *head;
	link *tail;
	int count;
}list;

link* creatOneNode(void);
void freeLink(list *plist);
link* searchNode( link *phead, link *positnode);
static boolean foundNode( link *phead,link *data,link **leftnode,
		link **positnode,boolean (*eq)(link*,link*));
boolean insertNode( list *plist, link *node,link *positnode);
boolean removeNode(list *plist, link *positnode);
boolean append(list *plist, link *node);
boolean setLink(list *plist,int count);
#endif
 