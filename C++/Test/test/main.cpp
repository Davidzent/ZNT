/*
 * Angel Zambrano
 *
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cmath>

using namespace std;

unsigned int RSHash  (const std::string& str);
unsigned int JSHash  (const std::string& str);
unsigned int PJWHash (const std::string& str);
unsigned int ELFHash (const std::string& str);
unsigned int BKDRHash(const std::string& str);
unsigned int SDBMHash(const std::string& str);
unsigned int DJBHash (const std::string& str);
unsigned int DEKHash (const std::string& str);
unsigned int BPHash  (const std::string& str);
unsigned int FNVHash (const std::string& str);
unsigned int APHash  (const std::string& str);
string* filArray(int, int);



int main(int argc, char** argv) {
    int size = 20;
    string userInput;
    srand(static_cast <unsigned int>(time(0)));
    string key="David";



    string* words = filArray(size, 20);

    vector<vector<string> >filter;


      filter.resize(14);

     filter[RSHash(key)%filter.size()].push_back(key);
     filter[JSHash(key)%filter.size()].push_back(key);

    //
    // for (int i = 0; i < filter.size(); i ++){
    //     cout << i << " ";
    //     for (int j = 0; j < filter[i].size(); j++){
    //         cout << filter[i][j] << " ";
    //     }
    //     cout << endl;
    // }


    filter.clear();
    filter.resize(120);



    for (int i = 0; i < size; i++){
        key = words[i];
        filter[RSHash(key)%(filter.size())].push_back(key);
        filter[JSHash(key)%(filter.size())].push_back(key);
        filter[PJWHash(key)%(filter.size() )].push_back(key);
        filter[ELFHash(key)%(filter.size() )].push_back(key);
        filter[BKDRHash(key)%(filter.size())].push_back(key);
        filter[SDBMHash(key)%(filter.size())].push_back(key);
        filter[DJBHash(key)%(filter.size())].push_back(key);
        filter[DEKHash(key)%(filter.size())].push_back(key);
        filter[BPHash(key)%(filter.size())].push_back(key);
        filter[FNVHash(key)%(filter.size())].push_back(key);
        filter[APHash(key)%(filter.size())].push_back(key);
    }


    for (int i = 0; i < filter.size(); i ++){
        cout << i << " ";
        for (int j = 0; j < filter[i].size(); j++){
            cout << filter[i][j] << " ";
        }
        cout << endl;
    }





    for (int i = 0; i < filter.size(); i ++){
        cout << i << " ";
        for (int j = 0; j < filter[i].size(); j++){
            cout << filter[i][j] << " ";
        }
        cout << endl;
    }

    cout<<exp(-143)<<endl;
    cout << pow(1 - exp(-143), 11) << endl;

    int* row = new int[11];
    int* col = new int[11];


    for (int i = 0; i < 11; i++){
        row[i]= rand()%10;
    }


    // filter[row[i]].size() has one a number greater than or equal to one

    for (int i = 0; i < 11; i++){
      int number = filter[row[i]].size();
      if(number==0){
          col[i]=0;
      }else{
        col[i]=rand()%(number) ;
      }
    }


    cout << "Enter a key:" << endl << endl;
    getline (cin, userInput);
    //cin >> userInput;





    for (int i = 0; i < 11; i++){


      if(!filter[row[i]].empty() && !filter[row[i]][col[i]].empty()) {
        // if (filter[row[i]][col[i]].compare("prprprp")) {
        //   cout << "hiii" << endl;
        // }

        if(row[i] == 0 && to_string(RSHash(userInput)) == filter[row[i]][col[i]]){
	cout << "maybe" << endl;
        }
        else if(row[i] == 1 && to_string(JSHash(userInput)) == filter[row[i]][col[i]]){
            cout << "maybe" << endl;
        }
        else if(row[i] == 2 && to_string(PJWHash(userInput)) == filter[row[i]][col[i]]){
            cout << "maybe" << endl;
        }
        else if(row[i] == 3 && to_string(ELFHash(userInput)) == filter[row[i]][col[i]]){
            cout << "maybe" << endl;
        }
        else if(row[i] == 4 && to_string(BKDRHash(userInput)) == filter[row[i]][col[i]]){
            cout << "maybe" << endl;
        }
        else if(row[i] == 5 && to_string(SDBMHash(userInput)) == filter[row[i]][col[i]]){
            cout << "maybe" << endl;
        }
        else if(row[i] == 6 && to_string(DJBHash(userInput)) == filter[row[i]][col[i]]){
            cout << "maybe" << endl;
        }
        else if(row[i] == 7 && to_string(DJBHash(userInput)) == filter[row[i]][col[i]]){
            cout << "maybe" << endl;
        }
        else if(row[i] == 8 && to_string(BPHash(userInput)) == filter[row[i]][col[i]]){
            cout << "maybe" << endl;
        }
        else if(row[i] == 9 && to_string(FNVHash(userInput)) == filter[row[i]][col[i]]){
            cout << "maybe" << endl;
        }
        else if(row[i] == 10 && to_string(APHash(userInput)) == filter[row[i]][col[i]]){
            cout << "maybe" << endl;
        }
        else{
            cout << "No." << endl;
        }

      }



    }


    delete[]words;
    delete[]row;
    delete[]col;
    return 0;
}

string* filArray(int wNum, int wLength){
    string word;
    char letter;
    string* array = new string[wNum];

    for (int i = 0; i < wNum; i++){
        for (int j = 0; j < wLength; j++){
            letter = rand()%26+'a';
            word+=letter;
        }
        array[i] = word;
        word = "";
    }
    return array;
}

unsigned int RSHash(const std::string& str)
{
   unsigned int b    = 378551;
   unsigned int a    = 63689;
   unsigned int hash = 0;

   for(std::size_t i = 0; i < str.length(); i++)
   {
      hash = hash * a + str[i];
      a    = a * b;
   }

   return hash;
}
/* End Of RS Hash Function */


