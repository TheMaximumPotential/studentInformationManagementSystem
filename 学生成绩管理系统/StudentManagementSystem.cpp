#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#define LEN sizeof(student)

typedef struct Student {
	long int id;
	char name[20];
	int age;
	int score;
	struct Student *next;
}student;

// 数据存入文件 （追加一条） 
student *writeFiles(student stu)
{
    FILE *fp = fopen("student.dat", "ab");
    if(fp == NULL)
    {
        printf("打开文件失败!");
        return NULL;
    }
    fprintf(fp, "%d %s %d %d\n", stu.id, stu.name, stu.age, stu.score);
    fclose(fp);
}

// 数据存入文件 （循环覆盖） 
student *loopWrite(student *head)
{
	student *p = head;
    FILE *fp = fopen("student.dat", "w");
    if(fp == NULL)
    {
        printf("打开文件失败!");
        return NULL;
    }
    while (p != NULL)
    {
    	fprintf(fp, "%d %s %d %d\n", p->id, p->name, p->age, p->score);
    	p = p->next;
	}
    fclose(fp);
}

// 创建生成链表并返回 
student *createLine(FILE *fp)
{
	student *head, *p1, *p2;
	p1 = p2 = (student *) malloc(LEN);
	head = p1;
	int n = 0;
	while(!feof(fp))
	{
		fscanf(fp, "%d%s%d%d\n", &p1->id, &p1->name, &p1->age, &p1->score);
		p2 = p1;
		p1 = (student *) malloc(LEN);
		p2->next = p1;
		n++;
	}
	if (head->name[0] == '\0') head = NULL;
	else p2->next = NULL;
	return head;
}

// 从文件读取数据并生成返回链表 
student *readFiles()
{
	student *head, *p;
	FILE *fp = fopen("student.dat", "rb");
    if(fp == NULL)
    {
        printf("打开文件失败!");
        return NULL;
    }
    head = createLine(fp);
	fclose(fp);
	return head;
} 



// 表格样式输出链表 
int outputLine(student *head)
 {
	system("cls");
 	printf("     --------------------------------------------------------------------------------------------------------------\n");
	printf("     |                                               学生列表                                                     |\n");
	printf("     --------------------------------------------------------------------------------------------------------------\n");
	printf("     |          学号                 姓名                 年龄                 成绩                 操作          |\n");
	int n = 0, y = 4, x1 = 17, x2 = 38, x3 = 59, x4 = 80, arrow = 6;
	student *p = head;
	void gotoxy(int x, int y);
    while(1)           
    {
    	gotoxy(0, y);
		printf("     |                                                                                                            |\n");
    	if (p == NULL) 
		{
			gotoxy(0, y);
			printf("     |                                                                                                            |\n");
	    	gotoxy(0, y + 1);
	    	if (n == 0) 
			printf("     |                                           ----暂无数据----                                                 |\n");
			else 
			printf("     |                                          ----无更多数据----                                                |\n");
    		y += 2;
			break;
		}
		else 
		{
			gotoxy(0, y);
			printf("     |                                                                                                            |\n");
	    	y++; 
	    	gotoxy(0, y);
			printf("     |                                                                                         删除     修改      |\n");
			gotoxy(x1, y);
	        printf("%d", p->id);                                                                                                  
	        gotoxy(x2, y);
	        printf("%s", p->name);                                                                                                
	        gotoxy(x3, y);
	        printf("%d", p->age);                                                                                            
	        gotoxy(x4, y);
	        printf("%d", p->score);
	    	p = p->next;
		}
    	n++;
    	y++;
    }
    gotoxy(0, y);
	printf("     --------------------------------------------------------------------------------------------------------------\n");
	printf("     |      排序：(1 学号) (2 年龄) (3 成绩)          ↑↓←→ 切换         ENTER  确认         ESC  返回         |\n");
    printf("     --------------------------------------------------------------------------------------------------------------\n");
	return n;
}

// 定位光标位置到指定坐标
void gotoxy(int x, int y)
{   
    HANDLE hOut;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = { x, y };
    SetConsoleCursorPosition(hOut, pos);
}

//定义隐藏光标函数
void HideCursor()
{
	CONSOLE_CURSOR_INFO cursor;    
	cursor.bVisible = FALSE;    
	cursor.dwSize = sizeof(cursor);    
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);    
	SetConsoleCursorInfo(handle, &cursor);
}

