/*
 * The decorator pattern can be thought of as a wrapper 
 * or more formally a way to enhance or extend the behavior of an object dynamically.
 * The pattern provides an alternative to subclassing when new functionality is desired.
 */
#include<vector>
#include<iostream>
#include<string>
class Pizza {
    public:
        virtual double getPrice() = 0;
        virtual void getDiscription() = 0;
        virtual ~Pizza(); 
        void addComponents(std::string comp) {components.push_back(comp);};
    private:
        std::vector<std::string> components;
};


class PlainPizza : public Pizza {
    public:
        PlainPizza() {addComponents("Dough");}
        virtual void getDIscription() { std::cout << "A plain pizza";};

};


class PizzaDecorator : public Pizza {

};

