//
//  helpingfunctions.cpp
//  8085 i
//
//  Created by Parth on 25/10/17.
//  Copyright © 2017 Parth. All rights reserved.
//

class helpingfunctions
{
    ifstream fin;
public:
    int wordcount(string line)
    {
        int count=0;
        for(int i=0;i<line.size();i++)
        {
            if(line[i+1]==' '||line[i+1]=='\0')
                count++;
        }
        return count;
    }
    
    int checkaddress(string str)
    {
        int f=1;
        if(str.size()>4)
            return 0;
        for(int i=0;i<str.size();i++)
        {
            if((str[i]>=65&&str[i]<=70)||(str[i]>=97&&str[i]<=102)||(str[i]>=48&&str[i]<=57))
            {
                f=1;
            }
            else
            {
                f=0;
                break;
            }
        }
        if(f)
            return 1;
        return 0;
    }
    
    int checkaddress(string &address,string line)
    {
        string temp;
        int pos=-1,j,flag=1,f=0;
        while(line!="")
        {
            if(line.size()<4)
            {
                flag=3;
                break;
            }
            pos=line.find(" ");
            for(j=0;j<pos;j++)
            {
                temp+=line[j];
            }
            if(flag==1)
            {
                for(j=0;j<pos;j++)
                {
                    if(!((temp[j]>=48&&temp[j]<=57)||(temp[j]>=65&&temp[j]<=70)))
                        return 0;
                }
                if(temp=="DAA"||temp=="ADD"||temp=="DAD"||temp=="ADC")
                    flag=2;
                else
                {
                    address=temp;
                    return 1;
                }
                address=temp;
                temp="";
                line.erase(0,pos+1);
            }
            else if(flag==2)
            {
                cout<<"temp:"<<temp<<endl;
                pos=temp.find(":");
                if(pos==-1)
                {
                    f=1 ;
                    break;
                }
                else
                {
                    if(temp=="A"||temp=="B"||temp=="C"||temp=="D"||temp=="E"||temp=="H"||temp=="L")
                    {
                        f=0;
                        break;
                    }
                    f=1;
                    break;
                }
            }
        }
        if(flag==3)
        {
            if(temp=="A"||temp=="B"||temp=="C"||temp=="D"||temp=="E"||temp=="H"||temp=="L")
            {
                f=0;
            }
        }
        if(f)
            return 1;
        return 0;
        
    }

    void touppercase(string &line)
    {
        for(int i=0;i<line.size();i++)
        {
            if(line[i]>=97&&line[i]<=122)
                line[i]=line[i]-32;
        }
    }
    
    string extractword(string line)
    //used to extract a first word of a line
    {
        string temp="";
        for(int i=0;i<line.size();i++)
        {
            if(line[i]==32||line[i]==0){
                break;}
            temp+=line[i];
        }
        return temp;
    }
    
    //general case
    void extractword(string line,string &address,string &opcode,string &operand1,string &operand2)
    {
        string temp="";
        int pos=-1,wc=4;
        for(int i=0;i<line.size();i++)
        {
            if(line[i]==32)
            {
                if(wc==4)
                    address=temp;
                else if(wc==3)
                    opcode=temp;
                else if(wc==2)
                    operand1=temp;
                temp="";
                i++;
                wc--;
            }
            temp+=line[i];
        }
        operand2=temp;
        if(temp.size()<4)
        {
            operand2="";
            pos=temp.find(",");
            if(pos>-1)
            {
                operand1="";
                for(int i=0;i<temp.size();i++)
                {
                    if(temp[i+1]==',')
                        operand1+=temp[i];
                    if(temp[i-1]==',')
                        operand2+=temp[i];
                }
            }
            else
            {
                operand2=temp;
            }
            
        }
        
        if(operand1=="")
        {
            operand1=operand2;
            operand2="";
        }
    }
    
