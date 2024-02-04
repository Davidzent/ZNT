import java.awt.Graphics2D;
import java.util.concurrent.TimeUnit;

import javax.swing.JFrame;

class App{
    public static JFrame frame = new JFrame();
    
    public static void main(String[] args) throws InterruptedException {
      frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
      frame.setLayout(null);
      frame.setSize(1440,750);
      frame.setVisible(true);
      
      Population pop = new Population(1000);
      int squareType = (int)Math.floor(Math.random()*4);
      Square square = types(squareType,0,0,false)[0];
      // square.show();
      Graphics2D g2d = (Graphics2D)frame.getGraphics();
      int guess = 0;
      int currentbest=0;
      int best=currentbest;
      int gen=1;

      do{
        while(!pop.done()){
          g2d.clearRect(0, 0, 1440,750);
          squareType = (int)Math.floor(Math.random()*4);
          square = types(squareType,0,0,false)[0];
          pop.updateAlive(square,squareType,false);
          // drawBrain(pop);
          square.show();
          guess++;
          currentbest=pop.currentBestScore;
          g2d.drawString("Guess "+guess, 10, 200);
          g2d.drawString("Current Best "+currentbest, 10, 220);
          g2d.drawString("Grade %"+(int)((currentbest/(float)guess)*100), 10, 240);
          g2d.drawString("Passing Grade %"+(int)(pop.passingGrade*100), 10, 260);
          g2d.drawString("Best Score "+best, 10, 280);
          g2d.drawString("Generation "+gen, 10, 300);
          g2d.drawString("Players Alive "+pop.cntAlive, 10, 320);




          TimeUnit.MILLISECONDS.sleep(200);

        }
        gen++;
        if(best<currentbest)best=currentbest;
        currentbest=0;
        guess=0;
        pop.naturalSelection();
        System.out.println(0);
      }while(true);


    }

    public static void drawBrain(Player player) {  //show the brain of whatever genome is currently showing
      int startX = 600;
      int startY = 10;
      int w = 600;
      int h = 400;
      player.brain.show(startX, startY, w, h);
      // for (int i = 0; i< pop.pop.size(); i++) {
      //   if (!pop.pop.get(i).dead) {
      //     pop.pop.get(i).brain.show(startX, startY, w, h);
      //     break;
      //   }
      // }
    }

    public static Square[] types(int type,int x,int y, boolean separate){
        Square[] s = new Square[2]; 
        for(int i=0;i<2;i++){
          s[i] = new Square();
          s[i].pixels = new Pixel[2][2];
          s[i].length=2;
          s[i].width=2;
        }
        
        int space = separate?3:0;
        
        
        switch(type){
          case 0://solid
            s[0].pixels[0][0] = new Pixel(x,y,0);
            s[0].pixels[0][1] = new Pixel(x,y+1,0);
            s[0].pixels[1][0] = new Pixel(x+1,y,0);
            s[0].pixels[1][1] = new Pixel(x+1,y+1,0);
            
            s[1].pixels[0][0] = new Pixel(x,y+space,1);
            s[1].pixels[0][1] = new Pixel(x,y+space+1,1);
            s[1].pixels[1][0] = new Pixel(x+1,y+space,1);
            s[1].pixels[1][1] = new Pixel(x+1,y+space+1,1);
            break;
      
          case 1://vertical
            s[0].pixels[0][0] = new Pixel(x,y,1);
            s[0].pixels[0][1] = new Pixel(x,y+1,0);
            s[0].pixels[1][0] = new Pixel(x+1,y,1);
            s[0].pixels[1][1] = new Pixel(x+1,y+1,0);
            
            s[1].pixels[0][0] = new Pixel(x,y+space,0);
            s[1].pixels[0][1] = new Pixel(x,y+space+1,1);
            s[1].pixels[1][0] = new Pixel(x+1,y+space,0);
            s[1].pixels[1][1] = new Pixel(x+1,y+space+1,1);
            break;
            
          case 2://diagonal
            s[0].pixels[0][0] = new Pixel(x,y,1);
            s[0].pixels[0][1] = new Pixel(x,y+1,0);
            s[0].pixels[1][0] = new Pixel(x+1,y,0);
            s[0].pixels[1][1] = new Pixel(x+1,y+1,1);
            
            s[1].pixels[0][0] = new Pixel(x,y+space,0);
            s[1].pixels[0][1] = new Pixel(x,y+space+1,1);
            s[1].pixels[1][0] = new Pixel(x+1,y+space,1);
            s[1].pixels[1][1] = new Pixel(x+1,y+space+1,0);
            break;
            
          case 3://horizontal
            s[0].pixels[0][0] = new Pixel(x,y,1);
            s[0].pixels[0][1] = new Pixel(x,y+1,1);
            s[0].pixels[1][0] = new Pixel(x+1,y,0);
            s[0].pixels[1][1] = new Pixel(x+1,y+1,0);
            
            s[1].pixels[0][0] = new Pixel(x,y+space,0);
            s[1].pixels[0][1] = new Pixel(x,y+space+1,0);
            s[1].pixels[1][0] = new Pixel(x+1,y+space,1);
            s[1].pixels[1][1] = new Pixel(x+1,y+space+1,1);
            break;
        }
        return s;
      }
}