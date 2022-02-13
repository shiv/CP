#include <iostream>
#include <cmath>
#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Car {
private:
    string brand;
    string vehicle_number;
    string model;
    int speed;
protected:
    int fuel_capacity;
public:
    void accelerate(int inc) {
        speed += inc;
    }
    void dislplay_speed() {
        cout << "The current speed is "<< speed << "km/h.\n";
    }
    Car() : speed(0) {}
};

class BMW : Car {
public:
    // void double_speed() {
    //     speed *= 2;
    // }
    void accelerate(int inc) {
        Car::accelerate(inc * 2);
        dislplay_speed();
    }
};

int main() {

    BMW mycar;
    mycar.accelerate(20);

    return 0;
}