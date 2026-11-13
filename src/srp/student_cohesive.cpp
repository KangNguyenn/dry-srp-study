#include <iomanip>
#include <iostream>
#include <numeric>
#include <string>
#include <utility>
#include <vector>

class StudentRecord {
public:
    explicit StudentRecord(std::string name)
        : name_(std::move(name)) {}

    void updateName(std::string name) {
        if (!name.empty()) {
            name_ = std::move(name);
        }
    }

    void addGrade(double grade) {
        if (grade >= 0.0 && grade <= 10.0) {
            grades_.push_back(grade);
        }
    }

    double gpa() const {
        if (grades_.empty()) {
            return 0.0;
        }

        const double sum = std::accumulate(
            grades_.begin(), grades_.end(), 0.0
        );
        return sum / static_cast<double>(grades_.size());
    }

    std::string academicStanding() const {
        if (grades_.empty()) {
            return "No grades";
        }
        return gpa() >= 5.0 ? "Pass" : "Needs improvement";
    }

    void printSummary() const {
        std::cout << "Student: " << name_ << '\n';
        std::cout << "Average: " << std::fixed << std::setprecision(2)
                  << gpa() << '\n';
        std::cout << "Standing: " << academicStanding() << '\n';
    }

private:
    std::string name_;
    std::vector<double> grades_;
};

int main() {
    StudentRecord student("An");
    student.addGrade(8.0);
    student.addGrade(7.5);
    student.addGrade(9.0);
    student.printSummary();
}
