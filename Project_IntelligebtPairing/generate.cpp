#include<stdio.h>
#include<sstream>
#include<ctime>
#include<stdlib.h>
#include<fstream>
#include<string>
#include<iostream>
using namespace std;
string Week[7] = {"Mon.","Tues.","Wed.","Thur.","Fri.","Sat.","Sun."};
string Tag[10] = {"study","film","English","music","reading","chess",                              
"football","dance","programming","basketball"};                                                    //兴趣标签
int firstStuNo = 31502001;

string ToString(int val)                                                                           //将int类型转换为string类型
{
    stringstream stream;
    stream << val;
    return stream.str();
}

int Rand(int num1,int num2)                                                                       //生成num1到num2之间的随机数 
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
	srand(time(NULL));                                                                             //根据时间生成随机数使随机数尽量不重复，让数据更多样化
	int i,stu,                                                                                     //定义学生循环的变量
	tLoop,                                                                                         //定义循环生成时间的变量
	tWeek,                                                                                         //定义生成时间是星期几的变量
	tStart,                                                                                        //定义时间开始时间的变量
	appliDepart,                                                                                   //定义学生报的部门循环的变量
	appliDepartNum,                                                                                //定义学生报的部号
	depart,                                                                                        //定义部门循环的变量
	tags,                                                                                          //定义标签循环的变量
	tagStart;                                                                                      //定义开始标签的变量
    string tString;                                                                                //定义用来输出的字符串
	ofstream fout("input_data.txt");
    if(fout)
    {
        fout<<"{"<<endl;
		fout<<"    \"students\": ["<<endl;
		for(stu=0;stu<300;stu++)
		{
			fout<<"        {"<<endl;
			fout<<"            \"free_time\": ["<<endl;
			i=Rand(2,8);                                                                           
			for(tLoop=0;tLoop<i;tLoop++)
			{
				if(tLoop==0) tWeek=Rand(0,7);
				else tWeek=(tWeek+1)%7;
				tString=Week[tWeek];
			    tStart=Rand(8,22);                                                                 //活动开始时间限制在8点到22点
				tString+=ToString(tStart);
				tString+=":00~";
				tString+=ToString(Rand(tStart+1,24));                                              //活动结束时间限制在24点
				tString+=":00\"";
				if(tLoop==i-1) 
					fout<<"                \""+tString<<endl;
				else
				fout<<"                \""+tString+","<<endl;
			}
			fout<<"            ],"<<endl;
			firstStuNo++;
			fout<<"            \"student_no\":\"0"+ToString(firstStuNo)+"\","<<endl;
			fout<<"            \"applications_department\": ["<<endl;
			i=Rand(1,6);
			for(appliDepart=0;appliDepart<i;appliDepart++)
			{
				appliDepartNum=Rand(1,21);
				if(appliDepartNum<10)
				{
					if(appliDepart==i-1)
					    fout<<"                \"D00"+ToString(appliDepartNum)+"\""<<endl;
                    else
					    fout<<"                \"D00"+ToString(appliDepartNum)+"\","<<endl;
				}
				else
				{
					if(appliDepart==i-1)
					    fout<<"                \"D0"+ToString(appliDepartNum)+"\""<<endl;
                    else
					    fout<<"                \"D0"+ToString(appliDepartNum)+"\","<<endl;
				}
			}
			fout<<"            ],"<<endl;
			fout<<"            \"tags\": ["<<endl;
			i=Rand(2,10);
			for(tags=0;tags<i;tags++)
			{
				if(tags==0) 
				    tagStart=Rand(0,10);
				else
					tagStart=(tagStart+1)%10; 
				if(tags==i-1)
				    fout<<"                \""+Tag[tagStart]+"\""<<endl;
				else
				fout<<"                \""+Tag[tagStart]+"\","<<endl;
			}
			fout<<"            ]"<<endl;
			if(stu==299) 
			    fout<<"        }"<<endl;
			else
			    fout<<"        },"<<endl;
		}
		fout<<"    ],"<<endl;
		fout<<"    \"departments\": ["<<endl;
		for(depart=1;depart<=20;depart++)
		{
			fout<<"        {"<<endl;
			fout<<"            \"event_schedules\": ["<<endl;
			i=Rand(2,8); 
			for(tLoop=0;tLoop<i;tLoop++)
			{
				if(tLoop==0) tWeek=Rand(0,7);
				else tWeek=(tWeek+1)%7;
				tString=Week[tWeek];
			    tStart=Rand(8,22);
				tString+=ToString(tStart);
				tString+=":00~";
				tString+=ToString(Rand(tStart+1,24));
				tString+=":00\"";
				if(tLoop==i-1) 
					fout<<"                \""+tString<<endl;
				else
				fout<<"                \""+tString+","<<endl;
			}
			fout<<"            ],"<<endl;
			fout<<"            \"member_limit\":"+ToString(Rand(10,16))+","<<endl;
			if (depart<9)
			    fout<<"            \"department_no\": \"D00"+ToString(depart)+"\","<<endl;
			else
			    fout<<"            \"department_no\": \"D0"+ToString(depart)+"\","<<endl;
			fout<<"            \"tags\": ["<<endl;
			i=Rand(2,10);
			for(tags=0;tags<i;tags++)
			{
				if(tags==0) 
				    tagStart=Rand(0,10);
				else
					tagStart=(tagStart+1)%10; 
				if(tags==i-1)
				    fout<<"                \""+Tag[tagStart]+"\""<<endl;
				else
				fout<<"                \""+Tag[tagStart]+"\","<<endl;
			}
			fout<<"            ]"<<endl;
			if(depart==20) 
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
