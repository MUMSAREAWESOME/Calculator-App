#include <array>
#include <iostream>
#include <cmath>
#include <memory>
#include <vector>


class Calculator{
    private:
        int smartness {0};
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
            double res {0};
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
            }
            lastAnswer = res;
            return res;
        }

        // Indexing (a^x)
        double calcIndex(const double& a, const double& b) {
            double res {a};
            for (int i = 0; i < (b-1); i ++) {
                res *= res;
            }
            lastAnswer = res;
            return res;
        }

        std::array<double, 2> quadraticSolver(const double& a, const double& b, const double& c) {
            std::array<double, 2> res;
            res[0] = {(-b+sqrt(((b*b)-(4*a*c)))) / (2 * a)};
            res[1] = {(-b-sqrt(((b*b)-(4*a*c)))) / (2 * a)};
            return res;
        }

        // Pythagoras theorem (A^2 + B^2 = C^2)

        double solveForC(const double& a2, const double& b2) {
            // The input needs to be the squared versions of A and B
            double res {(sqrt(a2) + sqrt(b2))};
            lastAnswer = res;
            return res;
        }

        double solveForAorB(const double& c2, const double& b2) {
            // The input needs to be the squared versions of A and B
            double res {(sqrt(c2) - sqrt(b2))};
            lastAnswer = res;
            return res;
        }
};

void arrCalc(Calculator& calc) {
    std::vector<double> nums;
    int length;
    char op;

    std::cout << "How many digits to you want to +, -, * or /? ";

    std::cin >> length;

    std::cout << "Enter numbers: ";

    for (int i = 0; i < length; i ++) {
        double tmp;
        std::cin >> tmp;
        nums.push_back(tmp);
    }

    std::cout << "Enter operator (+ - / *): ";

    std::cin >> op;

    std::cout << calc.basicMethods(nums, op) << '\n';
}

double roundToDecimalPlaces(const double& value, const int& decimalPlaces) {
    // From: https://medium.com/@ryan_forrester_/how-to-round-in-c-complete-guide-e02c9e671050
    const double multiplier = std::pow(10.0, decimalPlaces);
    return std::round(value * multiplier) / multiplier;
}

void solveQuadratic(Calculator& calc) {
    double a, b, c;
    int choice;
    std::cout << "Enter the a, b and c values in order: ";
    std::cin >> a >> b >> c;
    std::array<double, 2> res = calc.quadraticSolver(a, b, c);
    std::cout << "Solution 1: " << res[0] << "\nSolution 2: " << res[1] << '\n';
    std::cout << "Select solution to save as last answer [1/2]: ";
    std::cin >> choice;
    switch (choice) {
        case '1':
            std::cout << "Saving solution 1!\n";
            calc.lastAnswer = res[0];
            break;
        case '2':
            std::cout << "Saving solution 2!\n";
            calc.lastAnswer = res[1];
            break;
        default:
            std::cout << "Defaulting to 1!\nSaving solution 1!\n";
            calc.lastAnswer = res[0];
            break;
    }
}

int main() {
    std::unique_ptr<Calculator> calc {std::make_unique<Calculator>()};
    solveQuadratic(*calc);
    // arrCalc(*calc);
    return 0;
}