// 字符串转数字 
int str2int(char *arr) 
{
	const char *ptr = arr;
	int priceNum = 0;
	while(*ptr)
	{
		priceNum *= 10;
		priceNum += *ptr - '0';
		ptr++;
	}
	return priceNum;
}

// 目录界面 
void homeInterface() 
{
	system("cls");
	char c;
	int b = 0, x = 38 , y = 8;
	printf("     --------------------------------------------------------------------------------------------------------------\n");
	printf("     |                                            学生信息管理系统                                                |\n");
	printf("     --------------------------------------------------------------------------------------------------------------\n");
	printf("     |           请选择目录：                                                                                     |\n");
	printf("     |                                                                                                            |\n");
	printf("     |                                                                                                            |\n");
	printf("     |                                                                                                            |\n");
	printf("     |                                     ==============================                                         |\n");
	printf("     |                                     |         1.新增学生         |                                         |\n");
	printf("     |                                     ==============================                                         |\n");
	printf("     |                                                                                                            |\n");
	printf("     |                                               2.删除学生                                                   |\n");
	printf("     |                                                                                                            |\n");
	printf("     |                                                                                                            |\n");
	printf("     |                                               3.修改学生                                                   |\n");
	printf("     |                                                                                                            |\n");
	printf("     |                                                                                                            |\n");
	printf("     |                                               4.查询学生                                                   |\n");
	printf("     |                                                                                                            |\n");
	printf("     |                                                                                                            |\n");
	printf("     |                                               5.退出程序                                                   |\n");
	printf("     |                                                                                                            |\n");
	printf("     |                                                                                                            |\n");
	printf("     |                                                                                                            |\n");
	printf("     |                                                                                                            |\n");
	printf("     |                                                                                                            |\n");
	printf("     |                                                                   ↑↓控制       ENTER  确认               |\n");
	printf("     --------------------------------------------------------------------------------------------------------------\n");
	c = getch();
	while( c != 13 ) {
		if (c == 80 && b <= 5)
		{
			b++;
			if (b == 5) b = 0;
			gotoxy(43, y - 1);
    		puts("                              ");
    		gotoxy(43, y);
    		puts(" ");
    		gotoxy(72, y);
    		puts(" ");
    		gotoxy(43, y + 1);
    		puts("                              ");
    		if (b == 0) y = 5;
    		gotoxy(43, y + 2);
    		puts("==============================");
    		gotoxy(43, y + 3);
    		puts("|");
    		gotoxy(72, y + 3);
    		puts("|");
    		gotoxy(43, y + 4);
    		puts("==============================");
			y += 3;
			gotoxy(0, 28);
		}
		if (c == 72 && b >= -1)
		{
			b--;
			if (b == -1) b = 4;
			gotoxy(43, y - 1);
    		puts("                              ");
    		gotoxy(43, y);
    		puts(" ");
    		gotoxy(72, y);
    		puts(" ");
    		gotoxy(43, y + 1);
    		puts("                              ");
    		if (b == 4) y = 23;
    		gotoxy(43, y - 2);
    		puts("==============================");
    		gotoxy(43, y - 3);
    		puts("|");
    		gotoxy(72, y - 3);
    		puts("|");
    		gotoxy(43, y - 4);
    		puts("==============================");
			y -= 3;
			gotoxy(0, 28);
		}
		c = getch();
	}
	if (b != 4) 
	{
		void operationMap(int operationId);
		operationMap(b);
	} 
	else
	{
		gotoxy(0, 80);
		exit(0);
	}
} 
 
// 清空表单
void clearForm() 
{
	int i;
	for (i = 0; i < 4; i++)
	{
		gotoxy(49, 7 + i * 3);
		printf("                  ");
	}
}

// 在链表中找出对应标号的结构体 
student *findStu(student *head, int n)
{
	student *p = head;
	int num;
	if (n == 0) return p;
	else 
	{
		while (num < n)
		{
			p = p->next;
			num++;
		}
		return p;
	}
} 

