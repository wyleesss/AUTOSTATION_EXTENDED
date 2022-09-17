#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

const unsigned MAX_SEATS = 50, MAX_WEIGHT = 10000, MAX_STATION_VEHICLES = 100;
class Bus {
    unsigned seats;
    string model;
public:
    Bus(int seats, string model) : seats(seats), model(model) {}
    Bus() : Bus(0, "") {}
    void get(int& get_seats, string& get_model) {
        get_model = model;
        get_seats = seats;
    }
    string getmodel() { return model; }
    int getseats() { return seats; }
    void set(int set_seats, string& set_model) {
        model = set_model;
        seats = set_seats;
    }
    void print_info() {
        cout << "(i) <Bus> Model -> " << model << "; Seats -> " << seats << ";\n";
    }
};

class Car {
    unsigned seats;
    string model;
public:
    Car(int seats, string model) : seats(seats), model(model) {}
    Car() : Car(0, "") {}
    void get(int& get_seats, string& get_model) {
        get_model = model;
        get_seats = seats;
    }
    string getmodel() { return model; }
    int getseats() { return seats; }
    void set(int set_seats, string& set_model) {
        model = set_model;
        seats = set_seats;
    }
    void print_info() {
        cout << "(i) <Car> Model -> " << model << "; Seats -> " << seats << ";\n";
    }
};
class Truck {
    unsigned seats, weight;
    string model;
public:
    Truck(int seats, int weight, string model) : seats(seats), weight(weight), model(model) {}
    Truck() : Truck(0, 0, "") {}
    void get(int& get_seats, int& get_weight, string& get_model) {
        get_model = model;
        get_weight = weight;
        get_seats = seats;
    }
    string getmodel() { return model; }
    int getseats() { return seats; }
    int getweight() { return weight; }
    void set(int set_seats, int set_weight, string& set_model) {
        model = set_model;
        weight = set_weight;
        seats = set_seats;
    }
    void print_info() {
        cout << "(i) <Truck> Model -> " << model << "; Seats -> " << seats << "; Weight -> " << weight << "kg;\n";
    }
};

class AutoStation {
    vector<Bus>B;
    vector<Car>C;
    vector<Truck>T;
    unsigned truckN, carN, busN;
public:
    int get_busN() { return busN; }
    int get_carN() { return carN; }
    int get_truckN() { return truckN; }
    AutoStation() {
        truckN = carN = busN = 0;
        copydata();
    }
    void print_info() {
        cout << "\n|======(iGENERAL)======|\n" <<
            "|STATION CAPACITY |[" << MAX_STATION_VEHICLES <<
            "]\n|FREE PLACES      |[" << MAX_STATION_VEHICLES - (get_carN() + get_busN() + get_truckN()) <<
            "]\n|::BUSES          |[" << get_busN() <<
            "]\n|::CARS           |[" << get_carN() <<
            "]\n|::TRUCKS         |[" << get_truckN() <<
            "]\n|======================|\n";
    }
    void print_detail_info() {
        cout << "\n|==========================(iDETAIL)===========================|\n|BUSES:\n";
        for (int i = 1; i <= get_busN(); i++) {
            cout << "|#" << i;
            getBus(i).print_info();
        }
        cout << "|CARS:\n";
        for (int i = 1; i <= get_carN(); i++) {
            cout << "|#" << i;
            getCar(i).print_info();
        }
        cout << "|TRUCKS:\n";
        for (int i = 1; i <= get_truckN(); i++) {
            cout << "|#" << i;
            getTruck(i).print_info();
        }
        cout << "|==============================================================|\n";
    }
    Bus getBus(unsigned number) {
        if (number - 1 < busN) return B[number - 1];
        cout << "(!) bus number error\n";
        return Bus(0, "");
    }
    void addBus(int seats, string model) {
        if (carN + busN + truckN < MAX_STATION_VEHICLES && seats <= MAX_SEATS) {
            busN++;
            B.push_back(Bus(seats, model));
            cout << "(+) bus has been added\n";
            rewrite();
            return;
        }
        cout << "(!) impossible to add new bus" << (seats > MAX_SEATS ? ":<too many seats>\n" : ":<station is full>\n");
    }
    void delBus(unsigned number) {
        if (busN > number - 1) {
            B.erase(B.begin() + (number - 1));
            busN--;
            cout << "(-) bus #" << number << " has been deleted\n";
            rewrite();
            return;
        }
        cout << "(!) impossible to delete the bus\n";
    }

