package hard;
import java.util.PriorityQueue;

public class app5 {
            
        // public static ListNode mergeKLists(ListNode[] lists) {
            // if (lists.length==0)return null;
            
            // //Declaration
            // ListNode mergedHead;
            // ListNode mergedTail;
            // PriorityQueue<Integer> pq = new PriorityQueue<>();

            // //Insert into Queue
            // for (ListNode node : lists) {
            //     while (node != null) {
            //         pq.add(node.val);
            //         node = node.next;
            //     }
            // }
    
            // //return if empty or set the head node
            // if (pq.isEmpty()) return null;
            // else mergedHead = new ListNode(pq.poll());
            
            // //start with tail being the head
            // mergedTail = mergedHead;

            // //pop the values from the priority queue and repeat till there is a queue
            // while (!pq.isEmpty()) {
            //     mergedTail.next = new ListNode(pq.poll());
            //     mergedTail = mergedTail.next;
            // }

            // //remove extra node
            // mergedTail.next = null;

            // //return the head
            // return mergedHead;
        
            // ListNode mergedHead=new ListNode();
            // ListNode mergedTail=mergedHead;
            // ListNode PrevTail=mergedTail;

            // ListNode minNode=null;

            // int size=lists.length;
            // int minPos=0;

            // do{
            //     minNode=null;
            //     for(int i=0;i<size;i++){
            //         if(minNode==null){
            //             minNode=lists[i];
            //             minPos=i;
            //         }
            //         else if(lists[i]!=null&&minNode.val>lists[i].val){
            //             minNode=lists[i];
            //             minPos=i;
            //         }
            //     }        
            //     if(minNode!=null) {
            //         PrevTail=mergedTail;
            //         mergedTail.val=minNode.val;
            //         mergedTail.next=new ListNode();
            //         mergedTail=mergedTail.next;
            //         lists[minPos]=lists[minPos].next;
            //     }
            // }while(minNode!=null);
            // if(PrevTail==mergedTail)return null;
            // PrevTail.next=null;
            // return mergedHead;
        // }

        //Merge Sort With Nodes
        public  static ListNode mergeKLists(ListNode[] lists, int left, int right) {
            if (left == right)
                return lists[left];
            int mid = (left + right) / 2;
            return mergeTwoLists(mergeKLists(lists, left, mid), mergeKLists(lists, mid + 1, right));
        }
        
        
        public static ListNode mergeKLists(ListNode[] lists) {
            if (lists.length == 0)
                return null;
            return mergeKLists(lists, 0, lists.length - 1);
        }
        
         public static ListNode mergeTwoLists(ListNode l1, ListNode l2) {
            if (l1 == null || l2 == null)
                return l1 != null ? l1 : l2;
    
            ListNode mergedHead = new ListNode();
            ListNode mergedTail = mergedHead;
    
            while (l1 != null && l2 != null) {
                if (l1.val <= l2.val) {
                    mergedTail.next = l1;
                    l1 = l1.next;
                } else {
                    mergedTail.next = l2;
                    l2 = l2.next;
                }
                mergedTail = mergedTail.next;
            }
    
            mergedTail.next = (l1 != null ? l1 : l2);
    
            return mergedHead.next;
        }
        
        public static void main(String[] args){
            ListNode[] list = new ListNode[3];
            list[0]=new ListNode();
            list[1]=new ListNode();
            list[2]=new ListNode();


            ListNode first = list[0];
            first.next=new ListNode();
            first.val=1;
            first=first.next;
            first.next=new ListNode();
            first.val=4;
            first=first.next;
            first.val=5;

            
            first = list[1];
            first.next=new ListNode();
            first.val=1;
            first=first.next;
            first.next=new ListNode();
            first.val=3;
            first=first.next;
            first.val=4;

            first = list[2];
            first.next=new ListNode();
            first.val=2;
            first=first.next;
            first.val=6;


            ListNode test = mergeKLists(list);
            System.out.println(test);
        }
}
