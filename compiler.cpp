// https://github.com/MahediKamal/Basic_compiler
#include <bits/stdc++.h>
#define Dbug1(x)                 cout << #x << " is " << x << endl;
#define Dbug2(x,y)               cout << #x << " is " << x << "    " << #y << " is " << y << endl ;
#define Dbug3(x,y,z)             cout << #x << " is " << x << "    " << #y << " is " << y << "    "<< #z << " is " << z << endl;
#define Dbug4(x,y,z,a)           cout << #x << " is " << x << "    " << #y << " is " << y << "    "<< #z << " is " << z << "    " << #a << " is " << a << endl;
#define Dbug5(x,y,z,a,b)         cout << #x << " is " << x << "    " << #y << " is " << y << "    "<< #z << " is " << z << "    " << #a << " is " << a << "    " << #b << " is " << b << endl;
#define lli long long int
#define ff first
#define ss second
#define sz  100
#define mod 100
#define id 201914035
using namespace std;

//////global var
int line_number = 1;

//////


class SymbolInfo{
public:
    string smbl;
    string typ;
    int lne_nm;
    SymbolInfo(string a, string b, int ln){
        smbl = a; typ = b; lne_nm = ln;
    }
    SymbolInfo(){}
    void ShowIfo(ofstream &output_){
        output_<< "<  "<<smbl<<", "<<typ<<", "<<lne_nm<<"  > "<<endl;
    }
    void ShowIfo(){
        cout<< "<  "<<smbl<<", "<<typ<<", "<<lne_nm<<"  > ";
    }
    
    bool operator == (SymbolInfo const &obj) {// == overloading
         if(smbl == obj.smbl) return true;
         return false;
    }
};

class SymbolTable{
private:
    vector< SymbolInfo >table[sz+5];
    lli hash_Technique;

    lli Hash_1(string s){// hash_Technique 1 
        string x = s;
        lli val = 0;
        if(x.size() % 2 == 1){//odd
            val = x[0];
            if(x.size() >= 2) val += x[1];
        }else{//even
            val = x[x.size()-1];
            if(x.size() >= 2) val += x[x.size()-2]; 
        }
        val *= (id % 100);
        return (val % mod);
    }
    lli Hash_2(string s){// hash_Technique 2
        string x = s;
        lli val = 0;
        for(lli i=0; i<s.size(); i+=2){
            int v = s[i];
            val += (v<<(id%10));
        }
        return (val % mod);
    }
    lli Hash(string s){// generalized hash
        lli idx;
        if(hash_Technique == 1) idx = Hash_1(s);
        else idx = Hash_2(s);
        return idx;
    }
public:
    SymbolTable(lli typ){
        hash_Technique = typ; // saving which hash_Technique we are going to use
    }
    pair<lli,lli> LookUp(SymbolInfo s){// looking for a symbol and returning the position where it is saved in the table
        lli idx = Hash(s.smbl);
        pair<lli,lli> pos = make_pair(-1,-1); //initializing with invalid idx
        for(lli i=0; i<table[idx].size(); i++){
            if(s == table[idx][i]){
                pos = make_pair(idx, i);
                return pos; //0 based idx
            }
        }
        return pos;// if not found, returning (-1,-1)
    }
    pair<lli,lli> Insert(SymbolInfo s, ofstream &output_){// inserting if was not inserted before and returning inserted position
        // if(LookUp(s).ff != -1){// not inserting same dta 
        //     pair<lli,lli> pos = make_pair(-1, -1);
        //     return pos;// returning an invalid idx
        // }
        lli idx = Hash(s.smbl);
        table[idx].push_back(s);
        pair<lli,lli> pos = make_pair(idx, table[idx].size()-1); // 0 based position

        s.ShowIfo(output_);
        Print();
        // cout<< " inserted at position " <<"(" <<pos.ff <<"," <<pos.ss <<")"<<endl;
        return pos;

    }
    pair<lli,lli> Insert(SymbolInfo s){// inserting if was not inserted before and returning inserted position
        // if(LookUp(s).ff != -1){// not inserting same dta 
        //     pair<lli,lli> pos = make_pair(-1, -1);
        //     return pos;// returning an invalid idx
        // }
        lli idx = Hash(s.smbl);
        table[idx].push_back(s);
        pair<lli,lli> pos = make_pair(idx, table[idx].size()-1); // 0 based position

        s.ShowIfo();
        cout<< " inserted at position " <<"(" <<pos.ff <<"," <<pos.ss <<")"<<endl;
        return pos;

    }
    pair<lli,lli> Delete(SymbolInfo s){// deleting if found and returning deleted position
        lli idx = Hash(s.smbl);
        for(lli i=0; i<table[idx].size(); i++){
            if(s == table[idx][i]){
                for(lli j=i; j<table[idx].size()-1; j++){
                    table[idx][j] = table[idx][j+1];
                }
                table[idx].pop_back();
                cout<<"Deleted from "<<idx<<","<<i<<endl;
                pair<lli,lli> pos = make_pair(idx, i);
                return pos; //0 based idx
            }
        }
        cout<<s.smbl <<" not Found"<<endl;
        pair<lli,lli> pos = make_pair(-1, -1);
        return pos;// returning an invalid idx
    }
    void Print(){// Printing the whole hash table
        for(int i=0; i<=sz; i++){
            cout<<i <<" ------> ";
            for(int j=0; j<table[i].size(); j++){ 
                table[i][j].ShowIfo(); cout<<" ";
            }cout<<endl;
        }
    }
    SymbolInfo get_by_position(lli i,lli j){// returning value saved in index [i][j] in the table
        if(i < sz && table[i].size() > j)
            return table[i][j];
        SymbolInfo dummy("-1-1", "-1-1", -1);
        return dummy;
    }
};

