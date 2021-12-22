#include<iostream> //program to manage students' records
#include<string>
#include<iomanip>
#include<vector>
#include<fstream>
#include<algorithm>

using namespace std;

class Name{
    string name = " ";
	public:
	void set_name(string& na){ //name setter function
			this -> name = na;
	}
	string get_name(){
	    return name;
	}
};
class Degree{
    float degree = 0;
public:
	void set_degree(float de){ //degree setter function
		this -> degree = de;
	}
	float get_degree(){
	    return degree;
	}
};
class fees_state{
  string state;
public:
    void set_state(string& s){
        state = s;
    }
    string get_state(){
        return state;
    }
};
class Section{
    int section = 1;
public:
    void set_section(int se){ //section setter function
        this -> section = se;
    }
    int get_section(){
        return section;
    }
};
class Student : public Name, public Degree, public Section, public fees_state{

public:
    explicit Student(string name = " " , float degree = 0, int section = 1, string state = "not"){ //constructor to set the default values of the student as "blank"
        set_name(name), set_degree(degree), set_section(section), set_state(state);
    }

	void input_data(){ //function to input the data of the student
        float n; string s;
        cout << "Enter the name of the student:\n";
        cin >> s;
        cout << "Enter the degree of the student:\n";
        cin >> n;
        set_name(s);
        set_degree(n);
        cout << "Enter the section of the student:\n";
        cin >> n;
        set_section(int(n));
        cout << "Enter the fees state of the student:[Done/Not]\n";
        cin >> s;
        transform(s.begin(), s.end(), s.begin(), ::tolower);
        set_state(s);
    }
		void show_data(){ //function to show the data of the student
			cout  <<  setw(17)  <<  get_name()  <<  setw(22)  <<  fixed  <<  setprecision(1)  <<  get_degree()  <<  setw(16) << get_section() << setw(15) << get_state() << "\n";
		}
		bool operator<(Student& s){ //function for the < operator to use it in sorting
			return get_name() < s.get_name();
		}
		bool findIt(string& s){ //find function to use it in searching
			return get_name().find(s) != string::npos;
		}
		bool findDegree(float degree){ //function to find the particular degree wich the user want
		    return this -> get_degree() == degree;
		}
		bool findDegree(float degree1, float degree2){ //function to find all of the degrees in the interval wich the user entered
			if(degree1 > degree2)
			    swap(degree1, degree2);

			return this -> get_degree() >= degree1 and this -> get_degree() <= degree2;

		}

};
class Teacher{
    string name;
    int classTeaching;
    float salary;
public:
    Teacher(string& n, int v, float s){
        this -> name = n;
        this -> classTeaching = v;
        this -> salary = s;
    }
    Teacher(){
        this -> name = "", classTeaching = 0, salary = 0;
    }

    //setters
    void set_name(string& n){
        this -> name = n;
    }

    void set_class(int c){
        classTeaching = c;
    }

    void set_salary(float s){
        salary = s;
    }

    void input_data(){
        cout << "Enter the name of the Teacher:\n";
        string s; cin >> s;
        this -> set_name(s);

        cout << "Enter the number of the class this teacher teaches:\n";
        int n; cin >> n;
        this -> set_class(n);

        cout << "Enter the salary of the teacher:\n";
        float f; cin >> f;
        this -> set_salary(f);
    }

    //getters
    string get_name(){
        return name;
    }

    int get_class(){
        return classTeaching;
    }

    float get_salary(){
        return salary;
    }

    void show_data(){ //function to show the data of the student
        cout  <<  setw(17)  <<  name  <<  setw(20)  <<  fixed  <<  setprecision(1)  <<  classTeaching  << setw(20) << salary << "\n";
    }
    bool operator<(Teacher& t){ //function for the < operator to use it in sorting
        return name < t.name;
    }
    bool findIt(string& s){ //find function to use it in searching
        return name.find(s) != string::npos;
    }
    bool findClass(int c){ //function to find the particular degree witch the user want
        return c == classTeaching;
    }

};
class System : public Student, public Teacher{
	vector<Student> MyList;
	vector<Teacher> teachingStaff;

