import java.util.Random;

public class Comprador extends Thread implements Requisicao{
    private Buffer buffer;
    private int velMax;
    private Random random;
    private boolean fim = false;
    private boolean done = false;
    private String type = "Consumidor";

    public Comprador(Buffer buffer, int velMax) {
        this.buffer = buffer;
        this.velMax = velMax;
        random = new Random();
    }

    public void consumirItem(int item) {
        try {
            Thread.sleep(Math.abs(random.nextInt() % velMax));
        } catch (InterruptedException e) {
            //e.printStackTrace();
        }
    }


    public void finalizar() {
        fim = true;
        interrupt();
    }

    public void run() {
        Object obj;
        int item = 0;

        while (!fim) {
            obj = buffer.remover();
            if (obj != null) {
                item = (int)obj;
                consumirItem(item);
                done = true;
                //finalizar();
            }    
        }
    }

    public boolean getDone(){
        return this.done;
    }

    public String getType() {
        return this.type;
    }
}
