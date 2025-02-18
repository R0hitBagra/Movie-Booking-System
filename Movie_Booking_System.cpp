#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

// Enums for Seat Status and Booking Status
enum SeatStatus { AVAILABLE, BOOKED };

// Seat class
class Seat {
public:
    string seatId;
    SeatStatus status;
    string category; 
    Seat() : seatId(""), status(AVAILABLE), category("") {}  
    Seat(string id, string cat) : seatId(id), status(AVAILABLE), category(cat) {}
};

// Screen class
class Screen {
public:
    string screenId;
    string movieTitle;
    string genre;
    string language;
    string duration;
    string time;
    map<string, Seat> seats;
    int rows, cols;
    double silverPrice, goldPrice; 

    Screen(string id, string title, string gen, string lang, string dur, string t, double silver, double gold, int r, int c) 
        : screenId(id), movieTitle(title), genre(gen), language(lang), duration(dur), time(t), silverPrice(silver), goldPrice(gold), rows(r), cols(c) {
        int silverRows = (rows % 2 == 0) ? rows / 2 : (rows / 2) + 1; 
        for (char row = 'A'; row < 'A' + rows; row++) {
            for (int col = 1; col <= cols; col++) {
                string seatId = string(1, row) + to_string(col);
                string category = (row < 'A' + silverRows) ? "Silver" : "Gold";
                seats[seatId] = Seat(seatId, category);
            }
        }
    }
    
    void displaySeats() {
        cout << "\n  ";
        for (int col = 1; col <= cols; col++) {
            cout << col << " ";
        }
        cout << "\n";
        for (char row = 'A'; row < 'A' + rows; row++) {
            cout << row << " ";
            for (int col = 1; col <= cols; col++) {
                string seatId = string(1, row) + to_string(col);
                cout << (seats[seatId].status == AVAILABLE ? "_ " : "X ");
            }
            cout << " | ";
            if (seats[string(1, row) + "1"].category == "Silver") {
                cout << "Silver (Rs. " << silverPrice << ")";
            } else {
                cout << "Gold (Rs. " << goldPrice << ")";
            }
            cout << endl;
        }
    }
};

// Theater class
class Theater {
public:
    string name;
    string location;
    vector<Screen> screens;
    
    Theater(string n, string loc) : name(n), location(loc) {}
    void addScreen(Screen screen) {
        screens.push_back(screen);
    }
};

// Booking class
class Booking {
public:
    string bookingId;
    string userId;
    string seatId;
    string screenId;
    string theaterName;
    string movieTitle;
    double price;
    bool isActive;

    Booking() : bookingId(""), userId(""), seatId(""), screenId(""), theaterName(""), movieTitle(""), price(0), isActive(false) {} 
    Booking(string id, string uid, string seat, string screen, string theater, string movie, double p)
        : bookingId(id), userId(uid), seatId(seat), screenId(screen), theaterName(theater), movieTitle(movie), price(p), isActive(true) {}
};

// User class
class User {
public:
    string userId;
    string name;
    vector<string> bookings; 

    User() : userId(""), name("") {} 
    User(string id, string n) : userId(id), name(n) {}
};

// Movie Ticket Booking System
class MovieTicketBookingSystem {
private:
    vector<Theater> theaters;
    map<string, User> users; 
    map<string, Booking> bookings; 
    int bookingCounter = 1; 

    // Dummy payment system
    bool processPayment(double amount) {
        cout << "Proceed to payment of Rs. " << amount << "? (Y/N): ";
        char confirm;
        cin >> confirm;
        if (confirm == 'Y' || confirm == 'y') {
            cout << "Payment successful!\n";
            return true;
        } else {
            cout << "Payment failed. Booking cancelled.\n";
            return false;
        }
    }

public:
    void addTheater(Theater theater) {
        theaters.push_back(theater);
    }

    vector<Theater>& getTheaters() {  
        return theaters;
    }

    void displayMovies() {
        if (theaters.empty()) {
            cout << "No movies available!\n";
            return;
        }
        cout << "Available Movies:\n";
        for (auto &theater : theaters) {
            for (auto &screen : theater.screens) {
                cout << screen.movieTitle << " (" << screen.genre << ") - " << screen.language << ", " << screen.duration << " at " << screen.time << " in " << theater.name << "\n";
            }
        }
    }

