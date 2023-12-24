// Crivo de Eratostenes
public class Crivo implements Runnable {

    private long startTime;
    private long endTime;

    public void crivoSequencial(int n)
    {
        boolean[] primos = new boolean[n + 1];
        for (int i = 2; i <= n; i++)
            primos[i] = true;
        for (int i = 2; i * i <= n; i++)
            if (primos[i])
                for (int j = i * i; j <= n; j += i)
                    primos[j] = false;
        for (int i = 2; i <= n; i++)
            if (primos[i])
                System.out.print(i + " ");
    }

   
    public void run() {
        startTime = System.currentTimeMillis();
        crivoSequencial(100);
        endTime = System.currentTimeMillis();
        System.out.println("Tempo de execução: " + (endTime - startTime) + "ms");
        System.out.println("");
        startTime = System.currentTimeMillis();
    }

    public long getStartTime() {
        return startTime;
    }

    public void setStartTime(long startTime) {
        this.startTime = startTime;
    }
}