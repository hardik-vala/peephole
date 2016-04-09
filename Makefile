# Peephole Benchmarks directory.
PEEPBENCHDIR ?= $(PEEPDIR)/PeepholeBenchmarks
# Peephole lib directory.
PEEPLIBDIR ?= $(PEEPDIR)/lib

# JOOS compile the Benchmarks with and without optimizations, report the results and
# then make sure the Benchmark tests pass.
joosc: build
	$(PEEPDIR)/scripts/joosc_and_report.sh
	@-$(MAKE) test >& test.log
	@less test.log
	@rm -f test.log

# Build the JOOS source.
build:
	cd $(PEEPDIR)/JOOSA-src/ && $(MAKE) -f Makefile clean main

# Test the running of the Benchmarks (Pre-condition: JOOS compilation of
# Benchmarks).
test:
	@# Delete test .class files and outputs generated from running the Benchmarks
	rm -rf $(PEEPBENCHDIR)/test/*.class $(PEEPBENCHDIR)/*/gen1
	@# Compile the test source.
	javac -cp $(PEEPLIBDIR)/hamcrest-core-1.3.jar:$(PEEPLIBDIR)/junit-4.12.jar: $(PEEPBENCHDIR)/test/*.java
	@# Run the benchmarks.
	-$(PEEPDIR)/scripts/run_bench.sh
	@# Run the tests.
	cd $(PEEPBENCHDIR) && java -cp $(PEEPLIBDIR)/hamcrest-core-1.3.jar:$(PEEPLIBDIR)/junit-4.12.jar: org.junit.runner.JUnitCore test.BenchmarkTestSuite
