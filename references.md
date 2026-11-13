# References

**Access date for online sources:** 13 November 2026.

The sources below support the definitions and design concepts used in the report. The report paraphrases the sources and applies them to the repository's own C++ teaching examples.

## [1] DRY and knowledge duplication

Hunt, Andrew, and David Thomas. *The Pragmatic Programmer: Your Journey to Mastery*. 20th Anniversary Edition, 2nd ed. Addison-Wesley Professional, 2019. Topic 9, “DRY—The Evils of Duplication.”

- Publisher's book page: https://www.oreilly.com/library/view/the-pragmatic-programmer/9780135956977/
- Topic 9 preview: https://www.oreilly.com/library/view/the-pragmatic-programmer/9780135956977/f_0027.xhtml
- Publisher-hosted excerpt: https://media.pragprog.com/titles/tpp20/dry.pdf

**Used for:** defining DRY as avoiding multiple representations of the same knowledge; explaining why changing requirements make duplicated knowledge risky.

## [2] Single Responsibility Principle

Martin, Robert C. “The Single Responsibility Principle.” In *97 Things Every Programmer Should Know*. O'Reilly Media, 2010, Chapter 76.

- Publisher's chapter page: https://www.oreilly.com/library/view/97-things-every/9780596809515/ch76.html

**Used for:** explaining SRP through grouping things that change for the same reason and separating things that change for different reasons; illustrating that several methods can belong to different responsibilities.

## [3] Refactoring and behavior preservation

Fowler, Martin. “Definition Of Refactoring.” 1 September 2004.

- https://martinfowler.com/bliki/DefinitionOfRefactoring.html

Fowler, Martin, with Kent Beck. *Refactoring: Improving the Design of Existing Code*. 2nd ed. Addison-Wesley Professional, 2018.

- Author's book page and definition: https://martinfowler.com/books/refactoring.html
- Refactoring overview: https://www.refactoring.com/

**Used for:** defining refactoring as an internal structural change that improves understandability and ease of modification without changing observable behavior; supporting small, behavior-preserving steps.

## [4] Coupling and module dependencies

Fowler, Martin. “Reducing Coupling.” *IEEE Software* 18, no. 4 (July/August 2001).

- Author-hosted article (PDF): https://martinfowler.com/ieeeSoftware/coupling.pdf

**Used for:** explaining that dependencies between modules cannot be eliminated entirely; the design goal is to control harmful coupling and understand dependency patterns rather than pursuing zero coupling.

## Source-use notes

1. The definitions and conceptual explanations are based on the cited publications.
2. The five code-review decisions are reasoned applications of those concepts to the scenarios in the supplied assignment brief.
3. The C++ programs in src/ were written for this repository as illustrative examples. They are not quoted from the references and are not presented as production code.
4. The customer-validation example uses a deliberately simplified email check to focus on code duplication. It must not be treated as a complete email-validation implementation.
5. The order-service example simulates persistence and notification with console output; it does not connect to a real database or email provider.
