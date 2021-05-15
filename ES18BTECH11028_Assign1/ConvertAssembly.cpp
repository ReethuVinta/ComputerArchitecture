#include<iostream>
#include <fstream>
#include<bits/stdc++.h>
using namespace std;
vector<string>instructions;//Vector to store all the instuctions
map<string,string>HextoBin;//Map that has for the given binary string of 4 bits its hexadecimal represetnation 
map<string,string>OpcodeItype;//Map that contains mapping of I type instruction set Opcodes
map<string,string>OpcodeJtype;//Map that contains mapping of J type instruction set Opcodes
map<string,string>Funct;//Map that contains funtion values of R type instruction set
map<string,string>Register;//Map that stores registers binary representation
string filename;
void Set_HextoBinTable()//Function that initializes hexa values
{
    HextoBin.insert({"0","0000"});
    HextoBin.insert({"1","0001"});
    HextoBin.insert({"2","0010"});
    HextoBin.insert({"3","0011"});
    HextoBin.insert({"4","0100"});
    HextoBin.insert({"5","0101"});
    HextoBin.insert({"6","0110"});
    HextoBin.insert({"7","0111"});
    HextoBin.insert({"8","1000"});
    HextoBin.insert({"9","1001"});
    HextoBin.insert({"A","1010"});
    HextoBin.insert({"B","1011"});
    HextoBin.insert({"C","1100"});
    HextoBin.insert({"D","1101"});
    HextoBin.insert({"E","1110"});
    HextoBin.insert({"F","1111"});
}
void Set_Opcode_Itype()//Set the I Opcode table
{
    OpcodeItype.insert({"001000","addi"});
    OpcodeItype.insert({"001001","addiu"});
    OpcodeItype.insert({"001100","andi"});
    OpcodeItype.insert({"001101","ori"});
    OpcodeItype.insert({"001110","xori"});
    OpcodeItype.insert({"001010","slti"});
    OpcodeItype.insert({"001011","sltiu"});
    OpcodeItype.insert({"100000","lb"});
    OpcodeItype.insert({"100100","lbu"});
    OpcodeItype.insert({"100001","lh"});
    OpcodeItype.insert({"100101","lhw"});
    OpcodeItype.insert({"100011","lw"});
    OpcodeItype.insert({"101000","sb" });
    OpcodeItype.insert({"101001","sh"});
    OpcodeItype.insert({"101011","sw"});
    OpcodeItype.insert({"000100","beq"});
    OpcodeItype.insert({"000111","bgtz"}); 
    OpcodeItype.insert({"000110","blez"}); 
    OpcodeItype.insert({"000101","bne"}); 
}
void Set_Opcode_Jtype() //Set the J Opcode table
{
    OpcodeJtype.insert({"000010","j"});
    OpcodeJtype.insert({"000011","jal"});
}
void Set_Funct()//Set the Function table
{
    Funct.insert({"100000","add"});
    Funct.insert({"100001","addu"});
    Funct.insert({"100100","and"});
    Funct.insert({"011010","div"});
    Funct.insert({"011011","divu"});
    Funct.insert({"011000","mult"}); 
    Funct.insert({"011001","multu"}); 
    Funct.insert({"100111","nor"});
    Funct.insert({"100101","or"});
    Funct.insert({"000000","sll"});
    Funct.insert({"000100","sllv"});
    Funct.insert({"000011","sra"});
    Funct.insert({"000111","srav"});
    Funct.insert({"000010","srl"});
    Funct.insert({"000110","srlv"});
    Funct.insert({"100010","sub"});
    Funct.insert({"100100","subu"});
    Funct.insert({"100110","xor"});
    Funct.insert({"101010","slt"});
    Funct.insert({"101011","sll"});
    Funct.insert({"001001","jalr"});
    Funct.insert({"001000","jr"});
}
void Set_Register()//Set the register table
{
    Register.insert({"00000","$zero"});
    Register.insert({"00001","$at"});
    Register.insert({"00010","$v0"});
    Register.insert({"00011","$v1"});
    Register.insert({"00100","$a0"});
    Register.insert({"00101","$a1"});
    Register.insert({"00110","$a2"});
    Register.insert({"00111","$a3"});
    Register.insert({"01000","$t0"});
    Register.insert({"01001","$t1"});
    Register.insert({"01010","$t2"});
    Register.insert({"01011","$t3"});
    Register.insert({"01100","$t4"});
    Register.insert({"01101","$t5"});
    Register.insert({"01110","$t6"});
    Register.insert({"01111","$t7"});
    Register.insert({"10000","$s0"});
    Register.insert({"10001","$s1"});
    Register.insert({"10010","$s2"});
    Register.insert({"10011","$s3"});
    Register.insert({"10100","$s4"});
    Register.insert({"10101","$s5"});
    Register.insert({"10110","$s6"});
    Register.insert({"10111","$s7"});
    Register.insert({"11000","$t8"});
    Register.insert({"11001","$t9"});
    Register.insert({"11010","$k0"});
    Register.insert({"11011","$k1"});
    Register.insert({"11100","$gp"});
    Register.insert({"11101","$sp"});
    Register.insert({"11110","$fp"});
    Register.insert({"11111","$ra"});
}
string BinstringtoIntstring(string s)//Convert the given binary string into decimal string
{
    int n=s.length();
    int number=stoi(s,0,2);//Using stoi to convert into number
    string num=to_string(number);//Converting into string
    return num;
}
string twostodecimal(string s)//Converting 2s compliment to binary number
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
void Read_InputFile()//It reads the input .txt file and CurrentLineInMipss the mips instructions
{
    ifstream file;//File handling
    cout<<"Please give the txt file name "<<endl;
    cin>>filename;
    file.open(filename);
    if(file)
    {  
        while (file)
        {
            string presentline;
            getline(file,presentline);//Get the current line from input file
            stringstream take(presentline);//Using stringstream we we extract the binary strinig part
            string binarypart;
            take>>binarypart;
            instructions.push_back(binarypart);//Saving those in instructions vector         
        }
        file.close();
    }
    else 
    {
        cout<<"Mentioned file is not present";//Prints when the user mentioned file is not present
    }
}
string Rtype(string presentline)//Process the R type instruction
{
    string CurrentLineInMips;
    string function=presentline.substr(26,6);//Taking the last 6  bits to find the function in that instruction
    CurrentLineInMips+=Funct[function];
    CurrentLineInMips+=" ";
    if(Funct[function]=="jalr")//If the function is jalr we come here
    {
        string reg2=presentline.substr(6,5);//splitting the biniary string into respective argument string
        string reg1=presentline.substr(16,5);
        CurrentLineInMips+=Register[reg1];
        CurrentLineInMips+=", ";
        CurrentLineInMips+=Register[reg2];
    }
    else if(Funct[function]=="jr")//If the function is jr we come here
    {
        string reg1=presentline.substr(6,5);//splitting the biniary string into respective argument string
        CurrentLineInMips+=Register[reg1];
    }
    else if(Funct[function]=="mult" || Funct[function]=="multu" || Funct[function]=="div"|| Funct[function]=="divu")//For multiplication and division operatins we come here
    {
        string reg1=presentline.substr(6,5);//splitting the biniary string into respective argument string
        string reg2=presentline.substr(11,5);
        CurrentLineInMips+=Register[reg1];
        CurrentLineInMips+=", ";
        CurrentLineInMips+=Register[reg2];
    }
    else if(Funct[function]=="sll"||Funct[function]=="sra"||Funct[function]=="srl")//For sll,sra,srl we come here
    {
        string reg2=presentline.substr(11,5);//splitting the biniary string into respective argument string
        string reg1=presentline.substr(16,5);
        string reg3=presentline.substr(21,5);
        CurrentLineInMips+=Register[reg1];
        CurrentLineInMips+=", ";
        CurrentLineInMips+=Register[reg2];
        CurrentLineInMips+=", ";
        string temp=BinstringtoIntstring(reg3);//Converting Binary string into integer string
        CurrentLineInMips+=temp;
    }
    else 
    {
        string reg2=presentline.substr(6,5);//splitting the biniary string into respective argument string
        string reg3=presentline.substr(11,5);
        string reg1=presentline.substr(16,5);
        CurrentLineInMips+=Register[reg1];
        CurrentLineInMips+=", ";
        CurrentLineInMips+=Register[reg2];
        CurrentLineInMips+=", ";
        CurrentLineInMips+=Register[reg3];
    }
    return CurrentLineInMips;
}
string Itype(string presentline)//Handles I type instructions here
{
    string CurrentLineInMips;
    string op=OpcodeItype[presentline.substr(0,6)];
    if(op=="addi"|| op=="andi" || op=="ori" || op=="xori" || op=="slti")// Doing arithemetic,logical operations with one argument being constant value
    {
        CurrentLineInMips+=op;   
        CurrentLineInMips+=" ";
        string reg2=presentline.substr(6,5);//splitting the biniary string into respective argument string
        string reg1=presentline.substr(11,5);
        string offset=presentline.substr(16,16);
        CurrentLineInMips+=Register[reg1];
        CurrentLineInMips+=", ";
        CurrentLineInMips+=Register[reg2];
        CurrentLineInMips+=", ";
        if(offset[0]=='1')//Negative Number
        {
            string bin=twostodecimal(offset);//We convert 2s compliment into binary number to get the decimal value
            string numberstr=BinstringtoIntstring(bin);//Converting Binary string into integer string
            numberstr='-'+numberstr;//Appending - symbol to that last argument as offset value is negative
            CurrentLineInMips+=numberstr;
        }
        else 
        {
            string OffSetstr=BinstringtoIntstring(offset);//Converting Binary string into integer string
            CurrentLineInMips+=OffSetstr;
        }
    }
    else if(op=="addiu" || op=="sltiu")
    {
        CurrentLineInMips+=op;   
        CurrentLineInMips+=" ";
        string reg2=presentline.substr(6,5);//splitting the biniary string into respective argument string
        string reg1=presentline.substr(11,5);
        string offset=presentline.substr(16,16);
        CurrentLineInMips+=Register[reg1];
        CurrentLineInMips+=", ";
        CurrentLineInMips+=Register[reg2];
        CurrentLineInMips+=", ";
        if(offset[0]=='1')//Negative Number
        {
            //But we know that unsinged operators can't take negative values
            cout<<"Error! It is an unsigned instruction but given offset is negative number"<<endl;
        }
        else 
        {
            string OffSetstr=BinstringtoIntstring(offset);//Converting Binary string into integer string
            CurrentLineInMips+=OffSetstr;
        }
    }
    else if(op=="lb"||op=="lbu"||op=="lh"||op=="lhw"||op=="lw" || op=="sb"||op=="sh"||op=="sw")
    {
        CurrentLineInMips+=op;
        CurrentLineInMips+=" ";
        string reg2=presentline.substr(6,5);//splitting the biniary string into respective argument string
        string reg1=presentline.substr(11,5);
        string offset=presentline.substr(16,16);
        string OffSetstr=BinstringtoIntstring(offset);//Converting Binary string into integer string
        CurrentLineInMips+=Register[reg1];
        CurrentLineInMips+=", ";
        CurrentLineInMips+=OffSetstr;
        CurrentLineInMips+="(";
        CurrentLineInMips+=Register[reg2];
        CurrentLineInMips+=")";     
    }
    else //Branch equations are handled here
    {
        if(op=="bne" || op=="beq")//branch comparing instructions are handled here
        {
            CurrentLineInMips+=op;   
            CurrentLineInMips+=" ";
            string reg1=presentline.substr(6,5);//splitting the biniary string into respective argument string
            string reg2=presentline.substr(11,5);
            CurrentLineInMips+=Register[reg1];
            CurrentLineInMips+=", ";
            CurrentLineInMips+=Register[reg2];
            CurrentLineInMips+=", ";
            string offset=presentline.substr(16,16);
            if(offset[0]=='1')//Negative Number
            {
                string bin=twostodecimal(offset);//We convert 2s compliment into binary number to get the decimal value
                string numberstr=BinstringtoIntstring(bin);//Converting Binary string into integer string
                numberstr='-'+numberstr;//Appending - symbol to that last argument as offset value is negative
                CurrentLineInMips+=numberstr;
            }
            else 
            {
                string OffSetstr=BinstringtoIntstring(offset);//Converting Binary string into integer string
                CurrentLineInMips+=OffSetstr;
            }
        }
        else if(op=="bgtz" || op=="blez")// If-else branch equation are handled here
        {
            CurrentLineInMips+=op;   
            CurrentLineInMips+=" ";
            string reg1=presentline.substr(6,5);//splitting the biniary string into respective argument string
            CurrentLineInMips+=Register[reg1];
            CurrentLineInMips+=", ";
            string offset=presentline.substr(16,16);
            if(offset[0]=='1')//Negative Number
            {
                string bin=twostodecimal(offset);//We convert 2s compliment into binary number to get the decimal value
                string numberstr=BinstringtoIntstring(bin);//Converting Binary string into integer string
                numberstr='-'+numberstr;//Appending - symbol to that last argument as offset value is negative
                CurrentLineInMips+=numberstr;
            }
            else 
            {
                string OffSetstr=BinstringtoIntstring(offset);//Converting Binary string into integer string
                CurrentLineInMips+=OffSetstr;
            }
        }
    }
    return CurrentLineInMips;
}
string Jtype(string presentline)//Hadles Jtype instructions here
{
    string CurrentLineInMips;
    string op=OpcodeJtype[presentline.substr(0,6)];
    CurrentLineInMips+=op;
    CurrentLineInMips+=" ";
    string offset=presentline.substr(6,26);//splitting the biniary string into respective argument string
    if(offset[0]=='1')//Negative Number
    {   //If offset is negative it jumps to the location which is above the current address
        string bin=twostodecimal(offset);//We convert 2s compliment into binary number to get the decimal value
        string numberstr=BinstringtoIntstring(bin);//Converting Binary string into integer string
        numberstr='-'+numberstr;//Appending - symbol to that last argument as offset value is negative
        CurrentLineInMips+=numberstr;
    }
    else 
    {
        string OffSetstr=BinstringtoIntstring(offset);//Converting Binary string into integer string
        CurrentLineInMips+=OffSetstr;
    }
    return CurrentLineInMips;
}
void BintoMips()//Converts binary code into Mips instructions
{
    fstream file;
    string filesubstring="bin2";//Creating a new file with this name
    filesubstring+=filename.substr(12,5);
    filesubstring+=".txt";
    file.open(filesubstring,ios::out);//Opening the file with write access
    for(int i=0;i<instructions.size()-1;i++)
    {
        string presentline=instructions[i];
        string opcode=presentline.substr(0,6);
        if(opcode=="000000")//If opcode is all zeros then it is R type
        {
            string CurrentLineInMips=Rtype(presentline);
            file<<CurrentLineInMips<<endl;
        }
        else if(opcode=="000010"||opcode=="000011")//If opcode is 000010/000011 then it is R type
        {
            string CurrentLineInMips=Jtype(presentline);
            file<<CurrentLineInMips<<endl;
        }
        else //Else then it is I type
        {
            string CurrentLineInMips=Itype(presentline);
            file<<CurrentLineInMips<<endl;
        }
    }
}
int main()
{
    Set_Opcode_Itype();//Intialising OpcodeI table
    Set_Opcode_Jtype();//Intialising OpcodeJ table
    Set_HextoBinTable();//Intialising Hex to Bin table
    Set_Funct();//Intialising Function table
    Set_Register();//Intialising Register table
    Read_InputFile();//Reading the input file
    BintoMips();//Converts Mips file into binary code
    return 0;
}