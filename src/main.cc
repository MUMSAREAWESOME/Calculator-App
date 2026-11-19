#include <array>
#include <cctype>
#include <exception>
#include <iostream>
#include <cmath>
#include <memory>
#include <stdexcept>
#include <vector>
#include <limits>


class Calculator{
    public:

        double lastAnswer {0};

        Calculator() {
            std::cout << "Opened Calculator!\n";
        }

        ~Calculator() {
            std::cout << "Closed Calculator!\n";
        }

        // Basic methods (+, -, /, *)

        double basicMethods(const std::vector<double>& nums, const char& op) {
            double res {lastAnswer};
            bool divZero {false};
            switch (op){
                case '+':
                    for (const double i : nums){
                        res += i;
                    }
                    break;
                case '-':
                    for (const double i : nums){
                        res -= i;
                    }
                    break;
                case '/':
                    for (const double i : nums){
                        if (i == 0){
                            std::cout << "Dont fucking divide by zero numb nuts.\n";
                            divZero = true;
                            break;
                        }
                        res /= i;
                    }
                    break;
                case '*':
                    for (const double i : nums){
                        res *= i;
                    }
                    break;
                default:
                    std::cout << "Syntax error!\n";
                    break;
            }
            if (divZero) res = lastAnswer; 
            return res;
        }

        // Indexing (a^x)
        double calcIndex(const double& a, const double& b) {
            return std::pow(a, b);
        }

        std::array<double, 3> quadraticSolver(const double& a, const double& b, const double& c) {
            double discriminant = (b * b) - (4 * a * c); // From GROK

            if (discriminant < 0) {
                std::cout << "Erm, NO\n";
                std::array<double, 3> arr {0, 0, 1};
                return arr;
            }
            
            if (a == 0){
                std::cout << "Ahh... NO fuck yo\n";
                std::array<double, 3> arr {0, 0, 1};
                return arr;
            }
            std::array<double, 3> res;
            res[0] = {(-b+sqrt(((b*b)-(4*a*c)))) / (2 * a)};
            res[1] = {(-b-sqrt(((b*b)-(4*a*c)))) / (2 * a)};
            res[2] = 0;
            return res;
        }

        // Pythagoras theorem (A^2 + B^2 = C^2)

        double solveForC(const double& a2, const double& b2) {
            // The input needs to be the squared versions of A and B
            double res {(sqrt(a2 + b2))};
            return res;
        }

        double solveForAorB(const double& c2, const double& b2) {
            // The input needs to be the squared versions of A and B
            double check {c2 - b2};
            if (check < 0) return 0;
            double res {(sqrt(c2 - b2))};
            return res;
        }
};

double roundToDecimalPlaces(const double& value, const int& decimalPlaces) {
    // From: https://medium.com/@ryan_forrester_/how-to-round-in-c-complete-guide-e02c9e671050
    const double multiplier = std::pow(10.0, decimalPlaces);
    return std::round(value * multiplier) / multiplier;
}

void arrCalc(Calculator& calc) {
    std::vector<double> nums;
    int length;
    char op;

    std::cout << "How many digits to you want to +, -, * or / to your last answer? ";

    try {
        std::cin >> length;

        if (std::cin.fail()) {
            throw std::runtime_error("Not a double");
        }
    }
    catch (std::exception& e) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // From Grok
        length = 1;
        std::cerr << e.what() << "\nDefaulting to 1 digit\n";
    }



    std::cout << "Enter numbers: ";

    for (int i = 0; i < length; i ++) {
        double tmp;
        try {
            std::cin >> tmp;
            if (std::cin.fail()) {
                throw std::runtime_error("Not a double");
            }
        }
        catch (std::exception& e) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // From Grok
            tmp = 1;
            std::cerr << e.what() << "\nDefaulting to 1\n";
        }
        
        nums.push_back(tmp);
    }

    std::cout << "Enter the the operator you want (+ - / *): ";


    try {
        std::cin >> op;
        if (std::cin.fail()) {
            throw std::runtime_error("Not a char");
            }
    }
    catch (std::exception& e) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // From Grok
        op = '+';
        std::cerr << e.what() << "\nDefaulting to +\n";
    }

    switch (op) {
        case '+':
            op = '+';
            break;
        case '-':
            op = '-';
            break;
        case '/':
            op = '/';
            break;
        case '*':
            op = '*';
            break;
        default:
            std::cout << "Defaulting to +!\n";
            op = '+';
            break;
    }

    std::cout << "Answer: ";

    double res = calc.basicMethods(nums, op);
    
    std::cout << res << '\n';

    calc.lastAnswer = res;
}

void solveQuadratic(Calculator& calc) {
    double a, b, c;
    int choice;


    std::cout << "Enter the a, b and c values in order: ";
    try {
        std::cin >> a >> b >> c;
        if (std::cin.fail()) {
            throw std::runtime_error("Not a double");
        }
    }
    catch (std::exception& e) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // From Grok
        std::cerr << e.what() << "\nWhat the FUCK...\n";
        return;
    }

    std::array<double, 3> res = calc.quadraticSolver(a, b, c);
    if (res[2] == 1) {
        std::cout << "Could not calculate... Invalid\n";
        return;
    }
    std::cout << "Solution 1: " << res[0] << "\nSolution 2: " << res[1] << '\n';
    std::cout << "Select solution to save as last answer [1/2] or [0] to not save it: ";
    std::cin >> choice;

    try {
        std::cin >> choice;
        if (std::cin.fail()) {
            throw std::runtime_error("Not an int");
        }
    }
    catch (std::exception& e) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // From Grok
        return;
    }

    switch (choice) {
        case 0:
            break;
        case 1:
            std::cout << "Saving solution 1!\n";
            calc.lastAnswer = res[0];
            break;
        case 2:
            std::cout << "Saving solution 2!\n";
            calc.lastAnswer = res[1];
            break;
        default:
            std::cout << "Choice not found!\nDefaulting to 1!\nSaving solution 1!\n";
            calc.lastAnswer = res[0];
            break;
    }
}

void index(Calculator& calc) {
    double a, b;
    try {
        std::cin >> a >> b;
        if (std::cin.fail()) {
            throw std::runtime_error("Not a double");
        }
    }
    catch (std::exception& e) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // From Grok
        return;
    }
    double ans {calc.calcIndex(a, b)};
    std::cout << "Answer: " << ans;
    calc.lastAnswer = ans;
}


int main() {
    std::unique_ptr<Calculator> calc {std::make_unique<Calculator>()};
    bool quit = false;
    do{
        char choice;
        std::cout << "What would you like to do. (C)lear number, (A)dd/sub/mult/div numbers from your num, (S)olve quadratic, c(H)eck number, (Q)uit: ";
        std::cin >> choice;
        choice = std::tolower(choice);

        switch (choice) {
            case 'q':
                quit = true;
                break;
            case 'c':
                calc->lastAnswer = 0;
                break;
            case 'a':
                arrCalc(*calc);
                break;
            case 's':
                solveQuadratic(*calc);
                break;
            case 'h':
                std::cout << "Current number: " << calc->lastAnswer << '\n';
                break;
            default:
                std::cout << "Comand not found!\n";
                break;
        }

    }
    while (!quit);
    return 0;
}