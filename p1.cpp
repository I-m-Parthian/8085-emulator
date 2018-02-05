linecount++;
//Detection of label
flag=-1;
flag=line.find(":");
//if label not found
if(flag==-1)
{
    count=hf.wordcount(line);
    if(count==4)
    {
        hf.extractword(line, address, opcode, operand1,operand2);
    }
    else if(count==3)
    {
        hf.extractword(3,line, address, opcode, operand1, operand2);
    }
    else if(count==2)
    {
        hf.extractword(2,line, address, opcode, operand1, operand2);
    }
    else
    {
        cout<<"NOT A VALID INSTRUCTION\n";
        return 0;
    }
}
       
        //if label exist
else
{
    hf.extractword(line, address, label, opcode, operand1,operand2);
        //work on label and execute instruction?????
}
if(opcode=="SET")
{
        // mapping the address
    if(!ins.set(operand1, operand2))
    {
        cout<<"\tERROR IN ADDRESSING"<<endl;
        cout<<"\t***--->"<<line<<endl;
        return 0;
    }
}
else if(opcode=="MOV")
{
    ins.mov(hf.selecthw(operand1, operand2));
}
else if(opcode=="MVI")
{
    ins.mvi(hf.selecthw(operand1, operand2),operand2);
}
else if(opcode=="LDA")
{
    ins.lda(operand1);
}
else if(opcode=="STA")
{
    ins.sta(operand1);
}
else if(opcode=="LXI")
{
    ins.lxi(operand1,operand2);
}
else if(opcode=="LHLD")
{
    ins.lhld(operand1);
}
else if(opcode=="SHLD")
    ins.shld(operand1);
else if(opcode=="STAX")
    ins.stax(operand1);
else if(opcode=="XCHG")
    ins.xchg();
else if(opcode=="ADD")
    ins.add(hf.selecthw(operand1,operand2));
else if(opcode=="ADI")
    ins.adi(operand1);
else if(opcode=="INR")
    ins.inr(hf.selecthw(operand1, operand2));
else if(opcode=="INX")
    ins.inx(operand1);
else if(opcode=="DAD")
    ins.dad(operand1);
else if(opcode=="SUB")
    ins.sub(hf.selecthw(operand1,operand2));
else if(opcode=="SUI")
    ins.sui(operand1);
else if(opcode=="DCR")
    ins.dcr(hf.selecthw(operand1, operand2));
else if(opcode=="DCX")
    ins.dcx(operand1);
else if(opcode=="CMA")
    ins.cma();
else if(opcode=="CMP")
    ins.cmp(hf.selecthw(operand1, operand2));
else if(opcode=="JMP")
{
    if(hws.map2.count(operand1))
    {
        ptr=hws.map2[operand1];
    }
    else if(hws.traverse.count(operand1))
    {
        ptr.count=hws.traverse[operand1];
        ptr.address=operand1;
    }
    if(ptr.count>linecount)
    {
        for(int i=1;i<ptr.count-linecount;i++)//skipping lines
                    getline(source,line);
                linecount=ptr.count-1;
    }
    else
    {
        source.close();
        source.open("initial.txt");
        for(int i=1;i<ptr.count;i++)
        getline(source,line);
        linecount=ptr.count-1;
        }
    }
else if(opcode=="JC")
{
    if(hws.f[4])
    {
        if(hws.map2.count(operand1))
        {
            ptr=hws.map2[operand1];
        }
        else if(hws.traverse.count(operand1))
        {
            ptr.count=hws.traverse[operand1];
            ptr.address=operand1;
        }
        if(ptr.count>linecount)
        {
            for(int i=1;i<ptr.count-linecount;i++)//skipping lines
            getline(source,line);
            linecount=ptr.count-1;
        }
        else
        {
            source.close();
            source.open("initial.txt");
            for(int i=1;i<ptr.count;i++)
            getline(source,line);
            linecount=ptr.count-1;
        }
    }
}
else if(opcode=="JNC")
{
    if(!hws.f[4])
    {
        if(hws.map2.count(operand1))
        {
            ptr=hws.map2[operand1];
        }
        else if(hws.traverse.count(operand1))
        {
            ptr.count=hws.traverse[operand1];
            ptr.address=operand1;
        }
        if(ptr.count>linecount)
        {
            for(int i=1;i<ptr.count-linecount;i++)//skipping lines
            getline(source,line);
            linecount=ptr.count-1;
        }
        else
        {
            source.close();
            source.open("initial.txt");
            for(int i=1;i<ptr.count;i++)
                getline(source,line);
            linecount=ptr.count-1;
        }
    }
}
else if(opcode=="JZ")
{
    if(hws.f[1])
    {
        if(hws.map2.count(operand1))
        {
            ptr=hws.map2[operand1];
        }
        else if(hws.traverse.count(operand1))
        {
            ptr.count=hws.traverse[operand1];
            ptr.address=operand1;
        }
        if(ptr.count>linecount)
        {
            for(int i=1;i<ptr.count-linecount;i++)//skipping lines
            getline(source,line);
            linecount=ptr.count-1;
        }
        else
        {
            source.close();
            source.open("initial.txt");
            for(int i=1;i<ptr.count;i++)
                getline(source,line);
            linecount=ptr.count-1;
        }
    }
}
else if(opcode=="JNZ")
{
    if(!hws.f[1])
    {
        if(hws.map2.count(operand1))
        {
            ptr=hws.map2[operand1];
        }
        else if(hws.traverse.count(operand1))
        {
            ptr.count=hws.traverse[operand1];
            ptr.address=operand1;
        }
        if(ptr.count>linecount)
        {
            for(int i=1;i<ptr.count-linecount;i++)//skipping lines
                getline(source,line);
                linecount=ptr.count-1;
        }
        else
        {
            source.close();
            source.open("initial.txt");
            for(int i=1;i<ptr.count;i++)
                getline(source,line);
            linecount=ptr.count-1;
        }
    }
}
