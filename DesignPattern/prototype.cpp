/* the Prototype pattern is defined as specify the kind of objects to create 
 * using a prototypical instance as a model and making copies of the prototype to create new objects.
 */
#include<iostream>

class ClonableParent {
    public:
        virtual ClonableParent* makeCopy() const = 0;
        virtual void printData() const = 0;
};

class ClonableChild : public ClonableParent {
    public:
        ClonableChild(int a, float b):field1(a), field2(b) {}
        virtual ClonableParent* makeCopy() const {
            ClonableChild* clone = new ClonableChild(field1, field2);
            return clone;
        }
        virtual void printData() const {
            std::cout << field1 << " " << field2 << std::endl;
        }
    private:
        int field1;
        float field2;
};

class CloneFactory {
    public:
        ClonableParent* getClone(ClonableParent* other) const {
            return other->makeCopy();
        }
};



int main() {
    CloneFactory factory;
    ClonableParent* toBeCloned = new ClonableChild(1,2);
    ClonableParent* cloned = factory.getClone(toBeCloned);
    toBeCloned->printData();
    cloned->printData();
    delete toBeCloned;
    delete cloned;
}


