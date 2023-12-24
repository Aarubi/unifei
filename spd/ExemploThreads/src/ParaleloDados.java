import java.math.BigInteger;
import java.util.Scanner;

/*
 * Algoritmo Paralelo em Dados
 * Calculo do somatorio (1! + 2! + 3! + ... + n!) + (2^1 + 2^2 + ... + 2^n)
 * Exemplo para 2 threads (podem ser mais de 2 threads):
 * Calculo da thread 1 = (1! + 2! + 3! + ... + n/2!) + (2^1 + 2^2 + ... + 2^n/2)
 * Calculo da thread 2 = (n/2! + ... + n!) + (2^n/2 + ... + 2^n)
 */
public class ParaleloDados extends Thread {
	private BigInteger inicio; //inicio do intervalo de processamento
	private BigInteger fim; //fim do intervalo de processamento
	private BigInteger resultado; //resultado do processamento

	/*
	 * Construtor padrao
	 */
	public ParaleloDados(){
		this.inicio = BigInteger.ZERO;
		this.fim = BigInteger.ZERO;
		resultado = BigInteger.ZERO;
	}

	/*
	 * Define o inicio e o fim do intervalo de dados para processamento
	 */
	public void DefineIntervalo(BigInteger inicio, BigInteger fim){
		this.inicio = inicio;
		this.fim = fim;
		resultado = BigInteger.ZERO;
	}

	/*
	 * Algoritmo executado pela thread
	 * @see java.lang.Thread#run()
	 */
	public void run() {				
		resultado = BigInteger.ZERO;
		
		for(BigInteger i = inicio; i.compareTo(fim) != 0; i = i.add(BigInteger.ONE)) {
			resultado = resultado.add(Util.Potencia2(i));
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
		Scanner teclado = new Scanner(System.in);
		int numThreads;
		BigInteger n, resultado, passo, tamanho, posicao;
		long tempo1, tempo2; 
		
		
		n = BigInteger.ZERO;
		passo = new BigInteger("2000"); 
		
		System.out.println("Entre com a quantidade de threads: ");
		numThreads = teclado.nextInt();
		
		teclado.close();
		
		ParaleloDados[] threads = new ParaleloDados[numThreads]; 
		
		//Calcula o somatorio para os valores 2000, 4000, 6000, 8000, 10000
		for(int i = 0; i < 5; i++){
			n = n.add(passo);
			tamanho = n.divide( BigInteger.valueOf(numThreads) );
			
			posicao = BigInteger.ONE;
			resultado = BigInteger.ZERO;

			//cria as threads
			for(int j = 0; j < numThreads; j++) 
				threads[j] = new ParaleloDados();
			
			tempo1 = System.nanoTime();
			
			//divide os dados entre as (numThreads - 1) threads
			for(int j = 0; j < numThreads - 1; j++) {
				threads[j].DefineIntervalo(posicao, posicao.add(tamanho));
				posicao = posicao.add(tamanho);
			}
			//atribui o restante dos dados para a ultima thread 
			//resolve a questao da divisao inteira
			threads[numThreads - 1].DefineIntervalo(posicao, n);
		
			//inicia as threads
			for(int j = 0; j < numThreads; j++)
				threads[j].start();
			
			//define um ponto de sincronismo (barreira) 
			//aguarda o termino do processamento de todas as threads
			for(int j = 0; j < numThreads; j++)
				threads[j].join();
			
			//junta os resultados das threads
			for(int j = 0; j < numThreads; j++)
				resultado = resultado.add(threads[j].Resultado());
			
			tempo2 = System.nanoTime();
			
			System.out.print("N = " + n.toString());
			//System.out.print("\tResultado = " + resultado);
			System.out.println("\tTempo = " + String.valueOf((tempo2 - tempo1)/1000000) + " ms");
		}
	}

}
