public class BinTree {
    Node root;


    public BinTree() {
    }

    public BinTree(int root) {
        this.root = new Node(root);
    }

    public void insert(int val){
        root = RecInsert(root,val);

    }

    // Funcion para agragar el algoritmo de los nodos
    // basicamente si el valor que se quiere agragar es menor a la taiz entonses va
    // a la izquiera y si es mayo a la deracha
    private Node RecInsert(Node root,int val) {
        if(root == null){
            root = new  Node(val);
            return root;
        }

        if (val < root.val) {            
            root.left = RecInsert(root.left,val);

        } else {
           root.right = RecInsert(root.right,val);
        }

        return root;
    }

    @Override
    public String toString() {
        return "BinTree [root=" + root + "]";
    }


    

    // public void dispararPreorden(){
    //     this.preorden(this.inicial);
    // }
    
    // public void preorden(Node nodo){
    //     if(nodo==null) {
    //         return;
    //     }
    //     else{
    //         System.out.print(nodo.getValor()+", ");
    //         preorden(nodo.getNodoIzq());
    //         preorden(nodo.getNodoDer());
            
    //     }
    // }
    /*
    public void dipararBusMin(){
        this.busMin(this.inicial);
    }
    */
/* 
    public void busMin(nodoArbol inicial){
        if (inicial == null) {
            return;
        }
        else if (inicial.getNodoIzq() != null) {
            System.out.print(inicial.getValor());
            busMin(inicial.getNodoIzq());
            
        }
        else {
            System.out.print(inicial.getValor());
        }
    }
    */
    
    
}
