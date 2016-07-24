
//
//  main.c
//  8.6
//
//  Created by zph on 16/3/18.
//  Copyright © 2016年 zph. All rights reserved.
//
#include "stdafx.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

typedef struct Node{    /* 定义单链表结点类型 */
	int data[2];
	int L;
	int R;
	struct Node *next;
} Node;

int * ReadDate(char filename[])
{
	int i = 0;
	int r[20000];
	FILE *fp;
	int result = 0;
	char StrLine[8];             //每行最大读取的字符数
	errno_t err;
	err = fopen_s(&fp, filename, "r");
	if (err != 0) //判断文件是否存在及可读
	{
		printf("error!");
		return NULL;
	}
	while (!feof(fp))
	{
		fgets(StrLine, 6, fp);  //读取一行
		//printf("%s", StrLine);
		result = atoi(StrLine);
		if (result != 0)
		{
			r[i] = result;
			i++;
		}

	}
	fclose(fp);
	//关闭文件
	printf("success\n");
	return r;
}

int max(int a, int b)
{
	return a>b ? a : b;
}
//搜索链表
int Li = 0;
int Ri = 0;
int FindItem(Node *p, int num)
{
	int i = 0;
	if (p->L < num)
	{
		i = 1;
		Li = p->L;
		Ri = p->R;
		return i;
	}
	else
	{
		for (i = 1; p->next != NULL; i++)
		{

			p = p->next;
			if (p->L < num)
			{
				Li = p->L;
				Ri = p->R;
				return i + 1;
			}

			else
				return 0;
		}

	}
	return 0;
}
//打印链表
void PrintList(Node *p)/*出以head为头的链表各节点的值*/
{
	Node *temp;
	temp = p;/*取得链表的头指针*/
	while (temp != NULL)/*只要是非空表*/
	{
		printf("范围是%d-%d\n", temp->data[0] + 1, temp->data[1]);/*输出链表节点的值*/
		printf("子序列和为：%d\n", temp->R - temp->L);
		temp = temp->next;/*跟踪链表增长*/
	}

}
//清空链表
void ClearList(Node *phead)
{
	Node *pNext; //定义一个与pHead相邻节点


	if (phead == NULL)
	{
		//printf("clearList函数执行，链表为空\n");
		return;
	}
	while (phead->next != NULL)
	{
		pNext = phead->next;//保存下一结点的指针
		free(phead);
		phead = pNext;      //表头下移
	}
	//printf("clearList函数执行，链表已经清除\n");
}
//重构链表
Node *ReCreateList(Node *phead, int n)
{
	Node *pNext;            //定义一个与pHead相邻节点
	int i = 0;
	if (phead == NULL)
	{
		printf("clearList函数执行，链表为空\n");
		return NULL;
	}
	while (i < n - 1 && phead->next != NULL)
	{
		pNext = phead->next;//保存下一结点的指针
		free(phead);
		phead = pNext;      //表头下移
		i++;
	}
	return phead;
}
int sum[20000] = { 0 };
int MaxSubsequence(int n, int x[])
{
	Node *p1, *p2;
	p1 = (Node *)malloc(sizeof(Node)); //申请新节点
	p1->next = NULL;
	int flag = 0;

	for (int i = 0; i < n; i++) {
		//initial
		//第一个元素进入
		//p1 = p2 = (Node *)malloc(sizeof(Node)); //申请新节点
		flag = 0;
		if (i == 0 && x[i] > 0)
		{
			p1->data[0] = i;
			p1->data[1] = i + 1;
			p1->L = sum[i];
			p1->R = sum[i] + x[i];
			sum[i + 1] = x[i];
		}
		else if (i >= 1 && x[i] > 0)
		{
			flag = FindItem(p1, sum[i]);
			if (flag == 1 && sum[i] + x[i] <= Ri)
			{
				//找到L更小的Li,加入链表
				//申请新节点
				p2 = (struct Node*)malloc(sizeof(struct Node));/*下一个新节点*/
				p2->next = NULL;
				p2->next = p1;

				p1 = p2;
				p2->data[0] = i;
				p2->data[1] = i + 1;
				p2->L = sum[i];
				p2->R = sum[i] + x[i];
				sum[i + 1] = x[i] + sum[i];
			}
			else if (flag == 1 && sum[i] + x[i] > Ri)
			{
				//找到L更小的Li
				//判断R的值，找到则重构链表
				p1 = ReCreateList(p1, flag);
				p1->data[1] = i + 1;
				p1->R = sum[i] + x[i];
				sum[i + 1] = x[i] + sum[i];
			}

			else if (flag > 1 && sum[i] + x[i] <= Ri)
			{
				//找到L更小的Li,加入链表
				//申请新节点
				p2 = (struct Node*)malloc(sizeof(struct Node));/*下一个新节点*/
				p2->next = NULL;
				//PrintList(p1);
				int m = 1;
				while (p1->next != NULL && m < flag)
				{
					//printf("=====");
					printf("范围是%d-%d\n", p1->data[0] + 1, p1->data[1]);/*输出链表节点的值*/
					printf("子序列和为：%d\n", p1->R - p1->L);
					p1 = p1->next;

					++m;
				}
				p2->next = p1;

				p1 = p2;
				p2->data[0] = i;
				p2->data[1] = i + 1;
				p2->L = sum[i];
				p2->R = sum[i] + x[i];
				sum[i + 1] = x[i] + sum[i];
			}
			else if (flag > 1 && sum[i] + x[i] > Ri)
			{
				//找到L更小的Li
				//判断R的值，找到则重构链表
				p1 = ReCreateList(p1, flag);
				p1->data[1] = i + 1;
				p1->R = sum[i] + x[i];
				sum[i + 1] = x[i] + sum[i];
			}
			else if (flag == 0)
			{
				//没有找到L更小的，输出链表，删除原链表；
				//printf("++");
				PrintList(p1);
				ClearList(p1);
				//free(p1);
				//建立新链表，重新设置为I1
				p1 = (Node *)malloc(sizeof(Node)); //申请新节点
				p1->next = NULL;
				p1->data[0] = i;
				p1->data[1] = i + 1;
				p1->L = sum[i];
				p1->R = sum[i] + x[i];
				sum[i + 1] = x[i] + sum[i];
			}
			else sum[i + 1] = x[i] + sum[i];

		}
		else if (x[i + 1] > 0)
		{
			sum[i + 1] = x[i] + sum[i];
		}
		else
		{
			sum[i + 1] = x[i] + sum[i];
		}


		//merger positive subsequence
	}
	PrintList(p1);
	free(p1);
	return 0;
}

