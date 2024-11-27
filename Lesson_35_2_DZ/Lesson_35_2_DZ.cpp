#include <iostream>
#include <list>
#include <string>
#include <algorithm>

struct Taxi {
    int taxiNumber;
    std::string carBrand;
    std::string driverName;
    bool isOnCall; // true = на виклику, false = вільне

   
    void display() const {
        std::cout << "Номер таксі: " << taxiNumber
            << ", Марка автомобіля: " << carBrand
            << ", Водій: " << driverName
            << ", Статус: " << (isOnCall ? "На виклику" : "Вільне") << "\n";
    }
};


void displayTaxis(const std::list<Taxi>& taxis) {
    for (const auto& taxi : taxis) {
        taxi.display();
    }
}


auto findTaxi(std::list<Taxi>& taxis, int taxiNumber) {
    return std::find_if(taxis.begin(), taxis.end(), [taxiNumber](const Taxi& taxi) {
        return taxi.taxiNumber == taxiNumber;
        });
}

int main() {
    setlocale(0, "");
    std::list<Taxi> taxis;
    taxis.push_back({ 1, "Toyota", "Іванов І.І.", false });
    taxis.push_back({ 2, "BMW", "Петров П.П.", false });
    taxis.push_back({ 3, "Honda", "Сидоров С.С.", true });

    int choice;
    do {
        std::cout << "\nМеню:\n"
            << "1. Вивести всі таксі\n"
            << "2. Додати таксі на початок списку\n"
            << "3. Додати таксі перед певним таксі\n"
            << "4. Видалити таксі\n"
            << "5. Встановити 'На виклику'\n"
            << "6. Встановити 'Вільне'\n"
            << "7. Показати таксі за статусом\n"
            << "0. Вихід\n"
            << "Ваш вибір: ";
        std::cin >> choice;

        switch (choice) {
        case 1: { 
            displayTaxis(taxis);
            break;
        }
        case 2: { 
            Taxi newTaxi;
            std::cout << "Введіть номер, марку, водія, статус (1 - на виклику, 0 - вільне): ";
            std::cin >> newTaxi.taxiNumber >> newTaxi.carBrand >> newTaxi.driverName >> newTaxi.isOnCall;
            taxis.push_front(newTaxi);
            break;
        }
        case 3: { 
            int targetNumber;
            std::cout << "Введіть номер таксі, перед яким потрібно додати нове таксі: ";
            std::cin >> targetNumber;

            auto it = findTaxi(taxis, targetNumber);
            if (it != taxis.end()) {
                Taxi newTaxi;
                std::cout << "Введіть номер, марку, водія, статус (1 - на виклику, 0 - вільне): ";
                std::cin >> newTaxi.taxiNumber >> newTaxi.carBrand >> newTaxi.driverName >> newTaxi.isOnCall;
                taxis.insert(it, newTaxi);
            }
            else {
                std::cout << "Таксі з таким номером не знайдено.\n";
            }
            break;
        }
        case 4: {
            int taxiNumber;
            std::cout << "Введіть номер таксі для видалення: ";
            std::cin >> taxiNumber;

            auto it = findTaxi(taxis, taxiNumber);
            if (it != taxis.end()) {
                taxis.erase(it);
                std::cout << "Таксі видалено.\n";
            }
            else {
                std::cout << "Таксі з таким номером не знайдено.\n";
            }
            break;
        }
        case 5: { 
            int taxiNumber;
            std::cout << "Введіть номер таксі, щоб встановити статус 'На виклику': ";
            std::cin >> taxiNumber;

            auto it = findTaxi(taxis, taxiNumber);
            if (it != taxis.end()) {
                it->isOnCall = true;
                std::cout << "Статус оновлено.\n";
            }
            else {
                std::cout << "Таксі з таким номером не знайдено.\n";
            }
            break;
        }
        case 6: { 
            int taxiNumber;
            std::cout << "Введіть номер таксі, щоб встановити статус 'Вільне': ";
            std::cin >> taxiNumber;

            auto it = findTaxi(taxis, taxiNumber);
            if (it != taxis.end()) {
                it->isOnCall = false;
                std::cout << "Статус оновлено.\n";
            }
            else {
                std::cout << "Таксі з таким номером не знайдено.\n";
            }
            break;
        }
        case 7: { 
            bool status;
            std::cout << "Введіть статус (1 - на виклику, 0 - вільне): ";
            std::cin >> status;

            for (const auto& taxi : taxis) {
                if (taxi.isOnCall == status) {
                    taxi.display();
                }
            }
            break;
        }
        case 0: {
            std::cout << "Вихід з програми.\n";
            break;
        }
        default:
            std::cout << "Невірний вибір. Спробуйте ще раз.\n";
        }
    } while (choice != 0);

    return 0;
}
