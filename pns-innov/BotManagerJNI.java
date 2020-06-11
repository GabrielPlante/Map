import java.util.*;

interface _hasWaveEnded_func {
	public boolean func();
}
interface _startNextWave_func {
	public void func();
}
interface _hasGameEnded_func {
	public boolean func();
}
interface _startNewGame_func {
	public void func();
}
interface _getMoney_func {
	public int func();
}
interface _placeTower_func {
	public  void func(int a, int[] b);
}

public class BotManagerJNI {
	static {
		try{
			System.loadLibrary("pns-innov");
		}catch(Exception e){
			System.out.println(e.toString());
		}
	}
	
	
	private long nativeObjectPointer;

	public BotManagerJNI(
		_hasWaveEnded_func hasWaveEnded, _startNextWave_func startNextWave,
		_hasGameEnded_func hasGameEnded, _startNewGame_func startNewGame,
		_getMoney_func getMoney, _placeTower_func placeTower) {
		nativeObjectPointer = nativeNew(
			hasWaveEnded, startNextWave,
			hasGameEnded, startNewGame,
			getMoney, placeTower);
	}

	private native long nativeNew(
		_hasWaveEnded_func hasWaveEnded, _startNextWave_func startNextWave,
		_hasGameEnded_func hasGameEnded, _startNewGame_func startNewGame,
		_getMoney_func getMoney, _placeTower_func placeTower);
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