# DRY and SRP — Research Report and C++17 Examples

This public repository contains an English research report and standalone C++17 examples for the coursework topic **“DRY & SRP — Applying the Principles Appropriately.”**

## Main documents

- [Research report](report.md): definitions, practical examples, over-application, design trade-offs, personal design evaluation, and all five code-review scenarios.
- [References](references.md): bibliographic details, links, access date, and a note describing how each source is used.
- [Code-review decisions](src/code-review/decisions.md): a concise summary of the five scenarios.

## Repository structure

- README.md
- report.md
- references.md
- .gitignore
- scripts/build-all.sh
- .github/workflows/cpp.yml
- src/dry/: four DRY examples
- src/srp/: four SRP examples
- src/code-review/decisions.md

## Build and run

Requirements: a C++17 compiler (g++ or clang++) and Bash.

From the repository root:

    bash scripts/build-all.sh

The script compiles each .cpp file independently into build/, because every example contains its own main() function.

Run an example:

    ./build/validation_before
    ./build/validation_after
    ./build/independent_rules
    ./build/premature_abstraction
    ./build/order_service_before
    ./build/order_service_after
    ./build/student_cohesive
    ./build/over_split_student

## Example guide

| Topic | Example | Main point |
|---|---|---|
| DRY — duplicated shared policy | validation_before.cpp | Same customer-validation knowledge appears twice |
| DRY — extracted shared policy | validation_after.cpp | One validation function represents the common rule |
| DRY — acceptable duplication | independent_rules.cpp | Similar arithmetic belongs to independent business policies |
| DRY — premature abstraction | premature_abstraction.cpp | A generic policy framework may be excessive for a simple fixed calculation |
| SRP — mixed responsibilities | order_service_before.cpp | Validation, calculation, persistence, and notification are combined |
| SRP — separated responsibilities | order_service_after.cpp | Collaborators own distinct concerns; the service coordinates them |
| SRP — cohesive class | student_cohesive.cpp | Several related methods can belong to one student-record responsibility |
| SRP — excessive splitting | over_split_student.cpp | One class per simple getter/setter adds indirection without value |

## Continuous integration

GitHub Actions compiles and runs all C++ examples on pushes to main and on pull requests targeting main.

## Important scope notes

The report's code samples are educational demonstrations, not production implementations. The email check is simplified, and the order repository and email sender simulate their work with console output. Read the report's assumptions before reusing any sample in a real application.