void deorate(string dc = NULL, string smb = "", string typ = ""){
    return;
    cout<<"Input :"<<dc<<" "<<smb<<" "<<typ<<endl<<"output :"<<endl;
   
}

string findOperator(string &line, SymbolTable &s_table, ofstream &output_){// finding operators ans replacing them with gap
    
    for(int i=0; i<line.size(); i++){
        // +, +=, ++
        if(line[i] == '+'){
            line[i] = ' ';
            if(i+1 < line.size() && line[i+1] == '='){
                // cout<<" found +="<<" ";

                string smb = "+=", typ = "operator";
                SymbolInfo s(smb, typ, line_number);
                s_table.Insert(s, output_);
                deorate("I", smb, typ);
                
                i++;
                line[i] = ' ';
            }else if(i+1 < line.size() && line[i+1] == '+'){
                // cout<<" found +="<<" ";

                string smb = "++", typ = "operator";
                SymbolInfo s(smb, typ, line_number);
                s_table.Insert(s, output_);
                deorate("I", smb, typ);
                
                i++;
                line[i] = ' ';
            }else{
                // cout<<" found +"<<" ";
                string smb = "+", typ = "operator";
                SymbolInfo s(smb, typ, line_number);
                s_table.Insert(s, output_);
                deorate("I", smb, typ);
            }
        }
        // -, -=, --
        if(line[i] == '-'){
            line[i] = ' ';
            if(i+1 < line.size() && line[i+1] == '='){
                // cout<<" found -="<<" ";

                string smb = "-=", typ = "operator";
                SymbolInfo s(smb, typ, line_number);
                s_table.Insert(s, output_);
                deorate("I", smb, typ);

                i++;
                line[i] = ' ';
            }else if(i+1 < line.size() && line[i+1] == '-'){
                // cout<<" found -="<<" ";

                string smb = "--", typ = "operator";
                SymbolInfo s(smb, typ, line_number);
                s_table.Insert(s, output_);
                deorate("I", smb, typ);

                i++;
                line[i] = ' ';
            }else{
                // cout<<" found -"<<" ";
                string smb = "-", typ = "operator";
                SymbolInfo s(smb, typ, line_number);
                s_table.Insert(s, output_);
                deorate("I", smb, typ);
            }
        }
        // *, *=
        if(line[i] == '*'){
            line[i] = ' ';
            if(i+1 < line.size() && line[i+1] == '='){
                // cout<<" found *="<<" ";

                string smb = "*=", typ = "operator";
                SymbolInfo s(smb, typ, line_number);
                s_table.Insert(s, output_);
                deorate("I", smb, typ);

                i++;
                line[i] = ' ';
            }else{
                // cout<<" found *"<<" ";
                string smb = "*", typ = "operator";
                SymbolInfo s(smb, typ, line_number);
                s_table.Insert(s, output_);
                deorate("I", smb, typ);
            }
        }
        // /, /=
        if(line[i] == '/'){
            line[i] = ' ';
            if(i+1 < line.size() && line[i+1] == '='){
                // cout<<" found /="<<" ";
                string smb = "/=", typ = "operator";
                SymbolInfo s(smb, typ, line_number);
                s_table.Insert(s, output_);
                deorate("I", smb, typ);
                i++;
                line[i] = ' ';
            }else{
                // cout<<" found /"<<" ";
                string smb = "/", typ = "operator";
                SymbolInfo s(smb, typ, line_number);
                s_table.Insert(s, output_);
                deorate("I", smb, typ);
            }
        }
        // %, %=
        if(line[i] == '%'){
            line[i] = ' ';
            if(i+1 < line.size() && line[i+1] == '='){
                // cout<<" found %="<<" ";
                string smb = "%=", typ = "operator";
                SymbolInfo s(smb, typ, line_number);
                s_table.Insert(s, output_);
                deorate("I", smb, typ);
                i++;
                line[i] = ' ';
            }else{
                // cout<<" found %"<<" ";
                string smb = "%", typ = "operator";
                SymbolInfo s(smb, typ, line_number);
                s_table.Insert(s, output_);
                deorate("I", smb, typ);
            }
        }
        // =, ==
        if(line[i] == '='){
            line[i] = ' ';
            if(i+1 < line.size() && line[i+1] == '='){
                // cout<<" found =="<<" ";
                string smb = "==", typ = "operator";
                SymbolInfo s(smb, typ, line_number);
                s_table.Insert(s, output_);
                deorate("I", smb, typ);
                i++;
                line[i] = ' ';
            }else{
                // cout<<" found ="<<" ";
                string smb = "=", typ = "operator";
                SymbolInfo s(smb, typ, line_number);
                s_table.Insert(s, output_);
                deorate("I", smb, typ);
            }
        }
        // !, !=
        if(line[i] == '!'){
            line[i] = ' ';
            if(i+1 < line.size() && line[i+1] == '='){
                // cout<<" found !="<<" ";
                string smb = "!=", typ = "operator";
                SymbolInfo s(smb, typ, line_number);
                s_table.Insert(s, output_);
                deorate("I", smb, typ);
                i++;
                line[i] = ' ';
            }else{
                // cout<<" found !"<<" ";
                string smb = "!", typ = "operator";
                SymbolInfo s(smb, typ, line_number);
                s_table.Insert(s, output_);
                deorate("I", smb, typ);
            }
        }

        // >, >=
        if(line[i] == '>'){
            line[i] = ' ';
            if(i+1 < line.size() && line[i+1] == '='){
                // cout<<" found !="<<" ";
                string smb = ">=", typ = "operator";
                SymbolInfo s(smb, typ, line_number);
                s_table.Insert(s, output_);
                deorate("I", smb, typ);
                i++;
                line[i] = ' ';
            }else{
                // cout<<" found !"<<" ";
                string smb = ">", typ = "operator";
                SymbolInfo s(smb, typ, line_number);
                s_table.Insert(s, output_);
                deorate("I", smb, typ);
            }
        }

        // <, <=
        if(line[i] == '<'){
            line[i] = ' ';
            if(i+1 < line.size() && line[i+1] == '='){
                // cout<<" found !="<<" ";
                string smb = "<=", typ = "operator";
                SymbolInfo s(smb, typ, line_number);
                s_table.Insert(s, output_);
                deorate("I", smb, typ);
                i++;
                line[i] = ' ';
            }else{
                // cout<<" found !"<<" ";
                string smb = "<", typ = "operator";
                SymbolInfo s(smb, typ, line_number);
                s_table.Insert(s, output_);
                deorate("I", smb, typ);
            }
        }
        // &, &&
        if(line[i] == '&'){
            line[i] = ' ';
            if(i+1 < line.size() && line[i+1] == '&'){
                // cout<<" found &&"<<" ";
                string smb = "&&", typ = "operator";
                SymbolInfo s(smb, typ, line_number);
                s_table.Insert(s, output_);
                deorate("I", smb, typ);
                i++;
                line[i] = ' ';
            }else{
                // cout<<" found &"<<" ";
                string smb = "&", typ = "operator";
                SymbolInfo s(smb, typ, line_number);
                s_table.Insert(s, output_);
                deorate("I", smb, typ);
            }
        }
        // |, ||
        if(line[i] == '|'){
            line[i] = ' ';
            if(i+1 < line.size() && line[i+1] == '|'){
                // cout<<" found ||"<<" ";
                string smb = "||", typ = "operator";
                SymbolInfo s(smb, typ, line_number);
                s_table.Insert(s, output_);
                deorate("I", smb, typ);
                i++;
                line[i] = ' ';
            }else{
                // cout<<" found |"<<" ";
                string smb = "|", typ = "operator";
                SymbolInfo s(smb, typ, line_number);
                s_table.Insert(s, output_);
                deorate("I", smb, typ);
            }
        }
                

    }
    // fclose(stdout);
    return line;
}