// 在链表中对应位置替换结构体并显示更新删除操作的表单视图 
student *reviseStu(student *head, int a, student *stu)
{
	student *p = head;
	char inputContent[4][20] = {{0}}, c;
	int handleIdx[4] = {0}, i = 0, j = 0, y = 7, x = 39, b = 0, idx = 0, n;
	char ctx[20] = {0}; 
	void handleTable(student stu, int type, int sortIdx);
	student *filter(student stu);
	itoa(stu->id, inputContent[0], 10);
	for (i = 0; i < sizeof(inputContent[1]); i++)
	{
		inputContent[1][i] = stu->name[i];
	}
	itoa(stu->age, inputContent[2], 10);
	itoa(stu->score, inputContent[3], 10);
	for(i = 0; i < 4; i++)
	{
		idx = 0;
		for(j = 0; j < 20; j++)
		{
			if (inputContent[i][j] == '\0') break;
			else idx++;
		}
		handleIdx[i] = idx;
	}
	system("cls");
	printf("     --------------------------------------------------------------------------------------------------------------\n");
	printf("     |                                               修改学生                                                     |\n");
	printf("     --------------------------------------------------------------------------------------------------------------\n");
	printf("     |           请输入要修改的信息：                                                                             |\n");
	printf("     |                                                                                                            |\n");
	printf("     |                                                                                                            |\n");
	printf("     |                                                                                                            |\n");
	printf("     |                                 ->  学号：                                                                 |\n");
	printf("     |                                           ￣￣￣￣￣￣￣￣￣￣                                             |\n");
	printf("     |                                                                                                            |\n");
	printf("     |                                     姓名：                                                                 |\n");
	printf("     |                                           ￣￣￣￣￣￣￣￣￣￣                                             |\n");
	printf("     |                                                                                                            |\n");
	printf("     |                                     年龄：                                                                 |\n");
	printf("     |                                           ￣￣￣￣￣￣￣￣￣￣                                             |\n");
	printf("     |                                                                                                            |\n");
	printf("     |                                     成绩：                                                                 |\n");
	printf("     |                                           ￣￣￣￣￣￣￣￣￣￣                                             |\n");
	printf("     |                                                                                                            |\n");
	printf("     |                                                 修改                                                       |\n");
	printf("     |                                                                                                            |\n");
	printf("     |                                                                                                            |\n");
	printf("     |                                                                                                            |\n");
	printf("     |                                                                                                            |\n");
	printf("     |                                                      ↑↓控制       ENTER  确认      ESC  返回             |\n");
	printf("     --------------------------------------------------------------------------------------------------------------\n");
	for(i = 0; i < 4; i++)
	{
		gotoxy(49, 7 + i * 3);
		printf("%s", inputContent[i]);
	}
	c = getch();
	gotoxy(49, y);
	n = 0;
	while(1) {
		if (n > 0)
		{
			gotoxy(63, 19);
			printf("             ");
			gotoxy(49, y);
		}
		if ((c == 80 && b <= 5) || c == 13 && b != 4)
		{
			b++;
			if (b == 5) b = 0;
    		gotoxy(x, y);
    		puts("   ");
    		if (b == 0) y = 4;
    		gotoxy(x, y + 3);
    		puts("-> ");
			y += 3;
		}
		else if (c == 72 && b >= -1)
		{
			b--;
			if (b == -1) b = 4;
    		gotoxy(x, y);
    		puts("   ");
    		if (b == 4) y = 22;
    		gotoxy(x, y - 3);
    		puts("-> ");
			y -= 3;
		}
		else if (((c >= 65 && c <= 97) || (c >= 97 && c <= 122) || (c >= 48 && c <= 57) || (b == 3 && c == 46)) && (b == 0 || b == 1 || b ==2 || b == 3))
		{
			inputContent[b][handleIdx[b]] = c;
			handleIdx[b]++;
			printf("%s", inputContent[b]);
		}
		else if (b == 4 && c == 13)
		{
			int i, j = 0;
			n++;
			for (i = 0; i < 4; i++)
			{
				gotoxy(76, 7 + i * 3);
				printf("               ");
			}
			for (i = 0; i < 4; i++) 
			{
				if (inputContent[i][0] == 0)
				{
					gotoxy(76, 7 + i * 3);
					printf("(不可以为空哦!)");
					j++;
				}
			}
			if (j == 0)
			{
				int i;
				student stu;
				stu.id = str2int(inputContent[0]);
				for(i = 0; i < sizeof(inputContent[1]); i++)
				{
					stu.name[i] = inputContent[1][i];
				}
				stu.age = str2int(inputContent[2]);
				stu.score = str2int(inputContent[3]);
				int num = 0;
				student *stuP = &stu;
				if (a == 0)
				{
					if (p->next != NULL)
					{
						stuP->next = p->next;
						p = stuP;
					}
					else
					{
						head = p = stuP;
						stuP->next = NULL;
					}
				}
				else 
				{
					while (num < a - 1)
					{
						p = p->next;
						num++;
					}
					if (p->next->next != NULL)
					{
						stuP->next = p->next->next;
					}
					else
					{
						stuP->next = NULL;
					}
					p->next = stuP;
				}
				loopWrite(p);
				student newStu;
				newStu.id = 0;
				memset(newStu.name, 0, 20);
				newStu.age = 0;
				newStu.score = 0;
				handleTable(newStu, 0, 0);
			}
		}
		else if(c == 8)
		{
			memset(ctx, 0, 20);
			gotoxy(49, y);
			printf("                    ");
			gotoxy(49, y);
			handleIdx[b]--;
			if(handleIdx[b] < 0) handleIdx[b] = 0;
			strncpy(ctx, inputContent[b], handleIdx[b]);
			for(i = 0; i < 20; i++)
			{
				inputContent[b][i] = ctx[i];
			}
			printf("%s", inputContent[b]);
		}
		else if (c == 27)
		{
			break;
		}
		gotoxy(49, y);
		c = getch();
	}
	homeInterface();
}

