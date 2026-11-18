#include <iostream>
#include <cmath>
#include <memory>
#include <sstream>
#include <string>
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
            double result {0};
            switch (op){
                case '+':
                    for (const double i : nums){
                        result += i;
                    }
                    break;
                case '-':
                    for (const double i : nums){
                        result -= i;
                    }
                    break;
                case '/':
                    for (const double i : nums){
                        result /= i;
                    }
                    break;
                case '*':
                    for (const double i : nums){
                        result *= i;
                    }
                    break;
                default:
                    std::cout << "Syntax error!\n";
            }
            return result;
        }

        // Pythagoras theorem (A^2 + B^2 = C^2)

        double solveForC(const double& a2, const double& b2) {
            // The input needs to be the squared versions of A and B
            return (sqrt(a2) + sqrt(b2));
        }

        double solveForAorB(const double& c2, const double& b2) {
            // The input needs to be the squared versions of A and B
            return (sqrt(c2) - sqrt(b2));
        }

};

int main() {
    std::unique_ptr<Calculator> calc;
    std::vector<double> nums;
    int length;

    std::cout << "How many digits to you want to +, -, * or /? ";

    std::cin >> length;

    std::cout << "Enter numbers: ";

    for (int i = 0; i < length; i ++) {
        double tmp;
        std::cin >> tmp;
        nums.push_back(tmp);
    }

    std::cout << calc->basicMethods(nums, '+') << '\n';

    return 0;
}