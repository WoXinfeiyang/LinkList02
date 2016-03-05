#include<stdio.h>
#include<malloc.h>

/*
文件名称：线性表链式存储结构的基本操作
时间：2015-1-24 18:13
说明：线性表链式存储结构的基本操作 
*/ 

#define Bool int
#define True (1)
#define False (0)
#define Error (-1)

typedef int ElemType;
typedef struct LinkListNode
{
	struct LinkListNode*next;
	ElemType data;
}LinkListNode,*LinkList;

/*创建一个带头结点的链表*/
Bool LinkListInit(LinkList *list)
{
	(*list)=(LinkList)malloc(sizeof(LinkListNode));
	if(!(*list))
	{
		return False;	
	} 

	(*list)->next=NULL;
	return True; 

}

void LinkListClear(LinkList*list)
{
	LinkListNode*pnext,*p;/*结点指针pnext指向即将释放的下一个结点，结点指针p指向即将释放的结点*/
	p=(*list)->next;/*指针p指向第一个结点*/
	while(p)/*当还未遍历到表尾时*/ 
	{
		pnext=p->next;/*用指针pnext记下下一个即将释放的结点*/
		free(p);
		p=pnext;	
	}
	(*list)->next=NULL;
} 

void LinkListDestory(LinkList *list)
{
	free(*list);
}

int LinkListLength(LinkList list)
{
	int length=0;
 
	if(!list)
	{
		printf("\n当前链表为空，无法计算链表长度!\n");
		return Error;	
	}
	
	LinkListNode*node=list->next;
	for(length=0;node!=NULL;length++)
	{
		node=node->next;	
	}
	return length;
}
/*
函数名称：LinkListGetElem(LinkList list,int pos,ElemType*e)
函数参数：list-----指向链表的指针
		  pos------元素位置，范围 1<=pos<=LinkListLength(list)
		  e--------用于返回获取到元素的指针 
函数说明：按序号获取链表中指定位置的元素并将元素的数据域返回 
*/
void LinkListGetElem(LinkList list,int pos,ElemType*e)
{
	LinkListNode *p=list->next;
	int i=0;
	for(i=0;(i<pos-1)&&(p);i++)
	{
		p=p->next;
	}
	if((!p)&&(i>pos-1))
	{
		return;	
	}
	*e=p->data;
}
/*
函数说明：LinkListLocateElem(LinkList list,ElemType e)
函数参数：list-----指向链表的指针
		  e--------指定结点数据域的值
函数说明：按值查找链表中第一次出现指定值的结点并将结点返回 
*/
LinkListNode *LinkListLocateElem(LinkList list,ElemType e)
{
	LinkListNode *ret=(LinkListNode*)list;
	int pos=0;
	while((ret)&&(ret->data!=e))
	{
		ret=ret->next;
		pos++;
	}
	if(!ret)/*当遍历完整个链表也没有找到*/
	{
		printf("\n没有找到指定的结点!\n");		
		return NULL;	
	}
	printf("\n找到了指定的元素，且在链表中第一次出现的位置位于%d的位置！\n",pos);
	return ret;
}

/*
函数名称：LinkListInsert(LinkList *list,int pos,ElemType e)
函数参数：list-----指向链表的指针
          pos-------待插入的位置，范围:1<=pos<=LinkListLength(list) 
		  e----------带插入结点元素的数据域 
函数说明：在链表的指定位置插入结点，注意pos的范围是1<=pos<=LinkListLength(list) 
*/
void LinkListInsert(LinkList *list,int pos,ElemType e)
{
	int i=0;
	LinkListNode*ret=(LinkList)(*list);
	
	for(i=0;(i<pos-1)&&(ret);i++)//1遍历到第pos-1个结点
	{
	 ret=ret->next;		
	}
	/*
	while(ret&&(i<pos-1))
	{
		ret=ret->next;
		i++;	
	}*/
	if((!ret)||(i>pos-1))
	{
		return;	
	}
	LinkListNode *node=(LinkListNode*)malloc(sizeof(LinkListNode));
	node->data=e;
	node->next=ret->next;
	ret->next=node;		
}

/*
函数名称：LinkListDelete(LinkList *list,int pos,ElemType*e)
函数参数：list-----指向链表的指针
          pos-------待删除的位置，范围:1<=pos<=LinkListLength(list) 
		  e----------返回待删除结点元素的数据域 
函数说明：在链表中删除指定位置的结点，并将结点的数据域返回，注意pos的范围是1<=pos<=LinkListLength(list)
*/
void LinkListDelete(LinkList *list,int pos,ElemType*e)
{
	int i=0;
	LinkListNode*ret,*p;
	p=(LinkListNode*)(*list);
	for(i=0;((i<pos-1)&&(p->next!=NULL));i++)/*遍历到第pos-1个结点，p指向位于第(pos-1)个位置的结点*/
	{
		p=p->next;	
	}	
	if((!p)||(i>pos-1))
		return; 
	ret=p->next;/*指针ret指向待删除位于第pos个位置的结点*/
	p->next=ret->next;
	*e=ret->data;
	free(ret);
}

/*遍历访问链表中所用的结点*/

void LinkListTraverse(LinkList list)
{
	LinkListNode*p=list->next;
	if(!(LinkListLength(list)))
	{
		printf("\n当前链表为空！\n");
		return;	
	}
	while(p)
	{
		printf("%d ",p->data);
		p=p->next;	
	}
	printf("\n");
}