bool valid_end(string line, int i){
    if(i==line.size() || line[i]==' ' || line[i]==';' || line[i]=='{' || line[i]=='}' || line[i]=='(' || line[i]==')'){
        return true;
    }return false;
}
string findKeyword(string &line, SymbolTable &s_table, ofstream &output_){
    for(int i=0; i<line.size(); i++){
        // ..........if................
        if(i+1 < line.size() && line[i]=='i' && line[i+1]=='f' && valid_end(line, i+2)){
            line[i] = line[i+1] = ' ';
            // delete "( )"
            for(int j=i+2; j<line.size(); j++){
                if(line[j] == '('){
                    stack<char>stk; stk.push('(');
                    for(int k=j+1; k<line.size(); k++){
                        if(line[k] == ')' && stk.size() > 0){
                            if(stk.size() == 1){
                                line[j] = line[k] = ' ';
                                break;
                            }else stk.pop();
                        }else if(line[k] == '('){
                            stk.push('(');
                        }
                    }
                }
                i+=2;
                break;
            }
            // cout<< " found if ";
            string smb = "if", typ = "key word";
            SymbolInfo s(smb, typ, line_number);
            s_table.Insert(s, output_);
            deorate("I", smb, typ);
        }
        // ..........for................
        if(i+2 < line.size() && line[i]=='f' && line[i+1]=='o' && line[i+2]=='r' && valid_end(line, i+3)){
            line[i] = line[i+1] = line[i+2] = ' ';
            // delete "( )"
            for(int j=i+3; j<line.size(); j++){
                if(line[j] == '('){
                    stack<char>stk; stk.push('(');
                    for(int k=j+1; k<line.size(); k++){
                        if(line[k] == ')' && stk.size() > 0){
                            if(stk.size() == 1){
                                line[j] = line[k] = ' ';
                                break;
                            }else stk.pop();
                        }else if(line[k] == '('){
                            stk.push('(');
                        }
                    }
                }
                i+=3;
                break;
            }
            // cout<< " found for ";
            string smb = "for", typ = "key word";
            SymbolInfo s(smb, typ, line_number);
            s_table.Insert(s, output_);
            deorate("I", smb, typ);
        }
        // ..........int................
        if(i+2 < line.size() && line[i]=='i' && line[i+1]=='n' && line[i+2]=='t' && valid_end(line, i+3)){
            line[i] = line[i+1] = line[i+2] = ' ';
            i+=3;
            string smb = "int", typ = "key word";
            SymbolInfo s(smb, typ, line_number);
            s_table.Insert(s, output_);
            deorate("I", smb, typ);
        }
        // ..........float................
        if(i+4 < line.size() && line[i]=='f' && line[i+1]=='l' && line[i+2]=='o' && line[i+3]=='a' && line[i+4]=='t' && valid_end(line, i+5)){
            line[i] = line[i+1] = line[i+2] = line[i+3] = line[i+4] = ' ';
            i+=5;
            string smb = "float", typ = "key word";
            SymbolInfo s(smb, typ, line_number);
            s_table.Insert(s, output_);
            deorate("I", smb, typ);
        }
        // ..........double................
        if(i+5 < line.size() && line[i]=='d' && line[i+1]=='o' && line[i+2]=='u' && line[i+3]=='b' && line[i+4]=='l' && line[i+5]=='e' && valid_end(line, i+6)){
            line[i] = line[i+1] = line[i+2] = line[i+3] = line[i+4] = line[i+5] = ' ';
            i+=6;
            string smb = "double", typ = "key word";
            SymbolInfo s(smb, typ, line_number);
            s_table.Insert(s, output_);
            deorate("I", smb, typ);
        }
         // ..........else................
        if(i+3 < line.size() && line[i]=='e' && line[i+1]=='l' && line[i+2]=='s' && line[i+3]=='e'  && valid_end(line, i+4)){
            line[i] = line[i+1] = line[i+2] = line[i+3] = ' ';
            i+=4;
            while (i <line.size() && line[i] == ' '){
                i++;
            }
            if(i+1 < line.size() && line[i]=='i' && line[i+1]=='f' && valid_end(line, i+2)){
                line[i] = line[i+1] = ' ';
                // delete "( )"
                for(int j=i+2; j<line.size(); j++){
                    if(line[j] == '('){
                        stack<char>stk; stk.push('(');
                        for(int k=j+1; k<line.size(); k++){
                            if(line[k] == ')' && stk.size() > 0){
                                if(stk.size() == 1){
                                    line[j] = line[k] = ' ';
                                    break;
                                }else stk.pop();
                            }else if(line[k] == '('){
                                stk.push('(');
                            }
                        }
                    }
                    i+=2;
                    break;
                }
                string smb = "else if", typ = "key word";
                SymbolInfo s(smb, typ, line_number);
                s_table.Insert(s, output_);
                deorate("I", smb, typ);
            }else{
                string smb = "else", typ = "key word";
                SymbolInfo s(smb, typ, line_number);
                s_table.Insert(s, output_);
                deorate("I", smb, typ);
            }
        }
         // ..........void................
        if(i+3 < line.size() && line[i]=='v' && line[i+1]=='o' && line[i+2]=='i' && line[i+3]=='d'  && valid_end(line, i+4)){
            line[i] = line[i+1] = line[i+2] = line[i+3] = ' ';
            i+=4;
            string smb = "void", typ = "key word";
            SymbolInfo s(smb, typ, line_number);
            s_table.Insert(s, output_);
            deorate("I", smb, typ);
        }
        // ..........return................
        if(i+5 < line.size() && line[i]=='r' && line[i+1]=='e' && line[i+2]=='t' && line[i+3]=='u' && line[i+4]=='r' && line[i+5]=='n' && valid_end(line, i+6)){
            line[i] = line[i+1] = line[i+2] = line[i+3] = line[i+4] = line[i+5] = ' ';
            i+=6;
            string smb = "return", typ = "key word";
            SymbolInfo s(smb, typ, line_number);
            s_table.Insert(s, output_);
            deorate("I", smb, typ);
        }
        // ..........break................
        if(i+4 < line.size() && line[i]=='b' && line[i+1]=='r' && line[i+2]=='e' && line[i+3]=='a' && line[i+4]=='k' && valid_end(line, i+5)){
            line[i] = line[i+1] = line[i+2] = line[i+3] = line[i+4] = ' ';
            i+=5;
            string smb = "break", typ = "key word";
            SymbolInfo s(smb, typ, line_number);
            s_table.Insert(s, output_);
            deorate("I", smb, typ);
        }

    }
    return line;
}


