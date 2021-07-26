//
// Created by socktt on 7/25/21.
//

#include "Misc.h"
#include "typeDef.h"

int strcmp(char str1[], char str2[]) {
    for(int i = 0;i<=256;i++) {
        if(str1[i] + str2[i] == 0) {
            return 0;
        } else if(str1[i]!=str2[i]){
            return 1;
        }
    }
    return 0;
}

int strlen(char str[]) {
    for(int i=0;i<=256;i++){
        if(str[i] == 0){
            return i;
        }
    }
    return 256;
}