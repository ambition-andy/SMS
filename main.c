#include"student.h"

int main(void)
{
	int nOrder = -1;//指令
	ShowOrders();
	
	StuList studentList;
	studentList.pHead = studentList.pTail = NULL;
	StuNode temp;
	memset(&temp, 0, sizeof(StuNode));
	ReadStuFromFile(&studentList);//开始运行的时候读取文件
	while (1)
	{
		printf("输入指令数字(0 to show orderpage):");
		scanf("%d", &nOrder);
		char FindID[10];
		switch (nOrder)
		{
		case 0:
			ShowOrders();
			break;
		case 1://尾插法
			printf("\n请输入学号：");
			scanf("%s", temp.ID);
			printf("\n请输入姓名：");
			scanf("%s", temp.Name);
			printf("\n请输入分数：");
			scanf("%d", &temp.Score);
			AddStudent(&studentList, &temp);
			break;
		case 2://头插法
			printf("\n请输入学号：");
			scanf("%s", temp.ID);
			printf("\n请输入姓名：");
			scanf("%s", temp.Name);
			printf("\n请输入分数：");
			scanf("%d", &temp.Score);
			AddStudentToHead(&studentList, &temp);
			break;
		case 3:  //查找
			printf("Input ID:");
			scanf("%s",FindID);
			pStuNode pFind;
			pFind = FindStuByID(&studentList,FindID);
			if (NULL != pFind)
			{
				printf("已找到：\n");
				printf("学号：%s， 姓名：%s， 分数：%d \n", pFind->ID, pFind->Name, pFind->Score);
			}
			else
			{
				printf("未找到！\n");
			}
			break;
		case 4://中间插入
			AddStuByID(&studentList);
			break;
		case 5://修改学生节点信息
			ChangeStuInfo(&studentList);
			break;
		case 6://Save student info to file
			SaveToFile(&studentList);
			break;
		case 7://删除指定学生信息
			SaveToFile(&studentList);
			DeleteStuNode(&studentList);
			break;
		case 8://恢复删除学生的信息
			FreeList(&studentList);//恢复之前要清空一下
			ReadStuFromFile(&studentList);
			break;
		case 9:
			PrintList(&studentList);
			break;
		case 10:
			goto MyQuit;

		default:
			printf("指令有误\n");
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
