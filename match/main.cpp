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
    const int TEST1_NCRITERIA = 7;
    
    int test1dist[TEST1_NCRITERIA] = {2, 4, 1, 3, 2, 1, 13};
    
    char test1w1[TEST1_NCRITERIA][MAX_WORD_LENGTH+1] = {"", "deranged", "NEFARIOUS", "half-witted", "robot", "plot", "have" };
    
    char test1w2[TEST1_NCRITERIA][MAX_WORD_LENGTH+1] = {"scientist", "robot", "PLOT", "assistant", "deranged", "Nefarious", "mad"};

    
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
    
    
    
    cout<<endl<<" after char check"<<endl;
    
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
    
      
    
    //check words from different arrays now
    //problem

    int i=0;
    int y=1;
    int removew1=0; //counter if it removed word1
    int removew2=0;  //counter if it removed word2
    
    while(i<numRules)
    {
        if(y==numRules)
            break;
        while(y<numRules)
        {
        if((!strcmp(word1[i],word1[y]) || !strcmp(word1[i],word2[y])) && (!strcmp(word2[i],word2[y])|| !strcmp(word2[i],word1[y]))) //if words are equal
        {
            if(distance[i]>=distance[y]) //if distance of word1 rule > distance of word2 rule
            {
                
                //remove word2 rule
                
                int p=y+1;
                for (int k=y; k<numRules; k++)
                {
                    strcpy(word1[k],word1[p]);
                    
                    strcpy(word2[k],word2[p]);
                    p++;
                }
                
                for(int m=y; m<numRules; m++)
                {
                    distance[m]=distance[m+1];
                }
                numRules--;
                removew2=1;
            }else
            {   //remove word1 rule
                int p=i+1;
                for (int k=i; k<numRules; k++)
                {
                    strcpy(word1[k],word1[p]);
                    
                    strcpy(word2[k],word2[p]);
                    p++;
                }
                for(int m=i; m<numRules; m++)
                {
                    distance[m]=distance[m+1];
                }
                numRules--;
                removew1=1;
            }
        }else
            {
                if(y==numRules-1)
                {
                    if(i==numRules-1)
                    {
                        i++;
                        break;
                    }
                    i++;
                    y=i+1;
                    break;
                }
            }
                if(removew1==1)
                {  cout<<endl<<" after remove w1"<<endl;
                    
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
                    break;
                }
                if(removew2==1)
                {
                    cout<<endl<<" after remove w2"<<endl;
                    
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
                    break;
                }
                y++;
            }
        if(removew1==1)
        {
            i=0;
            y=i+1;
            removew1=0;
        }
        else if(removew2==1)
        {
            i++;
            y=i+1;
            removew2=0;
        }
    }
    
    cout<<endl<<" after array check"<<endl;
    
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
    
    cout<<endl<<" after empy string"<<endl;
    
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