    Car getCar(unsigned number) {
        if (number - 1 < carN) return C[number - 1];
        cout << "(!) car number error\n";
        return Car(0, "");
    }
    void addCar(int seats, string model) {
        if (carN + busN + truckN < MAX_STATION_VEHICLES && seats <= MAX_SEATS) {
            carN++;
            C.push_back(Car(seats, model));
            cout << "(+) car has been added\n";
            rewrite();
            return;
        }
        cout << "(!) impossible to add new car" << (seats > MAX_SEATS ? ":<too many seats>\n" : ":<station is full>\n");
    }
    void delCar(unsigned number) {
        if (carN > number - 1) {
            C.erase(C.begin() + (number - 1));
            carN--;
            cout << "(-) car #" << number << " has been deleted\n";
            rewrite();
            return;
        }
        cout << "(!) impossible to delete the car\n";
    }

    Truck getTruck(unsigned number) {
        if (number - 1 < truckN) return T[number - 1];
        cout << "(!) truck number error\n";
        return Truck(0, 0, "");
    }
    void addTruck(int seats, int weight, string model) {
        if (carN + busN + truckN < MAX_STATION_VEHICLES && weight <= MAX_WEIGHT) {
            truckN++;
            T.push_back(Truck(seats, weight, model));
            cout << "(+) truck has been added\n";
            rewrite();
            return;
        }
        cout << "(!) impossible to add new truck" << (weight > MAX_WEIGHT ? ":<too much weigth>\n" : ":<station is full>\n");
    }
    void delTruck(unsigned number) {
        if (truckN > number - 1) {
            T.erase(T.begin() + (number - 1));
            truckN--;
            cout << "(-) truck #" << number << " has been deleted\n";
            rewrite();
            return;
        }
        cout << "(!) impossible to delete the truck\n";
    }
private:
    void rewrite() {
        ofstream data("DATA.txt");
        data << "B" << busN << "C" << carN << "T" << truckN << endl;
        for (int i = 1; i <= B.size(); i++) 
            data << "!B!*" << getBus(i).getmodel() << "*+" << getBus(i).getseats() << "+/" << i << "/\n";
        for (int i = 1; i <= C.size(); i++)
            data << "!C!*" << getCar(i).getmodel() << "*+" << getCar(i).getseats() << "+/" << i << "/\n";
        for (int i = 1; i <= T.size(); i++)
            data << "!T!*" << getTruck(i).getmodel() << "*+" << getTruck(i).getseats() << "+^" << getTruck(i).getweight() << "^/" << i << "/\n";
        data.close();
    }
    void copydata() {
        string info;
        ifstream data("DATA.txt");
        while (getline(data, info)) {
            string p1, p2, p3;
            switch (info[1]) {
            case 'B':
                busN++;
                p1 = transcript(info, '+'), p2 = transcript(info, '*');
                B.push_back(Bus(stoi(p1), p2));
                info = "";
                continue;
            case 'C':
                carN++;
                p1 = transcript(info, '+'), p2 = transcript(info, '*');
                C.push_back(Car(stoi(p1), p2));
                info = "";
                continue;
            case 'T':
                truckN++;
                p1 = transcript(info, '+'), p2 = transcript(info, '*'), p3 = transcript(info, '^');
                T.push_back(Truck(stoi(p1), stoi(p3), p2));
                info = "";
                continue;
            default:
                info = "";
                continue;
            }
        }
        data.close();
    }
    string transcript(string str, char character) {
        do {
            str.erase(str.find(str[0]), 1);
        } while (str[0] != character);
        str.erase(str.find(str[0]), 1);
        str.erase(str.find(character));
        return str;
    }
    
};


int main() {

    srand(time(NULL));
    vector<string>bus_trucks_models{ "MERCEDES", "VOLVO", "SCANIA", "MAN", "SETRA", "TEMSA", "IVECO", "SUFFLE" };
    vector<string>car_models{ "AUDI", "MITSUBISHI", "MERCEDES", "VOLVO", "FORD", "BMW", "TOYOTA", "VOLKSWAGEN" };

    AutoStation station;
    /*cout << "timeline:\n";
    station.delCar(1);
    station.delBus(3);
    station.addTruck(rand() % 2 + 1, rand() % 5000 + 5000, bus_trucks_models[rand() % 8]);*/

    station.print_info();
    station.print_detail_info();
}