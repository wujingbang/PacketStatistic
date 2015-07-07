#include <iostream>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <iomanip>
#include <sstream>
#include <fstream>

using namespace std;
#define NODE_COUNT 5

void accumulate();
void accumulateFormFile(FILE *fp, double data[]);
void tmp2minus(char *fileStr1, char *fileStr2);
void tmp2average(char *fileStr1);

void main()
{
	tmp2minus("C://11.txt", "C://22.txt");
//	tmp2average("C://11.txt");
	system("PAUSE");
	
	double data[100];
	memset(data,0.0,100*sizeof(double));
	FILE *fp = NULL;
	for (int i=1; i<=NODE_COUNT; i++)
	{
		char* prefix = (char*)malloc(100);
		memset(prefix,0,100);
		strcat(prefix, "C://");
		char tmp[5] ;
		memset(tmp,0,5);
		strcat(prefix, itoa(i, tmp, 10));
		strcat(prefix, ".txt");
		fp = fopen(prefix, "r");
		accumulateFormFile(fp, data);
		system("PAUSE");
	}
	
//	accumulate();
	system("PAUSE");
}


void accumulateFormFile(FILE *fp, double data[]){
	
	double tmp[100];
	
	memset(tmp,0.0,100*sizeof(double));
	
		for (int i=0; EOF != fscanf(fp, "%lf", &tmp[i]); i++)
		{
			data[i] += tmp[i];
			cout<<data[i]<<endl;
		}
	
	
}

void accumulate(){
	double data[100];
	double tmp[100];
	memset(data,0.0,100*sizeof(double));
	memset(tmp,0.0,100*sizeof(double));
	for (int i=0; i<100; i++)
	{
		if (!scanf(	"%lf", &data[i]))
		{
			break;
		}
	}
	while(1){
		getchar();
		cout<<"input data2"<<endl;
		for (int i=0; i<100; i++)
		{
			if (!scanf(	"%lf", &tmp[i]))
			{
				break;
			}
		}
		cout<<"cal:"<<endl;


		for (int i=0; i<100; i++)
		{
			data[i]+=tmp[i];
			cout<<data[i]<<endl;
		}
		system("PAUSE");
	}
}
void file2cmd(){
	ifstream fin("C:\\Users\\wu\\Desktop\\实验处理\\aodv运行30s，断路80s\\iperf-数据.txt", ios::in);
	string line;
	while(getline(fin,line,'\n'))
	{
		cout<<line<<endl;
	}
	system("PAUSE");
}

void tmp2minus(char *fileStr1, char *fileStr2){
	double data1[100];
	double data2[100];
	memset(data1,0.0,100*sizeof(double));
	memset(data2,0.0,100*sizeof(double));
	int count = 0;

	FILE *fp1 = fopen(fileStr1,"r");
	FILE *fp2 = fopen(fileStr2,"r");
	for (int i=0; EOF != fscanf(fp1, "%lf", &data1[i]); i++)
	{
		count++;
	}
	for (int i=0; EOF != fscanf(fp2, "%lf", &data2[i]); i++)
	{
	}
	for (int i=0; i<=count; i++)
	{
		cout<<data1[i]-data2[i]<<endl;
	}

}

void tmp2average(char *fileStr1) {
	double data1[100];
	double sum = 0.0;
	memset(data1,0.0,100*sizeof(double));
	int count = 0;

	FILE *fp1 = fopen(fileStr1,"r");
	for (int i=0; EOF != fscanf(fp1, "%lf", &data1[i]); i++)
	{
		count++;
	}
	for (int i=0; i<100; i++)
	{
		sum+=data1[i];
	}
	cout<<count<<"'"<<sum/(double)count<<endl;
}