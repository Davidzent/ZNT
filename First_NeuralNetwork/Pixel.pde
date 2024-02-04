class Pixel{
  float val;
  int posx;
  int posy;
  final int scale =75;
  final int size = 1*scale;
  
  Pixel(int x, int y,float v){
    posx = x;
    posy = y;
    val = v;
  }
  
  void show(){
    fill(255*val);
    //System.out.println(val*2-1);
    rect(posx*scale,posy*scale,size,size);
  }
}