	public:
	static void titles(){cout << "ID" << setw(16) << "Name" << setw(24) << "Degree" << setw(17) << "Section" << setw(18) << "Fees State:\n\n";} //function to print the titles of the list when showing
	static void staff_titles(){cout << "ID" << setw(16) << "Teacher" << setw(22) << "Class" << setw(20) << "Salary\n\n";}
	static void Draw(int n){while(n--)cout << '#';} //function to draw hash as signs as i pass to it
	static void lines(){cout  <<  "\n\n";} //function to make two end lines
	//constructor and destructor to save the data of the students
	System(){ //constructor
        input_student();
        input_teacher();
    }
    ~System(){ //destructor
        output_student();
        output_teacher();
    }

    void input_student(){ //function to use in the constructor to retrieve the data from the file
        ifstream students ("students.txt");
        string name, fee_state; float degree; int section;
        while(students >> name >> degree >> section >> fee_state){
            MyList.emplace_back(name, degree, section, fee_state);
        }
    }

    void output_student(){ //function to use in the destructor to write the data in the file
        ofstream students ("students.txt");
        for(auto & i : MyList){
            students << i.get_name() << "  " << i.get_degree() << "  " << i.get_section() << "  " << i.get_state() << "  ";
        }
    }

    void input_teacher(){ //function to use in the constructor to retrieve the data from the file
        ifstream teachers ("teachers.txt");
        string name; int cc; float f;
        while(teachers >> name >> cc >> f){
            teachingStaff.emplace_back(name, cc, f);
        }
    }

    void output_teacher(){ //function to use in the destructor to write the data in the file
        ofstream students ("teachers.txt");
        for(auto & i : teachingStaff){
            students << i.get_name() << "  " << i.get_class() << "  " << i.get_salary() << "  ";
        }
    }

    void show_staff(){ //function to output the data of the current list of the staff
        if(!teachingStaff.empty()){ //if the list is not empty
            staff_titles();
            for(int i = 0; i < teachingStaff.size(); i++){
                cout << i + 1; teachingStaff[i].show_data();
            }
            cout << "\n";
        }else{ //if the list is empty
            cout  <<  "No data found!";
        }
    }

	void show_MyList(){ //function to output the data of the current list of the students
			if(!MyList.empty()){ //if the list is not empty
				titles();
                for(int i = 0; i < MyList.size(); i++){
                    cout << i + 1; MyList[i].show_data();
                }
			    cout << "\n";
			}else{ //if the list is empty
				cout  <<  "No data found!";
			}
	}

    static void sorting(vector<Teacher>& v){ //function to sort the students by the Alphabetical sorting using the overloading of the < operator
        for(int i = 0; i < v.size(); i++)
            for(int j = 0; j < v.size(); j++)
                if(v[i] < v[j])  swap(v[i], v[j]);
    }

	static void sorting(vector<Student>& v){ //function to sort the students by the Alphabetical sorting using the overloading of the < operator
		for(int i = 0; i < v.size(); i++)
			for(int j = 0; j < v.size(); j++)
				if(v[i] < v[j])  swap(v[i], v[j]);
	}

	void add(){ //the option of adding students to the list
		cout  <<  "How many students do wanna add??\n";
		int n; cin  >>  n;
		if(n == 1){ //if the user want to add only one student
			Student temp;
			temp.input_data();
			MyList.push_back(temp);
		cout << "Done!\nThe student have been added to the list.\n";
		sorting(MyList);

		}else{ //if the user want to add more than one student
			for(int i = 0; i < n; i++){
				cout << "Student number " << i + 1 << endl;
				Student temp;
				temp.input_data();
				MyList.push_back(temp);

			}
			cout << "Done!\nThe students have been added to the list.\n";
			sorting(MyList);
		}

    }
    void add_teacher(){ //the option of adding teachers to the list
        cout << "How many teachers do wanna add??\n";
        int n; cin >> n;
        if(n == 1){ //if the user want to add only one teacher
            Teacher temp;
            temp.input_data();
            teachingStaff.push_back(temp);
            cout << "Done!\nThe teacher have been added to the list.\n";
            sorting(teachingStaff);

        }else{ //if the user want to add more than one teacher
            for(int i = 0; i < n; i++){
                cout << "Teacher number " << i + 1 << endl;
                Teacher temp;
                temp.input_data();
                teachingStaff.push_back(temp);

            }
            cout << "Done!\nThe teachers have been added to the list.\n";
            sorting(teachingStaff);
        }

    }

