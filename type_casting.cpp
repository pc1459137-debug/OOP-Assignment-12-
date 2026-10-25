#include <iostream>
#include <typeinfo>
#include <cstdint>
using namespace std;

// ---------- Classes for dynamic_cast demo ----------
class Shape {
public:
    virtual void draw() const { cout << "Drawing a generic shape\n"; }
    virtual ~Shape() {}                      // virtual => polymorphic
};

class Circle : public Shape {
public:
    void draw() const override { cout << "Drawing a circle\n"; }
    void radiusInfo() const { cout << "Circle: radius-specific method called\n"; }
};

class Rectangle : public Shape {
public:
    void draw() const override { cout << "Drawing a rectangle\n"; }
};

// Legacy function that takes a non-const pointer but never modifies the data
void legacyPrint(int *p) { cout << "legacyPrint: " << *p << '\n'; }

enum Color { RED = 1, GREEN, BLUE };

int main() {
    cout << "===== 1. IMPLICIT CONVERSION =====\n";
    int i = 10;
    double d = i;                    // int -> double (widening, safe)
    double pi = 3.99;
    int t = pi;                      // double -> int (truncation)
    char ch = 'A';
    int code = ch;                   // char -> int
    cout << "int 10 -> double      : " << d << '\n';
    cout << "double 3.99 -> int    : " << t << " (fraction lost)\n";
    cout << "char 'A' -> int       : " << code << '\n';

    cout << "\n===== 2. C-STYLE CAST =====\n";
    int a = 7, b = 2;
    cout << "Without cast 7 / 2    = " << a / b << '\n';
    cout << "(float)a / b          = " << (float)a / b << '\n';

    cout << "\n===== 3. static_cast =====\n";
    cout << "static_cast<double>(a)/b = " << static_cast<double>(a) / b << '\n';
    Color c = GREEN;
    cout << "enum GREEN as int     = " << static_cast<int>(c) << '\n';
    Color c2 = static_cast<Color>(3);
    cout << "int 3 as enum         = " << c2 << " (BLUE)\n";
    int num = 25;
    void *vp = &num;                 // int* -> void* (implicit)
    int *ip = static_cast<int *>(vp); // void* -> int*
    cout << "void* back to int*    = " << *ip << '\n';
    cout << "char from int 66      = " << static_cast<char>(66) << '\n';

    cout << "\n===== 4. dynamic_cast =====\n";
    Shape *s1 = new Circle();
    Shape *s2 = new Rectangle();

    Circle *cp1 = dynamic_cast<Circle *>(s1);   // valid
    if (cp1) { cout << "s1 -> Circle*    : success\n"; cp1->radiusInfo(); }
    else       cout << "s1 -> Circle*    : failed\n";

    Circle *cp2 = dynamic_cast<Circle *>(s2);   // invalid -> nullptr
    if (cp2) cout << "s2 -> Circle*    : success\n";
    else     cout << "s2 -> Circle*    : failed (nullptr returned)\n";

    try {
        Circle &cr = dynamic_cast<Circle &>(*s2);  // invalid reference cast
        cr.radiusInfo();
    } catch (const bad_cast &e) {
        cout << "Exception caught  : bad_cast thrown for reference cast\n";
    }
    delete s1;
    delete s2;

    cout << "\n===== 5. const_cast =====\n";
    const int value = 99;
    legacyPrint(const_cast<int *>(&value));     // safe: function only reads
    int x = 5;
    const int *cx = &x;
    int *mx = const_cast<int *>(cx);            // safe: x is not truly const
    *mx = 50;
    cout << "x modified via const_cast = " << x << '\n';

    cout << "\n===== 6. reinterpret_cast =====\n";
    int n = 0x41424344;
    char *bytes = reinterpret_cast<char *>(&n);
    cout << "Bytes of 0x41424344 as chars: ";
    for (int k = 0; k < 4; k++) cout << bytes[k];
    cout << " (little-endian order)\n";
    uintptr_t addr = reinterpret_cast<uintptr_t>(&n);
    int *back = reinterpret_cast<int *>(addr);
    cout << "Address round trip works: " << (back == &n ? "yes" : "no") << '\n';
    return 0;
}
