#include <iostream>
#include <memory>
#include <string>

class PercentagePolicy {
public:
    virtual ~PercentagePolicy() = default;
    virtual double rate() const = 0;
    virtual std::string name() const = 0;
};

class TaxPolicy final : public PercentagePolicy {
public:
    double rate() const override {
        return 0.10;
    }

    std::string name() const override {
        return "Tax";
    }
};

class DiscountPolicy final : public PercentagePolicy {
public:
    double rate() const override {
        return 0.10;
    }

    std::string name() const override {
        return "Discount";
    }
};

class PercentageEngine {
public:
    double calculate(double amount, const PercentagePolicy& policy) const {
        return amount * policy.rate();
    }
};

void printResult(const PercentagePolicy& policy,
                 const PercentageEngine& engine,
                 double amount) {
    std::cout << policy.name() << ": "
              << engine.calculate(amount, policy) << '\n';
}

int main() {
    const PercentageEngine engine;
    const TaxPolicy taxPolicy;
    const DiscountPolicy discountPolicy;

    printResult(taxPolicy, engine, 20000.0);
    printResult(discountPolicy, engine, 20000.0);
}