// 根据条件（可多条件查询）过滤查询数据 并生成链表 
student *filter(student stu)
{
	student *head, *p, *newHead;
	head = readFiles();
	int flag[4] = {0}, flagBool = 0;
	if (stu.id != 0) 
	{
		flag[0] = 1;
		flagBool = 1;
	}
	if (stu.name[0] != '\0')
	{
		flag[1] = 1;
		flagBool = 1;
	}
	if (stu.age != 0) 
	{
		flag[2] = 1;
		flagBool = 1;
	}
	if (stu.score != 0) 
	{
		flag[3] = 1;
		flagBool = 1;
	}
	int i = 0, n = 0;
	int tag = 1;
	if (flagBool != 0)
	{
		while(head != NULL)           
	    {
	    	tag = 1;
	      	for(i = 0; i < 4; i++)
	    	{
	    		if (flag[i] == 1)
				{
					switch(i)
					{
						case 0:
							if (head->id != stu.id) tag = 0;
							break;
						case 1:
							if (strstr(head->name, stu.name) == NULL) tag = 0;
							break;
						case 2:
							if (head->age != stu.age) tag = 0;
							break;
						case 3:
							if (head->score != stu.score) tag = 0;
							break;
					}
				}
			}
			if (tag == 1) 
	    	{
	    		if (n == 0)
		    	{
			    	newHead = p = head;
				}
				else
				{
					p->next = head;
					p = p->next;
				}
	    		n++;
			}
			head = head->next;
	    }
	    if (n == 0) newHead = NULL;
		else p->next = NULL;
		return newHead;
	}
	else return readFiles();
}

// 链表排序  type 1：学号排序  2：年龄排序  3： 成绩排序 
student *sortChain(student *list, int type)
{
	if((list -> next == NULL) || (list -> next -> next == NULL)) return NULL;
    student *head, *prep1, *prep2, *p1, *p2, *premin, *min, *temp;
    int n = 0;
    head = list;
    for(prep1 = NULL, p1 = head; p1->next != NULL; prep1 = (n == 0 ? head : prep1->next), p1 = prep1->next, n++)
    {
        //保存最小节点
        premin = prep1;
        min = p1;
        for (prep2 = p1, p2 = prep2->next; p2 != NULL; prep2 = prep2->next, p2 = prep2->next)
        {
            if (type == 1 && min->id > p2->id)
            {
                premin = prep2;
                min = p2;
            }
            else if (type == 2 && min->age > p2->age)
            {
            	premin = prep2;
                min = p2;
			}
            else if (type == 3 && min->score > p2->score)
            {
            	premin = prep2;
                min = p2;
			}
        }
        if (p1 != min)
        {
            //一定要注意这个情况
            if (prep1 == NULL) 
			{
				if (p1->next == min)
				{
					temp = min->next;
					min->next = p1->next;
					p1->next = temp;
					head = min;
				} 
				else
				{
					temp = min->next;
					min->next = p1->next;
					premin->next = p1;
					p1->next = temp;
					head = min;
				}
			}
            else if(p1->next == min)
            {
                temp = min->next;
                prep1->next = min;
                min->next = p1;
                p1->next = temp;
            }
			else
			{
                temp = min->next;
                prep1->next = min;
                min->next = p1->next;
                premin->next = p1;
                p1->next = temp;
            }
        }
    }
    return head; 
}

