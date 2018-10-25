#include"hieu.h"
#include<sstream>
using namespace std;

void export_student_list( Presence* p ) {
	if (!p) cout << "No list found.\n\n";
	string id;
	cout << "Enter student id: ";
	cin.ignore();
	getline( cin, id );
	while (p) {
		if (p->id == id) {
			int count = 0;
			cout << p->CCode << endl;
			cout << p->id << endl;
			for (int i = 0; i < 10; ++i) {
				if (p->week[i] == 0) ++count;
			}
			cout << "Absent: " << count << " week(s).\n\n";
		}
		p = p->pNext;
	}
}
void export_course_attendance( Presence *p ) {
	if (!p)cout << "No list found.\n\n";
	string coursecode;
	cout << "Enter coursecode: ";
	cin.ignore();
	getline( cin, coursecode );
	cout << coursecode << endl;
	while (p) {
		if (p->CCode == coursecode) {
			int count = 0;
			cout << p->id << endl;
			for (int i = 0; i < 10; ++i) {
				if (p->week[i] == 0) ++count;
			}
			cout << "Absent: " << count << " week(s).\n\n";
		}
		p = p->pNext;
	}
}
void export_course_attendancetocsv( Presence *p ) {
	if (!p)cout << "No list found.\n\n";
	string coursecode;
	cout << "Enter coursecode: ";
	cin.ignore();
	getline( cin, coursecode );
	ofstream fout;
	string filename;
	cout << "Enter your filename: ";
	getline( cin, filename );
	filename += ".csv";
	fout.open( filename, ios::out  );
	int first = 0;
	while (p) {
		if (p->CCode == coursecode) {
			if (first == 0) {
				fout << "Course code,";
				fout << coursecode << endl;
				fout << "Year," << p->year << endl;
				fout << "Semester," << p->semester << endl;
				fout << "Student id,Absence\n";
				++first;
			}
			int count = 0;
			fout << p->id;
			fout << ",";
			for (int i = 0; i < 10; ++i) {
				if (p->week[i] == 0) ++count;
			}
			fout << count << " week(s)\n";
		}
		p = p->pNext;
	}
	if (first == 0) fout << "NO STUDENT FOUND\n";
	fout.close();
}

//______________Menu_____________
int menuStudent() {
	cout << "_________________________\n"
		"Menu choice:\n\n"
		"1. Check-in class.\n"
		"2. Read marks.\n"
		"3. View check-in history.\n"
		"4. Change password.\n"
		"5. Logout.\n"
		"6. Exit.\n\n";
	int choice;
	cout << "Enter your choice: ";
	cin >> choice;
	cin.ignore();
	return choice;
}
int menuStaff() {
	cout << "_________________________\n"
		"Menu choice:\n\n"
		"1. Import courses.\n"
		"2. Import student lists.\n"
		"3. Import schedules.\n"
		"4. Export student of a course.\n"
		"5. Export student of a class.\n"
		"6. Export scores of student.\n"
		"7. Show scores of course on the screen.\n"
		"8. Export scores of one course to csv file.\n"
		"9. Export list of attendance.\n"
		"10. Change password.\n"
		"11. Logout.\n"
		"12. Exit.\n\n";
	int choice;
	cout << "Enter your choice: ";
	cin >> choice;
	cin.ignore();
	return choice;
}
int menuLecturer() {
	cout << "_________________________\n"
		"Menu choice:\n\n"
		"1. Import scores.\n"
		"2. Import scores from csv file.\n"
		"3. Edit score of one student.\n"
		"4. Change password.\n"
		"5. Logout.\n"
		"6. Exit.\n\n";
	int choice;
	cout << "Enter your choice: ";
	cin >> choice;
	cin.ignore();
	return choice;
}

int menuImportCourse() {
	int choice;
	cout << "\n\n1. Add a new course.\n"
		"2.Import course from csv.\n"
		"3. View list of all courses.\n"
		"4.Exit.\n\n";
	cout << "Enter your choice: ";
	cin >> choice;
	return choice;
}

int menuAddCourse() {
	int choice;
	cout << "\n\n1. Add an existing class.\n"
		"2. Add a course.\n"
		"3. Add a student from different class.\n"
		"4.Exit.\n\n";
	cout << "Enter your choice: ";
	cin >> choice;
	return choice;
}

