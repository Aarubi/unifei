import java.util.ArrayList;
import java.util.concurrent.Semaphore;

public class Buffer_Semaforo implements Buffer {
    private Semaphore mutex, cheias, vazias;
    private ArrayList<Object> itens;
    private int N;

    public Buffer_Semaforo(int N) {
        this.N = N;
        mutex = new Semaphore(1, true);
        cheias = new Semaphore(N, true);
        try {
            cheias.acquire(N);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        vazias = new Semaphore(N, true);
        itens = new ArrayList<Object>(N);
    }

    public int quantidade() {
        int qtd = 0;
        try {
            mutex.acquire();
            qtd = itens.size();
        } catch (InterruptedException e) {
            e.printStackTrace();
        } 
            mutex.release();
        
        return qtd;
    }

    public void inserir(Object obj) {
        
        try {
            //System.out.println("Momento antes do sinal");
            vazias.acquire();
            mutex.acquire();
            //System.out.println("Momento antes da inserção "+itens.size());
            // System.out.println("N "+ N);
            if(itens.size() < N -1 ){ 
                itens.add(obj);
                //System.out.println("Item " + obj + " produzido!" + itens.size());
            }
        } catch (InterruptedException e) {
            //e.printStackTrace(); 
            mutex.release();
            cheias.release(N);
            vazias.release(N);
            return;
        }
            
            mutex.release();
            cheias.release();
            
    }


    public Object remover() {
        Object item = null;
        try {
            cheias.acquire();
            mutex.acquire();
            //System.out.println("Entrei ");
            if ( itens.size() > 0 ){
                item = itens.get(0);
                itens.remove(item);
                //System.out.println("Item " + item + " consumido!" + itens.size());
            }
                

        } catch (InterruptedException e) {
            //e.printStackTrace(); 
            mutex.release();
            cheias.release(N);
            vazias.release(N);
            //System.out.println("tu é mano?");
            return null;           
        } 
            mutex.release();
            vazias.release();
            //System.out.println("alou?");
        return item;   
    }

}
