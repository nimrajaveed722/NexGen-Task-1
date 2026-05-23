#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <sstream>
#include <ctime>
using namespace std;

int strToInt(const string& s) {
    istringstream ss(s); int v; ss >> v; return v;
}

double strToDouble(const string& s) {
    istringstream ss(s); double v; ss >> v; return v;
}

void clearBuffer() { cin.ignore(1000, '\n'); }

string getContactInput(const string& prompt) {
    string val;
    while (true) {
        cout << prompt;
        getline(cin, val);
        size_t s = val.find_first_not_of(" \t\r\n");
        size_t e = val.find_last_not_of(" \t\r\n");
        if (s == string::npos) { cout << "  [ERROR] Contact cannot be empty!\n"; continue; }
        val = val.substr(s, e - s + 1);
        if (val.length() != 11) {
            cout << "  [ERROR] Contact must be exactly 11 digits (e.g. 03001234567).\n";
            continue;
        }
        bool allDigits = true;
        for (int i = 0; i < (int)val.length(); i++) {
            if (val[i] < '0' || val[i] > '9') { allDigits = false; break; }
        }
        if (!allDigits) {
            cout << "  [ERROR] Contact must contain digits only (no spaces or dashes).\n";
            continue;
        }
        return val;
    }
}

string getCurrentDateTime() {
    time_t now = time(0);
    char buf[20];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M", localtime(&now));
    return string(buf);
}

class Patient {
public:
    int    patientId;
    string name;
    int    age;
    string gender;
    string contact;
    string disease;
    string doctorAssigned;
    string admitDate;
    string ward;
    double billAmount;

    Patient() : patientId(0), age(0), billAmount(0.0) {}

    Patient(int id, string nm, int ag, string gen,
            string con, string dis, string doc,
            string date, string wd, double bill)
        : patientId(id), name(nm), age(ag), gender(gen),
          contact(con), disease(dis), doctorAssigned(doc),
          admitDate(date), ward(wd), billAmount(bill) {}

    void printRecord() const {
        cout << "\n";
        cout << "  ============================================\n";
        cout << "           PATIENT RECORD\n";
        cout << "  ============================================\n";
        cout << "  Patient ID   : " << patientId      << "\n";
        cout << "  Name         : " << name           << "\n";
        cout << "  Age          : " << age            << "\n";
        cout << "  Gender       : " << gender         << "\n";
        cout << "  Contact      : " << contact        << "\n";
        cout << "  Disease      : " << disease        << "\n";
        cout << "  Doctor       : " << doctorAssigned << "\n";
        cout << "  Admit Date   : " << admitDate      << "\n";
        cout << "  Ward         : " << ward           << "\n";
        cout << "  Bill Amount  : Rs. " << fixed << setprecision(2) << billAmount << "\n";
        cout << "  ============================================\n\n";
    }
};

class Doctor {
public:
    int    doctorId;
    string name;
    string specialization;
    string contact;

    Doctor() : doctorId(0) {}

    Doctor(int id, string nm, string spec, string con)
        : doctorId(id), name(nm), specialization(spec), contact(con) {}

    void display() const {
        cout << "  [" << doctorId << "] "
             << left << setw(22) << name
             << setw(22) << specialization
             << contact << "\n";
    }
};

class Appointment {
public:
    int    appointmentId;
    int    patientId;
    string patientName;
    int    doctorId;
    string doctorName;
    string dateTime;
    string status;

    Appointment() : appointmentId(0), patientId(0), doctorId(0) {}

    Appointment(int aid, int pid, string pname,
                int did, string dname, string dt, string st)
        : appointmentId(aid), patientId(pid), patientName(pname),
          doctorId(did), doctorName(dname), dateTime(dt), status(st) {}

    void printRecord() const {
        cout << "  ----------------------------------------\n";
        cout << "  Appointment  : #" << appointmentId << "\n";
        cout << "  Patient      : [" << patientId << "] " << patientName << "\n";
        cout << "  Doctor       : [" << doctorId  << "] " << doctorName  << "\n";
        cout << "  Date & Time  : " << dateTime << "\n";
        cout << "  Status       : " << status   << "\n";
        cout << "  ----------------------------------------\n\n";
    }
};

