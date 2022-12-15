//Отче наш, благослови меня на успешную сдачу лабы пж пж пж
#include <stdio.h>
#include <iostream>
#include <complex>
#include <conio.h>
using namespace std;

template<typename T>
struct Coefficent {
    double degree;
    T coefficent;
    Coefficent* next;
};

template<typename T>
class Equalization
{
public:
    struct list {
        double degree;
        T coefficent;
        list* next;
    };
    int count = 0;
    Coefficent <T>* head = nullptr;
    T epsilon = 0;
    Equalization(T coefficent, double degree)
    {
        if (coefficent != T(0)) {
            this->head = new Coefficent<T>;
            this->head->degree = degree;
            this->head->coefficent = coefficent;
            this->head->next = NULL;
            count = 1;
        }
    }
    ~Equalization() {
        Coefficent<T>* p;
        count = 0;
        while (p = head)
        {
            head = p->next;
            delete p;
        }
    }
    Coefficent<T>* GetHead() { return head; }
    void SetHead(Coefficent<T>* head) { this->head = head; }
    bool DetectOldDegree(T coefficent, double degree)
    {
        Coefficent<T>* FunctionHead = GetHead();
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
    void Set(T coefficent, double degree)

    {
        if (!DetectOldDegree(coefficent, degree))
        {
            if (coefficent != T(0)) {
                Coefficent<T>* pointer;
                pointer = new Coefficent<T>;
                pointer->coefficent = coefficent;
                pointer->degree = degree;
                pointer->next = this->head;
                this->head = pointer;
                count++;
            }
        }

    }
    int DeleteElement(double degree) {
        int NowCount = 0;
        Coefficent<T>* FunctionHead = GetHead();
        Coefficent<T>* pred = FunctionHead;
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
    void Derivative() {
        Coefficent<T>* FunctionHead = GetHead();
        cout << "\nНаша производная: ";
        bool FirstStart = true;
        while (FunctionHead) {
            if (!FirstStart) {

                if (FunctionHead->coefficent * FunctionHead->degree > 0) cout << "+";
            }
            if(FunctionHead->degree!=0)cout << FunctionHead->coefficent * FunctionHead->degree;
            if (FunctionHead->degree != 1&&FunctionHead->degree!=0) {
                cout << "x^" << FunctionHead->degree - 1;
            }
            FirstStart = false;
            FunctionHead = FunctionHead->next;
        }
        cout << "\n";
    }
    void Calculation(T x) {
        Coefficent<T>* FunctionHead = GetHead();
        T sum = 0;
        while (FunctionHead) {
            sum += FunctionHead->coefficent * T(pow(x, FunctionHead->degree));
            FunctionHead = FunctionHead->next;
        }
        cout << "При x=" << x << " значение многочлена равно " << sum << endl;
    }
    void operator*(T value) {
        Coefficent<T>* FunctionHead = GetHead();
        while (FunctionHead) {

            FunctionHead->coefficent = FunctionHead->coefficent * value;
            FunctionHead = FunctionHead->next;
        }
        cout << "\nНаш многочлен успешно был умножен...\n";
    }
    void operator -(Equalization& src) {
        Coefficent<T>* FunctionHead = GetHead();
        Coefficent<T>* StartHeadB = src.head;
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
    void operator +(Equalization& src)
    {
        Coefficent<T>* FunctionHead = GetHead();
        Coefficent<T>* StartHeadB = src.head;
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
    bool operator ==(Equalization& src)

    {
        Coefficent<T>* FunctionHead = GetHead();
        Coefficent<T>* StartHeadB = src.head;
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
    int operator[](double degree) {
        Coefficent<T>* FunctionHead = GetHead();
        while (FunctionHead) {
            if (FunctionHead->degree == degree)
            {
                T coefficent;
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
};
template<typename T>
class Equalization<complex<T>>
{
public:
    struct Coefficent {
        double degree;
        complex<T> coefficent;
        Coefficent* next;
    };
    int count = 0;
    Coefficent *head = nullptr;
    T epsilon = 0;
    Equalization(complex<T> coefficent, double degree)
    {
        if (coefficent != T(0)) {
            this->head = new Coefficent;
            this->head->degree = degree;
            this->head->coefficent = coefficent;
            this->head->next = NULL;
            count = 1;
        }
    }
    ~Equalization() {
        Coefficent* p;
        count = 0;
        while (p = head)
        {
            head = p->next;
            delete p;
        }
    }
    Coefficent* GetHead() { return head; }
    void SetHead(Coefficent* head) { this->head = head; }
    bool DetectOldDegree(complex<T> coefficent, double degree)
    {
        Coefficent* FunctionHead = GetHead();
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
    void Set(complex<T> coefficent, double degree)

    {
        if (!DetectOldDegree(coefficent, degree))
        {
            if (real(coefficent) != 0 || imag(coefficent) != 0) {
                Coefficent* pointer;
                pointer = new  Coefficent;
                pointer->coefficent = coefficent;
                pointer->degree = degree;
                pointer->next = this->head;
                this->head = pointer;
                count++;
            }
        }

    }
    int DeleteElement(double degree) {
        int NowCount = 0;
        Coefficent* FunctionHead = GetHead();
        Coefficent* pred = FunctionHead;
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
    void Derivative() {
        Coefficent* FunctionHead = GetHead();
        cout << "\nНаша производная: ";
        bool FirstStart = true;
        while (FunctionHead) {
            if (!FirstStart) {

                //if (FunctionHead->coefficent * FunctionHead->degree > 0) 
                cout << "+";
            }
            if(FunctionHead->degree!=0)cout << FunctionHead->coefficent * T(FunctionHead->degree);
            if (FunctionHead->degree != 1&&FunctionHead->degree!=0) {
                cout << "x^" << FunctionHead->degree - 1;
            }
            FirstStart = false;
            FunctionHead = FunctionHead->next;
        }
        cout << "\n";
    }
    void Calculation(complex<T> x) {
        Coefficent* FunctionHead = GetHead();
        complex<T> sum;
        while (FunctionHead) {
            sum += FunctionHead->coefficent * complex<T>(pow(x, FunctionHead->degree));
            FunctionHead = FunctionHead->next;
        }
        cout << "При x=" << x << " значение многочлена равно " << sum << endl;
    }
    void operator*(complex<T> value) {
        Coefficent* FunctionHead = GetHead();
        while (FunctionHead) {

            FunctionHead->coefficent = FunctionHead->coefficent * value;
            FunctionHead = FunctionHead->next;
        }
        cout << "\nНаш многочлен успешно был умножен...\n";
    }
    void operator -(Equalization& src) {
        Coefficent* FunctionHead = GetHead();
        Coefficent* StartHeadB = src.head;
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
    void operator +(Equalization& src)
    {
        Coefficent* FunctionHead = GetHead();
        Coefficent* StartHeadB = src.head;
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
    bool operator ==(Equalization& src)

    {
        Coefficent* FunctionHead = GetHead();
        Coefficent* StartHeadB = src.head;
        int SearchSuccesesful = 0;
        if (count != src.count) return false;
        while (src.head) {
            while (FunctionHead) {

                //          ||degree1|  -   |degree2||   <  |epsilon|
                if (abs(abs(FunctionHead->degree) - abs(src.head->degree)) <= abs(epsilon) &&
                    abs(abs(real(FunctionHead->coefficent)) - abs(real(src.head->coefficent))) <= abs(epsilon) &&
                    abs(abs(imag(FunctionHead->coefficent)) - abs(imag(src.head->coefficent))) <= abs(epsilon)) SearchSuccesesful++;
                FunctionHead = FunctionHead->next;
            }
            src.head = src.head->next;
        }
        src.head = StartHeadB;

        if (SearchSuccesesful == count) return true;
        else return false;

    }
    int operator[](double degree) {
        Coefficent* FunctionHead = GetHead();
        while (FunctionHead) {
            if (FunctionHead->degree == degree)
            {
                complex<T> coefficent;
                cout << "Введите новый коэффицент для степени " << FunctionHead->degree << ": ";
                cin >> coefficent;
                if (real(coefficent) != 0||imag(coefficent)!=0) {
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
};
class EClassException
{
protected:
    char _err[256];
public:
    EClassException(const char* err);
    void Print();
};

EClassException::EClassException(const char* err) {
    strncpy_s(_err, err, 255);
    _err[255] = 0;
}
void EClassException::Print()
{
    std::cout << _err << std::endl;
}


template<typename T>
ostream& operator<<(ostream& os, Equalization<T> obj)
{
    cout << "Наши элементы:";
    while (obj.head)
    {
        cout << "\n" << obj.head->coefficent;
        if (obj.head->degree != 0)cout << "x";
        if (obj.head->degree > 0 && obj.head->degree != 1)cout << obj.head->degree;
        if (obj.head->degree < 0) cout << "x^(" << obj.head->degree << ")";
        obj.head = obj.head->next;
    }
    cout << "\n";
    return os;
}



template <typename T>
void Menu1() {
    try
    {
        double degree;
        T coefficent;
        int choice;
        cout << "Введите коэфффицент первого элемента: " << endl;
        cin >> coefficent;
        cout << "Введите степень первого элемента: " << endl;
        cin >> degree;
        Equalization<T> A(coefficent, degree);
        bool flag = true;
        while (flag) {
            system("cls");
            //A.DeleteElement(0);
            cout << A;
            cout << "Выберите действие:\n1)Добавить новый элемент\n2)Умножить на скаляр\n3)Вычислить х\n4)Найти производную\n5)Сумма с другим многочленом\n6)Вычесть из него другой многочлен\n7)Средактировать коэффицент\n8)Удалить элемент\n9)Сравнить многочлены\n10)Выход\n";
            cin >> choice;
            if (choice == 1)
            {
                cout << "Введите коэффицент нового элемента: " << endl;
                cin >> coefficent;
                cout << "Введите степень нового элемента: " << endl;
                cin >> degree;
                A.Set(coefficent, degree);
            }
            else if (choice == 2) {
                cout << "Введите значение скаляра: " << endl;
                cin >> coefficent;
                A* coefficent;
            }
            else if (choice == 3) {
                cout << "Введите значение х при котором вычисляем: " << endl;
                cin >> coefficent;
                A.Calculation(coefficent);
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
                    cin >> coefficent;
                    cout << "Введите степень первого элемента нового многочлена: ";
                    cin >> degree;
                    B.Set(coefficent, degree);
                    cout << "Хотите добавить ещё один элемент? \n1)Да\n2)Нет\n";
                    cin >> choice;
                } while (choice == 1);
                if (SumOperation) A + B;
                else A - B;
            }
            else if (choice == 7) {
                cout << "Выберите степень выбранного элемента";
                cin >> degree;
                A[degree];
            }
            else if (choice == 8) {
                cout << "Выберите степень выбранного элемента: ";
                cin >> degree;
                if (A.DeleteElement(degree) == 0) cout << "Нет такого элемента :(" << endl;
            }
            else if (choice == 9) {
                Equalization<T> B(0, 0);
                do {
                    cout << "Введите точность, пример 0.001: ";
                    cin >> A.epsilon;
                    cout << "Введите коэффицент первого элемента нового многочлена: ";
                    cin >> coefficent;
                    cout << "Введите степень первого элемента нового многочлена: ";
                    cin >> degree;
                    B.Set(coefficent, degree);
                    cout << "Хотите добавить ещё один элемент? \n1)Да\n2)Нет\n";
                    cin >> choice;
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
            Menu1<complex<float>>();
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