// 表格操作：删除、修改、视图更新 
void handleTable(student stu, int type, int sortIdx)
{
	int line, a = 0, arrow = 5, n = 0, tag = 0, dir = 0;
	char c;
	student *head, *p;
	head = p = sortIdx == 0 ? filter(stu): sortChain(filter(stu), sortIdx);
	line = outputLine(head);
	if (head != NULL)
	{
		gotoxy(92, arrow);
		printf("->");
		gotoxy(100, arrow);
		printf("<-");
	}
	c = getch();
	while(1)
	{
		if (c == 80 && a <= line)
		{
			a++;
			if (a == line) a = 0;
			if (dir == 0)
			{
				gotoxy(92, arrow);
				printf("  ");
				gotoxy(100, arrow);
				printf("  ");
			}
			else 
			{
				gotoxy(101, arrow);
				printf("  ");
				gotoxy(109, arrow);
				printf("  ");
			}
			arrow += 2;
			if (a == 0) arrow = 5;
			if (dir == 0)
			{
				gotoxy(92, arrow);
				printf("->");
				gotoxy(100, arrow);
				printf("<-");
			}
			else 
			{
				gotoxy(101, arrow);
				printf("->");
				gotoxy(109, arrow);
				printf("<-");
			}
		}
		if (c == 72 && a >= 0)
		{
			a--;
			if (a == -1) a = line - 1;
			if (dir == 0)
			{
				gotoxy(92, arrow);
				printf("  ");
				gotoxy(100, arrow);
				printf("  ");
			}
			else 
			{
				gotoxy(101, arrow);
				printf("  ");
				gotoxy(109, arrow);
				printf("  ");
			}
			if (a == line - 1) arrow = 5 + 2 * line;
			arrow -= 2;
			if (dir == 0)
			{
				gotoxy(92, arrow);
				printf("->");
				gotoxy(100, arrow);
				printf("<-");
			}
			else 
			{
				gotoxy(101, arrow);
				printf("->");
				gotoxy(109, arrow);
				printf("<-");
			}
		}
		else if ((c == 75 || c == 77) && a >= 0 && a < line) 
		{
			if (dir == 0) dir = 1;
			else if (dir == 1) dir = 0;
			if (dir == 1)
			{
				gotoxy(92, arrow);
				printf("  ");
				gotoxy(100, arrow);
				printf("  ");
				gotoxy(101, arrow);
				printf("->");
				gotoxy(109, arrow);
				printf("<-");
			}
			else if (dir == 0)
			{
				gotoxy(101, arrow);
				printf("  ");
				gotoxy(109, arrow);
				printf("  ");
				gotoxy(92, arrow);
				printf("->");
				gotoxy(100, arrow);
				printf("<-");
			}
		}
		else if (c == 49 || c == 50 || c == 51)
		{
			handleTable(stu, 1, c - 48);
		} 
		else if (c == 13)
		{
			int num = 0;
			if (dir == 0)
			{
				if (a == 0)
				{
					if (p->next != NULL) head = p = p->next;
					else head = p = NULL;
				}
				else 
				{
					while (num < a - 1)
					{
						p = p->next;
						num++;
					}
					p->next = p->next->next;
				}
				loopWrite(head);
				handleTable(stu, 0, 0);
			}
			else
			{
				tag = 1;
				break;
			} 
		}
		else if (c == 27) break;
		c = getch();
	}
	if (type == 1 && tag != 1)
	{
		homeInterface();
	}
	else if (tag == 1)
	{
		student *fStu = findStu(head, a);
		reviseStu(head, a, fStu);
	}
	else
	{
		void queryStudent();
		queryStudent();
	}
}

