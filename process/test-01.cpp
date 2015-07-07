#include <iostream>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <iomanip>
#include <sstream>
#include <fstream>

using namespace std;

void bamain()
{	
	int count = 0;
	int count0 = 0;
	double sum = 0.0;
	//	FILE * fp = fopen("C:\\Users\\wu\\Desktop\\实验处理\\aodv运行30s，断路80s\\packet-3.txt", "r");
	ifstream fin("C:\\Users\\wu\\Desktop\\实验处理\\20150409-epidemic五跳断路\\packet-15.txt", ios::in);
	ofstream fout_over3("C:\\Users\\wu\\Desktop\\实验处理\\20150409-epidemic五跳断路\\新建文件夹\\overload_5.txt");
	ofstream fout_pay3("C:\\Users\\wu\\Desktop\\实验处理\\20150409-epidemic五跳断路\\新建文件夹\\payload_5.txt");
	ofstream* fp = &fout_over3;
	if (fin == NULL)
	{
		cout<<"open failed!"<<endl;
	}
	string line;
	int flag = 1;
	int eclapse = 0;
	while(getline(fin,line,'\n'))
	{
		count0++;
//		cout<<line<<endl;
		if (strstr (const_cast<char*>(line.data()), "payload") != NULL)
		{
			fp->close();
			sum=0.0;
			fp = &fout_pay3;
		}
		char* timestr = strtok(const_cast<char*>(line.data()),",");
		char* datastr;
		datastr = strtok(NULL,",");

		if (flag&& datastr && timestr )
		{
			unsigned int time =  atoi(timestr);
			eclapse = time - 1;
			flag = 0;
		}
		if (datastr && timestr)
		{
			unsigned int time =  atoi(timestr);
//			sum += ((double)atoi(datastr))/1024.0;
			double data = ((double)atoi(datastr))/1024.0;
			time -= eclapse;
			cout.setf(ios::left);
//			(*fp)<<time << "," << sum <<endl;
			(*fp)<<time << "," << data <<endl;
/*			if(count++ >=250){
				count = 0;
				system("PAUSE");
			}*/
		}
//		cout<<count0<<endl;

	}
	fin.clear();
	fin.close();
	
//	system("PAUSE");
}

