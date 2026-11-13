#include <iostream>
#include <string>

struct Order {
    std::string customerEmail;
    double subtotal;
    double shippingFee;
};

class OrderService {
public:
    bool placeOrder(const Order& order) const {
        if (order.customerEmail.empty() || order.subtotal <= 0.0 ||
            order.shippingFee < 0.0) {
            std::cout << "Invalid order\n";
            return false;
        }

        const double total = order.subtotal + order.shippingFee;
        std::cout << "Saving order with total: " << total << '\n';
        std::cout << "Sending confirmation to: "
                  << order.customerEmail << '\n';
        return true;
    }
};

int main() {
    const OrderService service;
    const Order order{"student@example.com", 250000.0, 20000.0};
    service.placeOrder(order);
}
