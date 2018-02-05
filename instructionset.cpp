//
//  instructionset.cpp
//  8085 i
//
//  Created by Parth on 25/10/17.
//  Copyright © 2017 Parth. All rights reserved.
//

class instructions
{
	setflags flg;
    helpingfunctions hf;
    hardware hw;
public:
    int split(int &r1)
    {
        int r2=r1%10;
        r1=r1/10;
        return r2;
    }
    string split(string &operand)
    {
        string temp="";
        for(int i=0;i<operand.size()/2;i++)
            temp+=operand[i];
        operand.erase(0,operand.size()/2);
        return temp;
    }
	int complement(int dec)
	{
		dec=255-dec;
		return dec;
		
	}
	void show()
	{
		char ch='A';
		cout<<"\tREGISTERS\n";
		for(int i=0;i<6;i++){
			cout<<ch<<"="<<hw.registr[i]<<"\t";
			ch=ch+1;
		}
		cout<<"H="<<hw.registr[6]<<"\t";
		cout<<"\n\tFLAGS\n";
		cout<<"SF="<<hw.f[0]<<"\tZF="<<hw.f[1]<<"\tAC="<<hw.f[2]<<"\tPF="<<hw.f[3]<<"\tCY="<<hw.f[4];
		cout<<"\n\tMEMORY\n";
		for(hw.itrs=hw.maps.begin();hw.itrs!=hw.maps.end();hw.itrs++)
			cout<<hw.itrs->first<<"-->"<<hw.itrs->second<<endl;
	}
	
    int set(string op1,string op2)
    {
        if(hw.mapping(op1, op2))
            return 1;
        return 0;
    }
    void mov(int r1)
    {
        string address="";
        int r2=split(r1);
        if(r2==7)
        {
            address=hw.registr[5]+hw.registr[6];
            hw.itrs=hw.maps.find(address);
            hw.registr[r1]=hw.itrs->second;
        }
        else
            hw.registr[r1]=hw.registr[r2];
    }
    void mvi(int r1,string data)
    {
        hw.registr[r1]=data;
    }
    void lda(string address)
    {
        hw.itrs=hw.maps.find(address);
        hw.registr[0]=hw.itrs->second;
    }
    void sta(string address)
    {
        hw.mapping(address, hw.registr[0]);
    }
    void lxi(string op1,string data)
    {
        string temp=split(data);
        if(op1=="H")
        {
            hw.registr[5]=""+temp;
            hw.registr[6]=""+data;
        }
        else if(op1=="B")
        {
            hw.registr[1]=""+temp;
            hw.registr[2]=""+data;
        }
        else if(op1=="D")
        {
            hw.registr[3]=""+temp;
            hw.registr[4]=""+data;
        }
    }
    
    void lhld(string address)
    {
        hw.registr[6]=hw.maps[address];
        hf.increament(address, address.size()-1, 1);
        hw.registr[5]=hw.maps[address];
    }
    
    void shld(string address)
    {
        hw.mapping(address, hw.registr[6]);
        hf.increament(address, address.size()-1, 1);
        hw.mapping(address, hw.registr[5]);
    }
    
    void stax(string op1)
    {
        string address="";
        if(op1=="H")
        {
            address=hw.registr[5]+hw.registr[6];
            
        }
        else if(op1=="B")
        {
            address=hw.registr[1]+hw.registr[2];
        }
        else if(op1=="D")
        {
            address=hw.registr[3]+hw.registr[4];
        }
        hw.mapping(address, hw.registr[0]);
    }
    
    void xchg()
    {
        string temp;
        temp=hw.registr[3];
        hw.registr[3]=hw.registr[5];
        hw.registr[5]=temp;
        
        temp=hw.registr[4];
        hw.registr[4]=hw.registr[6];
        hw.registr[6]=temp;
    }
    