int menuAttendance() {
	int choice;
	cout << "\n\n1.Show attendance of one student.\n"
		"2. Show attendance list of students' attendance in one course.\n"
		"3. Export to csv file list of students' attendance in one course.\n"
		"4.Exit\n\n";
	cout << "Enter your choice: ";
	cin >> choice;
	return choice;
}
//______________Userlist_____________
//constructor and destructor
Userlist::Userlist() {
	pHead = NULL;
	num = 0;
}
Userlist::~Userlist() {
	User*cur = pHead;
	while (cur) {
		cur = pHead->pNext;
		delete pHead;
		pHead = cur;
	}
}

//input user from file
void inputuser( Userlist &a ) {
	ifstream fin;
	fin.open( "User.txt", ios::in );
	if (fin.is_open()) {
		while (!fin.eof()) {
			if (a.pHead == NULL) {
				a.pHead = new User;
				getline( fin, a.pHead->username );
				getline( fin, a.pHead->full_name );
				getline( fin, a.pHead->password );
				getline( fin, a.pHead->email );
				getline( fin, a.pHead->mobile_phone );
				fin >> a.pHead->type;
				fin.ignore();
				getline( fin, a.pHead->Class );
				a.pHead->pNext = NULL;
			}
			else {
				User * tmp = new User;
				getline( fin, tmp->username );
				getline( fin, tmp->full_name );
				getline( fin, tmp->password );
				getline( fin, tmp->email );
				getline( fin, tmp->mobile_phone );
				fin >> tmp->type;
				fin.ignore();
				getline( fin, tmp->Class );
				tmp->pNext = a.pHead;
				a.pHead = tmp;
			}
			a.num++;
		}
	}
	fin.close();
}
void updateuser( Userlist &a ) {
	ofstream fout;
	fout.open( "User.txt" );
	User *cur = a.pHead;
	while (cur) {
		fout << cur->username << endl;
		fout << cur->full_name << endl;
		fout << cur->password << endl;
		fout << cur->email << endl;
		fout << cur->mobile_phone << endl;
		fout << cur->type << endl;
		fout << cur->Class;
		if (cur->pNext) fout << endl;
		cur = cur->pNext;
	}
	fout.close();
}


//check user login
User *Userlist::log_in( string username_input, string password_input ) {
	User *cur = pHead;
	while (cur) {
		if (cur->username == username_input&&cur->password == password_input)
			return cur;
		cur = cur->pNext;
	}
	return NULL;
}
int Userlist::number() {
	return num;
}

//______________Course(Score list) Staff_____________

//input course from file
void inputcourse( Staff & a ) {
	ifstream fin;
	fin.open( "Course.txt" );
	if (fin.is_open()) {
		while (!fin.eof()) {
			if (a.pHead == NULL) {
				a.pHead = new Course;
				getline( fin, a.pHead->CCode );
				getline( fin, a.pHead->year );
				fin >> a.pHead->semester;
				fin.ignore();
				getline( fin, a.pHead->name );
				getline( fin, a.pHead->lecturerusername );
				fin >> a.pHead->starting.day;
				fin >> a.pHead->starting.month;
				fin >> a.pHead->starting.year;
				fin >> a.pHead->ending.day;
				fin >> a.pHead->ending.month;
				fin >> a.pHead->ending.year;
				fin >> a.pHead->from.hour;
				fin >> a.pHead->from.minute;
				fin >> a.pHead->to.hour;
				fin >> a.pHead->to.minute;
				fin >> a.pHead->dayofweek;
				fin.ignore();
				a.pHead->pNext = NULL;
				a.pHead->pHeadScore = NULL;
			}
			else {
				Course *temp = new Course;
				temp = new Course;
				getline( fin, temp->CCode );
				getline( fin, temp->year );
				fin >> temp->semester;
				fin.ignore();
				getline( fin, temp->name );
				getline( fin, temp->lecturerusername );
				fin >> temp->starting.day;
				fin >> temp->starting.month;
				fin >> temp->starting.year;
				fin >> temp->ending.day;
				fin >> temp->ending.month;
				fin >> temp->ending.year;
				fin >> temp->from.hour;
				fin >> temp->from.minute;
				fin >> temp->to.hour;
				fin >> temp->to.minute;
				fin >> temp->dayofweek;
				fin.ignore();
				temp->pNext = a.pHead;
				temp->pHeadScore = NULL;
				a.pHead = temp;
			}
		}
	}
	fin.close();
}
//input score from file
void inputscore( Staff & a ) {
	string coursename;
	ifstream fin;
	fin.open( "Score.txt" );
	while (!fin.eof()) {
		getline( fin, coursename );
		Course *cur = a.pHead;
		while (cur != nullptr && cur->CCode != coursename) {
			cur = cur->pNext;
		}
		if (cur == nullptr) cout << "Can't find the course!";
		else {
			while (!fin.eof()) {
				string  _studentid;
				getline( fin, _studentid );
				if (_studentid == ".") break;
				if (cur->pHeadScore == nullptr) {
					cur->pHeadScore = new Score;
					cur->pHeadScore->studentid = _studentid;
					fin >> cur->pHeadScore->mid;
					fin >> cur->pHeadScore->lab;
					fin >> cur->pHeadScore->final;
					fin.ignore();
					cur->pHeadScore->pNext = nullptr;
				}
				else {
					Score *p = new Score;
					p->studentid = _studentid;
					fin >> p->mid;
					fin >> p->lab;
					fin >> p->final;
					fin.ignore();
					p->pNext = cur->pHeadScore;
					cur->pHeadScore = p;
				}
			}
		}
	}
	fin.close();
}

