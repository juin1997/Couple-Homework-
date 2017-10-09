#include<stdio.h>
#include<sstream>
#include<list>
#include<string>
#include<cstring>
#include<fstream> 
#include<iostream>
using namespace std;

typedef list<int> LISTINT;
typedef list<string> LISTSTRING;

#include "cJSON.h"
#include "cJSON_Utils.h"

struct Student
{
	LISTSTRING FTDay;
	LISTINT FTStart;
	LISTINT FTEnd;
	string StudentNo;
	string ApliDepart[5];
	LISTSTRING Tag;
};

struct Department
{
	LISTSTRING ESDay;
	LISTINT ESStart;
	LISTINT ESEnd;
	int MemberLimit;
	string DepartNO;
	LISTSTRING Tag;
};
Student stu[300];
Department dep[20];

int StringToInt(string s)
{
	stringstream ss;
	ss<<s;
	int i;
	ss>>i;
	return i;
}


void GetTimeS(int i,string s)
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

void GetTimeD(int i,string s)
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
    infile.open("input_data.txt");
    string s;
	while(getline(infile,s))
	{
		d=d+s;
	}
	cJSON* json = cJSON_Parse(d.c_str());
	if (json!=NULL)
	{
		cJSON* temp = cJSON_GetObjectItem(json, "students");
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

		temp = cJSON_GetObjectItem(json, "departments");
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
	return 0;
}