    void searchMovies(string query) {
        bool found = false;
        for (auto &theater : theaters) {
            for (auto &screen : theater.screens) {
                if (screen.movieTitle.find(query) != string::npos || 
                    screen.genre.find(query) != string::npos || 
                    screen.language.find(query) != string::npos || 
                    theater.location.find(query) != string::npos || 
                    screen.time.find(query) != string::npos) {
                    cout << "Found: " << screen.movieTitle << " (" << screen.genre << ") - " << screen.language << ", " << screen.duration << " at " << screen.time << " in " << theater.name << "\n";
                    found = true;
                }
            }
        }
        if (!found) cout << "No results found!\n";
    }

    void registerUser(string userId, string name) {
        if (users.find(userId) != users.end()) {
            cout << "User ID already exists!\n";
            return;
        }
        users[userId] = User(userId, name);
        cout << "User registered successfully!\n";
    }

    void bookTicket(string userId) {
        if (users.find(userId) == users.end()) {
            cout << "User not found. Please register first.\n";
            return;
        }

        cout << "Enter Movie Title to Book: ";
        string title;
        cin >> ws;
        getline(cin, title);

        vector<pair<Theater*, Screen*>> availableScreens;
        for (auto &theater : theaters) {
            for (auto &screen : theater.screens) {
                if (screen.movieTitle == title) {
                    availableScreens.push_back({&theater, &screen});
                }
            }
        }
        if (availableScreens.empty()) {
            cout << "Movie not found!\n";
            return;
        }

        cout << "Available Screens:\n";
        for (size_t i = 0; i < availableScreens.size(); i++) {
            cout << i + 1 << ". " << availableScreens[i].second->movieTitle << " (" << availableScreens[i].second->genre << ") - " 
                 << availableScreens[i].second->language << ", " << availableScreens[i].second->duration << " at " 
                 << availableScreens[i].second->time << " in " << availableScreens[i].first->name << "\n";
        }
        cout << "Choose Screen: ";
        int choice;
        cin >> choice;
        if (choice < 1 || choice > availableScreens.size()) {
            cout << "Invalid choice!\n";
            return;
        }
        Screen* selectedScreen = availableScreens[choice - 1].second;
        Theater* selectedTheater = availableScreens[choice - 1].first;
        selectedScreen->displaySeats();
        cout << "Enter Row (A-" << char('A' + selectedScreen->rows - 1) << "): ";
        char row;
        cin >> row;
        cout << "Enter Column (1-" << selectedScreen->cols << "): ";
        int col;
        cin >> col;
        string seatId = string(1, row) + to_string(col);
        if (selectedScreen->seats.count(seatId) > 0 && selectedScreen->seats[seatId].status == AVAILABLE) {
            double price = (selectedScreen->seats[seatId].category == "Silver") ? selectedScreen->silverPrice : selectedScreen->goldPrice;
            cout << "Seat " << seatId << " selected. Price: Rs. " << price << "\n";
            if (processPayment(price)) {
                selectedScreen->seats[seatId].status = BOOKED;
                string bookingId = "B" + to_string(bookingCounter++);
                bookings[bookingId] = Booking(bookingId, userId, seatId, selectedScreen->screenId, selectedTheater->name, selectedScreen->movieTitle, price);
                users[userId].bookings.push_back(bookingId);
                cout << "Seat " << seatId << " booked successfully! Booking ID: " << bookingId << "\n";
            } else {
                cout << "Seat " << seatId << " is still available.\n";
            }
        } else {
            cout << "Invalid or already booked seat.\n";
        }
    }

