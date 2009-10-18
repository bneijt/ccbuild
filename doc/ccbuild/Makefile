.PHONY: all
all: ccbuild.1 ccbuild.html ccbuildman.html ccbuild.pdf
	

ccbuild.1: ccbuildman.sgml
	docbook-to-man $< > $@

ccbuildman.html: ccbuildman.sgml
	docbook2html -u -o . $<

ccbuild.pdf: ccbuild.dvi
	dvipdf $<

ccbuild.dvi: ccbuild.sgml
	debiandoc2dvi $<
	
ccbuild.html: ccbuild.sgml
	debiandoc2html $<

clean:
	rm -f ccbuild.1 ccbuild.dvi ccbuild.pdf ccbuildman.html ccbuild.log ccbuild.tex-in ccbuild.toc ccbuild.aux missfont.log ccbuild.tex
	rm -rf ccbuild.html
