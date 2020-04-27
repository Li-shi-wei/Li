#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<time.h>
using namespace std;
void menu()
{
	printf("\t\t\t\t******************************************\n");
	printf("\t\t\t\t\t欢迎使用四则运算自动出题系统\n");
	printf("\t\t\t\t\t请按照系统所给提示进行操作\n");
	printf("\t\t\t\t******************************************\n");
}
int get_int(int MAX)    //获取整型随机数
{
	int a;
	a = (rand() % MAX) + 1;
	return a;
}
float get_float(int MAX)   //获取浮点型随机数
{
	float a;
	int b;
	a = (rand() % 100)*0.01;
	b = (rand() % MAX);
	a = a + b;
	return a;
}
char get_symbol(int x)   //获取运算符
{
	if (x == 1){    //获取+-中随机运算符
		int a;
		char result;
		a = (rand() % 2) + 1;
		if (a == 1)result = '+';
		if (a == 2)result = '-';
		return result;
	}
	if (x == 2){      //获取*/中随机运算符
		int a;
		char result;
		a = (rand() % 2) + 1;
		if (a == 1)result = '*';
		if (a == 2)result = '/';
		return result;
	}
	if (x == 3){          //获取+-*/中随机运算符
		int a;
		char result;
		a = (rand() % 4) + 1;
		if (a == 1)result = '+';
		if (a == 2)result = '-';
		if (a == 3)result = '*';
		if (a == 4)result = '/';
		return result;
	}
}
int math(int operate,int symbols, int int_float, int out, int num, int MAX)  //operate为选择的运算符，1为加减，2为乘除，3为混合运算
{																		//symbol为是否带有括号，1为带括号，2为不带
	int flag;															//int_float为选择小数或小数，1为小数，2为整数
	FILE *fp;															//out为输出方式选择，1为输出到文件，2为不输出到文件
	if (out == 1)														//num为出题数量，MAX为运算中的最大数值
	{
		fp = fopen("d:\\math.txt", "w");
	}
	if (int_float == 1){
		for (int i = 0; i < num; i++)
		{
			float data1, data2, data3;
			char symbol1, symbol2;
			data1 = get_float(MAX);
			data2 = get_float(MAX);
			data3 = get_float(MAX);
			symbol1 = get_symbol(operate);
			symbol2 = get_symbol(operate);
			flag = (rand() % 2) + 1;   //flag为选择括号位置，1为前两位数据加括号，2为后两位数据加括号
			if (symbols == 1)
			{
				if (flag == 1)  //前两位数据加括号
				{
					printf("(%.2f%c%.2f)%c%.2f=\n", data1, symbol1, data2, symbol2, data3);
					if (out==1)   //输出到文件
						fprintf(fp,"(%.2f%c%.2f)%c%.2f=\n", data1, symbol1, data2, symbol2, data3);
				}
				if(flag==2)  //后两位数据加括号
				{
					printf("%.2f%c(%.2f%c%.2f)=\n", data1, symbol1, data2, symbol2, data3);
					if (out==1)     //输出到文件
						fprintf(fp,"%.2f%c(%.2f%c%.2f)=\n", data1, symbol1, data2, symbol2, data3);
				}
			}
			if (symbols==2)     //不带括号
			{
					printf("%.2f%c%.2f%c%.2f=\n", data1, symbol1, data2, symbol2, data3);
					if (out==1)    //输出到文件
						fprintf(fp,"%.2f%c%.2f%c%.2f=\n", data1, symbol1, data2, symbol2, data3);
			}

		}
		if (out == 1)
			fclose(fp);   //如果选择的输出到文件，需要关闭文件
	}
	if (int_float == 2){
		for (int i = 0; i < num; i++)
		{
			int data1, data2, data3;
			char symbol1, symbol2;
			data1 = get_int(MAX);
			data2 = get_int(MAX);
			data3 = get_int(MAX);
			symbol1 = get_symbol(operate);
			symbol2 = get_symbol(operate);
			flag = (rand() % 2) + 1;
			if (symbols == 1)  //带括号
			{
				if (flag == 1)  //前两位数据间加括号
				{
					printf("(%d%c%d)%c%d=\n", data1, symbol1, data2, symbol2, data3);
					if (out == 1)   //输出到文件
						fprintf(fp, "(%d%c%d)%c%d=\n", data1, symbol1, data2, symbol2, data3);
				}
				if (flag==2)   //后两位数据加括号
				{
					printf("%d%c(%d%c%d)=\n", data1, symbol1, data2, symbol2, data3);
					if (out == 1)   //输出到文件
						fprintf(fp, "%d%c(%d%c%d)=\n", data1, symbol1, data2, symbol2, data3);
				}
			}
			if (symbols==2)   //不带括号
			{
					printf("%d%c%d%c%d=\n", data1, symbol1, data2, symbol2, data3);
					if (out == 1)    //输出到文件
						fprintf(fp, "%d%c%d%c%d=\n", data1, symbol1, data2, symbol2, data3);
			}

		}
		if (out == 1)  //如果选择的输出到文件，此时需要关闭文件
			fclose(fp);
	}
	return 0;
}
int main()
{
	system("color 0B");
	int loop;  //定义的是否重新出题，1为重新出题，2为否
	srand((unsigned)time(NULL));
	while (1)
	{
		menu();
		int num;
		cout << "请输入题目个数：";
		while (1){
			cin >> num;
			if (num <= 0 || num > 200)
				cout << "输入错误，请重新输入：";
			else
				break;
		}
		int MAX;
		cout << "请输入参与运算的最大数：";
		while (1){
			cin >> MAX;
			if (MAX < 0 || MAX>200)
				cout << "数值过大或过小，请重新输入：";
			else
				break;
		}
		int int_float;
		cout << "请输入是否带小数，1为是，2为否：";
		while (1){
			cin >> int_float;
			if (int_float != 1 && int_float != 2)
				cout << "输入错误，请重新输入：";
			else
				break;
		}
		int operate;
		cout << "请输入选择的运算符，1为加减，2为乘除,3为混合运算: ";
		while (1){
			cin >> operate;
			if (operate != 1 && operate != 2 && operate != 3)
				cout << "输入错误，请重新输入：";
			else
				break;
		}
		int symbols;
		cout << "请选择是否带有括号，1为是，2为否: ";
		while (1){
			cin >> symbols;
			if (symbols != 1 && symbols != 2)
				cout << "输入错误，请重新输入：";
			else
				break;
		}
		int out;
		cout << "请选择是否输出到文件，1为是，2为否: ";
		while (1){
			cin >> out;
			if (out != 1 && out != 2)
				cout << "输入错误，请重新输入：";
			else
				break;
		}
		math(operate, symbols, int_float, out, num, MAX);
		system("pause");
		cout << "是否重新生成题目，1为是，2为否：";
		while (1)
		{
			cin >> loop;
			if (loop != 1 && loop != 2)
				cout << "输入错误，请重新输入：";
			else
				break;
		}
		if (loop == 2)
		{
			cout << "\n欢迎在此使用本系统，再见！\n";
			break;
		}
		if (loop == 1)
			system("cls");
	}
}