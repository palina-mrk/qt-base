#ifndef LOGIC_H
#define LOGIC_H

#include <QObject>
#include <iostream>
#include <cstdlib>
#include <cmath>

class Number{
    static const size_t maxLen = 10;
    size_t length = 2;
    bool is_dot = false;
    bool is_neg = false;
    //"-034.4535"
    // 012345678  length == 9 visValue[length] == '\0'
    char* visValue;           // maxLen+2 elements;
                              // visValue[maxLen + 1] == '\0' always
    long long int value = 0;  // number = (double)value/(double)divisor
    long long int divisor = 1;
public:
    bool toTrueMeaning(){
        if(!is_dot && !is_neg && !value) // only " 0"
            return false;

        if(!value){ //value = zero
            is_neg = false;
            is_dot = false;
            visValue[0] = ' ';
            visValue[1] = '0';
            for(size_t i = 2; i < length; ++i)
                visValue[i] = '\0';
            length = 2;
            return true;
        }

        // now we know: we have a dot
        // and number is nonzero

        // erasing zeroes
        while(visValue[length - 1] == '0'){
            divisor /= 10;
            visValue[--length] = '\0';
        }

        if(visValue[length - 1] == '.'){
            is_dot = false;
            visValue[--length] = '\0';
        }

        return true;
    }
private:
    bool setInt(long long int n){
        long long int tmp = (n > 0 ? n : -n);
        size_t counter = 0;
        while(tmp >= 1){
            tmp /= 10;
            ++counter;
        }
        if(counter >= maxLen + 1)
            return false;

        if(counter == 0){
            visValue[0] = ' ';
            visValue[1] = '0';
            for(size_t i = 2; i <= maxLen + 1; ++i)
                visValue[i] = '\0';
            length = 2;
            is_dot = false; is_neg = false;
            divisor = 1; value = 0;
            return true;
        }

        is_neg = (n < 0);
        is_dot = false;
        divisor = 1;
        length = counter + 1;
        value = (n > 0 ? n : -n);
        tmp = value;
        for(size_t i = maxLen + 1; i >= length; --i)
            visValue[i] = '\0';
        for(size_t i = length - 1; i; --i){
            visValue[i] = '0' + (tmp % 10);
            tmp /= 10;
        }

        return true;
    }

    bool setNumber(long double d){
        //вычисляем знак
        // c - целая часть, fr - дробная
        long double cd, fr = modfl((d < 0 ? - d : d), &cd);
        long long int c = cd;
        size_t counter = 0, nines = 0;
        bool neg = (d < 0);
        //считаем количество знаков слева от запятой
        while (c >= 1){
            nines += ((c%10) == 9);
            c /= 10;
            ++counter;
        }
        if(counter == 0)      //если сразу вышли из цикла -> counter == 0 и число дробное
            counter = 1;      //если counter != 0, значит, counter == кол-ву цифр слева от запятой


        if (counter > maxLen)
            return false;
        // исключаем случай переполнения d == 9999999.6
        // maxlen девяток и округление в бОльшую сторону
        if (counter == maxLen && nines == counter && fr >= 0.5)
            return false;
        else if (counter >= maxLen - 1){ // влезет только целая часть
            if (fr >= 0.5){
                ++c;
                if (nines == counter)
                    ++counter;
            }
            visValue[0] = ' ';
            visValue[1] = '0';
            visValue[maxLen + 1] = '\0';
            visValue[maxLen] = '\0';
            value = c;
            length = counter + 1;
            is_dot = false;
            divisor = 1;
            is_neg = neg;
            for(size_t i = length - 1; i ; --i){
                visValue[i] = '0' + (c % 10);
                c /= 10;
            }
            return true;
        }

        size_t before_dot = counter;
        int dig;
        divisor = 1;
        while (counter < maxLen - 1){
            fr *= 10;
            dig = (int)fr;
            c = c*10 + dig;
            fr -= dig;
            nines += (dig == 9);
            divisor *= 10;
            ++counter;
        }
        if (fr >= 0.5){
            ++c;
            if (nines == counter){
                ++before_dot;
                c /= 10;
                divisor /= 10; // на одну после запятой влезет меньше
            }
        }
        while(!(c%10) && (divisor > 1)){
            c /= 10;
            divisor /= 10;
            --counter;
        }
        if(divisor == 1) {
            is_neg = neg;
            is_dot = false;
            length = counter + 1;
            value = c;
            for(size_t i = maxLen + 1; i >= length; --i)
                visValue[i] = '\0';
            for(size_t i = length - 1; i; --i){
                visValue[i] = '0' + c%10;
                c /= 10;
            }
            visValue[0] = ' ';
            return true;
        }

        is_neg = neg;
        is_dot = true;
        length = counter + 2;
        value = c;
        for(size_t i = maxLen + 1; i >= length; --i)
            visValue[i] = '\0';
        for(size_t i = length - 1; i > before_dot; --i){
            visValue[i] = '0' + c%10;
            c /= 10;
        }
        visValue[before_dot + 1] = '.';
        for(size_t i = before_dot; i ; --i){
            visValue[i] = '0' + c%10;
            c /= 10;
        }
        return true;
    }
public:
    Number() {
        visValue = new char[maxLen + 2];
        visValue[0] = ' ';
        visValue[1] = '0';
        for(size_t i = 2; i <= maxLen + 1; ++i)
            visValue[i] = '\0';
    }
    ~Number() { delete []visValue; visValue = nullptr; }
    Number(Number& n) {
        visValue = new char[maxLen + 2];
        for(size_t i = 0; i <= maxLen + 1; ++i)
            visValue[i] = n.visValue[i];
        length = n.length;
        is_neg = n.is_neg;
        is_dot = n.is_dot;
        value = n.value;
        divisor = n.divisor;
    }
    Number& operator=(const Number& n) {
        for(size_t i = 0; i <= maxLen + 1; ++i)
            visValue[i] = n.visValue[i];
        length = n.length;
        is_neg = n.is_neg;
        is_dot = n.is_dot;
        value = n.value;
        divisor = n.divisor;
        return *this;
    }
    Number(Number&& n) {
        visValue = n.visValue;
        length = n.length;
        is_neg = n.is_neg;
        is_dot = n.is_dot;
        value = n.value;
        divisor = n.divisor;
    }
    Number& operator=(Number&& n) {
        delete []visValue;
        visValue = n.visValue;
        length = n.length;
        is_dot = n.is_dot;
        is_neg = n.is_neg;
        value = n.value;
        divisor = n.divisor;
        return *this;
    }
    bool inputDot() {
        if(is_dot || (length == maxLen + 1))
            return false;
        visValue[length++] = '.';
        is_dot = true;
        return true;
    }
    bool inputDig(char c){
        if( (c < '0') || (c > '9'))
            return false;
        short int dig = (c - '0');

        if(length == maxLen + 1)   // if max length
            return false;

        if(!value && !is_dot){     // if one-digit zero, change digit to zero
            visValue[1] = c;
            return  (value = dig); // if dig != 0, then we changed the number, return true
        }

        value = value*10 + dig;
        visValue[length++] = c;
        if(is_dot)   // was point -> non-integer
            divisor *= 10;

        return true;
    }
    bool delDig(){
        if(length == 2){  // if one-digit number
            visValue[1] = '0';
            return (value == 0 ? false : value = 0, true);
        }

        if(visValue[length - 1] == '.'){
            is_dot = 0;
            visValue[--length] = '\0';
            return true;
        }

        value /= 10;
        visValue[--length] = '\0';
        if(is_dot) // if non-integer
            divisor /= 10;

        return true;
    }

