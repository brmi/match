//  main.cpp
//  match
//
//  Created by desiree on 11/18/14.
//  Copyright (c) 2014 desiree. All rights reserved.
//
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <cctype>
#include <cassert>

using namespace std;

const int MAX_WORD_LENGTH=20;
const int MAX_WORD_LENGTH_DOC=200;

int standardizeRules(int distance[], char word1[][MAX_WORD_LENGTH+1], char word2[][MAX_WORD_LENGTH+1],
                     int nRules);


int determineQuality(const int distance[], const char word1[][MAX_WORD_LENGTH+1],
                     const char word2[][MAX_WORD_LENGTH+1], int nRules, const char document[]);


int main()
{
    const int TEST1_NCRITERIA = 4;
    int test1dist[TEST1_NCRITERIA] = {
        2,           4,          1,           13
    };
    char test1w1[TEST1_NCRITERIA][MAX_WORD_LENGTH+1] = {
        "mad",       "deranged", "nefarious", "have"
    };
    char test1w2[TEST1_NCRITERIA][MAX_WORD_LENGTH+1] = {
        "scientist", "robot",    "plot",      "mad"
    };
    
    
    assert(determineQuality(test1dist, test1w1, test1w2, TEST1_NCRITERIA,
                            "         mad scientist") == 1);
    
    assert(determineQuality(test1dist, test1w1, test1w2, TEST1_NCRITERIA,
                            "  **  mad scientist") == 1);
    
    assert(determineQuality(test1dist, test1w1, test1w2, TEST1_NCRITERIA,
                            "   ***  **  the mad wonky lemon scientist") == 0);
    assert(determineQuality(test1dist, test1w1, test1w2, TEST1_NCRITERIA,
                           "   ***  **  the mad wonky lemon scientist squeeb") == 0);
    assert(determineQuality(test1dist, test1w1, test1w2, TEST1_NCRITERIA,
                            "   ***  **  the scientist wonky lemon mad squeeb") == 0);
    
    assert(determineQuality(test1dist, test1w1, test1w2, TEST1_NCRITERIA,
                           "   ***  **  the scientist wonky lemon mad have scientist with a nefarious plot mad") == 3 );
    
    assert(determineQuality(test1dist, test1w1, test1w2, TEST1_NCRITERIA,
                            "   ***  **  the scientist wonky lemon mad have scientist with a nefarious plot mad deranged hi hi robot") == 4 );
    
    assert(determineQuality(test1dist, test1w1, test1w2, TEST1_NCRITERIA,
                           "   ***  **  the scientist wonky lemon have mad scientist with a nefarious plot mad") == 3 );
    assert(determineQuality(test1dist, test1w1, test1w2, TEST1_NCRITERIA,
                            "   ***  **  the scientist wonky lemon have mad scientist with a nefarious plot mad***") == 3 );
    
    assert(determineQuality(test1dist, test1w1, test1w2, TEST1_NCRITERIA,
                            "deranged robot deranged deranged robot robot") == 1 );
    
    assert(determineQuality(test1dist, test1w1, test1w2, TEST1_NCRITERIA,
                            "") == 0 );
    
    
    
    
     assert(determineQuality(test1dist, test1w1, test1w2, TEST1_NCRITERIA,
     "The mad UCLA scientist unleashed a deranged evil giant robot.") == 2);
     
    
     
     assert(determineQuality(test1dist, test1w1, test1w2, TEST1_NCRITERIA,
     "mad UCLA scientist unleashed    a deranged robot.") == 2);
     
    
     
    
    assert(determineQuality(test1dist, test1w1, test1w2, TEST1_NCRITERIA,
    "**** 2014 ****") == 0);
    
    
    
    assert(determineQuality(test1dist, test1w1, test1w2, TEST1_NCRITERIA,
                            "  That plot: NEFARIOUS!") == 1);
    
    
    
     assert(determineQuality(test1dist, test1w1, test1w2, TEST1_NCRITERIA,
     "deranged deranged robot deranged robot robot") == 1);
     
    
     
     assert(determineQuality(test1dist, test1w1, test1w2, TEST1_NCRITERIA,
     "Two mad scientists suffer from deranged-robot fever.") == 0);
    
     
    cout << "All tests succeeded" << endl;
    
    
}


