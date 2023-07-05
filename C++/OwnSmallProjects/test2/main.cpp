#include <cstdlib>
#include <string>
#include <iostream>
#include <iomanip>
#include <ctime> 
#include <fstream>
using namespace std;

struct playerstats{
    int strength;
    int dexterity;
    int consitition;
    int intellegence;
    int wisdom;
    int charisma;
};

struct player{
    string name;
    string race; 
    int health;
    int defense;
    int weapon;
    int *data;
    playerstats stats;
};

struct playerchar{
    char name[100];
    char race[100]; 
    int health;
    int defense;
    int weapon;
    int strength;
    int dexterity;
    int consitition;
    int intellegence;
    int wisdom;
    int charisma;
};


struct goblin{
    int health;
    int strength;
    int damage;
};

struct zombie{
    int health;
    int strength;
    int damage;
};

struct humwar{
    int health;
    int strength;
    int damage;
};

struct humran{
    int health;
    int strength;
    int damage;
};

player charmake(player);
player gobfight(player, goblin);
player zomfight(player, zombie);
player genstats(player, string);
goblin makegob(goblin);
zombie makezom (zombie);
humwar makewar(humwar);
humran makeran(humran);
player ranfight(player , humran);
player warfight(player , humwar);
void fileToArray(int []);
void charcreate();
void story1();
void story2();
void story3();
void story4();

enum race{Orc, Elf, Human};

int main(int argc, char** argv) {
    //set random seed time
    srand(static_cast<unsigned int>(time(0)));
    int strarry = 0;
    cout<<"Would you like to create multiple characters and store them in files (1 for yes, 2 for no) (Note this does not play the game it is only a character creator that stores the data." << endl;
    cin >> strarry;
    if (strarry == 1){
        charcreate();
    }
    
    else if (strarry == 2){
    //initalize pointers to the structures to dynamically make them
    player *user = new player;
    goblin *gob = new goblin;
    zombie *zom = new zombie;
    humwar *war = new humwar;
    humran *ran = new humran;
    
    //cout basic intro
    cout <<"Welcome to my DND-style game." << endl;
    cout<<"It is played like a normal DND game however instead of dice the program using a random number generator" << endl;
    cout <<"We are going to start with creating your character" << endl;
    
    //direct pointers to the proper function
    *user = charmake(*user);
    *gob = makegob(*gob);
    *zom = makezom(*zom);
    *war = makewar(*war);
    *ran = makeran(*ran);
    gobfight(*user, *gob);
    zomfight(*user, *zom);
    
    //clean up the program
    delete user;
    delete gob;
    delete zom;
    delete war;
    delete ran;
    return 0;
    }
}

