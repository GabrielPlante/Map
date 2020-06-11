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

	private long getNativeObjectPtr() { return nativeObjectPtr; }
	private void printList(List<Integer> l) {
		System.out.println(Arrays.toString(l.toArray()));
		System.out.println("");
	}
	public native long nativeNew(List<Integer> decisionMap);
	public native List<Integer> getDecisionMap();
	public native List<Integer> getValuesUnder(
		List<Integer> values, int max);


	public static void main(String[] args) {
		GeneticBotJNI self = new GeneticBotJNI(
			new ArrayList<Integer>(Arrays.asList(1, 2, 3, 4)));

		List<Integer> test1 = new ArrayList<Integer>(
			Arrays.asList(1, 8,  7, 16, 9, 4, 7, 3, 2));
		System.out.println("expected: 0, 5, 7, 8");
		test1 = self.getValuesUnder(test1, 5);
		self.printList(test1);

		System.out.println("expected 1, 2, 3, 4");
		List<Integer> bof = self.getDecisionMap();
		self.printList(bof);
	}
}