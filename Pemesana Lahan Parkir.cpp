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

public:
    ParkingLot(int numberOfSpots, const vector<string>& locations) {
        for (int i = 0; i < numberOfSpots; ++i) {
            spots.push_back(ParkingSpot(i + 1, locations[i % locations.size()]));
        }
    }

    void displayAvailableSpots() {
        cout << "\033[1;34mTempat Parkir yang Tersedia:\033[0m\n";
        cout << "\033[1;36m------------------------------------\033[0m\n";
        cout << "\033[1;36m| " << setw(10) << "Nomor" << " | " << setw(15) << "Lokasi" << " |" << "\033[0m\n";
        cout << "\033[1;36m------------------------------------\033[0m\n";
        for (const auto& spot : spots) {
            if (spot.isAvailable) {
                cout << "\033[1;32m| " << setw(10) << spot.spotNumber << " | " << setw(15) << spot.location << " |\033[0m\n";
            }
        }
        cout << "\033[1;36m------------------------------------\033[0m\n";
    }

    bool bookSpot(int spotNumber, string& location) {
        if (spotNumber < 1 || spotNumber > spots.size()) {
            cout << "\033[1;31mNomor tempat tidak valid!\033[0m\n";
            return false;
        }

        if (spots[spotNumber - 1].isAvailable) {
            spots[spotNumber - 1].isAvailable = false;
            location = spots[spotNumber - 1].location;
            return true;
        } else {
            cout << "\033[1;31mTempat " << spotNumber << " sudah dipesan.\033[0m\n";
            return false;
        }
    }

    void releaseSpot(int spotNumber) {
        if (spotNumber < 1 || spotNumber > spots.size()) {
            cout << "\033[1;31mNomor tempat tidak valid!\033[0m\n";
            return;
        }

        if (!spots[spotNumber - 1].isAvailable) {
            spots[spotNumber - 1].isAvailable = true;
            cout << "\033[1;32mTempat " << spotNumber << " telah dilepas.\033[0m\n";
        } else {
            cout << "\033[1;33mTempat " << spotNumber << " sudah tersedia.\033[0m\n";
        }
    }
};

string generateReceipt(const User& user, int spotNumber, const string& location) {
    string receipt = "\033[1;37mStruk Parkir\n";
    receipt += "Nama: " + user.name + "\n";
    receipt += "Nomor Kendaraan: " + user.carNumber + "\n";
    receipt += "Nomor Tempat Parkir: " + to_string(spotNumber) + "\n";
    receipt += "Lokasi: " + location + "\n";

    receipt += "Barcode: ||| || | || ||\n";
    receipt += "\033[0m";
    return receipt;
}

void displayMainMenu() {
    cout << "===== Menu =====\n";
    cout << "1. Registrasi\n";
    cout << "2. Login\n";
    cout << "3. Tampilkan Semua Pengguna\n";
    cout << "4. Keluar\n";
    cout << "Masukkan pilihan Anda: ";
}

void displayParkingMenu() {
    cout << "===================================================\n";
    cout << "|     Selamat Datang di Pemesanan Lahan Parkir    |\n";
    cout << "|               \033[1;36mMenu Tempat Parkir:\033[0m               |\n";
    cout << "===================================================\n";
    cout << "| 1. Tampilkan tempat yang tersedia               |\n";
    cout << "| 2. Pesan tempat                                 |\n";
    cout << "| 3. Lepaskan tempat                              |\n";
    cout << "| 4. Keluar                                       |\n";
    cout << "===================================================\n";
    cout << "Masukkan pilihan Anda: ";
}

void divideAndConquerExample(vector<int>& arr, int left, int right) {
    if (left >= right) {
        return;
    }

    int mid = left + (right - left) / 2;
    divideAndConquerExample(arr, left, mid);
    divideAndConquerExample(arr, mid + 1, right);

    vector<int> temp;
    int i = left, j = mid + 1;
    while (i <= mid && j <= right) {
        if (arr[i] < arr[j]) {
            temp.push_back(arr[i]);
++i;
        } else {
            temp.push_back(arr[j]);
            ++j;
        }
    }
    while (i <= mid) {
        temp.push_back(arr[i]);
        ++i;
    }
    while (j <= right) {
        temp.push_back(arr[j]);
        ++j;
    }
    for (int k = left; k <= right; ++k) {
        arr[k] = temp[k - left];
    }
}

int main() {
    UserManagement userManagement;
    int choice;

    do {
        displayMainMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                userManagement.registerUser();
                break;
            case 2: {
                if (userManagement.loginUser()) {
                    int numberOfSpots;
                    cout << "Masukkan jumlah tempat parkir: ";
                    cin >> numberOfSpots;

                    vector<string> locations = {"A1", "A2", "B1", "B2", "C1", "C2"};
                    ParkingLot parkingLot(numberOfSpots, locations);

                    User user;
                    user.registerUser();

                    stack<int> bookingStack;
                    queue<int> releaseQueue;

                    int parkingChoice;
                    do {
                        displayParkingMenu();
                        cin >> parkingChoice;

                        switch (parkingChoice) {
                            case 1:
                                parkingLot.displayAvailableSpots();
                                break;
                            case 2: {
                                int spotToBook;
                                cout << "Masukkan nomor tempat yang ingin dipesan: ";
                                cin >> spotToBook;
                                string location;
                                if (parkingLot.bookSpot(spotToBook, location)) {
                                    cout << "\033[1;32mKonfirmasi: Tempat " << spotToBook << " telah berhasil dipesan!\033[0m\n";
                                    bookingStack.push(spotToBook);
                                    string receipt = generateReceipt(user, spotToBook, location);
                                    cout << receipt;
                                }
                                break;
                            }
                            case 3: {
                                int spotToRelease;
                                if (!releaseQueue.empty()) {
                                    spotToRelease = releaseQueue.front();
                                    releaseQueue.pop();
                                    parkingLot.releaseSpot(spotToRelease);
                                } else {
                                    cout << "\033[1;33mAntrian tempat untuk dilepaskan kosong.\033[0m\n";
                                }
                                break;
                            }
                            case 4:
                                cout << "\033[1;32mTerima kasih telah menggunakan layanan parkir kami!\033[0m\n";
                                cout << "======================" << endl;
                                cout << "     TERIMAKASIH    " << endl;
                                cout << "======================" << endl;
                                break;
                            default:
                                cout << "\033[1;31mPilihan tidak valid. Silakan coba lagi.\033[0m\n";
                        }
                    } while (parkingChoice != 4);
                }
                break;
            }
            case 3:
                userManagement.displayRegisteredUsers();
                break;
            case 4:
                cout << "\033[1;32mTerima kasih telah menggunakan program ini!\033[0m\n";
                break;
            default:
                cout << "\033[1;31mPilihan tidak valid. Silakan coba lagi.\033[0m\n";
        }
    } while (choice != 4);

    return 0;
}
