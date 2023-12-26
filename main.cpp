#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Bus {
private:
    string busNumber;
    string source;
    string destination;
    int totalSeats;
    int availableSeats;

public:
    Bus(string busNumber, string source, string destination, int totalSeats)
        : busNumber(busNumber), source(source), destination(destination), totalSeats(totalSeats), availableSeats(totalSeats) {}

    string getBusNumber() const {
        return busNumber;
    }

    string getSource() const {
        return source;
    }

    string getDestination() const {
        return destination;
    }

    int getTotalSeats() const {
        return totalSeats;
    }

    int getAvailableSeats() const {
        return availableSeats;
    }

    bool reserveSeats(int seats) {
        if (seats <= availableSeats) {
            availableSeats -= seats;
            return true;
        }
        return false;
    }

    void display() const {
        cout << "Bus Number: " << busNumber << endl;
        cout << "Source: " << source << endl;
        cout << "Destination: " << destination << endl;
        cout << "Total Seats: " << totalSeats << endl;
        cout << "Available Seats: " << availableSeats << endl;
    }
};

class Ticket {
private:
    static int ticketCounter;
    int ticketNumber;
    Bus bus;
    string passengerName;
    int numberOfSeats;

public:
    Ticket(const Bus& bus, string passengerName, int numberOfSeats)
        : ticketNumber(++ticketCounter), bus(bus), passengerName(passengerName), numberOfSeats(numberOfSeats) {}

    int getTicketNumber() const {
        return ticketNumber;
    }

    const Bus& getBus() const {
        return bus;
    }

    string getPassengerName() const {
        return passengerName;
    }

    int getNumberOfSeats() const {
        return numberOfSeats;
    }

    void display() const {
        cout << "Ticket Number: " << ticketNumber << endl;
        cout << "Passenger Name: " << passengerName << endl;
        cout << "Bus Details:" << endl;
        bus.display();
        cout << "Number of Seats: " << numberOfSeats << endl;
    }
};

int Ticket::ticketCounter = 0;

class BusTicketReservationSystem {
private:
    vector<Bus> buses;
    vector<Ticket> tickets;

public:
    void addBus(const Bus& bus) {
        buses.push_back(bus);
    }

    void reserveTicket(Bus& bus, string passengerName, int numberOfSeats) {
        bool success = bus.reserveSeats(numberOfSeats);
        if (success) {
            Ticket ticket(bus, passengerName, numberOfSeats);
            tickets.push_back(ticket);
            cout << "Ticket reserved successfully!" << endl;
            cout << "Ticket Details:" << endl;
            ticket.display();
        } else {
            cout << "Failed to reserve ticket. Not enough available seats." << endl;
        }
    }

    void displayAvailableBuses() const {
        cout << "Available Buses:" << endl;
        for (const auto& bus : buses) {
            if (bus.getAvailableSeats() > 0) {
                bus.display();
                cout << endl;
            }
        }
    }

    void displayAllTickets() const {
        cout << "All Tickets:" << endl;
        for (const auto& ticket : tickets) {
            ticket.display();
            cout << endl;
        }
    }

    const vector<Bus>& getBuses() const {
        return buses;
    }
};

int main() {
    BusTicketReservationSystem reservationSystem;

    // Adding buses to the reservation system
    Bus bus1("B001", "City A", "City B", 50);
    Bus bus2("B002", "City B", "City C", 40);
    reservationSystem.addBus(bus1);
    reservationSystem.addBus(bus2);

    int choice;
    do {
        cout << "----- BUS TICKET RESERVATION SYSTEM -----" << endl;
        cout << "1. Display available buses" << endl;
        cout << "2. Reserve a ticket" << endl;
        cout << "3. Display all tickets" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                reservationSystem.displayAvailableBuses();
                break;
            case 2: {
                string busNumber;
                cout << "Enter the bus number: ";
                cin >> busNumber;

                auto it = find_if(reservationSystem.getBuses().begin(), reservationSystem.getBuses().end(),
                                  [busNumber](const Bus& bus) { return bus.getBusNumber() == busNumber; });

                if (it != reservationSystem.getBuses().end()) {
                    string passengerName;
                    cout << "Enter passenger name: ";
                    cin >> passengerName;

                    int numberOfSeats;
                    cout << "Enter the number of seats to reserve: ";
                    cin >> numberOfSeats;

                    reservationSystem.reserveTicket(const_cast<Bus&>(*it), passengerName, numberOfSeats);
                } else {
                    cout << "Invalid bus number." << endl;
                }
                break;
            }
            case 3:
                reservationSystem.displayAllTickets();
                break;
            case 0:
                cout << "Thank you for using the Bus Ticket Reservation System!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
        cout << endl;
    } while (choice != 0);

    return 0;
}
