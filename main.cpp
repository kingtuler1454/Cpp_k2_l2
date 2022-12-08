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
void Menu1() {
    try
    {
        double degree;
        T coefficent;
        int choice;

        cout << "Введите коэфффицент первого элемента: " << endl;
        cin>>coefficent;
        cout << "Введите степень первого элемента: " << endl;
        cin>>degree;
        Equalization<T> A(coefficent, degree);
        bool flag = true;
        while (flag) {
            system("cls");
            A.DeleteElement(0);
            cout << A;
            cout << "Выберите действие:\n1)Добавить новый элемент\n2)Умножить на скаляр\n3)Вычислить х\n4)Найти производную\n5)Сумма с другим многочленом\n6)Вычесть из него другой многочлен\n7)Средактировать коэффицент\n8)Удалить элемент\n9)Сравнить многочлены\n10)Выход\n";
            cin>>choice;
            if (choice == 1)
            {
                cout << "Введите коэффицент нового элемента: " << endl;
                cin>>coefficent;
                cout << "Введите степень нового элемента: " << endl;
                cin>>degree;
                A.Set(coefficent, degree);
            }
            else if (choice == 2) {
                cout << "Введите степень на: " << endl;
                cin>>degree;
                A.Multiplication(degree);
            }
            else if (choice == 3) {
                cout << "Введите значение на которое умножаем: " << endl;
                cin>>degree;
                A.Calculation(degree);
            }
            else if (choice == 4) {
                A.Derivative();
            }
            else if (choice == 5 || choice == 6) {
                bool SumOperation = false;
                if (choice == 5) SumOperation = true;
                Equalization<T> B(0, 0);
                do {
                    cout << "Введите коэффицент первого элемента нового многочлена: ";
                    cin>>coefficent;
                    cout << "Введите степень первого элемента нового многочлена: ";
                    cin>>degree;
                    B.Set(coefficent, degree);
                    cout << "Хотите добавить ещё один элемент? \n1)Да\n2)Нет\n";
                    cin>>choice;
                } while (choice == 1);
                if (SumOperation) A + B;
                else A - B;
            }
            else if (choice == 7) {
                cout << "Выберите степень выбранного элемента";
                cin>>degree;
                A[degree];
            }
            else if (choice == 8) {
                cout << "Выберите степень выбранного элемента: ";
                cin>>degree;
                if (A.DeleteElement(degree) == 0) cout << "Нет такого элемента :(" << endl;
            }
            else if (choice == 9) {
                Equalization<T> B(0, 0);
                do {
                    cout << "Введите точность, пример 0.001: ";
                    cin >> A.epsilon;
                    cout << "Введите коэффицент первого элемента нового многочлена: ";
                    cin>>coefficent;
                    cout << "Введите степень первого элемента нового многочлена: ";
                    cin>>degree;
                    B.Set(coefficent, degree);
                    cout << "Хотите добавить ещё один элемент? \n1)Да\n2)Нет\n";
                    cin>>choice;
                } while (choice == 1);
                if (A == B) cout << "\nМногочлены равны\n";
                else cout << "\nРавнества между многочленами нет\n";
            }
            else if (choice == 10) {
                flag = false;
            }
            else {
                cout << "Нет такого варианта\n";
                
            }
            cout << "Для продолжения нажмите любую клавишу\n";
            _getch();
        }
    }
    catch (EClassException& err)
    {
        err.Print();
    }

}

