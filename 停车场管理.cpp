#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<time.h>
#define MAX_STOP 3
#define price 0.05
typedef struct NODE   //车辆信息结构体定义
{
	int timein;
	int timeout;
	char num[10];
};
typedef struct Sqstack  //栈
{
	NODE data[20];
	int length;
}Sqtack;
typedef struct QNODE  //队列节点
{
	NODE data;
	QNODE *next;
}QNODE, *QPT;
typedef struct Linkqueen  //队列
{
	QPT front;
	QPT rear;
	int len;
}Linkqueen;

void menu(Sqstack &S, Linkqueen &Q, int MAX_stop, float DJ)    //主界面显示函数
{
	printf("\t\t\t\t*******************目前停车场状况***********************\n");
	printf("\t\t\t\t 停车场共有%d个车位,当前停车场共有%d辆车,等候区共有%d辆车\n",
		MAX_stop, S.length + 1, Q.len);
	printf("\t\t\t\t********************************************************\n");
	printf("\t\t\t\t--------------Welcome to Ep's Car Parking---------------\n");
	printf("\t\t\t\t*                                                      *\n");
	printf("\t\t\t\t*                   1.进入停车场停车                   *\n");
	printf("\t\t\t\t*                   2.从停车场离开                     *\n");
	printf("\t\t\t\t*                   3.停车场信息显示                   *\n");
	printf("\t\t\t\t*                   4.便道信息显示                     *\n");
	printf("\t\t\t\t*                   5.退出管理系统                     *\n");
	printf("\t\t\t\t*收费标准：本停车场按照%.0f元/小时计费，望周知            *\n", DJ);
	printf("\t\t\t\t*                                                      *\n");
	printf("\t\t\t\t*------------------------------------------------------*\n");
	printf("\t\t\t\t---------Press key(1/2/3/4/5) to run program------------\n");
	printf("\n");
	printf("\n");
}
void InitS(Sqstack &S)   //初始化栈
{

	S.length = -1;
}
void push(Sqstack &S, NODE car)   //进栈
{
	S.length++;
	S.data[S.length] = car;
}
int SIsempty(Sqstack &S)   //判断栈是否为空
{
	if (S.length == 0)
		return 1;
	else
		return 0;
}
void pop(Sqstack &S, NODE &CAR)   //出栈
{
	CAR = S.data[S.length];
	S.length--;
}
void InitQ(Linkqueen &Q)   //初始化队列
{
	Q.front = new QNODE;
	Q.rear = Q.front;
	Q.front->next = NULL;
	Q.len = 0;
}
int EN(Linkqueen &Q, NODE car)   //入队
{
	QPT p;
	p = new QNODE;
	p->data = car;
	p->next = NULL;
	Q.rear->next = p;
	Q.rear = p;
	Q.len++;
	return 1;
}
int OUT(Linkqueen &Q, NODE &CAR)  //出队并返回车辆信息给CAR
{
	if (Q.front == Q.rear) return 0;
	QPT p;
	p = Q.front->next;
	CAR = p->data;
	Q.front->next = p->next;
	if (Q.rear == p) Q.rear = Q.front;
	free(p);
	Q.len--;
	return 1;

}
int QIsempty(Linkqueen &Q)    //队列是否为空
{
	if (Q.front == Q.rear)
		return 1;
	else
		return 0;
}

int read(Sqstack &S, Linkqueen &Q, int MAX_stop)  //读取文件
{
	FILE *fp;
	int i = 0;
	if ((fp = fopen("d:\\car.txt", "r")) == NULL)
	{
		printf("文件打开失败,将创建文件存储停车信息！\n");
		return 0;
	}
	else
	{
		NODE car;
		for (i = 0; !feof(fp); i++)
		{
			if (S.length < MAX_stop - 1)
			{
				fscanf(fp, "%s %d %d\n", &S.data[i].num, &S.data[i].timein, &S.data[i].timeout);
				S.length++;
			}
			else
			{
				fscanf(fp, "%s %d %d\n", &car.num, &car.timein, &car.timeout);
				EN(Q, car);
			}
		}
		return 0;
	}
	fclose(fp);
}

