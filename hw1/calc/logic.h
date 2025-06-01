#ifndef LOGIC_H
#define LOGIC_H

#include <QObject>
#include <iostream>
#include <cstdlib>
#include <cmath>

class Number{
    static const size_t maxLen = 15;
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
    bool setTenPow(long long int pow, bool neg){
        if((pow + 1 > (long long int)maxLen)
            || (2 - pow > (long long int)maxLen))
            return false;

        if(pow >= 0){
            // " 10000"
            //  012345   length = 6 pow = 4 maxLen + 2 >= 6
            is_dot = false;
            is_neg = neg;
            visValue[0] = neg ? '-' : ' ';
            visValue[1] = '1';
            value = 1;
            divisor = 1;
            length = 2;
            while(pow--){
                visValue[length++] = '0';
                value *= 10;
            }
            for(size_t i = length; i <= maxLen + 1; ++i)
                visValue[i++] = '\0';
        } else {
            // " 0.001"
            //  012345   length = 6 pow = -3 maxLen + 2 >= 6
            is_dot = true;
            is_neg = neg;
            visValue[0] = neg ? '-' : ' ';
            visValue[1] = '0';
            visValue[2] = '.';
            value = 1;
            divisor = 10;
            length = 3;
            while(++pow){
                visValue[length++] = '0';
                divisor *= 10;
            }
            visValue[length++] = '1';
            for(size_t i = length; i <= maxLen + 1; ++i)
                visValue[i++] = '\0';
        }

        return true;
    }

