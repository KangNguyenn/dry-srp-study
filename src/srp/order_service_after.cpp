#include <iostream>
#include <string>

struct Order {
    std::string customerEmail;
    double subtotal;
    double shippingFee;
};

class OrderValidator {
public:
    bool isValid(const Order& order) const {
        return !order.customerEmail.empty() &&
               order.subtotal > 0.0 &&
               order.shippingFee >= 0.0;
    }
};

class OrderCalculator {
public:
    double total(const Order& order) const {
        return order.subtotal + order.shippingFee;
    }
};

class OrderRepository {
public:
    void save(const Order&, double total) const {
        std::cout << "Saving order with total: " << total << '\n';
    }
};

class ConfirmationSender {
public:
    void send(const Order& order) const {
        std::cout << "Sending confirmation to: "
                  << order.customerEmail << '\n';
    }
};

class OrderService {
public:
    OrderService(const OrderValidator& validator,
                 const OrderCalculator& calculator,
                 const OrderRepository& repository,
                 const ConfirmationSender& sender)
        : validator_(validator),
          calculator_(calculator),
          repository_(repository),
          sender_(sender) {}

    bool placeOrder(const Order& order) const {
        if (!validator_.isValid(order)) {
            std::cout << "Invalid order\n";
            return false;
        }

        const double total = calculator_.total(order);
        repository_.save(order, total);
        sender_.send(order);
        return true;
    }

private:
    const OrderValidator& validator_;
    const OrderCalculator& calculator_;
    const OrderRepository& repository_;
    const ConfirmationSender& sender_;
};

int main() {
    const OrderValidator validator;
    const OrderCalculator calculator;
    const OrderRepository repository;
    const ConfirmationSender sender;
    const OrderService service(validator, calculator, repository, sender);

    const Order order{"student@example.com", 250000.0, 20000.0};
    service.placeOrder(order);
}
