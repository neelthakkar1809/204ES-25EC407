#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Room {
public:
    string roomCode;
    string names[3];
    string rollNo[3];

    void input() {
        cout << "Enter room code (e.g. 4S13): ";
        cin >> roomCode;

        for (int i = 0; i < 3; i++) {
            cout << "Enter student " << i + 1 << " name: ";
            getline(cin >> ws, names[i]);

            // unique college roll number
            while (true) {
                cout << "Enter student " << i + 1 << " college roll no: ";
                cin >> rollNo[i];

                bool duplicate = false;
                for (int j = 0; j < i; j++) {
                    if (rollNo[j] == rollNo[i])
                        duplicate = true;
                }

                if (duplicate)
                    cout << "This roll no already lives in the hostel! Enter again.\n";
                else
                    break;
            }
        }
    }

    void show(ostream &out, string type, double bill, double fee) {
        double share = bill / 3;

        out.setf(ios::fixed);
        out.precision(2);

        out << "--- HostelSense Report ---\n";
        out << "Room: " << roomCode << "\n";
        out << "Type: " << type << "\n\n";

        out << "=== HOSTEL FEE ===\n";
        for (int i = 0; i < 3; i++) {
            out << "Student " << i + 1 << ": " << names[i]
                << " (Roll no: " << rollNo[i] << ")\n";
            out << "   TOTAL HOSTEL FEE PAYABLE : Rs. " << fee << "\n";
        }
        out << "Total hostel fee from this room: Rs. " << fee * 3 << "\n\n";

        out << "=== EXTRA ELECTRICITY BILL (paid separately) ===\n";
        out << "Room electricity bill: Rs. " << bill << "\n";
        for (int i = 0; i < 3; i++) {
            out << names[i] << " (Roll no: " << rollNo[i] << ") pays: Rs. " << share << "\n";
        }
    }
};

class ACRoom : public Room {
public:
    double units, rate;

    ACRoom() {
        units = 0;
        rate = 0;
    }

    void inputAC() {
        cout << "Enter AC units consumed: ";
        cin >> units;
        cout << "Enter rate per unit (Rs.): ";
        cin >> rate;
    }

    double bill() {
        return units * rate;
    }
};

int main() {
    int choice;
    cout << "1. Attached bathroom, Non-AC     (Rs. 95,000)\n";
    cout << "2. Non-attached bathroom, Non-AC (Rs. 73,000)\n";
    cout << "3. AC with attached bathroom     (Rs. 1,25,000)\n";
    cout << "Select room type: ";
    cin >> choice;

    if (cin.fail() || choice < 1 || choice > 3) {
        cout << "Invalid choice!\n";
        return 0;
    }

    Room r;
    ACRoom c;
    string type;
    double bill = 0;
    double fee = 0;

    if (choice == 3) {
        c.input();
        c.inputAC();

        if (cin.fail() || c.units < 0 || c.rate < 0) {
            cout << "Invalid electricity details!\n";
            return 0;
        }
        type = "AC with Attached Bathroom";
        bill = c.bill();
        fee = 125000;
    }
    else {
        r.input();
        if (choice == 1) {
            type = "Attached Bathroom, Non-AC";
            fee = 95000;
        }
        else {
            type = "Non-Attached Bathroom, Non-AC";
            fee = 73000;
        }
    }

    ofstream f("HostelReport.txt");
    if (!f) {
        cout << "Cannot create report!\n";
        return 0;
    }

    cout << "\n";
    if (choice == 3) {
        c.show(cout, type, bill, fee);
        c.show(f, type, bill, fee);
    }
    else {
        r.show(cout, type, bill, fee);
        r.show(f, type, bill, fee);
    }

    f.close();
    cout << "Report saved successfully!\n";
    return 0;
}