bool isNumber(char x){
    if(x>='0' && x<='9') return true;
    return false;
}
bool isLetter(char x){
    if((x>='a' && x<='z') || (x>='A' && x<='Z')) return true;
    return false;
}

string findFunction(string &line, SymbolTable &s_table, ofstream &output_){
    for(int i=0; i<line.size(); i++){
        if(line[i] == '('){
            // deleting corresponding )
            stack<char>stk; stk.push('(');
            for(int k=i+1; k<line.size(); k++){
                if(line[k] == ')' && stk.size() > 0){
                    if(stk.size() == 1){
                        line[i] = line[k] = ' ';
                        break;
                    }else stk.pop();
                }else if(line[k] == '('){
                    stk.push('(');
                }
            }

            // getting function name
            int j = i-1;
            while(j>=0 && line[j] == ' '){// gap eleminating
                j--;
            }
            string fn_mn = "";
            while (j>=0 && (isNumber(line[j]) || isLetter(line[j]) )){
                fn_mn += line[j];
                line[j] = ' ';
                j--;
            }
            reverse(fn_mn.begin(), fn_mn.end());
            if(isLetter(fn_mn[0]) == false && fn_mn[0] != '_'){
                // cout<<"Error at line = "<<line_number<<endl;
            }else{
                string smb = fn_mn, typ = "function";
                SymbolInfo s(smb, typ, line_number);
                s_table.Insert(s, output_);
                deorate("I", smb, typ);
            }
        }
    }
    return line;
}


