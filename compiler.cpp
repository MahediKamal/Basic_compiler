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

class SymbolInfo{
public:
    string smbl;
    string typ;
    SymbolInfo(string a, string b){
        smbl = a; typ = b;
    }
    SymbolInfo(){}
    void ShowIfo(){
        cout<<"<"<<smbl<<","<<typ<<">";
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
    pair<lli,lli> Insert(SymbolInfo s){// inserting if was not inserted before and returning inserted position
        if(LookUp(s).ff != -1){// not inserting same dta 
            pair<lli,lli> pos = make_pair(-1, -1);
            return pos;// returning an invalid idx
        }
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
        SymbolInfo dummy("-1-1", "-1-1");
        return dummy;
    }
};

void deorate(string dc = NULL, string smb = "", string typ = ""){
    cout<<"Input :"<<dc<<" "<<smb<<" "<<typ<<endl<<"output :"<<endl;
}

int main() {
    cout<<"Which hash technique you want to use ?\n Enter 1 0r 2 : ";
    int tnq; cin>>tnq;

    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
    SymbolTable s_table(tnq); 

    string dc;
    while(cin>>dc){
        //  cin>>dc;
        if(dc[0] == 'I'){
            string smb, typ; cin>>smb >>typ;
            deorate(dc, smb, typ);
            SymbolInfo s(smb, typ);
            s_table.Insert(s);
        }else if(dc[0] == 'P'){
            deorate(dc);
            s_table.Print();
        }else if(dc[0] == 'L'){
            string smb; cin>>smb;
            deorate(dc, smb);
            SymbolInfo tmp(smb, "grbz");
            pair<lli,lli> pos = s_table.LookUp(tmp);
            if(pos.ff != -1){
                s_table.get_by_position(pos.ff, pos.ss).ShowIfo();
                cout<<" Found at "<<pos.ff<<","<<pos.ss<<endl;
            }else{
                cout<<smb <<" not Found"<<endl;
            }

        }else{
            string smb; cin>>smb;
            deorate(dc, smb);
            SymbolInfo tmp(smb, "grbz");
            s_table.Delete(tmp);
        }
        cout<<endl<<endl;
    }
}
