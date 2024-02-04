
Population pop;
int range = 4;
int squareType = floor(random(range));
int rand2 = floor(random(2));
Square square;

int cnt=0;
int bestscore=0;
int maxGuess=100;

boolean showNothing =false;

int nextConnectionNo = 1000;
int frames=1;

void setup(){ 
   size(1400,800);
   frameRate(frames);
   pop = new Population(500); //<<number of dinosaurs in each generation
}


void draw(){
 background(255);
 stroke(0);
 update();

 if (cnt<maxGuess) {//if any players are alive then update them
    pop.updateAlive();
    cnt++;
  } else {//all dead
    //genetic algorithm 
    pop.naturalSelection();
    cnt=0;
  }
  if(bestscore==maxGuess)maxGuess+=10;
  if (!showNothing) {
   square.show();
   drawBrain();
   writeInfo();
  }
}

void keyPressed() {
  switch(key) {
  case '+'://speed up frame rate
    frames += 10;
    frameRate(frames);
    println(frames);
    break;
  case '-'://slow down frame rate
    if (frames > 10) {
      frames -= 10;
      frameRate(frames);
      println(frames);
    }
    break;
  case 'n'://show absolutely nothing in order to speed up computation
    showNothing = !showNothing;
  break;
  }
}

void update(){
  squareType = floor(random(range));
  rand2 = floor(random(2));
  square = types(squareType,0,0,false)[rand2];


}

Square[] types(int type,int x,int y, boolean separate){
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

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void drawBrain() {  //show the brain of whatever genome is currently showing
  int startX = 600;
  int startY = 10;
  int w = 600;
  int h = 400;
  
  for (int i = 0; i< pop.pop.size(); i++) {
    if (!pop.pop.get(i).dead) {
      pop.pop.get(i).brain.drawGenome(startX, startY, w, h);
      break;
    }
  }
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//writes info about the current player
void writeInfo() {
  fill(200);
  textAlign(LEFT);
  textSize(40);
  bestscore=pop.bestScore;
  text("best score: "+pop.currentBestScore,30,height-110);
  text("highest score : "+bestscore,30,height-70);
  text("guess: " + floor(pop.populationLife), 30, height - 30);
  //text(, width/2-180, height-30);
  textAlign(RIGHT);

  text("Gen: " + (pop.gen +1), width -40, height-30);
  textSize(20);
  int x = 580;
  text("Square (0,0)", x, 100);
  text("Square (0,1)", x, 175);
  text("Square (1,0)", x, 255);
  text("Square (1,1)", x, 335);


  textAlign(LEFT);
  text("Fill", 1220, 100);
  text("Vertical", 1220, 175);
  text("Diagonal", 1220, 255);
  text("Horizontal", 1220, 335);

}
