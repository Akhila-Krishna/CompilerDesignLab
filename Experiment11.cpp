#include<stdlib.h>
#include<stdio.h>
#include<string.h>

int k = 0, z = 0, i = 0, j = 0, c = 0;
char input[16], ac[20], stk[15], act[10];

void check();

int main() {
    printf("GRAMMAR is:\n\t E->E+E \n\t E->E*E \n\t E->(E) \n\t E->id \n");
    printf("Enter Input String: ");
    scanf("%s", input);

    c = strlen(input);
    strcpy(act, "SHIFT->");
    printf("Stack \t Input \t\tAction");
    for(k = 0, i = 0; j < c; k++, i++, j++) {
        if(input[j] == 'i' && input[j + 1] == 'd') {
            stk[i] = input[j];
            stk[i + 1] = input[j + 1];
            stk[i + 2] = '\0';
            input[j] = ' ';
            input[j + 1] = ' ';
            printf("\n$%s\t%s$\t%sid", stk, input, act);
                check();
        }
        else {
            stk[i] = input[j];
            stk[i + 1] = '\0';
            input[j] = ' ';
            printf("\n$%s\t%s$\t%ssymbols", stk, input, act);
                check();
        }
    }
}


void check() {
    strcpy(ac, "REDUCE TO E\t");
    for(z = 0; z < c; z++) {
        if(stk[z] == 'i' && stk[z + 1] == 'd') {
            stk[z] = 'E';
            stk[z + 1] = '\0';
            printf("\n$%s\t%s$\t%s", stk, input, ac);
            j++;
        }
    }

    for(z = 0; z < c; z++) {
       if(stk[z] == 'E' && stk[z + 1] == '+' && stk[z+2] == 'E') {
           stk[z] = 'E';
           stk[z + 1] = '\0';
           stk[z + 2] = '\0';
           printf("\n$%s\t%s$\t%s", stk, input, ac);
           i = i - 2;
        }
    }

    for(z = 0; z < c; z++) {
        if(stk[z] == 'E' && stk[z + 1] == '*' && stk[z + 2] == 'E') {
            stk[z] = 'E';
            stk[z + 1] = '\0';
            stk[z + 1] = '\0';
            printf("\n$%s\t%s$\t%s", stk, input, ac);
            i = i - 2;
         }
    }

    for(z = 0; z < c; z++) {
        if(stk[z] == '(' && stk[z + 1] == 'E' && stk[z + 2] == ')') {
            stk[z] = 'E';
            stk[z + 1] = '\0';
            stk[z + 1] = '\0';
            printf("\n$%s\t%s$\t%s", stk, input, ac);
            i = i - 2;
        }
    }
}