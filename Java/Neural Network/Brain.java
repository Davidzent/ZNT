import java.util.ArrayList;

public class Brain {
    private final double WeightMutationRate = 0.8;
    private final double ConnectionMutationRate = 0.1;
    private final double NodeMutationRate = 0.2;

    private ArrayList<Connection> connections = new ArrayList<Connection>();
    // private ArrayList<Node> nodes = new ArrayList<Node>();
    private int inputs; // Number of inputs in neural network
    private int outputs; // Number of outputs in neural network
    private int layers = 2; // current number of layers
    private int nextNode = 0; // the next position for a node
    private int biasNodePos; // the current position of a bias node

    private LinkedList network = new LinkedList();

    public Brain(int in, int out) {
        inputs = in;
        outputs = out;

        // create inputs
        for (int i = 0; i < inputs; i++) {
            network.AddOnLayer(new Node(i, 0));
            nextNode++;
        }

        network.AddOnLayer(new Node(nextNode, 0));
        biasNodePos = nextNode;
        nextNode++;

        // create outputs
        for (int i = 0; i < inputs; i++) {
            network.AddOnLayer(new Node(i + inputs, 1));
            nextNode++;
        }
    }

    public Brain(int in, int out, boolean cross) {
        inputs = in;
        outputs = out;
    }

    // public void generateNetwork() {
    //     connectNodes();
    //     network = new LinkedList();
    //     for (int i = 0; i < nodes.size(); i++) {
    //         network.AddOnLayer(nodes.get(i));
    //     }
    //     System.out.println(network);
    // }

    public void connectNodes() {
        network.clearAllConnections();

        for (int i = 0; i < connections.size(); i++) {// for each connection
            connections.get(i).getStart().addConnection(connections.get(i));// add it to node
        }
    }

    public double[] feedForward(double[] inputValues) {
        // set the outputs of the input nodes
        network.setInputsResponse(inputValues);

        network.engageAll();// for each node in the network engage it

        // the outputs are nodes[inputs] to nodes [inputs+outputs-1]
        double[] outs = network.getOutputsResponse(outputs);

        network.resetInputsSum();

        return outs;
    }

    public int getInnovationNumber(ArrayList<ConnectionHistory> innovationHistory, Node from, Node to) {
        boolean isNew = true;
        int connectionInnovationNumber = nextNode;
        for (int i = 0; i < innovationHistory.size(); i++) {// for each previous mutation
            if (innovationHistory.get(i).matches(this, from, to)) {// if match found
                isNew = false;// its not a new mutation
                connectionInnovationNumber = innovationHistory.get(i).innovationNumber; // set the innovation number as
                                                                                        // the innovation number of the
                                                                                        // match
                break;
            }
        }

        if (isNew) {// if the mutation is new then create an arrayList of integers representing the
                    // current state of the genome
            ArrayList<Integer> innoNumbers = new ArrayList<Integer>();
            for (int i = 0; i < connections.size(); i++) {// set the innovation numbers
                innoNumbers.add(connections.get(i).getID());
            }

            // then add this mutation to the innovationHistory
            innovationHistory
                    .add(new ConnectionHistory(from.getID(), to.getID(), connectionInnovationNumber, innoNumbers));
            nextNode++;
        }
        return connectionInnovationNumber;
    }

    public void addConnection(ArrayList<ConnectionHistory> innovationHistory) {
        // cannot add a connection to a fully connected network
        if (network.MaxConnections() == connections.size()) {
            System.out.println("connection failed");
            return;
        }

        // get random nodes
        int random1 = (int) (Math.random() * network.size());
        int random2 = (int) (Math.random() * network.size());
        Node randomNode1 = network.get(random1);
        Node randomNode2 = network.get(random2);

        while (checkNewConnection(randomNode1, randomNode2)) {// while the random nodes are no good
            // get new ones
            random1 = (int) (Math.random() * network.size());
            random2 = (int) (Math.random() * network.size());
            randomNode1 = network.get(random1);
            randomNode2 = network.get(random2);
        }


        if (randomNode1.getLayer() > randomNode2.getLayer()) {// swap if the first random node is after the second
            Node temp;
            temp = randomNode2;
            randomNode2 = randomNode1;
            randomNode1 = temp;
        }

        // get the innovation number of the connection
        // this will be a new number if no identical genome has mutated in the same way
        int connectionInnovationNumber = getInnovationNumber(innovationHistory, randomNode1,randomNode2);
        // add the connection with a random array

        connections.add(new Connection(randomNode1,randomNode2, (Math.random() * 2 - 1),
                connectionInnovationNumber));// changed this so if error here
        connectNodes();
    }

    public boolean checkNewConnection(Node r1, Node r2) {
        if (r1.getLayer() == r2.getLayer())
            return true; // if the nodes are in the same layer
        if (r1.isConnected(r2))
            return true; // if the nodes are already connected

        return false;
    }

    public void addNode(ArrayList<ConnectionHistory> innovationHistory) {
        // pick a random connection to create a node between
        if (connections.size() == 0) {
            addConnection(innovationHistory);
            return;
        }

        Node biasNode = network.get(biasNodePos);
        int randomConnection = (int) (Math.random() * connections.size());

        while (connections.get(randomConnection).getStart() == biasNode && connections.size() != 1) {// dont
                                                                                                                // disconnect
                                                                                                                // bias
            randomConnection = (int) (Math.random() * connections.size());
        }

        Connection temp = connections.get(randomConnection);

        temp.setEnabled(false);// disable it

        int newNodeNo = nextNode;
        Node newNode = new Node(newNodeNo);
        network.AddOnBetweenLayer(newNode);
        nextNode++;

        // add a new connection from the start of the disabled connection to the new
        // node with a weight of 1
        int connectionInno = getInnovationNumber(innovationHistory, temp.getStart(), newNode);
        connections.add(new Connection(temp.getStart(), newNode, 1, connectionInno));

        connectionInno = getInnovationNumber(innovationHistory, newNode, temp.getEnd());
        // add a new connection from the new node to the end of the disconnected
        // connection with a weight the same as the disabled
        connections.add(new Connection(newNode, temp.getEnd(), temp.getWeight(), connectionInno));
        newNode.setLayer(temp.getStart().getLayer() + 1);

        connectionInno = getInnovationNumber(innovationHistory, biasNode, newNode);
        // connect the bias to the new node with a weight of 0
        connections.add(new Connection(biasNode, newNode, 0, connectionInno));

        connectNodes();
    }

