joosc: clean
	$(PEEPDIR)/joosc *.java

javac: clean
	javac -cp $(PEEPDIR)/jooslib.jar: *.java

run:
	java -cp $(PEEPDIR)/jooslib.jar: Game

clean:
	rm -rf *.class *.j *.dump *.optdump

