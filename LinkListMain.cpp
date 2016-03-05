#include<stdio.h>
#include<malloc.h>

/*
�ļ����ƣ����Ա���ʽ�洢�ṹ�Ļ�������
ʱ�䣺2015-1-24 18:13
˵�������Ա���ʽ�洢�ṹ�Ļ������� 
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

/*����һ����ͷ��������*/
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
	LinkListNode*pnext,*p;/*���ָ��pnextָ�򼴽��ͷŵ���һ����㣬���ָ��pָ�򼴽��ͷŵĽ��*/
	p=(*list)->next;/*ָ��pָ���һ�����*/
	while(p)/*����δ��������βʱ*/ 
	{
		pnext=p->next;/*��ָ��pnext������һ�������ͷŵĽ��*/
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
		printf("\n��ǰ����Ϊ�գ��޷�����������!\n");
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
�������ƣ�LinkListGetElem(LinkList list,int pos,ElemType*e)
����������list-----ָ�������ָ��
		  pos------Ԫ��λ�ã���Χ 1<=pos<=LinkListLength(list)
		  e--------���ڷ��ػ�ȡ��Ԫ�ص�ָ�� 
����˵��������Ż�ȡ������ָ��λ�õ�Ԫ�ز���Ԫ�ص������򷵻� 
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
����˵����LinkListLocateElem(LinkList list,ElemType e)
����������list-----ָ�������ָ��
		  e--------ָ������������ֵ
����˵������ֵ���������е�һ�γ���ָ��ֵ�Ľ�㲢����㷵�� 
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
	if(!ret)/*����������������Ҳû���ҵ�*/
	{
		printf("\nû���ҵ�ָ���Ľ��!\n");		
		return NULL;	
	}
	printf("\n�ҵ���ָ����Ԫ�أ����������е�һ�γ��ֵ�λ��λ��%d��λ�ã�\n",pos);
	return ret;
}

