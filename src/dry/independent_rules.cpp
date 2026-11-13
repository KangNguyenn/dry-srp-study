#include <iomanip>
#include <iostream>

class TaxCalculator {
public:
    double calculateTax(double amount) const {
        constexpr double taxRate = 0.10;
        return amount * taxRate;
    }
};

class LoyaltyDiscountCalculator {
public:
    double calculateDiscount(double amount) const {
        constexpr double loyaltyDiscountRate = 0.10;
        return amount * loyaltyDiscountRate;
    }
};

int main() {
    constexpr double amount = 20000.0;

    const TaxCalculator taxCalculator;
    const LoyaltyDiscountCalculator discountCalculator;

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Tax: " << taxCalculator.calculateTax(amount) << '\n';
    std::cout << "Loyalty discount: "
              << discountCalculator.calculateDiscount(amount) << '\n';
}
