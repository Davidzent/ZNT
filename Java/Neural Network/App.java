

class App{
    public static void main(String[] args) {
        Brain brain = new Brain(4,4);
        LinkedList network = brain.getNetwork().clone();
        System.out.println(network);
    }


}