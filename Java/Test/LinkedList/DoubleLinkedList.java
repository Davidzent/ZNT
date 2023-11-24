public class DoubleLinkedList {
    Node node;
    DoubleLinkedList next;
    DoubleLinkedList prev;

    int size(){
        //checamos si el primero esta iniciado si no lo esta entonces tiene el tamaño de 0
        if(node==null){
            return 0;
        }

        int cnt=1;                      //empezamos el contador en 1 ya que el primero esta iniciado
        DoubleLinkedList temp = this;
        
        while (temp.next != null) {     //contamos el numero de veces que ocupamos para llegar al final
            temp = temp.next;
            cnt++;
        }
        return cnt;
    }

    void pushBack(int n) {
        // asignamos el valor de temp como el principio de la DoubleLinkedList
        DoubleLinkedList temp = this;

        // Checamos si el primer valor ya esta asignado
        if (temp.node == null) {
            // Si no esta asignado ponemos el nuevo valor como el principio
            temp.node = new Node(n);
            temp.prev=null;
            return;
        }

        // Vamos nodo a nodo checando si ya esta creado
        while (temp.next != null) {
            temp = temp.next;
        }

        // cuando llegamos al final creamos un nuevo nodo y una coneccion
        temp.next = new DoubleLinkedList();
        temp.next.node = new Node(n);

        temp.next.prev = temp;  //Creas la coneccion hacia atras del nuevo nodo
    }

    void pushFront(int n) {
        DoubleLinkedList temp = new DoubleLinkedList(); //Creas un nuevo espacio para el que solia ser el primer nodo
        temp.node = node;                   //Asignas el nodo que era el primero

        node = new Node(n);                 //Asignas el nodo que ahora ira enfrente a la posicion de enfrente
        DoubleLinkedList temp2 = next;            //Guardas la coneccion de la que solia ser la segunda posicion en un lugar temporal
        next = temp;                        //Asignas el que solia ser el primer nodo a la segunda posicion
        next.next = temp2;                  //Conectas el nuevo espacio del que solia ser el primer nodo con la guarda 
        next.prev = this;                   //Creas la coneccion hacia atras
    }

    Node popBack() {
        // asignamos el valor de temp como el principio de la DoubleLinkedList
        DoubleLinkedList temp = this;

        //checamos si el primer valor es nulo y si lo es regresamos nada
        if (temp.node == null) {
            return null;
        }

        //checamos si el segundo nodo es nulo y si lo es regresamos el primer nodo
        if (temp.next.node == null) {
            return temp.node;
        }

        // Vamos nodo a nodo checando si ya esta creado
        while (temp.next.next != null) {
            temp = temp.next;
        }

        Node poped = temp.next.node;

        temp.next = null;

        return poped;
    }

    Node popFront() {
        Node poped = node;      //sacamos una copia del primer valor para regresar
        node = next.node;       //sobrescribes el primer valor de la Linked List con el segundo
        next = next.next;       //mueves el tercer nodo a la segunda posicion
        return poped;           //regresas la copia del que era el primer nodo
    }

    @Override
    public String toString() {
        return "Head=" + node + "\n" +
                "next=" + next + (next == null ? "\n" : "");
    }

    //

}
