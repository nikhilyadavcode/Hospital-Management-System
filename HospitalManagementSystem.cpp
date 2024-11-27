#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;

class Patient {
public:
    Patient(int id, string name, string ailment) : id(id), name(name), ailment(ailment) {}
    void display() const {
        cout << "ID: " << id << ", Name: " << name << ", Ailment: " << ailment << endl;
    }
    int getId() const { return id; }
    string getName() const { return name; }
    string getAilment() const { return ailment; }
    void setAilment(string newAilment) { ailment = newAilment; }

private:
    int id;
    string name;
    string ailment;
};

class Doctor {
public:
    Doctor(int id, string name, string specialty) : id(id), name(name), specialty(specialty) {}
    void display() const {
        cout << "ID: " << id << ", Name: " << name << ", Specialty: " << specialty << endl;
    }
    int getId() const { return id; }
    string getName() const { return name; }
    string getSpecialty() const { return specialty; }
    void setSpecialty(string newSpecialty) { specialty = newSpecialty; }

private:
    int id;
    string name;
    string specialty;
};

class Appointment {
public:
    Appointment(int id, const Patient &patient, const Doctor &doctor, string date, double cost)
        : id(id), patient(patient), doctor(doctor), date(date), cost(cost) {}

    void display() const {
        cout << "Appointment ID: " << id << endl;
        cout << "Patient: ";
        patient.display();
        cout << "Doctor: ";
        doctor.display();
        cout << "Date: " << date << endl;
        cout << "Cost: $" << fixed << setprecision(2) << cost << endl;
    }

    int getId() const { return id; }  // Added getter for appointment ID
    double getCost() const { return cost; }
    void setCost(double newCost) { cost = newCost; }

private:
    int id;
    Patient patient;
    Doctor doctor;
    string date;
    double cost;
};

class Billing {
public:
    void addBill(int appointmentId, double amount) {
        auto it = find_if(bills.begin(), bills.end(), [appointmentId](const pair<int, double>& bill) {
            return bill.first == appointmentId;
        });

        if (it != bills.end()) {
            it->second = amount; // Update existing bill amount
        } else {
            bills.push_back(make_pair(appointmentId, amount)); // Add new bill
        }
    }

    void displayBills() const {
        cout << "Bills List:" << endl;
        for (const auto &bill : bills) {
            cout << "Appointment ID: " << bill.first << ", Amount: $" << fixed << setprecision(2) << bill.second << endl;
        }
    }

private:
    vector<pair<int, double>> bills;
};

class HospitalManagementSystem {
public:
    void addPatient(int id, string name, string ailment) {
        patients.push_back(Patient(id, name, ailment));
    }

    void updatePatient(int id, string newAilment) {
        for (auto &patient : patients) {
            if (patient.getId() == id) {
                patient.setAilment(newAilment);
                return;
            }
        }
        cout << "Error: Patient not found." << endl;
    }

    void deletePatient(int id) {
        auto it = remove_if(patients.begin(), patients.end(), [id](const Patient& p) { return p.getId() == id; });
        if (it != patients.end()) patients.erase(it, patients.end());
        else cout << "Error: Patient not found." << endl;
    }

    void addDoctor(int id, string name, string specialty) {
        doctors.push_back(Doctor(id, name, specialty));
    }

    void updateDoctor(int id, string newSpecialty) {
        for (auto &doctor : doctors) {
            if (doctor.getId() == id) {
                doctor.setSpecialty(newSpecialty);
                return;
            }
        }
        cout << "Error: Doctor not found." << endl;
    }

    void deleteDoctor(int id) {
        auto it = remove_if(doctors.begin(), doctors.end(), [id](const Doctor& d) { return d.getId() == id; });
        if (it != doctors.end()) doctors.erase(it, doctors.end());
        else cout << "Error: Doctor not found." << endl;
    }

    void addAppointment(int id, int patientId, int doctorId, string date, double cost) {
        Patient *patient = findPatient(patientId);
        Doctor *doctor = findDoctor(doctorId);
        if (patient && doctor) {
            appointments.push_back(Appointment(id, *patient, *doctor, date, cost));
            billing.addBill(id, cost);
        } else {
            cout << "Error: Patient or Doctor not found." << endl;
        }
    }

    void updateAppointment(int id, double newCost) {
        for (auto &appointment : appointments) {
            if (appointment.getId() == id) { // Corrected condition to check appointment ID
                appointment.setCost(newCost);
                billing.addBill(id, newCost); // Update the bill with the new cost
                return;
            }
        }
        cout << "Error: Appointment not found." << endl;
    }

    void cancelAppointment(int id) {
        auto it = remove_if(appointments.begin(), appointments.end(), [id](const Appointment& a) { return a.getId() == id; }); // Corrected condition to check appointment ID
        if (it != appointments.end()) appointments.erase(it, appointments.end());
        else cout << "Error: Appointment not found." << endl;
    }

    void displayPatients() const {
        cout << "Patients List:" << endl;
        for (const auto &patient : patients) {
            patient.display();
        }
    }

    void displayDoctors() const {
        cout << "Doctors List:" << endl;
        for (const auto &doctor : doctors) {
            doctor.display();
        }
    }

    void displayAppointments() const {
        cout << "Appointments List:" << endl;
        for (const auto &appointment : appointments) {
            appointment.display();
        }
    }

    void displayBills() const {
        billing.displayBills();
    }

private:
    vector<Patient> patients;
    vector<Doctor> doctors;
    vector<Appointment> appointments;
    Billing billing;

    Patient* findPatient(int id) {
        for (auto &patient : patients) {
            if (patient.getId() == id) return &patient;
        }
        return nullptr;
    }

    Doctor* findDoctor(int id) {
        for (auto &doctor : doctors) {
            if (doctor.getId() == id) return &doctor;
        }
        return nullptr;
    }
};

int main() {
    HospitalManagementSystem hms;

    // Adding sample data
    hms.addPatient(1, "John Doe", "Flu");
    hms.addPatient(2, "Jane Smith", "Headache");

    hms.addDoctor(1, "Dr. Brown", "General Physician");
    hms.addDoctor(2, "Dr. Adams", "Neurologist");

    hms.addAppointment(1, 1, 1, "2024-08-07", 150.00);
    hms.addAppointment(2, 2, 2, "2024-08-08", 200.00);

    // Display data
    hms.displayPatients();
    hms.displayDoctors();
    hms.displayAppointments();
    hms.displayBills();

    // Updating and deleting operations
    hms.updatePatient(1, "Cold");
    hms.updateDoctor(1, "Internal Medicine");
    hms.updateAppointment(1, 180.00);
    hms.cancelAppointment(2);
    hms.deletePatient(2);
    hms.deleteDoctor(2);

    // Display data after updates and deletions
    hms.displayPatients();
    hms.displayDoctors();
    hms.displayAppointments();
    hms.displayBills();

    return 0;
}