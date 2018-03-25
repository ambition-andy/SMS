
#include"student.h"

//从文件读取学生信息
void ReadStuFromFile(pStuList pList)
{
	FILE * pFile;
	char strBuf[30] = { 0 };
	char strStuID[10] = { 0 };
	char strStuName[10] = { 0 };
	char strStuScore[10] = { 0 };
	pFile = fopen("stu.txt", "r");
	if (NULL == pFile)
	{
		printf("文件打开失败");
		return;
	}
	while (NULL != fgets(strBuf, 30, pFile))
	{
		if (1 == strlen(strBuf))
		{
			break;
		}
		int point = 0;
		int i = 0;
		int j = 0;
		int k = 0;
		for (; '\n' != strBuf[i]; ++i)
		{
			if (0 == point)
			{
				strStuID[i] = strBuf[i];
				if ('.' == strBuf[i])
				{
					strStuID[i] = '\0';
					point++;
				}
			}
			else if (1 == point)
			{
				strStuName[j] = strBuf[i];
				if ('.' == strBuf[i])
				{
					strStuName[j] = '\0';
					point++;
				}
				j++;
			}
			else if (2 == point)
			{
				strStuScore[k] = strBuf[i];
				if ('.' == strBuf[i])
				{
					strStuScore[k] = '\0';
					point++;
				}
				k++;
			}
		}
		pStuNode pNode = malloc(sizeof(StuNode));
		memset(pNode, 0, sizeof(StuNode));
		strcpy(pNode->ID, strStuID);
		strcpy(pNode->Name, strStuName);
		pNode->Score = atoi(strStuScore);
		AddStudent(pList, pNode);

	}
	
	fclose(pFile);


}
void SaveToFile(pStuList pList)
{
	if (NULL == pList->pHead)
	{
		printf("没有学生\n");
		return;
	}
	FILE * pFile;
	pStuNode pNode = pList->pHead;
	char strBuf[30] = { 0 };
	char strScore[10] = { 0 };
	//open
	pFile = fopen("stu.txt", "w+");//fopen
	if (NULL == pFile)
	{		
		printf("文件打开失败\n");
		return;
	}
	//操作
	while (pNode)
	{
		strcpy(strBuf, pNode->ID);
		strcat(strBuf, ".");

		strcat(strBuf, pNode->Name);
		strcat(strBuf, ".");

		itoa(pNode->Score, strScore, 10);
		strcat(strBuf, strScore);
		strcat(strBuf, ".");

		fwrite(strBuf, 1, strlen(strBuf), pFile);
		fwrite("\n", 1, strlen("\n"), pFile);
		pNode = pNode->pNext;
	}

	//close
	fclose(pFile);
	return;
}

//删除指定学生信息
void DeleteStuNode(pStuList pList)
{
	//判断是否为空
	if (NULL == pList->pHead)
	{
		printf("没有任何学生信息\n");
		return;
	}
	
	pStuNode pcur, ppre;
	pcur = ppre = pList->pHead;
	char name[10];
	printf("请输入要删除学生的姓名：");
	scanf("%s", name);
	if (0 == strcmp(pcur->Name, name))
	{
		if (NULL != pcur->pNext)
		{
			pList->pHead = pList->pHead->pNext;
			free(pcur);
			pcur = NULL;
			printf("SUCCESS!\n");
			return;
		}
		else
		{
			pList->pHead = pList->pTail = NULL;
			free(pcur);
			pcur = NULL;
			printf("SUCCESS!\n");
			return;
		}
	}
	pcur = pcur->pNext;
	while (NULL != pcur)
	{
		if (0 == strcmp(pcur->Name, name))
		{
			ppre->pNext = pcur->pNext;
			if (NULL == pcur->pNext)
			{
				pList->pTail = ppre;
			}
			free(pcur);
			pcur = NULL;
			printf("SUCCESS!\n");
			return;
		}
		ppre = pcur;
		pcur = pcur->pNext;
	}
	printf("NO such student\n");
	return;
}

//修改学生信息
void ChangeStuInfo(pStuList pList)
{
	char ID[10];
	printf("请输入学号：");
	scanf("%s", ID);
	pStuNode pFind;
	pFind = FindStuByID(pList, ID);
	if (pFind == NULL)
	{
		printf("未找到\n");
	}
	else
	{
		printf("---开始修改---\n");
		printf("\n请输入学号：");
		scanf("%s", pFind->ID);
		printf("\n请输入姓名：");
		scanf("%s", pFind->Name);
		printf("\n请输入分数：");
		scanf("%d", &pFind->Score);
	}
}

