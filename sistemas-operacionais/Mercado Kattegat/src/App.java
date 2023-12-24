/*
Gabriel Arthur Teixeira Perpétuo - 2018006170
Arthur Leitão Barbosa 
*/

import java.util.Random;
import java.util.Scanner;
import java.util.ArrayList;

public class App {
   static   int contProd=0;
   static int contCons=0;
    public static void decideRole(ArrayList<Requisicao> requisicoes,int velNum,Buffer estoque,int reqNum){
            Random r = new Random();
            if(r.nextInt(2)==1 && contCons < reqNum-1){
                Comprador comprador = new Comprador (estoque,velNum);
               
                comprador.start();
                requisicoes.add(comprador);
                contCons++;
            }
            else{ 
                Vendedor vendedor = new Vendedor (estoque,velNum);
               
                vendedor.start();
                requisicoes.add(vendedor);
                contProd++;
            }
    }
    public static void main(String[] args) throws Exception {

        System.out.println("Insira o numero máximo de requisições ");
        Scanner input = new Scanner(System.in);
        int rqNum = input.nextInt();

        System.out.println("Insira o tamanho do estoque");
        int stNum = input.nextInt();

        System.out.println("Insira a velocidade");
        int velNum = input.nextInt();
        input.close();

        Buffer estoque = new Buffer_Semaforo(stNum);

        ArrayList<Requisicao> requisicoes = new ArrayList<Requisicao>();
        
        

       

        while(true){

            while(requisicoes.size() < rqNum){
                //decideRole(requisicoes, velNum, estoque);
                //comprador.run();
                decideRole(requisicoes, velNum, estoque, rqNum);
            }
         
            Thread.sleep(500);
            if(requisicoes.size() > 0){ 
                for (Integer i = requisicoes.size()-1;i>=0;i--){   
                        if(requisicoes.get(i).getDone()==true){
                            //System.out.println("thread" + i + "acabou");
                            requisicoes.get(i).finalizar();
                            if(requisicoes.get(i).getType()=="Produtor"){
                                contProd--;
                            }else{
                                contCons--;
                            }
                            requisicoes.remove(requisicoes.get(i));
                        }
                        
                }
                
            }  

            System.out.print("\033[H\033[2J");  
            System.out.flush();  
            
            System.out.println("Tamanho do Buffer:"+ estoque.quantidade());
            System.out.println("Numero de Compradores:" + contCons);
            System.out.println("Numero de Vendedores:" + contProd);
            System.out.println("Numero de Requsições:" + requisicoes.size());
            
            

        }

    }
}

