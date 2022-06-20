/*
 * The Singleton pattern is defined as ensuring that only a single instance of a class exists 
 * and a global point of access to it exists.
 */
#include <iostream>
using namespace std;

class Singleton {
    public:
        // global point of access, static
        static Singleton& getInstance() {
            static Singleton instance;
            return instance;
        }
        void address() {
            cout << this << endl;
        }
        // don't allow copy constructor and assignment operator
        Singleton(const Singleton&) = delete;
        void operator=(const Singleton&) = delete;
    private:
        // don't allow construction
        Singleton() = default;
};



int main() {
    Singleton& singleton1 = Singleton::getInstance();
    Singleton& singleton2 = Singleton::getInstance();
    singleton1.address();
    singleton2.address();
}