int write(Sqstack &S, Linkqueen &Q, int MAX_stop)     //写入文件
{
	FILE *fp;
	int i = 0, k = 0;
	if ((fp = fopen("d:\\car.txt", "w")) == NULL)
	{
		printf("文件打开失败！\n");
		return 0;
	}
	else
	{
		if (S.length <= MAX_stop - 1 && Q.len == 0)
		{
			for (i = 0; i <= S.length; i++)
			{
				fprintf(fp, "%s %d %d\n", S.data[i].num, S.data[i].timein, S.data[i].timeout);
			}
		}
		if (S.length == MAX_stop - 1 && Q.len>0)
		{
			QPT p = Q.front;
			for (k = 0; k <= S.length; k++)
			{
				fprintf(fp, "%s %d %d\n", S.data[k].num, S.data[k].timein, S.data[k].timeout);
			}
			for (int j = 0; j < Q.len; j++)
			{
				fprintf(fp, "%s %d %d\n", p->next->data.num, p->next->data.timein, p->next->data.timeout);
				p = p->next;
			}
		}
	}
	fclose(fp);
	return 0;
}


int park(Sqstack &S, Linkqueen &Q, int MAX_stop)               //汽车进入停车场
{

	char ch[10];
	printf("请输入即将停车的车牌号：");
	scanf("%s", &ch);
	int i = S.length;
	while (i != -1)
	{
		if (0 == strcmp(S.data[i].num, ch))
		{
			printf("输入有误，此汽车已存在！\n");
			return 1;
		}
		i--;
	}
	QPT p = Q.front;
	int j = Q.len;
	while (j>0)
	{
		if (0 == strcmp(p->next->data.num, ch))
		{
			printf("输入有误，此汽车已存在！\n");
			return 1;
		}
		p = p->next;
		j--;
	}
	NODE car;
	strcpy(car.num, ch);
	if (S.length == MAX_stop - 1)
	{
		EN(Q, car);
		printf("停车位已满，牌照为%s的车辆将停入便道上第%d个位置\n", car.num, Q.len);
		write(S, Q, MAX_stop);
		return 1;
	}
	else
	{
		time_t t1;
		long int t = time(&t1);			// 记录停入时间
		char* t2;						// 将当前时间转换成字符串 
		t2 = ctime(&t1);
		car.timein = t;
		push(S, car);
		printf("牌照为%s的车辆已经停入停车场第%d个位置,停车时间为%s\n", car.num, S.length + 1, t2);
		write(S, Q, MAX_stop);
		return 1;
	}
}


