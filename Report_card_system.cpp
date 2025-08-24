#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

class Student {
protected:
    string Name;
    int Age;
    int Standard;
public:
    void data_input() {
        cout << "Enter the name of student: ";
        cin.ignore();
        getline(cin, Name);
        cout << "Enter the current age of student: ";
        cin >> Age;
        cout << "Enter the standard (class) " << Name << " is studying in: ";
        cin >> Standard;
    }
    string getName() { return Name; }
};

class Marks : public Student {
    int Marks[5];
    int total;
    float percentage;
    char grade;
public:
    void mark_input() {
        total = 0;
        for (int i = 0; i < 5; i++) {
            cout << "Enter marks of " << Name << " in Subject " << i + 1 << " (out of 100): ";
            cin >> Marks[i];
            total += Marks[i];
        }
        percentage = (total / 500.0f) * 100;
        grade = calculate_grade();
    }

    char calculate_grade() {
        if (percentage >= 90) return 'A';
        else if (percentage >= 75) return 'B';
        else if (percentage >= 60) return 'C';
        else if (percentage >= 50) return 'D';
        else return 'F';
    }

    void save_to_file() {
        ofstream out("Studentreport.csv", ios::app);
        if (!out) {
            cout << "Error opening file!\n";
            return;
        }
        out << Name << "," << Age << "," << Standard;
        for (int i = 0; i < 5; i++) out << "," << Marks[i];
        out << "," << total << "," << fixed << setprecision(2) << percentage << "," << grade << "\n";
        out.close();
        cout << "Data saved successfully!\n";
    }
};

void print_all_data() {
    ifstream in("Studentreport.csv");
    if (!in) {
        cout << "No data found.\n";
        return;
    }
    string line;
    cout << "\n--- All Student Data ---\n";
    while (getline(in, line)) {
        cout << line << endl;
    }
    in.close();
}

void search_student() {
    string search_name;
    cout << "Enter student's name to search: ";
    cin.ignore();
    getline(cin, search_name);

    ifstream in("Studentreport.csv");
    if (!in) {
        cout << "No data found.\n";
        return;
    }

    string line;
    bool found = false;
    while (getline(in, line)) {
        stringstream ss(line);
        string name;
        getline(ss, name, ',');
        if (name == search_name) {
            cout << "Record found:\n" << line << endl;
            found = true;
            break;
        }
    }
    in.close();
    if (!found) {
        cout << "Student not found.\n";
    }
}

void download_report_card() {
    string search_name;
    cout << "Enter student's name to download report card: ";
    cin.ignore();
    getline(cin, search_name);

    ifstream in("Studentreport.csv");
    if (!in) {
        cout << "No data found.\n";
        return;
    }

    
    string line;
    bool found = false;
    while (getline(in, line)) {
        stringstream ss(line);
        string name;
        getline(ss, name, ',');
        if (name == search_name) {
            found = true;
            ofstream out(search_name + "_ReportCard.txt");
            if (!out) {
                cout << "Error creating report card.\n";
                return;
            }

            string age, std, m1, m2, m3, m4, m5, total, perc, grade;
            getline(ss, age, ',');
            getline(ss, std, ',');
            getline(ss, m1, ',');
            getline(ss, m2, ',');
            getline(ss, m3, ',');
            getline(ss, m4, ',');
            getline(ss, m5, ',');
            getline(ss, total, ',');
            getline(ss, perc, ',');
            getline(ss, grade, ',');

            out << "----- Report Card -----\n";
            out << "Name: " << name << "\n";
            out << "Age: " << age << "\n";
            out << "Standard: " << std << "\n";
            out << "Marks: " << m1 << " " << m2 << " " << m3 << " " << m4 << " " << m5 << "\n";
            out << "Total: " << total << "\n";
            out << "Percentage: " << perc << "%\n";
            out << "Grade: " << grade << "\n";
            out.close();

            cout << "Report card saved as " << search_name << "_ReportCard.txt\n";
            break;
        }
    }
    in.close();
    if (!found) {
        cout << "Student not found.\n";
    }
}

int main() {
    int choice;
    do {
        cout << "\n--- Student Report Management System ---\n";
        cout << "1. Add student data\n";
        cout << "2. Search student data\n";
        cout << "3. Print all student data\n";
        cout << "4. Download student's report card\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                Marks m;
                m.data_input();
                m.mark_input();
                m.save_to_file();
                break;
            }
            case 2:
                search_student();
                break;
            case 3:
                print_all_data();
                break;
            case 4:
                download_report_card();
                break;
            case 5:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 5);

    return 0;
}