class FileManager {
public:
    string patientFile;
    string appointmentFile;

    FileManager(string pf, string af)
        : patientFile(pf), appointmentFile(af) {}

    void savePatient(const Patient& p) {
        ofstream f(patientFile.c_str(), ios::app);
        if (!f.is_open()) { cout << "  [ERROR] Cannot open patient file!\n"; return; }
        f << "PAT_START\n"
          << p.patientId      << "\n"
          << p.name           << "\n"
          << p.age            << "\n"
          << p.gender         << "\n"
          << p.contact        << "\n"
          << p.disease        << "\n"
          << p.doctorAssigned << "\n"
          << p.admitDate      << "\n"
          << p.ward           << "\n"
          << p.billAmount     << "\n"
          << "PAT_END\n";
        f.close();
    }

    vector<Patient> loadAllPatients() {
        vector<Patient> list;
        ifstream f(patientFile.c_str());
        if (!f.is_open()) return list;
        string line;
        while (getline(f, line)) {
            if (line == "PAT_START") {
                Patient p;
                string age, bill;
                f >> p.patientId; f.ignore(1000, '\n');
                getline(f, p.name);
                getline(f, age);   p.age = strToInt(age);
                getline(f, p.gender);
                getline(f, p.contact);
                getline(f, p.disease);
                getline(f, p.doctorAssigned);
                getline(f, p.admitDate);
                getline(f, p.ward);
                getline(f, bill);  p.billAmount = strToDouble(bill);
                list.push_back(p);
            }
        }
        f.close();
        return list;
    }

    void rewritePatients(const vector<Patient>& list) {
        ofstream f(patientFile.c_str(), ios::trunc);
        for (int i = 0; i < (int)list.size(); i++) {
            const Patient& p = list[i];
            f << "PAT_START\n"
              << p.patientId      << "\n"
              << p.name           << "\n"
              << p.age            << "\n"
              << p.gender         << "\n"
              << p.contact        << "\n"
              << p.disease        << "\n"
              << p.doctorAssigned << "\n"
              << p.admitDate      << "\n"
              << p.ward           << "\n"
              << p.billAmount     << "\n"
              << "PAT_END\n";
        }
        f.close();
    }

    int getNextPatientId() {
        vector<Patient> list = loadAllPatients();
        if (list.empty()) return 1001;
        return list[list.size() - 1].patientId + 1;
    }

    void saveAppointment(const Appointment& a) {
        ofstream f(appointmentFile.c_str(), ios::app);
        if (!f.is_open()) { cout << "  [ERROR] Cannot open appointment file!\n"; return; }
        f << "APT_START\n"
          << a.appointmentId << "\n"
          << a.patientId     << "\n"
          << a.patientName   << "\n"
          << a.doctorId      << "\n"
          << a.doctorName    << "\n"
          << a.dateTime      << "\n"
          << a.status        << "\n"
          << "APT_END\n";
        f.close();
    }

    vector<Appointment> loadAllAppointments() {
        vector<Appointment> list;
        ifstream f(appointmentFile.c_str());
        if (!f.is_open()) return list;
        string line;
        while (getline(f, line)) {
            if (line == "APT_START") {
                Appointment a;
                string aid, pid, did;
                getline(f, aid); a.appointmentId = strToInt(aid);
                getline(f, pid); a.patientId     = strToInt(pid);
                getline(f, a.patientName);
                getline(f, did); a.doctorId      = strToInt(did);
                getline(f, a.doctorName);
                getline(f, a.dateTime);
                getline(f, a.status);
                list.push_back(a);
            }
        }
        f.close();
        return list;
    }

    void rewriteAppointments(const vector<Appointment>& list) {
        ofstream f(appointmentFile.c_str(), ios::trunc);
        for (int i = 0; i < (int)list.size(); i++) {
            const Appointment& a = list[i];
            f << "APT_START\n"
              << a.appointmentId << "\n"
              << a.patientId     << "\n"
              << a.patientName   << "\n"
              << a.doctorId      << "\n"
              << a.doctorName    << "\n"
              << a.dateTime      << "\n"
              << a.status        << "\n"
              << "APT_END\n";
        }
        f.close();
    }

