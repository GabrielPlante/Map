public interface BotManager {

	private boolean hasWaveEnded();
	private void startNextWave();
	private boolean hasGameEnded();
	private void startNewGame();

	private int getMoney();
	private void placeTower(int a, int[] b);
	private

	static {
		try{
			System.loadLibrary("../x64/Debug/pns-innov");
		}catch(Exception e){
			System.out.println(e.toString());
		}
	}

	private long nativeObjectPointer;

	private native long nativeNew(int age, String name);

	public BotManager(int age, String name) {
		nativeObjectPointer = nativeNew(age, name);	
	}

	public static void main(String[] args) {

	}
}