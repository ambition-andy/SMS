#ifndef __STUDENT__H__
#define __STUDENT__H__

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Student
{
	char ID[10];
	char Name[10];
	int Score;
	struct Student *pNext;
} StuNode, *pStuNode;
typedef struct stulist
{
	pStuNode pHead;
	pStuNode pTail;
} StuList, *pStuList;

//Add student information
void AddStudent(pStuList, pStuNode);
//Free List
void FreeList(pStuList);
//Print List
void PrintList(pStuList);
//Head insert
void AddStudentToHead(pStuList pList, pStuNode ptemp);
//查找指定学生
pStuNode FindStuByID(pStuList pList, char *ID);
//指定节点后添加
void AddStuByID(pStuList pList);
//修改学生信息
void ChangeStuInfo(pStuList pList);
//删除学生节点
void DeleteStuNode(pStuList pList);

//Show orders
void ShowOrders();
//Save to file
void SaveToFile(pStuList pList);
//Read stuinfo from file
void ReadStuFromFile(pStuList pList);
#endif