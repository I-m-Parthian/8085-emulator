#include<iostream>
#include<fstream>
#include<map>
#include<cmath>
using namespace std;

int hextodec(string op)
{
    int sum=0,i,j;
    for(i=op.size()-1,j=0;i>=0;i--,j++)
    {
       if(op[i]>=48&&op[i]<=57)
           sum+=(pow(16,j)*(op[i]-48));
        else
            sum+=(pow(16,j)*(op[i]-48-7));
    }
    return sum;
}

string dectohex(int dec)
{
    string sum="",t="";
    while(dec!=0)
    {
        t=to_string(dec%16);
        if(t=="10")
            t="A";
        else if(t=="11")
            t="B";
        else if(t=="12")
            t="C";
        else if(t=="13")
            t="D";
        else if(t=="14")
            t="E";
        else if(t=="15")
            t="F";
        sum=""+t+sum;
        dec=dec/16;
    }
    return sum;
}

string dectobin(int dec)
{
    string bin;
    while(dec!=0)
    {
        bin=""+to_string(dec%2)+bin;
        dec=dec/2;
    }
    return bin;
}

int zeroflag(string op)
{
    if(op=="00")
        return 1;
    else
        return 0;
}

int signflag(string op)
{
    if((op[0]==56||op[0]==57||(op[0]>=65&&op[0]<=70))&&((op[1]>=48&&op[1]<=57)||(op[1]>=65&&op[1]<=70)))
       return 1;
    else
       return 0;
}

int parityflag(string op)
{
    int dec=hextodec(op);
    op=dectobin(dec);
    int count=0;
    for(int i=0;i<op.size();i++)
        if(op[i]=='1')
            count++;
    if(count%2==0)
        return 1;
    return 0;
}

int carryflag(string op)
{
    
}

int add(string op)
{
    string registr="14";
    int sum=hextodec(registr)+hextodec(op);
    
    return sum;
}

int main()
{
    string str="2FFF LOOP:ADD A";
    int pos=str.find(":");
    str=str.substr(pos+1);
    cout<<str<<endl;
    return 0;
}
