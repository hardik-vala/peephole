joosc: clean
	$(PEEPDIR)/joosc *.java *.joos

joosco: clean
	$(PEEPDIR)/joosc -O *.java *.joos

javac:
	javac -cp $(PEEPDIR)/lib/jooslib.jar: *.java

run:
	java -cp $(PEEPDIR)/lib/jooslib.jar: Main < in1 >& gen1

clean:	
	rm -rf *.class *.j *~ *.dump *.optdump
