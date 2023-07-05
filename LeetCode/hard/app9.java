package hard;
import java.util.Stack;

public class app9 { 
        public static int largestRectangleArea(int[] heights) {
            if (heights==null||heights.length==0)return 0;

            Stack<Integer> stack = new Stack<Integer>();
            int max = 0;
            int i = 0;
            while (i < heights.length){
                System.out.println("Start: "+stack);
                //push index to stack when the current height is larger than the previous one
                if (stack.isEmpty() || heights[i] >= heights[stack.peek()]){
                    stack.push(i);
                    i++;
                }
                else{
                    //calculate max value when the current height is less than the previous one
                    int p = stack.pop();
                    int h = heights[p];
                    int w = stack.isEmpty() ? i : i - stack.peek() - 1;
                    max = Math.max(h * w, max);
                }
                System.out.println("End: "+stack);
            }
            System.out.println(stack);
            while (!stack.isEmpty()){
                int p = stack.pop();
                int h = heights[p];
                int w = stack.isEmpty() ? i : i - stack.peek() - 1;
                max = Math.max(h * w, max);
            }

            return max;
        }

        public static void main(String[] args){
            int[] arr = {2,1,5,6,2,3};
            System.out.println(largestRectangleArea(arr));
        }
}