void updatecourse( Staff & a ) {
	ofstream fout;
	fout.open( "Course.txt" );
	Course*cur = a.pHead;
	if (fout.is_open()) {
		while (cur != NULL) {
			fout << cur->CCode << endl;
			fout << cur->year << endl;
			fout << cur->semester << endl;
			fout << cur->name << endl;
			fout << cur->lecturerusername << endl;
			fout << cur->starting.day << endl;
			fout << cur->starting.month << endl;
			fout << cur->starting.year << endl;
			fout << cur->ending.day << endl;
			fout << cur->ending.month << endl;
			fout << cur->ending.year << endl;
			fout << cur->from.hour << endl;
			fout << cur->from.minute << endl;
			fout << cur->to.hour << endl;
			fout << cur->to.minute << endl;
			fout << cur->dayofweek;
			if (cur->pNext) fout << endl;
			cur = cur->pNext;
		}
	}
	fout.close();
}

void Staff::init() {
	pHead = NULL;
}

//constructor and destructor
Staff::Staff() {
	pHead = new Course;
	pHead->pHeadScore = NULL;
}
Staff::~Staff() {
	while (pHead) {
		Course*cur = pHead;
		Score *temp = cur->pHeadScore;
		while (temp) {
			Score *remove = temp;
			temp = temp->pNext;
			delete remove;
		}
		pHead = pHead->pNext;
		delete cur;
	}
}

