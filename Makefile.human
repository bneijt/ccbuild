
.PHONY: all clean doc apidoc help
all: ./src/ccbuild

help:
	@echo Possible targets include:
	@echo all        build the main program.
	@echo clean      distclean and remove generatable files.
	@echo distclean  Remove all .o, .gch and o files, recursively.
	@echo doc        Build documentation.
	@echo apidoc     Build api documentation using doxygen.
	@echo help       Show this message.

./src/SourceScanner/yylex.cc: ./src/SourceScanner/lexer
	flex $<
	mv yylex.cc $@

include Makefile.ccbuild

clean: distclean
	rm -f src/ccbuild
	rm -f src/SourceScanner/yylex.cc

apidoc:
	doxygen

doc:
	$(MAKE) -C doc/debiandoc
