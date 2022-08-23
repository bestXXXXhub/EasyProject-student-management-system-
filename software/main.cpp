/*
* 
* 
* 
--->2022.8.23
--->Liu


数据存储和用户交互分离
数据处理：链式结构
	*创建数据
	* 插入数据
	* 指定位置删除
	* 遍历链表
	* 查找节点
用户交互 
	* 绘制菜单
	* 按键交互
*/
#include<stdio.h>
#include<string.h>
#include<assert.h>       //断言，判断指针是否为空
#include<stdlib.h>


//封装自己需要管理的数据
struct student 
{
	char name[10];
	int age;
	int num;
	char tel[11];
};


struct Node
{
	struct student data;
	struct Node* next;

};

struct Node* list;


//链表是结构图变量和结构体连在一起
//1.指针指向变量
//2.动态内存申请，指向堆区的变量
struct Node* creatHead()
{
	//表头做差异化处理
	struct Node* headNode = (struct Node*)malloc(sizeof(struct Node));
	assert(headNode);
	headNode->next = NULL;
	return headNode;
}


//创建结点（把用户数据变成结构体变量）
struct Node* creatNode(struct student data)
{
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	assert(newNode);
	/*
	防御性编程
	if(newNode==NULL)
		return NULL;
	*/
	//NULL->data=data;错的，空里面没data
	newNode->data = data;
	newNode->next = NULL;
	return newNode;

	
};


//插入
void insertByHead(struct Node* headNode, struct student data)
{
	struct Node* newNode = creatNode(data);
	newNode->next = headNode->next;
	headNode->next = newNode;

}


//删除
void deleteByName(struct Node* headNode,const char* name)
{
	struct Node* preNode = headNode;
	struct Node* posNode = headNode->next;
	while (posNode != NULL && strcmp(posNode->data.name ,name))  //字符串比要有规则
	{
		preNode = posNode;
		posNode = preNode->next;

	}
	if (posNode != NULL)
	{
		preNode->next = posNode->next;
		free(posNode);
		printf("删除成功\n");
	}
}

//遍历
void printList(struct Node* headNode)
{
	struct Node* pMove = headNode->next;
	printf("姓名\t年龄\t学号\t手机\n");
	while (pMove != NULL)
	{
		//printf("%d\t", pMove->data);
		printf("%s\t%d\t%d\t%s\n",pMove->data.name,                            
								  pMove->data.age, 
								  pMove->data.num, 
								  pMove->data.tel);

		pMove = pMove->next;
	}
	printf("\n");
}

//查找
struct Node* searchByNum(struct Node* headNode,char* name)
{
	struct Node* pMove = headNode->next;
	while (pMove != NULL && strcmp(pMove->data.name, name))
	{
		pMove = pMove->next;
	}
	return pMove;
}
//写文件
void saveFile(struct Node* headNode, const char* fileURL)
{
	FILE* fp = fopen(fileURL, "w");
	struct Node* pMove = headNode->next;
	while (pMove != NULL)
	{
		fprintf(fp, "%s\t%d\t%d\t%s\n", pMove->data.name,
			pMove->data.age,
			pMove->data.num,
			pMove->data.tel);
		pMove = pMove->next;

	}
	fclose(fp);           //记得关闭，养成习惯
}

//用户交互
void makeMenu()
{
	printf("************************【学生管理系统】************************\n");
	printf("\n\n\n");
	printf("\t\t\t0.推出系统\n");
	printf("\n");
	printf("\t\t\t1.录入信息\n");
	printf("\n");
	printf("\t\t\t2.浏览信息\n");
	printf("\n");
	printf("\t\t\t3.删除信息\n");
	printf("\n");
	printf("\t\t\t4.查找信息\n");
	printf("\n");
	printf("\t\t\t5.修改信息\n");
	printf("\n\n\n");
	printf("----------------------------------------------------------------------\n");
	printf("请输入你的选择（0-5）：");
	
}

//按键操作
void keyDown()
{
	struct student data;
	struct Node* result = NULL;
	int userKey = 0;
	scanf_s("%d",&userKey);
	switch (userKey)
	{
	case 0:
		printf("\n");
		printf("退出成功\n");
		printf("\n");
		system("pause");
		exit(0);
			break;
	case 1:
		printf("\n");
		printf("请输入学生信息（name,age,num,tel）");
		scanf_s("%s%d%d%s", data.name,10,                          //%s从首地址开始，到\0结束
							&data.age,							  //数组名就是首地址
							&data.num, 
							data.tel,11);

		insertByHead(list, data);
		saveFile(list, "student.txt");
		printf("\n");
		printf("录入成功\n");
		printf("\n");
		break;
	case 2:
		printf("\n");
		printList(list);
		break;
	case 3:
		printf("\n");
		printf("请输入要删除的姓名：\n");
		scanf_s("%s", data.name,10);
		deleteByName(list, data.name);
		saveFile(list, "student.txt");
		break;
	case 4:
		printf("\n");
		printf("请输入查找姓名：\n");
		scanf_s("%s", data.name,10);
		result = searchByNum(list,data.name);
		if (result != NULL)
		{
			printf("\n");
			printf("姓名\t年龄\t编号\t手机\n");
			printf("%s\t%d\t%d\t%s\t\n",result->data.name,
									 result->data.age,
									 result->data.num,
									 result->data.tel);
		}
		else
		{
			printf("\n");
			printf("\n");
			printf("未找到相关信息！\n");
			printf("\n");
		}
		break;
	case 5:
		printf("\n");
		printf("请输入要修改的姓名");
		scanf_s("%s", data.name,10);
		result = searchByNum(list, data.name);
		if (result != NULL)
		{
			printf("请输入新的信息（name,age,num,tel）:");
			scanf_s("%s%d%d%s", 
								result->data.name, 10,
								&result->data.age,
								&result->data.num,
								result->data.tel, 11);
			saveFile(list,"student.txt");
			printf("\n");
			printf("\n");
			printf("修改成功！\n");
			printf("\n");
			printf("\n");
		}
		else
		{
			printf("\n");
			printf("\n");
			printf("无法修改！\n");
			printf("\n");
			printf("\n");
		}
		break;
	
	default:
		printf("\n");
		printf("\n");
		printf("输入错误\n");
	}
}


//读文件
void readFile(struct Node* headNode, const char* fileURL)
{
	FILE* fp = fopen(fileURL,"r"); //第一次打开会失败 ，r，不能创建，得先创建
	if (fp == NULL)
	{	
		fp = fopen(fileURL, "w+"); //w能创建
		fclose(fp);
		return;
	}
	struct student data;
	while (fscanf(fp, "%s\t%d\t%d\t%s\n",
		data.name,
		&data.age,
		&data.num,
		data.tel)!=EOF)
	{	
		insertByHead(list, data);
	}
	fclose(fp);

}


int main()
{
	list = creatHead();
	readFile(list, "student.txt");
	while (1)
	{
		makeMenu();
		keyDown();
		system("pause");
		system("cls");			//清屏
	}
	
	return 0;
}




