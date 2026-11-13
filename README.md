# DRY and SRP — Research Repository

The **`latex-report`** branch contains the English coursework report in LaTeX, with integrated numeric citations and a BibLaTeX bibliography.

## Main deliverables

- [LaTeX report source](latex/report.tex)
- [BibLaTeX references](latex/references.bib)
- [Build instructions](latex/BUILD.txt)
- [Makefile](latex/Makefile)
- [C++ examples](src/)

## Build the PDF

Requirements: TeX Live, BibLaTeX, Biber, and GNU Make.

```bash
cd latex
make
```

The generated file is `latex/report.pdf`. GitHub Actions also compiles the report and uploads the PDF as a workflow artifact.

The appendices in the report load the C++ examples directly from `src/`. Do not move those files without updating the paths in `latex/report.tex`.

The Markdown report remains on the `main` branch; this branch uses LaTeX as the report source.
