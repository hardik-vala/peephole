joosc: clean
	$(PEEPDIR)/joosc BacktrackSolver.java SudokuSolver.java Benchmark.java

joosc_opt: clean
	$(PEEPDIR)/joosc -O BacktrackSolver.java SudokuSolver.java Benchmark.java

javac:
	javac -cp $(PEEPDIR)/jooslib.jar: BacktrackSolver.java SudokuSolver.java Benchmark.java

run:
	java -cp $(PEEPDIR)/jooslib.jar: Benchmark < in1

clean:	
	rm -rf *.class *.j *~ *.dump *.optdump