    int getNextAppointmentId() {
        vector<Appointment> list = loadAllAppointments();
        if (list.empty()) return 2001;
        return list[list.size() - 1].appointmentId + 1;
    }
};

class Hospital {
private:
    vector<Doctor> doctors;
    FileManager    fm;

    int getIntInput(const string& prompt, int mn, int mx) {
        int val;
        while (true) {
            cout << prompt;
            if (cin >> val && val >= mn && val <= mx) {
                clearBuffer(); return val;
            }
            cin.clear(); clearBuffer();
            cout << "  [ERROR] Enter a value between " << mn << " and " << mx << ".\n";
        }
    }

    string getStringInput(const string& prompt) {
        string val;
        while (true) {
            cout << prompt;
            getline(cin, val);
            size_t s = val.find_first_not_of(" \t\r\n");
            size_t e = val.find_last_not_of(" \t\r\n");
            if (s != string::npos) return val.substr(s, e - s + 1);
            cout << "  [ERROR] Field cannot be empty!\n";
        }
    }

    Doctor* findDoctor(int id) {
        for (int i = 0; i < (int)doctors.size(); i++)
            if (doctors[i].doctorId == id) return &doctors[i];
        return NULL;
    }

    void displayDoctors() {
        cout << "\n  ============================================\n";
        cout << "               AVAILABLE DOCTORS\n";
        cout << "  ============================================\n";
        cout << "  " << left << setw(6) << "ID"
             << setw(22) << "Name"
             << setw(22) << "Specialization"
             << "Contact\n";
        cout << "  --------------------------------------------\n";
        for (int i = 0; i < (int)doctors.size(); i++)
            doctors[i].display();
        cout << "  ============================================\n\n";
    }

    double wardCharge(const string& ward, int days) {
        if (ward == "ICU")     return days * 5000.0;
        if (ward == "Private") return days * 3000.0;
        return days * 1000.0;
    }

public:
    Hospital() : fm("patients.txt", "appointments.txt") {
        doctors.push_back(Doctor(1, "Dr. Ahmed Khan",     "Cardiology",   "0300-1234567"));
        doctors.push_back(Doctor(2, "Dr. Sara Malik",     "Neurology",    "0301-2345678"));
        doctors.push_back(Doctor(3, "Dr. Usman Raza",     "Orthopedics",  "0302-3456789"));
        doctors.push_back(Doctor(4, "Dr. Ayesha Noor",    "Pediatrics",   "0303-4567890"));
        doctors.push_back(Doctor(5, "Dr. Bilal Chaudhry", "General Med.", "0304-5678901"));
        doctors.push_back(Doctor(6, "Dr. Fatima Sheikh",  "Dermatology",  "0305-6789012"));
    }

    void admitPatient() {
        cout << "\n  === ADMIT NEW PATIENT ===\n";
        string name    = getStringInput("  Patient Name              : ");
        int    age     = getIntInput   ("  Age                       : ", 1, 120);
        clearBuffer();
        string gender  = getStringInput("  Gender (M/F/Other)        : ");
        string contact = getContactInput("  Contact (11 digits)       : ");
        string disease = getStringInput("  Disease/Complaint         : ");

        displayDoctors();
        int did = getIntInput("  Select Doctor ID          : ", 1, (int)doctors.size());
        Doctor* doc = findDoctor(did);

        cout << "\n  Ward Options:\n";
        cout << "  [1] General  (Rs. 1000/day)\n";
        cout << "  [2] Private  (Rs. 3000/day)\n";
        cout << "  [3] ICU      (Rs. 5000/day)\n";
        int wChoice = getIntInput("  Select Ward               : ", 1, 3);
        string ward = (wChoice == 1) ? "General" : (wChoice == 2) ? "Private" : "ICU";

        int days = getIntInput("  Expected Stay (days)      : ", 1, 365);
        double bill = wardCharge(ward, days);

        int pid = fm.getNextPatientId();
        Patient p(pid, name, age, gender, contact, disease,
                  doc->name, getCurrentDateTime(), ward, bill);
        fm.savePatient(p);
        p.printRecord();
        cout << "  [OK] Patient admitted! ID: " << pid << "\n\n";
    }

