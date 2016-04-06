package test;

import test.Utils;

import java.io.File;
import java.io.IOException;

import static org.hamcrest.CoreMatchers.containsString;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertThat;
import org.junit.Test;


/**
 * Benchmark #7 test.
 *
 * @precondition Benchmark #7 has been run and the output saved to file.
 */
public class Benchmark7Test {

    /** Path to Benchmark #7 directory. */
    private static final String DIR_PATH = "bench07";

    /** Path to file with generated output. */
	private static final String GEN_OUT_PATH = DIR_PATH + File.separator + "gen1";

    // The generated output is stotchastic and hence cannot be directly compared to a "gold
    // standard". Instead we simply check introductory and concluding messages appear in the output.
    @Test
    public void test() throws IOException {
        // Generated output.
        String gen = Utils.slurp(GEN_OUT_PATH);

        // Assert that the welcome message appears in the output.
        assertThat(gen, containsString("Welcome to GrueHunt! Please don't feed the grues."));
        // Assert that the farwell message appears in the output.
        assertThat(gen, containsString("Thank you for playing"));
    }

}
