# assumes sablecc script is on your PATH

joosc: clean
	$(PEEPDIR)/joosc *.java

joosco: clean
	$(PEEPDIR)/joosc -O *.java

javac:
	javac -cp $(PEEPDIR)/lib/jooslib.jar: *.java

check:	
	./check.py

run:
	java -cp $(PEEPDIR)/lib/jooslib.jar: Main < in1 >& gen1

clean:	
	rm -rf *.class *.j *~ *.dump *.optdump
