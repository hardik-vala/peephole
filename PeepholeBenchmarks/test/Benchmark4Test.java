package test;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.InputStreamReader;
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
    public void benchmark4Test() throws InterruptedException, IOException {
        // Read the expected output from file.
        String exp = "";
        try (BufferedReader r = new BufferedReader(new FileReader(EXP_OUT_PATH))) {
        	String s;
       		while ((s = r.readLine()) != null) exp += s + "\n";
        }

        // Read the generated output from file.
        String gen = "";
        try (BufferedReader r = new BufferedReader(new FileReader(GEN_OUT_PATH))) {
            String s;
            while ((s = r.readLine()) != null) gen += s + "\n";
        }

        // Assert they be equal.
        assertEquals(exp, gen);
    }

}
