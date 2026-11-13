LATEX=pdflatex
BIBER=biber

.PHONY: all clean

all:
	$(LATEX) -interaction=nonstopmode -halt-on-error report.tex
	$(BIBER) report
	$(LATEX) -interaction=nonstopmode -halt-on-error report.tex
	$(LATEX) -interaction=nonstopmode -halt-on-error report.tex

clean:
	rm -f report.aux report.bbl report.bcf report.blg report.log report.out report.run.xml report.toc report.pdf