void Staff::importschedule() {
	ofstream fout;
	fout.open( "schedule.txt" );
	string input_from_user;
	cout << "Please input course code:" << endl;
	cin >> input_from_user;
	fout << "course code: ";
	fout << input_from_user << endl;
	cout << "Please input year:" << endl;
	cin >> input_from_user;
	cin.ignore();
	fout << "year: ";
	fout << input_from_user << endl;
	cout << "Please input semester:" << endl;
	getline( cin, input_from_user );
	fout << "semester: ";
	fout << input_from_user << endl;
	cout << "Please input course name:" << endl;
	getline( cin, input_from_user );
	fout << " course name: ";
	fout << input_from_user << endl;
	cout << "Please input lecturer name:" << endl;
	getline( cin, input_from_user );
	fout << " lecturer name: ";
	fout << input_from_user << endl;
	cout << "Please input starting day:" << endl;
	getline( cin, input_from_user );
	fout << "Starting date: " << input_from_user << "/";
	cout << "Please input starting month:" << endl;
	getline(cin, input_from_user);
	fout << input_from_user << "/";
	cout << "Please input starting year:" << endl;
	getline(cin, input_from_user);
	fout << input_from_user << endl;
	cout << "Please input ending day:" << endl;
	getline(cin, input_from_user);
	fout << "ending date: " << input_from_user << "/";
	cout << "Please input ending month:" << endl;
	getline(cin, input_from_user);
	fout << input_from_user << "/";
	cout << "Please input ending year:" << endl;
	getline(cin, input_from_user);
	fout << input_from_user << endl;
	cout << "Please input starting time:" << endl;
	getline( cin, input_from_user );
	fout << "From: ";
	fout << input_from_user << endl;
	cout << "Please input ending time:" << endl;
	getline( cin, input_from_user );
	fout << "To: ";
	fout << input_from_user << endl;
	fout.close();
}
void importscore( Staff &a, string lecturerusername, string CCode ) {
	Course *cur = a.pHead;
	while (cur && ((CCode != cur->CCode) || (lecturerusername != cur->lecturerusername)))
		cur = cur->pNext;
	if (cur) {
		Score *curScore = cur->pHeadScore;
		if (curScore == NULL) {
			int studentnum;
			cout << "Number of student: ";
			cin >> studentnum;
			for (int i = 1; i <= studentnum; ++i) {
				Score *tmp = new Score;
				cout << "Student id: ";
				cin >> tmp->studentid;
				cout << tmp->studentid << endl;
				cout << "Mid: ";
				cin >> tmp->mid;
				cout << tmp->mid << endl;
				cout << "Lab: ";
				cin >> tmp->lab;
				cout << tmp->lab << endl;
				cout << "Final: ";
				cin >> tmp->final;
				cout << tmp->final << endl;
				tmp->pNext = cur->pHeadScore;
				cur->pHeadScore = tmp;
			}
		}
		while (curScore) {
			cout << "Student id: " << curScore->studentid << endl;
			cout << "Mid: ";
			cin >> curScore->mid;
			cout << "Lab: ";
			cin >> curScore->lab;
			cout << "Final: ";
			cin >> curScore->final;
			curScore = curScore->pNext;
		}
		return;
	}
	cout << "No course satisfied with your information.\n";
}
void editscore( Staff & a ,string lecturerusername) {
	string CCode;
	cout << "Enter course code: ";
	getline( cin, CCode );
	Course *cur = a.pHead;
	while (cur && ((CCode != cur->CCode) || (lecturerusername != cur->lecturerusername)))
		cur = cur->pNext;
	if (!cur) {
		cout << "Course no found.\n\n";
		return;
	}
	Score *curScore = cur->pHeadScore;
	string id;
	cout << "Enter id: ";
	getline( cin, id );
	while (curScore&&curScore->studentid != id) {
		curScore = curScore->pNext;
	}
	if (!curScore) {
		cout << "No student found.\n\n";
		return;
	}
	cout << "Student id: " << curScore->studentid << endl;
	cout << "Mid: ";
	cin >> curScore->mid;
	cout << "Lab: ";
	cin >> curScore->lab;
	cout << "Final: ";
	cin >> curScore->final;
}
void Staff::importcourse( ) {
	Course *tmp = new Course;
	cout << "Course Code: ";
	getline(cin, tmp->CCode);
	cout << "Year: ";
	getline(cin, tmp->year);
	cout << "Semester: ";
	cin >> tmp->semester;
	cin.ignore();
	cout << "Course name: ";
	getline(cin, tmp->name);
	cout << "Lecturer user name: ";
	getline(cin, tmp->lecturerusername);
	cout << "Starting day: ";
	cin >> tmp->starting.day;
	cout << "Starting month: ";
	cin >> tmp->starting.month;
	cout << "Starting year: ";
	cin >> tmp->starting.year;
	cout << "Ending day: ";
	cin >> tmp->ending.day;
	cout << "Ending month: ";
	cin >> tmp->ending.month;
	cout << "Ending year: ";
	cin >> tmp->ending.year;
	cout << "From (hour): ";
	cin >> tmp->from.hour;
	cout << "Frome (minute): ";
	cin >> tmp->from.minute;
	cout << "To (hour): ";
	cin >> tmp->to.hour;
	cout << "To (minute): ";
	cin >> tmp->to.minute;
	cout << "Day of week: ";
	cin >> tmp->dayofweek;
	cin.ignore();
	tmp->pHeadScore = NULL;
	tmp->pNext = pHead;
	pHead = tmp;
}
void Staff::importcourseCSV() {
	string filename;
	string token;
	ifstream fin;
	cout << "Enter your file name: ";
	cin.ignore();
	getline( cin, filename );
	filename += ".csv";
	fin.open( filename );
	while (!fin.is_open()) {
		cout << "File doesn't exist.\n\n";
		cout << "Enter your file name: ";
		getline( cin, filename );
		filename += ".csv";
		fin.open( filename );
	}
	while (fin.good()) {
		while (getline( fin, token, ',' )) {
			Course *tmp = new Course;
			tmp->CCode = token;
			getline( fin, token, ',' );
			tmp->year = token;
			getline( fin, token, ',' );
			tmp->semester = stoi( token );
			getline( fin, token, ',' );
			tmp->name = token;
			getline( fin, token, ',' );
			tmp->lecturerusername = token;
			getline( fin, token, ',' );
			tmp->starting.day = stoi( token );
			getline( fin, token, ',' );
			tmp->starting.month = stoi( token );
			getline( fin, token, ',' );
			tmp->starting.year = stoi( token );
			getline( fin, token, ',' );
			tmp->ending.day = stoi( token );
			getline( fin, token, ',' );
			tmp->ending.month = stoi( token );
			getline( fin, token, ',' );
			tmp->ending.year = stoi( token );
			getline( fin, token, ',' );
			tmp->from.hour = stoi( token );
			getline( fin, token, ',' );
			tmp->from.minute = stoi( token );
			getline( fin, token, ',' );
			tmp->to.hour = stoi( token );
			getline( fin, token, ',' );
			tmp->to.minute = stoi( token );
			getline( fin, token, '\n' );
			tmp->dayofweek = stoi( token );
			tmp->pHeadScore = NULL;
			tmp->pNext = pHead;
			pHead = tmp;
		}
	}
	fin.close();
}
void printcourslist( Staff &a ) {
	Course* cur = a.pHead;
	while (cur != nullptr) {
		cout << cur->CCode << endl;
		cout << cur->name << endl;
		cur = cur->pNext;
	}
}
void importstudentlist( string classname ,Class *&classHead, bool check[]) {
	string filename;
	ifstream fin;
	string token;
	Student *curr = new Student;
	Class* tmp;
	tmp = new Class;
	tmp->studentHead = NULL;
	tmp->classname = classname;
	cout << "Enter your file name: ";
	getline( cin, filename );
	filename += ".csv";
	fin.open( filename );
	while (!fin.is_open()) {
		cout << "File doesn't exist.\n\n";
		cout << "Enter your file name: ";
		getline( cin, filename );
		filename += ".csv";
		fin.open( filename );
	}
	while (fin.good()) {
		while (getline( fin, token, ',' )) {
			curr->fullname = token;
			getline( fin, token, '\n' );
			curr->id = token;
			int intid = stoi( curr->id );
			check[intid] = true;
			curr->pNext = tmp->studentHead;
			tmp->studentHead = curr;
			curr = new Student;
		}
	}	
	fin.close();
	tmp->pNext = classHead;
	classHead = tmp;
	cout << "Class: ";
	cout << classHead->classname << endl;
	curr = classHead->studentHead;
	while (curr) {
		cout << "Full name: " << curr->fullname;
		cout << "\nStudent id: " << curr->id << endl;
		curr = curr->pNext;
	}
}
void outputstudentinclass(Class *classHead ) {
	string classname; 
	cout << "Input class name: ";
	cin >> classname;
	Class* cur= classHead;
	while (cur) {
		if (classHead->classname == classname) {
			Student *curr = cur->studentHead;
			while (curr) {
				cout << "Full name: " << curr->fullname;
				cout << "\nStudent id: " << curr->id << endl;
				curr = curr->pNext;
			}
			break;
		}
		cur = cur->pNext;
	}
	if (cur == NULL) cout << "Wrong name class!\n";
}
void updatescore( Staff &a ) {
	ofstream fout;
	fout.open( "Score.txt" );
	Course *cur = a.pHead;
	while (cur) {
		if (cur->pHeadScore != NULL) {
			fout << cur->CCode << endl;
			Score *curscore = cur->pHeadScore;
			while (curscore) {
				fout << curscore->studentid << endl;
				fout << curscore->mid << endl;
				fout << curscore->lab << endl;
				fout << curscore->final;
				if (curscore->pNext) fout << endl;
				curscore = curscore->pNext;
			}
			while (cur->pNext && !cur->pNext->pHeadScore )
				cur = cur->pNext;
			if (cur->pNext) fout << "\n.\n";
		}
		cur = cur->pNext;
	}
	fout.close();
}