    //if addressing is not done
    void extractword(int count,string line,string &address,string &opcode,string &operand1,string &operand2)
    {
        string temp="";
        int wc=3,pos=-1;
        int flag=0;
        for(int i=0;i<line.size();i++)
        {
            if(line[i]==32)
            {
                if(wc==3)
                    address=temp;
                else if(wc==2)
                    opcode=temp;
                temp="";
                i++;
                wc--;
            }
            temp+=line[i];
        }
        operand1=temp;
        operand2="";
        if(temp.size()<4)
        {
            pos=temp.find(",");
            if(pos>-1)
            {
                operand1="";
                for(int i=0;i<temp.size();i++)
                {
                    if(temp[i+1]==',')
                        operand1+=temp[i];
                    if(temp[i-1]==',')
                        operand2+=temp[i];
                }
            }
            
        }
        if(count==2)
        {
            opcode=operand1;
            operand1="";
            
        }
    }
    
    //if label exists
    void extractword(string line,string &address,string &label,string &opcode,string &operand1,
                     string &operand2)
    {
        string temp="",temp1="";
        int flag=1,pos=-1;
        for(int i=0;i<line.size();i++)
        {
            if(line[i]==32)
            {
                if(flag==1)
                    address=temp;
                else if(flag==2)
                {
                    temp1=temp.substr(temp.find(":")+1);
                    opcode=temp1;
                    temp=temp.erase(temp.find(":"));
                    label=temp;
                }
                flag++;
                temp="";
                i++;
            }
            temp+=line[i];
        }
        operand1=temp;
        operand2="";
        if(temp.size()<4)
        {
            pos=temp.find(",");
            if(pos>-1)
            {
                operand1="";
                for(int i=0;i<temp.size();i++)
                {
                    if(temp[i+1]==',')
                        operand1+=temp[i];
                    if(temp[i-1]==',')
                        operand2+=temp[i];
                }
            }
            
        }
        
    }
    
    void increament(string &addrs,int len,int inc)
    {
        addrs[len]+=inc;
        if(addrs[len]>57&&addrs[len]<65)
        {
            inc=addrs[len]-57;
            addrs[len]=64+inc;
        }
        else if(addrs[len]>70)
        {
            inc=addrs[len]-70;
            addrs[len]=47+inc;
            return increament(addrs, len-1, 1);
        }
        
    }
    
    int increamentaddrs(string &addrs,string line1)
    {
        string str,line;
        int flag=0,len=addrs.size();
        int pos=-1;
        
    up:
        line=extractword(line1);
        fin.open("1BYTE.txt");
        while(fin)
        {
            fin>>str;
            if(str==line)
            {
                increament(addrs,addrs.size()-1,1);
                flag=1;
                break;
            }
        }
        fin.close();
        if(!flag)
        {
            fin.open("2BYTE.txt");
            while(fin)
            {
                fin>>str;
                if(str==line)
                {
                    increament(addrs,addrs.size()-1,2);
                    flag=1;
                    break;
                }
            }
            fin.close();
        }
        if(!flag)
        {
            fin.open("3BYTE.txt");
            while(fin)
            {
                fin>>str;
                if(str==line)
                {
                    increament(addrs,addrs.size()-1,3);
                    flag=1;
                    break;
                }
            }
            fin.close();
        }
        if(!flag)
        {
            if((line=="SET")||(line=="HLT")||(line==""))
                flag=1;
            else
            {
                pos=line1.find(":");
                if(pos>-1)
                {
                    line1=line1.substr(pos+1);
                    goto up;
                }
                flag=0;
            }
        }
        if(flag==1)
            return 1;
        else
        {
            return -1;
        }
    }
    
