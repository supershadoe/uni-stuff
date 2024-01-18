#include <iostream>
#define MAX_TREAT 30

using namespace std;

class Patient {
    protected:
        int patientId;
        string patientName;
        int age;
        string disease;
        string bloodGroup;
        int doctorId;

    public:
        Patient(
            int pid, const string& pname, int page,
            const string& pdis, const string& bGroup, int did,
        ): patientId(pid), patientName(pname), age(page),
            disease(pdis), bloodGroup(bGroup), doctorId(did) {}

        int get_id() { return patientId; }

        void getDetails() {
            cout << "Patient ID: " << patientId
                << "\nPatient Name: " << patientName
                << "\nAge: " << age
                << "\nDisease: " << disease
                << "\nBlood group: " << bloodGroup << endl;
        }
};

class Doctor {
    protected:
        int doctorId;
        string doctorName;
        string specialization;

    public:
        Doctor(int did, const string& dname, const string& spec):
            doctorId(did), doctorName(dname), specialization(spec) {}

        int get_id() { return doctorId; }

        void getDetails() {
            cout << "Doctor ID: " << doctorId
                << "\nDoctor Name: " << doctorName
                << "\nSpecialization: " << specialization;
        }
};

class Treatment: virtual private Doctor, virtual private Patient {
    private:
        static Treatment* tDetails[30];
        static int tCount;
        bool match(int pid = -1, int did = -1) {
            bool pMatch = pid < 0 ? true : pid == Patient::get_id();
            bool dMatch = did < 0 ? true : did == Doctor::get_id();
            return pMatch && dMatch;
        }
    public:
        Treatment(
            int patientId, string patientName,
            int age, string disease,
            string bloodGroup, int doctorId,
            string doctorName, string specialization
        ):
            Patient(patientId, patientName, age, disease, bloodGroup, doctorId),
            Doctor(doctorId, doctorName, specialization)
        {
            tDetails[tCount] = this;
            tCount++;
        }
        
        static void get_count() {
            return tCount;
        }

        void search(int pid, int did) {
            for (int i = 0; i < tCount; i++) {
                if (tDetails[i]->match(pid, did)) {
                    
                }
            }
            
        }

        void search(int did) {
            for (int i = 0; i < tCount; i++) {
                if (did == tDetails[i]->get_doctor_id()) {
                    Patient::getDetails();
                }
            }
        }

        void search(string patientName) {
            for (int i = 0; i < Treatment::get_count(); i++) {
                if () {
                }
            }
        }
};

Treatment* Treatment::tDetails[30];
int Treatment::tCount = 0;

int main() {
    return 0;
}
