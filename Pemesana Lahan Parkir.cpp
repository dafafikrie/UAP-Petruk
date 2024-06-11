#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <unordered_map>
#include <stack>
#include <queue>
#include <algorithm>
#include <cstring>

using namespace std;

template<typename T>
void displayElement(T element) {
    cout << element << endl;
}

class User {
public:
    string name;
    string carNumber;

    void registerUser() {
        cout << "Masukkan nama Anda: ";
        cin >> name;
        cout << "Masukkan nomor kendaraan Anda: ";
        cin >> carNumber;
    }

    bool operator<(const User& other) const {
        return name < other.name;
    }
};

class UserManagement {
private:
    unordered_map<string, string> users;
    vector<User> registeredUsers;

public:
    void registerUser() {
        string username, password;
        cout << "===== Registrasi =====\n";
        cout << "Masukkan nama pengguna: ";
        cin >> username;
        cout << "Masukkan kata sandi: ";
        cin >> password;

        users[username] = password;

        User newUser;
        newUser.name = username;
        registeredUsers.push_back(newUser);

        cout << "Registrasi berhasil!\n";
    }

    bool loginUser() {
        string username, password;
        cout << "===== Sistem Login =====\n";
        cout << "Masukkan nama pengguna: ";
        cin >> username;
        cout << "Masukkan kata sandi: ";
        cin >> password;

        if (users.find(username) != users.end() && users[username] == password) {
            cout << "Login berhasil!\n";
            return true;
        } else {
            cout << "Nama pengguna atau kata sandi salah.\n";
            return false;
        }
    }

    void displayRegisteredUsers() {
        sort(registeredUsers.begin(), registeredUsers.end());

        cout << "\033[1;34mDaftar Pengguna Terdaftar:\033[0m\n";
        cout << "\033[1;36m------------------------------------\033[0m\n";
        cout << "\033[1;36m| " << setw(15) << "Nama Pengguna" << " |\033[0m\n";
        cout << "\033[1;36m------------------------------------\033[0m\n";
        for (const auto& user : registeredUsers) {
            cout << "\033[1;32m| " << setw(15) << user.name << " |\033[0m\n";
        }
        cout << "\033[1;36m------------------------------------\033[0m\n";
    }
};

class ParkingSpot {
public:
    int spotNumber;
    bool isAvailable;
    string location;

    ParkingSpot(int number, const string& loc) : spotNumber(number), isAvailable(true), location(loc) {}
};

class ParkingLot {
private:
    vector<ParkingSpot> spots;
