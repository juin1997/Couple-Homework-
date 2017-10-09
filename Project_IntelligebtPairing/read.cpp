#include<stdio.h>
#include<sstream>
#include<list>
#include<string>
#include<cstring>
#include<fstream> 
#include<iostream>
#include<algorithm>
#include<set>
using namespace std;

typedef list<int> LISTINT;
typedef list<string> LISTSTRING;

string DepartmentMember[20][15];                                                                   //对应二十个部门，部门内部有零不输出，对应学号 
string unluckyStrudent [300];                                                                      //对应学号，为零不输出 
#include "cJSON.h"
#include "cJSON_Utils.h"

struct Student                                                                                     //定义学生结构体
{
	LISTSTRING FTDay;                                                                              //定义学生空闲时间是星期几
	LISTINT FTStart;                                                                               //定义学生空闲时间的开始时间   
	LISTINT FTEnd;                                                                                 //定义学生空闲时间的结束时间
	string StudentNo;                                                                              //定义学生的学号
	string ApliDepart[5];                                                                          //定义学生报的部门
	LISTSTRING Tag;                                                                                //定义学生的兴趣标签
};

struct Department                                                                                  //定义部门结构体
{
	LISTSTRING ESDay;                                                                              //定义部门活动时间是星期几
	LISTINT ESStart;                                                                               //定义部门活动时间的开始时间
	LISTINT ESEnd;                                                                                 //定义部门活动的结束时间
	int MemberLimit;                                                                               //定义部门人数限制
	string DepartNO;                                                                               //定义部门号
	LISTSTRING Tag;                                                                                //定义部门特点标签
};
Student stu[300];                                                                                  
Department dep[20];                                                                         

struct StudentScore
{
	double tagScore;
	double otherScore;
	int tag;
	string StudentNo;
};

int StringToInt(string s)
{
	stringstream ss;
	ss<<s;
	int i;
	ss>>i;
	return i;
}

bool cmp(StudentScore a,StudentScore b)
{
	if (a.tagScore == b.tagScore){
		return a.otherScore > b.otherScore;
	}
	else{
		return a.tagScore > b.tagScore;
	}
}

void GetTimeS(int i,string s)                                                                      //从学生空闲时间的字符串中获取星期几，开始和结束时间
{
	int k;
	int first=0;
	string tmp="";
	for(k=0;k<s.length();k++)
	{
		if(s[k]>64&&s[k]<123) tmp+=s[k];
		if(s[k]>47&&s[k]<58) tmp+=s[k];
		if(s[k]=='"')
		{
			stu[i].FTDay.push_back(tmp);
			tmp="";
		}
		if(s[k]==':')
		{
			if(first==0) stu[i].FTStart.push_back(StringToInt(tmp));
			else stu[i].FTEnd.push_back(StringToInt(tmp));
			first++;
			tmp="";
		}

	}
}

void GetTimeD(int i,string s)                                                                      //从部门活动时间的字符串中获取星期几，开始和结束时间
{
	int k;
	int first=0;
	string tmp="";
	for(k=0;k<s.length();k++)
	{
		if(s[k]>64&&s[k]<123) tmp+=s[k];
		if(s[k]>47&&s[k]<58) tmp+=s[k];
		if(s[k]=='"')
		{
			dep[i].ESDay.push_back(tmp);
			tmp="";
		}
		if(s[k]==':')
		{
			if(first==0) dep[i].ESStart.push_back(StringToInt(tmp));
			else dep[i].ESEnd.push_back(StringToInt(tmp));
			first++;
			tmp="";
		}

	}
}