void Staff::show_course_score( string courseCode ) {
	Course *cur = pHead;
	while (cur) {
		if (cur->CCode == courseCode) break;
		cur = cur->pNext;
	}
	if (!cur) {
		cout << "Course not found.\n\n";
		return;
	}
	Score *temp = cur->pHeadScore;
	if (!temp) {
		cout << "Student not found.\n\n";
		return;
	}
	while (temp) {
		cout << temp->studentid << endl;
		cout << "Midterm= " << temp->mid << endl;
		cout << "Lab= " << temp->lab << endl;
		cout << "Final= " << temp->final << endl << endl;
		temp = temp->pNext;
	}
}
//Mission of staff
void Staff::export_course_score( string courseCode ) {
	ofstream fout;
	string filename;
	Course *cur = pHead;
	while (cur) {
		if (cur->CCode == courseCode) break;
		cur = cur->pNext;
	}
	if (!cur) {
		cout << "Course not found.\n\n";
		return;
	}
	Score *temp = cur->pHeadScore;
	if (!temp) {
		cout << "Student not found.\n\n";
		return;
	}
	cout << "Enter filename: ";
	cin.ignore();
	getline( cin, filename );
	filename += ".csv";
	fout.open( filename,ios::out );
	cout << "\n\n" << courseCode << endl << endl;
	fout << "SCORE BOARD.\n";
	fout << "Course code," << cur->CCode << endl;
	fout << "Year," << cur->year << endl;
	fout << "Semester," << cur->semester << endl;
	fout << "Student id,Midterm score,Lab score,Final score\n";
	while (temp) {
		cout << temp->studentid << endl;
		fout << temp->studentid << ",";
		cout << "Midterm= " << temp->mid << endl;
		fout << temp->mid << ",";
		cout << "Lab= " << temp->lab << endl;
		fout << temp->lab << ",";
		cout << "Final= " << temp->final << endl << endl;
		fout << temp->final << "," << endl;
		temp = temp->pNext;
	}
	fout.close();
}
void Staff::export_student_score( string studentid ) {
	Course *temp = pHead;
	while (temp) {
		Score *cur = temp->pHeadScore;
		while (cur) {
			if (cur->studentid == studentid) break;
			cur = cur->pNext;
		}
		if (cur) {
			cout << temp->name << "-" << temp->CCode << ": " << endl;
			cout << "Midterm= " << cur->mid << endl;
			cout << "Lab= " << cur->lab << endl;
			cout << "Final= " << cur->final << endl;
		}
		temp = temp->pNext;
	}
}