	void search(){ //the option of searching for a student in the list
		while(true){ //loop this section of code till the user enter write inputs

			cout << "* Enter '1' if you want to search by ID.\n* Enter '2' if you want to search by name.\n* Enter '3' if you want to search by degree.\n\n";
			char choice; cin >> choice;
			cout << "\n";
		if(choice == '1'){ //searching by the ID of the student
			int id;
			while(true){
				cout << "* Enter the ID number of the student who you want to serch for:\n";
				cin >> id;
				if(id > MyList.size() + 1 or id < 1){ //if the id is larger or smaller than the size of the list continue looping
					cout << "This ID does not exist.\nDo you want to search for another ID?\n* Enter yes or no only!";
					lines();
					string answer; cin >> answer;
					transform(answer.begin(), answer.end(), answer.begin(), ::tolower);

					if(answer == "yes") continue; else break;

				}else{ //if the id is correct show the data of the student
					titles();
					cout <<  id; MyList[id - 1].show_data();
					break;
				}
			}
				break;
		}
		else if(choice == '2'){ //searching by the name of the student(we use find function to get all the related names
			while(true){
				cout << "* Enter the name/character the name of the student you want contains:\n";
				string name; cin >> name;
				bool found = false; //flag named(found) refers to the result of searching operation
				titles();
			for(int i = 0; i < MyList.size(); i++){
				if(MyList[i].findIt(name)){
					found = true;
					cout << i + 1; MyList[i].show_data();
				}
			}
			if(!found){ //if the name is not found in the list
				cout << "Student not found!\nDo you want to search for another name?\n* Enter yes or no only!";
				lines();
				string answer; cin >> answer;
				transform(answer.begin(), answer.end(), answer.begin(), ::tolower);
				if(answer == "yes")continue; else break;
			}else break;
			}
			break;
		}
		else if(choice == '3'){ //searching by the degree of the students
			while(true){ //looping while the input is wrong

				cout << "\n* Enter '1' if you want to search for a particular degree.\n* Enter '2' if you want to search for degrees in an interval.\n\n";
				cin >> choice;
				bool found = false;
				if(choice == '1'){ //searching for a particular degree and get all the students who have this degree
					while(true){
					cout << "* Enter the degree you want to search for:\n";
					float degree; cin >> degree;
					titles();
				for(int i = 0; i < MyList.size(); i++){
							if(MyList[i].findDegree(degree)){
							found = true;
							cout << i + 1; MyList[i].show_data();
					}
				}
				if(!found){ //if there's no one of the students has this degree
					cout << "There's no one has this degree.\nDo you want to search for another degree?\n** Enter yes or no only";
					lines();
					string answer; cin >> answer;
					transform(answer.begin(), answer.end(), answer.begin(), ::tolower);
					if(answer == "yes") continue; else break;
				}else break;
				}
				break;
				}else if(choice == '2'){ //searching for the students in an interval
					while(true){
						cout << "* Enter the bounds of the interval:\n";
						float upperBound, lowerBound; cin >> lowerBound >> upperBound;
						bool found = false;
						titles();

						for(int i = 0; i < MyList.size(); i++){
							if(MyList[i].findDegree(lowerBound, upperBound)){
							cout  <<  i + 1; MyList[i].show_data();
							found = true;
							}
						}
						if(!found){ //if there is no student has a degree in the interval
							cout << "There's no degree in this interval.\nTry again.\n";
							lines();
							continue;
						}else break;
					}
					break;
				}else{ //catching the wrong input in the searching by degree list
				cout << "\nInvalid input\nEnter a number of the above only!\n";
				continue;
				}
			}
			break;
		}else{ //catching the wrong input in the searching list
			cout << "\nInvalid input!\nEnter a number of the above only!\n";
			continue;
		}
		}
	}

