#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Flight {
private:
    static int flightCounter;
    int flightID;
    string flightName;
    string startPoint;
    string destination;
    int seatsAvailable;
    int seatsTotal;

public:
    Flight(string fname, string start, string dest, int seats) 
    : flightName(fname), startPoint(start), destination(dest), seatsAvailable(seats), seatsTotal(seats) {
        flightID = ++flightCounter;
    }
    
    int getFlightID() { return flightID; }
    string getFlightName() { return flightName; }
    string getStartPoint() { return startPoint; }
    string getDestination() { return destination; }
    int getSeatsAvailable() { return seatsAvailable; }
    int getSeatsTotal() { return seatsTotal; }

    void bookSeat() {
        if (seatsAvailable > 0) {
            seatsAvailable--;
        } else {
            cout << "No seats available!" << endl;
        }
    }

    void cancelSeat() {
        if (seatsAvailable < seatsTotal) {
            seatsAvailable++;
        } else {
            cout << "All seats are already available!" << endl;
        }
    }

    friend void showFlightDetails(Flight &f);
    
    virtual ~Flight() {
        // Destructor
    }
};

int Flight::flightCounter = 0;

void showFlightDetails(Flight &f) {
    cout << "Flight ID: " << f.flightID << endl;
    cout << "Flight Name: " << f.flightName << endl;
    cout << "Start Point: " << f.startPoint << endl;
    cout << "Destination: " << f.destination << endl;
    cout << "Seats Available: " << f.seatsAvailable << "/" << f.seatsTotal << endl;
}

class Reservation {
public:
    int flightID;
    string customerName;
    int seatNumber;
};

class AirlineSystem {
private:
    vector<Flight*> flights;
    vector<Reservation> reservations;

public:
    void addFlight() {
        string name, start, destination;
        int seats;
        cout << "Enter flight name: ";
        cin >> name;
        cout << "Enter start point: ";
        cin >> start;
        cout << "Enter destination: ";
        cin >> destination;
        cout << "Enter seats available: ";
        cin >> seats;

        flights.push_back(new Flight(name, start, destination, seats));
        cout << "Flight added successfully!" << endl;
    }

    void showAllFlights() {
        cout << "\nAll Flights Schedule:" << endl;
        for (size_t i = 0; i < flights.size(); ++i) {
            cout << "Flight ID: " << flights[i]->getFlightID() 
                 << ", Name: " << flights[i]->getFlightName() 
                 << ", Start Point: " << flights[i]->getStartPoint() 
                 << ", Destination: " << flights[i]->getDestination() 
                 << ", Seats Available: " << flights[i]->getSeatsAvailable() << endl;
        }
    }

    void bookSeat() {
        int flightID;
        cout << "Enter flight ID to book seats: ";
        cin >> flightID;
        for (size_t i = 0; i < flights.size(); ++i) {
            if (flights[i]->getFlightID() == flightID) {
                int numSeats;
                cout << "Enter the number of seats to book: ";
                cin >> numSeats;
                if (numSeats > flights[i]->getSeatsAvailable()) {
                    cout << "Not enough seats available!" << endl;
                    return;
                }
                for (int j = 0; j < numSeats; j++) {
                    Reservation res;
                    res.flightID = flightID;
                    cout << "Enter name for seat " << (j + 1) << ": ";
                    cin >> res.customerName;
                    res.seatNumber = flights[i]->getSeatsTotal() - flights[i]->getSeatsAvailable() + 1; // Corrected Seat Number
                    reservations.push_back(res);
                    flights[i]->bookSeat();
                }
                cout << "Seats booked successfully!" << endl;
                return;
            }
        }
        cout << "Invalid flight ID!" << endl;
    }

    void showReservedSeats() {
        int flightID;
        cout << "Enter flight ID to show reserved seats: ";
        cin >> flightID;
        cout << "\nReserved Seats for Flight ID: " << flightID << endl;
        for (size_t i = 0; i < reservations.size(); ++i) {
            if (reservations[i].flightID == flightID) {
                cout << "Customer Name: " << reservations[i].customerName 
                     << ", Seat Number: " << reservations[i].seatNumber << endl;
            }
        }
    }

    void cancelSeat() {
        int flightID;
        cout << "Enter flight ID to cancel a seat: ";
        cin >> flightID;
        for (size_t i = 0; i < flights.size(); ++i) {
            if (flights[i]->getFlightID() == flightID) {
                int seatNumber;
                cout << "Enter seat number to cancel: ";
                cin >> seatNumber;
                for (size_t j = 0; j < reservations.size(); ++j) {
                    if (reservations[j].flightID == flightID && reservations[j].seatNumber == seatNumber) {
                        flights[i]->cancelSeat();
                        reservations.erase(reservations.begin() + j);
                        cout << "Seat canceled successfully!" << endl;
                        return;
                    }
                }
                cout << "Seat not found!" << endl;
                return;
            }
        }
        cout << "Invalid flight ID!" << endl;
    }

    void adminMenu() {
        while (true) {
            cout << "\nAdmin Menu" << endl;
            cout << "1. Add Flight" << endl;
            cout << "2. Exit" << endl;
            cout << "Select an option: ";

            int choice;
            cin >> choice;

            if (choice == 1) {
                addFlight();
            } else if (choice == 2) {
                break;
            } else {
                cout << "Invalid option! Please try again." << endl;
            }
        }
    }

    void customerMenu() {
        while (true) {
            cout << "\nCustomer Menu" << endl;
            cout << "1. Flight Schedule" << endl;
            cout << "2. Book a Seat" << endl;
            cout << "3. Reserved Seats" << endl;
            cout << "4. Cancel a Seat" << endl;
            cout << "5. Exit" << endl;
            cout << "Select an option: ";

            int choice;
            cin >> choice;

            if (choice == 1) {
                showAllFlights();
            } else if (choice == 2) {
                bookSeat();
            } else if (choice == 3) {
                showReservedSeats();
            } else if (choice == 4) {
                cancelSeat();
            } else if (choice == 5) {
                break;
            } else {
                cout << "Invalid option! Please try again." << endl;
            }
        }
    }

    void mainMenu() {
        while (true) {
            cout << "\nAirline Management System" << endl;
            cout << "1. Admin" << endl;
            cout << "2. Customer" << endl;
            cout << "3. Exit" << endl;
            cout << "Select an option: ";

            int choice;
            cin >> choice;

            if (choice == 1) {
                adminMenu();
            } else if (choice == 2) {
                customerMenu();
            } else if (choice == 3) {
                break;
            } else {
                cout << "Invalid option! Please try again." << endl;
            }
        }

        // Cleanup dynamically allocated memory
        for (size_t i = 0; i < flights.size(); ++i) {
            delete flights[i];
        }
    }
};

int main() {
    AirlineSystem system;
    system.mainMenu();
    return 0;
}
