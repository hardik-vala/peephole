package test;

import test.Utils;

import java.io.File;
import java.io.IOException;

import static org.junit.Assert.assertEquals;
import org.junit.Test;


/**
 * Benchmark #4 test.
 *
 * @precondition Benchmark #4 has been run and the output saved to file.
 */
public class Benchmark4Test {

    /** Path to Benchmark #4 directory. */
    private static final String DIR_PATH = "bench04";

	/** Path to file with expected output. */
    private static final String EXP_OUT_PATH = DIR_PATH + File.separator + "out1";
    /** Path to file with generated output. */
	private static final String GEN_OUT_PATH = DIR_PATH + File.separator + "gen1";

    @Test
    public void test() throws IOException {
        // Expected output.
        String exp = Utils.slurp(EXP_OUT_PATH);
        // Generated output.
        String gen = Utils.slurp(GEN_OUT_PATH);

        // Assert they be equal.
        assertEquals(exp, gen);
    }

}