// 增加学生	
void addStudent()
{
	system("cls");
	char c, inputContent[4][20] = {{0}};
	int b = 0, x = 39 , y = 7, handleIdx[5] = {0};
	printf("     --------------------------------------------------------------------------------------------------------------\n");
	printf("     |                                               增加学生                                                     |\n");
	printf("     --------------------------------------------------------------------------------------------------------------\n");
	printf("     |           请输入如下信息：                                                                                 |\n");
	printf("     |                                                                                                            |\n");
	printf("     |                                                                                                            |\n");
	printf("     |                                                                                                            |\n");
	printf("     |                                 ->  学号：                                                                 |\n");
	printf("     |                                           ￣￣￣￣￣￣￣￣￣￣                                             |\n");
	printf("     |                                                                                                            |\n");
	printf("     |                                     姓名：                                                                 |\n");
	printf("     |                                           ￣￣￣￣￣￣￣￣￣￣                                             |\n");
	printf("     |                                                                                                            |\n");
	printf("     |                                     年龄：                                                                 |\n");
	printf("     |                                           ￣￣￣￣￣￣￣￣￣￣                                             |\n");
	printf("     |                                                                                                            |\n");
	printf("     |                                     成绩：                                                                 |\n");
	printf("     |                                           ￣￣￣￣￣￣￣￣￣￣                                             |\n");
	printf("     |                                                                                                            |\n");
	printf("     |                                                 插入                                                       |\n");
	printf("     |                                                                                                            |\n");
	printf("     |                                                                                                            |\n");
	printf("     |                                                                                                            |\n");
	printf("     |                                                                                                            |\n");
	printf("     |                                                      ↑↓控制       ENTER  确认      ESC  返回             |\n");
	printf("     --------------------------------------------------------------------------------------------------------------\n");
	c = getch();
	gotoxy(49, y);
	int n = 0;
	while(1) {
		if (n > 0)
		{
			gotoxy(63, 19);
			printf("             ");
			gotoxy(49, y);
		}
		if ((c == 80 && b <= 5) || c == 13 && b != 4)
		{
			b++;
			if (b == 5) b = 0;
    		gotoxy(x, y);
    		puts("   ");
    		if (b == 0) y = 4;
    		gotoxy(x, y + 3);
    		puts("-> ");
			y += 3;
		}
		else if (c == 72 && b >= -1)
		{
			b--;
			if (b == -1) b = 4;
    		gotoxy(x, y);
    		puts("   ");
    		if (b == 4) y = 22;
    		gotoxy(x, y - 3);
    		puts("-> ");
			y -= 3;
		}
		else if (((c >= 65 && c <= 97) || (c >= 97 && c <= 122) || (c >= 48 && c <= 57) || (b == 3 && c == 46)) && (b == 0 || b == 1 || b ==2 || b == 3))
		{
			inputContent[b][handleIdx[b]] = c;
			handleIdx[b]++;
			printf("%s", inputContent[b]);
		}
		else if (b == 4 && c == 13)
		{
			int i, j = 0;
			n++;
			for (i = 0; i < 4; i++)
			{
				gotoxy(76, 7 + i * 3);
				printf("               ");
			}
			for (i = 0; i < 4; i++) 
			{
				if (inputContent[i][0] == 0)
				{
					gotoxy(76, 7 + i * 3);
					printf("(不可以为空哦!)");
					j++;
				}
			}
			if (j == 0)
			{
				int i;
				student stu;
				stu.id = str2int(inputContent[0]);
				for(i = 0; i < sizeof(inputContent[1]); i++)
				{
					stu.name[i] = inputContent[1][i];
				}
				stu.age = str2int(inputContent[2]);
				stu.score = str2int(inputContent[3]);
				writeFiles(stu);
				gotoxy(55, 19);
				printf("插入    （插入成功!）");
				clearForm();
				memset(inputContent, 0, sizeof(inputContent));
				memset(handleIdx, 0, sizeof(handleIdx));
			}
		}
		else if (c == 27)
		{
			break;
		}
		gotoxy(49, y);
		c = getch();
	}
	homeInterface();
}

// 删除学生 
void deleteStudent()
{
	student stu;
	stu.id = 0;
	memset(stu.name, 0, 20);
	stu.age = 0;
	stu.score = 0;
	handleTable(stu, 1, 0);
}

