#include<stdio.h>
#include<sstream>
#include<ctime>
#include<stdlib.h>
#include<fstream>
#include<string>
#include<iostream>
using namespace std;
string Week[7] = {"Mon.","Tues.","Wed.","Thur.","Fri.","Sat.","Sun."};
string Tag[10] = {"study","film","English","music","reading","chess","football","dance","programming","basketball"};
int FirstStuNo = 31502001;

string ToString(int val)/将int类型转换为string类型
{
    stringstream stream;
    stream << val;
    return stream.str();
}

int Rand(int num1,int num2)//生成num1到num2之间的随机数 
{
	int r;
	while(1)
	{
		r=rand()%num2;
		if(r>=num1) return r;
	}
}

int main()
{
	srand(time(NULL));
    int i,Stu,TLoop,TWeek,TStart,AppliDepart,AppliDepartNum,DepartNum,TagsNum,Tags,TagStart;
    string TString;
	ofstream fout("input_data.txt");
    if(fout)
    {
        fout<<"{"<<endl;
		fout<<"    \"students\": ["<<endl;
		for(Stu=0;Stu<300;Stu++)
		{
			fout<<"        {"<<endl;
			fout<<"            \"free_time\": ["<<endl;
			i=Rand(2,8); 
			for(TLoop=0;TLoop<i;TLoop++)
			{
				if(TLoop==0) TWeek=Rand(0,7);
				else TWeek=(TWeek+1)%7;
				TString=Week[TWeek];
			    TStart=Rand(8,22);
				TString+=ToString(TStart);
				TString+=":00~";
				TString+=ToString(Rand(TStart+1,24));
				TString+=":00\"";
				if(TLoop==i-1) 
					fout<<"                \""+TString<<endl;
				else
				fout<<"                \""+TString+","<<endl;
			}
			fout<<"            ],"<<endl;
			FirstStuNo++;
			fout<<"            \"student_no\":\"0"+ToString(FirstStuNo)+"\","<<endl;
			fout<<"            \"applications_department\": ["<<endl;
			i=Rand(1,6);
			for(AppliDepart=0;AppliDepart<i;AppliDepart++)
			{
				AppliDepartNum=Rand(1,21);
				if(AppliDepartNum<10)
				{
					if(AppliDepart==i-1)
					    fout<<"                \"D00"+ToString(AppliDepartNum)+"\""<<endl;
                    else
					    fout<<"                \"D00"+ToString(AppliDepartNum)+"\","<<endl;
				}
				else
				{
					if(AppliDepart==i-1)
					    fout<<"                \"D0"+ToString(AppliDepartNum)+"\""<<endl;
                    else
					    fout<<"                \"D0"+ToString(AppliDepartNum)+"\","<<endl;
				}
			}
			fout<<"            ],"<<endl;
			fout<<"            \"tags\": ["<<endl;
			i=Rand(2,10);
			for(Tags=0;Tags<i;Tags++)
			{
				if(Tags==0) 
				    TagStart=Rand(0,10);
				else
					TagStart=(TagStart+1)%10; 
				if(Tags==i-1)
				    fout<<"                \""+Tag[TagStart]+"\""<<endl;
				else
				fout<<"                \""+Tag[TagStart]+"\","<<endl;
			}
			fout<<"            ]"<<endl;
			if(Stu==299) 
			    fout<<"        }"<<endl;
			else
			    fout<<"        },"<<endl;
		}
		fout<<"    ],"<<endl;
		fout<<"    \"departments\": ["<<endl;
		for(DepartNum=1;DepartNum<=20;DepartNum++)
		{
			fout<<"        {"<<endl;
			fout<<"            \"event_schedules\": ["<<endl;
			i=Rand(2,8); 
			for(TLoop=0;TLoop<i;TLoop++)
			{
				if(TLoop==0) TWeek=Rand(0,7);
				else TWeek=(TWeek+1)%7;
				TString=Week[TWeek];
			    TStart=Rand(8,22);
				TString+=ToString(TStart);
				TString+=":00~";
				TString+=ToString(Rand(TStart+1,24));
				TString+=":00\"";
				if(TLoop==i-1) 
					fout<<"                \""+TString<<endl;
				else
				fout<<"                \""+TString+","<<endl;
			}
			fout<<"            ],"<<endl;
			fout<<"            \"member_limit\":"+ToString(Rand(10,16))+","<<endl;
			if (DepartNum<9)
			    fout<<"            \"department_no\": \"D00"+ToString(DepartNum)+"\","<<endl;
			else
			    fout<<"            \"department_no\": \"D0"+ToString(DepartNum)+"\","<<endl;
			fout<<"            \"tags\": ["<<endl;
			i=Rand(2,10);
			for(Tags=0;Tags<i;Tags++)
			{
				if(Tags==0) 
				    TagStart=Rand(0,10);
				else
					TagStart=(TagStart+1)%10; 
				if(Tags==i-1)
				    fout<<"                \""+Tag[TagStart]+"\""<<endl;
				else
				fout<<"                \""+Tag[TagStart]+"\","<<endl;
			}
			fout<<"            ]"<<endl;
			if(DepartNum==20) 
			    fout<<"        }"<<endl;
			else
			    fout<<"        },"<<endl;		
		}
		fout<<"    ]"<<endl;
		fout<<"}"<<endl;
    }
    fout.close();
    return 0;
}
