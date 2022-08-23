/*
* 
* 
* 
--->2022.8.23
--->Liu


���ݴ洢���û���������
���ݴ�����ʽ�ṹ
	*��������
	* ��������
	* ָ��λ��ɾ��
	* ��������
	* ���ҽڵ�
�û����� 
	* ���Ʋ˵�
	* ��������
*/
#include<stdio.h>
#include<string.h>
#include<assert.h>       //���ԣ��ж�ָ���Ƿ�Ϊ��
#include<stdlib.h>


//��װ�Լ���Ҫ���������
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


//�����ǽṹͼ�����ͽṹ������һ��
//1.ָ��ָ�����
//2.��̬�ڴ����룬ָ������ı���
struct Node* creatHead()
{
	//��ͷ�����컯����
	struct Node* headNode = (struct Node*)malloc(sizeof(struct Node));
	assert(headNode);
	headNode->next = NULL;
	return headNode;
}


//������㣨���û����ݱ�ɽṹ�������
struct Node* creatNode(struct student data)
{
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	assert(newNode);
	/*
	�����Ա��
	if(newNode==NULL)
		return NULL;
	*/
	//NULL->data=data;��ģ�������ûdata
	newNode->data = data;
	newNode->next = NULL;
	return newNode;

	
};


//����
void insertByHead(struct Node* headNode, struct student data)
{
	struct Node* newNode = creatNode(data);
	newNode->next = headNode->next;
	headNode->next = newNode;

}


//ɾ��
void deleteByName(struct Node* headNode,const char* name)
{
	struct Node* preNode = headNode;
	struct Node* posNode = headNode->next;
	while (posNode != NULL && strcmp(posNode->data.name ,name))  //�ַ�����Ҫ�й���
	{
		preNode = posNode;
		posNode = preNode->next;

	}
	if (posNode != NULL)
	{
		preNode->next = posNode->next;
		free(posNode);
		printf("ɾ���ɹ�\n");
	}
}

//����
void printList(struct Node* headNode)
{
	struct Node* pMove = headNode->next;
	printf("����\t����\tѧ��\t�ֻ�\n");
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

//����
struct Node* searchByNum(struct Node* headNode,char* name)
{
	struct Node* pMove = headNode->next;
	while (pMove != NULL && strcmp(pMove->data.name, name))
	{
		pMove = pMove->next;
	}
	return pMove;
}
//д�ļ�
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
	fclose(fp);           //�ǵùرգ�����ϰ��
}

//�û�����
void makeMenu()
{
	printf("************************��ѧ������ϵͳ��************************\n");
	printf("\n\n\n");
	printf("\t\t\t0.�Ƴ�ϵͳ\n");
	printf("\n");
	printf("\t\t\t1.¼����Ϣ\n");
	printf("\n");
	printf("\t\t\t2.�����Ϣ\n");
	printf("\n");
	printf("\t\t\t3.ɾ����Ϣ\n");
	printf("\n");
	printf("\t\t\t4.������Ϣ\n");
	printf("\n");
	printf("\t\t\t5.�޸���Ϣ\n");
	printf("\n\n\n");
	printf("----------------------------------------------------------------------\n");
	printf("���������ѡ��0-5����");
	
}

//��������
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
		printf("�˳��ɹ�\n");
		printf("\n");
		system("pause");
		exit(0);
			break;
	case 1:
		printf("\n");
		printf("������ѧ����Ϣ��name,age,num,tel��");
		scanf_s("%s%d%d%s", data.name,10,                          //%s���׵�ַ��ʼ����\0����
							&data.age,							  //�����������׵�ַ
							&data.num, 
							data.tel,11);

		insertByHead(list, data);
		saveFile(list, "student.txt");
		printf("\n");
		printf("¼��ɹ�\n");
		printf("\n");
		break;
	case 2:
		printf("\n");
		printList(list);
		break;
	case 3:
		printf("\n");
		printf("������Ҫɾ����������\n");
		scanf_s("%s", data.name,10);
		deleteByName(list, data.name);
		saveFile(list, "student.txt");
		break;
	case 4:
		printf("\n");
		printf("���������������\n");
		scanf_s("%s", data.name,10);
		result = searchByNum(list,data.name);
		if (result != NULL)
		{
			printf("\n");
			printf("����\t����\t���\t�ֻ�\n");
			printf("%s\t%d\t%d\t%s\t\n",result->data.name,
									 result->data.age,
									 result->data.num,
									 result->data.tel);
		}
		else
		{
			printf("\n");
			printf("\n");
			printf("δ�ҵ������Ϣ��\n");
			printf("\n");
		}
		break;
	case 5:
		printf("\n");
		printf("������Ҫ�޸ĵ�����");
		scanf_s("%s", data.name,10);
		result = searchByNum(list, data.name);
		if (result != NULL)
		{
			printf("�������µ���Ϣ��name,age,num,tel��:");
			scanf_s("%s%d%d%s", 
								result->data.name, 10,
								&result->data.age,
								&result->data.num,
								result->data.tel, 11);
			saveFile(list,"student.txt");
			printf("\n");
			printf("\n");
			printf("�޸ĳɹ���\n");
			printf("\n");
			printf("\n");
		}
		else
		{
			printf("\n");
			printf("\n");
			printf("�޷��޸ģ�\n");
			printf("\n");
			printf("\n");
		}
		break;
	
	default:
		printf("\n");
		printf("\n");
		printf("�������\n");
	}
}


//���ļ�
void readFile(struct Node* headNode, const char* fileURL)
{
	FILE* fp = fopen(fileURL,"r"); //��һ�δ򿪻�ʧ�� ��r�����ܴ��������ȴ���
	if (fp == NULL)
	{	
		fp = fopen(fileURL, "w+"); //w�ܴ���
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
		system("cls");			//����
	}
	
	return 0;
}




