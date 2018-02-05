//
//  main.cpp
//  8085 i
//
//  Created by Parth on 25/10/17.
//  Copyright © 2017 Parth. All rights reserved.
//

#include "header.cpp"
#include "helpingfunctions.cpp"
#include "hardware.cpp"
#include "instructionset.cpp"


int main(int argc,char *argv[])
{
    helpingfunctions hf;
    instructions ins;
    hardware hws;
    data ptr;
    //argv;
    //argc=2;
    cout<<"\t8085 Emulator\n";
    int debug=0,totline;
    int flag=-1,count=0;
    int linecount=0,flag1;
    char ch;
    string G_address;
    string address,opcode;
    string operand1,operand2,label;
    ofstream outfile;
    ifstream source;
    string line="",fname;
    
    // with no assembly program file name
    if(argc==1)
    {
        while(1)
        {
            cout<<"Enter starting address of the program :";
            cin>>address;
            if(hf.checkaddress(address))
                break;
            else
                cout<<"\tinput address is out of bound\n";
        }
        //to convert address into uppercase;
        
        for(int i=address.size();i>=0;i--)
        {
            if(address[i]>=97&&address[i]<=102)
                address[i]=address[i]-32;
        }
        outfile.open("prog.txt");
        cout<<"Input Instructions and then press Esc key to execute\n";
        
        cout<<setfill('0')<<setw(4)<<address<<" ";
        outfile<<setfill('0')<<setw(4)<<address<<" ";
        cin.ignore();
        while((ch=cin.get())!=27)
        {
            if(ch!='\n')
            {
                line=line+ch;
            }
            else
            {
                hf.touppercase(line); //uppercase conversion
                flag=hf.increamentaddrs(address,line); //increamenting address
                if(flag==1)
                {
                    outfile<<line<<ch<<setfill('0')<<setw(4)<<address<<" ";
                    cout<<setfill('0')<<setw(4)<<address<<" ";
                    //cout<<"yes\n";
                }
                else
                    cout<<setfill('0')<<setw(4)<<address<<" ";
                line="";
            }
        }
        outfile.close();
        source.open("prog.txt");
        //for the purpose of mapping
        linecount=0;
        getline(source,line);
        while(source)
        {
            linecount++;
            address=hf.extractword(line);
            hws.mapping(address, linecount);
            flag=-1;
            flag=line.find(":");
            if(flag!=-1)
            {
                hf.extractword(line, address, label, opcode, operand1,operand2);
                hws.mapping(label, address,linecount);
            }
            getline(source,line);
        }
        totline=linecount;
        source.close();
        fname="prog.txt";
    }
    //END OF ARGC1
    
    
    //with a asm program file
    else if(argc==2)
    {
    argc2:
        flag=0;
        fname=argv[1];
       // fname="srx.txt"; //make changes at last
        source.open(fname);
        outfile.open("initial.txt");
        if(source.fail())
        {
            cout<<"\tFILE Does Not Exist\n";
            return -1;
        }
        else
        {
            int value=0;
            char ch='N';
            linecount=0;
            getline(source,line);
            while(source)
            {
                linecount++;
                hf.touppercase(line);
                G_address=hf.extractword(line);
                //if addressing is given
                if(hf.checkaddress(G_address,line))
                {
                    if(flag==0)
                    {
                        address=G_address;
                        flag=1;
                    }
                    //writting address with line in file and remove G_address
                    line.erase(0,line.find(" ")+1);
                    outfile<<setfill('0')<<setw(4)<<address<<" "<<line<<endl;
                    hws.mapping(address, linecount);
                    value=hf.increamentaddrs(address, line);
                    if(value==-1)
                    {
                        cout<<"Not a recognised opcode\n";
                        cout<<"****-->"<<line<<endl;
                        return 0;
                    }//if Not a recognised opcode ?
                }
                //if addressing is not given
                else
                {
                    if(flag==0&&debug==0)
                    {
                        cout<<"Addressing is not given :\n";
                        cout<<"Please enter starting address of the program :";
                        cin>>address;
                        flag=1;
                        ch='Y';
                    }
                    else if(flag==0&&debug==1)
                    {
                        address="0000";
                        flag=1;
                        ch='Y';
                    }
                    outfile<<setfill('0')<<setw(4)<<address<<" "<<line<<endl;
                    hws.mapping(address, linecount);
                    hf.increamentaddrs(address, line);
                    //if Not a recognised opcode ?
                }
                flag1=-1;
                flag1=line.find(":");
                if(flag1!=-1)
                {
                    if(ch=='Y')
                        line=address+" "+line;
                    hf.extractword(line, address, label, opcode, operand1,operand2);
                    hws.mapping(label, address,linecount);
                    ptr=hws.map2[label];
                }
                getline(source,line);
            }   //end of while loop
            source.close();
            outfile.close();
            totline=linecount;
        }
        fname="initial.txt";
        cout<<"\t\tYour program is :\n";
        source.open(fname);
        getline(source,line);
        while(source)
        {
            cout<<line<<endl;
            getline(source,line);
        }
        source.close();
        if(debug==1)
            goto argc3;
    }
    // END of argc2
    
    else if(argc==3)
    {
        debug=1;
        goto argc2;
    argc3:
        int brk[20],n = 0;
        linecount=1;
        cout<<"\t\t\tDEBUGGER MODE:ON\n";
        cout<<"\tDEBUGGER MENU\n";
        cout<<"b: To add break point\n";
        cout<<"r: To run the program\n";
        cout<<"s: To execute one by one\n";
        cout<<"p: To print values\n";
        cout<<"q: To turn OFF DEBUGGER\n";
        cout<<"h: to see menu\n";
        cout<<"\tPress key to continue:";
        while((ch=cin.get())!='q')
        {
            if(ch=='h')
            {
                cout<<"\t\t\tDEBUGGER MODE:ON\n";
                cout<<"\tDEBUGGER MENU\n";
                cout<<"b: To add break point\n";
                cout<<"r: To run the program\n";
                cout<<"s: To execute one by one\n";
                cout<<"p: To print values\n";
                cout<<"q: To turn OFF DEBUGGER\n";
                cout<<"h: to see menu\n";
                cout<<"\tPress key to continue:";
            }
            else if(ch=='s')
            {
                source.open(fname);
                for(int i=1;i<linecount;i++)
                getline(source,line);
                getline(source,line);
                linecount++;
                cout<<line<<endl;
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
                        linecount=ptr.count;
                    }
                    else
                    {
                        source.close();
                        source.open("initial.txt");
                        for(int i=1;i<ptr.count;i++)
                            getline(source,line);
                        linecount=ptr.count;
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
                            linecount=ptr.count;
                        }
                        else
                        {
                            source.close();
                            source.open("initial.txt");
                            for(int i=1;i<ptr.count;i++)
                                getline(source,line);
                            linecount=ptr.count;
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
                            linecount=ptr.count;
                        }
                        else
                        {
                            source.close();
                            source.open("initial.txt");
                            for(int i=1;i<ptr.count;i++)
                                getline(source,line);
                            linecount=ptr.count;
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
                            linecount=ptr.count;
                        }
                        else
                        {
                            source.close();
                            source.open("initial.txt");
                            for(int i=1;i<ptr.count;i++)
                                getline(source,line);
                            linecount=ptr.count;
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
                            linecount=ptr.count;
                        }
                        else
                        {
                            source.close();
                            source.open("initial.txt");
                            for(int i=1;i<ptr.count;i++)
                                getline(source,line);
                            linecount=ptr.count;
                        }
                    }
                }
                source.close();
                ins.show();
                cout<<"\n\tDEBUGGER MENU\n";
                cout<<"b: To add break point\n";
                cout<<"r: To run the program\n";
                cout<<"s: To execute one by one\n";
                cout<<"p: To print values\n";
                cout<<"q: To turn OFF DEBUGGER\n";
                cout<<"h: to see menu\n";
                cout<<"\tPress key to continue:";
            }
            else if(ch=='p')
            {
                ins.show();
                cout<<"\n\tDEBUGGER MENU\n";
                cout<<"b: To add break point\n";
                cout<<"r: To run the program\n";
                cout<<"s: To execute one by one\n";
                cout<<"p: To print values\n";
                cout<<"q: To turn OFF DEBUGGER\n";
                cout<<"h: to see menu\n";
                cout<<"\tPress key to continue:";
                debug=0;
            }
            else if(ch=='b')
            {
                cout<<"Enter no of break points:";
                cin>>n;
                cout<<"Enter line numbers";
                for(int i=0;i<n;i++)
                    cin>>brk[i];
                for(int i=0;i<n-1;i++)
                    for(int j=0;j<n-i-1;j++)
                        if(brk[j]>brk[j+1])
                            swap(brk[j],brk[j+1]);
                cout<<"r: To run the program\n";
                cout<<"s: To execute one by one\n";
                cout<<"p: To print values\n";
                cout<<"q: To turn OFF DEBUGGER\n";
                cout<<"h: to see menu\n";
                cout<<"\tPress key to continue:";
            }
            else if(ch=='r')
            {
                int i=0;
                linecount=0;
                source.open(fname);
                getline(source,line);
                while(1)
                {
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
                    if((brk[i]==linecount)||debug==0)
                    {
                        ins.show();
                        i++;
                        if(i==n)
                        {
                            debug=1;
                            break;
                        }
                    }
                    else if((linecount==totline)&&(debug==1))
                    {
                        ins.show();
                        break;
                    }
                    getline(source,line);
                }
                cout<<"\n\tDEBUGGER MENU\n";
                cout<<"b: To add break point\n";
                cout<<"r: To run the program\n";
                cout<<"s: To execute one by one\n";
                cout<<"p: To print values\n";
                cout<<"q: To turn OFF DEBUGGER\n";
                cout<<"h: to see menu\n";
                cout<<"\tPress key to continue:";
            }
        }//end of while
        if(ch=='q')
        {
            cout<<"\t\t\tDEBBUGER: OFF\n";
            cout<<"Want to run the program or not \n";
            cout<<"\nPRESS Y/N :";
            cin>>ch;
            if(ch=='n')
                return 0;
        }
    }
    else
    {
        cout<<"\tERROR IN INPUT\n\tPlease run your program Again\n";
        return 0;
    }

    
    
//--------------------------------------------------------------------------------------------------//
    //Execution part
    source.open(fname);
    if(source.fail())
        cout<<"ERROR\n";
    else
    {
        linecount=0;
        getline(source,line);
        while(source)
        {
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
                        //cout<<"JITGYA\n";
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
            else if(opcode=="HLT")
            {
                ins.show();
            }
            getline(source,line);
        }
        source.close();
  }//end of while
    return 0;
}