int leave(Sqstack &S, Linkqueen &Q, Sqstack &S2, int MAX_stop, float DJ)    //汽车离开停车场
{
	int flag = -1; int biaozhi;
	char ch[10];
	printf("请输入即将离开的车牌号：");
	scanf("%s", &ch);
	int i = S.length;
	while (i != -1)
	{
		if (0 == strcmp(S.data[i].num, ch))           //汽车在停车场内；flag=1在便道，flag=0
		{
			flag = 1;
			biaozhi = i;
			break;
		}
		i--;
	}

	QPT p = Q.front;
	while (flag != 1 && Q.len>0)
	{
		if (0 == strcmp(p->data.num, ch))
		{
			flag = 0;
			break;
		}
		p = p->next;
	}
	NODE car; NODE car2;
	if (flag == 1)
	{
		                                                 //从停车场离开


		time_t t3;
		t3 = S.data[i].timein;
		char* t4;
		t4 = ctime(&t3);


		printf("牌照为%s的汽车已离开\n停车时间为：%s", S.data[biaozhi].num,t4);

		time_t t1;
		long int t = time(&t1);
		S.data[biaozhi].timeout = t;     // 记录离开时间
		char* t2;
		t2 = ctime(&t1);
		printf("停车时长为：%d时%d分%d秒\n", (S.data[biaozhi].timeout - S.data[biaozhi].timein+3600) / 3600, ((S.data[biaozhi].timeout - S.data[biaozhi].timein+3600) % 3600) / 60, ((3600+S.data[biaozhi].timeout - S.data[biaozhi].timein) % 3600) % 60);
		printf("应收取费用为：%.0f元\n", DJ / 3600 * (S.data[biaozhi].timeout - S.data[biaozhi].timein + 3600));
		printf("开票时间为：%s", t2);
		int j = S.length;
		while (j != i)
		{
			pop(S, car2);
			j--;
			push(S2, car2);
		}
		pop(S, car2);
		while (S2.length != -1)
		{
			pop(S2, car2);
			push(S, car2);
		}

		while (S.length<MAX_stop - 1 && Q.len>0)
		{
			NODE CAR;
			OUT(Q, CAR);
			time_t t1;
			long int t = time(&t1);			// 记录进场时间
			char* t2;
			t2 = ctime(&t1);
			CAR.timein = t1;
			push(S, CAR);
			printf("牌照为%s的车辆已经从便道驶入停车场第%d个位置,停车时间为%s\n", CAR.num, S.length + 1, t2);
		}
		write(S, Q, MAX_stop);
	}
	else if (flag == 0)
	{                                 //从便道离开
		QPT q;
		q = Q.front;
		while (q->next != p)
		{
			q = q->next;
		}
		q->next = p->next;
		printf("牌照为%s的车辆将从便道离开，不收费\n", ch);
		Q.len--;
		write(S, Q, MAX_stop);
	}
	else
		printf("输入错误，不存在该车\n");
	return 1;
}
int Tdisplay(Sqstack &S, float DJ)   //停车场信息显示
{
	int i = S.length;
	if (-1 == i)
		printf("停车场目前为空\n");
	time_t t1;
	long int t = time(&t1);
	long int t9 = t + 3600;
	char* t2;
	printf("\t车牌号\t\t停车时间\t\t\t\t当前所需支付金额\t停放位序\n");
	while (i != -1)
	{
		time_t t2;
		t2 = S.data[i].timein;
		char* t3;
		t3 = ctime(&t2);
		printf("\t%s\t%s\t\t\t\t\t\t\t\t%.0f元\t\t\t第%d个\n", S.data[i].num,t3, DJ / 3600 * (t9 - S.data[i].timein ), i + 1);
		i--;
	}
	return 1;
}

int Bdisplay(Linkqueen &Q)    //便道信息显示
{
	QPT p; int i = 1;
	p = Q.front;
	if (Q.len == 0)
		printf("便道上没有车辆\n");
	else
	{
		int j = Q.len;
		printf("\t车牌号\t\t停放位序\n");
		while (j != 0)
		{
			printf("\t%s\t第%d个\n", p->next->data.num, i++);
			p = p->next;
			j--;

		}
	}
	return 1;
}


int main()
{
	system("color 0B");
	int MAX_stop;                                     //停车场车位数目
	float DJ;                                         //每小时的停车费用
	printf("请输入停车位最大数量\n");
	scanf("%d", &MAX_stop);
	printf("请输入停车场每小时的费用\n");
	scanf("%f", &DJ);
	Sqstack S, S2;
	Linkqueen Q;
	InitS(S);
	InitS(S2);
	InitQ(Q);
	read(S, Q, MAX_stop);
	int i;
	while (1)
	{
		system("cls");             //清屏
		menu(S, Q, MAX_stop, DJ);
		printf("请输入要选择的操作的序号:");
		scanf("%d", &i);
		switch (i)
		{
		case 1:{park(S, Q, MAX_stop); system("pause"); break; }
		case 2:{leave(S, Q, S2, MAX_stop, DJ); system("pause"); break; }
		case 3:{Tdisplay(S, DJ); system("pause"); break; }
		case 4:{Bdisplay(Q); system("pause"); break; }
		case 5:{printf("欢迎再次使用本系统···\n"); exit(0); }
		default:{printf("输入错误，请输入列表中存在的序号\n"); system("pause"); break; }
		}
	}

	return 1;
}