int main()
{
	int i,j;
	string d;
    ifstream infile;
    infile.open("input_data.txt");                                                                 //打开输入文件
    string s;
	while(getline(infile,s))                                                                       //将文件中的内容全部转为字符串               
	{
		d=d+s;
	}
	cJSON* json = cJSON_Parse(d.c_str());                                                          //利用cJSON读取字符串里对应键值的数值
	if (json!=NULL)
	{
		cJSON* temp = cJSON_GetObjectItem(json, "students");                                       //读取学生的数据存入结构体数组       
		if (temp!=NULL)
		{
			i=0;
			int icount=cJSON_GetArraySize(temp);
			for(;i<icount;i++)
			{
				cJSON* students = cJSON_GetArrayItem(temp,i);
				if(students!=NULL)
				{
					cJSON* free_time=NULL;
					cJSON* student_no=NULL;
					cJSON* applications_department=NULL;
					cJSON* tags=NULL;
					free_time=cJSON_GetObjectItem(students,"free_time");
					student_no=cJSON_GetObjectItem(students,"student_no");
					applications_department=cJSON_GetObjectItem(students,"applications_department");
					tags=cJSON_GetObjectItem(students,"tags");
					if(student_no!=NULL) stu[i].StudentNo=student_no->valuestring;
					if(free_time!=NULL)
					{
						j=0;
						int jcount=cJSON_GetArraySize(free_time);
						for(;j<jcount;j++)
						{
							cJSON* free_timeItem=cJSON_GetArrayItem(free_time,j);
							if(free_timeItem!=NULL) GetTimeS(i,free_timeItem->valuestring);
						}
					}
					if(applications_department!=NULL)
					{
						j=0;
						int jcount=cJSON_GetArraySize(applications_department);
						for(;j<jcount;j++)
						{
							cJSON* applications_departmentItem=cJSON_GetArrayItem(applications_department,j);
							if(applications_departmentItem!=NULL) stu[i].ApliDepart[j]=applications_departmentItem->valuestring;
						}
					}
					if(tags!=NULL)
					{
						j=0;
						int jcount=cJSON_GetArraySize(tags);
						for(;j<jcount;j++)
						{
							cJSON* tagsItem=cJSON_GetArrayItem(tags,j);
							if(tagsItem!=NULL) stu[i].Tag.push_back(tagsItem->valuestring);
						}
					}
				}
			}
		}

		temp = cJSON_GetObjectItem(json, "departments");                                           //读取部门的数据存入结构体数组
		if(temp!=NULL)
		{
			int i=0;
			int icount=cJSON_GetArraySize(temp);
			for(;i<icount;i++)
			{
				cJSON* departments = cJSON_GetArrayItem(temp,i);
				if(departments!=NULL)
				{
					cJSON* event_schedules=NULL;
					cJSON* member_limit=NULL;
					cJSON* department_no=NULL;
					cJSON* tags=NULL;
					event_schedules=cJSON_GetObjectItem(departments,"event_schedules");
					member_limit=cJSON_GetObjectItem(departments,"member_limit");
					department_no=cJSON_GetObjectItem(departments,"department_no");
					tags=cJSON_GetObjectItem(departments,"tags");
					if(member_limit!=NULL) dep[i].MemberLimit=member_limit->valueint;
					if(department_no!=NULL) dep[i].DepartNO=department_no->valuestring;
					if(event_schedules!=NULL)
					{
						int j=0;
						int jcount=cJSON_GetArraySize(event_schedules);
						for(;j<jcount;j++)
						{
							cJSON* event_schedulesItem=cJSON_GetArrayItem(event_schedules,j);
							if(event_schedulesItem!=NULL) GetTimeD(i,event_schedulesItem->valuestring);
						}
					}
					if(tags!=NULL)
					{
						j=0;
						int jcount=cJSON_GetArraySize(tags);
						for(;j<jcount;j++)
						{
							cJSON* tagsItem=cJSON_GetArrayItem(tags,j);
							if(tagsItem!=NULL) dep[i].Tag.push_back(tagsItem->valuestring);
						}
					}
				}
			}
		}
	}
	//读取结束，临时变量stu数组！ 
	 StudentScore stu[20][300];
	 
//	stu[1].tagScore = 100;
//	stu[1].otherScore = 101111;
//	stu[2].tagScore = 100;
//	stu[2].otherScore = 101;
//	stu[0].tagScore = 103;
//	stu[0].otherScore = 10;
//	sort(stu,stu+3,cmp);
//	cout << stu[0].tagScore<< " "<< stu[1].tagScore<<" "<< stu[2].tagScore<<endl;
//	cout << stu[0].otherScore<< " "<< stu[1].otherScore<<" "<< stu[2].otherScore<<endl;


	return 0;
}