    void add(int r1)
    {
        int sum;
		string data;
		if(r1==7)
		{
			data=hw.maps[hw.registr[5]+hw.registr[6]];
			sum=hw.hextodec(hw.registr[0])+hw.hextodec(data);
			
		}
		else
		{
			sum=hw.hextodec(hw.registr[0])+hw.hextodec(hw.registr[r1]);
			data=hw.registr[r1];
		}
		split(data);
		split(hw.registr[0]);
		hw.f[2]=flg.auxcarry(hw.registr[0], data);
		hw.registr[0]=hw.dectohex(sum);
		hw.f[4]=flg.carry(hw.registr[0]);
		if(hw.f[4])
			hw.registr[0].erase(0,1);
		hw.f[0]=flg.signflag(hw.registr[0]);
		hw.f[1]=flg.zeroflag(hw.registr[0]);
		hw.f[3]=flg.parityflag(hw.registr[0]);
	}
    void adi(string op)
    {
        int sum;
        sum=(hw.hextodec(hw.registr[0]) +hw.hextodec(op));
        split(hw.registr[0]);
        split(op);
        hw.f[2]=flg.auxcarry(hw.registr[0],op);
        hw.registr[0]=hw.dectohex(sum);
        hw.f[4]=flg.carry(hw.registr[0]);
        if(hw.f[4])
            hw.registr[0].erase(0,1);
        hw.f[0]=flg.signflag(hw.registr[0]);
        hw.f[1]=flg.zeroflag(hw.registr[0]);
        hw.f[3]=flg.parityflag(hw.registr[0]);
    }
    
    void inr(int r1)
    {
        string temp,temp1;
        int sum;
        if(r1==7)
        {
            temp=hw.maps[hw.registr[5]+hw.registr[6]];
            temp1=temp;
            split(temp);
            hw.f[2]=flg.auxcarry(temp, "1");
			sum=hw.hextodec(temp1)+1;
			temp=hw.dectohex(sum);
			if(temp.size()>2)
				temp.erase(0,1);
			hw.mapping(hw.registr[5]+hw.registr[6], temp);
			hw.f[0]=flg.signflag(temp);
			hw.f[1]=flg.zeroflag(temp);
			hw.f[3]=flg.parityflag(temp);
        }
        else
        {
            temp=hw.registr[r1];
            split(temp);
            hw.f[2]=flg.auxcarry(temp, "1");
            sum=hw.hextodec(hw.registr[r1])+1;
			temp=hw.dectohex(sum);
			if(temp.size()>2)
				temp.erase(0,1);
			hw.registr[r1]=temp;
			hw.f[0]=flg.signflag(hw.registr[r1]);
			hw.f[1]=flg.zeroflag(hw.registr[r1]);
			hw.f[3]=flg.parityflag(hw.registr[r1]);
		}
    }
	
	void inx(string op)
	{
		string address,temp;
		int sum;
		if(op=="H")
		{
			address=hw.registr[5]+hw.registr[6];
			if(address=="FFFF")
			{
				address="0000";
				temp=split(address);
			}
			else
			{
				sum=hw.hextodec(address)+1;
				address=hw.dectohex(sum);
				temp=split(address);
			}
			hw.registr[5]=temp;
			hw.registr[6]=address;
		}
		else if(op=="B")
		{
			address=hw.registr[1]+hw.registr[2];
			if(address=="FFFF")
			{
				address="0000";
				temp=split(address);
			}
			else
			{
				sum=hw.hextodec(address)+1;
				address=hw.dectohex(sum);
				temp=split(address);
			}
			hw.registr[1]=temp;
			hw.registr[2]=address;
		}
		else if(op=="D")
		{
			address=hw.registr[3]+hw.registr[4];
			if(address=="FFFF")
			{
				address="0000";
				temp=split(address);
			}
			else
			{
				sum=hw.hextodec(address)+1;
				address=hw.dectohex(sum);
				temp=split(address);
			}
			hw.registr[3]=temp;
			hw.registr[4]=address;
		}
	}
	
	void dad(string op)
	{
		string address,HL;
		int sum;
		HL=hw.registr[5]+hw.registr[6];
		if(op=="H")
		{
			address=hw.registr[5]+hw.registr[6];
			
		}
		else if(op=="B")
		{
			address=hw.registr[1]+hw.registr[2];
		}
		else if(op=="D")
		{
			address=hw.registr[3]+hw.registr[4];
		}
		sum=hw.hextodec(HL)+hw.hextodec(address);
		HL=hw.dectohex(sum);
		if(HL.size()>4)
		{
			HL.erase(0,1);
			hw.f[4]=1;
		}
		else
			hw.f[4]=0;
		address=split(HL);
		hw.registr[5]=address;
		hw.registr[6]=HL;
	}
	
