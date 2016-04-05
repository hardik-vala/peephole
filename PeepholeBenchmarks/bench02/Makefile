# assumes sablecc script is on your PATH

joosc: clean
	$(PEEPDIR)/joosc *.java

joosc_opt: clean
	$(PEEPDIR)/joosc -O *.java

javac: clean
	javac -cp $(PEEPDIR)/jooslib.jar: *.java

check:	
	./check.py

clean:	
	rm -rf *.class *.j *.dump *.optdump