    public void mutate(ArrayList<ConnectionHistory> innovationHistory) {
        if (connections.size() == 0) {
            addConnection(innovationHistory);
        }

        double rand = Math.random();
        if (rand < WeightMutationRate) { // 80% of the time mutate weights
            for (int i = 0; i < connections.size(); i++) {
                connections.get(i).mutateWeight();
            }
        }
        // 5% of the time add a new connection
        rand = Math.random();
        if (rand < ConnectionMutationRate) {
            addConnection(innovationHistory);
        }

        // 1% of the time add a node
        rand = Math.random();
        if (rand < NodeMutationRate) {
            addNode(innovationHistory);
        }
    }

    public Brain crossover(Brain parent2) {
        Brain child = new Brain(inputs, outputs, true);
        child.connections.clear();
        child.network=new LinkedList();
        child.layers = layers;
        child.nextNode = nextNode;
        child.biasNodePos = biasNodePos;

        ArrayList<Connection> childConnections = new ArrayList<Connection>();// list of connections to be inherrited
                                                                             // form
                                                                             // the parents
        ArrayList<Boolean> isEnabled = new ArrayList<Boolean>();
        // all inherrited connections
        for (int i = 0; i < connections.size(); i++) {
            boolean setEnabled = true;// is this node in the chlid going to be enabled

            int parent2gene = matchingGene(parent2, connections.get(i).getID());
            if (parent2gene != -1) {// if the connections match
                if (!connections.get(i).isEnabled() || !parent2.connections.get(parent2gene).isEnabled()) {// if either
                                                                                                           // of the
                                                                                                           // matching
                    // connections are disabled

                    if (Math.random() < 0.75) {// 75% of the time disabel the childs gene
                        setEnabled = false;
                    }
                }
                double rand = Math.random();
                // Decide who's connection it will get
                if (rand < 0.5) {
                    childConnections.add(connections.get(i));
                } else {
                    childConnections.add(parent2.connections.get(parent2gene));
                }
            } else {// disjoint or excess gene
                childConnections.add(connections.get(i));
                setEnabled = connections.get(i).isEnabled();
            }
            isEnabled.add(setEnabled);
        }

        // since all excess and disjoint connections are inherrited from the more fit
        // parent
        // (this brain) the childs structure is no different from this parent | with
        // exception of dormant connections being enabled but this wont effect nodes
        // so all the nodes can be inherrited from this parent
        child.network = network.clone();


        // clone all the connections so that they connect the childs new nodes
        for (int i = 0; i < childConnections.size(); i++) {
            child.connections.add(childConnections.get(i).clone());
            child.connections.get(i).setEnabled(isEnabled.get(i));
        }

        child.connectNodes();
        return child;
    }

    public int matchingGene(Brain parent2, int innovationNumber) {
        for (int i = 0; i < parent2.connections.size(); i++) {
            if (parent2.connections.get(i).getID() == innovationNumber) {
                return i;
            }
        }
        return -1; // no matching gene found
    }

    public Brain clone() {
        Brain clone = new Brain(inputs, outputs, true);

        clone.network=network.clone();

        // copy all the connections so that they connect the clone new nodes

        for (int i = 0; i < connections.size(); i++) {// copy genes
            clone.connections.add(connections.get(i).clone());
        }

        clone.layers = layers;
        clone.nextNode = nextNode;
        clone.biasNodePos = biasNodePos;
        clone.connectNodes();

        return clone;
    }

    //Getters and Seters    
    public ArrayList<Connection> getConections() {
        return connections;
    }

    public void setConections(ArrayList<Connection> connections) {
        this.connections = connections;
    }

    public int getInputs() {
        return inputs;
    }

    public void setInputs(int inputs) {
        this.inputs = inputs;
    }

    public int getOutputs() {
        return outputs;
    }

    public void setOutputs(int outputs) {
        this.outputs = outputs;
    }

    public int getLayers() {
        return layers;
    }

    public void setLayers(int layers) {
        this.layers = layers;
    }

    public int getNextNode() {
        return nextNode;
    }

    public void setNextNode(int nextNode) {
        this.nextNode = nextNode;
    }

    public int getbiasNodePos() {
        return biasNodePos;
    }

    public void setbiasNodePos(int biasNodePos) {
        this.biasNodePos = biasNodePos;
    }

    public LinkedList getNetwork() {
        return network;
    }

    public void setNetwork(LinkedList network) {
        this.network = network;
    }

    @Override
    public String toString() {
        return "Brain [WeightMutationRate=" + WeightMutationRate + ", ConnectionMutationRate=" + ConnectionMutationRate
                + ", NodeMutationRate=" + NodeMutationRate + ", \nconnections=" + connections
                + ", \ninputs=" + inputs + ", \noutputs=" + outputs + ", \nlayers=" + layers 
                + ", \nnextNode="+ nextNode
                + ", \nbiasNodePos=" + biasNodePos 
                + ", \nnetwork=" + network + "]";
    }

}