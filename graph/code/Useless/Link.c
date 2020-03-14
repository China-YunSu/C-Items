#include <stdio.h>
#include <malloc.h>

#include "./include/Link.h"//�ṩ�ṹ��
#include "./include/boolean.h"//�ṩboolean
#include "./include/userType.h"

static boolean InsertNode(List *plist, Node *node,Node *seek) ;
static Node* CreatOneNode(USER_TYPE data);
static Node *SearchPreNoed(Node *phead, Node *node, EQUAL eq);
static Node *SearchCurNoed(Node *phead, Node *node, EQUAL eq);
static boolean RemoveNode(List *plist, Node *node);

static Node* CreatOneNode(USER_TYPE data) {
	Node *ptr = (Node *) calloc(sizeof(Node),1);
	ptr->data = data;
	ptr->next = NULL;

	return ptr;
}

boolean InitList(List **plist) {
	List *ptr = NULL;

	if (NULL == plist || NULL != *plist)  {
		printf("��ʼ��ʧ�ܣ�");
		return FALSE;
	}
	//���ʼ��
	ptr = (List *) calloc(sizeof(List), 1);
	ptr->head = NULL;
	ptr->tail = NULL;
	ptr->count = 0;

	*plist = ptr;

	return TRUE;
}

void DestoryLink(List **plist) {
	Node *pre = NULL;//ǰ���ڵ�
	Node *cur = NULL;//��ǰ�ڵ�

	if (NULL == plist) {
		printf("ɾ��ʧ�ܣ�\n");
		return;
	}

	cur = (*plist)->head;
	while (NULL != cur) {
		pre = cur;
		cur = cur->next;
		free(pre);
	}

	free(*plist);
	*plist = NULL;
}

static Node *SearchPreNoed(Node *phead, Node *node, EQUAL eq) {
	Node *pre = NULL;//ǰ���ڵ�ָ��

	//���ҵ�һ���ڵ�
	if (eq(phead->data, node->data)) {
		return pre;
	}
	//���Һ����ڵ�
	pre = phead;
	while (NULL != pre->next && 
		FALSE == eq(pre->next->data,node->data)) {
		pre = pre->next;
	}

	return pre;
}
 
static Node *SearchCurNoed(Node *phead, Node *node, EQUAL eq) {
	Node *cur = phead;

	while (NULL != cur && FALSE == eq(cur->data,node->data)) {
		cur = cur->next;
	}

	return cur;
}

boolean Insert(List *plist, USER_TYPE insertData, USER_TYPE data) {
	Node location;
	
	if(NULL == plist->head) { 
		printf("����ʧ�ܣ�");
		return FALSE;
	}

	location.data = insertData;
	return InsertNode(plist, CreatOneNode(data), &location);
}

static boolean InsertNode(List *plist, Node *node,Node *seek) {
	Node *pre = NULL;//��ǰ�ڵ�ָ��

	pre = SearchPreNoed(plist->head,seek, equal);
	if (NULL == pre) {//ͷ�ڵ������
		node->next = plist->head;
		plist->head = node;
	} 
	else if (NULL != pre->next) {
		node->next = pre->next;
		pre->next = node;
	} else {
		return FALSE;
	}
	++plist->count;	

	return TRUE;	
}
// //��ɾ��
boolean Remove(List *plist, USER_TYPE data) {
	Node del;

	if(NULL == plist) { 
		return FALSE;
	}
	del.data = data;
	return RemoveNode(plist, &del);
}

static boolean RemoveNode(List *plist, Node *node) {
	Node *pre = NULL;//ǰ���ڵ�ָ��
	Node *cur = NULL;//��ǰ�ڵ�ָ��

	pre = SearchPreNoed(plist->head, node, equal);

	if(NULL == pre) {//ɾ��ͷ�ڵ�
		cur = plist->head;
		plist->head = cur->next;
	} 
	else if (NULL != pre->next){
		cur = pre->next;
		pre->next = cur->next;	

		if (NULL == cur->next) { //����β�ڵ�
			plist->tail = pre;
		}
	}
	else {
		return FALSE;
	}

	free(cur);
	--plist->count;
	
	return TRUE;
}

boolean Add(List *plist, USER_TYPE data) {
	if (NULL == plist) {
		printf("׷��ʧ�ܣ�");
		return FALSE;	
	}
	//β����
	if (NULL == plist->head) {
		plist->head = plist->tail = CreatOneNode(data);
	}
	else {
		plist->tail->next = CreatOneNode(data);
		plist->tail = plist->tail->next;
	}
	++plist->count;
	
	return TRUE;
}

int GetLinkCount(List *plist) {
	if(NULL == plist) {
		return -1;
	}

	return plist->count;
}

