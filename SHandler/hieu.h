#pragma once
#ifndef FUNCTION_H
#define FUNCTION_H
#include<string.h>
#include<string>
#include<ctime>
#include<iostream>
#include<fstream>
using namespace std;

const int monthDays[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
//Creat struct user
struct User
{
	string username;
	string full_name;
	string email;
	string mobile_phone;
	int type;
	string password;
	string Class;
	User* pNext;
	void changepass();
}; 

//________date_________
struct Date
{
	int day, month, year;
};

//________time_______
struct Time
{
	int hour, minute;

};

//______creat struct score_________
struct Score
{
	string studentid;
	float mid, lab, final;
	Score* pNext;
};
struct Student
{
	string id;
	string fullname;
	Student *pNext;
};
struct Class
{
	string classname;
	Student* studentHead;
	Class* pNext;
};

struct Course
//_______create struct course_______
{
	Course *pNext;
	string CCode, year, name, lecturerusername;
	int semester;
	Date starting, ending;
	Time from, to;
	Score *pHeadScore; //score linkedlist is stored in node course
	int dayofweek;
};
struct Presence
{
	string CCode;
	string year;
	int semester;
	string id;
	int week[10] = { 0 };
	Presence *pNext;
};
void importstudentlist( string classname, Class *&classHead, bool check[] ); //dtb
void exportstudentclass( Class * curr );//dtb

//______________User list(staff,student,lecturer)___________
class Userlist{
	friend void updateuser( Userlist &a );
	friend void inputuser( Userlist &a); //trung
private:
	User* pHead;
	int num;
public:
	Userlist();
	~Userlist();
	User *log_in(string username_input, string password_input); //hieu
	int number();
};

void viewcheckin( Presence*p );//dtb
//________________Staff____________________
class Staff {
	friend void updatescore( Staff &a );
	friend void checkinclass( Staff &a,string id, string CCode,Presence *p);//dtb
	friend void inputcourse( Staff &a ); //hieu
	friend void updatecourse( Staff &a );
	friend void inputscore( Staff &a ); //trung
	friend void readmarks( Staff &a ,string studentid);//student //trung
	friend void editscore( Staff &a ,string lecturerusername);
	friend void importscore( Staff &a, string lecturerusername ,string CCode); //trung
	friend void printcourslist( Staff &a);
	friend void assign_class_to_course(Class* classHead, Staff&a );
	friend void addexiststudenttocourse( Staff &a, bool check[] );
private:
	Course*pHead;
public:
	void init();
	Staff();
	~Staff();
	void importschedule(); //hieu
	void importcourse(); //tu
	void importcourseCSV();  //tu
	void importscoreCSV(); //tu
	void export_course_student();
	void show_course_score( string courseCode );
	void export_course_score(string courseCode);  //export score of course //tu
	void export_student_score(string studentid); //export score of 1 student //tu
};
void export_student_list( Presence* p );//dtb
void export_course_attendance( Presence *p );//dtb
void export_course_attendancetocsv( Presence *p );//dtb
void inputpresence(Presence *& p);//dtb
void outputPresence( Presence *curr );
void outputstudentinclass( Class *classHead );

//menu
int menuStudent();//dtb
int menuStaff();//dtb
int menuLecturer();//dtb
int menuImportCourse();
int menuAddCourse();
int menuAttendance();
void getRealTime(Time &);//dtb
void getRealDay( Date & );//dtb
#endif // !FUNCTION_H
