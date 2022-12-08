#include <stdio.h>
#include <iostream>
#include "main.h"
#include <conio.h>
#include <complex>

using namespace std;

template<typename T>
ostream& operator<<(ostream& os, Equalization<T> obj)
{
    bool FirstStart = true;
    cout << "\nНаша последовательность: ";
    while (obj.head) {
        if (obj.head->coefficent == T(0))
        {
            obj.DeleteElement(obj.head->degree);
            FirstStart = true;
        }
        if (!FirstStart && obj.head->coefficent > T(0)) cout << "+";
        if (obj.head->coefficent != T(1)) cout << obj.head->coefficent;
        if (obj.head->degree != 0) cout << "x";
        else cout << obj.head->coefficent;
        if (obj.head->degree < 0) { cout << "^(" << obj.head->degree << ")"; }
        else if (obj.head->degree != 1 && obj.head->degree != 0) cout << "^" << obj.head->degree;

        obj.head = obj.head->next;
        FirstStart = false;
    }
    cout << "\n";
    return os;
}

ostream& operator<< (ostream& os, Equalization<complex<float>> obj)
{
    bool FirstStart = true;
    cout << "\nНаша последовательность: ";
    while (obj.head) {
        if (real(obj.head->coefficent) == 0 and imag(obj.head->coefficent) == 0)
        {
            obj.DeleteElement(obj.head->degree);
            FirstStart = true;
        }
        if (!FirstStart && real(obj.head->coefficent) > 0) cout << "+";
        if (obj.head->coefficent != complex<float>(1)) cout << obj.head->coefficent;
        if (obj.head->degree != 0) cout << "x";
        else cout << obj.head->coefficent;
        if (obj.head->degree < 0) { cout << "^(" << obj.head->degree << ")"; }
        else if (obj.head->degree != 1 && obj.head->degree != 0) cout << "^" << obj.head->degree;

        obj.head = obj.head->next;
        FirstStart = false;
    }
    cout << "\n";
    return os;
}

ostream& operator<< (ostream& os, Equalization<complex<double>> obj)
{
    bool FirstStart = true;
    cout << "\nНаша последовательность: ";
    while (obj.head) {
        if (real(obj.head->coefficent) == 0 and imag(obj.head->coefficent) == 0)
        {
            obj.DeleteElement(obj.head->degree);
            FirstStart = true;
        }
        if (!FirstStart && real(obj.head->coefficent) > 0) cout << "+";
        if (obj.head->coefficent != complex<double>(1)) cout << obj.head->coefficent;
        if (obj.head->degree != 0) cout << "x";
        else cout << obj.head->coefficent;
        if (obj.head->degree < 0) { cout << "^(" << obj.head->degree << ")"; }
        else if (obj.head->degree != 1 && obj.head->degree != 0) cout << "^" << obj.head->degree;

        obj.head = obj.head->next;
        FirstStart = false;
    }
    cout << "\n";
    return os;
}


/**template<typename T>
void MenuInputComplex()
{
    system("clear");
    cout << "Create poilynominal menu\n\n"
        << endl;
    cout << "Order of Equalization: " << endl;
    long long OrderOfPolynominal = 0;
    cin >> OrderOfPolynominal;
    Equalization<T>* Newbie = NULL;
    try
    {
        Newbie = new Equalization<T>(OrderOfPolynominal);
    }
    catch (exception e)
    {
        clog << "An exception occured" << endl;
    }
    double R = 0;
    double I = 0;
    for (int i = OrderOfPolynominal; i >= 0; i--)
    {
        cout << "Coef by (input like : *real *img)" << i << ":\n";
        string str;
        cin >> str;
        R = stoi(str);
        cin >> str;
        I = stoi(str);
        Newbie->Set(i, T(R, I));
    }
    cout << "Created polynominal: " << *Newbie << endl;
    cout << "Press any key" << endl;
    getch();
    //Menu1(Newbie);
}
*/
template <class T>