//__________________Check-in class Student____________

void check( Presence* &p, string id, int i ,string CCode) {
	if (p != NULL) {
		Presence *curr = p;
		while (curr && (curr->id != id || curr->CCode!=CCode)) {
			curr = curr->pNext;
		}
		if (curr) {
			curr->week[i] = 1;
		}
	}

}
void checkinclass( Staff &a, string id, string CCode, Presence *p ) {
	Course * curr = a.pHead;
	while (curr && curr->CCode != CCode) {
		curr = curr->pNext;
	}
	if (curr == NULL) {
		cout << "Failed check-in.\n\n";
		return;
	}
	Score *temp = curr->pHeadScore;
	while (temp && temp->studentid != id) {
		temp = temp->pNext;
	}
	if (temp == NULL) {
		cout << "Failed check-in.\n\n";
		return;
	}
	Time realtime;
	Date realday;
	getRealTime( realtime );
	getRealDay( realday );
	if (curr->starting.year <= realday.year &&realday.year <= curr->ending.year) {
		if (curr->starting.month <= realday.month&&realday.month <= curr->ending.month) {
			int day = 0;
			if (realday.month == curr->starting.month&&realday.day >= curr->starting.day) {
				day = realday.day - curr->starting.day;
			}
			else {
				day += monthDays[curr->starting.month - 1] - curr->starting.day;
				int month = curr->starting.month + 1;
				while (month < realday.month) {
					day += monthDays[month++ - 1];
				}
				day += realday.day;
			}
			if (day % 7 == 0) {
				if (realtime.hour == curr->from.hour&&realtime.minute >= curr->from.minute) {
					check( p, id, (realday.day - curr->starting.day) / 7, CCode );
					cout << "Sucessful check-in.\n\n";
				}
				else if (realtime.hour == curr->to.hour&&realtime.minute <= curr->to.minute) {
					check( p, id, (realday.day - curr->starting.day) / 7, CCode );
					cout << "Sucessful check-in.\n\n";
				}
				else if (realtime.hour > curr->from.hour&&realtime.hour < curr->to.hour) {
					check( p, id, (realday.day - curr->starting.day) / 7, CCode );
					cout << "Sucessful check-in.\n\n";
				}
				else {
					cout << "Failed check-in.\n\n";
				}
			}
			else {
				cout << "Failed check-in.\n\n";
			}
		}
		else cout << "Failed check-in.\n\n";
	}
	else cout << "Invalid check-in.\n\n";
	while (p && (p->id != id || p->CCode != CCode)) {
		p = p->pNext;
	}
	if (p == NULL) cout << "No student found.\n\n";
	else {
		for (int i = 0; i < 10; i++) {
			cout << "Week " << i + 1 << " :";
			if (p->week[i] == 0) cout << "Absent\n";
			else cout << "X\n";
		}
	}
}
void viewcheckin( Presence *p ) {
	string id, CCode;
	cout << "Enter id: ";
	getline( cin, id );
	cout << "Enter course code: ";
	getline( cin, CCode );
	while (p && (p->id != id || p->CCode != CCode)) {
		p = p->pNext;
	}
	if (p == NULL) {
		cout << "No student found.\n\n";
		return;
	}
	for (int i = 0; i < 10; i++) {
		cout << "Week " << i + 1 << " :";
		if (p->week[i] == 0) cout << "Absent\n";
		else cout << "X\n";
	}
}
void inputpresence(Presence *& p)
{
	ifstream fin;
	fin.open("Presence.txt");
	Presence *blank;
	while (!fin.eof()) {
		blank = new Presence;
		getline(fin, blank->CCode);
		getline(fin, blank->year);
		fin >> blank->semester;
		fin.ignore();
		getline(fin, blank->id);
		for (int i = 0; i < 10; ++i)
			fin >> blank->week[i];
		blank->pNext = p;
		p = blank;
		fin.ignore();
	}
}
void outputPresence( Presence * curr ) {
	ofstream fout;
	fout.open( "Presence.txt" );
	if (fout.is_open()) {
		while (curr) {
			fout << curr->CCode;
			fout << endl;
			fout << curr->year;
			fout << endl;
			fout << curr->semester;
			fout << endl;
			fout << curr->id;
			fout << endl;
			for (int i = 0; i < 9; i++) {
				fout << curr->week[i] << ' ';
			}
			fout << curr->week[9];
			if (curr->pNext)
				fout << endl;
			curr = curr->pNext;
		}
	}
	fout.close();
}
//read marks
void readmarks( Staff & a, string studentid ) {
	string coursecode;
	cout << "Enter course code: ";
	getline( cin, coursecode );
	Course *temp = a.pHead;
	while (temp) {
		if (temp->CCode == coursecode) {
			break;
		}
		temp = temp->pNext;
	}
	if (!temp) {
		cout << "Course not found.\n\n";
		return;
	}
	Score *cur = temp->pHeadScore;
	while (cur) {
		if (cur->studentid == studentid) break;
		cur = cur->pNext;
	}
	if (cur) {
		cout << temp->name << "-" << temp->CCode << ": " << endl;
		cout << "Midterm= " << cur->mid << endl;
		cout << "Lab= " << cur->lab << endl;
		cout << "Final= " << cur->final << endl;
	}
}