    void search_staff(){ //the option of searching for a student in the list
        while(true){ //loop this section of code till the user enter write inputs

            cout << "* Enter '1' if you want to search by ID.\n* Enter '2' if you want to search by name.\n* Enter '3' if you want to search by class.\n\n";
            char choice; cin >> choice;
            cout << "\n";
            if(choice == '1'){ //searching by the ID of the teacher
                int id;
                while(true){
                    cout << "* Enter the ID number of the teacher who you want to search for:\n";
                    cin >> id;
                    if(id > teachingStaff.size() + 1 or id < 1){ //if the id is larger or smaller than the size of the list continue looping
                        cout << "This ID does not exist.\nDo you want to search for another ID?\n* Enter yes or no only!";
                        lines();
                        string answer; cin >> answer;
                        transform(answer.begin(), answer.end(), answer.begin(), ::tolower);

                        if(answer == "yes") continue; else break;

                    }else{ //if the id is correct show the data of the teacher
                        titles();
                        cout <<  id; teachingStaff[id - 1].show_data();
                        break;
                    }
                }
                break;
            }else if(choice == '2'){ //searching by the name of the teacher(we use find function to get all the related names
                while(true){
                    cout << "* Enter the name/character the name of the teacher you want contains:\n";
                    string name; cin >> name;
                    bool found = false; //flag named "found" refers to the result of searching operation
                    titles();
                    for(int i = 0; i < teachingStaff.size(); i++){
                        if(teachingStaff[i].findIt(name)){
                            found = true;
                            cout << i + 1; teachingStaff[i].show_data();
                        }
                    }
                    if(!found){ //if the name is not found in the list
                        cout << "Teacher not found!\nDo you want to search for another name?\n* Enter yes or no only!";
                        lines();
                        string answer; cin >> answer;
                        transform(answer.begin(), answer.end(), answer.begin(), ::tolower);
                        if(answer == "yes")continue; else break;
                    }else break;
                }
                break;
            }else if(choice == '3'){ //searching by the class of the teachers
                while(true){ //looping while the input is wrong

                    cin >> choice;
                    bool found = false;
                     //searching for a particular class and get all the teachers who teach this class
                        while(true){
                            cout << "* Enter the class you want to search for:\n";
                            int cla; cin >> cla;
                            titles();
                            for(int i = 0; i < teachingStaff.size(); i++){
                                if(teachingStaff[i].findClass(cla)){
                                    found = true;
                                    cout << i + 1; teachingStaff[i].show_data();
                                }
                            }
                            if(!found){ //if there's no one of the teachers teaches this class
                                cout << "There's no one teaches this class.\nDo you want to search for another class?\n** Enter yes or no only";
                                lines();
                                string answer; cin >> answer;
                                transform(answer.begin(), answer.end(), answer.begin(), ::tolower);
                                if(answer == "yes") continue; else break;
                            }else break;
                        }
                        break;
                    }
                }else{ //catching the wrong input in the searching list
                cout << "\nInvalid input!\nEnter a number of the above only!\n";
                continue;
            }

            }
        }