// 修改学生 
void changeStudent()
{
	student stu;
	stu.id = 0;
	memset(stu.name, 0, 20);
	stu.age = 0;
	stu.score = 0;
	handleTable(stu, 1, 0);
}	

// 查询学生 
void queryStudent()
{
	system("cls");
	student stu;
	char c, inputContent[4][20] = {{0}};
	int b = 0, x = 39 , y = 7, handleIdx[4] = {0};
	printf("     --------------------------------------------------------------------------------------------------------------\n");
	printf("     |                                               查询学生                                                     |\n");
	printf("     --------------------------------------------------------------------------------------------------------------\n");
	printf("     |           请选填查询信息：                                                                                 |\n");
	printf("     |                                                                                                            |\n");
	printf("     |                                                                                                            |\n");
	printf("     |                                                                                                            |\n");
	printf("     |                                 ->  学号：                       （选填）                                  |\n");
	printf("     |                                           ￣￣￣￣￣￣￣￣￣￣                                             |\n");
	printf("     |                                                                                                            |\n");
	printf("     |                                     姓名：                       （选填）                                  |\n");
	printf("     |                                           ￣￣￣￣￣￣￣￣￣￣                                             |\n");
	printf("     |                                                                                                            |\n");
	printf("     |                                     年龄：                       （选填）                                  |\n");
	printf("     |                                           ￣￣￣￣￣￣￣￣￣￣                                             |\n");
	printf("     |                                                                                                            |\n");
	printf("     |                                     成绩：                       （选填）                                  |\n");
	printf("     |                                           ￣￣￣￣￣￣￣￣￣￣                                             |\n");
	printf("     |                                                                                                            |\n");
	printf("     |                                                   查询                                                     |\n");
	printf("     |                                                                                                            |\n");
	printf("     |                                                                                                            |\n");
	printf("     |                                                                                                            |\n");
	printf("     |                                                                                                            |\n");
	printf("     |                                                      ↑↓控制       ENTER  确认      ESC  返回             |\n");
	printf("     --------------------------------------------------------------------------------------------------------------\n");
	c = getch();
	gotoxy(49, y);
	int flag = 1, tag = 0, dir = 0;
	while(1) {
		if ((c == 80 && b <= 5) || c == 13 && b != 4)
		{
			b++;
			if (b == 5) b = 0;
    		gotoxy(x, y);
    		puts("   ");
    		if (b == 0) y = 4;
    		gotoxy(x, y + 3);
    		puts("-> ");
			y += 3;
		}
		else if (c == 72 && b >= -1)
		{
			b--;
			if (b == -1) b = 4;
    		gotoxy(x, y);
    		puts("   ");
    		if (b == 4) y = 22;
    		gotoxy(x, y - 3);
    		puts("-> ");
			y -= 3;
		}
		else if (((c >= 65 && c <= 97) || (c >= 97 && c <= 122) || (c >= 48 && c <= 57) || (b == 3 && c == 46)) && (b == 0 || b == 1 || b ==2 || b == 3))
		{
			inputContent[b][handleIdx[b]] = c;
			handleIdx[b]++;
			printf("%s", inputContent[b]);
		}
		else if (b == 4 && c == 13)
		{
			if (flag == 1)
		 	{
		 		flag = 0;
		 		int i;
				stu.id = str2int(inputContent[0]);
				for(i = 0; i < sizeof(inputContent[1]); i++)
				{
					stu.name[i] = inputContent[1][i];
				}
				stu.age = str2int(inputContent[2]);
				stu.score = str2int(inputContent[3]);
				memset(inputContent, 0, sizeof(inputContent));
				memset(handleIdx, 0, sizeof(handleIdx));
				tag = 1;
				break;
			}
		}
		else if (c == 27) break;
		gotoxy(49, y);
		c = getch();
	}
	int a = 0, line;
	if (tag == 1) handleTable(stu, 0, 0);
	else homeInterface();
}

// 首页操作对应map 
void operationMap(int operationId)
{
	switch(operationId)
	{
		case 0:
			addStudent();
			break;
		case 1:
			deleteStudent();
			break;
		case 2:
			changeStudent();
			break;
		case 3:
			queryStudent();
			break;
		default: 
			break;
	}
}	
		
// 初始化函数 
void init() 
{
	// 隐藏光标 
	HideCursor();
	// 展示主界面
	homeInterface();
} 

int main()
{
	init();
	return 0;
}

