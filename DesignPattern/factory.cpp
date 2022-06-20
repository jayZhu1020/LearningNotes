/*
 * The factory method is defined as providing an interface for object creation 
 * but delegating the actual instantiation of objects to subclasses.
 */

#include<iostream>
#include<vector>

using namespace std;

class Parent {
    public:
        virtual void info() = 0;
        virtual ~Parent() = default;
};

class Child1 :  public Parent {
    public:
        virtual void info() {
            cout << "I'm child 1" <<endl;
        }
};

class Child2 :  public Parent {
    public:
        virtual void info() {
            cout << "I'm child 2" <<endl;
        }
};

class Child3 :  public Parent {
    public:
        virtual void info() {
            cout << "I'm child 3" <<endl;
        }
};

// Delegate the object creation to the factory rather than the user so objects can be created at run time
class Factory {
    public:
        Parent* createInstance(int a) {
            switch (a) {
                case 1:
                    return new Child1();
                case 2:
                    return new Child2();
                case 3:
                    return new Child3();
                case 4:
                    return nullptr;
            }
        }
};

int main() {
    vector<int> inputs;
    inputs.push_back(1); inputs.push_back(3); inputs.push_back(2);
    vector<Parent*> outputs;
    Factory factory;
    for (int i : inputs) {
        outputs.push_back(factory.createInstance(i));
    }
    for (Parent* obj : outputs) {
        obj->info();
    }
    for (Parent* obj : outputs) {
        delete obj;
    }

}