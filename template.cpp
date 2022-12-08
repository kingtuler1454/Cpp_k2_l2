#include "main.h"
#include <stdio.h>
#include <iostream>
#include <complex>


using namespace std;

template<typename T>
Equalization<T>::Equalization(T coefficent, double degree) {
    if (coefficent != T(0)) {
        this->head = new list<T>;
        this->head->degree = degree;
        this->head->coefficent = coefficent;
        this->head->next = NULL;
        count = 1;
    }
}



template<typename T>
Equalization<T>:: ~Equalization() {
    list<T>* p;
    count = 0;
    while (p = head)
    {
        head = p->next;
        delete p;
    }
}

template<typename T>
list<T>* Equalization<T>::GetHead()
{
    return head;
}

template<typename T>
void Equalization<T>::SetHead(list<T>* head) { this->head = head; }

template<typename T>
bool Equalization<T>::DetectOldDegree(T coefficent, double degree) {
    list<T>* FunctionHead = GetHead();
    while (FunctionHead) {
        if (FunctionHead->degree == degree) {
            FunctionHead->coefficent = FunctionHead->coefficent + coefficent;
            std::cout << "\nСтепени " << FunctionHead->degree << " изменён коэффицент на " << coefficent << endl;
            return true;
        }
        FunctionHead = FunctionHead->next;
    }
    return false;
}

template<typename T>
void Equalization<T>::Set(T coefficent, double degree)
{
    if (!DetectOldDegree(coefficent, degree))
    {
        if (coefficent != T(0)) {
            list<T>* pointer;
            pointer = new list<T>;
            pointer->coefficent = coefficent;
            pointer->degree = degree;
            pointer->next = this->head;
            this->head = pointer;
            count++;
        }
    }

}

template<typename T>
int Equalization<T>::DeleteElement(double degree)
{
    int NowCount = 0;
    list<T>* FunctionHead = GetHead();
    list<T>* pred = FunctionHead;
    while (NowCount < count)
    {
        if (FunctionHead->degree == degree)
        {
            if (NowCount == 0)
            {
                SetHead(FunctionHead->next);

            }
            else if (NowCount == count - 1)
            {
                pred->next = nullptr;
            }
            else {
                pred->next = FunctionHead->next;
            }
            delete FunctionHead;
            count--;
            return 1;
        }
        pred = FunctionHead;
        FunctionHead = FunctionHead->next;
        NowCount++;
    }
    return 0;
}

template<typename T>
void  Equalization<T>::Derivative() {
    list<T>* FunctionHead = GetHead();

    while (FunctionHead)
    {
        FunctionHead->coefficent = FunctionHead->coefficent * T(FunctionHead->degree);
        FunctionHead->degree--;
        FunctionHead = FunctionHead->next;

    }


}

template<typename T>
void Equalization<T>::Multiplication(T value) {
    list<T>* FunctionHead = GetHead();
    while (FunctionHead) {
        FunctionHead->coefficent = FunctionHead->coefficent * value;
        FunctionHead = FunctionHead->next;
    }
    cout << "\nНаш многочлен успешно был умножен...\n";
}

template<typename T>
void Equalization<T>::Calculation(T x) {
    list<T>* FunctionHead = GetHead();
    T sum = 0;
    while (FunctionHead) {
        sum += FunctionHead->coefficent * T(pow(x, FunctionHead->degree));
        FunctionHead = FunctionHead->next;
    }
    cout << "При x=" << x << " значение многочлена равно " << sum << endl;
}

template<typename T>
void Equalization<T>:: operator -(Equalization& src)
{
    list<T>* FunctionHead = GetHead();
    list<T>* StartHeadB = src.head;
    bool SearchSuccesesful;
    while (src.head) {
        SearchSuccesesful = false;
        while (FunctionHead) {
            if (FunctionHead->degree == src.head->degree)
            {
                SearchSuccesesful = true;
                FunctionHead->coefficent -= src.head->coefficent;

                break;
            }
            FunctionHead = FunctionHead->next;
        }
        if (!SearchSuccesesful)
        {
            Set(src.head->coefficent * T(-1), src.head->degree);
        }
        src.head = src.head->next;
    }
    src.head = StartHeadB;
}

