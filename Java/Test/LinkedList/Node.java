/**
 * Node
 */
public class Node {
    int data;

    Node(){

    }

    Node(int a){
        data = a;
    }

    public int getData() {
        return data;
    }

    public void setData(int data) {
        this.data = data;
    }

    @Override
    public String toString() {
        return "data =" + data;
    }

    
}