    int selecthw(string op1,string op2)
    {
        if(op1=="A"&&op2=="A")
            return 0;
        else if(op1=="A"&&op2=="B")
            return 1;
        else if(op1=="A"&&op2=="C")
            return 2;
        else if(op1=="A"&&op2=="D")
            return 3;
        else if(op1=="A"&&op2=="E")
            return 4;
        else if(op1=="A"&&op2=="H")
            return 5;
        else if(op1=="A"&&op2=="L")
            return 6;
        else if(op1=="A"&&op2=="M")
            return 7;
        
        else if(op1=="A"&&op2=="")
            return 0;
        else if(op1=="B"&&op2=="")
            return 1;
        else if(op1=="C"&&op2=="")
            return 2;
        else if(op1=="D"&&op2=="")
            return 3;
        else if(op1=="E"&&op2=="")
            return 4;
        else if(op1=="H"&&op2=="")
            return 5;
        else if(op1=="L"&&op2=="")
            return 6;
        else if(op1=="M"&&op2=="")
            return 7;
        
        else if(op1=="B"&&op2=="A")
            return 10;
        else if(op1=="B"&&op2=="B")
            return 11;
        else if(op1=="B"&&op2=="C")
            return 12;
        else if(op1=="B"&&op2=="D")
            return 13;
        else if(op1=="B"&&op2=="E")
            return 14;
        else if(op1=="B"&&op2=="H")
            return 15;
        else if(op1=="B"&&op2=="L")
            return 16;
        else if(op1=="B"&&op2=="M")
            return 17;
        
        else if(op1=="C"&&op2=="A")
            return 20;
        else if(op1=="C"&&op2=="B")
            return 21;
        else if(op1=="C"&&op2=="C")
            return 22;
        else if(op1=="C"&&op2=="D")
            return 23;
        else if(op1=="C"&&op2=="E")
            return 24;
        else if(op1=="C"&&op2=="H")
            return 25;
        else if(op1=="C"&&op2=="L")
            return 26;
        else if(op1=="C"&&op2=="M")
            return 27;
        
        else if(op1=="D"&&op2=="A")
            return 30;
        else if(op1=="D"&&op2=="B")
            return 31;
        else if(op1=="D"&&op2=="C")
            return 32;
        else if(op1=="D"&&op2=="D")
            return 33;
        else if(op1=="D"&&op2=="E")
            return 34;
        else if(op1=="D"&&op2=="H")
            return 35;
        else if(op1=="D"&&op2=="L")
            return 36;
        else if(op1=="D"&&op2=="M")
            return 37;
        
        else if(op1=="E"&&op2=="A")
            return 40;
        else if(op1=="E"&&op2=="B")
            return 41;
        else if(op1=="E"&&op2=="C")
            return 42;
        else if(op1=="E"&&op2=="D")
            return 43;
        else if(op1=="E"&&op2=="E")
            return 44;
        else if(op1=="E"&&op2=="H")
            return 45;
        else if(op1=="E"&&op2=="L")
            return 46;
        else if(op1=="E"&&op2=="M")
            return 47;
        
        else if(op1=="H"&&op2=="A")
            return 50;
        else if(op1=="H"&&op2=="B")
            return 51;
        else if(op1=="H"&&op2=="C")
            return 52;
        else if(op1=="H"&&op2=="D")
            return 53;
        else if(op1=="H"&&op2=="E")
            return 54;
        else if(op1=="H"&&op2=="H")
            return 55;
        else if(op1=="H"&&op2=="L")
            return 56;
        else if(op1=="H"&&op2=="M")
            return 57;
        
        else if(op1=="L"&&op2=="A")
            return 60;
        else if(op1=="L"&&op2=="B")
            return 61;
        else if(op1=="L"&&op2=="C")
            return 62;
        else if(op1=="L"&&op2=="D")
            return 63;
        else if(op1=="L"&&op2=="E")
            return 64;
        else if(op1=="L"&&op2=="H")
            return 65;
        else if(op1=="L"&&op2=="L")
            return 66;
        else if(op1=="L"&&op2=="M")
            return 67;
        return 0;
    }
};

