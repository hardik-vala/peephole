package test;

import org.junit.runner.RunWith;
import org.junit.runners.Suite;


@RunWith(Suite.class)
@Suite.SuiteClasses({
	Benchmark1Test.class,
	Benchmark2Test.class,
	Benchmark3Test.class,
	Benchmark4Test.class,
	Benchmark5Test.class,
	Benchmark6Test.class,
	Benchmark7Test.class
})

public class BenchmarkTestSuite {
  // This class remains empty, used only as a holder for the above annotations.
}
