#include <iostream>
#include <string>
#include <bitset>
#include <unordered_map>
#define null NULL
using namespace std;
unordered_map<string, short> lable;
vector<pair<string, short>> v;
short AC, PC;
bool E = false;

typedef struct {
    bool I;
    string op_code, lable_name;
    string data;
} instruction;
instruction M[10000] = {};

short exData(string s, bool I) {
    short i, r = -1;
    bool pure_number = true;
    for (i = 0; i < s.length(); ++i)
        if (s[i] > '9' || s[i] < '0') {
            pure_number = false;
            break;
        }
    if (pure_number) r = stoi(s);
    else   r = stoi(M[lable[s]].data);
    if (I) {
        r = stoi(M[r].data);
    }
    return r;
}
short BUN(bool I, short t) {
    short i, loc = -1;
    bool pure_num = true;
    for (i = 0; i < M[t].data.length(); ++i)
        if (M[t].data[i] > '9' || M[t].data[i] < '0') {
            pure_num = false;
            break;
        }
    if (pure_num)
        loc = stoi(M[t].data) - 1;
    else
        loc = lable[M[t].data] - 1;
    if (!I)
        return loc;
    loc++;
    pure_num = true;
    for (i = 0; i < M[loc].data.length(); ++i)
        if (M[loc].data[i] > '9' || M[loc].data[i] < '0') {
            pure_num = false;
            break;
        }
    if (pure_num)
        return stoi(M[loc].data) - 1;
    else
        return lable[M[loc].data] - 1;
}
short BSA(bool I, short t) {
    short i, loc = -1;
    bool pure_num = true;
    for (i = 0; i < M[t].data.length(); ++i)
        if (M[t].data[i] > '9' || M[t].data[i] < '0') {
            pure_num = false;
            break;
        }
    if (pure_num)
        loc = stoi(M[t].data) - 1;
    else
        loc = lable[M[t].data] - 1;
    if (!I) {
        M[loc + 1].data = to_string(t + 1);
        return loc;
    }
    loc++;
    pure_num = true;
    for (i = 0; i < M[loc].data.length(); ++i)
        if (M[loc].data[i] > '9' || M[loc].data[i] < '0') {
            pure_num = false;
            break;
        }
    if (pure_num)
        loc = stoi(M[loc].data);
    else
        loc = lable[M[loc].data];
    M[loc].data = to_string(t + 1);
    return loc - 1;
}
void STA(bool I, short t) {
    if (I) {
        short i;
        bool pure_num = true;
        string s = M[lable[M[t].data]].data;
        for (i = 0; i < s.length(); ++i)
            if (s[i] > '9' || s[i] < '0') {
                pure_num = false;
                break;
            }
        if (pure_num)
            M[stoi(s)].data = to_string(AC);
        else {
            M[lable[s]].data = to_string(AC);
        }
        return;
    }
    M[lable[M[t].data]].data = to_string(AC);
    return;
}
void bin(short a) {
    printf("0b");
    for (short i = 16; i >= 0; --i) {
        short t = (a >> i) & 1;
        printf("%d", t);
    }
}
short print_type;
void print_result() {
    printf("%s\t%s\t%d\t%s\n", M[PC - 1].lable_name.c_str(), M[PC - 1].op_code.c_str(), !!M[PC - 1].I, M[PC - 1].data.c_str());
    for (short i = 0; i < v.size(); ++i) {
        //cout << i + 1 << ".\t" << v[i].first << "\t" << M[v[i].second].data << '(' << v[i].second << ")\n";
        printf("%d.\t", i + 1);
        cout << v[i].first << "\t";
        printf("\t(0x%X)\t", v[i].second);
        if (print_type == 16)
            printf("0x%04X", (short)stoi(M[v[i].second].data));
        else if (print_type == 2)
            bin(stoi(M[v[i].second].data));
        else if (print_type == 10)
            printf("%d", (short)stoi(M[v[i].second].data));
        printf("\n");
    }
    printf("AC : ");
    if (print_type == 2)
        bin(AC);
    else if (print_type == 10)
        printf("%d", AC);
    else if (print_type == 16)
        printf("0x%X", AC);
    printf("\nPC : 0x%X\nE  : %d\n-----------------------------------------------\n", PC, !!E);
    return;
}
int main()
{
    //indirect?   op-code name   lable-name   data
    //M[2] = { 0,"DEC","CTR","-8" };
    //M[3] = { 0,"DEC","X","15" };
    //M[4] = { 0,"DEC","Y","11" };
    //M[5] = { 0,"DEC","P","0" };

    //M[6] = { 0,"CLE","LOP","0" };
    //M[7] = { 0,"LDA","","Y" };
    //M[8] = { 0,"CIR","","0" };
    //M[9] = { 0,"STA","","Y" };
    //M[10] = { 0,"SZE","","0" };
    //M[11] = { 0,"BUN","","ONE" };
    //M[12] = { 0,"BUN","","ZRO" };
    //M[13] = { 0,"LDA","ONE","X" };
    //M[14] = { 0,"ADD","","P" };
    //M[15] = { 0,"STA","","P" };
    //M[16] = { 0,"CLE","","" };
    //M[17] = { 0,"LDA","ZRO","X" };
    //M[18] = { 0,"CIL","","0" };
    //M[19] = { 0,"STA","","X" };
    //M[20] = { 0,"ISZ","","CTR" };
    //M[21] = { 0,"BUN","","LOP" };
    //M[22] = { 0,"HLT","","0" };


    //first pass for Labling.
    for (short i = 0; i < 10000; ++i)
        if (M[i].lable_name.length() > 0) {
            lable.insert({ M[i].lable_name,i });
            if (!M[i].op_code.compare("HEX") || !M[i].op_code.compare("DEC"))
                v.push_back({ M[i].lable_name,i });
        }

    bool P = true; //결과 프린트?
    print_type = 10; ////////////////////////////////////////////////////////// 10,16,2만 가능

    //second pass for Executing.
    for (PC = 0; PC < 10000; ++PC)
        if (M[PC].op_code.length() > 0) //명령 있음
        {
            if (!M[PC].op_code.compare("AND")) {
                if (P)   print_result();
                short Data = exData(M[PC].data, M[PC].I);
                AC = AC & Data;
            }
            else if (!M[PC].op_code.compare("ADD")) {
                if (P)   print_result();
                short Data = exData(M[PC].data, M[PC].I);
                AC = AC + Data; //E 무시
            }
            else if (!M[PC].op_code.compare("LDA")) {
                if (P)   print_result();
                short Data = exData(M[PC].data, M[PC].I);
                AC = Data;
            }
            else if (!M[PC].op_code.compare("STA")) {
                if (P)   print_result();
                STA(M[PC].I, PC);
            }
            else if (!M[PC].op_code.compare("BUN")) {
                if (P)   print_result();
                PC = BUN(M[PC].I, PC);
            }
            else if (!M[PC].op_code.compare("BSA")) {
                if (P)   print_result();
                PC = BSA(M[PC].I, PC);
            }
            else if (!M[PC].op_code.compare("ISZ")) {
                if (P)   print_result();
                M[lable[M[PC].data]].data = to_string(stoi(M[lable[M[PC].data]].data) + 1);
                if (!stoi(M[lable[M[PC].data]].data))   PC++;
            }
            else if (!M[PC].op_code.compare("CLA")) {
                if (P)   print_result();
                AC = 0;
            }
            else if (!M[PC].op_code.compare("CLE")) {
                if (P)   print_result();
                E = 0;
            }
            else if (!M[PC].op_code.compare("CMA")) {
                if (P)   print_result();
                AC = ~AC;
            }
            else if (!M[PC].op_code.compare("CME")) {
                if (P)   print_result();
                E = E ^ 1;
            }
            else if (!M[PC].op_code.compare("CIR")) {
                if (P)   print_result();
                bool t = AC & 1;
                AC = AC >> 1;
                AC = AC | (E << 15);
                E = t;
            }
            else if (!M[PC].op_code.compare("CIL")) {
                if (P)   print_result();
                bool t = AC & (1 << 15);
                AC = AC << 1;
                AC = AC + E;
                E = t;
            }
            else if (!M[PC].op_code.compare("INC")) {
                if (P)   print_result();
                AC++;
            }
            else if (!M[PC].op_code.compare("SPA")) {
                if (P)   print_result();
                if (AC > 0)   PC++;
            }
            else if (!M[PC].op_code.compare("SNA")) {
                if (P)   print_result();
                if (AC < 0)   PC++;
            }
            else if (!M[PC].op_code.compare("SZA")) {
                if (P)   print_result();
                if (!AC)   PC++;
            }
            else if (!M[PC].op_code.compare("SZE")) {
                if (P)   print_result();
                if (!E)   PC++;
            }
            else if (!M[PC].op_code.compare("HLT")) {
                print_result();
                exit(0);
            }
        }
}
