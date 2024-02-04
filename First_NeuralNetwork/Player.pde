class Player{
  float fitness;
  Genome brain;
  boolean replay = false;
  
  float unadjustedFitness;
  int lifespan = 0;//how long the player lived for fitness
  int bestScore =0;//stores the score achieved used for replay
  boolean dead;
  int guess=0;
  int score=1;
  int gen = 0;

  int genomeInputs = 4;
  int genomeOutputs = range;
  
  float[] vision = new float[genomeInputs];//t he input array fed into the neuralNet 
  float[] decision = new float[genomeOutputs]; //the out put of the NN 
  
  Player(){
    brain = new Genome(genomeInputs, genomeOutputs);
  }
  
  void show(){
    Square[] s = types(guess,3,0,true);
    for(int i=0;i<2;i++){
      s[i].show();
    }
  }
  
  //---------------------------------------------------------------------------------------------------------------------------------------------------------
  //fot Genetic algorithm
  void calculateFitness() {
    fitness = score*score;
  }
  
  void update(int ans){
    if(ans==guess)score++;
  }
  
  void look(){
    int cnt=0;
    for(int i=0;i<square.length;i++){
      for(int j=0;j<square.length;j++){
        vision[cnt++]=square.pixels[i][j].val*2-1;
        //println(vision[cnt-1],cnt-1);
      }
    }
    
  }
  
  void think(){
    float max = 0;
    int maxIndex = 0;
    //get the output of the neural network
    decision = brain.feedForward(vision);

    for (int i = 0; i < decision.length; i++) {
      //println(decision[i],i);
      if (decision[i] > max) {
        max = decision[i];
        maxIndex = i;
      }
    }
    guess=maxIndex;
  }
  
  //---------------------------------------------------------------------------------------------------------------------------------------------------------
  Player crossover(Player parent2) {
    Player child = new Player();
    child.brain = brain.crossover(parent2.brain);
    child.brain.generateNetwork();
    return child;
  }
  
  //---------------------------------------------------------------------------------------------------------------------------------------------------------  
  //returns a clone of this player with the same brian
  Player clone() {
    Player clone = new Player();
    clone.brain = brain.clone();
    clone.fitness = fitness;
    clone.brain.generateNetwork(); 
    clone.gen = gen;
    clone.bestScore = score;
    return clone;
  }

  //---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  //since there is some randomness in games sometimes when we want to replay the game we need to remove that randomness
  //this fuction does that

  Player cloneForReplay() {
    Player clone = new Player();
    clone.brain = brain.clone();
    clone.fitness = fitness;
    clone.brain.generateNetwork();
    clone.gen = gen;
    clone.bestScore = score;
    clone.replay = true;

    return clone;
  }

}