	void modify(){ //the option of modifying the data of the students
			while(true){
				if(!MyList.empty()){ //if the list is already containing data

					cout << "* Enter '1' if you want to modify a name.\n* Enter '2' if you want to modify a degree.\n* Enter '3' if you want to modify both.\n\n";
					int choice, id; cin >> choice;
					if(choice == 1){ //modifying a name
						show_MyList();
						cout << "\n* Enter the ID of the student you want to change his/her name:\n";
						cin >> id;
						cout << "* Enter the new name of the student:\n";
						string name; cin >> name;
						MyList[id - 1].set_name(name);
						sorting(MyList);
						break;
					}
					else if(choice == 2){ //modifing a degree
						cout << "* Enter '1' if you want to write a new degree.\n* Enter '2' if you want to increase/decrease by a percentage.\n";
						cin >> choice;
						if(choice == 1){ //writing a new degree
							show_MyList();
							cout << "\n* Enter the ID of the student you want to change his/her degree:\n";
							cin >> id;
							cout << "* Enter the new degree of the student:\n";
							float degree; cin >> degree;
							MyList[id - 1].set_degree(degree);
							break;
						}else if(choice == 2){ //increasing & decreasing
							cout << "* Enter '1' if you want to increase by a percentage.\n* Enter '2' if you want to decrease by a percentage.\n\n";
							int choice2; cin >> choice2;

							if(choice2 == 1){ //increasing
								cout << "* Enter '1' if you want to increase particular number of students.\n* Enter '2' if you want to increase all of the degrees.\n\n";
								cin >> choice2;
								if(choice2 == 1){ //increasing particular number of degrees (one or more)
									cout << "* Enter the number of the students that you want to increase their degrees.\n\n";
									int num; cin >> num;
									if(num == 1){ //if the number of students is one only
										show_MyList();
										cout << endl << "* Enter the ID of the student.\n";
										int id; cin >> id;
										cout << "* Enter the percentage that you want to add to the degree %";
										float percentage, temp; cin >> percentage;
										temp = ((percentage / 100) * MyList[id - 1].get_degree()) + MyList[id - 1].get_degree();
										MyList[id - 1].set_degree(temp);
										cout << "Done!"; lines();
										break;
									} //if there's more than one student
									for(int i = 0; i < num; i++){
										show_MyList();
										cout << endl << "* Enter the ID of the studnet number " << i+1 << "." << endl;
										int id; cin >> id;
										cout << "* Enter the percentage that you want to add to the degree %";
										float percentage, temp; cin >> percentage;
										temp = ((percentage / 100) * MyList[id - 1].get_degree()) + MyList[id - 1].get_degree();
										MyList[id - 1].set_degree(temp);
									}
									cout << "Done!"; lines();
									break;
								}else if(choice2 == 2){ //increasing all the degrees in the list
									cout << "* Enter the percentage of that you want to add to the degrees %";
									float percentage, temp; cin >> percentage;

									for(auto & i : MyList){
										temp = ((percentage / 100) * i.get_degree()) + i.get_degree();
									i.set_degree(temp);
									}
									cout << "Done!"; lines();
									break;
								}else{ //wrong inputs and catching them in increasing only
									cout << "Invalid input!!\n* Enter a number of the above only!\n";
									continue;
								}

							}else if(choice2 == 2){ //decreasing
								cout << "* Enter '1' if you want to decrease particular number of students.\n* Enter '2' if you want to decrease all of the degrees.\n\n";
								cin >> choice2;

								if(choice2 == 1){ //particular number of students
									cout << "* Enter the number of the students that you want to decrease their degrees.\n\n";
									int num; cin >> num;
									if(num == 1){ //if the number of students is one only
										show_MyList();
										cout << endl << "* Enter the ID of the student.\n";
										int id; cin >> id;
										cout << "* Enter the percentage that you want to add to the degree %";
										float percentage, temp; cin >> percentage;
										temp = MyList[id - 1].get_degree() - ((percentage / 100) * MyList[id - 1].get_degree());
										MyList[id - 1].set_degree(temp);
										cout  <<  "Done!"; lines();
										break;
									} //if there're more than one student
									for(int i = 0; i < num; i++){
										show_MyList();
										cout << endl << "* Enter the ID of the student number " << i + 1 << endl;
										int id; cin >> id;
										cout  <<  "* Enter the percentage that you want to subtract from the degree %";
										float percentage, temp; cin >> percentage;
										temp = MyList[id - 1].get_degree() - ((percentage / 100) * MyList[id - 1].get_degree());
										MyList[id - 1].set_degree(temp);
									}
									break;
								}else if(choice2 == 2){ //decreasing all the degrees in the list
									cout << "* Enter the percentage of that you want to subtract from the degrees %";
									float percentage, temp; cin >> percentage;

									for(auto & i : MyList){
										temp = i.get_degree() - ((percentage / 100) * i.get_degree());
										i.set_degree(temp);
									}
									break;
								}else{ //the wrong inputs and catching them in decreasing only
									cout << "Invalid input!!\n* Enter a number of the above only!\n";
									continue;
								}

							}else{ //the wrong inputs and catching them in increasing and decreasing
								cout << "Invalid input!!\n* Enter a number of the above only!\n";
								continue;
							}
						}else{ //catching the wrong inputs in modifying the degree
							cout << "Invalid input!!\n* Enter a number of the above only!\n";
							continue;
						}
					}
					else if(choice == 3){ //modifying the hole data of the student(name & degree)
						show_MyList();
						cout << "\n* Enter the ID of the student you want to change his/her data:\n";
						int id; cin >> id;
						MyList[id-1].input_data();
						sorting(MyList);
						break;
					}else{ //wrong inputs and catching them in modifying
						cout << "Invalid input!\nEnter a number of the above only!!\n";
						continue;
					}
				}else{ //if the list is empty(no data to modify)
					cout << "There's no data to modify!";
					break;
				}
			}
	}

