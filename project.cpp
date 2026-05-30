#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cctype>
#include <cstdlib>
using namespace std;

const int MAX = 100;

class Student {
public:
    int id;
    string name;
    float marks;
    char grade;
};

Student students[MAX];
int totalStudents = 0;

// Function to calculate grade
char calculateGrade(float marks) {

    if (marks >= 90)
        return 'A';

    else if (marks >= 80)
        return 'B';

    else if (marks >= 70)
        return 'C';

    else if (marks >= 60)
        return 'D';
        
    else if (marks >= 50)    
        return 'E';
        
    else
        return 'F';
}

// Function to validate name
bool isValidName(string name) {

    for (int i = 0; i < name.length(); i++) {

        char c = name[i];

        if (!isalpha(c) && c != ' ') {
            return false;
        }
    }

    return true;
}

// Function to validate ID
bool isValidID(string id) {

    for (int i = 0; i < id.length(); i++) {

        if (!isdigit(id[i])) {
            return false;
        }
    }

    return true;
}

// Add Student
void addStudent() {

    if (totalStudents >= MAX) {

        cout << "\nStorage Full!\n";
        return;
    }

    Student s;

    cin.ignore();

    // Name Input
    while (true) {

        cout << "\nEnter Student Name: ";
        getline(cin, s.name);

        if (isValidName(s.name)) {
            break;
        }

        cout << "Invalid Name! Only alphabets allowed.\n";
    }

    // ID Input
    string tempID;

    while (true) {

        cout << "Enter Student ID: ";
        cin >> tempID;

        if (!isValidID(tempID)) {

            cout << "Invalid ID! Enter integers only.\n";
            continue;
        }

        s.id = atoi(tempID.c_str());
        break;
    }

    // Marks Input
    while (true) {

        cout << "Enter Marks (0-100): ";
        cin >> s.marks;

        if (cin.fail() || s.marks < 0 || s.marks > 100) {

            cout << "Invalid Marks! Enter between 0 and 100.\n";

            cin.clear();
            cin.ignore(1000, '\n');

            continue;
        }

        break;
    }

    s.grade = calculateGrade(s.marks);

    students[totalStudents] = s;
    totalStudents++;

    cout << "\nStudent Added Successfully!\n";
}

// Display Students
void displayStudents() {

    if (totalStudents == 0) {

        cout << "\nNo Records Found!\n";
        return;
    }

    cout << "\n===================================================\n";

    cout << left
         << setw(10) << "ID"
         << setw(20) << "Name"
         << setw(10) << "Marks"
         << setw(10) << "Grade" << endl;

    cout << "===================================================\n";

    for (int i = 0; i < totalStudents; i++) {

        cout << left
             << setw(10) << students[i].id
             << setw(20) << students[i].name
             << setw(10) << students[i].marks
             << setw(10) << students[i].grade
             << endl;
    }
}

// Search Student
void searchStudent() {

    int searchID;
    bool found = false;

    cout << "\nEnter Student ID to Search: ";
    cin >> searchID;

    if (cin.fail()) {

        cout << "Invalid ID! Enter integers only.\n";

        cin.clear();
        cin.ignore(1000, '\n');

        return;
    }

    for (int i = 0; i < totalStudents; i++) {

        if (students[i].id == searchID) {

            cout << "\nStudent Found!\n";

            cout << "ID: " << students[i].id << endl;
            cout << "Name: " << students[i].name << endl;
            cout << "Marks: " << students[i].marks << endl;
            cout << "Grade: " << students[i].grade << endl;

            found = true;
            break;
        }
    }

    if (!found) {
        cout << "\nStudent Not Found!\n";
    }
}

// Update Student
void updateStudent() {

    int updateID;
    bool found = false;

    cout << "\nEnter Student ID to Update: ";
    cin >> updateID;

    if (cin.fail()) {

        cout << "Invalid ID! Enter integers only.\n";

        cin.clear();
        cin.ignore(1000, '\n');

        return;
    }

    for (int i = 0; i < totalStudents; i++) {

        if (students[i].id == updateID) {

            while (true) {

                cout << "Enter New Marks (0-100): ";
                cin >> students[i].marks;

                if (cin.fail() || students[i].marks < 0 || students[i].marks > 100) {

                    cout << "Invalid Marks! Enter between 0 and 100.\n";

                    cin.clear();
                    cin.ignore(1000, '\n');

                    continue;
                }

                break;
            }

            students[i].grade = calculateGrade(students[i].marks);

            cout << "\nRecord Updated Successfully!\n";

            found = true;
            break;
        }
    }

    if (!found) {
        cout << "\nStudent Not Found!\n";
    }
}

// Delete Student
void deleteStudent() {

    int deleteID;
    bool found = false;

    cout << "\nEnter Student ID to Delete: ";
    cin >> deleteID;

    if (cin.fail()) {

        cout << "Invalid ID! Enter integers only.\n";

        cin.clear();
        cin.ignore(1000, '\n');

        return;
    }

    for (int i = 0; i < totalStudents; i++) {

        if (students[i].id == deleteID) {

            for (int j = i; j < totalStudents - 1; j++) {

                students[j] = students[j + 1];
            }

            totalStudents--;

            cout << "\nRecord Deleted Successfully!\n";

            found = true;
            break;
        }
    }

    if (!found) {
        cout << "\nStudent Not Found!\n";
    }
}

// Save Data
void saveToFile() {

    ofstream file("students.txt");

    for (int i = 0; i < totalStudents; i++) {

        file << students[i].id << endl;
        file << students[i].name << endl;
        file << students[i].marks << endl;
        file << students[i].grade << endl;
    }

    file.close();

    cout << "\nData Saved Successfully!\n";
}

// Load Data
void loadFromFile() {

    ifstream file("students.txt");

    if (!file) {
        return;
    }

    while (file >> students[totalStudents].id) {

        file.ignore();

        getline(file, students[totalStudents].name);

        file >> students[totalStudents].marks;
        file >> students[totalStudents].grade;

        totalStudents++;
    }

    file.close();
}

// Main Function
int main() {

    loadFromFile();

    int choice;

    do {

        cout << "\n========== STUDENT MANAGEMENT SYSTEM ==========\n";

        cout << "1. Add Student\n";
        cout << "2. Display Students\n";
        cout << "3. Search Student\n";
        cout << "4. Update Student\n";
        cout << "5. Delete Student\n";
        cout << "6. Save Data\n";
        cout << "7. Exit\n";

        cout << "\nEnter Your Choice: ";
        cin >> choice;

        if (cin.fail()) {

            cout << "Invalid Input!\n";

            cin.clear();
            cin.ignore(1000, '\n');

            continue;
        }

        switch (choice) {

        case 1:
            addStudent();
            break;

        case 2:
            displayStudents();
            break;

        case 3:
            searchStudent();
            break;

        case 4:
            updateStudent();
            break;

        case 5:
            deleteStudent();
            break;

        case 6:
            saveToFile();
            break;

        case 7:
            saveToFile();
            cout << "\nProgram Exited Successfully!\n";
            break;

        default:
            cout << "\nInvalid Choice!\n";
        }

    } while (choice != 7);

    return 0;
}
