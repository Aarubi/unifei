import java.util.Random;

public class Vendedor extends Thread implements Requisicao{
    private Buffer buffer;
    private int velMax;
    private Random random;
    private int qtd = 0;
    private boolean fim = false;
    private boolean done = false;
    private String type = "Produtor";

    public String getType() {
        return this.type;
    }

    public Vendedor(Buffer buffer, int velMax) {
        this.buffer = buffer;
        this.velMax = velMax;
        random = new Random();
    }

    public int produzirItem() {
        int item = ++qtd;
        try {
            Thread.sleep(Math.abs(random.nextInt() % velMax));
            
        } catch (InterruptedException e) {
            // e.printStackTrace();
        }
        

        return item;
    }

    public void finalizar() {
        fim = true;
        interrupt();
    }

    public void run() {

        int item = 0;
        
        while (!fim) {
            item = produzirItem();
            buffer.inserir(item);
            done = true;
        }
    }

    public boolean getDone(){
        return this.done;
    }
}
