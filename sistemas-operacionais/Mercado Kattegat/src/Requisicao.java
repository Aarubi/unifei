public interface Requisicao {
    public abstract void start();
    public abstract void finalizar();
    public abstract boolean getDone();
    public abstract String getType();
}