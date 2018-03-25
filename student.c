
#include"student.h"

//���ļ���ȡѧ����Ϣ
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
		printf("�ļ���ʧ��");
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
		printf("û��ѧ��\n");
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
		printf("�ļ���ʧ��\n");
		return;
	}
	//����
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

//ɾ��ָ��ѧ����Ϣ
void DeleteStuNode(pStuList pList)
{
	//�ж��Ƿ�Ϊ��
	if (NULL == pList->pHead)
	{
		printf("û���κ�ѧ����Ϣ\n");
		return;
	}
	
	pStuNode pcur, ppre;
	pcur = ppre = pList->pHead;
	char name[10];
	printf("������Ҫɾ��ѧ����������");
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

//�޸�ѧ����Ϣ
void ChangeStuInfo(pStuList pList)
{
	char ID[10];
	printf("������ѧ�ţ�");
	scanf("%s", ID);
	pStuNode pFind;
	pFind = FindStuByID(pList, ID);
	if (pFind == NULL)
	{
		printf("δ�ҵ�\n");
	}
	else
	{
		printf("---��ʼ�޸�---\n");
		printf("\n������ѧ�ţ�");
		scanf("%s", pFind->ID);
		printf("\n������������");
		scanf("%s", pFind->Name);
		printf("\n�����������");
		scanf("%d", &pFind->Score);
	}
}

void AddStuByID(pStuList pList)
{
	char ID[10];
	printf("������ѧ�ţ�");
	scanf("%s", ID);
	pStuNode pFind;
	pFind = FindStuByID(pList, ID);
	if (pFind == NULL)
	{
		printf("δ�ҵ�\n");
	}
	else
	{
		printf("���ҵ���");
		printf("ѧ�ţ�%s�� ������%s�� ������%d \n", pFind->ID, pFind->Name, pFind->Score);
		pStuNode pCur = pList->pHead;
		pStuNode pNode = (pStuNode)malloc(sizeof(StuNode));//Error:pStuNode pNode = (pStuNode)malloc(sizeof(pStuNode))
		memset(pNode, 0, sizeof(StuNode));//Error:memset(pNode, 0, sizeof(pNode))
		printf("\n������ѧ�ţ�");
		scanf("%s", pNode->ID);
		printf("\n������������");
		scanf("%s", pNode->Name);
		printf("\n�����������");
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
		printf("����ɹ�\n");
		PrintList(pList);

	}
}

pStuNode FindStuByID(pStuList pList, char *ID)
{
	//������
	if (NULL == ID)
	{
		printf("ѧ���������\n");
		return NULL;
	}
	if (NULL == pList->pHead)
	{
		printf("����Ϊ��\n");
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
		printf("������Ϣ����\n");
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
		printf("ѧ�ţ�%s, ������%s, ������%d\n", pTemp->ID, pTemp->Name, pTemp->Score);
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
	printf("********************ѧ������ϵͳ********************\n");
	printf("********************����ָ������********************\n");
	printf("***             0��������ʾָ�����              ***\n");
	printf("***             1������һ��ѧ����Ϣ(β���)      ***\n");
	printf("***             2������һ��ѧ����Ϣ(ͷ���)      ***\n");
	printf("***             3������ָ��ѧ������Ϣ(����/ѧ��) ***\n");
	printf("***             4������һ��ѧ����Ϣ(ָ��ѧ��)    ***\n");
	printf("***             5���޸�ָ��ѧ������Ϣ            ***\n");
	printf("***             6��ѧ������Ϣ���浽�ļ�          ***\n");
	printf("***             7��ɾ��ָ��ѧ������Ϣ            ***\n");
	printf("***             8���ָ�ɾ��ѧ������Ϣ            ***\n");
	printf("***             9����ӡ��Ϣ                      ***\n");
	printf("***             10���˳�ϵͳ                      ***\n");
}

