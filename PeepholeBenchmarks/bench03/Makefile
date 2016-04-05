joosc: clean
	$(PEEPDIR)/joosc *.java *.joos

joosco: clean
	$(PEEPDIR)/joosc -O *.java *.joos

javac:
	javac -cp $(PEEPDIR)/jooslib.jar: *.java

run:
	java -cp $(PEEPDIR)/jooslib.jar: Main < in1 > gen1

clean:	
	rm -rf *.class *.j *.dump *.optdump
