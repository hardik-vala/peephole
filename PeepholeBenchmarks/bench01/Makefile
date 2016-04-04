all: clean
	$(PEEPDIR)/joosc BacktrackSolver.java SudokuSolver.java Benchmark.java

java:
	javac -cp $(PEEPDIR)/jooslib.jar: BacktrackSolver.java SudokuSolver.java Benchmark.java

clean:	
	rm -rf *.class *.j *~

run:
	java -cp $(PEEPDIR)/jooslib.jar: Benchmark < in1