    void modify_staff(){ //the option of modifying the data of the students
        while(true){
            if(!teachingStaff.empty()){ //if the list is already containing data

                cout << "* Enter '1' if you want to modify a name.\n* Enter '2' if you want to modify a class.\n* Enter '3' if you want to modify both.\n\n";
                int choice, id; cin >> choice;

                if(choice == 1){ //modifying a name
                    show_staff();
                    cout << "\n* Enter the ID of the teacher you want to change his/her name:\n";
                    cin >> id;
                    cout << "* Enter the new name of the teacher:\n";
                    string name; cin >> name;
                    teachingStaff[id - 1].set_name(name);
                    sorting(teachingStaff);
                    break;
                }else if(choice == 2){ //modifying a class
                    show_MyList();
                    cout << "\n* Enter the ID of the teacher you want to change his/her class:\n";
                    cin >> id;
                    cout << "* Enter the new class of the teacher:\n";
                    int cla; cin >> cla;
                    teachingStaff[id - 1].set_class(cla);
                    break;
                }else if(choice == 3){ //modifying the hole data of the teacher(name & class)
                    show_MyList();
                    cout << "\n* Enter the ID of the teacher you want to change his/her data:\n";
                    cin >> id;
                    teachingStaff[id - 1].input_data();
                    sorting(teachingStaff);
                    break;
                }else{ //wrong inputs and catching them in modifying
                        cout << "Invalid input!\nEnter a number of the above only!!\n";
                        continue;
                }
            }else{ //if the list is empty(no data to modify)
                cout << "There's no data to modify!";
                break;
            }
        }
    }

	void deleting(){ //the option of deleting students and its data from the list
		while(true){
		if(!MyList.empty()){ //if the list is not empty

				cout << "* Enter '1' if you want to delete a number of students' data.\n* Enter '2' if you want to delete all the data.\n\n";
				char choice; cin >> choice;
				if(choice == '1'){ //deleting number of students' data
					while(true){
						cout << "* Enter the number of students you want to delete their data:\n";
						int num, id; cin >> num;
						if(num == 0) //the user don't want to delete a student
							break;
						else if(num <= MyList.size()){ //if the number of the students is larger than 0 and smaller than tha size of the list
							for(int i = 0; i<num; i++){
								label:
								show_MyList();
								if(num == 1){ //if the number is one, there's no need to number the students
									cout << "Enter the ID of the student.\n";
								}else{ //many students and we need to number them
									cout << "* Enter the ID of the student number " << i+1 << endl;
								}
								cin >> id;

						while(true){ //looping untill the user wants to exit
						cout << "** WARNING **\nTHE DATA OF THIS STUDENT WILL BE DELETED ARE YOU SURE ?!\n* Enter yes or no only!\n\n";
						string sureOrNot; cin >> sureOrNot;
						transform(sureOrNot.begin(), sureOrNot.end(), sureOrNot.begin(), ::toupper);

						if(sureOrNot == "YES"){ //the user wants to delete the data of the student
							cout << "Done!\n\n";
							break;
						}else if(sureOrNot == "NO"){ //the user don't want to delete the data of the student
							cout << "OK, Student's data will not be deleted.\n\nDo you want to delete another student?\nEnter yes or no only!\n\n";
							string answer; cin >> answer; transform(answer.begin(), answer.end(), answer.begin(), ::tolower);
							if(answer == "yes")
							goto label;
							else break;
						}else{ //wrong inputs and catching them in the question
							cout << "Invalid input!!\n";
							continue;
						}
				}
				auto it = MyList.begin() + (id - 1); //positioning the iterator at the begin of the list + (the position that the user want - 1)
				int newSize = int(MyList.size()); //shrinking the list to fit the new size after deleting the data
				MyList.erase(it);
				--newSize;
				MyList.resize(newSize);
				MyList.shrink_to_fit();
			}
			break;
			}else{ //if the number of the students the user want is larger than the size of the list or smaller than 0
				cout << "Invalid input!\n* Enter a number less than or equal to the number of students!!\n";
				continue;
			}

			}
			break;
		}else if(choice == '2'){ //deleting all of the data in the list
				if(!MyList.empty()){ //if the list is not empty
						while(true){
							cout << "** WARNING **\nALL THE DATA WILL BE DELETED ARE YOU SURE ?!\n* Enter yes or no only!\n";
							string sureOrNot; cin >> sureOrNot;
							transform(sureOrNot.begin(), sureOrNot.end(), sureOrNot.begin(), ::toupper);

							if(sureOrNot == "YES"){
								MyList.clear();
								cout << "Done!\n";
								break;
							}else if(sureOrNot == "NO"){
								cout << "OK, Nothing will be deleted.\n";
								break;
							}else{
								cout << "Invalid input!!\n";
								continue;
							}
						}
							break;
				}else{ //if the list is empty
					cout << "There's no data to delete from!\n";
					break;
				}
		}else{ //wrong inputs and catching them in deleting option
			cout << "\nInvalid input!\nEnter a number of the above only!\n";
			continue;
		}
		}else{ //if the list is empty
			cout << "There's no data to delete from!";
			break;
		}
	}
	}

