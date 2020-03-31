/* 
 * File:   main.cpp
 * Author: Guijosa, David
 * Created on Nov 08, 2018, 11:00 AM
 * Purpose:  
 */

#include <cstring>
#ifndef NUMBER_H
#define NUMBER_H

using namespace std;
class number{
    private:
        int numbe;
        string lsthn20[20]={"Zero","One ","Two ","Three ","Four ","Five ","Six ",
        "Seven ","Eight ","Nine ","Ten ","Eleven ","Twelve ","thirteen ",
        "Fifteen ","Sixteen ","Nineteen "};
        string thusand="Thousand ";
        string hundred="Hundred ";
        string tens[8]={"twenty ","Thirty ","Forty ","Fifty","Sixty ","Seventy ",
        "Eighty ","Ninety "};
        string name;
    public:
        number(int);
        void prnt();
};


#endif /* NUMBER_H */