    void viewAllPatients() {
        vector<Patient> list = fm.loadAllPatients();
        if (list.empty()) { cout << "\n  [INFO] No patients on record.\n\n"; return; }
        cout << "\n  === ALL PATIENT RECORDS (" << list.size() << ") ===\n";
        for (int i = 0; i < (int)list.size(); i++)
            list[i].printRecord();
    }

    void searchPatient() {
        int id = getIntInput("\n  Enter Patient ID to search: ", 1, 99999);
        vector<Patient> list = fm.loadAllPatients();
        for (int i = 0; i < (int)list.size(); i++) {
            if (list[i].patientId == id) { list[i].printRecord(); return; }
        }
        cout << "  [INFO] Patient #" << id << " not found.\n\n";
    }

    void updatePatient() {
        int id = getIntInput("\n  Enter Patient ID to update: ", 1, 99999);
        vector<Patient> list = fm.loadAllPatients();
        bool found = false;
        for (int i = 0; i < (int)list.size(); i++) {
            if (list[i].patientId == id) {
                found = true;
                cout << "\n  Current record:\n";
                list[i].printRecord();
                cout << "  What to update?\n";
                cout << "  [1] Disease / Complaint\n";
                cout << "  [2] Assigned Doctor\n";
                cout << "  [3] Ward\n";
                cout << "  [4] Bill Amount\n";
                int ch = getIntInput("  Choice: ", 1, 4);
                if (ch == 1) {
                    list[i].disease = getStringInput("  New Disease/Complaint: ");
                } else if (ch == 2) {
                    displayDoctors();
                    int did = getIntInput("  New Doctor ID: ", 1, (int)doctors.size());
                    list[i].doctorAssigned = findDoctor(did)->name;
                } else if (ch == 3) {
                    cout << "  [1] General  [2] Private  [3] ICU\n";
                    int w = getIntInput("  Ward: ", 1, 3);
                    list[i].ward = (w == 1) ? "General" : (w == 2) ? "Private" : "ICU";
                } else {
                    list[i].billAmount = strToDouble(getStringInput("  New Bill Amount (Rs.): "));
                }
                fm.rewritePatients(list);
                cout << "  [OK] Record updated!\n\n";
                break;
            }
        }
        if (!found) cout << "  [INFO] Patient #" << id << " not found.\n\n";
    }

    void dischargePatient() {
        int id = getIntInput("\n  Enter Patient ID to discharge: ", 1, 99999);
        vector<Patient> list = fm.loadAllPatients();
        bool found = false;
        for (int i = 0; i < (int)list.size(); i++) {
            if (list[i].patientId == id) {
                found = true;
                cout << "\n  ============================================\n";
                cout << "            DISCHARGE SUMMARY\n";
                cout << "  ============================================\n";
                list[i].printRecord();
                cout << "  [DISCHARGED] Patient " << list[i].name
                     << " discharged on " << getCurrentDateTime() << "\n";
                cout << "  Final Bill: Rs. " << fixed << setprecision(2)
                     << list[i].billAmount << "\n";
                cout << "  ============================================\n\n";
                list.erase(list.begin() + i);
                fm.rewritePatients(list);
                cout << "  [OK] Patient record removed from active list.\n\n";
                break;
            }
        }
        if (!found) cout << "  [INFO] Patient #" << id << " not found.\n\n";
    }

    void bookAppointment() {
        cout << "\n  === BOOK APPOINTMENT ===\n";
        string pname = getStringInput("  Patient Name: ");
        vector<Patient> plist = fm.loadAllPatients();
        cout << "\n  Active Patient IDs:\n";
        for (int i = 0; i < (int)plist.size(); i++)
            cout << "    [" << plist[i].patientId << "] " << plist[i].name << "\n";
        int pid = getIntInput("  Patient ID (0 if walk-in): ", 0, 99999);
        displayDoctors();
        int did = getIntInput("  Doctor ID: ", 1, (int)doctors.size());
        Doctor* doc = findDoctor(did);
        string dt = getStringInput("  Date & Time (e.g. 2026-06-01 10:00): ");
        int aid = fm.getNextAppointmentId();
        Appointment a(aid, pid, pname, did, doc->name, dt, "Scheduled");
        fm.saveAppointment(a);
        cout << "\n  [OK] Appointment booked! ID: " << aid << "\n";
        a.printRecord();
    }

