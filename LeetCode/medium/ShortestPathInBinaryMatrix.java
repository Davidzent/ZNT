package medium;

import java.util.LinkedList;
import java.util.Queue;

class Path{
    int value;
    String s;
    public Path(int value, String s) {
        this.value = value;
        this.s = s;
    }
}


public class ShortestPathInBinaryMatrix {
    public static int shortestPathBinaryMatrix(int[][] grid) {
        int n = grid.length;
        if (grid[0][0] == 1 || grid[n - 1][n - 1] == 1) {
            return -1;
        }

        Queue<int[]> queue = new LinkedList<>();
        queue.offer(new int[]{0, 0, 1});
        grid[0][0] = 1;

        int[][] directions = {
            {-1, -1}, {-1, 0}, {-1, 1},
            {0, -1},           {0, 1},
            {1, -1},  {1, 0},  {1, 1}
        };

        while (!queue.isEmpty()) {
            int[] current = queue.poll();
            int row = current[0];
            int col = current[1];
            int distance = current[2];

            if (row == n - 1 && col == n - 1) {
                return distance;
            }

            for (int[] direction : directions) {
                int newRow = row + direction[0];
                int newCol = col + direction[1];

                if (newRow >= 0 && newRow < n && newCol >= 0 && newCol < n && grid[newRow][newCol] == 0) {
                    grid[newRow][newCol] = 1;
                    queue.offer(new int[]{newRow, newCol, distance + 1});
                }
            }
        }

        return -1;
        
        // final int MAXVALUE = 100*100;
        // int p = RecShortestPath(grid, 0, 0,MAXVALUE,0);
        // return p>=(MAXVALUE)?-1:p;
    }

    public static int RecShortestPath(int[][]grid,int y,int x, int currentMin,int currentPath){
        final int MAXVALUE = 100*100;
        if(x==grid.length||x<0)return MAXVALUE;
        if(y==grid[x].length||y<0)return MAXVALUE;
        if(grid[x][y]==1)return MAXVALUE;
        if(x==grid.length-1&&y==x){
            return 1;
        }
        if(currentMin==currentPath)return MAXVALUE;
        
        int min=currentMin;

        grid[x][y]=1;

        int br = RecShortestPath(grid,y+1,x+1,min,currentPath+1)+1;     //down right
        min=min>br?br:min;

        int bl = RecShortestPath(grid,y+1,x-1,min,currentPath+1)+1;     //down left
        min=min>bl?bl:min;

        int b = RecShortestPath(grid,y+1,x,min,currentPath+1)+1;        //down
        min=min>b?b:min;

        int ul = RecShortestPath(grid, y-1, x-1,min,currentPath+1)+1;   //up left
        min=min>ul?ul:min;

        int ur = RecShortestPath(grid, y-1, x+1,min,currentPath+1)+1;   //up right
        min=min>ur?ur:min;

        int r = RecShortestPath(grid,y,x+1,min,currentPath+1)+1;        //right
        min=min>r?r:min;

        int u = RecShortestPath(grid,y-1,x,min,currentPath+1)+1;        //up
        min=min>u?u:min;

        int l = RecShortestPath(grid,y,x-1,min,currentPath+1)+1;        //left
        min=min>l?l:min;

        grid[x][y]=0;
        
        return min;
    }

    public static void main(String[] args) {
        int[][] test = {{0,1,0,1,0},
                        {1,0,0,0,1},
                        {0,0,1,1,1},
                        {0,0,0,0,0},
                        {1,0,1,0,0}};
        
        int[][] test1 = {{0,1,0,0,0,0},
                        {0,1,0,1,1,0},
                        {0,1,1,0,1,0},
                        {0,0,0,0,1,0},
                        {1,1,1,1,1,0},
                        {1,1,1,1,1,0}};

        int[][] test2 = {{0,0,0,0,0,0,0,0},
                        {0,0,1,0,0,0,0,1},
                        {1,0,0,0,0,0,0,0},
                        {0,0,0,0,0,1,1,0},
                        {0,0,1,0,1,0,1,1},
                        {0,0,0,0,0,0,0,0},
                        {0,0,0,1,1,1,0,0},
                        {1,0,1,1,1,0,0,0}};

        int[][] test3 = {
                        {0,0,0,0,1,1,1,1},
                        {1,1,0,1,1,1,1,1},
                        {1,1,0,1,0,0,0,0},
                        {0,0,0,0,1,1,1,0},
                        {1,1,1,1,1,0,1,0},
                        {0,0,0,0,0,0,0,0},
                        {0,0,0,1,1,1,0,0},
                        {1,0,1,1,1,0,0,0}};

        //[[0,1,0,1,0],[1,0,0,0,1],[0,0,1,1,1],[0,0,0,0,0],[1,0,1,0,0]]
        int ans = shortestPathBinaryMatrix(test);
        System.out.println(ans);

        ans = shortestPathBinaryMatrix(test2);
        System.out.println(ans);

        ans = shortestPathBinaryMatrix(test1);
        System.out.println(ans);

        ans = shortestPathBinaryMatrix(test3);
        System.out.println(ans);
    }
}
