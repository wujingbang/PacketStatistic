#include <iostream>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <iomanip>
#include <sstream>
#include <fstream>
using namespace std;
#define NODE_NUM 6
#define LINE_NUM 500

void deal_lastnode();
void deal_allnode(char* pre);
void flowrate(char* pre, int average_time);
void flowrate_node(char* pre, int node,  int average_time);
void jamain(){
//	deal_lastnode();
//	deal_allnode("C:\\Users\\wu\\Desktop\\实验处理\\20150409-epidemic五跳断路\\新建文件夹");
//	flowrate("C:\\Users\\wu\\Desktop\\实验处理\\dtn四跳直线\\新建文件夹", 7);
	flowrate_node("C:\\Users\\wu\\Desktop\\实验处理\\20150409-epidemic五跳断路\\新建文件夹", 4, 7);
	system("PAUSE");
}

void deal_lastnode(){
	ofstream foutp("C:\\Users\\wu\\Desktop\\实验处理\\20150321-epidemic五跳断路-较差\\新建文件夹\\packet-5out.txt");
	FILE* fout_over3;
	FILE* fout_pay3;
	fout_over3 = fopen("C:\\Users\\wu\\Desktop\\实验处理\\20150321-epidemic五跳断路-较差\\新建文件夹\\overload_5.txt","r");
	fout_pay3 = fopen("C:\\Users\\wu\\Desktop\\实验处理\\20150321-epidemic五跳断路-较差\\新建文件夹\\payload_5.txt", "r");

	double data[400];
	memset(data, 0, 400*sizeof(double));
	int time1;
	double data1;
	int time2;
	double data2;
	while(1){
		int flag1 = fscanf(fout_over3,"%d,%lf", &time1, &data1);
		int flag2 = fscanf(fout_pay3,"%d,%lf", &time2, &data2);
		
		if (flag1 == EOF && flag2 == EOF)
		{
			break;
		}
		if (flag1 != EOF)
		{
			data[time1] += data1;
		} 
		if (flag2 != EOF) {
			data[time2] += data2;
		}
	}//while
	for (int i =1; i<400; i++)
	{
		foutp<<setw(3)<<i<<","<<data[i]<<endl;
	}
	
}

void deal_allnode(char* pre){

	char* prefix = (char*)malloc(100);
	memset(prefix,0,100);
	strcat(prefix, pre);

	ofstream fout_over(strcat(prefix, "\\overload.txt"));
	ofstream fout_pay(strcat(prefix, "\\pay.txt"));
	FILE* fin_overload[NODE_NUM+1];
	FILE* fin_payload[NODE_NUM+1];
	for (int i=1; i <= NODE_NUM; i++)
	{
		memset(prefix,0,100);
		strcat(prefix, pre);
		strcat(prefix, "\\overload_");
		char tmp[5] ;
		strcat(prefix, itoa(i, tmp, 10));
		strcat(prefix, ".txt");
		fin_overload[i] = fopen(prefix, "r");

		memset(prefix,0,100);
		strcat(prefix, pre);
		strcat(prefix, "\\payload_");
		memset(tmp,0,5);
		strcat(prefix, itoa(i, tmp, 10));
		strcat(prefix, ".txt");
		fin_payload[i] = fopen(prefix, "r");
	}

	double data_o[LINE_NUM];
	memset(data_o, 0, LINE_NUM*sizeof(double));
	double data_p[LINE_NUM];
	memset(data_p, 0, LINE_NUM*sizeof(double));
	int time_o1;
	double data_o1;
	int time_p1;
	double data_p1;

	for (int i=1; i<=NODE_NUM; i++)
	{
		while(EOF != fscanf(fin_overload[i],"%d,%lf", &time_o1, &data_o1)){
			data_o[time_o1] += data_o1;
		}
		while(EOF != fscanf(fin_payload[i],"%d,%lf", &time_p1, &data_p1)){
			data_p[time_p1] += data_p1;
		}
	}

	
	int j=0;
	for (int i =1; i<LINE_NUM; i++)
	{
		if (i>=2)
		{
			data_o[i]+=data_o[i-1];
		}
		cout<<setw(3)<<i<<" "<<data_o[i]<<endl;
		if (j++>290)
		{
			system("PAUSE");
			j=0;
		}
	}
	system("PAUSE");
	for (int i =1; i<LINE_NUM; i++)
	{
		if (i>=2)
		{
			data_p[i]+=data_p[i-1];
		}
		cout<<setw(3)<<i<<" "<<data_p[i]<<endl;
		if (j++>290)
		{
			system("PAUSE");
			j=0;
		}
	}
	

}

