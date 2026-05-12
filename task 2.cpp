#include <iostream>
#include <limits>
#include <cctype>
using namespace std;

const int MAX = 100;

int ids[MAX];
string names[MAX];
int marks[MAX];
char grade[MAX];

int countStudents = 0;

char calculateGrade(int m) {
    if (m >= 90) return 'A';
    else if (m >= 80) return 'B';
    else if (m >= 70) return 'C';
    else if (m >= 60) return 'D';
    else return 'F';
}


bool isValidName(string name) {
    if (name.length() == 0) return false;

    for (int i = 0; i < name.length(); i++) {
        char c = name[i];

        if (!isalpha(c) && c != ' ')
            return false;
    }
    return true;
}

void addData() {

    if (countStudents >= MAX) {
        cout << "Storage Full!\n";
        return;
    }

    string tempName;
    int tempID;
    int tempMarks;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter Name (alphabets only): ";
    getline(cin, tempName);

    if (!isValidName(tempName)) {
        cout << "Invalid Name!\n";
        return;
    }

    cout << "Enter Student ID (integer only): ";
    cin >> tempID;

    if (cin.fail()) {
        cout << "Invalid ID!\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    cout << "Enter Marks (0 - 100): ";
    cin >> tempMarks;

    if (cin.fail() || tempMarks < 0 || tempMarks > 100) {
        cout << "Invalid Marks!\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    names[countStudents] = tempName;
    ids[countStudents] = tempID;
    marks[countStudents] = tempMarks;
    grade[countStudents] = calculateGrade(tempMarks);

    countStudents++;

    cout << "Record Added Successfully!\n";
}

void displayData() {
    if (countStudents == 0) {
        cout << "No records found!\n";
        return;
    }

    cout << "\n--- Student Records ---\n";

    for (int i = 0; i < countStudents; i++) {
        cout << "Name: " << names[i]
             << " | ID: " << ids[i]
             << " | Marks: " << marks[i]
             << " | Grade: " << grade[i] << endl;
    }
}

void searchData() {

    int choice;

    cout << "\nSearch by:\n";
    cout << "1. ID\n";
    cout << "2. Name\n";
    cout << "Enter choice: ";
    cin >> choice;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (choice == 1) {
        int searchID;
        cout << "Enter ID: ";
        cin >> searchID;

        for (int i = 0; i < countStudents; i++) {
            if (ids[i] == searchID) {
                cout << "\nRecord Found!\n";
                cout << "Name: " << names[i]
                     << " | ID: " << ids[i]
                     << " | Marks: " << marks[i]
                     << " | Grade: " << grade[i] << endl;
                return;
            }
        }

        cout << "Record Not Found!\n";
    }

    else if (choice == 2) {
        string searchName;

        cout << "Enter Name: ";
        getline(cin, searchName);

        for (int i = 0; i < countStudents; i++) {
            if (names[i] == searchName) {
                cout << "\nRecord Found!\n";
                cout << "Name: " << names[i]
                     << " | ID: " << ids[i]
                     << " | Marks: " << marks[i]
                     << " | Grade: " << grade[i] << endl;
                return;
            }
        }

        cout << "Record Not Found!\n";
    }

    else {
        cout << "Invalid Choice!\n";
    }
}

int main() {

    int choice;

    do {
        cout << "\n--- MENU ---\n";
        cout << "1. Add Data\n";
        cout << "2. Display Data\n";
        cout << "3. Search Data\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addData(); break;
            case 2: displayData(); break;
            case 3: searchData(); break;
            case 4: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }

    } while (choice != 4);

    return 0;
}
