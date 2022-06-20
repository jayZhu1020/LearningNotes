#include <iostream>
using namespace std;
/*
BUILDER PATTERN:
    a builder pattern encapsulates or hides the process of building 
    a complex object and separates the representation of the object and its construction. 
    The separation allows us to construct different representations 
    using the same construction process.

    Classes:
    1. Builder
    2. Concrete Builder (inherited from Builder)
    3. Director
    4. Product
*/

/* Objects we wanna build*/
class ParentObject {
    public:
        void spec() {
            cout << "I have attrA:" << attrA << " and attrB:" << attrB << " and attrC:" << attrC << endl;
        }
        void setattrA(int A) {
            attrA = A;
        }
        void setattrB(int B) {
            attrB = B;
        }
        void setattrC(int C) {
            attrC = C;
        }
        virtual ~ParentObject() = default;
    private:
        int attrA;
        int attrB;
        int attrC;
};

/* Abstract Builder Class*/
class Builder {
    public:
        void buildPartA() {};
        void buildPartB() {};
        void buildPartC() {};
        // any derived builder must overwrite this method
        virtual ParentObject* buildObject() = 0;
};

/* Object 1 Builder Class*/
class Object1Builder : public Builder {
    public:
        void buildPartA() {
            obj->setattrA(1);
        }
        void buildPartB() {
            obj->setattrB(2);
        }
        void buildPartC() {
            obj->setattrC(3);
        }
        virtual ParentObject* buildObject() {
            obj = new ParentObject();
            buildPartA();
            buildPartB();
            buildPartC();
            return obj;
        }
    private:
        ParentObject* obj;
};

/* Object 2 Builder Class*/
class Object2Builder : public Builder {
    public:
        void buildPartA() {
            obj->setattrA(4);
        }
        void buildPartB() {
            obj->setattrB(5);
        }
        void buildPartC() {
            obj->setattrC(6);
        }
        virtual ParentObject* buildObject() {
            obj = new ParentObject();
            buildPartA();
            buildPartB();
            buildPartC();
            return obj;
        }
    private:
        ParentObject* obj;
};


/* Director */
class Director {
    public:
        Director(Builder* b) {
            builder = b;
        }
        void setBuilder(Builder* b) {
            builder = b;
        }
        ParentObject* build() {
            return builder->buildObject();
        }
    private:
        Builder* builder;
};

int main()  {
    Object1Builder b1;
    Object2Builder b2;
    Director d(&b1);
    ParentObject* obj1 = d.build();
    obj1->spec();
    d.setBuilder(&b2);
    ParentObject* obj2 = d.build();
    obj2->spec();
    delete obj1;
    delete obj2;
    
}