/*
�������ƣ�LinkListInsert(LinkList *list,int pos,ElemType e)
����������list-----ָ�������ָ��
          pos-------�������λ�ã���Χ:1<=pos<=LinkListLength(list) 
		  e----------��������Ԫ�ص������� 
����˵�����������ָ��λ�ò����㣬ע��pos�ķ�Χ��1<=pos<=LinkListLength(list) 
*/
void LinkListInsert(LinkList *list,int pos,ElemType e)
{
	int i=0;
	LinkListNode*ret=(LinkList)(*list);
	
	for(i=0;(i<pos-1)&&(ret);i++)//1��������pos-1�����
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
�������ƣ�LinkListDelete(LinkList *list,int pos,ElemType*e)
����������list-----ָ�������ָ��
          pos-------��ɾ����λ�ã���Χ:1<=pos<=LinkListLength(list) 
		  e----------���ش�ɾ�����Ԫ�ص������� 
����˵������������ɾ��ָ��λ�õĽ�㣬�������������򷵻أ�ע��pos�ķ�Χ��1<=pos<=LinkListLength(list)
*/
void LinkListDelete(LinkList *list,int pos,ElemType*e)
{
	int i=0;
	LinkListNode*ret,*p;
	p=(LinkListNode*)(*list);
	for(i=0;((i<pos-1)&&(p->next!=NULL));i++)/*��������pos-1����㣬pָ��λ�ڵ�(pos-1)��λ�õĽ��*/
	{
		p=p->next;	
	}	
	if((!p)||(i>pos-1))
		return; 
	ret=p->next;/*ָ��retָ���ɾ��λ�ڵ�pos��λ�õĽ��*/
	p->next=ret->next;
	*e=ret->data;
	free(ret);
}

/*�����������������õĽ��*/

void LinkListTraverse(LinkList list)
{
	LinkListNode*p=list->next;
	if(!(LinkListLength(list)))
	{
		printf("\n��ǰ����Ϊ�գ�\n");
		return;	
	}
	while(p)
	{
		printf("%d ",p->data);
		p=p->next;	
	}
	printf("\n");
}

/*����ת*/
void LinkListReverse(LinkList list,LinkList *newLinkList)
{
	//LinkList *newLinkList;
	LinkListNode *ptarget,*pnext,*ptemp;
	int i=0;
	/*��ʼ��newLinkList*/
	(*newLinkList)=(LinkList)malloc(sizeof(LinkListNode));
	(*newLinkList)->data=list->data;
	(*newLinkList)->next=NULL;
	
	pnext=(LinkListNode*)list->next;/*ָ������list�е�һ�����*/
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
�������ƣ�LinkListCreate_Head(LinkList *list,int n)
����������list------ָ������������ָ��
		  n---------����ĳ��� 
����˵����ͷ��㴴��������ͷ��㷨������������˳��Ϊ���� 
*/
void LinkListCreate_Head(LinkList *list,int n)
{
	LinkListNode *p;
	(*list)=(LinkList)malloc(sizeof(LinkListNode)); 
	(*list)->next=NULL;
	int i=0;
	
	if(*list==NULL)
	{
		printf("\n�������ڣ���ʼ��δ�ɹ����޷���������!\n");	
	}
	else
	{
		printf("\n������%d������������\n",n);

		for(i=0;i<n;i++)
		{
			p=(LinkListNode*)malloc(sizeof(LinkListNode));
			p->next=NULL;			
			scanf("%d",&(p->data));
			p->next=(*list)->next;/*�ֽ������Ľ���nextָ����ָ��ͷ�����ָ�����һ��Ԫ��*/
			(*list)->next=p;		
		}	
	}	
}


/*
�������ƣ�LinkListCreate_Tail(LinkList *list,int n)
����������list------ָ������������ָ��
		  n---------����ĳ��� 
����˵����ͷβ��㴴��������β��㷨������������˳��Ϊ���� 
*/
void LinkListCreate_Tail(LinkList *list,int n)
{	
	LinkListNode *pre,*p;
	(*list)=(LinkList)malloc(sizeof(LinkListNode));
	(*list)->next=NULL;
	pre=(*list);
	int i=0;
		
	if(*list==NULL)/*�Ϸ��Լ��*/
	{
		printf("\n�������ڣ���ʼ�����ɹ����޷���������!\n");	
	}
	else
	{
		printf("\n������%d������������\n",n);
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

/*β��㷨��������*/
int main(int argc, char *argv[]) 
{
	LinkList L,M;
	int i=0;
	ElemType a,b;
	LinkListNode *c;
	
	LinkListInit(&L);
	printf("\n��ǰ����ĳ���Ϊ:%d\n",LinkListLength(L));
	
	
	printf("\nβ��㷨��������\n");
	LinkListCreate_Tail(&L,5);
	
	/*
	printf("\n\ͷ��㷨��������n");
	LinkListCreate_Head(&L,5); 
	*/
	printf("\n��ȡ������ָ��λ�õ�Ԫ��:\n");
	for(i=1;i<=LinkListLength(L);i++)
	{
		LinkListGetElem(L,i,&b);
		printf("%d ",b);	
	} 
	printf("\n��ֵ����Ԫ�ؽ�㣺\n");
	c=LinkListLocateElem(L,301);
	 
	LinkListInsert(&L,1,101);
	LinkListInsert(&L,2,102);
	LinkListInsert(&L,3,103);
	LinkListInsert(&L,4,104);
	printf("\n��ǰ����ĳ���Ϊ:%d\n",LinkListLength(L));
	LinkListTraverse(L);
	
	printf("\n��ֵ����Ԫ�ؽ�㣺\n");
	c=LinkListLocateElem(L,104);
	
	LinkListDelete(&L,2,&a);
	printf("\n��ɾ����Ԫ��Ϊ:%d\n",a);
	
	printf("\n��ǰ����ĳ���Ϊ:%d\n",LinkListLength(L));
	LinkListTraverse(L);

	printf("\n����ת����:\n");
	LinkListReverse(L,&M);
	printf("\n����M�����Ľ��Ϊ:\n");
	LinkListTraverse(M);	

	printf("\n��ǰ����ĳ���Ϊ:%d\n",LinkListLength(L));
	LinkListTraverse(L);
	
	printf("\n�������\n");
	LinkListClear(&L);	
	printf("\n��ǰ����ĳ���Ϊ:%d\n",LinkListLength(L));
	
	printf("\n��������\n");
	LinkListDestory(&L);

	return 0;
}
