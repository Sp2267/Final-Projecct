#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Define a Car class to represent each car
class Car {
public:
    string make;
    string model;
    int year;
    int mileage; // in kilometers
    bool available;

    Car(string _make, string _model, int _year, int _mileage) : make(_make), model(_model), year(_year), mileage(_mileage), available(true) {}
};

// Define a RentalSystem class to manage the rental operations
class RentalSystem {
public:
    vector<Car> cars; // Make cars vector public

    // Function to add a new car to the system
    void addCar(string make, string model, int year, int mileage) {
        cars.push_back(Car(make, model, year, mileage));
    }

    // Function to display all available cars
    void displayAvailableCars() {
        cout << "Available Cars:\n";
        for (int i = 0; i < cars.size(); ++i) {
            if (cars[i].available) {
                cout << i+1 << ". " << cars[i].make << " " << cars[i].model << " (" << cars[i].year << ")\n";
            }
        }
    }

    // Function to rent a car
    void rentCar(int index, int duration, int age) {
        if (index >= 0 && index < cars.size() && cars[index].available) {
            if (age < 18) {
                cout << "Sorry, but we can't rent you a car as you are too young.\n";
                return;
            }
            cars[index].available = false;
            int amount = calculateAmount(cars[index], duration);
            cout << "You have rented: " << cars[index].make << " " << cars[index].model << "\n";
            cout << "Rental duration: " << duration << " days\n";
            cout << "Total Amount: $" << amount << "\n";
            // Ask for customer information
            string name;
            string phone;
            cout << "Please provide your name: ";
            cin >> name;
            cout << "Please provide your phone number: ";
            cin >> phone;
            // Generate bill
            generateBill(name, age, phone, amount);
        } else {
            cout << "Invalid selection or car not available\n";
        }
    }

    // Function to return a rented car
    void returnCar(int index, int age, int duration) {
        if (index >= 0 && index < cars.size() && !cars[index].available) {
            cars[index].available = true;
            cout << "You have returned: " << cars[index].make << " " << cars[index].model << "\n";
            // Generate bill
            int amount = calculateAmount(cars[index], duration);
            generateBill(cars[index].make, age, "", amount); // Assume no phone number for returning
        } else {
            cout << "Invalid selection or car not rented\n";
        }
    }

private:
    // Function to calculate the rental amount
    int calculateAmount(const Car& car, int duration) {
        // Assume a flat rate of $50 per day
        return duration * 50;
    }

    // Function to generate the bill
    void generateBill(const string& name, int age, const string& phone, int amount) {
        cout << "\n----- Bill -----\n";
        cout << "Name: " << name << "\n";
        cout << "Age: " << age << "\n";
        cout << "Phone: " << phone << "\n";
        cout << "Total Amount: $" << amount << "\n";
        cout << "----------------\n";
    }
};

// Function to display the home screen menu
void displayMenu() {
    cout << "\n----- Home Screen -----\n";
    cout << "1. Add a new car\n";
    cout << "2. Rent a car\n";
    cout << "3. Return a car\n";
    cout << "4. Exit\n";
    cout << "------------------------\n";
}

