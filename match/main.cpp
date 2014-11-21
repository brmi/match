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
    
    int test1dist[TEST1_NCRITERIA] = {2, 1, 3, 2};
    
    char test1w1[TEST1_NCRITERIA][MAX_WORD_LENGTH+1] = {"dog", "bat", "brm", "bat" };
    
    char test1w2[TEST1_NCRITERIA][MAX_WORD_LENGTH+1] = {"lion", "sea", "lion", "rate"};

    
    cout<<standardizeRules(test1dist, test1w1, test1w2,TEST1_NCRITERIA);
}


int standardizeRules(int distance[], char word1[][MAX_WORD_LENGTH+1], char word2[][MAX_WORD_LENGTH+1],
                     int nRules)
{
    int numRules=nRules;
    //first wanna check if distance is >0
    //if it's not greater than 0, take out that whole rule!
    //strcpy(destination, source);
    //this works
    
    for (int i=0; i<nRules; i++)
    {
        if(distance[i]<=0)
        {
            numRules--;
            for(int m=i; m<nRules; m++)
            {
                distance[m]=distance[m+1];
            }
            
            int j=i+1;
            while(j<nRules)
            {
                for (int k=i; k<nRules; k++)
                {
                    strcpy(word1[k],word1[j]);
                    
                    strcpy(word2[k],word2[j]);
                    j++;
                }
            }
        }
    }
    
    //check all the word1's and see if any of them are equal
    //this works
    
    for (int i=0; i<nRules; i++)
    {
        int j=1;
        if(!strcmp(word1[i],word1[j]))
        {
            if (distance[i]>distance[j]) //word1 distance> word2, remove word2
            {
                for(int m=j; m<nRules; m++)
                {
                    distance[m]=distance[m+1];
                }
                
                int m=j+1;
                while(m<nRules)
                {
                    for (int k=j; k<nRules; k++)
                    {
                        strcpy(word1[k],word1[m]);
                        
                        strcpy(word2[k],word2[m]);
                        m++;
                    }
                }
                
            }else   //word1 distance < word2, remove word1
            {
                for(int m=i; m<nRules; m++)
                {
                    distance[m]=distance[m+1];
                }
                
                int m=i+1;
                while(m<nRules)
                {
                    for (int k=i; k<nRules; k++)
                    {
                        strcpy(word1[k],word1[m]);
                        
                        strcpy(word2[k],word2[m]);
                        m++;
                    }
                }
            }
        }else
        {
            if(j==nRules-1)
            {
                j=0;
                i++;
            }
            j++;
        }
    }

//check all the word2's and see if any of them are equal

    for (int i=0; i<nRules; i++)
    {
        int j=1;
        if(!strcmp(word2[i],word2[j]))
        {
            if (distance[i]>distance[j]) //word1 distance> word2, remove word2
            {
                for(int m=j; m<nRules; m++)
                {
                    distance[m]=distance[m+1];
                }
                
                int m=j+1;
                while(m<nRules)
                {
                    for (int k=j; k<nRules; k++)
                    {
                        strcpy(word1[k],word1[m]);
                        
                        strcpy(word2[k],word2[m]);
                        m++;
                    }
                }
                
            }else   //word1 distance < word2, remove word1
            {
                for(int m=i; m<nRules; m++)
                {
                    distance[m]=distance[m+1];
                }
                
                int m=i+1;
                while(m<nRules)
                {
                    for (int k=i; k<nRules; k++)
                    {
                        strcpy(word1[k],word1[m]);
                        
                        strcpy(word2[k],word2[m]);
                        m++;
                    }
                }
            }
        }else
        {
            if(j==nRules-1)
            {
                j=0;
                i++;
            }
            j++;
        }
       
    }
    for(int i=0; i<nRules; i++)
        cout<<distance[i]<<" ";
    cout<< " --> distance";
    
    cout<<endl;
    
    for (int i=0; i<nRules; i++)
        cout<<word1[i]<<" ";
    cout<<" --> word1";
    
    cout<<endl;
    
    for(int i=0; i<nRules; i++)
        cout<<word2[i]<<" ";
    cout<<"---> word2"<<endl;
     return 0;
}



 /*
                int j=i+1;
                while(j<nRules)
                {
                    for (int k=i; k<nRules; k++)
                    {
                        strcpy(word1[k],word1[j]);
  
                        strcpy(word2[k],word2[j]);
                        j++;
                    }
            }
        }
           return numRules;
    }

 /*
    //if two rules have the same w1 & w2 values, in either order, remove rule whose distance is less.
    //if same distance remove one
    
    
    
    int i=0;
    while(i<nRules)
    {
        int j=0;
        while(j<nRules)
        {
        if(!strcmp(word1[i],word2[j])) //if words are equal
        {
            if(distance[i]>distance[j]) //if distance of word1 rule > distance of word2 rule
            {
                int p=i+1;  //remove word2 rule
                for (int k=i; k<nRules; k++)
                {
                    strcpy(word1[k],word1[p]);
                    
                    strcpy(word2[k],word2[p]);
                    p++;
                }
            }else
            {
                int p=i+1;
                for (int k=i; k<nRules; k++)
                {
                    strcpy(word1[k],word1[p]);
                    
                    strcpy(word2[k],word2[p]);
                    
                    for(int m=i; m<nRules; m++)
                    {
                        distance[m]=distance[m+1];
                    }
                    
                    p++;
                }
            }
        }else
            {
                if(j==nRules-1)
                {
                    i++;
                    j=0;
                }else if(i==nRules-1)
                    {
                        i=0;
                        //compare all the word1's
                        
                        for(int word=0; word<nRules; word++)
                        {
                            for(int nxtword=1; nxtword<nRules; nxtword++)
                            {
                                if(!strcmp(word1[word],word2[nxtword]))
                                {
                                    if(distance[word]>distance[nxtword]) //if distance of word1 rule > distance of word2 rule
                                    {
                                        int p=word+1;
                                        for (int k=word; k<nRules; k++)
                                        {
                                            strcpy(word1[k],word1[p]);
                                            
                                            strcpy(word2[k],word2[p]);
                                            p++;
                                        }
                                    }else
                                    {
                                        int p=nxtword+1;
                                        for (int k=nxtword; k<nRules; k++)
                                        {
                                            strcpy(word1[k],word1[p]);
                                            
                                            strcpy(word2[k],word2[p]);
                                            p++;
                                        }
                                    }
                                }
                            }
                        }
                        
                        //compare all the word2's
                        
                        for(int word=0; word<nRules; word++)
                        {
                            for(int nxtword=1; nxtword<nRules; nxtword++)
                            {
                                if(!strcmp(word2[word],word2[nxtword]))
                                {
                                    if(distance[word]>distance[nxtword]) //if distance of word1 rule > rule2
                                    {
                                        int p=word+1;
                                        for (int k=word; k<nRules; k++)
                                        {
                                            strcpy(word1[k],word1[p]);
                                            
                                            strcpy(word2[k],word2[p]);
                                            p++;
                                        }
                                    }else
                                    {
                                        int p=nxtword+1;
                                        for (int k=nxtword; k<nRules; k++)
                                        {
                                            strcpy(word1[k],word1[p]);
                                            
                                            strcpy(word2[k],word2[p]);
                                            p++;
                                        }
                                    }
                                }
                            }
                        }
                        
                    }
                }
            }
            j++;
        }
    

    //take out entire rule if word is empty string
    
    
    for(int i=0; i<nRules; i++)
    {
        
        if(!strcmp(word1[i],"")||!strcmp(word2[i],""))
        {
            numRules--;
            for(int m=i; m<nRules; m++)
            {
                distance[m]=distance[m+1];
            }
            
            int p=i+1;
            for (int k=i; k<nRules; k++)
            {
                strcpy(word1[k],word1[p]);
                
                strcpy(word2[k],word2[p]);
                p++;
            }
            i--;
        }
    }

    cout<<numRules<<" numrules empty string"<<endl;
    
    for(int i=0; i<nRules; i++)
        cout<<distance[i]<<" ";
    cout<< " --> distance";
    
    cout<<endl;
    
    for (int i=0; i<nRules; i++)
        cout<<word1[i]<<" ";
    cout<<" --> word1";
    
    cout<<endl;
    
    for(int i=0; i<nRules; i++)
        cout<<word2[i]<<" ";
    cout<<"---> word2"<<endl;
    
    return numRules;
}


    //take out entire rule if word contains a character that is not a letter
    
    for(int i=0; i<nRules; i++)
    {
        for(int j=0; j<MAX_WORD_LENGTH+1; j++)
        {
            if(word1[i][j]=='\0')
                break;
            
            if(!isalpha(word1[i][j]) || !isalpha(word2[i][j]))
            {
                numRules--;
                for(int m=i; m<nRules; m++)
                {
                    distance[m]=distance[m+1];
                }
                
                for(int i=0; i<nRules; i++)
                    cout<<distance[i]<<" ";
                cout<< " distance1";
                
                int p=i+1;
                for (int k=i; k<nRules; k++)
                    {
                        strcpy(word1[k],word1[p]);
                        
                        strcpy(word2[k],word2[p]);
                        p++;
                    }
                break;
            }
        }
    }
    
    cout<<numRules<<" number of rules after checking if it's all letters."<<endl;
    
    for(int i=0; i<nRules; i++)
        cout<<distance[i]<<" ";
    cout<< " --> distance";
    
    cout<<endl;
    
    for (int i=0; i<nRules; i++)
        cout<<word1[i]<<" ";
    cout<<" --> word1";
    
    cout<<endl;
    
    for(int i=0; i<nRules; i++)
        cout<<word2[i]<<" ";
    cout<<"---> word2"<<endl;
    

    //now I wanna transform every uppercase letter into lowercase
    //going to go through every element of the 2d array
    
    
    for (int i=0; i<nRules; i++)
    {
        for (int j=0; j<MAX_WORD_LENGTH+1; j++)
        {
            word1[i][j]=tolower(word1[i][j]);
            word2[i][j]=tolower(word2[i][j]);
        }
    }

    return numRules;
}
*/







