public class app {
    public static void main(String[] args) {
        LinkedList a = new LinkedList();

        a.pushBack(1);
        a.pushBack(2);
        a.pushBack(3);
        a.pushBack(4);
        a.pushBack(5);
        a.pushBack(6);
        a.pushBack(7);
        a.pushBack(8);

        //[1,2,3,4,5,6,7,8]

        System.out.println(a);

        Node popBack = a.popBack(); //[8]
        //[1,2,3,4,5,6,7]

        System.out.println(a);

        Node popFront = a.popFront();//[1]
        //[2,3,4,5,6,7]

        System.out.println(a);

        a.pushFront(8);
        //[8,1,2,3,4,5,6,7]

        System.out.println(a);

    }
}
