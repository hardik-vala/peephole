# assumes sablecc script is on your PATH

# to compile the code
joosc: clean
	$(PEEPDIR)/joosc *.java

java: clean
	javac -cp $(PEEPDIR)/jooslib.jar: *.java

check:	
	./check.py

clean:	
	rm -rf *.class *.j
