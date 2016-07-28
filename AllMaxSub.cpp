
//
//  main.c
//  8.6
//
//  Created by zph on 16/3/18.
//  Copyright © 2016年 zph. All rights reserved.
//
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
using namespace std;

typedef struct Node{    /* 定义单链表结点类型 */
	int data[2];
	__int64 L;
	__int64 R;
	struct Node *next;
} Node;

const int g_data_line = 20000;
int data[g_data_line + 1];
int g_data_num = 0;
void GetData(string filename, int start, int end)
{
	ifstream file;
	char line[8];
	file.open(filename, ios::in);
	int i = 0;
	while (i <= end && !file.eof())
	{
		i++;
		file.getline(line, 10);
		if (i >= start)
		{
			g_data_num++;
			data[g_data_num] = atoi(line);
		}
	}
	file.close();
}

//搜索链表
__int64 Li = 0;
__int64 Ri = 0;
int FindItem(Node *p, __int64 num)
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
		printf("范围是%d-%d\n", temp->data[0], temp->data[1]-1);/*输出链表节点的值*/
		//printf("子序列和为：%d\n", temp->R - temp->L);
		cout << temp->R - temp->L << endl;
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
Node *ReCreateList(Node *phead, int n, __int64 num)
{
	Node *pNext;            //定义一个与pHead相邻节点
	if (phead == NULL)
	{
		printf("clearList函数执行，链表为空\n");
		return NULL;
	}
	while (phead->next != NULL && phead->R <= num )
	{
		pNext = phead->next;//保存下一结点的指针
		//free(phead);
		phead = pNext;      //表头下移
	}
	return phead;
}
__int64 sum[30003] = { 0 };
int MaxSubsequence(int n, int x[])
{
	Node *p1, *p2, *p3;
	p1 = new Node(); //申请新节点
	p2 = new Node();
	p3 = new Node();
	p1->next = NULL;
	int flag = 0;
	for (int i = 1; i <= n; i++) {
		//initial
		//第一个元素进入
		//p1 = p2 = (Node *)malloc(sizeof(Node)); //申请新节点
		if (p1->L >= 9000000 || p1->R >= 9000000)
			i = i;
		if (i == 15666)
		{
			i = i;
			int s = x[i];
		}
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
			if (flag >= 1 && sum[i] + x[i] <= Ri)
			{
				//找到L更小的Li,加入链表
				//申请新节点
				p2 = new Node();/*下一个新节点*/
				p2->next = NULL;
				p2->next = p1;

				p1 = p2;
				p2->data[0] = i;
				p2->data[1] = i + 1;
				p2->L = sum[i];
				p2->R = sum[i] + x[i];
				sum[i + 1] = x[i] + sum[i];
				
			}
			else if (flag >= 1 && sum[i] + x[i] > Ri)
			{
				//找到L更小的Li
				//判断R的值，找到则重构链表
				p3 = new Node();
				p3 = p1;
				p1 = ReCreateList(p1, flag, sum[i] + x[i]);
				if (p1->R >= sum[i] + x[i])
				{
					p2 = new Node();/*下一个新节点*/
					p2->next = NULL;
					p2->next = p3;

					p1 = p2;
					p2->data[0] = i;
					p2->data[1] = i + 1;
					p2->L = sum[i];
					p2->R = sum[i] + x[i];
					sum[i + 1] = x[i] + sum[i];
				}
				else
				{
					p1->data[0] = p1->data[0];
					p1->data[1] = i + 1;
					p1->L = p1 -> L;
					p1->R = sum[i] + x[i];
					sum[i + 1] = x[i] + sum[i]; 
				}
				
			}
			else if (flag == 0)
			{
				//没有找到L更小的，输出链表，删除原链表；
				PrintList(p1);
				ClearList(p1);
				//建立新链表，重新设置为I1
				p1 = new Node(); //申请新节点
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



int main(int argc, const char * argv[])
{
	clock_t start_time, end_time;
	double  duration_time;
	start_time = clock();

	int a[] = { 4, -5, 3, -3, 1, 2, -2, 2, -2, 1, 5 };
	/*int b[] = { -2, 11, -4, 13, -5, -2 };
	int c[] = { 4, -5, 3, -3, 1, 2 };
	int d[] = { -10, 3, -2, -4, -5, 1 };
	int e[] = { 5, -3, -1, 5, -4, -5, 0, 3, 3, 6, 1, -3, -6, 3, -6, 3, -1, 0, 3, -3, 0, 6, 1, -4, 0, -6 };
	printf("sum is :%d\n", MaxSubsequence(26, e));
	printf("Subsequence's amount is :%d\n", numsum);*/

	int *p;
	int i;
	GetData("data2w.txt", 1, 20000);
	MaxSubsequence(20000, data);

	end_time = clock();
	duration_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
	printf("duration: %lf seconds\n", duration_time);
	return 0;
}
