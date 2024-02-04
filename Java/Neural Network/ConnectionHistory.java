import java.util.ArrayList;

public class ConnectionHistory {
  int fromNode;
  int toNode;
  int innovationNumber;

  ArrayList<Integer> innovationNumbers = new ArrayList<Integer>();//the innovation Numbers from the connections of the genome which first had this mutation 
  //this represents the genome and allows us to test if another genoeme is the same
  //this is before this connection was added

  //---------------------------------------------------------------------------------------------------------------------------------------------------------
  //constructor
  ConnectionHistory(int from, int to, int inno, ArrayList<Integer> innovationNos) {
    fromNode = from;
    toNode = to;
    innovationNumber = inno;
    innovationNumbers = (ArrayList<Integer>)innovationNos.clone();
  }
  //---------------------------------------------------------------------------------------------------------------------------------------------------------
  //returns whether the genome matches the original genome and the connection is between the same nodes
  boolean matches(Brain brain, Node from, Node to) {
    if (brain.getConections().size() == innovationNumbers.size()) { //if the number of connections are different then the genoemes aren't the same
      if (from.getID() == fromNode && to.getID() == toNode) {
        //next check if all the innovation numbers match from the genome
        for (int i = 0; i< brain.getConections().size(); i++) {
          if (!innovationNumbers.contains(brain.getConections().get(i).getID())) {
            return false;
          }
        }

        //if reached this far then the innovationNumbers match the genes innovation numbers and the connection is between the same nodes
        //so it does match
        return true;
      }
    }
    return false;
  }
}