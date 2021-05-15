#include<iostream>
#include <fstream>
#include<bits/stdc++.h>
using namespace std;
vector<string>instructions; //Vector to store all the instuctions
vector<string>main_instructions; //Vector to store all the instrucitions except label instructions
vector<int>linenumbers; //Vector that stores line numbers of each instruction in main_instructions
map<string,int>labels; //Map that stores line for each label 
map<string,string>OpcodeRtype; //Map that contains mapping of R type instruction set Opcodes
map<string,string>OpcodeItype; //Map that contains mapping of I type instruction set Opcodes
map<string,string>OpcodeJtype; //Map that contains mapping of J type instruction set Opcodes
map<string,string>Funct; //Map that contains funtion values of R type instruction set
map<string,string>Register; //Map that stores registers binary representation
map<string,string>BintoHex; //Map that has hexadecimal represetnation for the given binary string of 4 bits
string filename; //Store the file name user specified

void Set_BintoHexTable() //Function that initializes hexa values
{
    BintoHex.insert({"0000","0"});
    BintoHex.insert({"0001","1"});
    BintoHex.insert({"0010","2"});
    BintoHex.insert({"0011","3"});
    BintoHex.insert({"0100","4"});
    BintoHex.insert({"0101","5"});
    BintoHex.insert({"0110","6"});
    BintoHex.insert({"0111","7"});
    BintoHex.insert({"1000","8"});
    BintoHex.insert({"1001","9"});
    BintoHex.insert({"1010","A"});
    BintoHex.insert({"1011","B"});
    BintoHex.insert({"1100","C"});
    BintoHex.insert({"1101","D"});
    BintoHex.insert({"1110","E"});
    BintoHex.insert({"1111","F"});
}
void Set_Opcode_Rtype() //Set the R Opcode table
{
    OpcodeRtype.insert({"add","000000"});
    OpcodeRtype.insert({"addu","000000"});
    OpcodeRtype.insert({"and","000000"});
    OpcodeRtype.insert({"div","000000"});
    OpcodeRtype.insert({"divu","000000"});
    OpcodeRtype.insert({"mult","000000"});
    OpcodeRtype.insert({"multu","000000"});
    OpcodeRtype.insert({"nor","000000"});
    OpcodeRtype.insert({"or","000000"});
    OpcodeRtype.insert({"sll","000000"});
    OpcodeRtype.insert({"sllv","000000"});
    OpcodeRtype.insert({"slt","000000"});
    OpcodeRtype.insert({"sltu","000000"});
    OpcodeRtype.insert({"sra","000000"});
    OpcodeRtype.insert({"srav","000000"});
    OpcodeRtype.insert({"srl","000000"});
    OpcodeRtype.insert({"srlv","000000"});
    OpcodeRtype.insert({"sub","000000"});
    OpcodeRtype.insert({"subu","000000"});
    OpcodeRtype.insert({"xor","000000"});
    OpcodeRtype.insert({"jr","000000"});
    OpcodeRtype.insert({"jalr","000000"});
}
void Set_Opcode_Itype() //Set the I Opcode table
{
    OpcodeItype.insert({"addi", "001000"});
    OpcodeItype.insert({"addiu", "001001"});
    OpcodeItype.insert({"andi", "001100"});
    OpcodeItype.insert({"ori", "001101"});
    OpcodeItype.insert({"xori", "001110"});
    OpcodeItype.insert({"slti", "001010"});
    OpcodeItype.insert({"sltiu", "001011"});
    OpcodeItype.insert({"lb", "100000"});
    OpcodeItype.insert({"lbu", "100100"});
    OpcodeItype.insert({"lh", "100001"});
    OpcodeItype.insert({"lhu", "100101"});
    OpcodeItype.insert({"lw", "100011"});
    OpcodeItype.insert({"sb", "101000"});
    OpcodeItype.insert({"sh", "101001"});
    OpcodeItype.insert({"sw", "101011"});
    OpcodeItype.insert({"beq", "000100"}); 
    OpcodeItype.insert({"bne", "000101"}); 
    OpcodeItype.insert({"bgtz", "000111"}); 
    OpcodeItype.insert({"blez", "000110"});
}
void Set_Opcode_Jtype() //Set the J Opcode table
{
    OpcodeJtype.insert({"j", "000010"});
    OpcodeJtype.insert({"jal", "000011"});
}
void Set_Funct() //Set the Function table
{
    Funct.insert({"add","100000"});
    Funct.insert({"addu","100001"});
    Funct.insert({"and","100100"});
    Funct.insert({"div","011010"});
    Funct.insert({"divu","011011"});
    Funct.insert({"mult","011000"}); 
    Funct.insert({"multu","011001"}); 
    Funct.insert({"nor","100111"});
    Funct.insert({"or","100101"});
    Funct.insert({"sll","000000"});
    Funct.insert({"sllv","000100"});
    Funct.insert({"slt","101010"});
    Funct.insert({"sltu","101011"});
    Funct.insert({"sra","000011"});
    Funct.insert({"srav","000111"});
    Funct.insert({"srl","000010"});
    Funct.insert({"srlv","000110"});
    Funct.insert({"sub","100010"});
    Funct.insert({"subu","100100"});
    Funct.insert({"xor","100110"});
    Funct.insert({"jr", "001000"});
    Funct.insert({"jalr", "001001"});
}
void Set_Register() //Set the register table
{
    Register.insert({"$zero","00000"});
    Register.insert({"$at","00001"});
    Register.insert({"$v0","00010"});
    Register.insert({"$v1","00011"});
    Register.insert({"$a0","00100"});
    Register.insert({"$a1","00101"});
    Register.insert({"$a2","00110"});
    Register.insert({"$a3","00111"});
    Register.insert({"$t0","01000"});
    Register.insert({"$t1","01001"});
    Register.insert({"$t2","01010"});
    Register.insert({"$t3","01011"});
    Register.insert({"$t4","01100"});
    Register.insert({"$t5","01101"});
    Register.insert({"$t6","01110"});
    Register.insert({"$t7","01111"});
    Register.insert({"$s0","10000"});
    Register.insert({"$s1","10001"});
    Register.insert({"$s2","10010"});
    Register.insert({"$s3","10011"});
    Register.insert({"$s4","10100"});
    Register.insert({"$s5","10101"});
    Register.insert({"$s6","10110"});
    Register.insert({"$s7","10111"});
    Register.insert({"$t8","11000"});
    Register.insert({"$t9","11001"});
    Register.insert({"$k0","11010"});
    Register.insert({"$k1","11011"});
    Register.insert({"$gp","11100"});
    Register.insert({"$sp","11101"});
    Register.insert({"$fp","11110"});
    Register.insert({"$ra","11111"});
}
string int2bin_5bits(int n) //Function to Convert integer into 16 length string
{
    string x;
    for(int i=0;i<5;i++){
        if(n&1) 
        {
            x+='1';
        }
        else 
        {
            x+='0';
        }
        n>>=1;
    }
    reverse(x.begin(),x.end());
    return x;
}
string int2bin_16bits(int n) //Function to Convert integer into 16 length string
{
    string x;
    for(int i=0;i<16;i++){
        if(n&1) 
        {
            x+='1';
        }
        else 
        {
            x+='0';
        }
        n>>=1;
    }
    reverse(x.begin(),x.end());
    return x;
}
string int2bin_26bits(int n) //Function to Convert integer into 26 length string
{
    string x;
    for(int i=0;i<26;i++){
        if(n&1) 
        {
            x+='1';
        }
        else 
        {
            x+='0';
        }
        n>>=1;
    }
    reverse(x.begin(),x.end());
    return x;
}
bool isnumber(string s) //Function to check whether a given string ia a number or not
{ 
    int i=0;
    int n=s.length();
    if(s[i]=='-')i++;//If the given number is negative we incrment i
    for(;i<n;i++)
    {
        if(!isdigit(s[i]))break;
    }
    bool answer=!s.empty() && i == n;
    return answer;
}
string twoscompliment(string s) //Function that finds 2's compliment of the given binary string
{
    int n = s.length(); 
    int i;
    for (i=n-1;i>=0;i--) 
    {
        if(s[i]=='1') 
        {
            break;
        }
    }  
    if(i==-1)return '1'+s; 
    for (int j=i-1;j>= 0;j--) 
    { 
        if(s[j]=='1')
        {
            s[j]='0'; 
        }
        else 
        {
            s[j]='1';
        } 
    } 
    return s;
}
string binHexConv(string s) //Convert binary string into Hexadecimal string
{
    string hexvalue;
    for(int i=0;i<s.length();i+=4)
    {
        hexvalue+=BintoHex[s.substr(i,4)];
    }
    return hexvalue;
}
void Read_InputFile()//It reads the input .asm file and stores the instructions
{
    ifstream file; //File handling
    cout<<"Please give the MIPS file name "<<endl;
    cin>>filename;
    file.open(filename);
    if(file)
    {  
        while (file)
        {
            string presentline;
            getline(file,presentline);//Get the current line from input file
            instructions.push_back(presentline);  //Storing the instructions         
        }
        file.close();
    }
    else 
    {
        cout<<"Mentioned file is not present";//Prints when the user mentioned file is not present
    }
}
void SaveLabels()//Save the instructions removing comments in main_instructions vector file
{
    main_instructions.clear();
    string current_instruction;
    int line_number;
    int index=1;
    for(int i=0;i<instructions.size();i++)
    {
        line_number=i+1;
        current_instruction=instructions[i];
        int comment=current_instruction.find('#');//Find the location of #
        if(comment!=string::npos)//Removing comment part in the instruction
        {
            auto temp=current_instruction.substr(0,comment);
            current_instruction=temp;
        }
        if(current_instruction[current_instruction.length()-1]==':')//Label starts here
        {
            string temp=current_instruction.substr(0,current_instruction.length()-1);
            if(labels.find(temp)!=labels.end())cout<<"Error! Multiple instances of this label is found"<<endl;
            if(temp[0]>='0' && temp[0]<='9')
            {
                cout<<"Error! Label name starts with digit"<<endl;//Error is reported when label starts with digit
                continue;
            }
            labels[temp]=index;//Saving the line number of label
            index++;
        }
        else if(current_instruction.length()!=0)
        {
            main_instructions.push_back(current_instruction);
            linenumbers.push_back(index);
            index++;//increment the line number
        }
    }
    //for(auto x:labels)cout<<x.first<<" --"<<x.second<<endl;
}
string Rtype(string op,string reg1,string reg2,string reg3)//Process the R type instruction
{
    string CurrentLineInBinary;
       if(op=="jalr")//When op is jalr it is handled here
       {
            CurrentLineInBinary+=OpcodeRtype[op];
            CurrentLineInBinary+=Register[reg2];
            CurrentLineInBinary+="00000";
            CurrentLineInBinary+=Register[reg1];
            CurrentLineInBinary+="00000";
            CurrentLineInBinary+=Funct[op];
       }
       else if(op=="jr")//When op is jr it is handled here
       {
            CurrentLineInBinary+=OpcodeRtype[op];
            CurrentLineInBinary+=Register[reg1];
            CurrentLineInBinary+="00000";
            CurrentLineInBinary+="00000";
            CurrentLineInBinary+="00000";
            CurrentLineInBinary+=Funct[op];
       }
       else if(op=="mult" || op=="multu" || op=="div"||op=="divu")
       {
           //When op is multiplication,division commands are handled here
           CurrentLineInBinary+=OpcodeRtype[op];
           CurrentLineInBinary+=Register[reg1];
           CurrentLineInBinary+=Register[reg2];
           CurrentLineInBinary+="0000000000";
           CurrentLineInBinary+=Funct[op];
       }
       else if(op=="sll"||op=="sra"||op=="srl")
       {
           // sll,sra,srl commands are handled here
           CurrentLineInBinary+=OpcodeRtype[op];
           CurrentLineInBinary+="00000";
           CurrentLineInBinary+=Register[reg2];
           CurrentLineInBinary+=Register[reg1];
           int sa =stoi(reg3);
           string temp=int2bin_5bits(sa);//converting the integer into binary string
           CurrentLineInBinary+=temp; 
           CurrentLineInBinary+=Funct[op];
       }
       else //rest of the commands are handled here
       {
           CurrentLineInBinary+=OpcodeRtype[op];
           CurrentLineInBinary+=Register[reg2];
           CurrentLineInBinary+=Register[reg3];
           CurrentLineInBinary+=Register[reg1];
           CurrentLineInBinary+="00000";
           CurrentLineInBinary+=Funct[op];
       }
       return CurrentLineInBinary;
}

