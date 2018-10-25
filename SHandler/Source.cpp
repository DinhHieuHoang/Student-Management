#include"hieu.h"
using namespace std;

int main() {
	cout << "......///..........////////......////////..../////////..///......///......" << endl
		<< "......///........///......///..///......///.....///.....///......///......" << endl
		<< "......///........///......///..///..............///.....//////...///......" << endl
		<< "......///........///......///..///..............///.....///.//...///......" << endl
		<< "......///........///......///..///..............///.....///..//..///......" << endl
		<< "......///........///......///..///....///////...///.....///...//.///......" << endl
		<< "......///........///......///..///......///,,...///.....///...//////......" << endl
		<< "....../////////..///......///..///......///.....///.....///......///......" << endl
		<< "....../////////....////////......////////..../////////..///......///......" << endl;
	User *user_login = NULL;//create a log_in pointer
	Userlist user;//user task
	Staff staff;//staff task
	staff.init();
	Presence *student=NULL;//student task
	Class *classHead=NULL;
	//______________additional variables_____________
	string username, password,studentid,classname;
	int type = 0;
	int choice = 0;
	int count_login = 0;
	string CCode;
	bool *check;
	check = new bool[2000001];
	for (int i = 0; i<2000001; i++) 
		check[i] = false;
	//read data from file
	inputuser( user);
	inputcourse( staff );
	inputscore( staff );
	inputpresence(student);
	//input from file
	//Login menu
	cout << "Username: ";
	getline( cin, username );
	cout << "Password: ";
	getline( cin, password );
	user_login = user.log_in( username, password );
	++count_login;
	while (!user_login) {
		if (count_login == 10) {
			cout << "\nYou have logined with wrong username and password ten times. The program ends automatically.\n\n";
			outputPresence( student );
			updatecourse( staff );
			updatescore( staff );
			updateuser( user );
			return 0;
		}
		++count_login;
		cout << "Invalid username or password!\n\n";
		//Login menu
		cout << "Username: ";
		getline( cin, username );
		cout << "Password: ";
		getline( cin, password );
		user_login = user.log_in( username, password );
	}
	type = user_login->type;
	while (type != 3) {
		if ( choice == 11 || choice == 5 ) {
			user_login = NULL;
			count_login = 0;
			//Login menu
			cout << "Username: ";
			getline( cin, username );
			cout << "Password: ";
			getline( cin, password );
			user_login = user.log_in( username, password );
			++count_login;
			while (!user_login) {
				if (count_login == 10) {
					cout << "\nYou have logined with wrong username and password ten times. The program ends automatically.\n\n";
					outputPresence( student );
					updatescore( staff );
					updatecourse( staff );
					updateuser( user );
					return 0;
				}
				++count_login;
				cout << "Invalid username or password!\n\n";
				//Login menu
				cout << "Username: ";
				getline( cin, username );
				cout << "Password: ";
				getline( cin, password );
				user_login = user.log_in( username, password );
			}
			type = user_login->type;
		}
		else if ( choice == 6 || choice == 12) {
			type = 3;
		}
		switch (type) {
			//___________Student___________
		case 0:
			while ((choice = menuStudent()) != 6 && choice != 5) {
				switch (choice) {
				case 1:
					cout << "Enter course code: ";
					getline( cin, CCode );
					checkinclass( staff, user_login->username, CCode, student );
					break;
				case 2:
					readmarks( staff ,user_login->username);
					break;
				case 3://view check-in history
					viewcheckin( student );
					break;
				case 4:
					user_login->changepass();
					break;
				default:
					cout << "Invalid choice.\n";
					break;
				}
			}
			break;
			//___________Staff____________
		case 1:
			while ((choice = menuStaff()) != 12 && choice != 11) {
				switch (choice) {
				case 1:
					while ((choice = menuImportCourse()) != 4) {
						switch (choice) {
						case 1:
							while ((choice = menuAddCourse()) != 4) {
								switch (choice) {
								case 1:
										assign_class_to_course( classHead, staff );
									break;

								case 2:
									staff.importcourse();
									break;

								case 3:
									addexiststudenttocourse( staff, check );
									break;
								}
							}
							break;
						case 2: 
							staff.importcourseCSV();
							break;
						case 3:
							printcourslist( staff );
							break;
						}
					}
					break;
				case 2:
					cout << "Enter class name: ";
					getline( cin, classname );
					importstudentlist( classname, classHead , check);
					break;
				case 3:
					staff.importschedule();
					break;
				case 4:
					staff.export_course_student();
					break;
				case 5:
					exportstudentclass( classHead );
					break;
				case 6:
					cout << "Input student id: ";
					getline(cin, studentid);
					staff.export_student_score( studentid );
					break;
				case 7://show score course on the screen
					cout << "Input Course code: ";
					cin >> CCode;
					staff.show_course_score( CCode );
					break;
				case 8:
					cout << "Input Course code: ";
					cin >> CCode;
					staff.export_course_score( CCode );
					break;

				case 9:
					while ((choice = menuAttendance()) != 4) {
						switch (choice) {
						case 1:
							export_student_list( student );
							break;
						case 2:
							export_course_attendance( student );
							break;
						case 3:
							export_course_attendancetocsv( student );
							break;
						}
					}
					break;

				case 10:
					user_login->changepass();
					break;
				default:
					cout << "Invalid choice.\n\n";
					break;
				}
			}
			break;

		case 2:
			while ((choice = menuLecturer()) != 6 && choice != 5) {
				switch (choice) {
				case 1:
					cout << "Input Course code: ";
					cin >> CCode;
					importscore( staff, user_login->username, CCode );
					break;
				case 2:
					staff.importscoreCSV();
					break;
				case 3:
					editscore( staff, user_login->username );
					break;
				case 4:
					user_login->changepass();
					break;
				default:
					cout << "Invalid choice.\n\n";
					break;
				}
			}
			break;
		}
	}

	cout << "....../////////..///......///../////////........." << endl
		<< "......///........///......///..///.....///......." << endl
		<< "......///........//////...///..///......///......" << endl
		<< "......///........///.//...///..///......///......" << endl
		<< "....../////////..///..//..///..///......///......" << endl
		<< "......///........///...//.///..///......///......" << endl
		<< "......///........///...//////..///......///......" << endl
		<< "......///........///......///..///.....///......." << endl
		<< "....../////////..///......///..////////.........." << endl;
	delete[] check;
	updateuser( user );
	updatescore( staff );
	outputPresence( student );
	updatecourse( staff );
	return 0;
}