    void deleting_staff(){ //the option of deleting teachers and its data from the list
        while(true){
            if(!teachingStaff.empty()){ //if the list is not empty

                cout << "* Enter '1' if you want to delete a number of teachers' data.\n* Enter '2' if you want to delete all the data.\n\n";
                char choice; cin >> choice;
                if(choice == '1'){ //deleting number of teachers' data
                    while(true){
                        cout << "* Enter the number of teachers you want to delete their data:\n";
                        int num, id; cin >> num;
                        if(num == 0) //the user don't want to delete a student
                            break;
                        else if(num <= teachingStaff.size()){ //if the number of the students is larger than 0 and smaller than tha size of the list
                            for(int i = 0; i < num; i++){
                                label:
                                show_staff();
                                if(num == 1){ //if the number is one, there's no need to number the teachers
                                    cout << "Enter the ID of the teacher.\n";
                                }else{ //many teachers and we need to number them
                                    cout << "* Enter the ID of the teacher number " << i + 1 << endl;
                                }
                                cin >> id;

                                while(true){ //looping until the user wants to exit
                                    cout << "** WARNING **\nTHE DATA OF THIS TEACHER WILL BE DELETED ARE YOU SURE ?!\n* Enter yes or no only!\n\n";
                                    string sureOrNot; cin >> sureOrNot;
                                    transform(sureOrNot.begin(), sureOrNot.end(), sureOrNot.begin(), ::toupper);

                                    if(sureOrNot == "YES"){ //the user wants to delete the data of the teacher
                                        cout << "Done!\n\n";
                                        break;
                                    }else if(sureOrNot == "NO"){ //the user don't want to delete the data of the teacher
                                        cout << "OK, Teacher's data will not be deleted.\n\nDo you want to delete another teacher?\nEnter yes or no only!\n\n";
                                        string answer; cin >> answer; transform(answer.begin(), answer.end(), answer.begin(), ::tolower);
                                        if(answer == "yes")
                                            goto label;
                                        else break;
                                    }else{ //wrong inputs and catching them in the question
                                        cout << "Invalid input!!\n";
                                        continue;
                                    }
                                }
                                auto it = teachingStaff.begin() + (id - 1); //positioning the iterator at the begin of the list + (the position that the user want - 1)
                                int newSize = int(teachingStaff.size()); //shrinking the list to fit the new size after deleting the data
                                teachingStaff.erase(it);
                                --newSize;
                                teachingStaff.resize(newSize);
                                teachingStaff.shrink_to_fit();
                            }
                            break;
                        }else{ //if the number of the teachers the user want is larger than the size of the list or smaller than 0
                            cout << "Invalid input!\n* Enter a number less than or equal to the number of students!!\n";
                            continue;
                        }

                    }
                    break;
                }else if(choice == '2'){ //deleting all of the data in the list
                    if(!teachingStaff.empty()){ //if the list is not empty
                        while(true){
                            cout << "** WARNING **\nALL THE DATA WILL BE DELETED ARE YOU SURE ?!\n* Enter yes or no only!\n";
                            string sureOrNot; cin >> sureOrNot;
                            transform(sureOrNot.begin(), sureOrNot.end(), sureOrNot.begin(), ::toupper);

                            if(sureOrNot == "YES"){
                                teachingStaff.clear();
                                cout << "Done!\n";
                                break;
                            }else if(sureOrNot == "NO"){
                                cout << "OK, Nothing will be deleted.\n";
                                break;
                            }else{
                                cout << "Invalid input!!\n";
                                continue;
                            }
                        }
                        break;
                    }else{ //if the list is empty
                        cout << "There's no data to delete from!\n";
                        break;
                    }
                }else{ //wrong inputs and catching them in deleting option
                    cout << "\nInvalid input!\nEnter a number of the above only!\n";
                    continue;
                }
            }else{ //if the list is empty
                cout << "There's no data to delete from!";
                break;
            }
        }
    }

    void fees_information(){
        if(!MyList.empty()){
            cout << setw(15) << "Name" << setw(22) << "fees state" << endl << endl;
            int i = 1;
            for (auto &it : MyList) {
                cout << i++ << setw(15) << it.get_name() << setw(20) << it.get_state() << endl;
            }
            cout << endl << endl;
        }else{
            cout << "No data found!" << endl << endl;
        }
	}