    void cancelBooking(string userId) {
        if (users.find(userId) == users.end()) {
            cout << "User not found.\n";
            return;
        }

        if (users[userId].bookings.empty()) {
            cout << "No bookings found for this user.\n";
            return;
        }

        cout << "Your Bookings:\n";
        for (size_t i = 0; i < users[userId].bookings.size(); i++) {
            string bookingId = users[userId].bookings[i];
            if (bookings[bookingId].isActive) {
                cout << i + 1 << ". Booking ID: " << bookingId << " - " << bookings[bookingId].movieTitle << " at " << bookings[bookingId].theaterName << ", Seat " << bookings[bookingId].seatId << "\n";
            }
        }
        cout << "Choose Booking to Cancel: ";
        int choice;
        cin >> choice;
        if (choice < 1 || choice > users[userId].bookings.size()) {
            cout << "Invalid choice!\n";
            return;
        }
        string bookingId = users[userId].bookings[choice - 1];
        if (!bookings[bookingId].isActive) {
            cout << "Booking already canceled.\n";
            return;
        }

        for (auto &theater : theaters) {
            for (auto &screen : theater.screens) {
                if (screen.screenId == bookings[bookingId].screenId) {
                    screen.seats[bookings[bookingId].seatId].status = AVAILABLE;
                    break;
                }
            }
        }

        bookings[bookingId].isActive = false;
        cout << "Booking " << bookingId << " canceled successfully! Seat " << bookings[bookingId].seatId << " is now available.\n";
    }
};

// Main function
int main() {
    MovieTicketBookingSystem system;
    int choice;
    while (true) {
        cout << "\n1. Admin\n2. User\n3. Exit\nChoose: ";
        cin >> choice;
        if (choice == 1) {
            cout << "Admin Panel\n1. Add Theater\n2. Add Screen\nChoose: ";
            int adminChoice;
            cin >> adminChoice;
            if (adminChoice == 1) {
                string name, location;
                cout << "Enter Theater Name: ";
                cin >> ws;
                getline(cin, name);
                cout << "Enter Location: ";
                getline(cin, location);
                system.addTheater(Theater(name, location));
            } else if (adminChoice == 2) {
                if (system.getTheaters().empty()) {
                    cout << "No theaters available. Please add a theater first.\n";
                    continue;
                }
                cout << "Available Theaters:\n";
                for (size_t i = 0; i < system.getTheaters().size(); i++) {
                    cout << i + 1 << ". " << system.getTheaters()[i].name << "\n";
                }
                cout << "Choose Theater: ";
                int theaterIndex;
                cin >> theaterIndex;
                if (theaterIndex < 1 || theaterIndex > system.getTheaters().size()) {
                    cout << "Invalid choice!\n";
                    continue;
                }
                string title, genre, language, duration, time;
                double silverPrice, goldPrice;
                int rows, cols;
                cout << "Enter Movie Title: ";
                cin >> ws;
                getline(cin, title);
                cout << "Enter Movie Genre: ";
                getline(cin, genre);
                cout << "Enter Movie Language: ";
                getline(cin, language);
                cout << "Enter Movie Duration: ";
                getline(cin, duration);
                cout << "Enter Show Time: ";
                getline(cin, time);
                cout << "Enter Silver Seat Price: ";
                cin >> silverPrice;
                cout << "Enter Gold Seat Price: ";
                cin >> goldPrice;
                cout << "Enter Number of Rows: ";
                cin >> rows;
                cout << "Enter Number of Columns: ";
                cin >> cols;
                system.getTheaters()[theaterIndex - 1].addScreen(Screen("S1", title, genre, language, duration, time, silverPrice, goldPrice, rows, cols));
            }
        } else if (choice == 2) {
            cout << "User Panel\n1. Register\n2. View Movies\n3. Search Movies\n4. Book Ticket\n5. Cancel Booking\nChoose: ";
            int userChoice;
            cin >> userChoice;
            if (userChoice == 1) {
                string userId, name;
                cout << "Enter User ID: ";
                cin >> userId;
                cout << "Enter Name: ";
                cin >> ws;
                getline(cin, name);
                system.registerUser(userId, name);
            } else if (userChoice == 2) {
                system.displayMovies();
            } else if (userChoice == 3) {
                cout << "Enter search query: ";
                string query;
                cin >> ws;
                getline(cin, query);
                system.searchMovies(query);
            } else if (userChoice == 4) {
                string userId;
                cout << "Enter User ID: ";
                cin >> userId;
                system.bookTicket(userId);
            } else if (userChoice == 5) {
                string userId;
                cout << "Enter User ID: ";
                cin >> userId;
                system.cancelBooking(userId);
            }
        } else break;
    }
    return 0;
}