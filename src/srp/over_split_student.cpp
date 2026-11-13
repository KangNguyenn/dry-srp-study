#include <iostream>
#include <string>
#include <utility>

struct Student {
    std::string name;
    int age;
};

class StudentNameGetter {
public:
    explicit StudentNameGetter(const Student& student)
        : student_(student) {}

    std::string get() const {
        return student_.name;
    }

private:
    const Student& student_;
};

class StudentNameSetter {
public:
    explicit StudentNameSetter(Student& student)
        : student_(student) {}

    void set(std::string name) const {
        student_.name = std::move(name);
    }

private:
    Student& student_;
};

class StudentAgeGetter {
public:
    explicit StudentAgeGetter(const Student& student)
        : student_(student) {}

    int get() const {
        return student_.age;
    }

private:
    const Student& student_;
};

class StudentAgeSetter {
public:
    explicit StudentAgeSetter(Student& student)
        : student_(student) {}

    void set(int age) const {
        student_.age = age;
    }

private:
    Student& student_;
};

int main() {
    Student student{"An", 19};

    const StudentNameGetter nameGetter(student);
    const StudentNameSetter nameSetter(student);
    const StudentAgeGetter ageGetter(student);
    const StudentAgeSetter ageSetter(student);

    nameSetter.set("Binh");
    ageSetter.set(20);

    std::cout << nameGetter.get() << ", "
              << ageGetter.get() << '\n';
}
