#include "logic.h"
#include <iostream>
#include <cstdlib>

void Logic::turnOn(){
    prevNum.toZero();
    memNum.toZero();
    if(currNum.toZero() || isBlocked){
        isBlocked = false;
        emit onChanged();
    }
}
void Logic::turnOff(){
    prevNum.toZero();
    memNum.toZero();
    currNum.toZero();
    isBlocked = true;
    emit onChanged();
}
void Logic::inputDigit(char c){
    if(isBlocked)
        return;
    if(c == '.'){
        if(currNum.inputDot())
        emit onChanged();
    } else if(c == 'w') { // двойной ноль
        if(currNum.inputDig('0')){
            currNum.inputDig('0');
            emit onChanged();
        }
    } else {
        if(currNum.inputDig(c))
            emit onChanged();
    }
}
void Logic::delDig(){
    if(isBlocked)
        return;
    if(currNum.delDig())
        emit onChanged();
}
void Logic::chSign(){
    if(isBlocked)
        return;
    if(currNum.changeSign())
        emit onChanged();

}
void Logic::doubleOp(char c){
    if(isBlocked)
        return;
    if(c == 'x' || c == ':'
        || c == '+' || c == '-'){
        op = c;
        prevNum = currNum;
        return;
    }
}
