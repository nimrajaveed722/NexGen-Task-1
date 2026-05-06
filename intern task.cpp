#include <iostream>
#include <limits> 
using namespace std;

void calculator() {
    int a, b, choice;
    cout << "\n--- Calculator ---\n";
    cout << "Enter two numbers: ";
    cin >> a >> b;

    if(cin.fail()) {
        cout << "Invalid input!\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    cout << "1. Add\n2. Subtract\n3. Multiply\n4. Divide\n";
    cout << "Choose operation: ";
    cin >> choice;

    switch(choice) {
        case 1:
            cout << "Result = " << a + b << endl;
            break;
        case 2:
            cout << "Result = " << a - b << endl;
            break;
        case 3:
            cout << "Result = " << a * b << endl;
            break;
        case 4:
            if(b != 0)
                cout << "Result = " << (float)a / b << endl;
            else
                cout << "Error! Division by zero.\n";
            break;
        default:
            cout << "Invalid choice!\n";
    }
}

void numberChecker() {
    int num;
    cout << "\n--- Number Checker ---\n";
    cout << "Enter a number: ";
    cin >> num;

    if(cin.fail()) {
        cout << "Invalid input!\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    if(num % 2 == 0)
        cout << "Even number\n";
    else
        cout << "Odd number\n";

    bool isPrime = true;
    if(num <= 1) isPrime = false;

    for(int i = 2; i <= num/2; i++) {
        if(num % i == 0) {
            isPrime = false;
            break;
        }
    }

    if(isPrime)
        cout << "Prime number\n";
    else
        cout << "Not a prime number\n";
}

void gradingSystem() {
    float marks;
    cout << "\n--- Grading System ---\n";
    cout << "Enter marks (0-100): ";
    cin >> marks;

    if(cin.fail()) {
        cout << "Invalid input! Enter numbers only.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    if(marks < 0 || marks > 100) {
        cout << "Invalid marks! Must be between 0 and 100.\n";
        return;
    }

    if(marks >= 90)
        cout << "Grade: A\n";
    else if(marks >= 75)
        cout << "Grade: B\n";
    else if(marks >= 60)
        cout << "Grade: C\n";
    else if(marks >= 50)
        cout << "Grade: D\n";
    else
        cout << "Grade: F\n";
}

int main() {
    int choice;

    do {
        cout << "\n===== MAIN MENU =====\n";
        cout << "1. Calculator\n";
        cout << "2. Number Checker\n";
        cout << "3. Grading System\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if(cin.fail()) {
            cout << "Invalid input!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch(choice) {
            case 1:
                calculator();
                break;
            case 2:
                numberChecker();
                break;
            case 3:
                gradingSystem();
                break;
            case 4:
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid choice! Try again.\n";
        }

    } while(choice != 4);

    return 0;
}
