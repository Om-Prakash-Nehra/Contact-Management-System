#include <bits/stdc++.h>

using namespace std;

class Course {
public:
    string courseName;
    vector<shared_ptr<Course>> subCourses; 

    Course(string name) : courseName(name) {}

    void addSubCourse(shared_ptr<Course> subCourse) {
        subCourses.push_back(subCourse);
    }

    void displayCourse(int level = 0) const {
        for (int i = 0; i < level; ++i) cout << "--";
        cout << courseName << endl;
        for (const auto& subCourse : subCourses) {
            subCourse->displayCourse(level + 1);
        }
    }
};


class Student {
public:
    int studentID;
    string name;
    int age;
    list<shared_ptr<Course>> courses; 

    Student(int id, string name, int age) : studentID(id), name(name), age(age) {}

    void addCourse(shared_ptr<Course> course) {
        courses.push_back(course);
    }

    void displayStudent() const {
        cout << "ID: " << studentID << ", Name: " << name << ", Age: " << age << endl;
        cout << "Courses: " << endl;
        if (courses.empty()) {
        cout<<"No courses Enrolled"<<endl;
        }
        for (const auto& course : courses) {
            course->displayCourse();
        }
    }
};

class StudentManagementSystem {
    vector<shared_ptr<Student>> students; 

public:
    void addStudent(int id, string name, int age) {
        students.push_back(make_shared<Student>(id, name, age));
    }

    void updateStudent(int id, string newName, int newAge) {
        for (auto& student : students) {
            if (student->studentID == id) {
                student->name = newName;
                student->age = newAge;
                return;
            }
        }
        cout << "Student with ID " << id << " not found." << endl;
    }

    void addCourseToStudent(int id, shared_ptr<Course> course) {
        bool found = false;
        for (auto& student : students) {
            if (student->studentID == id) {
                student->addCourse(course);
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Student with ID " << id << " not found." << endl;
        }
    }

    void displayAllStudents() const {
        for (const auto& student : students) {
            student->displayStudent();
        }
    }

    vector<shared_ptr<Student>>& getStudents() {
        return students;
    }
    
    const vector<shared_ptr<Student>>& getStudents() const {
        return students;
    }
};

int main() {
    StudentManagementSystem sms;
    int choice, id, age;
    string name, courseName;

    while (true) {
        cout << "\nStudent Management System\n";
        cout << "1. Add Student\n";
        cout << "2. Update Student\n";
        cout << "3. Add Course to Student\n";
        cout << "4. Display All Students\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); 
        switch (choice) {
        case 1:
            cout << "Enter Student ID: ";
            cin >> id;
            cin.ignore(); 
            cout << "Enter Student Name: ";
            getline(cin, name); 
            cout << "Enter Student Age: ";
            cin >> age;
            sms.addStudent(id, name, age);
            break;
        case 2:
            cout << "Enter Student ID to Update: ";
            cin >> id;
            cin.ignore(); 
            cout << "Enter New Name: ";
            getline(cin, name); 
            cout << "Enter New Age: ";
            cin >> age;
            sms.updateStudent(id, name, age);
            break;
        case 3:
            {
                cout << "Enter Student ID to Add Course: ";
                cin >> id;
                cin.ignore(); 
                cout << "Enter Course Name: ";
                getline(cin, courseName); 

                auto newCourse = make_shared<Course>(courseName);
                bool found = false;

                for (auto& student : sms.getStudents()) {
                    if (student->studentID == id) {
                        student->addCourse(newCourse);
                        found = true;
                        break;
                    }
                }

                if (!found) {
                    cout << "Student with ID " << id << " not found." << endl;
                }
            }
            break;
        case 4:
            sms.displayAllStudents();
            break;
        case 5:
            return 0; 
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}