    void viewAllAppointments() {
        vector<Appointment> list = fm.loadAllAppointments();
        if (list.empty()) { cout << "\n  [INFO] No appointments found.\n\n"; return; }
        cout << "\n  === ALL APPOINTMENTS (" << list.size() << ") ===\n\n";
        for (int i = 0; i < (int)list.size(); i++)
            list[i].printRecord();
    }

    void cancelAppointment() {
        int id = getIntInput("\n  Enter Appointment ID to cancel: ", 1, 99999);
        vector<Appointment> list = fm.loadAllAppointments();
        bool found = false;
        for (int i = 0; i < (int)list.size(); i++) {
            if (list[i].appointmentId == id) {
                list[i].status = "Cancelled";
                fm.rewriteAppointments(list);
                cout << "  [OK] Appointment #" << id << " cancelled.\n\n";
                found = true; break;
            }
        }
        if (!found) cout << "  [INFO] Appointment #" << id << " not found.\n\n";
    }

    void generateBill() {
        int id = getIntInput("\n  Enter Patient ID for billing: ", 1, 99999);
        vector<Patient> list = fm.loadAllPatients();
        for (int i = 0; i < (int)list.size(); i++) {
            if (list[i].patientId == id) {
                const Patient& p = list[i];
                cout << "\n";
                cout << "  ============================================\n";
                cout << "              HOSPITAL BILL\n";
                cout << "  ============================================\n";
                cout << "  Patient ID   : " << p.patientId      << "\n";
                cout << "  Name         : " << p.name           << "\n";
                cout << "  Ward         : " << p.ward           << "\n";
                cout << "  Doctor       : " << p.doctorAssigned << "\n";
                cout << "  Admit Date   : " << p.admitDate      << "\n";
                cout << "  --------------------------------------------\n";
                cout << "  Ward Charges : Rs. " << fixed << setprecision(2) << p.billAmount << "\n";
                cout << "  Misc. Charges: Rs. 500.00\n";
                double total = p.billAmount + 500.0;
                cout << "  --------------------------------------------\n";
                cout << "  TOTAL DUE    : Rs. " << total << "\n";
                cout << "  ============================================\n\n";
                return;
            }
        }
        cout << "  [INFO] Patient #" << id << " not found.\n\n";
    }

    void viewDoctors() { displayDoctors(); }

    void run() {
        cout << "\n";
        cout << "  ============================================\n";
        cout << "    WELCOME TO CITY CARE HOSPITAL\n";
        cout << "      Hospital Management System\n";
        cout << "  ============================================\n";

        int choice;
        do {
            cout << "\n  ========== MAIN MENU ===========\n";
            cout << "  [1]  Admit New Patient\n";
            cout << "  [2]  View All Patients\n";
            cout << "  [3]  Search Patient by ID\n";
            cout << "  [4]  Update Patient Record\n";
            cout << "  [5]  Discharge Patient\n";
            cout << "  [6]  Book Appointment\n";
            cout << "  [7]  View All Appointments\n";
            cout << "  [8]  Cancel Appointment\n";
            cout << "  [9]  Generate Patient Bill\n";
            cout << "  [10] View Available Doctors\n";
            cout << "  [0]  Exit\n";
            cout << "  =================================\n";

            choice = getIntInput("  Enter your choice: ", 0, 10);

            switch (choice) {
                case 1:  admitPatient();        break;
                case 2:  viewAllPatients();     break;
                case 3:  searchPatient();       break;
                case 4:  updatePatient();       break;
                case 5:  dischargePatient();    break;
                case 6:  bookAppointment();     break;
                case 7:  viewAllAppointments(); break;
                case 8:  cancelAppointment();   break;
                case 9:  generateBill();        break;
                case 10: viewDoctors();         break;
                case 0:
                    cout << "\n  Thank you! Stay Healthy. Goodbye!\n\n";
                    break;
            }
        } while (choice != 0);
    }
};

int main() {
    Hospital hospital;
    hospital.run();
    return 0;
}