player charmake(player user){
    //initalize temp variables 
    int points = 10;
    int choice = 0;
    int racesel;
    string tempwep;
    cin.ignore();
    //get character name and what race they want
    cout <<"What is your characters name?" << endl;
    getline(cin,user.name);
    cout <<"What is your characters race? 0 for Orc, 1 for elf, 2 for human" <<endl;
    cin >> racesel;
    if (racesel != 0 && racesel != 1 && racesel != 2){
        cout <<"Incorrect input please put 0, 1, or 2" << endl;
        cin >> racesel;
    }
    
    if (racesel == Orc){
        user.race = "Orc";
        user.stats.strength = 6;
        user.stats.dexterity = 2;
    }
    
    else if (racesel == Elf){
       user.race = "Elf";
       user.stats.charisma = 5;
       user.stats.consitition = 3;
    }
    
    else if (racesel == Human){
        user.race = "Human";
        user.stats.charisma = 3;
        user.stats.strength = 1;
    }
    
    //introduce skill points
    cout <<"You have 10 extra skill points to put into your skills along side the random roll" << endl;
    cout <<"How many points would you like to put into strength?" << endl;
    cin >>choice;
    
    if (choice > 10 || choice < 0){
        cout <<"Invalid points please enter a number from 0-10";
        cin >> choice;
    }
    
    user.stats.strength += choice;
    points = points - choice;
    
       
    if (points > 0){
    cout <<"How many points would you like to put into dexterity?" << endl;
    cin >>choice;
    user.stats.dexterity += choice;
    points = points - choice;
    }
    
    if (points > 0){
    cout <<"How many points would you like to put into consitition?" << endl;
    cin >>choice;
    user.stats.consitition += choice;
    points = points - choice;
    }
    
    if (points > 0){
    cout <<"How many points would you like to put into intellegence?" << endl;
    cin >>choice;
    user.stats.intellegence += choice;
    points = points - choice;
    }
    
    if (points > 0){
    cout <<"How many points would you like to put into wisdom?" << endl;
    cin >>choice;
    user.stats.wisdom += choice;
    points = points - choice;
    }
    
    if (points > 0){
    cout <<"How many points would you like to put into charisma?" << endl;
    cin >>choice;
    user.stats.charisma += choice;
    points = points - choice;
    }
    
    cin.ignore();
    cout <<"What weapon would you like to use?" << endl;
    cout <<"A Sword, A bow, or A Magic Wand?" << endl;
    getline(cin,tempwep);
    
    if (tempwep != "Sword" && tempwep != "sword" && tempwep != "bow" && tempwep != "Bow" && tempwep != "Magic Wand" && tempwep != "magic wand"){
        cout <<"Invalid choice please choice Sword,Bow, or Magic Wand" << endl;
        getline(cin,tempwep);
    }

    //send data to genstats to randomly add points to their character
    user = genstats(user, tempwep);
    
    //display the characters data
    cout << endl;
    cout <<"Here is your characters stats" << endl;
    cout << user.name << endl;
    cout << user.race << endl;
    cout <<"Your weapon :" << tempwep << endl;
    cout <<"Your Health :" << user.health << endl;
    cout <<"Your Defence :" << user.defense << endl;
    cout << user.stats.charisma <<" Charisma" << endl;
    cout << user.stats.wisdom<<" Wisdom" << endl;
    cout << user.stats.intellegence<<" Intellegence" << endl;
    cout << user.stats.consitition<<" Consitition" << endl;
    cout << user.stats.dexterity<<" Dexterity"  << endl;
    cout << user.stats.strength<<" Strength" << endl;
    
    return user;
}


player genstats(player user, string tempwep){
    //initalize structure variables and randomly generate them
    user.health = 30;
    user.defense = 5;
    user.stats.charisma += ((rand()%10) + 1); 
    user.stats.wisdom +=  ((rand()%10) + 1);
    user.stats.intellegence += ((rand()%10) + 1); 
    user.stats.consitition += ((rand()%10) + 1); 
    user.stats.dexterity += ((rand()%10) + 1); 
    user.stats.strength += ((rand()%10) + 1); 
    
    if (tempwep == "Sword" || tempwep == "sword"){
        user.weapon = 10 + user.stats.strength;
    }
    
    if (tempwep == "bow" || tempwep == "Bow"){
        user.weapon = 15 + user.stats.dexterity;
    }
    
    if (tempwep == "Magic Wand" || tempwep == "magic wand"){
        user.weapon = 7 + user.stats.intellegence;
    }
    
    return user;
}

goblin makegob(goblin gob){
    //set goblins values
    gob.health = 17;
    gob.damage = 2;
    gob.strength = 1;
    return gob;
}

zombie makezom (zombie zom){
    //set zombies values
    zom.health = 30;
    zom.damage = 4;
    zom.strength = 2;
    return zom;
}

humwar makewar(humwar war){
    //set human warriors values
    war.health = 20;
    war.damage = 5;
    war.strength = 3;
    return war;
}

humran makeran(humran ran){
    //set human rangers values
    ran.health = 16;
    ran.damage = 10;
    ran.strength = 4;
    return ran;
}