    QString getString(){ return QString(visValue); }
    bool isVisZero() { return (!is_dot && !is_neg && !value); }
    bool toZero() {
        if (is_dot && !is_neg && !value)
            return false;
        visValue[0] = ' ';
        visValue[1] = '0';
        for(size_t i = 2; i < length; ++i)
            visValue[i] = '\0';
        value = 0;
        divisor = 1;
        length = 2;
        is_dot = false;
        is_neg = false;
        return true;
    }
    bool changeSign(){
        is_neg = !is_neg;
        visValue[0] = (is_neg ? '-' : ' ');
        return true;
    }
    bool add(Number& n){
        long double a, b;
        a = is_neg ? -(long double)value / divisor : (long double)value / divisor;
        b = n.is_neg ? -(long double)n.value / n.divisor : (long double)n.value / n.divisor;
        a += b;
        return setNumber(a);
    }
    bool sub(Number& n){
        long double a, b;
        a = is_neg ? -(long double)value / divisor : (long double)value / divisor;
        b = n.is_neg ? -(long double)n.value / n.divisor : (long double)n.value / n.divisor;
        a -= b;
        return setNumber(a);
    }
    bool mult(Number& n){
        long double a, b;
        a = is_neg ? -(long double)value / divisor : (long double)value / divisor;
        b = n.is_neg ? -(long double)n.value / n.divisor : (long double)n.value / n.divisor;
        a *= b;
        return setNumber(a);
    }
    bool div(Number& n){
        long double a, b;
        a = is_neg ? -(long double)value / divisor : (long double)value / divisor;
        b = n.is_neg ? -(long double)n.value / n.divisor : (long double)n.value / n.divisor;
        if(b < __DBL_EPSILON__)
            return false;
        a /= b;
        return setNumber(a);
    }
    bool sqrt(){
        if(is_neg)
            return false;
        long double a;
        a = (long double)value / divisor;
        return setNumber(sqrtl(a));
    }
    bool log(){
        if(is_neg)
            return false;
        long double a;
        a = (long double)value / divisor;
        return setNumber(logl(a));
    }
    void test(){
        long double d = value;
        value = 0;
        for(size_t i =0 ; i < maxLen + 2; ++i)
            visValue[i] = '\0';
        std::cout << setNumber(d) << visValue;
        return;
    }
};


class Logic : public QObject {
    Q_OBJECT
private:
    void inputDigit(char c);
    void doubleOp(char c);
public:
    Logic(QObject *parent = nullptr) : QObject(parent) {};
    QString getCurrent() {return (isBlocked ? "" : currNum.getString());};
signals:
    QString onChanged();
public slots:
    void turnOn();
    void turnOff();
    void input0() {inputDigit('0');}
    void input1() {inputDigit('1');}
    void input2() {inputDigit('2');}
    void input3() {inputDigit('3');}
    void input4() {inputDigit('4');}
    void input5() {inputDigit('5');}
    void input6() {inputDigit('6');}
    void input7() {inputDigit('7');}
    void input8() {inputDigit('8');}
    void input9() {inputDigit('9');}
    void input00() {inputDigit('w');}
    void inputDot() {inputDigit('.');}
    void delDig();
    void chSign();
    void mult(){doubleOp('x');}
    void add() {doubleOp('-');}
    void div() {doubleOp(':');}
    void sub() {doubleOp('-');}
    void test() {currNum.test();}
private:
    bool isBlocked = true;
    char op = '\0';
    Number currNum{};
    Number prevNum{};
    Number memNum{};
};

#endif // LOGIC_H
