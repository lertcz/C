#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*
[space] 32
*/

bool isLetter(char c)
{
    if((c >= 'a') && (c <= 'z') || (c >= 'A') && (c <= 'Z'))
        return true;
    return false;
}

char codeLetter(char c,int increment)
{
    // A 65 90 | a 97 122
    increment %= 26;
    if((c >= 'a') && (c <= 'z'))
    {
        if((c+increment) < 'a')
           return 'z'+1+increment - (c - 'a');

        else if((c+increment) > 'z')
            return 'a' - 1 + increment;

        else
            return (c+increment);
        
    }
    else if((c >= 'A') && (c <= 'Z'))
    {
        if((c+increment) < 'A')
            return 'Z'+1+increment - (c - 'A');

        else if((c+increment) > 'Z')
           return 'A' - 1 + increment;

        else
            return (c+increment);
    }
    return 'a';
}

/*
    \type : 1 = code, 0 = encode
*/
int caesar_code(char *source,char *destination, int length, bool type,int increment)
{
    //Switching between coding/encoding
    if(!type)
        increment *= -1;
    
    //iterate over all chars in source
    for(int i = 0;i < length;i++)
    {
        //if is letter => code it
        //else destination = source
        if(isLetter(source[i]))
           destination[i] = codeLetter(source[i],increment);
        else
            destination[i] = source[i];
    }

    return EXIT_SUCCESS;
}

char ReadFile(char* source, int size, FILE* fd)
{
    for(int i = 0; i <= size;i++)
    {
        source[i] = fgetc(fd);
    }
}

void PrintInput(char* source, int size)
{
    printf("\nInput:\n");
    for(int i = 0; i <= size; i++)
    {
        printf("%c",source[i]);
    }
}

void PrintOutput(char* destination, int size)
{
    printf("\nOutput:\n");
    for(int i = 0; i <= size; i++)
    {
        printf("%c",destination[i]);
    }
}

int ArgcCheck(int argc, char** argv)
{
    if(argc == 3)
        return EXIT_SUCCESS;
    else   
        return EXIT_FAILURE;
}
/*
    \pre open file
    \fd file descriptor to file
    \post close file
*/
int GetSizeOfFile(FILE* fd)
{
    fseek(fd, 0, SEEK_END); // seek to end of file
    int size = ftell(fd); // get current file pointer
    fseek(fd, 0, SEEK_SET); // seek back to beginning of file
    return size;
}

int main(int argc, char** argv)
{
    if(ArgcCheck(argc,argv) == EXIT_FAILURE)
    {
        fprintf(stderr, "Wrong arguments.");
        return EXIT_FAILURE;
    }
    FILE * fd = fopen(argv[1],"r");
    int increment = atoi(argv[2]);
    if(fd == NULL)
    {
        fprintf(stderr, "File not founds.");
        return EXIT_FAILURE;
    }

    int size = GetSizeOfFile(fd);
    
    char source[size];
    char destination[size];

    ReadFile(source, size, fd);

    caesar_code(source,destination,size,1,increment);

    //test print
    PrintInput(source, size);

    PrintOutput(destination, size);

    fclose(fd);
    return EXIT_SUCCESS;
}