	void sub(int r1)
	{
		string data;
		int diff;
		if(r1==7)
		{
			data=hw.maps[hw.registr[5]+hw.registr[6]];
			diff=hw.hextodec(hw.registr[0])-hw.hextodec(data);
		}
		else
		{
			diff=hw.hextodec(hw.registr[0])-hw.hextodec(hw.registr[r1]);
			data=hw.registr[r1];
		}
		if(diff<0)
		{
			diff=complement(diff*-1)+1;
			hw.f[4]=1;
			hw.f[2]=1;
		}
		else
		{
			hw.f[4]=0;
			hw.f[2]=0;
		}
		data=hw.dectohex(diff);
		hw.registr[0]=data;
		hw.f[0]=flg.signflag(hw.registr[0]);
		hw.f[1]=flg.zeroflag(hw.registr[0]);
		hw.f[3]=flg.parityflag(hw.registr[0]);
	}
	
	void sui(string data)
	{
		int diff=hw.hextodec(hw.registr[0])-hw.hextodec(data);
		if(diff<0)
		{
			diff=complement(diff*-1)+1;
			hw.f[4]=1;
			hw.f[2]=1;
		}
		else
		{
			hw.f[4]=0;
			hw.f[2]=0;
		}
		data=hw.dectohex(diff);
		hw.registr[0]=data;
		hw.f[0]=flg.signflag(hw.registr[0]);
		hw.f[1]=flg.zeroflag(hw.registr[0]);
		hw.f[3]=flg.parityflag(hw.registr[0]);
	}
	
	void dcr(int r1)
	{
		string data;
		int diff;
		if(r1==7)
		{
			data=hw.maps[hw.registr[5]+hw.registr[6]];
			diff=hw.hextodec(data)-1;
			if(diff<0)
			{
				diff=complement(diff*-1)+1;
				hw.f[2]=0;
			}
			data=hw.dectohex(diff);
			hw.mapping(hw.registr[5]+hw.registr[6], data);
		}
		else
		{
			diff=hw.hextodec(hw.registr[r1])-1;
			if(diff<0)
			{
				diff=complement(diff*-1)+1;
				hw.f[2]=0;
			}
			data=hw.dectohex(diff);
			hw.registr[r1]=data;
		}
		hw.f[0]=flg.signflag(data);
		hw.f[1]=flg.zeroflag(data);
		hw.f[3]=flg.parityflag(data);
	}
	
	void dcx(string op)
	{
		string address;
		int diff;
		if(op=="H")
		{
			address=hw.registr[5]+hw.registr[6];
			diff=hw.hextodec(address)-1;
			if(diff<0)
				diff=complement(diff*-1)+1;
			address=hw.dectohex(diff);
			op=split(address);
			hw.registr[5]=op;
			hw.registr[6]=address;
		}
		else if(op=="B")
		{
			address=hw.registr[1]+hw.registr[2];
			diff=hw.hextodec(address)-1;
			if(diff<0)
				diff=complement(diff*-1)+1;
			address=hw.dectohex(diff);
			op=split(address);
			hw.registr[1]=op;
			hw.registr[2]=address;
		}
		else if(op=="D")
		{
			address=hw.registr[3]+hw.registr[4];
			diff=hw.hextodec(address)-1;
			if(diff<0)
				diff=complement(diff*-1)+1;
			address=hw.dectohex(diff);
			op=split(address);
			hw.registr[3]=op;
			hw.registr[4]=address;
		}
	}
	
	void cma()
	{
		int dec=hw.hextodec(hw.registr[0]);
		dec=complement(dec);
		hw.registr[0]=hw.dectohex(dec);
	}
	
	void cmp(int r1)
	{
		string data;
		int diff;
		if(r1==7)
		{
			data=hw.maps[hw.registr[5]+hw.registr[6]];
		}
		else
		{
			data=hw.registr[r1];
		}
		diff=hw.hextodec(hw.registr[0])-hw.hextodec(data);
		if(diff<0)
		{
			diff=complement(diff*-1)+1;
			hw.f[4]=1;
			hw.f[2]=1;
		}
		else
		{
			hw.f[4]=0;
			hw.f[2]=0;
		}
		data=hw.dectohex(diff);
		hw.f[0]=flg.signflag(data);
		hw.f[1]=flg.zeroflag(data);
		hw.f[3]=flg.parityflag(data);
	}
};
