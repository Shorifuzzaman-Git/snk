#include<bits/stdc++.h>
using namespace std;
void substring(char text[100],int position,int length)
{
    for(int i=position; i<position+length; i++)
    {
        cout<<text[i];
    }
    cout<<endl;
}

void deleting(char text[100],int position, int length)
{
    int l=strlen(text);
    if(position+length>l)
    {
        cout<<"Invalid position and length."<<endl;
        exit(0);
    }
    for(int i=position+length;i<=l;i++)
    {
        text[i-length]=text[i];
    }
    cout<<text;
    cout<<endl;
}

void inserting(char text[100],int position,char pattern[50])
{
    int x=strlen(text);
    int y=strlen(pattern);
    for(int i=x+y;i>=position;i--)
    {
        text[i]=text[i-y];
    }
    for(int i=0;i<y;i++)
    {
        text[i+position]=pattern[i];
    }
    cout<<text;
}

void indexing(char text[100],char pattern[50])
{
    int x=strlen(text);
    int y=strlen(pattern),i,j;
    for(i=0;i<=x;i++)
    {
        for(j=0;j<y;j++)
        {
            if(pattern[j]!=text[i+j-1])break;
        }
        if(j==y)
        {
            cout<<"pattern is found at index number :"<<i<<endl;
            break;
        }
    }
}
int main()
{
    char text[100],pattern[50];
    int position,length;
    gets(text);
    gets(pattern);
    //cin>>position;
    indexing(text,pattern);
}

