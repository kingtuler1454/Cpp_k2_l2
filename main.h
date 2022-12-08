#include <stdio.h>
#include <iostream>

using namespace std;

template<typename T>
struct list {
    double degree;
    T coefficent;
    list* next;
};

template<typename T>
class Equalization
{
public:
    int count = 0;
    list<T>* head = nullptr;
    T epsilon = 0;
    Equalization(T coefficent, double degree);
    ~Equalization();

    list<T>* GetHead();

    void SetHead(list<T>* head);

    bool DetectOldDegree(T coefficent, double degree);

    void Set(T coefficent, double degree);

    int DeleteElement(double degree);

    void Derivative();

    void Multiplication(T value);

    void Calculation(T x);


    void operator -(Equalization& src);

    void operator +(Equalization& src);

    bool operator ==(Equalization& src);
    int operator[](double degree);

};


class EClassException
{
protected:
    char _err[256];
public:
    EClassException(const char* err);
    void Print();
};