#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Car {
public:
    string make;
    string model;
    int year;
    double price_per_day;
    bool is_available;

    Car(string mk, string mdl, int yr, double price)
        : make(mk), model(mdl), year(yr), price_per_day(price), is_available(true) {}
};

class Customer {
public:
    string name;
    string license_number;

    Customer(string nm, string license)
        : name(nm), license_number(license) {}
};

class Rental {
public:
    Car* car;
    Customer* customer;
    int rental_days;

    Rental(Car* c, Customer* cust, int days)
        : car(c), customer(cust), rental_days(days) {
        car->is_available = false;
    }

    double calculateTotalCost() {
        return rental_days * car->price_per_day;
    }
};

void displayCars(const vector<Car>& cars) {
    cout << "Available cars:\n";
    for (size_t i = 0; i < cars.size(); ++i) {
        if (cars[i].is_available) {
            cout << i + 1 << ". " << cars[i].make << " " << cars[i].model << " (" << cars[i].year << ") - $" << cars[i].price_per_day << " per day\n";
        }
    }
}

void displayWelcomeMessage() {
    cout << "*******************************\n";
    cout << "*      CAR RENTAL  SYSTEM     *\n";
    cout << "*******************************\n\n";
}

bool continueOrExit() {
    cout << "\nDo you want to continue or exit ? (1. Continue, 2. Exit): ";
    int choice;
    cin >> choice;
    return choice == 1;
}

int main() {
    vector<Car> cars = {
        Car("Toyota", "Corolla", 2022, 4800),
        Car("Toyota", "Camry", 2020, 3800),
        Car("Toyota", "Innova Crysta", 2020, 3499),
        Car("Honda", "Venue", 2019, 2299),
        Car("Ford", "Mustang", 2021, 5000)
    };

    displayWelcomeMessage();

    int choice;
    do {
        cout << "\t1. Display cars\n";
        cout << "\t2. Rent a car\n";
        cout << "\t3. Exit\n";
        cout << "\n";
        cout << "*******************************\n\n";
        
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            displayCars(cars);
            if (!continueOrExit()) break;
        } else if (choice == 2) {
            cin.ignore(); // To clear the newline character left in the buffer
            string customer_name, license_number;
            cout << "Enter customer name: ";
            getline(cin, customer_name);
            cout << "Enter license number: ";
            getline(cin, license_number);

            Customer customer(customer_name, license_number);
            displayCars(cars);

            int car_choice, rental_days;
            cout << "Enter the number of the car you want to rent: ";
            cin >> car_choice;
            cout << "Enter the number of days you want to rent the car: ";
            cin >> rental_days;

            if (car_choice > 0 && car_choice <= cars.size() && cars[car_choice - 1].is_available) {
                Rental rental(&cars[car_choice - 1], &customer, rental_days);
                cout << "Customer: " << rental.customer->name << endl;
                cout << "Car: " << rental.car->make << " " << rental.car->model << endl;
                cout << "Total Cost: ₹" << rental.calculateTotalCost() << endl;
            } else {
                cout << "Invalid car choice or car not available.\n";
            }
            if (!continueOrExit()) break;
        } else if (choice != 3) {
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 3);

    return 0;
}