int main()
{
    setlocale(LC_ALL, "RUS");
    while (true) {
        cout << "Выберите тип:" << endl;;
        cout << "1)int" << endl;;
        cout << "2)float" << endl;;
        cout << "3)double" << endl;;
        cout << "4)complex (float)" << endl;;
        cout << "5)complex (double)" << endl;;
        cout << "6)Выход " << endl;;
        int Choice;
        cin >> Choice;
        system("cls");
        switch (Choice)
        {
        case 1:
            Menu1<int>();
            break;
        case 2:
            Menu1<float>();
            break;
        case 3:
            Menu1<double>();
            break;
        case 4:
            Menu1<std::complex<float>>();
            break;
        case 5:
            Menu1<complex<double>>();
            break;
        case 6:
            return EXIT_SUCCESS;
        default:
            break;
        }
        system("cls");
    }
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
/*
template<typename T>
void Menu1() {
    try
    {
        double degree;
        T coefficent;
        int choice;

        cout << "Введите коэфффицент первого элемента: " << endl;
        coefficent = CheckCoefficient<T>();
        cout << "Введите степень первого элемента: " << endl;
        degree = CheckDegree();
        Equalization<T> A(coefficent, degree);
        bool flag = true;
        while (flag) {
            system("cls");
            A.DeleteElement(0);
            cout << A;
            cout << "Выберите действие:\n1)Добавить новый элемент\n2)Умножить на скаляр\n3)Вычислить х\n4)Найти производную\n5)Сумма с другим многочленом\n6)Вычесть из него другой многочлен\n7)Средактировать коэффицент\n8)Удалить элемент\n9)Сравнить многочлены\n10)Выход\n";
            choice = CheckChoise();
            if (choice == 1)
            {
                cout << "Введите коэффицент нового элемента: " << endl;
                coefficent = CheckCoefficient<T>();
                cout << "Введите степень нового элемента: " << endl;
                degree = CheckDegree();
                A.Set(coefficent, degree);
            }
            else if (choice == 2) {
                cout << "Введите степень на: " << endl;
                degree = CheckDegree();
                A.Multiplication(degree);
            }
            else if (choice == 3) {
                cout << "Введите значение на которое умножаем: " << endl;
                degree = CheckDegree();
                A.Calculation(degree);
            }
            else if (choice == 4) {
                A.Derivative();
            }
            else if (choice == 5 || choice == 6) {
                bool SumOperation = false;
                if (choice == 5) SumOperation = true;
                Equalization<T> B(0, 0);
                do {
                    cout << "Введите коэффицент первого элемента нового многочлена: ";
                    coefficent = CheckCoefficient<T>();
                    cout << "Введите степень первого элемента нового многочлена: ";
                    degree = CheckDegree();
                    B.Set(coefficent, degree);
                    cout << "Хотите добавить ещё один элемент? \n1)Да\n2)Нет\n";
                    choice = CheckChoise();
                } while (choice == 1);
                if (SumOperation) A + B;
                else A - B;
            }
            else if (choice == 7) {
                cout << "Выберите степень выбранного элемента";
                degree = CheckDegree();
                A[degree];
            }
            else if (choice == 8) {
                cout << "Выберите степень выбранного элемента: ";
                degree = CheckDegree();
                if (A.DeleteElement(degree) == 0) cout << "Нет такого элемента :(" << endl;
            }
            else if (choice == 9) {
                flag = false;
            }
            else {
                system("CLS");
            }
        }
    }
    catch (EClassException& err)
    {
        err.Print();
    }

}

int main()
{
    setlocale(LC_ALL, "RUS");
    while (true) {
        cout << "Выберите тип:" << endl;;
        cout << "1)int" << endl;;
        cout << "2)float" << endl;;
        cout << "3)double" << endl;;
        cout << "4)complex (float)" << endl;;
        cout << "5)complex (double)" << endl;;
        cout << "6)Выход " << endl;;
        int Choice;
        cin >> Choice;
        system("cls");
        switch (Choice)
        {
        case 1:
            Menu1<int>();
            break;
        case 2:
            Menu1<float>();
            break;
        case 3:
            Menu1<double>();
            break;
        case 4:
            Menu1<std::complex<float>>();
            break;
        case 5:
            Menu1<complex<double>>();
            break;
        case 6:
            return EXIT_SUCCESS;
        default:
            break;
        }
        system("cls");
    }
}
*/