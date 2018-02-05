//
//  hardware.cpp
//  8085 i
//
//  Created by Parth on 25/10/17.
//  Copyright © 2017 Parth. All rights reserved.
//
struct data
{
    string address;
    int count;
};
class setflags;
class hardware
{
public:
    helpingfunctions hf;
    map <string,string> maps;
    map <string,data> map2;
    map <string,int> traverse;
    map <string,string> :: iterator itrs;
    map <string,data> :: iterator itr2;

    string registr[7];
    bool f[5];
    hardware()
    {
        for(int i=0;i<7;i++)
            registr[i]="00";
    }
    int mapping(string op1,string op2)
    {
        if(hf.checkaddress(op1))//checking address is valid or not
        {
            if(maps.count(op1)) //if key exists or not
                maps.erase(op1);
            maps.insert(pair <string,string> (op1,op2));
            return 1;
        }
        return 0;
    }
    void mapping(string label,string add,int count)
    {
        data ptr;
        ptr.address=add;
        ptr.count=count;
        if(map2.count(label)) //if key exists or not
            map2.erase(label);
        map2.insert(pair <string,data> (label,ptr));
    }
    void mapping(string address,int count)
    {
        if(traverse.count(address)) //if key exists or not
            traverse.erase(address);
        traverse.insert(pair <string,int> (address ,count));
    }

    void showmap(string op1)
    {
        itrs=maps.find(op1);
        cout<<itrs->first<<"-->"<<itrs->second<<endl;
        
    }
    
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
        if(dec==0)
            return "00";
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
    
    
};

class setflags
{
    hardware hw;
public:
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
        int dec=hw.hextodec(op);
        op=hw.dectobin(dec);
        int count=0;
        for(int i=0;i<op.size();i++)
            if(op[i]=='1')
                count++;
        if(count%2==0)
            return 1;
        return 0;
    }
    int auxcarry(string op1,string op2)
    {
        int sum= hw.hextodec(op1)+hw.hextodec(op2);
        if(sum>15)
            return 1;
        return 0;
    }
    int carry(string op)
    {
        if(op.size()>2)
            return 1;
        return 0;
    }

};
