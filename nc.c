#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

//itoa = int > str
//atoi = str > int

/*
    \type 1:Binary  2:Octal  3:Hexadecimal
*/

/*char NumbToHex(int numb){
    if(numb > 9)
        return (65 + numb - 10);
    return numb + '0';
}*/

int AnyToDec(char* num, char* type){
    //char buffer[12];
    int len;
    int increment = 1;
    int add;
    int sum = 0;
    int temp;

    //sprintf(buffer, "%d", num);
    len = strlen(num);
    switch (tolower(type[0]))
    {
    case 'b': //Bin
        add = 2;
        for(int x = len-1; x >= 0; x--)
        {
            sum += ((num[x] - '0') * increment);

            increment *= add;
        }
        break;
    
    case 'o': //Oct
        add = 8;
        for(int x = len-1; x >= 0; x--)
        {
            sum += ((num[x] - '0') * increment);

            increment *= add;
        }
        break;
    
    case 'h': //Hex
        add = 16;
        for(int x = len-1; x >= 0; x--)
        {
            switch (tolower(num[x]))
            {
            case 'a':
                sum += (10 * increment);
                break;

            case 'b':
                sum += (11 * increment);
                break;
            
            case 'c':
                sum += (12 * increment);
                break;
            
            case 'd':
                sum += (13 * increment);
                break;
            
            case 'e':
                sum += (14 * increment);
                break;
            
            case 'f':
                sum += (15 * increment);
                break;
            
            default:
                sum += ((num[x] - '0') * increment);
                break;
            }

            increment *= add;
        }
        break;

    case 'd':
        sum = atoi(num);
        break;

    default:
        fprintf(stderr, "wrong type! (D)ecimal, (B)inary, (O)ctal, (H)exadecimal");
        break;
    }

    return sum;
}

int DecToBin(int num){
    int left;
    char out[12] = "";
    char temp[12];
    while(num != 0)
    {
        left = num & 1;
        sprintf(temp, "%d", left);
        strcat(out, temp);

        num = num >> 1;
    }
    printf("\nnumber: %s\n", strrev(out));
    
}

int DecToOct(int num){
    int left;
    char out[12] = "";
    char temp[12];
    while(num > 0)
    {
        left = num % 8;
        sprintf(temp, "%d", left);
        strcat(out, temp);
        num = num >> 3;
    }
    printf("\nnumber: %s\n", strrev(out));
}

int DecToHex(int num){
    int left;
    char out[12] = "";
    char temp[12];
    while(num > 0)
    {
        left = num % 16;
        sprintf(temp, "%d", left);

        if(left > 9)
        {
            char tempchar = (65 + (left - 10));
            strncat(out , &tempchar, 1);
        }
        else
        {
            strcat(out, temp);
        }

        num = num >> 4;
    }
    printf("\nnumber: %s\n", strrev(out));
}

int main(int argc, char** argv)
{
    for(int i = 0; i < 36; i++)
    printf("%d => %c\n",i,NumbToHex(i));

    if(argc != 4)       
    {
        fprintf(stderr, "Wrong arguments!\n./process number (D = Decimal, B = Binar, O = Octal, H = Hexadecimal) to (D,B,O,H)");
        return EXIT_FAILURE;
    }

    char* number = argv[1];
    bool run = true;
    char* temp;
    //printf("START\n\n");
    printf("Original: %s\n\n", number);
    //printf("%s\n", type);
    //printf("%d\n", AnyToDec(number, argv[2]));

    if(strlen(argv[3]) > 1)
    {
        fprintf(stderr, "\n2nd type is not one char!\nShuting down");
        exit(1);
    }

    switch (tolower(argv[3][0]))
    {
    case 'b':
        DecToBin(AnyToDec(number, argv[2]));
        break;
    
    case 'o':
        DecToOct(AnyToDec(number, argv[2]));
        break;
    
    case 'h':
        DecToHex(AnyToDec(number, argv[2]));
        break;
    
    case 'd':
        printf("number: %d\n", AnyToDec(number, argv[2]));
        break;

    default:
        fprintf(stderr, "\nNot an decimal/binary/octal/hexadecimal system\n\n");
        break;
    }

    return EXIT_SUCCESS;
}