//get real time
void getRealTime( Time &realtime ) {
	long int totalTime;
	int currentYear = 2017 - 1970;
	double totalYear;
	double totalDay;
	double day;
	long double divisor;
	const int timeShift = 7;

	totalTime = time( NULL );//number of seconds since 1970
	divisor = (60.0*60.0*24.0*365);
	totalYear = totalTime / divisor - currentYear;
	totalDay = 365 * totalYear;
	day = totalDay - (int)totalDay;
	realtime.hour = day * 24 + timeShift;
	realtime.minute = (day * 24 - (int)(day * 24)) * 60;
	//cout << realtime.hour << realtime.minute << endl;
}
void getRealDay( Date &realdate ) {
	long int totalTime;
	double totalYear;
	long double divisor;

	totalTime = time( NULL );
	divisor = (60.0*60.0*24.0*365.22);
	totalYear = totalTime / divisor + 1970;
	realdate.year = (int)totalYear;
	totalYear -= realdate.year;
	realdate.day = (int)(365 * totalYear);
	realdate.month = 1;

	while (realdate.day - monthDays[realdate.month - 1] > 0) {
		realdate.day -= monthDays[realdate.month - 1];
		++realdate.month;
	}
	//cout << realdate.day << realdate.month << realdate.year << endl;
}
void User::changepass() {
	string newpass;
	cout << "Enter new password:";
	getline( cin, newpass );
	password = newpass;
}

