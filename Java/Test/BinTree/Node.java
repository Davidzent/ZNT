public class Node {
    int val; // Integral que sera agregada al arbol
    Node left;
    Node right;

    Node(){

    }

    Node(int val){
        this.val=val;
    }

    public int getValor() {
        return val;
    }

    public void setValor(int valor) {
        this.val = valor;
    }

    public Node getLeft() {
        return left;
    }

    public void setLeft(Node left) {
        this.left = left;
    }

    public Node getRight() {
        return right;
    }

    public void setRight(Node right) {
        this.right = right;
    }

    @Override
    public String toString() {
        return "Node [valor=" + val + ", left=" + left + ", right=" + right + "]";
    }

    
}