template<typename T>
void  Equalization<T>:: operator +(Equalization& src)
{
    list<T>* FunctionHead = GetHead();
    list<T>* StartHeadB = src.head;
    bool SearchSuccesesful;
    while (src.head) {
        SearchSuccesesful = false;
        while (FunctionHead) {
            if (FunctionHead->degree == src.head->degree)
            {
                SearchSuccesesful = true;
                FunctionHead->coefficent += src.head->coefficent;
                if (FunctionHead->coefficent == T(0)) count--;
            }
            FunctionHead = FunctionHead->next;
        }
        if (!SearchSuccesesful)
        {
            Set(src.head->coefficent, src.head->degree);
        }
        src.head = src.head->next;
    }
    src.head = StartHeadB;
}

template<typename T>
bool Equalization<T>::operator==(Equalization& src)

{
    list<T>* FunctionHead = GetHead();
    list<T>* StartHeadB = src.head;
    int SearchSuccesesful = 0;
    if (count != src.count) return false;
    while (src.head) {
        while (FunctionHead) {

            //          ||degree1|  -   |degree2||   <  |epsilon|
            if (abs(abs(FunctionHead->degree) - abs(src.head->degree)) <= abs(epsilon) &&
                abs(abs(FunctionHead->coefficent) - abs(src.head->coefficent)) <= abs(epsilon)) SearchSuccesesful++;
            FunctionHead = FunctionHead->next;
        }
        src.head = src.head->next;
    }
    src.head = StartHeadB;

    if (SearchSuccesesful == count) return true;
    else return false;

}
bool Equalization<complex<double>>::operator==(Equalization& src)
{
    list<complex<double>>* FunctionHead = GetHead();
    list<complex<double>>* StartHeadB = src.head;
    int SearchSuccesesful = 0;
    if (count != src.count) return false;
    while (src.head) {
        while (FunctionHead) {

            //          ||degree1|  -   |degree2||   <  |epsilon|
            if (abs(abs(real(FunctionHead->degree)) - abs(real(src.head->degree))) <= abs(epsilon) &&
                abs(abs(imag(FunctionHead->degree)) - abs(imag(src.head->degree))) <= abs(epsilon) &&
                abs(abs(FunctionHead->coefficent) - abs(src.head->coefficent)) <= abs(epsilon)) SearchSuccesesful++;
            FunctionHead = FunctionHead->next;
        }
        src.head = src.head->next;
    }
    src.head = StartHeadB;

    if (SearchSuccesesful == count) return true;
    else return false;

}
bool Equalization<complex<float>>::operator==(Equalization& src)
{
    list<complex<float>>* FunctionHead = GetHead();
    list<complex<float>>* StartHeadB = src.head;
    int SearchSuccesesful = 0;
    if (count != src.count) return false;
    while (src.head) {
        while (FunctionHead) {

            //          ||degree1|  -   |degree2||   <  |epsilon|
            if (abs(abs(real(FunctionHead->degree)) - abs(real(src.head->degree))) <= abs(epsilon) &&
                abs(abs(imag(FunctionHead->degree)) - abs(imag(src.head->degree))) <= abs(epsilon) &&
                abs(abs(FunctionHead->coefficent) - abs(src.head->coefficent)) <= abs(epsilon)) SearchSuccesesful++;
            FunctionHead = FunctionHead->next;
        }
        src.head = src.head->next;
    }
    src.head = StartHeadB;

    if (SearchSuccesesful == count) return true;
    else return false;

}
template<typename T>
int Equalization<T>:: operator[](double degree)
{
    list<T>* FunctionHead = GetHead();
    while (FunctionHead) {
        if (FunctionHead->degree == degree)
        {
            double coefficent;
            cout << "Введите новый коэффицент для степени " << FunctionHead->degree << ": ";
            cin >> coefficent;
            if (coefficent != 0) {
                FunctionHead->coefficent = coefficent;
            }
            else { cout << "Нельзя менять на ноль "; }
            return 0;
        }
        FunctionHead = FunctionHead->next;
    }
    cout << "Нет такого элемента :( \n";
    return 0;
}




EClassException::EClassException(const char* err) {
    strncpy_s(_err, err, 255);
    _err[255] = 0;
}
void EClassException::Print()
{
    std::cout << _err << std::endl;
}

template class Equalization<int>;
template class Equalization<float>;
template class Equalization<double>;
template class Equalization<complex<float>>;
template class Equalization<complex<double>>;