#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int MAX_PATIENTS = 100; 
struct Patient {
    int patientID;
    string name;
    int age;
    string disease;
    int roomNumber;
};

Patient patients[MAX_PATIENTS];
int numPatients = 0; 
void addPatient() {
    if (numPatients >= MAX_PATIENTS) {
        cout << "Maximum number of patients reached." << endl;
        return;
    }

    Patient newPatient;

    cout << "Enter patient ID: ";
    cin >> newPatient.patientID;
    cin.ignore();  
    cout << "Enter name: ";
    getline(cin, newPatient.name);

    cout << "Enter age: ";
    cin >> newPatient.age;

    cout << "Enter disease: ";
    cin.ignore();  
    getline(cin, newPatient.disease);

    cout << "Enter room number: ";
    cin >> newPatient.roomNumber;

    patients[numPatients++] = newPatient; 
    cout << "Patient added successfully!" << endl;
}

void searchPatient() {
    int patientID;
    cout << "Enter patient ID to search: ";
    cin >> patientID;

    bool found = false;
    for (int i = 0; i < numPatients; ++i) {
        if (patients[i].patientID == patientID) {
            cout << "Patient found:" << endl;
            cout << "Name: " << patients[i].name << endl;
            cout << "Age: " << patients[i].age << endl;
            cout << "Disease: " << patients[i].disease << endl;
            cout << "Room Number: " << patients[i].roomNumber << endl;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Patient not found." << endl;
    }
}

void displayPatients() {
    if (numPatients == 0) {
        cout << "No patients found." << endl;
        return;
    }

    cout << "List of patients:" << endl;
    for (int i = 0; i < numPatients; ++i) {
        cout << "Patient ID: " << patients[i].patientID << endl;
        cout << "Name: " << patients[i].name << endl;
        cout << "Age: " << patients[i].age << endl;
        cout << "Disease: " << patients[i].disease << endl;
        cout << "Room Number: " << patients[i].roomNumber << endl;
    
    }
}

void savePatientsToFile() {
    ofstream outfile("patients.txt");
    if (outfile.is_open()) {
        for (int i = 0; i < numPatients; ++i) {
            outfile << patients[i].patientID << ","
                    << patients[i].name << ","
                    << patients[i].age << ","
                    << patients[i].disease << ","
                    << patients[i].roomNumber << endl;
        }
        outfile.close();
        cout << "Patients saved to file successfully!" << endl;
    } else {
        cout << "Error opening file for writing." << endl;
    }
}

void loadPatientsFromFile() {
    ifstream infile("patients.txt");
    if (infile.is_open()) {
        string line;
        while (getline(infile, line) && numPatients < MAX_PATIENTS) {
            Patient patient;
            size_t pos = 0;
            string token;

            pos = line.find(",");
            token = line.substr(0, pos);
            patient.patientID = stoi(token);
            line.erase(0, pos + 1);

            pos = line.find(",");
            patient.name = line.substr(0, pos);
            line.erase(0, pos + 1);

            pos = line.find(",");
            token = line.substr(0, pos);
            patient.age = stoi(token);
            line.erase(0, pos + 1);
            pos = line.find(",");
            patient.disease = line.substr(0, pos);
            line.erase(0, pos + 1);
            patient.roomNumber = stoi(line);
            patients[numPatients++] = patient;
        }
        infile.close();
        cout << "Patients loaded from file successfully!" << endl;
    } else {
        cout << "Error opening file for reading." << endl;
    }
}

int main() {
    int choice;
    loadPatientsFromFile(); 

    do {
        cout << "\nHospital Patient Management System" << endl;
        cout << "1. Add new patient" << endl;
        cout << "2. Search for patient" << endl;
        cout << "3. Display all patients" << endl;
        cout << "4. Save patients to file" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: 
                addPatient();
                break;
            case 2: 
                searchPatient();
                break;
            case 3: 
                displayPatients();
                break;
            case 4: 
                savePatientsToFile();
                break;
            case 5: 
                cout << "Exiting..." << endl;
                break;
            default: 
                cout << "Invalid choice." << endl;
        }
    } while (choice != 5);

    return 0;
}