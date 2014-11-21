//
//  main.cpp
//  match
//
//  Created by desiree on 11/18/14.
//  Copyright (c) 2014 desiree. All rights reserved.
//

#include <iostream>
#include <cstring>
#include <cctype>
#define _CRT_SECURE_NO_WARNINGS
using namespace std;

const int MAX_WORD_LENGTH=20;

int standardizeRules(int distance[], char word1[][MAX_WORD_LENGTH+1], char word2[][MAX_WORD_LENGTH+1],
                     int nRules);


int determineQuality(const int distance[], const char word1[][MAX_WORD_LENGTH+1],
                     const char word2[][MAX_WORD_LENGTH+1], int nRules, const char document[]);


int main()
{
    const int TEST1_NCRITERIA = 4;
    
    int test1dist[TEST1_NCRITERIA] = {2, 5, 0, 2};
    
    char test1w1[TEST1_NCRITERIA][MAX_WORD_LENGTH+1] = {"afrbop", "afrbrtrt!", "brm", "b!t" };
    
    char test1w2[TEST1_NCRITERIA][MAX_WORD_LENGTH+1] = {"swan", "SEA", "lion", "brm"};

    
    cout<<standardizeRules(test1dist, test1w1, test1w2,TEST1_NCRITERIA);
}


int standardizeRules(int distance[], char word1[][MAX_WORD_LENGTH+1], char word2[][MAX_WORD_LENGTH+1],
                     int nRules)
{
    int numRules=nRules;
    //int interesting=numRules; //only wanna check interesting indexes
    
    //first wanna check if distance is >0
    //if it's not greater than 0, take out that whole rule!
    //strcpy(destination, source);
    //this works
    
    for (int i=0; i<numRules; i++)
    {
        if(distance[i]<=0)
        {
            for(int m=i; m<numRules; m++)
            {
                distance[m]=distance[m+1];
            }
            
            int j=i+1;
            while(j<numRules)
            {
                for (int k=i; k<numRules; k++)
                {
                    strcpy(word1[k],word1[j]);
                    
                    strcpy(word2[k],word2[j]);
                    j++;
                }
            }
            numRules--;
        }
    }
    
    
    
    //check all the word1's and see if any of them are equal
    //this works
    
    int j=1;
    int q=0;
    
    for (int i=0; i<numRules; i++)
    {
        if(q==j)
            break;
        if(!strcmp(word1[q],word1[j]))
        {
            if (distance[q]>=distance[j]) //word1 distance> word2, remove word2
            {
                for(int m=j; m<nRules; m++)
                {
                    distance[m]=distance[m+1];
                }
                
                int m=j+1;
                while(m<nRules)
                {
                    for (int k=j; k<numRules; k++)
                    {
                        strcpy(word1[k],word1[m]);
                        
                        strcpy(word2[k],word2[m]);
                        m++;
                    }
                }
                numRules--;
                
            }else   //word1 distance < word2, remove word1
            {
                for(int m=q; m<numRules; m++)
                {
                    distance[m]=distance[m+1];
                }
                
                int m=i+1;
                while(m<numRules)
                {
                    for (int k=q; k<numRules; k++)
                    {
                        strcpy(word1[k],word1[m]);
                        
                        strcpy(word2[k],word2[m]);
                        m++;
                    }
                }
                numRules--;
            }
        }else
        {
            if(j==numRules-1)
            {
                j=0;
                q++;
            }
            j++;
        }
    }
    
//check all the word2's and see if any of them are equal
//this works
  
    j=1;
    q=0;
    
    for (int i=0; i<numRules; i++)
    {
        if(q==j)
            break;
        if(!strcmp(word2[q],word2[j]))
        {
            if (distance[q]>=distance[j]) //word1 distance> word2, remove word2
            {
                for(int m=j; m<numRules; m++)
                {
                    distance[m]=distance[m+1];
                }
                
                int m=j+1;
                while(m<numRules)
                {
                    for (int k=j; k<numRules; k++)
                    {
                        strcpy(word1[k],word1[m]);
                        
                        strcpy(word2[k],word2[m]);
                        m++;
                    }
                }
                numRules--;
                
            }else   //word1 distance < word2, remove word1
            {
                for(int m=q; m<numRules; m++)
                {
                    distance[m]=distance[m+1];
                }
                
                int m=i+1;
                while(m<numRules)
                {
                    for (int k=q; k<numRules; k++)
                    {
                        strcpy(word1[k],word1[m]);
                        
                        strcpy(word2[k],word2[m]);
                        m++;
                    }
                }
                numRules--;
            }
        }else
        {
            if(j==numRules-1)
            {
                j=0;
                q++;
            }
            j++;
        }
       
    }
    
   
    
    //check words from different arrays now
    //this works

    int i=0;
    int y=0;
    
    while(i<numRules)
    {
        while(y<numRules)
        {
        if(!strcmp(word1[i],word2[y])) //if words are equal
        {
            if(distance[i]>=distance[y]) //if distance of word1 rule > distance of word2 rule
            {
                
                //remove word2 rule
                
                int p=i+1;
                for (int k=i; k<numRules; k++)
                {
                    strcpy(word1[p],word1[p+1]);
                    
                    strcpy(word2[p],word2[p+1]);
                    p++;
                }
                
                for(int m=j; m<numRules; m++)
                {
                    distance[m]=distance[m+1];
                }
                numRules--;
                
            }else
            {   //remove word1 rule
                int p=i+1;
                for (int k=i; k<numRules; k++)
                {
                    strcpy(word1[k],word1[p]);
                    
                    strcpy(word2[k],word2[p]);
                    
                    for(int m=i; m<nRules; m++)
                    {
                        distance[m]=distance[m+1];
                    }
                    
                    p++;
                }
                numRules--;
            }
        }else
            {
                if(y==numRules-1)
                {
                    if(i==numRules-1)
                    {
                        break;
                    }
                    i++;
                    y=0;
                    break;
                }
            }
                y++;
            }
        i++;
        }
    
 
    
    //take out entire rule if word is empty string
    //make sure stuff doesn't go out of index O:!!!
    //this works
    
    
    for(int i=0; i<numRules; i++)
    {
        
        if(!strcmp(word1[i],"")||!strcmp(word2[i],""))
        {
            for(int m=i; m<numRules; m++)
            {
                distance[m]=distance[m+1];
            }
            
            int p=i+1;
            for (int k=i; k<numRules; k++)
            {
                strcpy(word1[k],word1[p]);
                
                strcpy(word2[k],word2[p]);
                p++;
            }
            numRules--;
            i--;
        }
    }
    

    //take out entire rule if word contains a character that is not a letter
    //problematic for words over length of numRules 
    
    int t=0;
    while(t<numRules)
    {
        int j=0;
        while(j<MAX_WORD_LENGTH+1)
        {
            if((word1[t][j]=='\0' || word2[t][j]=='\0')&&(isalpha(word1[t][j]) || isalpha(word2[t][j])))
            {
            
            }else if (word1[t][j]=='\0' && word2[t][j]=='\0')
            {
                break;
            }
            else if(!isalpha(word1[t][j]) || !isalpha(word2[t][j]))
            {
                for(int m=t; m<numRules; m++)
                {
                    distance[m]=distance[m+1];
                }
                
                int p=t+1;
                for (int k=t; k<numRules; k++)
                    {
                        
                        strcpy(word1[k],word1[p]);
                 
                        
                        strcpy(word2[k],word2[p]);
                        p++;
                    }
                numRules--;
                t--;
                break;
            }
            j++;
        }
        t++;
    }
   
    
    
    //now I wanna transform every uppercase letter into lowercase
    //going to go through every element of the 2d array
    
    
    for (int i=0; i<numRules; i++)
    {
        for (int j=0; j<MAX_WORD_LENGTH+1; j++)
        {
            word1[i][j]=tolower(word1[i][j]);
            word2[i][j]=tolower(word2[i][j]);
        }
    }
    
    for(int i=0; i<nRules; i++)
        cout<<distance[i]<<" ";
    cout<< "---> distance"<<endl;
    
    
    for (int i=0; i<nRules; i++)
        cout<<word1[i]<<" ";
    cout<<"---> word1";
    
    cout<<endl;
    
    for(int i=0; i<nRules; i++)
        cout<<word2[i]<<" ";
    cout<<"---> word2"<<endl;
    
    return numRules;
}








