import java.math.BigInteger;

/*
 * Algoritmo Paralelo em Controle
 * Calculo do somatorio (2^1 + 2^2 + ... + 2^n) + (1! + 2! + 3! + ... + n!) 
 * Calculo da thread 1 = (2^1 + 2^2 + ... + 2^n) 
 * Calculo da thread 2 = (1! + 2! + 3! + ... + n!)
 */
public class ParaleloControle extends Thread {			
	private BigInteger n; //numero de elementos para processamento
	private BigInteger resultado; //resultado do processamento
	private int tarefa; //tarefa realizada pela thread
	
	/*
	 * Construtor padrao 
	 */
	public ParaleloControle(BigInteger n, int tarefa){
		this.n = n;
		this.tarefa = tarefa;
		resultado = BigInteger.ZERO;
	}
		
	/*
	 * Algoritmo executado pela thread
	 * @see java.lang.Thread#run()
	 */
	public void run() {				
		resultado = BigInteger.ZERO;
		
		if (tarefa == 0) { //Somatorio (2^1 + 2^2 + ... + 2^n)
		
			for(BigInteger i = BigInteger.ONE; i.compareTo(n) != 0; i = i.add(BigInteger.ONE))
				resultado = resultado.add(Util.Potencia2(i));
		
		} else { //Somatorio (1! + 2! + 3! + ... + n!)

			for(BigInteger i = BigInteger.ONE; i.compareTo(n) != 0; i = i.add(BigInteger.ONE)) 
				resultado = resultado.add(Util.Fatorial(i));		
		
		}
		
	}
	
	/*
	 * Retorna o resultado do processamento
	 */
	public BigInteger Resultado() {
		return resultado;
	}
	
	public static void main(String[] args) throws InterruptedException {
		BigInteger n, resultado, passo;
		long tempo1, tempo2; 
		
		n = BigInteger.ZERO;
		passo = new BigInteger("2000");
				
		ParaleloControle thread0, thread1;
		
		//Calcula o somatorio para os valores 2000, 4000, 6000, 8000, 10000
		for(int i = 0; i < 5; i++){
			n = n.add(passo);
			resultado = BigInteger.ZERO;
		
			//cria as threads
			thread0 = new ParaleloControle(n, 0);
			thread1 = new ParaleloControle(n, 1);

			tempo1 = System.nanoTime();

			//inicia as threads
			thread0.start();
			thread1.start();
					
			//define um ponto de sincronismo (barreira) 
			//aguarda o termino do processamento de todas as threads
			thread0.join();
			thread1.join();
			
			//junta os resultados das threads
			resultado = resultado.add(thread0.Resultado());
			resultado = resultado.add(thread1.Resultado());
			
			tempo2 = System.nanoTime();
			
			System.out.print("N = " + n.toString());
			//System.out.print("\tResultado = " + resultado);
			System.out.println("\tTempo = " + String.valueOf((tempo2 - tempo1)/1000000) + " ms");
		}
	}

}
