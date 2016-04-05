joosco_bench: build
	$(PEEPDIR)/scripts/total_code_length_bench.sh -O

joosc_bench: build
	$(PEEPDIR)/scripts/total_code_length_bench.sh

build:
	$(PEEPDIR)/scripts/build_src.sh
