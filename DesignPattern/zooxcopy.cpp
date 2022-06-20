/*
You're building a tool to estimate the cost of various airplane tickets based on the airline, distance and seating class. Your tool must take in this information as a series of inputs (one ticket calculation per line of input) and produce a list of output costs.

Each airline contains its own cost requirements. Ultimately, the airline is only interested in two major components: the space you take on the plane, and the distance you fly. You must generate ticket costs using this gathered data:

Airlines: United, Delta, Southwest, LuigiAir

Operating Costs:

 - Economy:  No charge
 - Premium:  $25
 - Business: $50 + $0.25/mile

Per-Airline Prices:

 - Delta charges $0.50/mile
   + OperatingCost
   
 - United charges $0.75/mile
   + OperatingCost
   + $0.10/mile for Premium seats

 - Southwest charges $1.00/mile

 - LuigiAir charges $100 or 2 * OperatingCost, whichever is higher

Keep in mind that, while there are only four airlines listed above, your solution should be able to expand to dozens of individual airlines,  whose ticket cost can be based on arbitrary functions of "Operating Costs", miles, and/or seating class.

You can assume that the input will be provided as a list of strings and that there could be millions of lines of input. Each string will provide the Airline, Distance and Seating Class. Please review the examples below:

Example Input:
-------------------------------------------
United 150.0 Premium
Delta 60.0 Business
Southwest 1000.0 Economy
LuigiAir 50.0 Business
-------------------------------------------

Example Output:
-------------------------------------------
152.50
95.00
1000.00
125.00
-------------------------------------------

Explanation of Output:
-------------------------------------------
152.50      (150.0 * (0.75 + 0.10) + 25)
95.00       (60.0 * (0.50 + 0.25) + 50)
1000.00     (1000.0 * 1.00)
125.00      (100 <= 2 * (50 + 50 * 0.25))
-------------------------------------------
*/

#include <unordered_map>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

enum airline {United, Delta, SouthWest, LuigiAir};

enum level {Economy, Premium, Business};

unordered_map<string, airline> stringToAirline{{"United", United},{"Delta", Delta},{"SouthWest", SouthWest},{"LuigiAir", LuigiAir}};

unordered_map<string, level> stringToLevel{{"Economy", Economy},{"Premium", Premium},{"Business", Business}};



struct Ticket {
    airline air;
    float mile;
    level lvl;
};

class AirlineCalculator {
    public:
        // singleton pattern
        static AirlineCalculator* getInstance(const Ticket& ticket);
        // pure virtual function that must be implemented by all subclasses
        virtual float getTotalCost(const Ticket& ticket) const = 0;
        virtual ~AirlineCalculator() = default;
        // cannot use copy constructor and assignment opeartor
        AirlineCalculator& operator= (const AirlineCalculator& ) = delete;
        AirlineCalculator(const AirlineCalculator& ) = delete;
    protected:
        virtual float getOperationCost(const Ticket& ticket) const {
            float opCost = 0;
            switch (ticket.lvl) {
                case (Economy):
                    opCost = getEconomyCost(ticket);
                    break;
                case (Premium):
                    opCost = getPremiumCost(ticket);
                    break;
                case (Business):
                    opCost = getBusinessCost(ticket);
            }
            return opCost;
        }

        virtual float getEconomyCost(const Ticket& ticket) const {
            return 0.0;
        } 

        virtual float getPremiumCost(const Ticket& ticket) const {
            return 25.0;
        } 

        virtual float getBusinessCost(const Ticket& ticket) const {
            return 50.0 + 0.25 * ticket.mile;
        } 

        AirlineCalculator() = default;
};

class UnitedCalculator : public AirlineCalculator {
    public:
        virtual float getTotalCost(const Ticket& ticket) const { 
            float cost = getOperationCost(ticket);
            return 0.75 * ticket.mile + cost;
        }

        virtual ~UnitedCalculator() = default;
        // make sure there is only one calculator
        static UnitedCalculator* instance() {
            static UnitedCalculator calc;
            return &calc;
        }
    protected:
        virtual float getPremiumCost(const Ticket& ticket) const {
            return 25.0 + 0.1 * ticket.mile;
        }
    private:
        UnitedCalculator() = default;
};

/*
 - Delta charges $0.50/mile
   + OperatingCost
*/
class DeltaCalculator : public AirlineCalculator {
    public:
        virtual float getTotalCost(const Ticket& ticket) const {
            return (float) (0.5 * ticket.mile) + getOperationCost(ticket);
        }

        virtual ~DeltaCalculator() = default;

        static DeltaCalculator* instance() {
            static DeltaCalculator calc;
            return &calc;
        }
    private:
        DeltaCalculator() = default;
};

/*
 - Southwest charges $1.00/mile
*/
class SouthWestCalculator : public AirlineCalculator {
    public:
        virtual float getTotalCost(const Ticket& ticket) const {
            return 1.0 * ticket.mile;
        }

        virtual ~SouthWestCalculator() = default;

        static SouthWestCalculator* instance() {
            static SouthWestCalculator calc;
            return &calc;
        }
    private:
        SouthWestCalculator() = default;
};

/* - LuigiAir charges $100 or 2 * OperatingCost, whichever is higher */
class LuigiAirCalculator : public AirlineCalculator {
    public:
    virtual float getTotalCost(const Ticket& ticket) const {
        return max((float) 100.0, 2 * getOperationCost(ticket));
    }

    virtual ~LuigiAirCalculator() = default;


    static LuigiAirCalculator* instance() {
        static LuigiAirCalculator calc;
        return &calc;
    }

    private:
        LuigiAirCalculator() = default;
};




AirlineCalculator* AirlineCalculator::getInstance(const Ticket& ticket) {
    // United, Delta, Southwest, LuigiAir
    switch (ticket.air) {
        case (United):
            return UnitedCalculator::instance();
        case (Delta):
            return DeltaCalculator::instance();
        case (SouthWest):
            return SouthWestCalculator::instance();
        case (LuigiAir):
            return LuigiAirCalculator::instance();
    }
    return nullptr;
}


Ticket parseString(string& s) {
    Ticket t;
    stringstream ss(s);
    string air;
    float mile;
    string lvl;
    ss >> air >> mile >> lvl;
    t.air = stringToAirline[air];
    t.mile = mile;
    t.lvl = stringToLevel[lvl];
    return t;
}





int main() {
    vector<string> input{"United 150.0 Premium", "United 120.0 Economy","United 100.0 Business","Delta 60.0 Economy","Delta 60.0 Premium","Delta 60.0 Business", "SouthWest 1000.0 Economy", "SouthWest 4000.0 Economy"};
    vector<float> output;
    for (string& s : input) {
        Ticket ticket = parseString(s);
        AirlineCalculator* clc = AirlineCalculator::getInstance(ticket);
        output.push_back(clc->getTotalCost(ticket));
    }
    for (int i = 0; i < output.size(); ++i) {
        cout << input[i] << " costs " << output[i] <<endl; 
    }


}