	void salary_information(){
        if(!teachingStaff.empty()){
            cout << setw(17) << "Teacher" << setw(22) << "Salary" << endl << endl;
            int i = 1;
            for (auto &it : teachingStaff) {
                cout << i++ << setw(15) << it.get_name() << setw(22) << it.get_salary() << endl;
            }
            cout << endl << endl;
        }else{
            cout << "No data found!" << endl << endl;
        }
	}

	static void interface(){
		cout << "||"; Draw(4); cout << "^_^ Students' Records ^_^"; Draw(4); cout << "||";
		lines();
		cout << "* Enter '1' to add students.\n* Enter '2' to search for students/degrees.\n* Enter '3' to modify student's name/ degree.\n* Enter '4' to delete students.\n* Enter '5' to show the list.\n* Enter '6' to exit the program.\n* Enter '7' to go back to the previous menu.\n\n";

    }
    static void interfaceForStaff(){
        cout << "||"; Draw(4); cout << "^_^ Staff' List ^_^"; Draw(4); cout << "||";
        lines();
        cout << "* Enter '1' to add teachers.\n* Enter '2' to search for teachers/classes.\n* Enter '3' to modify teachers' names/classes.\n* Enter '4' to delete teachers.\n* Enter '5' to show the list.\n* Enter '6' to exit the program.\n* Enter '7' to go back to the previous menu.\n\n";
    }


		void start(){
	        label:
	        bool go_out = false;
            while(!go_out){
                cout << "* Enter '1' if you want to access the list of the students.\n* Enter '2' if you want to access the list of teachers.\n* Enter '3' to see the fees states of the students.\n* Enter '4' to see salary information of the teachers.\n* Enter '5' to exit.\n\n";
                int mode; cin >> mode;

                if (mode == 1) {
                    while (true) {
                        interface();

                        char choice;
                        cin >> choice;
                        if (choice == '1') {
//				            system("CLS");
                            add();
                            lines();
                            continue;
                        } else if (choice == '2') {
//				            system("CLS");
                            if (MyList.empty()) {
                                cout << "There's no Student's to search in!\n\n";
                                continue;
                            }
                            search();
                            lines();
                            continue;
                        } else if (choice == '3') {
//			            	system("CLS");
                            modify();
                            lines();
                            continue;
                        } else if (choice == '4') {
//			            	system("CLS");
                            deleting();
                            lines();
                            continue;
                        } else if (choice == '5') {
//		            		system("CLS");
                            show_MyList();
                            lines();
                            continue;
                        } else if (choice == '6') {
                            go_out = true;
                            break;
                        } else if(choice == '7'){
                            goto label;
                        } else {
//				            system("CLS");
                            cout << "\nInvalid input!\nEnter a number of the above only!\n";
                            continue;
                        }

                    }
                } else if (mode == 2) {
                    while (true) {
                        interfaceForStaff();

                        char choice;
                        cin >> choice;

                        if (choice == '1') {
//			            	system("CLS");
                            add_teacher();
                            lines();
                            continue;
                        } else if (choice == '2') {
//				            system("CLS");
                            if (teachingStaff.empty()) {
                                cout << "There's no teachers to search in!\n\n";
                                continue;
                            }
                            search_staff();
                            lines();
                            continue;
                        } else if (choice == '3') {
//			            	system("CLS");
                            modify_staff();
                            lines();
                            continue;
                        } else if (choice == '4') {
//			            	system("CLS");
                            deleting_staff();
                            lines();
                            continue;
                        } else if (choice == '5') {
//			            	system("CLS");
                            show_staff();
                            lines();
                            continue;
                        } else if (choice == '6') {
                            go_out = true;
                            break;
                        } else if (choice == '7'){
                            goto label;
                        } else {
//		            		system("CLS");
                            cout << "\nInvalid input!\nEnter a number of the above only!\n";
                            continue;
                        }

                    }
                } else if (mode == 3){
                    fees_information();
                    goto label;
                } else if (mode == 4) {
                    salary_information();
                    goto label;
                } else if (mode == 5){
                    break;
                } else { //user's input is wrong (larger than 3 or smaller than 1)
                    cout << "Wrong input, enter a number of the above only!\n\n";
                    continue;
                }
            }
		}

};
void runTheProject(){
    System s;
    s.start();
}
int main(){
	runTheProject();
	return 0;
}
