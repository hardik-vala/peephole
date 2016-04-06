joosc: clean
	$(PEEPDIR)/joosc *.java

joosco: clean
	$(PEEPDIR)/joosc -O *.java

javac:
	javac -cp $(PEEPDIR)/jooslib.jar: *.java

run:
	java -cp $(PEEPDIR)/jooslib.jar: Main < in1 >& gen1

clean:
	rm -f *.class *.j *.optdump *.dump
