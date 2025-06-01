#include "logic.h"
#include <iostream>
#include <cstdlib>

void Logic::turnOn(){
    bool stringChanged = false;
    prevNum.toZero();
    memNum.toZero();
    // изменилась строка - если изменилось число, был выключен или была ошибка
    stringChanged = (currNum.toZero()
                     || (state & (STATE::isError|STATE::isOff)) );
    state = 0;
    prevOp = '\0';
    if(stringChanged)
        emit onChanged();
}
void Logic::turnOff(){
    bool stringChanged = false;
    prevNum.toZero();
    memNum.toZero();
    currNum.toZero();
    // изменилась строка - если  был включен или была ошибка
    stringChanged = ((state & STATE::isError)
                     || !(state & STATE::isOff));
    state = STATE::isOff;
    prevOp = '\0';
    if(stringChanged)
        emit onChanged();
}
void Logic::inputDigit(char c){  //цифра, или точкаб или w (aka 00)
    if(state & (STATE::isOff | STATE::isError))
        return;
    bool stringChanged1 = false, stringChanged2 = false;
    if(state & (STATE::toRenew)){
        stringChanged1 = currNum.toZero();
        state &= (~STATE::toRenew);
    }

    if(c == '.')
        stringChanged2 = currNum.inputDot();
    else if(c == 'w') { // двойной ноль
        stringChanged2 = currNum.inputDig('0');
        currNum.inputDig('0');
    } else
        stringChanged2 = currNum.inputDig(c);

    if(stringChanged1 || stringChanged2)
        emit onChanged();
}
void Logic::delDig(){
    if(state & (STATE::isOff | STATE::isError))
        return;

    state &= (~STATE::toRenew);
    if(currNum.delDig())
        emit onChanged();
}
void Logic::chSign(){
    if(state & (STATE::isOff | STATE::isError))
        return;

    state &= (~STATE::toRenew);
    if(currNum.changeSign())
        emit onChanged();
}
void Logic::operateBinary(char op){
    if(state & (STATE::isOff | STATE::isError))
        return;

    if(op == 'x' || op == ':'
        || op == '+' || op == '-'
        || op == 'p'){  //p = "a^b"
        prevOp = op;
        state |= STATE::toRenew;
        prevNum = currNum;
        return;
    }
}
void Logic::operateUnary(char op){
    if(state & (STATE::isOff | STATE::isError))
        return;
    state |= STATE::toRenew;

    if(op == 's' || op == 'c'
        || op == 'l' || op == 'q'){   // s = sin, c = cos, l = log, q = sqr
        prevOp = op;
        bool isSucces = false;

        switch (op){
        case 's': isSucces = currNum.sin();
            break;
        case 'c': isSucces = currNum.cos();
            break;
        case 'l': isSucces = currNum.log();
            break;
        case 'q': isSucces = currNum.sqrt();
            break;
        };
        if(!isSucces)
            state |= STATE::isError;
        emit onChanged();
    }
}
void Logic::operateMem(char mop){
    if(state & (STATE::isOff | STATE::isError))
        return;

    state |= STATE::toRenew;
    if(mop == 'r' || mop == '+'|| mop == '-' ){   // r = mrc, + = m+, - = m-
        bool isSucces = false;

        switch (mop){
        case 'r': currNum = memNum;
            isSucces = true;
            break;
        case '+': isSucces = memNum.add(currNum);
            break;
        case '-': isSucces = memNum.sub(currNum);
            break;
        };

        if(!isSucces)
            state |= STATE::isError;

        emit onChanged();
    }
}

void Logic::operateEvaluate(){
    if(state & (STATE::isOff | STATE::isError))
        return;

    state |= STATE::toRenew;

    bool isSuccess = false;
    if(prevOp == 'x' || prevOp == ':'
        || prevOp == '+' || prevOp == '-'
        || prevOp == 'p'){  //binary
        secNum = currNum;
        switch (prevOp){
        case 'x': isSuccess = prevNum.mult(secNum);
            break;
        case ':': isSuccess = prevNum.div(secNum);
            break;
        case '+': isSuccess = prevNum.add(secNum);
            break;
        case '-': isSuccess = prevNum.sub(secNum);
            break;
        case 'p': isSuccess = prevNum.pow(secNum);
            break;
        }

        if(isSuccess)
            currNum = prevNum;
        else
            state |= STATE::isError;

        emit onChanged();
    } else if(prevOp == 's' || prevOp == 'c'
               || prevOp == 'l' || prevOp == 'q'){   // unary
        operateUnary(prevOp);
    } else {
        if(currNum.toTrueMeaning())
            emit onChanged();
    }
}
