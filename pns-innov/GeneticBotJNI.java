import java.util.*;

public class GeneticBotJNI {
	private long nativeObjectPtr;

	static {
		try{
			System.loadLibrary("pns-innov");
		}catch(Exception e){
			System.out.println(e.toString());
		}
	}

	public GeneticBotJNI(List<Integer> decisionMap) {
		nativeObjectPtr = nativeNew(decisionMap);	
	}

	public native long nativeNew(List<Integer> decisionMap);

	public native List<Integer> getValuesUnder(
		List<Integer> values, int max);

	public static void main(String[] args) {
		GeneticBotJNI self = new GeneticBotJNI(
			new ArrayList<Integer>(Arrays.asList(1, 2, 3, 4)));
	}
}