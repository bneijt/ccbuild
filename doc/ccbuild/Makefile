.PHONY: all
all: ccbuild.1 ccbuildman.html
#TODO Add ccbuild.pdf and ccbuild.html back to the list


ccbuild.1:  ccbuild.1.md
	pandoc -s -t man $< > $@

ccbuildman.html:  ccbuild.1.md
	pandoc -s -t html $< > $@

ccbuild.pdf: ccbuild.dvi
	dvipdf $<

ccbuild.dvi: ccbuild.sgml
	debiandoc2dvi $<

ccbuild.html: ccbuild.sgml
	debiandoc2html $<

clean:
	rm -f ccbuild.1 ccbuild.dvi ccbuild.pdf ccbuildman.html ccbuild.log ccbuild.tex-in ccbuild.toc ccbuild.aux missfont.log ccbuild.tex
	rm -rf ccbuild.html