/*链表反转*/
void LinkListReverse(LinkList list,LinkList *newLinkList)
{
	//LinkList *newLinkList;
	LinkListNode *ptarget,*pnext,*ptemp;
	int i=0;
	/*初始化newLinkList*/
	(*newLinkList)=(LinkList)malloc(sizeof(LinkListNode));
	(*newLinkList)->data=list->data;
	(*newLinkList)->next=NULL;
	
	pnext=(LinkListNode*)list->next;/*指向链表list中第一个结点*/
	/*
	while(list->next)
	{
		p=(*newLinkList)->next;
		(*newLinkList)->next=list->next;
		list->next=list->next->next;
		(*newLinkList)->next->next=p;	
	}
	*/
	
	while(pnext)
	{
		ptemp=(*newLinkList)->next; 		
		ptarget=pnext;
		(*newLinkList)->next=ptarget;
		pnext=pnext->next;
		(*newLinkList)->next->next=ptemp;		
	}
	
	//for(i=0;i<LinkListLength(list);i++)
	/*
	while(pnext)
	{
		ptarget=(LinkListNode*)malloc(sizeof(LinkListNode));
		ptarget->next=(*newLinkList)->next; 
		
		ptarget=pnext;
		
		//ptarget->next=(*newLinkList)->next;
		//(*newLinkList)->next=ptarget;
		(*newLinkList)->next=ptarget;
	
		printf("%d**",ptarget->data);
		pnext=pnext->next;
		
	}*/
	//(*newLinkList)->next=NULL;
}
 
/*
函数名称：LinkListCreate_Head(LinkList *list,int n)
函数参数：list------指向待创建链表的指针
		  n---------链表的长度 
函数说明：头结点创建链表，用头结点法创建的链表结点顺序为逆序 
*/
void LinkListCreate_Head(LinkList *list,int n)
{
	LinkListNode *p;
	(*list)=(LinkList)malloc(sizeof(LinkListNode)); 
	(*list)->next=NULL;
	int i=0;
	
	if(*list==NULL)
	{
		printf("\n链表不存在，初始化未成功，无法创建链表!\n");	
	}
	else
	{
		printf("\n请输入%d个结点的数据域：\n",n);

		for(i=0;i<n;i++)
		{
			p=(LinkListNode*)malloc(sizeof(LinkListNode));
			p->next=NULL;			
			scanf("%d",&(p->data));
			p->next=(*list)->next;/*现将创建的结点的next指针域指向头结点所指向的下一个元素*/
			(*list)->next=p;		
		}	
	}	
}


/*
函数名称：LinkListCreate_Tail(LinkList *list,int n)
函数参数：list------指向待创建链表的指针
		  n---------链表的长度 
函数说明：头尾结点创建链表，用尾结点法创建的链表结点顺序为逆序 
*/
void LinkListCreate_Tail(LinkList *list,int n)
{	
	LinkListNode *pre,*p;
	(*list)=(LinkList)malloc(sizeof(LinkListNode));
	(*list)->next=NULL;
	pre=(*list);
	int i=0;
		
	if(*list==NULL)/*合法性检查*/
	{
		printf("\n链表不存在，初始化不成功，无法创建链表!\n");	
	}
	else
	{
		printf("\n请输入%d个结点的数据域；\n",n);
		for(i=0;i<n;i++)
		{
			p=(LinkListNode*)malloc(sizeof(LinkListNode));
			scanf("%d",&(p->data));
			pre->next=p;
			pre=p;	
		}	
		pre->next=NULL;
	}	
}

/*尾结点法创建链表*/
int main(int argc, char *argv[]) 
{
	LinkList L,M;
	int i=0;
	ElemType a,b;
	LinkListNode *c;
	
	LinkListInit(&L);
	printf("\n当前链表的长度为:%d\n",LinkListLength(L));
	
	
	printf("\n尾结点法创建链表：\n");
	LinkListCreate_Tail(&L,5);
	
	/*
	printf("\n\头结点法创建链表：n");
	LinkListCreate_Head(&L,5); 
	*/
	printf("\n获取链表中指定位置的元素:\n");
	for(i=1;i<=LinkListLength(L);i++)
	{
		LinkListGetElem(L,i,&b);
		printf("%d ",b);	
	} 
	printf("\n按值查找元素结点：\n");
	c=LinkListLocateElem(L,301);
	 
	LinkListInsert(&L,1,101);
	LinkListInsert(&L,2,102);
	LinkListInsert(&L,3,103);
	LinkListInsert(&L,4,104);
	printf("\n当前链表的长度为:%d\n",LinkListLength(L));
	LinkListTraverse(L);
	
	printf("\n按值查找元素结点：\n");
	c=LinkListLocateElem(L,104);
	
	LinkListDelete(&L,2,&a);
	printf("\n被删除的元素为:%d\n",a);
	
	printf("\n当前链表的长度为:%d\n",LinkListLength(L));
	LinkListTraverse(L);

	printf("\n链表反转测试:\n");
	LinkListReverse(L,&M);
	printf("\n链表M遍历的结果为:\n");
	LinkListTraverse(M);	

	printf("\n当前链表的长度为:%d\n",LinkListLength(L));
	LinkListTraverse(L);
	
	printf("\n清除链表：\n");
	LinkListClear(&L);	
	printf("\n当前链表的长度为:%d\n",LinkListLength(L));
	
	printf("\n销毁链表！\n");
	LinkListDestory(&L);

	return 0;
}
