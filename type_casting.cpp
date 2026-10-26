//Practical 12: Type Casting, covering all four casting operators: static_cast, dynamic_cast, const_cast, and reinterpret_cast.


#include <iostream>
using namespace std;

// Base class
class Base {
public:
    virtual ~Base() {}
};

// Derived class
class Derived : public Base {
public:
    void show() {
        cout << "dynamic_cast successful: Derived object found." << endl;
    }
};

int main() {

    // 1. static_cast
    double price = 99.75;
    int wholePrice = static_cast<int>(price);

    cout << "static_cast: " << wholePrice << endl;

    // 2. dynamic_cast
    Base* basePtr = new Derived();

    Derived* derivedPtr = dynamic_cast<Derived*>(basePtr);

    if (derivedPtr != nullptr) {
        derivedPtr->show();
    } else {
        cout << "dynamic_cast failed." << endl;
    }

    delete basePtr;

    // 3. const_cast
    int value = 10;  // Originally non-const

    const int* constPtr = &value;

    int* modifiablePtr = const_cast<int*>(constPtr);

    *modifiablePtr = 25;

    cout << "const_cast: " << value << endl;

    // 4. reinterpret_cast
    int number = 50;

    int* intPtr = &number;

    char* charPtr = reinterpret_cast<char*>(intPtr);

    int* restoredPtr = reinterpret_cast<int*>(charPtr);

    cout << "reinterpret_cast (after converting back): "
         << *restoredPtr << endl;

    return 0;
}
