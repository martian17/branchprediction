#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool* bpinit(int n,int* _mask){//n bits
    int size = (1<<n);
    bool* states = malloc(sizeof(bool)*size);//size one
    //to every possible immediate past history
    int mask = 0;
    for(int i = 0; i < n; i++){//initializing the mask and the states
        mask = mask<<1;
        mask |= 1;
        states[i] = false;
    }
    *_mask = mask;
    return states;
}

int main(){
    int mask;
    bool* table = bpinit(5,&mask);
    int state = 0;
    char input;
    int cnt = 0;
    int cntr = 0;
    while(true){
        cnt++;
        printf("Predicted result: %s\n",table[state]?"t":"f");
        printf("make your decision: ");
        scanf(" %c",&input);
        bool _input;
        if(input == 't'){
            _input = true;
        }else if(input == 'f'){
            _input = false;
        }else{
            printf("Invalid input %c\n",input);
            continue;
        }
        if(_input == table[state]){
            cntr++;
            printf("\033[F\n\e[42mPrediction Success :D!\e[0m\n");
        }else{
            printf("\033[F\n\e[41mPrediction Failed D:\e[0m\n");
        }
        printf("Prediction accuracy: %d%%\n",cntr*100/cnt);
        //printf("%d\n",state);
        table[state] = _input;
        state = ((state<<1)|(_input?1:0))&mask;
    }
}