player gobfight(player user, goblin gob){
    //create temp variable to help loop and store data
    int temp[20];
    int size = 0;
    int hit = 10;
    int point[20];
    int i = 0;
    fstream datafile;
    int roll = 0;
    
    cout << endl;
    cout << endl;
    cout <<"You encounter a goblin and it seems ready to fight" << endl;
    cout <<"You ready your weapon" << endl;
    
    // Begin the do-while loop to do the battle
    do{
        int temphit = 0;
        cout <<"Roll to hit" << endl;
        cin >> roll;
        temphit = ((rand()%20) + 1);
        if (temphit >= hit ){
            cout <<"You hit the goblin" << endl;
            temp[i] = user.weapon;
            gob.health -= user.weapon;
        }
        else if (temphit < hit){
            cout <<"You miss the goblin" << endl;
            temp[i] = 0;
        }
        
        cout << endl;
        temphit = 0;
        cout <<"The goblin attacks" << endl;
        temphit = ((rand()%20) + 1);
        
        if (temphit >= hit + user.defense){
            cout <<"The goblin hits you" << endl;
            user.health -= gob.damage + gob.strength;
        }
        else if (temphit < hit + user.defense){
            cout <<"The goblin misses you" << endl;
        }
        cout << endl;
        cout <<"Your health :" << user.health <<endl;
        cout <<"The goblins health :" << gob.health << endl;
        cout << endl;
        i++;
        size++;
    }
    while(user.health > 0 && gob.health > 0);
    
    //find who has won
    cout <<"The size is " << size << endl;
    if (user.health <= 0){
        cout <<"You died" << endl;
    }
    
    if (gob.health <= 0){
        cout <<"The goblin died" << endl;
        cout <<"You gain some health back from the fight" << endl;
        user.health += 10;
    }
    //transfer the data to the new variables
    user.data = new int[size];
    
    for (int i = 0; i < size; i++){
        user.data[i] = temp[i];
        cout << user.data[i] << endl;
    }
    
    //open and create a new binary file and read into it
    datafile.open("Battledata.dat", ios::out | ios::binary);
    datafile.write(reinterpret_cast<char  *>(temp), sizeof(temp));
    datafile.close();
    
    //send the data to a binary file
    fileToArray(point);
    
    //display the data from the file
    for (int i = 0; i < size; i++){
        cout <<"Here is the damage you did to the goblin :" << point[i] << endl;
    } 
          
    //clean up memory
    delete []user.data;
    return user;
}

void fileToArray(int point[]){
    //create fstream variable to open file
    fstream datafile;
    datafile.open("Battledata.dat", ios::in | ios::binary);
    datafile.read(reinterpret_cast<char  *>(point), 80);
    datafile.close();
    
}



player zomfight(player user, zombie zom){
    //create temp variable to loop and store data
    char bat[20];
    int size = 0;
    int hit = 12;
    int i = 0;
    int roll = 0;
    //set the empty slots of the array to 'a'
    for (int i = 0; i < 20; i++){
        bat[i] = 'a';
    }
    
    cout << endl;
    cout << endl;
    cout <<"You encounter a Zombie" << endl;
    cout <<"You ready your weapon" << endl;
    
    //begin the do-while loop for the fight
    do{
        int temphit = 0;
        cout <<"Roll to hit" << endl;
        cin >> roll;
        temphit = ((rand()%20) + 1);
        
        if (temphit >= hit ){
            cout <<"You hit the Zombie" << endl;
            bat[i] = 'H';
            zom.health -= user.weapon;
        }
        else if (temphit < hit){
            cout <<"You miss the Zombie" << endl;
            bat[i] = 'M'; 
        }
        
        cout << endl;
        temphit = 0;
        cout <<"The Zombie attacks" << endl;
        temphit = ((rand()%20) + 1);
        
        if (temphit >= hit + user.defense){
            cout <<"The Zombie hits you" << endl;
            user.health -= zom.damage + zom.strength;
        }
        else if (temphit < hit + user.defense){
            cout <<"The Zombie misses you" << endl;
        }
        cout << endl;
        cout <<"Your health :" << user.health <<endl;
        cout <<"The Zombies health :" << zom.health << endl;
        cout << endl;
        i++;
        size++;
    }
    while(user.health > 0 && zom.health > 0);
    
    //see who wins
    if (user.health <= 0){
        cout <<"You died" << endl;
    }
    
    if (zom.health <= 0){
        cout <<"The Zombie died" << endl;
        cout <<"You gain some health back from the fight" << endl;
        user.health += 10;
    }
    
    //display data for hits and misses from the fight
    for (int i = 0; i < size; i++){
        cout<<"Here are your hits and misses : " << bat[i] << endl;
    }

    return user;
}

