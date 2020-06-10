public interface BotManager {
	public interface hasWaveEnded_func {
		@Delegate
		public boolean func();
	}
	public interface startNextWave_func {
		@Delegate
		public void func();
	}
	public interface hasGameEnded_func {
		@Delegate
		public boolean func();
	}
	public interface startNewGame_func {
		@Delegate
		public void func();
	}
	public interface getMoney_func {
		@Delegate
		public int func();
	}
	public interface placeTower_func {
		@Delegate
		public  void func(int a, int[] b);
	}
	static {
		try{
			System.loadLibrary("pns-innov");
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