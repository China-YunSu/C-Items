#include <stdio.h>
#include <malloc.h>

#include "./include/myLink.h"//提供结构体
#include "./include/SIMS.h"//equal
#include "./include/boolean.h"//提供boolean

link* creatOneNode(void) {
	link *pst = (link*) calloc(sizeof(link),1);
	return pst;
}

boolean setLink(list *plist,int count) {

	int i;

	if(NULL != plist->head || count <= 0) {
		return FALSE;
	}

	for(i = 0; i < count; i++) {
		append(plist,creatOneNode());
	}

	return TRUE;
}

void freeLink(list *plist) {
	
	link *pst = NULL;
	link *next = NULL;

	if(NULL == plist->head) {
		return;
	}

	for(pst = plist->head; pst; pst = next) {
		next = pst ->next;
		free(pst);
	}
	plist->head = NULL;
	plist->tail = NULL;
	plist->count = 0;
}

static boolean foundNode( link *phead,link *data,link **leftnode,
		link **positnode,boolean (*eq)(link*,link*)) {
	
	if(NULL == phead) {
		return FALSE;
	}

	for(*positnode = phead; *positnode; *leftnode = *positnode,
								 *positnode = (*positnode)->next) {
		if(TRUE == eq(*positnode,data)) {
			return TRUE;
		}
	}
	return FALSE;
}

boolean insertNode( list *plist, link *node,link *found) {
	
	link *temp;
	link *positnode;

	if(NULL == plist->head || NULL == found || NULL == node) { 
		return FALSE;
	}

	positnode = searchNode(plist->head,found);
	if(NULL != positnode) {
		if(positnode == plist->head) {
			temp = plist->head->next;
			plist->head->next = node;
			node->next = temp;
		} else if(NULL == positnode->next) {
			positnode->next = node;
			plist->tail = node;

		} else {
			temp = positnode->next;
			positnode->next = node;
			node->next = temp;
		}
		++plist->count;	
		return TRUE;
	}
	return FALSE;
}

boolean removeNode( list *plist, link *node) {
	
	link *leftnode = NULL;
	link *positnode = NULL;

	if(NULL == node) {
		return FALSE;
	}
	if (FALSE == foundNode(plist->head,node,&leftnode,&positnode,equal)) {
		return FALSE;
	}

		if(positnode == plist->head) {
			plist->head = positnode->next;
			free(positnode);
		} else if(NULL == positnode->next) {
			leftnode->next = NULL;
			plist->tail = leftnode->next;
			free(positnode);
		} else {
			leftnode->next = positnode->next;
			free(positnode);
		}	
		--plist->count;
		return TRUE;
}

link* searchNode( link *phead, link *node) {
	link *leftnode = NULL;
	link *positnode = NULL;
	
	if(NULL == node) {
		return NOT_FOUND;
	}
	if(TRUE == foundNode(phead,node,&leftnode,&positnode,equal)) {
		return positnode;
	}

	return NOT_FOUND;
}

boolean append(list *plist, link *node) {
	if(NULL == node ) {
		return FALSE;
	}
	
	if(NULL == plist->head) {
		plist->head = node;
		plist->tail = plist->head;
		++plist->count;
		return TRUE;
	}
	if(NULL != plist->tail) {
		plist->tail->next = node;
		plist->tail= node;
		++plist->count;
		return TRUE;	
	}
	
	return FALSE; 
}
