#include <iostream>
#include <string>

bool registerCustomer(const std::string& name, const std::string& email) {
    if (name.empty() || email.empty() || email.find('@') == std::string::npos) {
        return false;
    }

    std::cout << "Customer registered\n";
    return true;
}

bool updateCustomer(const std::string& name, const std::string& email) {
    if (name.empty() || email.empty() || email.find('@') == std::string::npos) {
        return false;
    }

    std::cout << "Customer updated\n";
    return true;
}

int main() {
    std::cout << std::boolalpha;
    std::cout << "Register: " << registerCustomer("An", "an@example.com") << '\n';
    std::cout << "Update: " << updateCustomer("Binh", "invalid-email") << '\n';
}
