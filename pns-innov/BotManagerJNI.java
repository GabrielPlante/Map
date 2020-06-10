import java.util.*;

interface hasWaveEnded_func {
	public boolean func();
}

public class BotManagerJNI {
	static {
		try{
			System.loadLibrary("pns-innov");
		}catch(Exception e){
			System.out.println(e.toString());
		}
	}
	/*
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
	} */
	
	private long nativeObjectPointer;

	public BotManagerJNI(hasWaveEnded_func hasWaveEnded) {
		nativeObjectPointer = nativeNew(hasWaveEnded);
	}

	private native long nativeNew(
		hasWaveEnded_func hasWaveEnded);
	/*
	private native long nativeNew(
		hasWaveEnded_func hasWaveEnded, startNextWave_func startNextWave,
		hasGameEnded_func hasGameEnded, startNewGame_func startNewGame,
		getMoney_func getMoney, placeTower_func placeTower,
		List<Integer> towersCost, TowerManagerJNI towerManager, int moneyGap,
		int nbrOfBotPerGeneration, int percentageOfBotKept,
		int percentageOfParameterChanged, int nbrOfStaleGenerationForReset);

	public BotManager(
		hasWaveEnded_func hasWaveEnded, startNextWave_func startNextWave,
		hasGameEnded_func hasGameEnded, startNewGame_func startNewGame,
		getMoney_func getMoney, placeTower_func placeTower,
		List<Integer> towersCost, TowerManagerJNI towerManager, int moneyGap,
		int nbrOfBotPerGeneration, int percentageOfBotKept,
		int percentageOfParameterChanged, int nbrOfStaleGenerationForReset) {
		
		nativeObjectPointer = nativeNew(
			hasWaveEnded_func hasWaveEnded, startNextWave,
			hasGameEnded, startNewGame, getMoney, placeTower,
			towersCost, towerManager, moneyGap, nbrOfBotPerGeneration,
			percentageOfBotKept, percentageOfParameterChanged,
			nbrOfStaleGenerationForReset);
	} */

	public static void main(String[] args) {

	}
}