string Itype(string op,string reg1,string reg2,string reg3,int i)//Handles I type instructions here
{
    string CurrentLineInBinary;
    if(op=="addi" || op=="andi" || op=="ori" || op=="xori" || op=="slti")// Doing arithemetic,logical operations with one argument being constant value
    {
        CurrentLineInBinary+=OpcodeItype[op];
        CurrentLineInBinary+=Register[reg2];
        CurrentLineInBinary+=Register[reg1];
        int offset=stoi(reg3);
        if(offset<0)//If the number is less than 0, We take 2's compliment
        {
            string temp=int2bin_16bits(abs(offset));
            string twos=twoscompliment(temp);
            CurrentLineInBinary+=twos;
        }
        else //If number is greater than 0 then offset is direct the binary representation of that number
        {
            CurrentLineInBinary+=int2bin_16bits(offset);
        }
    }
    else if(op=="addiu"|| op=="sltiu")//Doing unsigned operations with one argument as argument
    {
        CurrentLineInBinary+=OpcodeItype[op];
        CurrentLineInBinary+=Register[reg2];
        CurrentLineInBinary+=Register[reg1];
        int offset=stoi(reg3);
        if(offset<0)//Since this is unsigned instruction negative values are not accepted
        {
            cout<<"Error! It is an unsigned instruction but given offset at line- "<<linenumbers[i]<<" is negative number"<<endl;
        }
        else
        {
            CurrentLineInBinary+=int2bin_16bits(offset);//Converting into binary string
        }
    }
    else if(op=="lb"||op=="lbu"||op=="lh"||op=="lhu"||op=="lw" || op=="sb"||op=="sh"||op=="sw")//Instructions such as load word,store word are handled
    {
        CurrentLineInBinary+=OpcodeItype[op];
        int posLeft=reg2.find('(');
        int posRight=reg2.find(')');
        int offset=stoi(reg2.substr(0,posLeft));
        string base=reg2.substr(posLeft+1,posRight-posLeft-1);//Finding the register between ( )
        CurrentLineInBinary+=Register[base];
        CurrentLineInBinary+=Register[reg1];
        CurrentLineInBinary+=int2bin_16bits(offset);//Converting integer into 16 length binary string
    }
    else //Handling branch equations here
    {
        if(op=="beq" || op=="bne")//branch comparing instructions are handled here
        {
            CurrentLineInBinary+=OpcodeItype[op];
            CurrentLineInBinary+=Register[reg1];
            CurrentLineInBinary+=Register[reg2];
            if(isnumber(reg3)) //Here the third argument is the distance between the current istruction and jump location
            {
                int offset=stoi(reg3);
                if(offset<0)//If offset is negative it jumps to the location which is above the current address
                {   //if offset is negative number we take the 2's compliment
                    string temp=int2bin_16bits(abs(offset));
                    string twos=twoscompliment(temp);
                    CurrentLineInBinary+=twos;
                }
                else
                {
                    CurrentLineInBinary+=int2bin_16bits(offset);//Converting integer into 16 length binary string
                }            
            }
            else //If the 3rd argument is a label it is handled here
            {
                if(labels[reg3]>linenumbers[i])
                {
                    int offset=labels[reg3]-linenumbers[i]-1;
                    CurrentLineInBinary+=int2bin_16bits(offset);//Converting integer into 16 length binary string
                }
                else 
                {
                    //If offset is negative it jumps to the location which is above the current address
                    int offset=(labels[reg3]-linenumbers[i])-1;
                    string temp=int2bin_16bits(abs(offset));//if offset is negative number we take the 2's compliment
                    string twos=twoscompliment(temp);
                    CurrentLineInBinary+=twos;
                }
            }
        }
        else if(op=="bgtz" || op=="blez")// If-else branch equation are handled here
        {
            CurrentLineInBinary+=OpcodeItype[op];
            CurrentLineInBinary+=Register[reg1];
            CurrentLineInBinary+="00000";
            if(isnumber(reg2))//Here the third argument is the distance between the current istruction and jump location
            {
                int offset = stoi(reg2);
                if(offset<0)//If offset is negative it jumps to the location which is above the current address
                {   //if offset is negative number we take the 2's compliment
                    string temp=int2bin_16bits(abs(offset));
                    string twos=twoscompliment(temp);
                    CurrentLineInBinary+=twos;
                }
                else 
                {
                    CurrentLineInBinary+=int2bin_16bits(offset);//Converting integer into 16 length binary string
                }
            }
            else //If the 3rd argument is a label it is handled here
            {
                if(labels[reg2]>linenumbers[i])
                {
                    int offset=labels[reg2]-linenumbers[i]-1;
                    CurrentLineInBinary+=int2bin_16bits(offset);//Converting integer into 16 length binary string
                }
                else 
                {
                    //If offset is negative it jumps to the location which is above the current address
                    int offset=(labels[reg2]-linenumbers[i])-1;
                    string temp=int2bin_16bits(abs(offset));//if offset is negative number we take the 2's compliment
                    string twos=twoscompliment(temp);
                    CurrentLineInBinary+=twos;
                }
            }
        }
    }
    return CurrentLineInBinary;
}
string Jtype(string op,string reg1,string reg2,string reg3,int i)//Hadles Jtype instructions here
{
    string CurrentLineInBinary;
    CurrentLineInBinary+=OpcodeJtype[op];
    int offset=stoi(reg1);
    if(offset<0)
    {   
        //If offset is negative it jumps to the location which is above the current address
        string temp=int2bin_26bits(abs(offset));//if offset is negative number we take the 2's compliment
        string twos=twoscompliment(temp);
        CurrentLineInBinary+=twos;
    }
    else
    {
        CurrentLineInBinary+=int2bin_26bits(offset);//Converting integer into 26 length binary string
    }
    return CurrentLineInBinary;
}
void mipstobin()//Convert mips code into binary code
{
    fstream file;
    int pos=filename.find('.');
    string filesubstring=filename.substr(0,pos);
    filesubstring+="bin.txt";//Creating a new file with this name
    file.open(filesubstring,ios::out);//OPening the filw with write access
    for(int i=0;i<main_instructions.size();i++)//Looping over instructions
    {
       string presentline=main_instructions[i];//Taking the current instruction
       stringstream take(presentline);
       string op;take>>op;//using string stream and getting the arguments as individual string
       string reg1,reg2,reg3;
       if(op.length()!=0)
       {
           string temp;take>>temp;
           if(temp[temp.length()-1]==',')reg1=temp.substr(0,temp.length()-1);
           else reg1=temp;
       }
       if(reg1.length()!=0)
       {
           string temp;take>>temp;
           if(temp[temp.length()-1]==',')reg2=temp.substr(0,temp.length()-1);
           else reg2=temp;
       }
       if(reg2.length()!=0)
       {
           string temp;take>>temp;
           if(temp[temp.length()-1]==',')
           {
               reg3=temp.substr(0,temp.length()-1);
           }
           else reg3=temp;
       }
       if(OpcodeRtype.find(op)!=OpcodeRtype.end())//If it is present in OpR table we go into this branch
       {
           string output=Rtype(op,reg1,reg2,reg3);
           string hex=binHexConv(output);
           file<<output<<" ("<<hex<<")"<<presentline<<endl;
       }
       else if(OpcodeItype.find(op)!=OpcodeItype.end())//If it is present in OpI table we go into this branch
       {
           string output=Itype(op,reg1,reg2,reg3,i);
           string hex=binHexConv(output);
           file<<output<<" ("<<hex<<")"<<presentline<<endl;
       }
       else if(OpcodeJtype.find(op)!=OpcodeJtype.end())//If it is present in OpJ table we go into this branch
       {
           string output=Jtype(op,reg1,reg2,reg3,i);
           string hex=binHexConv(output);
           file<<output<<" ("<<hex<<")"<<presentline<<endl;
       }
       else cout<<"Sorry! This Assembler doesn't support - "<<op<<" function"<<endl;//When an unknown instruction is given error is reported
    }
}
int main()
{
    instructions.clear();
    main_instructions.clear();
    labels.clear();
    linenumbers.clear();
    //Clearing all the vectors
    Read_InputFile(); //Reading the input file
    SaveLabels();//Saving the labels line numbers
    Set_Opcode_Rtype();//Intialising OpcodeR table
    Set_Opcode_Itype();//Intialising OpcodeI table
    Set_Opcode_Jtype();//Intialising OpcodeJ table
    Set_Funct();//Intialising Function table
    Set_Register();//Intialising Register table
    Set_BintoHexTable();//Intialising Binary to Hex table
    mipstobin();//Converts Mips file into binary code
    return 0;
}