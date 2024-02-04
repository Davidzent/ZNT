class Square{
   Pixel[][] pixels;
   int length;
   int width;
   
   Square(){
   
   }
   
   void show(){
     for(int i=0;i<length;i++){
       for(int j=0;j<width;j++){
            pixels[i][j].show();
       }
     }
   }
   
   boolean isEqual(Square s){
     for(int i=0;i<length;i++){
       for(int j=0;j<width;j++){
            if(s.pixels[i][j]!=pixels[i][j])return false;
       }
     }
     return true;
   }
   
}
