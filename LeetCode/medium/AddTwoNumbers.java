package medium;

public class AddTwoNumbers {
    public static ListNode addTwoNumbers(ListNode l1, ListNode l2) {
        ListNode head = recSum(l1,l2,0);
        return head;
    }

    public static ListNode recSum(ListNode l1, ListNode l2,int carry){
        if(l1==null&&l2==null){
            if(carry==1)return new ListNode(carry);
            return null;
        }
        if(l1==null)l1=new ListNode(0);
        if(l2==null)l2=new ListNode(0);

        int nexcarry = (l1.val+l2.val+carry)/10;
        ListNode next = recSum(l1.next,l2.next,nexcarry);
        
        int unit = (l1.val+l2.val+carry)%10;

        ListNode node = new ListNode(unit, next);

        return node;
    }



    public static void main(String[] args) {
        ListNode[] list = new ListNode[3];
            list[0]=new ListNode();
            list[1]=new ListNode();
            list[2]=new ListNode();


            ListNode first = list[0];
            first.val=9;
            first.next=new ListNode();
            first=first.next;
            first.val=9;
            first.next=new ListNode();
            first=first.next;
            first.val=9;
            first.next=new ListNode();
            first=first.next;
            first.val=9;
            first.next=new ListNode();
            first=first.next;
            first.val=9;
            first.next=new ListNode();
            first=first.next;
            first.val=9;
            first.next=new ListNode();
            first=first.next;
            first.val=9;
            


            
            first = list[1];
            first.val=9;
            first.next=new ListNode();
            first=first.next;
            first.val=9;
            first.next=new ListNode();
            first=first.next;
            first.val=9;
            first.next=new ListNode();
            first=first.next;
            first.val=9;

            first = list[2];
            first.next=new ListNode();
            first.val=2;
            first=first.next;
            first.val=6;


            ListNode test = addTwoNumbers(list[0],list[1]);
            System.out.println(test);
    }
}