void AddStuByID(pStuList pList)
{
	char ID[10];
	printf("请输入学号：");
	scanf("%s", ID);
	pStuNode pFind;
	pFind = FindStuByID(pList, ID);
	if (pFind == NULL)
	{
		printf("未找到\n");
	}
	else
	{
		printf("已找到：");
		printf("学号：%s， 姓名：%s， 分数：%d \n", pFind->ID, pFind->Name, pFind->Score);
		pStuNode pCur = pList->pHead;
		pStuNode pNode = (pStuNode)malloc(sizeof(StuNode));//Error:pStuNode pNode = (pStuNode)malloc(sizeof(pStuNode))
		memset(pNode, 0, sizeof(StuNode));//Error:memset(pNode, 0, sizeof(pNode))
		printf("\n请输入学号：");
		scanf("%s", pNode->ID);
		printf("\n请输入姓名：");
		scanf("%s", pNode->Name);
		printf("\n请输入分数：");
		scanf("%d", &(pNode->Score));
		pNode->pNext = NULL;
		if (pList->pTail == pFind)
		{
			pList->pTail->pNext = pNode;
			pList->pTail = pNode;
		}
		else
		{
			while (pCur != pFind)
			{
				pCur = pCur->pNext;
			}
			
			pNode->pNext = pCur->pNext;
			pCur->pNext = pNode;
		}
		printf("插入成功\n");
		PrintList(pList);

	}
}

pStuNode FindStuByID(pStuList pList, char *ID)
{
	//检查参数
	if (NULL == ID)
	{
		printf("学号输入错误。\n");
		return NULL;
	}
	if (NULL == pList->pHead)
	{
		printf("链表为空\n");
		return NULL;
	}
	pStuNode pTemp = pList->pHead;
	while (NULL != pTemp)
	{
		if (0==strcmp(pTemp->ID, ID))
		{
			return pTemp;
		}
		pTemp = pTemp->pNext;
	}
	return NULL;
}

void AddStudentToHead(pStuList pList, pStuNode ptemp)
{
	if (NULL == ptemp->ID || NULL == ptemp->Name || ptemp->Score < 0)
	{
		printf("输入信息有误\n");
		return;
	}
	pStuNode pNode = (pStuNode)malloc(sizeof(StuNode));
	memset(pNode, 0, sizeof(StuNode));
	strcpy(pNode->ID, ptemp->ID);
	strcpy(pNode->Name, ptemp->Name);
	pNode->Score = ptemp->Score;
	//pNode->pNext = NULL;
	if (NULL == pList->pHead)
	{
		pList->pHead = pNode;
		pList->pTail = pNode;
	}
	else
	{
		pNode->pNext = pList->pHead;
		pList->pHead = pNode;
	}
}

void PrintList(pStuList pList)
{
	if (NULL == pList->pHead)
	{
		printf("List is empty!\n");
		return;
	}
	pStuNode pTemp = pList->pHead;
	while (pTemp != NULL)
	{
		printf("学号：%s, 姓名：%s, 分数：%d\n", pTemp->ID, pTemp->Name, pTemp->Score);
		pTemp = pTemp->pNext;
	}
	printf("\n");
}

void FreeList(pStuList pList)
{
	pStuNode pTemp;
	while (NULL != pList->pHead)
	{
		pTemp = pList->pHead;
		pList->pHead = pList->pHead->pNext;
		free(pTemp);
	}
}

void AddStudent(pStuList pList, pStuNode ptemp)
{
	pStuNode pNode = (pStuNode)malloc(sizeof(StuNode));
	memset(pNode, 0, sizeof(StuNode));
	strcpy(pNode->ID, ptemp->ID);
	strcpy(pNode->Name, ptemp->Name);
	pNode->Score = ptemp->Score;
	pNode->pNext = NULL;
	if (NULL == pList->pHead)
	{
		pList->pHead = pNode;
		pList->pTail = pNode;
	}
	else
	{
		pList->pTail->pNext = pNode;
		pList->pTail = pNode;
	}
}

void ShowOrders()
{
	printf("********************学生管理系统********************\n");
	printf("********************操作指令如下********************\n");
	printf("***             0、重新显示指令界面              ***\n");
	printf("***             1、增加一个学生信息(尾添加)      ***\n");
	printf("***             2、增加一个学生信息(头添加)      ***\n");
	printf("***             3、查找指定学生的信息(姓名/学号) ***\n");
	printf("***             4、增加一个学生信息(指定学号)    ***\n");
	printf("***             5、修改指定学生的信息            ***\n");
	printf("***             6、学生的信息保存到文件          ***\n");
	printf("***             7、删除指定学生的信息            ***\n");
	printf("***             8、恢复删除学生的信息            ***\n");
	printf("***             9、打印信息                      ***\n");
	printf("***             10、退出系统                      ***\n");
}

