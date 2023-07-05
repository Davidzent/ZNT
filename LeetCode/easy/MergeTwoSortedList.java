public class MergeTwoSortedList {

    public static ListNode mergeTwoLists(ListNode list1, ListNode list2) {
        if (list1==null || list2==null)return list1!=null?list1:list2;

        ListNode mergedHead=new ListNode();
        ListNode mergedTail=mergedHead;

        while (list1!=null&&list2!=null){
            if (list1.val<=list2.val){
                mergedTail.next=list1;
                list1=list1.next;
            }else{
                mergedTail.next=list2;
                list2=list2.next;
            }
            mergedTail=mergedTail.next;
        }
        mergedTail.next=(list1!=null?list1:list2);

        return mergedHead.next;
    }

    public static void main(String[] args) {
        
    }
}
