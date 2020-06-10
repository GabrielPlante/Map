import java.util.*;

public class TowerManagerJNI {
	static {
		try{
			System.loadLibrary("pns-innov");
		}catch(Exception e){
			System.out.println(e.toString());
		}
	}
	private long nativeObjectPtr;
	
	// the 2 first parameters take list of int[2]
	public TowerManagerJNI(
		List<int[]> pathVector,
		List<int[]> buildableVector,
		List<Integer> towersRange) {
		nativeObjectPtr = nativeNew(
			pathVector, buildableVector, towersRange);	
	}

	private long getNativeObjectPtr() { return nativeObjectPtr; }
	private void printList(List<Integer> l) {
		System.out.println(Arrays.toString(l.toArray()));
		System.out.println("");
	}
	private native long nativeNew(
		List<int[]> pathVector,
		List<int[]> buildableVector,
		List<Integer> towersRange);

	/*
	public static void main(String[] args) {
		List<int[]> pathVector = new ArrayList<int[]>(
			Arrays.asList(
				new int[]{2, 3}, new int[]{5, 7}));
		List<int[]> buildableVector = new ArrayList<int[]>(
			Arrays.asList(
					new int[]{10, 12}, new int[]{14, 16}));
		List<Integer> towersRange = new ArrayList<Integer>(
					Arrays.asList(7, 14, 21, 28));
		TowerManagerJNI self = new TowerManagerJNI(
			pathVector, 
			buildableVector,
			towersRange);
		System.out.println("nativeObjectPtr= " + self.getNativeObjectPtr());
	} */
}