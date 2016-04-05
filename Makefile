# Peephole Benchmarks directory.
PEEPBENCHDIR ?= $(PEEPDIR)/PeepholeBenchmarks

# JOOS compile the Benchmarks with optimizations, and then make sure the Benchmark tests pass.
joosco: build
	$(PEEPDIR)/scripts/total_code_length_bench.sh -O
	@$(MAKE) test >& test.log
	@less test.log
	@rm test.log

# JOOS compile the Benchmarks with no optimizations.
joosc: build
	$(PEEPDIR)/scripts/total_code_length_bench.sh

# Build the JOOS source.
build:
	$(PEEPDIR)/scripts/build_src.sh

# Test the running of the Benchmarks (Pre-condition: JOOS compilation of
# Benchmarks).
test:
	cd $(PEEPBENCHDIR)/bench01 && $(MAKE) -f Makefile javac # Java compile Benchmark #1 sources.
	javac -cp $(PEEPDIR)/lib/junit-4.12.jar: $(PEEPBENCHDIR)/test/*.java # Compile the Benchmark tests.
	cd $(PEEPBENCHDIR)/bench01 && $(MAKE) -f Makefile run # Run Benchmark #1.
	cd $(PEEPBENCHDIR) && java -cp $(PEEPDIR)/lib/hamcrest-core-1.3.jar:$(PEEPDIR)/lib/junit-4.12.jar: org.junit.runner.JUnitCore test.BenchmarkTestSuite # Test Benchmark #1.