#include <iostream>
#include <vector> 
#include "Bank.h"
#include "Rental.h"
#include "Reservation.h"

using namespace std;

void printMainMenu() {
    cout << "Main Menu" << endl;
    cout << "1. Ticket Reservation" << endl;
    cout << "2. Rental System" << endl;
    cout << "3. Bank System" << endl;
    cout << "4. Exit" << endl;
    cout << "Enter your choice: ";
}
void tickets()
{
    vector<Ticket*> tickets; 
    vector<Ticket*> reservedTickets; 
    // Add some tickets to the vector
                tickets.push_back(new BusTicket("Bus Trip", "April 20, 2024", 25.0, 10, "ABC Bus Co."));
                tickets.push_back(new TrainTicket("Train Journey", "April 22, 2024", 50.0, 20, "XYZ Train Route"));
                tickets.push_back(new MovieTicket("Movie Night", "April 25, 2024", 15.0, 15, "Star Cinema"));

                // Display ticket options
                cout << "Available ticket options:" << endl;
                cout << "1. Bus Ticket" << endl;
                cout << "2. Train Ticket" << endl;
                cout << "3. Movie Ticket" << endl;

                // Ask user for choice
                int choice;
                cout << "Enter the number of the ticket type you want to view (1-3): ";
                cin >> choice;

                // Validate choice
                if (choice >= 1 && choice <= 3) {
                    // Display available tickets for the selected type
                    cout << "Available tickets for ";
                    switch (choice) {
                        case 1:
                            cout << "Bus Ticket:";
                            break;
                        case 2:
                            cout << "Train Ticket:";
                            break;
                        case 3:
                            cout << "Movie Ticket:";
                            break;
                    }
                    cout << endl;
                    tickets[choice - 1]->display();
                    cout << "------------------------" << endl;

                    // Ask user for the quantity of tickets
                    int quantity;
                    cout << "Enter the number of tickets you want to reserve: ";
                    cin >> quantity;

                    // Reserve tickets if available
                    Ticket* selectedTicket = tickets[choice - 1];
                    if (selectedTicket->checkAvailability(quantity)) {
                        string name;
                        int age;
                        cout << "Enter your name: ";
                        cin.ignore(); // Clear input buffer
                        getline(cin, name);
                        cout << "Enter your age: ";
                        cin >> age;
                        selectedTicket->reserve(name, age, quantity);
                        reservedTickets.push_back(selectedTicket);
                    } else {
                        cout << "Not enough tickets available." << endl;
                    }
                } else {
                    cout << "Invalid choice. Please enter a number between 1 and 3." << endl;
                }

                // Display all reserved tickets
                cout << "Reserved Tickets:" << endl;
                for (const auto& ticket : reservedTickets) {
                    ticket->display();
                    cout << "------------------------" << endl;
                }

                // Clean up allocated memory
                for (auto& ticket : tickets) {
                    delete ticket;
                }
}

void bank()
{
    printLogo();
    Bank bank;

    int choice;
    do {
        cout << "\nBank System Menu\n";
        cout << "1. Create Account\n";
        cout << "2. Deposit\n";
        cout << "3. Withdraw\n";
        cout << "4. Transfer\n";
        cout << "5. Display Account Info\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                bank.createAccount();
                break;
            case 2:
                bank.deposit();
                break;
            case 3:
                bank.withdraw();
                break;
            case 4:
                bank.transfer();
                break;
            case 5:
                bank.displayAccountInfo();
                break;
            case 6:
                cout << "Thank you for using our bank system. Have a great day!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }

        cin.ignore(); // Clear input buffer
    } while (choice != 6);

}

void rental()
{
    RentalSystem rentalSystem;

    while (true) {
        // Display home screen menu
        displayMenu();

       int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        // Process user choice
        switch (choice) {
            case 1: {
                // Add a new car
                string make, model;
                int year, mileage;
                cout << "Enter car make: ";
                cin >> make;
                cout << "Enter car model: ";
                cin >> model;
                cout << "Enter car year: ";
                cin >> year;
                cout << "Enter car mileage: ";
                cin >> mileage;
                rentalSystem.addCar(make, model, year, mileage);
                cout << "Car added successfully!\n";
                break;
            }
            case 2: {
                // Rent a car
                rentalSystem.displayAvailableCars();
                int carIndex;
                cout << "Enter the number of the car you want to rent: ";
                cin >> carIndex;
                carIndex--; // adjust index to match vector indexing

                // Check if car index is valid
                if (carIndex < 0 || carIndex >= rentalSystem.cars.size() || !rentalSystem.cars[carIndex].available) {
                    cout << "Invalid selection or car not available\n";
                    break;
                }

                // Get rental duration from user
                int duration;
                cout << "Enter rental duration (in days): ";
                cin >> duration;

                // Get customer age
                int age;
                cout << "Enter your age: ";
                cin >> age;

                // Rent the selected car
                rentalSystem.rentCar(carIndex, duration, age);
                break;
            }
            case 3: {
                // Return a car
                int carIndex;
                cout << "Enter the number of the car you want to return: ";
                cin >> carIndex;
                carIndex--; // adjust index to match vector indexing

                // Get customer age
                int age;
                cout << "Enter your age: ";
                cin >> age;

                // Get rental duration from user
                int duration;
                cout << "Enter rental duration (in days): ";
                cin >> duration;

                // Return the selected car
                rentalSystem.returnCar(carIndex, age, duration);
                break;
            }
            case 4:
                // Exit the rental system menu
                cout << "Exiting Rental System Menu...\n";
                return;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
}

int main() {
    while (true) {
        printMainMenu();
        int option;
        cin >> option;

        switch (option) {
            case 1:
                tickets();
                break;
            case 2:
                rental();
                break;
            case 3:
                bank();
                break;
            case 4:
                cout << "Exiting the Multi-App System...\n";
                return 0; // Exit the program
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    }

    return 0;
}