package test;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;


/**
  * Container for test utilities.
  */
class Utils {

	// System line separator.
	private static final String LS = System.getProperty("line.separator");

	/**
	 * Slurp a file.
	 *
	 * @param path - Filepath
	 * @return File contents as a string
	 * @throws IOException if something goes wrong in the reading of the file
	 */
	static String slurp(String path) throws IOException {
		StringBuilder sb = new StringBuilder();

        try (BufferedReader r = new BufferedReader(new FileReader(path))) {
        	String l;
       		while ((l = r.readLine()) != null) sb.append(l + LS);
        }

        return sb.toString();
	}
	
}