int standardizeRules(int distance[], char word1[][MAX_WORD_LENGTH+1], char word2[][MAX_WORD_LENGTH+1],
                     int nRules)
{
    int numRules=nRules;
    //int interesting=numRules; //only wanna check interesting indexes
    
    //first wanna check if distance is >0
    //if it's not greater than 0, take out that whole rule!
    
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
    
    //check words from different arrays now
    
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
            {
                break;
            }
            if(removew2==1)
            {
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
    
    //take out entire rule if word is empty string
    
    
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
    return numRules;
    
}

int determineQuality(const int distance[], const char word1[][MAX_WORD_LENGTH+1],
                     const char word2[][MAX_WORD_LENGTH+1], int nRules, const char document[])
{
    
    char newdoc[MAX_WORD_LENGTH_DOC +1]={0};
    char finalDoc[MAX_WORD_LENGTH_DOC][MAX_WORD_LENGTH_DOC+1]={0}; //put words into this doc
    
    int length=strlen(document);
    
    
    for(int i=0; i<MAX_WORD_LENGTH_DOC+1; i++)
    {
        if(document[i]=='\0')
            break;
        newdoc[i]=document[i];
    }
    
    cerr<<"original"<<endl;
    
    for(int i=0; i<length; i++)
    {
        cerr<<newdoc[i];
    }
    
    //now change elements in array so there are only alphabetic characters and spaces (one space btwn)
    
    int prevSpace=0;
    int t=0;
    int numSpaces=0; //want to keep track of number of spaces. one want one between each word
    while(t<length)
    {
        if(newdoc[t]=='\0')
            break;
        if(t==length)
        {
            break;
        }if(newdoc[0]==' ')
        {
            for(int g=0; g<length; g++)
            {
                newdoc[g]=newdoc[g+1];
                
            }
            t=0;
        }else if (newdoc[t]==' ')
        {
            numSpaces++;
            if(numSpaces>=1 && prevSpace==1)
            {
                for(int g=t; g<length; g++)
                {
                    newdoc[g]=newdoc[g+1];
                    
                }
                //length--;
                numSpaces=1;
                prevSpace=1;
                t--;
            }prevSpace=1;
        }
        else
        {
            prevSpace=0;
        }if(!isalpha(newdoc[t])&& newdoc[t]!=' ')
        {
            if(t==length-1)
                break;
            int p=t+1;
            for (int k=t; k<length; k++)
            {
                newdoc[k]=newdoc[p];
                p++;
            }
            
            t--;
        }
        t++;
    }
    
    
    
    
    //now I wanna transform every uppercase letter into lowercase
    //going to go through every element of the 2d array
    
    
    for (int i=0; i<length; i++)
    {
        newdoc[i]=tolower(newdoc[i]);
        
    }
    
    cerr<<endl;
    cerr<<endl<<"newdoc"<<endl;
    
    for(int i=0; i<length; i++)
    {
        cerr<<newdoc[i];
    }
    
    
    //now want to put words into new array, one word at a time.
    
    
    
    int h=0;        //first wanna ignore any spaces in the beginning
    while(h<length)
    {
        if(newdoc[h]==' ')
            h++;
        else
            break;
    }
    
    
    
    //go through each character, if it gets to a space and the word before was a letter, that is a word.
    //put that word into new 2d array, holding c strings.
    
    int alphaBefore=0; //this variable is to check that the character before is a letter
    
    int row=0;      //row of final doc
    int indexf=0;    //index of final doc
    
    
    h=0;
    
    while(h<length)
    {
        if(newdoc[h]=='\0')
            break;
        if(isalpha(newdoc[h]))
        {
            finalDoc[row][indexf]=newdoc[h];
            indexf++;
            h++;
            alphaBefore=1;
        }else if(alphaBefore==1)
        {
            
            row++;
            indexf=0;
            h++;
        }
    }
    
    cerr<<endl<<endl<<"final doc"<<endl;
    for(int i=0; i<length; i++)
    {
        if(!strcmp(finalDoc[i],""))
            break;
        cerr<<finalDoc[i]<<" ";
    }
    
    cerr<<endl<<endl;
    
    
    //now just compare distances! and look for match rules
    //work with finalDoc
    
    int distancebtwn=0; //distance between w1 and w2
    
    int q=0;    //which rule i'm on
    int i=0;
    int match=0;
    int tempMatch=0;
    
    while(i<=row)
    {
        if(tempMatch>=1)
        {
            i=0;
            tempMatch=0;
        }
        //check if word1 is in doc, if it is, check to see if word2 is distance or less after it
        //w2 appears distance or fewer words before or after w1
        if(!strcmp(word1[q],finalDoc[i]))
        {
            i++;
            distancebtwn++;
            while(q<=row)
            {
                if(i>row)
                    break;
                if(!strcmp(word2[q],finalDoc[i]))
                {
                    if(i==row && distancebtwn>0 && distancebtwn<=distance[q])
                    {
                        match++;
                        tempMatch=1;
                        q++;
                        distancebtwn=0;
                        i=0;
                        break;
                    }else if(distancebtwn>0 && distancebtwn<=distance[q])
                    {
                        match++;
                        tempMatch=1;
                        q++;
                        i++;
                        distancebtwn=0;
                        break;
                    }else
                    {
                        i=0;
                        q++;
                        distancebtwn=0;
                        
                    }
                    
                }else
                {
                    i++;
                    distancebtwn++;
                }
            }
        }else
        {
            i++;
            if(i>row && q!=length)
            {
                i=0;
                q++;
                distancebtwn=0;
            }
        }
    }
    
    
    i=0;
    q=0;
    distancebtwn=0;
    
    if (match==0)
    {
        while (i<=row)
        {
            if (!strcmp(word2[q],finalDoc[i]))
            {
                i++;
                distancebtwn++;
                while(q<=row)
                {
                    if(i>row)
                        break;
                    if(!strcmp(word1[q],finalDoc[i]))
                    {
                        if(distancebtwn>0 && distancebtwn<=distance[q])
                        {
                            match++;
                            q++;
                            i++;
                            distancebtwn=0;
                            break;
                        }else
                        {
                            i=0;
                            q++;
                            distancebtwn=0;
                            
                        }
                    }else
                    {
                        i++;
                        distancebtwn++;
                    }
                }
            }else
            {
                i++;
                if(i>row && q!=length)
                {
                    i=0;
                    q++;
                    distancebtwn=0;
                }
                
            }
        }
    }else
    {
        return match;
    }
    
    return match;
    
}
