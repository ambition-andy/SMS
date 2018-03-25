#include"student.h"

int main(void)
{
	int nOrder = -1;//ָ��
	ShowOrders();
	
	StuList studentList;
	studentList.pHead = studentList.pTail = NULL;
	StuNode temp;
	memset(&temp, 0, sizeof(StuNode));
	ReadStuFromFile(&studentList);//��ʼ���е�ʱ���ȡ�ļ�
	while (1)
	{
		printf("����ָ������(0 to show orderpage):");
		scanf("%d", &nOrder);
		char FindID[10];
		switch (nOrder)
		{
		case 0:
			ShowOrders();
			break;
		case 1://β�巨
			printf("\n������ѧ�ţ�");
			scanf("%s", temp.ID);
			printf("\n������������");
			scanf("%s", temp.Name);
			printf("\n�����������");
			scanf("%d", &temp.Score);
			AddStudent(&studentList, &temp);
			break;
		case 2://ͷ�巨
			printf("\n������ѧ�ţ�");
			scanf("%s", temp.ID);
			printf("\n������������");
			scanf("%s", temp.Name);
			printf("\n�����������");
			scanf("%d", &temp.Score);
			AddStudentToHead(&studentList, &temp);
			break;
		case 3:  //����
			printf("Input ID:");
			scanf("%s",FindID);
			pStuNode pFind;
			pFind = FindStuByID(&studentList,FindID);
			if (NULL != pFind)
			{
				printf("���ҵ���\n");
				printf("ѧ�ţ�%s�� ������%s�� ������%d \n", pFind->ID, pFind->Name, pFind->Score);
			}
			else
			{
				printf("δ�ҵ���\n");
			}
			break;
		case 4://�м����
			AddStuByID(&studentList);
			break;
		case 5://�޸�ѧ���ڵ���Ϣ
			ChangeStuInfo(&studentList);
			break;
		case 6://Save student info to file
			SaveToFile(&studentList);
			break;
		case 7://ɾ��ָ��ѧ����Ϣ
			SaveToFile(&studentList);
			DeleteStuNode(&studentList);
			break;
		case 8://�ָ�ɾ��ѧ������Ϣ
			FreeList(&studentList);//�ָ�֮ǰҪ���һ��
			ReadStuFromFile(&studentList);
			break;
		case 9:
			PrintList(&studentList);
			break;
		case 10:
			goto MyQuit;

		default:
			printf("ָ������\n");
			break;

		}
	}
MyQuit:
	printf("MyQuit\n");
	SaveToFile(&studentList);
	FreeList(&studentList);
	system("pause");
	return 0;
}
