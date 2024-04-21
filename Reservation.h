#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Base class for tickets
class Ticket {
protected:
    string eventName;
    string eventDate;
    double price;
    int quantity;

public:
    Ticket(const string& name, const string& date, double cost, int qty)
        : eventName(name), eventDate(date), price(cost), quantity(qty) {}

    virtual void display() const {
        cout << "Event Name: " << eventName << endl;
        cout << "Event Date: " << eventDate << endl;
        cout << "Price: $" << price << endl;
        cout << "Available Quantity: " << quantity << endl;
    }

    bool checkAvailability(int requestedQuantity) const {
        return requestedQuantity <= quantity;
    }

    virtual void reserve(const string& name, int age, int requestedQuantity) {
        if (checkAvailability(requestedQuantity)) {
            quantity -= requestedQuantity;
            displayReservationDetails(name, age, requestedQuantity);
        } else {
            cout << "Not enough tickets available." << endl;
        }
    }

    virtual void displayReservationDetails(const string& name, int age, int quantity) const {
        cout << "Reserved Ticket Details:" << endl;
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        display();
    }
};

// Subclass for bus tickets
class BusTicket : public Ticket {
private:
    string busCompany;

public:
    BusTicket(const string& name, const string& date, double cost, int qty, const string& company)
        : Ticket(name, date, cost, qty), busCompany(company) {}

    void display() const override {
        cout << "Bus Ticket:" << endl;
        Ticket::display();
        cout << "Bus Company: " << busCompany << endl;
    }

    void reserve(const string& name, int age, int requestedQuantity) override {
        cout << "Reserving Bus Ticket..." << endl;
        Ticket::reserve(name, age, requestedQuantity);
    }
};

// Subclass for train tickets
class TrainTicket : public Ticket {
private:
    string trainRoute;

public:
    TrainTicket(const string& name, const string& date, double cost, int qty, const string& route)
        : Ticket(name, date, cost, qty), trainRoute(route) {}

    void display() const override {
        cout << "Train Ticket:" << endl;
        Ticket::display();
        cout << "Train Route: " << trainRoute << endl;
    }

    void reserve(const string& name, int age, int requestedQuantity) override {
        cout << "Reserving Train Ticket..." << endl;
        Ticket::reserve(name, age, requestedQuantity);
    }
};

// Subclass for movie tickets
class MovieTicket : public Ticket {
private:
    string cinemaName;

public:
    MovieTicket(const string& name, const string& date, double cost, int qty, const string& cinema)
        : Ticket(name, date, cost, qty), cinemaName(cinema) {}

    void display() const override {
        cout << "Movie Ticket:" << endl;
        Ticket::display();
        cout << "Cinema Name: " << cinemaName << endl;
    }

    void reserve(const string& name, int age, int requestedQuantity) override {
        cout << "Reserving Movie Ticket..." << endl;
        Ticket::reserve(name, age, requestedQuantity);
    }
};