unsigned int JSHash(const std::string& str)
{
   unsigned int hash = 1315423911;

   for(std::size_t i = 0; i < str.length(); i++)
   {
      hash ^= ((hash << 5) + str[i] + (hash >> 2));
   }

   return hash;
}

/* End Of JS Hash Function */


unsigned int PJWHash(const std::string& str)
{
   unsigned int BitsInUnsignedInt = (unsigned int)(sizeof(unsigned int) * 8);
   unsigned int ThreeQuarters     = (unsigned int)((BitsInUnsignedInt  * 3) / 4);
   unsigned int OneEighth         = (unsigned int)(BitsInUnsignedInt / 8);
   unsigned int HighBits          = (unsigned int)(0xFFFFFFFF) << (BitsInUnsignedInt - OneEighth);
   unsigned int hash              = 0;
   unsigned int test              = 0;

   for(std::size_t i = 0; i < str.length(); i++)
   {
      hash = (hash << OneEighth) + str[i];

      if((test = hash & HighBits)  != 0)
      {
         hash = (( hash ^ (test >> ThreeQuarters)) & (~HighBits));
      }
   }

   return hash;
}
/* End Of  P. J. Weinberger Hash Function */


unsigned int ELFHash(const std::string& str)
{
   unsigned int hash = 0;
   unsigned int x    = 0;

   for(std::size_t i = 0; i < str.length(); i++)
   {
      hash = (hash << 4) + str[i];
      if((x = hash & 0xF0000000L) != 0)
      {
         hash ^= (x >> 24);
      }
      hash &= ~x;
   }

   return hash;
}
/* End Of ELF Hash Function */


unsigned int BKDRHash(const std::string& str)
{
   unsigned int seed = 131; // 31 131 1313 13131 131313 etc..
   unsigned int hash = 0;

   for(std::size_t i = 0; i < str.length(); i++)
   {
      hash = (hash * seed) + str[i];
   }

   return hash;
}
/* End Of BKDR Hash Function */


unsigned int SDBMHash(const std::string& str)
{
   unsigned int hash = 0;

   for(std::size_t i = 0; i < str.length(); i++)
   {
      hash = str[i] + (hash << 6) + (hash << 16) - hash;
   }

   return hash;
}
/* End Of SDBM Hash Function */


unsigned int DJBHash(const std::string& str)
{
   unsigned int hash = 5381;

   for(std::size_t i = 0; i < str.length(); i++)
   {
      hash = ((hash << 5) + hash) + str[i];
   }

   return hash;
}
/* End Of DJB Hash Function */


unsigned int DEKHash(const std::string& str)
{
   unsigned int hash = static_cast<unsigned int>(str.length());

   for(std::size_t i = 0; i < str.length(); i++)
   {
      hash = ((hash << 5) ^ (hash >> 27)) ^ str[i];
   }

   return hash;
}
/* End Of DEK Hash Function */


unsigned int BPHash(const std::string& str)
{
   unsigned int hash = 0;
   for(std::size_t i = 0; i < str.length(); i++)
   {
      hash = hash << 7 ^ str[i];
   }

   return hash;
}
/* End Of BP Hash Function */


unsigned int FNVHash(const std::string& str)
{
   const unsigned int fnv_prime = 0x811C9DC5;
   unsigned int hash = 0;
   for(std::size_t i = 0; i < str.length(); i++)
   {
      hash *= fnv_prime;
      hash ^= str[i];
   }

   return hash;
}
/* End Of FNV Hash Function */


unsigned int APHash(const std::string& str)
{
   unsigned int hash = 0xAAAAAAAA;

   for(std::size_t i = 0; i < str.length(); i++)
   {
      hash ^= ((i & 1) == 0) ? (  (hash <<  7) ^ str[i] * (hash >> 3)) :
                               (~((hash << 11) + (str[i] ^ (hash >> 5))));
   }

   return hash;
}
