#include <iostream>
#include <string>
using namespace std;

bool NAND(bool x, bool y)
{
    if (x == 1 && y == 1)
        return 0;
    else
        return 1;
}

bool OR(bool x, bool y)
{
    bool t1 = NAND(x, x);
    bool t2 = NAND(y, y);
    bool rez = NAND(t1, t2);
    return rez;
}

bool AND(bool x, bool y)
{
    bool t1 = NAND(x, y);
    bool rez = NAND(t1, t1);
    return rez;
}

bool XOR(bool x, bool y)
{
    bool t1 = NAND(x, y);
    bool t2 = NAND(t1, x);
    bool t3 = NAND(t1, y);
    bool rez = NAND(t2, t3);
    return rez;
}

bool NOT(bool x)
{
    bool rez = NAND(x, x);
    return rez;
}

bool NOR(bool x, bool y)
{
    bool t1 = NAND(x, x);
    bool t2 = NAND(y, y);
    bool t3 = NAND(t1, t2);
    bool rez = NAND(t3, t3);
    return rez;
}

void HALFADDER(bool x, bool y, bool &sum, bool &carry)
{
    sum = XOR(x, y);
    carry = AND(x, y);
}

void FULLADDER(bool x, bool y, bool CarryIn, bool &sum, bool &CarryOut)
{
    bool sum1, carry1, carry2;
    HALFADDER(x, y, sum1, carry1);
    HALFADDER(sum1, CarryIn, sum, carry2);

    CarryOut = OR(carry1, carry2);
}

bool MUX(bool l1, bool l2, bool l3, bool l4, bool M0, bool M1)
{
    bool nM0 = NOT(M0);
    bool nM1 = NOT(M1);

    bool t1a = AND(nM0, nM1);
    bool t1 = AND(l1, t1a);

    bool t2a = AND(nM0, M1);
    bool t2 = AND(l2, t2a);

    bool t3a = AND(M0, nM1);
    bool t3 = AND(l3, t3a);

    bool t4a = AND(M0, M1);
    bool t4 = AND(l4, t4a);

    bool t12 = OR(t1, t2);
    bool t34 = OR(t3, t4);

    bool rez = OR(t12, t34);
    return rez;
}

void ONEBITALU(bool A, bool B, bool ENA, bool ENB, bool M0, bool M1, bool CarryIn, bool &CarryOut, bool &Output)
{
    bool A1 = AND(A, ENA);
    bool B1 = AND(B, ENB);

    bool xorRez = XOR(A1, B1);
    bool orRez = OR(A1, B1);
    bool notBRez = NOT(B1);

    bool sum;
    FULLADDER(A1, B1, CarryIn, sum, CarryOut);

    Output = MUX(xorRez, orRez, notBRez, sum, M0, M1);
}

void DECODER(bool D[3], bool O[8])
{
    bool D0 = D[0];
    bool D1 = D[1];
    bool D2 = D[2];

    bool nD0 = NOT(D0);
    bool nD1 = NOT(D1);
    bool nD2 = NOT(D2);

    O[0] = AND(AND(nD0, nD1), nD2);
    O[1] = AND(AND(nD0, nD1), D2);
    O[2] = AND(AND(nD0, D1), nD2);
    O[3] = AND(AND(nD0, D1), D2);
    O[4] = AND(AND(D0, nD1), nD2);
    O[5] = AND(AND(D0, nD1), D2);
    O[6] = AND(AND(D0, D1), nD2);
    O[7] = AND(AND(D0, D1), D2);
}

void SHIFTER(bool A[8], bool ctrl, bool O[8])
{
    bool nctrl = NOT(ctrl);

    O[0] = OR(AND(A[1], nctrl), AND(0, ctrl));
    O[1] = OR(AND(A[2], nctrl), AND(A[0], ctrl));
    O[2] = OR(AND(A[3], nctrl), AND(A[1], ctrl));
    O[3] = OR(AND(A[4], nctrl), AND(A[2], ctrl));
    O[4] = OR(AND(A[5], nctrl), AND(A[3], ctrl));
    O[5] = OR(AND(A[6], nctrl), AND(A[4], ctrl));
    O[6] = OR(AND(A[7], nctrl), AND(A[5], ctrl));
    O[7] = OR(AND(0, nctrl), AND(A[6], ctrl));
}