int numsum = 0;
int MaxSum(int n, int a[])
{
	int sum = 0, b = 0;
	for (int i = 1; i<n; i++)
	{
		if (b>0)
		{
			b += a[i];

		}
		else
		{
			b = a[i];
			++numsum;
		}
		if (b>sum)
		{
			sum = b;
			++numsum;
		}
	}
	return sum;
}

int main(int argc, const char * argv[])
{
	clock_t start_time, end_time;
	double  duration_time;
	start_time = clock();

	int a[] = { 4, -5, 3, -3, 1, 2, -2, 2, -2, 1, 5 };
	int b[] = { -2, 11, -4, 13, -5, -2 };
	int c[] = { 4, -5, 3, -3, 1, 2 };
	int d[] = { -10, 3, -2, -4, -5, 1 };
	int e[] = { 5, -3, -1, 5, -4, -5, 0, 3, 3, 6, 1, -3, -6, 3, -6, 3, -1, 0, 3, -3, 0, 6, 1, -4, 0, -6 };
	printf("sum is :%d\n", MaxSubsequence(26, e));
	printf("Subsequence's amount is :%d\n", numsum);

	//int *p;
	//int i;
	//p = ReadDate("/Users/zph/XcodeProject/编程珠玑/8.4/8.4/data.txt");
	//printf("%d\n",MaxSubsequence(50,p));

	end_time = clock();
	duration_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
	printf("duration: %lf seconds\n", duration_time);
	//    for ( i = 0; i < 51; i++ )
	//    {
	//        printf("%d\n",sum[i]);
	//    }

	return 0;
}