void Staff::importscoreCSV() {
	string filename;
	string token;
	ifstream fin;
	cout << "Enter your file name: ";
	getline( cin, filename );
	filename += ".csv";
	fin.open( filename );
	while (!fin.is_open()) {
		cout << "File doesn't exist.\n\n";
		cout << "Enter your file name: ";
		getline( cin, filename );
		filename += ".csv";
		fin.open( filename );
	}
	while (fin.good()) {
		while (getline( fin, token, ',' )) {
			Course *cur = pHead;
			string ccode = token;
			while (cur) {
				if (cur->CCode == ccode) break;
				cur = cur->pNext;
			}
			if (cur) {
				Score *curscore = cur->pHeadScore;
				getline( fin, token, ',' );
				string id = token;
				while (curscore) {
					if (curscore->studentid == id) {
						getline( fin, token, ',' );
						curscore->mid = stoi( token );
						getline( fin, token, ',' );
						curscore->lab = stoi( token );
						getline( fin, token, '\n' );
						curscore->final = stoi( token );
						break;
					}
					curscore = curscore->pNext;
				}
			}
		}
	}
	fin.close();
}



void Staff::export_course_student() {
	string courseCode;
	cout << "Enter the course code: ";
	getline( cin, courseCode );
	Course *cur = pHead;
	while (cur) {
		if (cur->CCode == courseCode) break;
		cur = cur->pNext;
	}
	if (!cur) {
		cout << "No course found.\n\n";
		return;
	}
	Score *temp = cur->pHeadScore;
	if (!temp) {
		cout << "No student found.\n\n";
		return;
	}
	cout << "\n\n" << courseCode << endl << endl;
	while (temp) {
		cout << "Student id: ";
		cout << temp->studentid << endl;
		temp = temp->pNext;
	}
}


void assign_class_to_course( Class* classHead, Staff&a ) {
	string course_id, class_name;
	cout << "Input course code: ";
	cin >> course_id;
	cout << "Input class name: ";
	cin >> class_name;
	Class* cur = classHead;
	while (cur != NULL&&cur->classname != class_name) {
		cur = cur->pNext;
	}
	if (cur == NULL) {
		cout << "There is not your class!" << endl;
		return;
	}
	Course* cur_course = a.pHead;
	while (cur_course != NULL&&cur_course->CCode != course_id)cur_course = cur_course->pNext;
	if (cur_course == NULL) {
		cout << "There is not your course!" << endl;
		return;
	}
	Score* new_student;
	Student* cur_student = cur->studentHead;
	while (cur_student != NULL) {
		new_student = new Score;
		new_student->studentid = cur_student->id;
		new_student->mid = -1;
		new_student->lab = -1;
		new_student->final = -1;
		new_student->pNext = cur_course->pHeadScore;
		cur_course->pHeadScore = new_student;
		cur_student = cur_student->pNext;
	}
}

void addexiststudenttocourse( Staff &a,bool check[] ) {
	string st, course_id;
	cout << "Enter student id:";
	cin.ignore();
	getline( cin, st );
	int intid = stoi( st );
	cout << "Enter the course id:";
	getline( cin, course_id );
	if (!check[intid])
		cout << "Student is not exist" << endl;
	else {
		Course* cur_course = a.pHead;
		while (cur_course != NULL&&cur_course->CCode != course_id)cur_course = cur_course->pNext;
		if (cur_course == NULL) {
			cout << "There is not your course!" << endl;
			return;
		}
		Score* new_student = new Score;
		new_student->studentid = st;
		new_student->mid = -1;
		new_student->lab = -1;
		new_student->final = -1;
		new_student->pNext = cur_course->pHeadScore;
		cur_course->pHeadScore = new_student;
	}
}

//export student of a class
void exportstudentclass( Class * curr ) {
	string classname;
	cout << "Enter the class name: ";
	getline( cin, classname );
	while (curr&&curr->classname != classname) {
		curr = curr->pNext;
	}
	if (!curr) {
		cout << "No class found.\n\n";
		return;
	}
	cout << classname << endl;
	Student* temp = curr->studentHead;
	while (temp) {
		cout << "\nFull name: " << temp->fullname<<endl;
		cout << "Student id: " << temp->id<<endl;
		temp = temp->pNext;
	}
}