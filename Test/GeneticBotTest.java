import org.junit.Test;
import static org.junit.Assert.*;
import java.util.*;
//import GeneticBotJNI;

public class GeneticBotTest {
    @Test
    public void testConstructor() {
    	List<Integer> expected = new ArrayList<Integer>(
    		Arrays.asList(1, 2, 3, 4));
    	GeneticBotJNI self = new GeneticBotJNI(expected);
    	List<Integer> real = self.getDecisionMap();

    	assertEquals(expected.size(), real.size());
    	for (int i = 0; i < expected.size(); i++)
    		assertEquals(expected.get(i), real.get(i));
    }

    @Test
    public void testGetValuesUnder() {
    	List<Integer> array1 = new ArrayList<Integer>(
    		Arrays.asList(1, 8, 7, 16, 9, 4, 7, 3, 2));
		List<Integer> expected1, expected2, res;

		expected1 = new ArrayList<Integer>(Arrays.asList( 0, 5, 7, 8));
		expected2 = new ArrayList<Integer>(Arrays.asList(0, 1, 2, 4, 5, 6, 7, 8));

		GeneticBotJNI bot = new GeneticBotJNI(new ArrayList<Integer>());

		res = bot.getValuesUnder(array1, 5);
		for (int i = 0; i < expected1.size(); i++)
			assertEquals(expected1.get(i), res.get(i));
		res = bot.getValuesUnder(array1, 9);
		for (int i = 0; i < expected2.size(); i++)
			assertEquals(expected2.get(i), res.get(i));
		res = bot.getValuesUnder(array1, 0);
		assertEquals(0, res.size());
    }
}