player warfight(player user, humwar war){
    //create temp variable to loop and store data
    char bat[20];
    int size = 0;
    int hit = 14;
    int i = 0;
    int roll = 0;
    //set the empty slots of the array to 'a'
    for (int i = 0; i < 20; i++){
        bat[i] = 'a';
    }
    
    cout << endl;
    cout << endl;
    cout <<"You encounter a Human Warrior" << endl;
    cout <<"You ready your weapon" << endl;
    
    //begin the do-while loop for the fight
    do{
        int temphit = 0;
        cout <<"Roll to hit" << endl;
        cin >> roll;
        temphit = ((rand()%20) + 1);
        
        if (temphit >= hit ){
            cout <<"You hit the Warrior" << endl;
            bat[i] = 'H';
            war.health -= user.weapon;
            
        }
        else if (temphit < hit){
            cout <<"You miss the Warrior" << endl;
            bat[i] = 'M';
            
        }
        
        cout << endl;
        temphit = 0;
        cout <<"The Warrior attacks" << endl;
        temphit = ((rand()%20) + 1);
        
        if (temphit >= hit + user.defense){
            cout <<"The Warrior hits you" << endl;
            user.health -= war.damage + war.strength;
        }
        else if (temphit < hit + user.defense){
            cout <<"The Warrior misses you" << endl;
        }
        cout << endl;
        cout <<"Your health :" << user.health <<endl;
        cout <<"The Zombies health :" << war.health << endl;
        cout << endl;
        i++;
        size++;
    }
    while(user.health > 0 && war.health > 0);
    
    //see who wins
    if (user.health <= 0){
        cout <<"You died" << endl;
    }
    
    if (war.health <= 0){
        cout <<"The Warrior died" << endl;
        cout <<"You gain some health back from the fight" << endl;
        user.health += 10;
    }
    
    //display data for hits and misses from the fight
    for (int i = 0; i < size; i++){
        cout<<"Here are your hits and misses : " << bat[i] << endl;
    }

    return user;
}


player ranfight(player user, humran ran){
    //create temp variable to loop and store data
    char bat[20];
    int size = 0;
    int hit = 12;
    int i = 0;
    int roll = 0;
    //set the empty slots of the array to 'a'
    for (int i = 0; i < 20; i++){
        bat[i] = 'a';
    }
    
    cout << endl;
    cout << endl;
    cout <<"You encounter a Human Ranger" << endl;
    cout <<"You ready your weapon" << endl;
    
    //begin the do-while loop for the fight
    do{
        int temphit = 0;
        cout <<"Roll to hit" << endl;
        cin >> roll;
        temphit = ((rand()%20) + 1);
        
        if (temphit >= hit ){
            cout <<"You hit the Ranger" << endl;
            bat[i] = 'H';
            ran.health -= user.weapon;
        }
        else if (temphit < hit){
            cout <<"You miss the Ranger" << endl;
            bat[i] = 'M';
        }
        
        cout << endl;
        temphit = 0;
        cout <<"The Ranger attacks" << endl;
        temphit = ((rand()%20) + 1);
        
        if (temphit >= hit + user.defense){
            cout <<"The Ranger hits you" << endl;
            user.health -= ran.damage + ran.strength;
        }
        else if (temphit < hit + user.defense){
            cout <<"The Ranger misses you" << endl;
        }
        cout << endl;
        cout <<"Your health :" << user.health <<endl;
        cout <<"The Rangers health :" << ran.health << endl;
        cout << endl;
        i++;
        size++;
    }
    while(user.health > 0 && ran.health > 0);
    
    //see who wins
    if (user.health <= 0){
        cout <<"You died" << endl;
    }
    
    if (ran.health <= 0){
        cout <<"The Ranger died" << endl;
        cout <<"You gain some health back from the fight" << endl;
        user.health += 10;
    }
    
    //display data for hits and misses from the fight
    for (int i = 0; i < size; i++){
        cout<<"Here are your hits and misses : " << bat[i] << endl;
    }

    return user;
}


void story1(){
    
}

void story2(){
    
}

void story3(){
    
}

void story4(){
    
}


