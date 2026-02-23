#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

class Student {
public:
    int roll;
    char name[50];
    float marks;

    void input() {
        cout << "Enter Roll Number: ";
        cin >> roll;
        cout << "Enter Name: ";
        cin.ignore();
        cin.getline(name, 50);
        cout << "Enter Marks: ";
        cin >> marks;
    }

    void display() const {
        cout << "\nRoll No: " << roll;
        cout << "\nName   : " << name;
        cout << "\nMarks  : " << marks << endl;
    }

    int getRoll() const {
        return roll;
    }
};

void addStudent() {
    Student s;
    ofstream file("students.dat", ios::binary | ios::app);
    s.input();
    file.write((char*)&s, sizeof(s));
    file.close();
    cout << "Record Added Successfully!\n";
}

void displayAll() {
    Student s;
    ifstream file("students.dat", ios::binary);
    while (file.read((char*)&s, sizeof(s))) {
        s.display();
        cout << "----------------------";
    }
    file.close();
}

void searchStudent() {
    int rollNo;
    bool found = false;
    Student s;
    ifstream file("students.dat", ios::binary);

    cout << "Enter Roll Number to Search: ";
    cin >> rollNo;

    while (file.read((char*)&s, sizeof(s))) {
        if (s.getRoll() == rollNo) {
            s.display();
            found = true;
            break;
        }
    }
    file.close();

    if (!found)
        cout << "Record Not Found!\n";
}

void deleteStudent() {
    int rollNo;
    bool found = false;
    Student s;
    ifstream file("students.dat", ios::binary);
    ofstream temp("temp.dat", ios::binary);

    cout << "Enter Roll Number to Delete: ";
    cin >> rollNo;

    while (file.read((char*)&s, sizeof(s))) {
        if (s.getRoll() != rollNo) {
            temp.write((char*)&s, sizeof(s));
        } else {
            found = true;
        }
    }

    file.close();
    temp.close();

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found)
        cout << "Record Deleted Successfully!\n";
    else
        cout << "Record Not Found!\n";
}

int main() {
    int choice;

    do {
        cout << "\n====== Student Record Management ======\n";
        cout << "1. Add Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Search Student\n";
        cout << "4. Delete Student\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: addStudent(); break;
        case 2: displayAll(); break;
        case 3: searchStudent(); break;
        case 4: deleteStudent(); break;
        case 5: cout << "Exiting Program...\n"; break;
        default: cout << "Invalid Choice!\n";
        }
    } while (choice != 5);

    return 0;
}