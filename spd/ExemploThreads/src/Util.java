import java.math.BigInteger;

/*
 * Funcoes matematicas utilitarias
 */
public class Util {

	/*
	 * Funcao para calcular o fatorial de um numero qualquer n
	 */
	public static BigInteger Fatorial(BigInteger n) {
		BigInteger soma = BigInteger.ONE;
		
		//calculo de 0!
		if (n.compareTo(BigInteger.ZERO) == 0) return soma; 
		
		//calculo de n!
		for(BigInteger i = BigInteger.ONE; i.compareTo(n) != 0; i = i.add(BigInteger.ONE))
			soma = soma.multiply(i);
		
		return soma;
	}
	
	/*
	 * Funcao para calcular a potencia de 2^n
	 */
	public static BigInteger Potencia2(BigInteger n) {
		BigInteger soma = BigInteger.ONE;
		
		//calculo de 2^0 
		if (n.compareTo(BigInteger.ZERO) == 0) return soma;
		
		//calculo de 2^n 
		for(BigInteger i = BigInteger.ONE; i.compareTo(n) != 0; i = i.add(BigInteger.ONE))
			soma = soma.multiply(BigInteger.valueOf(2));
		
		return soma;
	} 

}
