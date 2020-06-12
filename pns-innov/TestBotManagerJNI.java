import java.util.*;


class hasWaveEnded_func implements _hasWaveEnded_func {
	public boolean func() {
		return true;
	}
}

class startNextWave_func implements _startNextWave_func{
	public void func() {
		System.out.println("startNextWave()!");
	}
}
class hasGameEnded_func implements _hasGameEnded_func {
	public boolean func() {
		return false;
	}
}
class startNewGame_func implements _startNewGame_func {
	public void func() {
		System.out.println("startNewGame()!");
	}
}
class getMoney_func implements _getMoney_func{
	public int func() {
		return 77;
	}
}
class placeTower_func implements _placeTower_func {
	public  void func(int a, int[] b) {
		System.out.println("a= " + a + "\n" + "b= " + Arrays.toString(b));
		for (int i = 0; i < b.length; i++)
			b[i] += a;
		System.out.println("b= " + Arrays.toString(b));
	}
}

public class TestBotManagerJNI {

	public static void main(String[] args) {
		hasWaveEnded_func hwe = new hasWaveEnded_func();
		startNextWave_func snw = new startNextWave_func();
		hasGameEnded_func hge = new hasGameEnded_func();
		startNewGame_func sng = new startNewGame_func();
		getMoney_func gm = new getMoney_func();
		placeTower_func pt = new placeTower_func();
		BotManagerJNI self = new BotManagerJNI(hwe, snw, hge, sng, gm, pt);
	}
}