string  finfIdentifier(string &line, SymbolTable &s_table, ofstream &output_){
    for(int i=0; i<line.size(); i++){
        // if(i<line.size() && (line[i])){
        //     while(i<line.size() && (isNumber(line[i]) || isLetter(line[i]) )){
        //         line[i] = ' ';
        //         i++;
        //     }
        //     // cout<<"Error at line = "<<line_number<<endl;
        // }
        if(i<line.size() && (isLetter(line[i]) || line[i]=='_') && (i==0 || line[i-1]==' ' || line[i-1] == ',' || line[i-1] == ';' || line[i-1] == '(' || line[i-1] == '{' || line[i-1] == ')' || line[i-1] == '}')){
            string idf_name = "";
            while(i<line.size() && (isNumber(line[i]) || isLetter(line[i]) )){
                idf_name += line[i];
                line[i] = ' ';
                i++;
            }
            if(valid_end(line, i)){
                string smb = idf_name, typ = "Identifier";
                SymbolInfo s(smb, typ, line_number);
                s_table.Insert(s, output_);
                deorate("I", smb, typ);
            }
        }
    }
    return line;
}

void remove_cotation_and_number_include(string &line){
    for(int i=0; i<line.size(); i++){
        if(line[i] == '"'){
            line[i] = ' ';
            i++;
            while (i<line.size()){
                if(line[i] == '"'){
                    line[i] = ' '; 
                    i++; break;
                }
                line[i] = ' ';
                i++;
            }
            
        }
        if(i<line.size() && isNumber(line[i]) && (i==0 || line[i-1]==' ' || line[i-1] == ',' || line[i-1] == ';' || line[i-1] == '(' || line[i-1] == '{' || line[i-1] == ')' || line[i-1] == '}' || line[i-1] == '=' || line[i-1] == '<' || line[i-1] == '>')){
            int j = i;
            while (j < line.size() && isNumber(line[j])){
                j++;
            }
            if(j == line.size() || line[j] == ',' || line[j] == ';' || line[j] == '}' || line[j] == ')' || line[j] == ' ' || line[j] == '{' || line[j] == '('){
                for( ; i<j; i++){
                    line[i] = ' ';
                }
            }
            
        }
        if(i<line.size() && line[i] == '#'){
            for(; i<line.size(); i++) line[i] = ' ';
        }
    }
}
void find_error(string &line){
    bool er = false;
    for(int i=0; i<line.size(); i++){
        if(line[i] == ';' || line[i] == ',' || line[i] == ' ' || line[i] == '?' || line[i] == '{' || line[i] == '}' || line[i] == '\n' || line[i] == '\t' || line[i] == '\v'){
            line[i] = ' ';
        }else er = true;
    }
    if(er == true) cout<<"error at line: "<<line_number<<endl;
}
int main() {
    // cout<<"Which hash technique you want to use ?\n Enter 1 0r 2 : ";
    int tnq; //cin>>tnq;
    tnq = 2;
    ofstream output_operator;
    ofstream output_keyword;
    ofstream output_function;
    ofstream output_identifier;
    output_operator.open("output_operator.txt");
    output_keyword.open("output_keyword.txt");
    output_function.open("output_function.txt");
    output_identifier.open("output_identifier.txt");

    freopen("input_code.txt","r",stdin);

    SymbolTable s_table(tnq); 

    string line;
    
    while(getline(cin,line)){
        remove_cotation_and_number_include(line);
        
        findOperator(line, s_table, output_operator);

        findKeyword(line, s_table, output_keyword);
        findFunction(line, s_table, output_function);
        finfIdentifier(line, s_table, output_identifier);
        find_error(line);
        line_number++;
    }

    output_operator.close();
    output_keyword.close();
    output_function.close();
    output_identifier.close();

    return 0;
}