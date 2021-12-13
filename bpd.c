#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int* bpinit(int hist_len, int cnt_len){
    int size = (1<<hist_len);
    int* states = malloc(sizeof(int)*size);//size one
    
    //to every possible immediate past history
    for(int i = 0; i < hist_len; i++){//initializing the states
        states[i] = 1<<(cnt_len-1);
    }
    return states;
}

int main(){
    int hist_len = 2;
    int cnt_len = 2;
    int hist_mask = (1<<hist_len)-1;
    int cnt_mask = (1<<cnt_len)-1;
    int* table = bpinit(hist_len,cnt_len);
    int history = 0;
    int cnt = 0;
    int cntr = 0;
    char input;
    while(true){
        cnt++;
        bool prediction = (bool)((table[history]>>(cnt_len-1))&1);
        printf("Predicted result: %s\n",prediction?"t":"f");
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
        if(_input == prediction){
            cntr++;
            printf("\033[F\n\e[42mPrediction Success :D!\e[0m\n");
        }else{
            printf("\033[F\n\e[41mPrediction Failed D:\e[0m\n");
        }
        printf("Prediction accuracy: %d%%\n",cntr*100/cnt);
        printf("%d\n",history);
        printf("%d\n",table[history]);
        int counter = table[history];
        counter += _input?1:-1;
        if(counter < 0){
            counter = 0;
        }else if(counter > cnt_mask){
            counter = cnt_mask;
        }
        table[history] = counter;//write back
        history = ((history<<1)|(_input?1:0))&hist_mask;
    }
}