void flowrate(char* pre, int average_time){
	char* prefix = (char*)malloc(100);
	memset(prefix,0,100);
	strcat(prefix, pre);
	
	ofstream fout_over(strcat(prefix, "\\overload.txt"));
	ofstream fout_pay(strcat(prefix, "\\pay.txt"));
	FILE* fin_overload[NODE_NUM+1];
	FILE* fin_payload[NODE_NUM+1];
	for (int i=1; i <= NODE_NUM; i++)
	{
		memset(prefix,0,100);
		strcat(prefix, pre);
		strcat(prefix, "\\overload_");
		char tmp[5] ;
		strcat(prefix, itoa(i, tmp, 10));
		strcat(prefix, ".txt");
		fin_overload[i] = fopen(prefix, "r");

		memset(prefix,0,100);
		strcat(prefix, pre);
		strcat(prefix, "\\payload_");
		memset(tmp,0,5);
		strcat(prefix, itoa(i, tmp, 10));
		strcat(prefix, ".txt");
		fin_payload[i] = fopen(prefix, "r");
	}

	double data_o[LINE_NUM];
	memset(data_o, 0, LINE_NUM*sizeof(double));
	double data_p[LINE_NUM];
	memset(data_p, 0, LINE_NUM*sizeof(double));
	int time_o1;
	double data_o1;
	int time_p1;
	double data_p1;

	for (int i=1; i<=NODE_NUM; i++)
	{
		while(EOF != fscanf(fin_overload[i],"%d,%lf", &time_o1, &data_o1)){
			data_o[time_o1] += data_o1;
		}
		while(EOF != fscanf(fin_payload[i],"%d,%lf", &time_p1, &data_p1)){
			data_p[time_p1] += data_p1;
		}
	}
/*
	for (int i =1; i<LINE_NUM; i++)
	{
		cout<<setw(3)<<i<<" "<<data_o[i]<<endl;
	}
	system("PAUSE");
	for (int i =1; i<LINE_NUM; i++)
	{
		cout<<setw(3)<<i<<" "<<data_p[i]<<endl;
	}
*/
	for (int i =average_time; i<LINE_NUM; i+=average_time)
	{
		for (int j=1; j<average_time; j++)
		{
			data_o[i] += data_o[i-j];

		}
		cout<<setw(3)<<i<<" "<<(data_o[i]/(double)average_time)<<endl;
	}
	system("PAUSE");
	for (int i =average_time; i<LINE_NUM; i+=average_time)
	{
		for (int j=1; j<average_time; j++)
		{
			data_p[i] += data_p[i-j];

		}
		cout<<setw(3)<<i<<" "<<(data_p[i]/(double)average_time)<<endl;
	}
}

void flowrate_node(char* pre, int node, int average_time) {
	FILE* fin_overload;
	FILE* fin_payload;
	char* prefix = (char*)malloc(100);
	memset(prefix,0,100);

		strcat(prefix, pre);
		strcat(prefix, "\\overload_");
		char tmp[5] ;
		strcat(prefix, itoa(node, tmp, 10));
		strcat(prefix, ".txt");
		fin_overload = fopen(prefix, "r");

		memset(prefix,0,100);
		strcat(prefix, pre);
		strcat(prefix, "\\payload_");
		memset(tmp,0,5);
		strcat(prefix, itoa(node, tmp, 10));
		strcat(prefix, ".txt");
		fin_payload = fopen(prefix, "r");

	double data_o[LINE_NUM];
	memset(data_o, 0, LINE_NUM*sizeof(double));
	double data_p[LINE_NUM];
	memset(data_p, 0, LINE_NUM*sizeof(double));
	int time_o1;
	double data_o1;
	int time_p1;
	double data_p1;

//		while(EOF != fscanf(fin_overload,"%d,%lf", &time_o1, &data_o1)){
//			data_o[time_o1] += data_o1;
//		}
		while(EOF != fscanf(fin_payload,"%d,%lf", &time_p1, &data_p1)){
			data_o[time_p1] += data_p1;
		}

	for (int i =average_time; i<LINE_NUM; i+=average_time)
	{
			for (int j=1; j<average_time; j++)
			{
				data_o[i] += data_o[i-j];
				
			}
		cout<<setw(3)<<i<<" "<<(data_o[i]/(double)average_time)<<endl;
	}

}