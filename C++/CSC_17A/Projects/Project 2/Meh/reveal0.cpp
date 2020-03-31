/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   reveal0.cpp
 * Author: gabriel
 *
 * Created on November 23, 2018, 12:44 PM
 */

#include <cstdlib>

int cntx=x;
    int cnty=y;
    if(x==0){
        cntx=x;
        while(map[y][cntx]=='0'&&cntx<col){
            reveal(y,cntx); 
            cntx++; 
        }
        cntx=x;
        cnty=y;
        while(map[cnty][cntx]=='0'&&cntx<col-1&&cnty<row-1){
            cntx++;
            cnty++;
            reveal(cnty,cntx);  
        }
    }
    if(x==9){
        cntx=x;
        while(map[y][cntx]=='0'&&cntx>=0){
            reveal(y,cntx); 
            cntx--;  
        }
        cntx=x;
        cnty=y;
        while(map[cnty][cntx]=='0'&&cntx>=1&&cnty<row-1){
            cntx--;
            cnty++;
            reveal(cnty,cntx);  
            
        }
    }
    if(x>0&&x<9){
        cntx=x;
        while(map[y][cntx]=='0'&&cntx<col){
            reveal(y,cntx); 
            cntx++; 
        }
        cntx=x;
        while(map[y][cntx]=='0'&&cntx>=0){
            reveal(y,cntx); 
            cntx--;
        }
        cntx=x;
        cnty=y;
        while(map[cnty][cntx]=='0'&&cntx<col-1&&cnty<row-1){
            cntx++;
            cnty++;
            reveal(cnty,cntx);  
        }
        cntx=x;
        cnty=y;
        while(map[cnty][cntx]=='0'&&cntx>=1&&cnty<row-1){
            cntx--;
            cnty++;
            reveal(cntx,cnty);   
        }
    }
    if(y==0){
        cnty=y;
        while(map[cnty][x]=='0'&&cnty<row-1){
            cnty++; 
            reveal(cnty,x); 
        }
    }
    if(y==9){
        cnty=y;
        while(map[cnty][x]=='0'&&cnty>=1){
            cnty--; 
            reveal(cnty,x);  
        } 
    }
    if(y>0&&y<9){
        cnty=y;
        while(map[cnty][x]=='0'&&cnty<row-1){
            cnty++; 
            reveal(cnty,x);     
        } 
        cnty=y;
        while(map[cnty][x]=='0'&&cnty>=1){
            cnty--; 
            reveal(cnty,x);  
        }
        cntx=x;
        cnty=y;
        while(map[cnty][cntx]=='0'&&cntx>=1&&cnty>=1){
            cntx--;
            cnty--;
            reveal(cnty,cntx);  
        }
        cntx=x;
        cnty=y;
        while(map[cnty][cntx]=='0'&&cnty>=1&&cntx<col-1){
            cntx++;
            cnty--;
            reveal(cnty,cntx);   
        }
    }