void charcreate(){
    ifstream datafile;
    ofstream outfile;
    int size = 0;
    cout <<"How many characters would you like to make?" << endl;
    cin >> size;
    playerchar user[size];
    
    for (int i = 0; i < size; i++){
    
    //initalize temp variables 
    int points = 10;
    int choice = 0;
    string tempwep;

    //get character name and what race they want
    cout <<"What is your characters name?" << endl;
    cin >> user[i].name;
    cout <<"What is your characters race? Orc,elf, or human" <<endl;
    cin >> user[i].race;
    //introduce skill points
    cout <<"You have 10 extra skill points to put into your skills along side the random roll" << endl;
    cout <<"How many points would you like to put into strength?" << endl;
    cin >>choice;
    
    if (choice > 10 || choice < 0){
        cout <<"Invalid points please enter a number from 0-10";
        cin >> choice;
    }
    
    user[i].strength = choice;
    points = points - choice;
    
       
    if (points > 0){
    cout <<"How many points would you like to put into dexterity?" << endl;
    cin >>choice;
    user[i].dexterity = choice;
    points = points - choice;
    }
    
    if (points > 0){
    cout <<"How many points would you like to put into consitition?" << endl;
    cin >>choice;
    user[i].consitition = choice;
    points = points - choice;
    }
    
    if (points > 0){
    cout <<"How many points would you like to put into intellegence?" << endl;
    cin >>choice;
    user[i].intellegence = choice;
    points = points - choice;
    }
    
    if (points > 0){
    cout <<"How many points would you like to put into wisdom?" << endl;
    cin >>choice;
    user[i].wisdom = choice;
    points = points - choice;
    }
    
    if (points > 0){
    cout <<"How many points would you like to put into charisma?" << endl;
    cin >>choice;
    user[i].charisma = choice;
    points = points - choice;
    }
    
    cin.ignore();
    cout <<"What weapon would you like to use?" << endl;
    cout <<"A Sword, A bow, or A Magic Wand?" << endl;
    getline(cin,tempwep);
    
    if (tempwep != "Sword" && tempwep != "sword" && tempwep != "bow" && tempwep != "Bow" && tempwep != "Magic Wand" && tempwep != "magic wand"){
        cout <<"Invalid choice please choice Sword,Bow, or Magic Wand" << endl;
        getline(cin,tempwep);
    }

    //send data to genstats to randomly add points to their character
    user[i].health = 30;
    user[i].defense = 5;
    user[i].charisma = ((rand()%10) + 1); 
    user[i].wisdom =  ((rand()%10) + 1);
    user[i].intellegence = ((rand()%10) + 1); 
    user[i].consitition = ((rand()%10) + 1); 
    user[i].dexterity = ((rand()%10) + 1); 
    user[i].strength = ((rand()%10) + 1); 
    
    if (tempwep == "Sword" || tempwep == "sword"){
        user[i].weapon = 10 + user[i].strength;
    }
    
    if (tempwep == "bow" || tempwep == "Bow"){
        user[i].weapon = 15 + user[i].dexterity;
    }
    
    if (tempwep == "Magic Wand" || tempwep == "magic wand"){
        user[i].weapon = 7 + user[i].intellegence;
    }
    
   
    
    
    outfile.open("Storage.dat", ios::binary);
    outfile.write((char  *)(&user), sizeof(user));
    outfile.close();
  
    datafile.open("Storage.dat", ios::binary);
    datafile.read((char  *)(&user), sizeof(user));
    datafile.close();
    
    
    //display the characters data
    cout << endl;
    cout <<"Here is your characters stats" << endl;
    cout << user[i].name << endl;
    cout << user[i].race << endl;
    cout <<"Your weapon :" << tempwep << endl;
    cout <<"Your Health :" << user[i].health << endl;
    cout <<"Your Defence :" << user[i].defense << endl;
    cout << user[i].charisma <<" Charisma" << endl;
    cout << user[i].wisdom<<" Wisdom" << endl;
    cout << user[i].intellegence<<" Intellegence" << endl;
    cout << user[i].consitition<<" Consitition" << endl;
    cout << user[i].dexterity<<" Dexterity"  << endl;
    cout << user[i].strength<<" Strength" << endl;
    } 
}