void ADD8(bool A[8], bool B[8], bool O[8], bool &carry)
{
    bool c1, c2, c3, c4, c5, c6, c7;
    FULLADDER(A[0], B[0], 0, O[0], c1);
    FULLADDER(A[1], B[1], c1, O[1], c2);
    FULLADDER(A[2], B[2], c2, O[2], c3);
    FULLADDER(A[3], B[3], c3, O[3], c4);
    FULLADDER(A[4], B[4], c4, O[4], c5);
    FULLADDER(A[5], B[5], c5, O[5], c6);
    FULLADDER(A[6], B[6], c6, O[6], c7);
    FULLADDER(A[7], B[7], c7, O[7], carry);
}

void SUB8(bool A[8], bool B[8], bool O[8], bool &carry)
{
    bool one[8] = {1,0,0,0,0,0,0,0};
    bool c;
    bool temp[8];
    bool Bnot[8];

    for (int i = 0; i < 8; i++)
        Bnot[i] = NOT(B[i]);

    ADD8(Bnot, one, temp, c);
    ADD8(A, temp, O, carry);
}

void COMPARE(bool A[8], bool B[8], bool &F)
{
    bool e0 = NOT(XOR(A[0], B[0]));
    bool e1 = NOT(XOR(A[1], B[1]));
    bool e2 = NOT(XOR(A[2], B[2]));
    bool e3 = NOT(XOR(A[3], B[3]));
    bool e4 = NOT(XOR(A[4], B[4]));
    bool e5 = NOT(XOR(A[5], B[5]));
    bool e6 = NOT(XOR(A[6], B[6]));
    bool e7 = NOT(XOR(A[7], B[7]));

    bool t1 = AND(e0, e1);
    bool t2 = AND(e2, e3);
    bool t3 = AND(e4, e5);
    bool t4 = AND(e6, e7);

    bool t5 = AND(t1, t2);
    bool t6 = AND(t3, t4);

    F = AND(t5, t6);
}

void ALU8BIT(bool A[8], bool B[8], bool D[3], bool ctrl, bool Out[8], bool& cflag, bool& F)
{
    bool Dec[8];
    DECODER(D, Dec);

    bool carry = 0;
    if (Dec[3]) carry = 1;

    for (int i = 0; i < 8; i++)
    {
        bool ENA = 1;
        bool ENB = 1;
        bool M0 = 0;
        bool M1 = 0;

        if (Dec[6])
        {
            M0 = 1;
            M1 = 1;
        }

        bool Bin = B[i];
        if (Dec[3])
        {
            M0 = 1;
            M1 = 1;
            Bin = NOT(B[i]);
        }

        if (Dec[5])
        {
            SHIFTER(A, ctrl, Out);
        }

        if (Dec[1])
        {
            COMPARE(A, B, F);
        }

        ONEBITALU(A[i], Bin, ENA, ENB, M0, M1, carry, carry, Out[i]);
    }

    cflag = carry;
}

void STRINGTOBITS(string s, bool X[8])
{
    for (int i = 0; i < 8; i++)
        X[i] = 0;

    if (s.length() != 8) {
        cout << "Input must contain exactly 8 bits." << endl;
        return;
    }

    for (int i = 0; i < 8; i++) {
        if (s[7 - i] == '1')
            X[i] = 1;
        else
            X[i] = 0;
    }
}

void PRINTBITS(bool X[8])
{
    for (int i = 7; i >= 0; i--)
        cout << X[i];
}

int main()
{
    bool A[8] = {0,0,0,0,0,0,0,0};
    bool B[8] = {0,0,0,0,0,0,0,0};
    bool O[8] = {0,0,0,0,0,0,0,0};

    string Astr = "00000001";
    string Bstr = "00000010";

    STRINGTOBITS(Astr, A);
    STRINGTOBITS(Bstr, B);

    bool D[3] = {0, 1, 1};
    bool F = 0;
    bool ctrl = 0;
    bool carry = 0;

    ALU8BIT(A, B, D, ctrl, O, carry, F);

    cout << "A: ";
    PRINTBITS(A);
    cout << endl;

    cout << "B: ";
    PRINTBITS(B);
    cout << endl;

    cout << "Output: ";
    PRINTBITS(O);
    cout << endl;

    cout << "F: " << F << endl;
    cout << "Carry: " << carry << endl;

    return 0;
}