    bool setDouble(long double d){
        if(!std::isfinite(d))
            return false;
        size_t counter = 0, nines = 0;
        bool neg = (d < 0);
        long long int c = (d < 0 ? -d : d);
        //считаем количество знаков слева от запятой
        while (c >= 1){
            nines += ((c%10) == 9);
            c /= 10;
            ++counter;
        }
        //если сразу вышли из цикла -> counter == 0 и число дробное
        //если counter != 0, значит, counter == кол-ву цифр слева от запятой


        if (counter > maxLen)
            return false;

        // c = cd - целая, fr - дробная часть
        long double cd, fr = modfl((d < 0 ? - d : d), &cd);
        c = cd;
        // обрабатываем случаи, когда влезет только целая часть
        if (counter >= maxLen - 1){
            // visValues = " xxx"
            // indexes      0123  length = 4 counter = 3
            //если при округлении увеличится кол-во цифр
            // это - только если все девятки
            if ((nines == counter)&&(fr >= 0.5))
                return setTenPow(counter + 1, neg);
            if (fr >= 0.5)
                ++c;

            visValue[0] = neg ? '-' : ' ';
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

        // теперь знаем, что наше число точно влезет с учетом точки
        // значит, рассчитываем на maxLen - 1 мест чисто для цифр

        // обрабатываем чисто дробное число
        // сначала нужно домножить на степень десятки и округлить
        // после запятой рассчитываем на maxLen - 2 цифры
        if(!counter){
            // в данном случае counter == nines == 0, c == 0
            divisor = 1;
            while (counter <= maxLen - 2){
                fr *= 10;
                c = c*10 + (int)fr;
                divisor *= 10;
                nines += (int(fr) == 9);
                counter++;
                fr = fr - (int)fr;
            }
            //counter = кол-во цифр посл запятой
            if ((nines == counter)&&(fr >= 0.5)) // если к-во цифр изменится
                return setTenPow(0, neg);

            if (fr >= 0.5)
                ++c;
            // c - наше число, divisor - делитель
            // сократим, сколько сможем
            while( !(divisor%10) && !(c%10) ){
                divisor /= 10;
                c /= 10;
                --counter;
            }

            if(divisor == 1){ // получили 0 после округления
                // visValues = " 0"
                // indexes      01  length = 2 counter = 5
                visValue[0] = ' ';
                visValue[1] = '0';
                visValue[maxLen] = '\0';
                value = 0;
                length = 2;
                is_dot = false;
                is_neg = false;
                for(size_t i = length; i <= maxLen + 1; ++i)
                    visValue[i] = '\0';
            } else {
                // visValues = " 0.xxx"
                // indexes      012345 length = 6 counter = 3
                length = counter + 3;
                visValue[0] = neg ? '-' : ' ';
                visValue[1] = '0';
                visValue[2] = '.';
                value = c;
                is_dot = true;
                is_neg = neg;
                for(size_t i = length; i <= maxLen + 1; ++i)
                    visValue[i] = '\0';
                for(size_t i = length - 1; i > 2; --i){
                    visValue[i] = '0' + (c%10);
                    c /= 10;
                }
            }
            return true;
         }

        // теперь обрабатываем число с целой и дробной частями
        size_t before_dot = counter;
        divisor = 1;
        while (counter <= maxLen - 1){
            fr *= 10;
            c = c*10 + (int)fr;
            divisor *= 10;
            nines += (int(fr) == 9);
            counter++;
            fr = fr - (int)fr;
        } // теперь counter = кол-во цифр

        if ((nines == counter)&&(fr >= 0.5)) // если к-во цифр изменится
            return setTenPow(before_dot + 1, neg);

        if (fr >= 0.5)
            ++c;
        // c - наше число, divisor - делитель
        // сократим, сколько сможем
        while( !(divisor%10) && !(c%10) ){
            divisor /= 10;
            c /= 10;
            --counter;
        }

        if(divisor == 1){ // если число оказалось целым
            // visValues = " xxx"
            // indexes      0123  length = 4 counter = 3
            visValue[0] = neg ? '-' : ' ';
            value = c;
            length = counter + 1;
            is_dot = false;
            is_neg = neg;
            for(size_t i = length; i <= maxLen + 1; ++i)
                visValue[i] = '\0';
            for(size_t i = length - 1; i; --i){
                visValue[i] = '0' + (c%10);
                c /= 10;
            }
        } else {
            // visValues = " xxx.xx"
            // indexes      0123456  length = 7 counter = 5
            length = counter + 2;
            visValue[0] = neg ? '-' : ' ';
            value = c;
            is_dot = true;
            is_neg = neg;
            for(size_t i = length; i <= maxLen + 1; ++i)
                visValue[i] = '\0';
            for(size_t i = length - 1; i > before_dot + 1; --i){
                visValue[i] = '0' + (c%10);
                c /= 10;
            }
            visValue[before_dot + 1] = '.';
            for(size_t i = before_dot; i ; --i){
                visValue[i] = '0' + (c%10);
                c /= 10;
            }
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
        a = (long double)value / divisor;
        b = (long double)n.value / n.divisor;
        if(is_neg) a = -a;
        if(n.is_neg) b = -b;
        a += b;
        return setDouble(a);
    }
    bool sub(Number& n){
        long double a, b;
        a = (long double)value / divisor;
        b = (long double)n.value / n.divisor;
        if(is_neg) a = -a;
        if(n.is_neg) b = -b;
        a -= b;
        return setDouble(a);
    }
    bool mult(Number& n){
        long double a, b;
        a = (long double)value / divisor;
        b = (long double)n.value / n.divisor;
        a *= b;
        if(is_neg != n.is_neg)
            a = -a;
        return setDouble(a);
    }
    bool div(Number& n){
        long double a, b;

        a = (long double)value / divisor;
        b = (long double)n.value / n.divisor;
        if(b < __DBL_EPSILON__ && b > -__DBL_EPSILON__)
            return false;
        a /= b;
        if(is_neg != n.is_neg)
            a = -a;
        return setDouble(a);
    }
    bool pow(Number& n){
        long double a, b;
        a = (long double)value / divisor;
        b = (long double)n.value / n.divisor;
        if(is_neg) a = -a;
        if(n.is_neg) b = -b;
        if(b < __DBL_EPSILON__ && b > -__DBL_EPSILON__)
            return false;
        a = powl(a, b);
        return setDouble(a);
    }
    bool sqrt(){
        if(is_neg)
            return false;
        long double a;
        a = (long double)value / divisor;
        return setDouble(sqrtl(a));
    }
    bool log(){
        if(is_neg)
            return false;
        long double a;
        a = (long double)value / divisor;
        return setDouble(logl(a));
    }
    bool sin(){
        long double a;
        a = (long double)value / divisor;
        a *= (M_PIl/180.0); // в радианы
        return setDouble(sinl(a));
    }
    bool cos(){
        long double a;
        a = (long double)value / divisor;
        a *= (M_PIl/180.0); // в радианы
        return setDouble(cosl(a));
    }
    void test(){
        long double d = value;
        value = 0;
        for(size_t i =0 ; i < maxLen + 2; ++i)
            visValue[i] = '\0';
        setDouble(d);
        std::cout << visValue << '\n';
        return;
    }
};

enum STATE {isOff = 1,
            isError = 2,
            toRenew = 4};


class Logic : public QObject {
    Q_OBJECT
private:
    void inputDigit(char c);
    void operateBinary(char op);
    void operateUnary(char op);
    void operateMem(char op);
public:
    Logic(QObject *parent = nullptr) : QObject(parent) {};
    QString getCurrent() {return ((state & isOff)? "" :
                                (state & isError) ? "ERROR" : currNum.getString());};
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
    void operateEvaluate();
    void binMult(){operateBinary('x');}
    void binAdd() {operateBinary('+');}
    void binDiv() {operateBinary(':');}
    void binSub() {operateBinary('-');}
    void binPow() {operateBinary('p');}
    void unSin() {operateUnary('s');}
    void unCos() {operateUnary('c');}
    void unLog() {operateUnary('l');}
    void unSqr() {operateUnary('q');}
    void mrc() {operateMem('r');}
    void mPlus() {operateMem('+');}
    void mMinus() {operateMem('-');}
//    void test() {currNum.test();}
private:
    unsigned int state = 0;
    char prevOp = '\0';
    Number currNum{};
    Number prevNum{};
    Number secNum{};
    Number memNum{};
};

#endif // LOGIC_H
