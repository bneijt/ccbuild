.PHONY: all
all: ccbuild.1 ccbuild.dvi ccbuild.html ccbuildman.html
	

ccbuild.1: ccbuildman.sgml
	docbook-to-man $< > $@

ccbuildman.html: ccbuildman.sgml
	docbook2html -u -o . $<

ccbuild.dvi: ccbuild.sgml
	debiandoc2dvi $<

	
ccbuild.html: ccbuild.sgml
	debiandoc2html $<

clean:
	rm -f ccbuild.1 ccbuild.dvi ccbuild.info ccbuildman.html
	rm -rf ccbuild.html
