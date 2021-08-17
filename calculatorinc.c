/* Program to calculate eqn in c. You can calculate
basic clculations like (9*9+80-88/5). 
this program has some loop hole due to which
the program inverts the order from input 
eg 4/2 => 2/4 (etc) 
their is something wrong in inserting the string
to the stack and retreiving them, thats why 
there is some problem.there is also some problem
in the brackets and sign push and pop in stack.
also add float capability in this programm.

the main problem in this programs is found.
that is it contains a string returning functions
and tries to modify that string. instead what should
be done is pass the pointer no return pointer .
*/
#include <stdio.h> 
#include <string.h>
#include "stackforcalc.h"

// char str[50];

int isOperand(char b){
    if(b>='0' && b<='9'){
        return 1;
    }else{  
    return 0;
    }
}

int isOperator(char b){
    if(b=='+' || b=='-' || b=='*' || b=='/'){
        return 1;
    }
    return 0;
}

int getwt(char b){
    int g=-1;
    switch (b)
    {
    case '+':
    case '-':
    g=1;
    break;
    case '/':
    case '*':
    g=28787868;
    break;
    }
    return g;
}


int higherprecedence(char a,char b){
    int c=getwt(a);
    int d=getwt(b);
    return (c>=d)?1:0;
}

int infToPost(char *b,char *str){
    int j=0;
    for(int i=0;i<strlen(b);i++){
        if(b[i]== ' ' || b[i]== ',' ){
            continue;
        }

        else if(isOperator(b[i])){
            str[j]=' ';
            j++;
            while(!empty() && gettop() != '(' && higherprecedence(gettop(),b[i])){
                str[j]=gettop();
                j++;
                pop();
            }
            push(b[i]);
        }

        else if(isOperand(b[i])){
            str[j]=b[i];
            j++;
        }

        else if(b[i]=='('){
            push(b[i]);
        }

        else if(b[i] ==')'){
            while(!empty() && gettop() != '('){
                str[i]=gettop();
                j++;
                pop();
            }
            pop();
        }
    }
    while(!empty()){
        str[j]=gettop();
        j++;
        pop();
    }
}

int Evaluate(int t,char y,int r){
    int ty;
    switch(y){
        case '+':
        ty=t+r;
        break;
        case '-':
        ty=r-t; //i inverted this.
        break;
        case '*':
        ty=r*t; //i inverted this.
        break;
        case '/':
        ty=r/t; //i inverted this.
        break;
        default:
        ty=-1;
        break;
    }
    return ty;
}

int calculatepostfix(char *c){
    for(int i=0;i<strlen(c);i++){
        if(c[i]==' ' || c[i]==','){
            continue;
        }

        else if(isOperator(c[i])){
            int op1=gettop2();
            pop2();
            int op2=gettop2();
            pop2();
            int oper=Evaluate(op1,c[i],op2);
            push2(oper);
        }
        else if(isOperand(c[i])){
            int res=0;
            while(i<strlen(c) && isOperand(c[i])){
                res=(res*10)+(c[i]-'0');
                i++;
            }
            i--;
            push2(res);
        }
    }
    return gettop2();
}

int main(){
    char b[65];
    printf("\n \n**-- Calculator --**\n");
    printf("Enter expression: ");
    fgets(b,sizeof(b),stdin);
    char str[50];
    infToPost(b,str);
    int tt =calculatepostfix(str);
    printf("Your answer is: %d",tt);
}