#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>

int doIndex[25];
int doCount = 0;
int arraySize = 0;
int arrayOpen[25];
int arrayClose[25];
int virgulCountint = 0;
int openCurlyCount = 0;

int boolIndexesCount = 0;
int doubleIndexesCount = 0;
int satirsonuSemiColon[50];
int intCount = 0;
int controllerOperations[100];
int operationsIndexes[50];
int esittirIndexes[1000];
int forIndexes[1000];
int charIndexes[1000];
int floatIndexes[1000];
int boolIndexes[25];
int doubleIntexes[1000];
int forIndexesLevels[1000];
int icIceForIndexes[1000];
int curlyIndexes[1000];
int openCurlyIndexes[1000];
int whileIndexes[1000];
int switchIndexes[50];
int intIndexes[50];
int braceIndexes[100];
int semiColonIndexes[100];
int closedBraceIndexes[100];
int inlinesemiColon[50];
int forCount = 0;
int whileCount = 0;
int charCount = 0;
int floatCount = 0;
int doubleCount = 0;
int esittirCount = 0;
int inlinesemicolonCount = 0;
int semicolonCount = 0;

bool whileinwhile = false;
bool foricindewhile = false;
bool whileicindefor = false;

int arrayCount = 0;

int findIndex(const char *str, const char *aranan)
{
    const char *ptr = str;
    int count = 0;
    int level = 1;
    int index = 0;
    while ((ptr = strstr(ptr, aranan)) != NULL)
    {
        ptr += strlen(aranan);
        count++;

        index = (ptr - str) - strlen(aranan);
        if (strcmp(aranan, "for") == 0)
        {
            forIndexes[count] = index;
            level++;
            forCount++;
        }
        else if (strcmp(aranan, "[") == 0)
            arrayOpen[count] = index;
        else if (strcmp(aranan, "]") == 0)
            arrayClose[count] = index;
        else if (strcmp(aranan, "do") == 0)
        {
            doIndex[count] = index;
            doCount++;
        }
        else if (strcmp(aranan, "double") == 0)
        {
            doubleIntexes[count] = index;
            doubleIndexesCount++;
        }
        else if (strcmp(aranan, "bool") == 0)
        {
            boolIndexes[count] = index;
            boolIndexesCount++;
        }
        else if (strcmp(aranan, "char") == 0)
        {
            charIndexes[count] = index;
            charCount++;
        }
        else if (strcmp(aranan, "float") == 0)
        {
            floatIndexes[count] = index;
            floatCount++;
        } //
        else if (strcmp(aranan, "while") == 0)
        {
            whileIndexes[count] = index;
            whileCount++;
        }

        else if (strcmp(aranan, "int") == 0)
        {
            if ((str[index - 1] == 'r' && str[index - 2] == 'p'))
            {

                count--;
                continue;
            }
            else
            {
                intIndexes[count] = index;

                intCount++;
            }
        }
        else if (strcmp(aranan, ";") == 0)
        {
            semiColonIndexes[count] = index;
            semicolonCount++;
        }
        else if (strcmp(aranan, "(") == 0)
        {
            braceIndexes[count] = index;
        }
        else if (strcmp(aranan, ")") == 0)
        {
            closedBraceIndexes[count] = index;
        }
        else if (strcmp(aranan, "}") == 0)
        {
            curlyIndexes[count] = index;
            level--;
        }
        else if (strcmp(aranan, "{") == 0)
        {
            openCurlyIndexes[count] = index;
            openCurlyCount++;
        }
        else if (strcmp(aranan, "+") == 0)
        {
            operationsIndexes[count] = index;
        }
        else if (strcmp(aranan, "=") == 0)
        {
            esittirIndexes[count] = index;
            esittirCount++;
        }
        //printf("%s indexleri: %d\n", aranan, index);
    }
    return index;
}

char *ReadFile(char *filename)
{
    char *buffer = NULL;
    int string_size, read_size;
    FILE *handler = fopen(filename, "r");

    if (handler)
    {
        fseek(handler, 0, SEEK_END);
        string_size = ftell(handler);
        rewind(handler);

        buffer = (char *)malloc(sizeof(char) * (string_size + 1));
        read_size = fread(buffer, sizeof(char), string_size, handler);

        buffer[string_size] = '\0';

        if (string_size != read_size)
        {
            free(buffer);
            buffer = NULL;
        }

        fclose(handler);
    }
    return buffer;
}
char ustelRecursive;

int checkRecursive(const char *stringName, int mainIndex, int intIndexes[], int semiColonIndexes[], int esittirIndexes[])
{
    int ilkNoktaliVirgul[100];
    for (int i = 0; i < 100; i++)
    {
        ilkNoktaliVirgul[i] = 0;
    }
    int ilkNoktaliVirgulCount = 1;
    for (int i = 1; i < esittirCount + 1; i++)
    {
        for (int j = 0; j < strlen(stringName); j++)
        {
            if (semiColonIndexes[j] > esittirIndexes[i])
            {
                ilkNoktaliVirgul[ilkNoktaliVirgulCount] = semiColonIndexes[j];
                ilkNoktaliVirgulCount++;
                break;
            }
        }
    }
    int flag = 0;
    for (int i = 0; i < esittirCount; i++)
    {
        if (intIndexes[mainIndex] < esittirIndexes[i])
        {
            for (int j = esittirIndexes[i]; j < ilkNoktaliVirgul[i]; j++)
            {

                if (stringName[j] == '(')
                {
                    //printf("\nRECURSIVE TESPIT EDILDI\n\n");
                    if (stringName[j + 2] == '/')
                    {
                        //printf("logaritmik tespit edildi\n");
                        flag = 2;
                        //flag = 1 lineer flag = 2 logaritmik flag = 3 üstel
                    }
                    else if (stringName[j + 2] == '*')
                    {
                        ustelRecursive = stringName[j + 3];
                        //printf("üstel tespit edildi\n");
                        flag = 3;
                    }
                    else
                        flag = 1;
                    break;
                }
            }
        }
    }

    return flag;
}

int main()
{
    char *string = ReadFile("code.txt");
    printf("\n\n\n\n\n");

    findIndex(string, "for");
    findIndex(string, "}");
    findIndex(string, "while");
    findIndex(string, "(");
    findIndex(string, ")");
    findIndex(string, ";");
    findIndex(string, "int");
    findIndex(string, "[");
    findIndex(string, "]");
    findIndex(string, "{");
    findIndex(string, "do");
    findIndex(string, "double");
    findIndex(string, "char");
    findIndex(string, "float");
    findIndex(string, "bool");
    findIndex(string, "=");

    int ilkparantez[100];
    int ilkKapananParantez[100];

    int ilkParantezCount = 0;
    int ilkKapananParantezCount = 0;

    for (int i = 1; i < forCount + 1; i++)
    {
        for (int j = 0; j < strlen(string); j++)
        {
            if (braceIndexes[j] > forIndexes[i])
            {
                ilkparantez[ilkParantezCount] = braceIndexes[j];
                ilkParantezCount++;
                break;
            }
        }
    }
    int mainIndex = 0;
    for (int i = 0; i < intCount; i++)
    {
        for (int j = 0; j < strlen(string); j++)
        {
            if (string[intIndexes[i] + j] == 'm' && string[intIndexes[i] + j + 1] == 'a' && string[intIndexes[i] + j + 2] == 'i' && string[intIndexes[i] + j + 3] == 'n')
            {
                mainIndex = i;
                //printf("Kacinci indexte main var :%d\n",i);
                break;
            }
        }
    }
    if (mainIndex >= 1)
        printf("\n\t\tText dosyasi bir kod parcacigi iceriyor!\n\n");
    else
        printf("\n\t\tText dosyasi bir kod parcacigi icermiyor!\n\n");
    //ilk for ' a for arrayi kadar döndür ikinci for string length kadar döndür
    int arrayCount = 0;
    int inttutmak = 0;
    int koseliCount = 0;
    int koseliIntler[100];
    int ilkNoktaliVirgulInt[100];
    int ilkNoktaliVirgulIntCount = 0;
    for (int i = 0; i < 100; i++)
    {
        koseliIntler[i] = 0;
        ilkNoktaliVirgulInt[i] = 0;
    }
    for (int i = mainIndex + 1; i < intCount + 1; i++)
    {
        for (int j = 0; j < strlen(string); j++)
        {
            if (semiColonIndexes[j] > intIndexes[i])
            {
                ilkNoktaliVirgulInt[ilkNoktaliVirgulIntCount] = semiColonIndexes[j];
                ilkNoktaliVirgulIntCount++;
                break;
            }
        }
    }
    for (int i = mainIndex + 1; i < intCount + 1; i++)
    {
        inttutmak++;

        for (int j = intIndexes[i]; j < ilkNoktaliVirgulInt[(i - 1) - mainIndex]; j++)
        {

            if (string[j] == ',')
                virgulCountint++;
            else if (string[j] == '[')
            {
                koseliCount++;
                if (koseliIntler[i] == 0)
                    koseliIntler[i] = koseliCount;
                else
                    koseliIntler[i]++;
                arraySize++;
                if (arraySize != 0)
                    arrayCount = 1;
                koseliCount = 0;
            }
        }
    }
    inttutmak += virgulCountint;

    int virgulCountfloat = 0;
    int floattutmak = 0;
    int ilkNoktaliVirgulFloatCount = 0;
    int ilkNoktaliVirgulFloat[100];

    for (int i = 0; i < 100; i++)
        ilkNoktaliVirgulFloat[i] = 0;
    for (int i = 0; i < floatCount + 1; i++)
    {
        if (floatIndexes[i] > intIndexes[mainIndex])
        {
            for (int j = 0; j < strlen(string); j++)
            {
                if (semiColonIndexes[j] > floatIndexes[i])
                {
                    ilkNoktaliVirgulFloat[ilkNoktaliVirgulFloatCount] = semiColonIndexes[j];
                    ilkNoktaliVirgulFloatCount++;
                    break;
                }
            }
        }
    }

    for (int i = 1; i < floatCount + 1; i++)
    {
        floattutmak++;

        for (int j = floatIndexes[i]; j < ilkNoktaliVirgulFloat[i-1] + 1; j++)
        {
            if (string[j] == ',')
                virgulCountfloat++;
        }
    }
    floattutmak += virgulCountfloat;


    int ilkNoktaliVirgulChar[100];
    int ilkNoktaliVirgulCharCount = 0;
    int chartutmak = 0;
    int virgulCountChar = 0;

    for (int i = 0; i < 100; i++)
        ilkNoktaliVirgulChar[i] = 0;
    for (int i = 0; i < charCount + 1; i++)
    {
        if (charIndexes[i] > intIndexes[mainIndex])
        {
            for (int j = 0; j < strlen(string); j++)
            {
                if (semiColonIndexes[j] > charIndexes[i])
                {
                    ilkNoktaliVirgulChar[ilkNoktaliVirgulCharCount] = semiColonIndexes[j];
                    ilkNoktaliVirgulCharCount++;
                    break;
                }
            }
        }
    }

    for (int i = 1; i < charCount + 1; i++)
    {
        chartutmak++;

        for (int j = charIndexes[i]; j < ilkNoktaliVirgulChar[i-1] + 1; j++)
        {
            if (string[j] == ',')
                virgulCountChar++;
        }
    }
    chartutmak += virgulCountChar;


    for (int i = 0; i < ilkParantezCount; i++)
    {
        for (int j = 1; j < strlen(string) + 1; j++)
        {
            if (closedBraceIndexes[j] > ilkparantez[i])
            {
                ilkKapananParantez[ilkKapananParantezCount] = closedBraceIndexes[j];
                ilkKapananParantezCount++;
                break;
            }
        }
    }
    int algoritmaSize;
    if(inttutmak > 0 && floattutmak == 0 && chartutmak == 0)
    {
        algoritmaSize = (inttutmak - arrayCount) * (sizeof(int));
    }
    else if(inttutmak == 0 && floattutmak > 0 && chartutmak == 0)
    {
        algoritmaSize = floattutmak * (sizeof(float));
    }
    else if(inttutmak > 0 && floattutmak == 0 && chartutmak > 0)
    {
        algoritmaSize = chartutmak * (sizeof(char));
    }
    else if(inttutmak > 0 && floattutmak > 0 && chartutmak == 0)
    {
        algoritmaSize = (inttutmak- arrayCount) * sizeof(int) + floattutmak * sizeof(float);
    }
    else if(inttutmak > 0 && floattutmak == 0 && chartutmak > 0)
    {
        algoritmaSize = (inttutmak - arrayCount) * sizeof(int) + chartutmak * sizeof(char);
    }
    else if(inttutmak == 0 && floattutmak > 0 && chartutmak > 0)
    {
        algoritmaSize = floattutmak * sizeof(float) + chartutmak * sizeof(char);
    }
    else if(inttutmak > 0 && floattutmak > 0 && chartutmak == 0)
    {
        algoritmaSize = (inttutmak - arrayCount) * sizeof(int) + floattutmak * sizeof(float);
    }
    else if(inttutmak > 0 && floattutmak > 0 && chartutmak > 0)
    {
        algoritmaSize = (inttutmak - arrayCount) * sizeof(int) + floattutmak * sizeof(float) + chartutmak * sizeof(char);
    }
    //printf("%d",algoritmaSize);

    int whileicinde_for = 0;
    int whilecinde_for_lineer = 0;
    int whilecinde_for_log = 0;
    int whilecinde_for_us = 0;

    int whilein_while = 0;
    int whilein_while_lineer = 0;
    int whilein_while_log = 0;
    int whilein_while_us = 0;
    //forun ici kontrolü
    int h = 0, t = 1, y = 1, g = 1;
    int insideForCount = 0;
    int forarasindakisuslu = 0;
    int currentForIndex = 0;
    int yeniForIndex = 1;
    int foricinde_while = 0;
    int p;
    int foricinde_while_lineer = 0;
    int foricinde_while_log = 0;
    int foricinde_while_us = 0;
    if (forCount >= 1)
    {
        for (int i = 0; i <= strlen(string); i++)
        {
            if (openCurlyIndexes[t] > forIndexes[y])
            {
                if (curlyIndexes[g] > forIndexes[y])
                {
                    for (int j = openCurlyIndexes[t]; j < curlyIndexes[g]; j++)
                    {
                        if ('f' == string[j] && 'o' == string[j + 1] && 'r' == string[j + 2])
                        {
                            currentForIndex = forIndexes[y - insideForCount];
                            icIceForIndexes[y - insideForCount] = currentForIndex;
                            //printf("\t\tIc ice for bulundu\n");
                            //printf("\t\tIndexi : %d\n", j);
                            //forIndexesLevels[y-insideForCount]++;

                            for (int o = forIndexes[y]; o < forIndexes[y + 1]; o++)
                            {
                                if (string[o] == '}')
                                    forarasindakisuslu++;
                                if (forarasindakisuslu >= insideForCount + 1)
                                {
                                    currentForIndex = forIndexes[(y + forarasindakisuslu) - insideForCount];
                                    //icIceForIndexes[y] = 0;
                                    icIceForIndexes[(y + forarasindakisuslu) - insideForCount] = currentForIndex;
                                    forIndexesLevels[(y + forarasindakisuslu) - insideForCount] = 0;
                                    yeniForIndex = (y + forarasindakisuslu) - insideForCount;
                                    forarasindakisuslu = 0;
                                }
                            }
                            //yeniForIndex++;
                            forIndexesLevels[yeniForIndex]++;
                            //printf("%d. for'un leveli :%d\n", icIceForIndexes[yeniForIndex], forIndexesLevels[yeniForIndex]);
                            insideForCount++;
                            y++;
                            g++; //sonradan eklendi
                            t++; //sonradan eklendi
                        }
                        else if ('w' == string[j] && 'h' == string[j + 1] && 'i' == string[j + 2])
                        {
                            foricindewhile = true;
                            printf("\t\tFor'un icinde while bulundu\n");
                            printf("\t\tIndexi : %d\n", j);

                            for (int k = openCurlyIndexes[t]; k < curlyIndexes[g + 1]; k++)
                            {
                                if (string[j + foricinde_while] == '+' && string[j + foricinde_while + 1] == '=')
                                    foricinde_while_lineer++;
                                else if (string[j + foricinde_while] == '-' && string[j + foricinde_while + 1] == '=')
                                    foricinde_while_lineer++;
                                else if (string[j + foricinde_while] == '*' && string[j + foricinde_while + 1] == '=')
                                {
                                    if ((string[j + foricinde_while + 2] && string[j + foricinde_while + 3] == ' '))
                                        foricinde_while_us = string[j + foricinde_while + 2];
                                    else if ((string[j + foricinde_while + 2] == ' ' && string[j + foricinde_while + 3]))
                                        foricinde_while_us = string[j + foricinde_while + 3];
                                    else if (string[j + foricinde_while + 2] && string[j + foricinde_while + 3] == ')')
                                        foricinde_while_us = string[j + foricinde_while + 2];
                                    else if (string[j + foricinde_while + 2] && string[j + foricinde_while + 3] == ';')
                                        foricinde_while_us = string[j + foricinde_while + 2];
                                }
                                else if (string[j + foricinde_while] == '/' && string[j + foricinde_while + 1] == '=')
                                    foricinde_while_log++;
                                else if (string[j + foricinde_while] == '+' && string[j + foricinde_while + 1] == '+')
                                    foricinde_while_lineer++;
                                else if (string[j + foricinde_while] == '-' && string[j + foricinde_while + 1] == '-')
                                    foricinde_while_lineer++;
                                foricinde_while++;
                            }

                            g++;
                            t++; //sonradan eklendi
                            y++; //sonradan eklendi
                        }
                    }
                    g++;
                    t++;
                }
            }
            else
                t++;
        }
    }

    int whileicindeforCount = 0;
    int while_lineer = 0;
    int while_log = 0;
    int while_us = 0;
    char while_us_deger;
    //while ici kontrolü
    h = 0, t = 1, y = 1, g = 1;
    if (whileCount >= 1)
    {
        for (int i = 0; i <= strlen(string); i++)
        {
            if (openCurlyIndexes[t] > whileIndexes[y])
            {
                if (curlyIndexes[g] > whileIndexes[y])
                {
                    for (int j = openCurlyIndexes[t]; j < curlyIndexes[g]; j++)
                    {
                        if ('f' == string[j] && 'o' == string[j + 1] && 'r' == string[j + 2])
                        {
                            whileicindefor = true;
                            whileicindeforCount++;
                            printf("\t\tWhile'in icinde for bulundu\n");
                            printf("\t\tIndexi : %d\n", j);
                            for (int k = openCurlyIndexes[t]; k < curlyIndexes[g + 1]; k++)
                            {
                                if (string[j + whileicinde_for] == '+' && string[j + whileicinde_for + 1] == '=')
                                {
                                    whilecinde_for_lineer++;
                                    break;
                                }
                                else if (string[j + whileicinde_for] == '-' && string[j + whileicinde_for + 1] == '=')
                                {
                                    whilecinde_for_lineer++;
                                    break;
                                }
                                else if (string[j + whileicinde_for] == '*' && string[j + whileicinde_for + 1] == '=')
                                {
                                    if ((string[j + whileicinde_for + 2] && string[j + whileicinde_for + 3] == ' '))
                                    {
                                        whilecinde_for_us = string[j + whileicinde_for + 2];
                                        break;
                                    }

                                    else if ((string[j + whileicinde_for + 2] == ' ' && string[j + whileicinde_for + 3]))
                                    {
                                        whilecinde_for_us = string[j + whileicinde_for + 3];
                                        break;
                                    }
                                    else if ((string[j + whileicinde_for + 2] && string[j + whileicinde_for + 3] == ')'))
                                    {
                                        whilecinde_for_us = string[j + whileicinde_for + 2];
                                        break;
                                    }
                                }
                                else if (string[j + whileicinde_for] == '/' && string[j + whileicinde_for + 1] == '=')
                                {
                                    whilecinde_for_log++;
                                    break;
                                }
                                else if (string[j + whileicinde_for] == '+' && string[j + whileicinde_for + 1] == '+')
                                {
                                    whilecinde_for_lineer++;
                                    break;
                                }
                                else if (string[j + whileicinde_for] == '-' && string[j + whileicinde_for + 1] == '-')
                                {
                                    whilecinde_for_lineer++;
                                    break;
                                }
                                whileicinde_for++;
                            }
                            for (int l = openCurlyIndexes[t]; l < j; l++)
                            {
                                if (string[l] == '+' && string[l + 1] == '+')
                                {
                                    while_lineer++;
                                }
                                else if (string[l] == '+' && string[l + 1] == '-')
                                {
                                    while_lineer++;
                                }
                                else if (string[l] == '+' && string[l + 1] == '=')
                                {
                                    while_lineer++;
                                }
                                else if (string[l] == '-' && string[l + 1] == '=')
                                {
                                    while_lineer++;
                                }
                                else if (string[l] == '*' && string[l + 1] == '=')
                                {
                                    while_us++;
                                    if (string[l + 2] && string[l + 3] == ';')
                                    {
                                        while_us_deger = string[l + 2];
                                    }
                                    else if (string[l + 2] == ' ' && string[l + 3] == ';')
                                    {
                                        while_us_deger = string[l + 2];
                                    }
                                    else if (string[l + 2] == ' ' && string[l + 3])
                                    {
                                        while_us_deger = string[p + 3];
                                    }
                                    else if (string[l + 2] && string[p + 3] == ' ')
                                    {
                                        while_us_deger = string[p + 3];
                                    }
                                }
                                else if (string[l] == '/' && string[l + 1] == '=')
                                {
                                    while_log++;
                                }
                            }
                            for (int p = curlyIndexes[g]; p < curlyIndexes[g + 1]; p++)
                            {
                                if (string[p] == '+' && string[p + 1] == '+')
                                {
                                    while_lineer++;
                                }
                                else if (string[p] == '+' && string[p + 1] == '-')
                                {
                                    while_lineer++;
                                }
                                else if (string[p] == '+' && string[p + 1] == '=')
                                {
                                    while_lineer++;
                                }
                                else if (string[p] == '-' && string[p + 1] == '=')
                                {
                                    while_lineer++;
                                }
                                else if (string[p] == '*' && string[p + 1] == '=')
                                {
                                    while_us++;
                                    if (string[p + 2] && string[p + 3] == ';')
                                    {
                                        while_us_deger = string[p + 2];
                                    }
                                    else if (string[p + 2] == ' ' && string[p + 3] == ';')
                                    {
                                        while_us_deger = string[p + 2];
                                    }
                                    else if (string[p + 2] == ' ' && string[p + 3])
                                    {
                                        while_us_deger = string[p + 3];
                                    }
                                    else if (string[p + 2] && string[p + 3] == ' ')
                                    {
                                        while_us_deger = string[p + 3];
                                    }
                                }
                                else if (string[p] == '/' && string[p + 1] == '=')
                                {
                                    while_log++;
                                }
                            }
                            //Yer Karmasikligi : %d*n^%d+%d\n\n",notasyon_us_us,foricinde_while_lineer,sizeof(int),arraySize,(inttutmak-arrayCount)*sizeof(int));
                            if (while_lineer > 0 && while_log == 0 && while_us_deger == 0 && whilecinde_for_lineer > 0 && whilecinde_for_log == 0 && whilecinde_for_us == 0)
                            {
                                printf("\n\n\t\tNotasyon : O(N^%d * N^%d)\n\n\t\tYer Karmasikligi : %dn^%d+%d\n", while_lineer, whilecinde_for_lineer, sizeof(int), arraySize, algoritmaSize);
                            }
                            else if (while_lineer == 0 && while_log > 0 && while_us_deger == 0 && whilecinde_for_lineer == 0 && whilecinde_for_log > 0 && whilecinde_for_us == 0)
                            {
                                printf("\n\n\t\tNotasyon : O(logN^%d * logN^%d)\n\n\t\tYer Karmasikligi : %dn^%d+%d\n", while_log, whilecinde_for_log, sizeof(int), arraySize, algoritmaSize);
                            }
                            else if (while_lineer == 0 && while_log == 0 && while_us_deger > 0 && whilecinde_for_lineer == 0 && whilecinde_for_log == 0 && whilecinde_for_us > 0)
                            {
                                printf("\n\n\t\tNotasyon : O(%c^n * %c^n)\n\n\t\tYer Karmasikligi : %dn^%d+%d\n", while_us_deger, whilecinde_for_us, sizeof(int), arraySize,algoritmaSize);
                            }
                            else if (while_lineer > 0 && while_log == 0 && while_us_deger == 0 && whilecinde_for_lineer == 0 && whilecinde_for_log > 0 && whilecinde_for_us == 0)
                            {
                                printf("\n\n\t\tNotasyon : O(N^%d * logN^%d)\n\n\t\tYer Karmasikligi : %dn^%d+%d\n", while_lineer, whilecinde_for_log, sizeof(int), arraySize, algoritmaSize);
                            }
                            else if (while_lineer == 0 && while_log > 0 && while_us_deger == 0 && whilecinde_for_lineer > 0 && whilecinde_for_log == 0 && whilecinde_for_us == 0)
                            {
                                printf("\n\n\t\tNotasyon : O(logN^%d * N^%d)\n\n\t\tYer Karmasikligi : %dn^%d+%d\n", while_log, whilecinde_for_lineer, sizeof(int), arraySize, algoritmaSize);
                            }
                            else if (while_lineer == 0 && while_log == 0 && while_us_deger > 0 && whilecinde_for_lineer == 0 && whilecinde_for_log > 0 && whilecinde_for_us == 0)
                            {
                                printf("\n\n\t\tNotasyon : O(%c^n * logN^%d)\n\n\t\tYer Karmasikligi : %dn^%d+%d\n", while_us_deger, whilecinde_for_log, sizeof(int), arraySize, algoritmaSize);
                            }
                            else if (while_lineer == 0 && while_log > 0 && while_us_deger > 0 && whilecinde_for_lineer == 0 && whilecinde_for_log > 0 && whilecinde_for_us > 0)
                            {
                                printf("\n\n\t\tNotasyon : O(logN^%d * %c^n)\n\n\t\tYer Karmasikligi : %dn^%d+%d\n", while_log, whilecinde_for_log, sizeof(int), arraySize,algoritmaSize);
                            }
                            else if (while_lineer == 0 && while_log == 0 && while_us_deger > 0 && whilecinde_for_lineer > 0 && whilecinde_for_log == 0 && whilecinde_for_us == 0)
                            {
                                printf("\n\n\t\tNotasyon : O(%c^n * N^%d)\n\n\t\tYer Karmasikligi : %dn^%d+%d\n", while_us_deger, whilecinde_for_lineer, sizeof(int), arraySize,algoritmaSize);
                            }
                            else if (while_lineer > 0 && while_log == 0 && while_us_deger == 0 && whilecinde_for_lineer == 0 && whilecinde_for_log == 0 && whilecinde_for_us > 0)
                            {
                                printf("\n\n\t\tNotasyon : O(N^%d * %c^n)\n\n\t\tYer Karmasikligi : %dn^%d+%d\n", while_lineer, whilecinde_for_us, sizeof(int), arraySize,algoritmaSize);
                            }
                            p++;
                            //insideForCount++;
                            y++;
                            g++; //sonradan eklendi
                            t++; //sonradan eklendi
                        }

                        else if ('w' == string[j] && 'h' == string[j + 1] && 'i' == string[j + 2])
                        {
                            whileinwhile = true;
                            printf("\t\tWhile icinde while bulundu !");
                            printf("\t\tIndexi : %d\n", j);
                            for (int k = openCurlyIndexes[t]; k < curlyIndexes[g + 1]; k++)
                            {
                                if (string[j + whilein_while] == '+' && string[j + whilein_while + 1] == '=')
                                {
                                    whilein_while_lineer++;
                                }
                                else if (string[j + whilein_while] == '-' && string[j + whilein_while + 1] == '=')
                                {
                                    whilein_while_lineer++;
                                }
                                else if (string[j + whilein_while] == '*' && string[j + whilein_while + 1] == '=')
                                {
                                    if ((string[j + whilein_while + 2] && string[j + whilein_while + 3] == ' '))
                                    {
                                        whilein_while_us = string[j + whilein_while + 2];
                                    }

                                    else if ((string[j + whilein_while + 2] == ' ' && string[j + whilein_while + 3]))
                                    {
                                        whilein_while_us = string[j + whilein_while + 3];
                                    }
                                    else if ((string[j + whilein_while + 2] && string[j + whilein_while + 3] == ';'))
                                    {
                                        whilein_while_us = string[j + whilein_while + 2];
                                    }
                                }
                                else if (string[j + whilein_while] == '/' && string[j + whilein_while + 1] == '=')
                                {
                                    whilein_while_log++;
                                }
                                else if (string[j + whilein_while] == '+' && string[j + whilein_while + 1] == '+')
                                {
                                    whilein_while_lineer++;
                                }
                                else if (string[j + whilein_while] == '-' && string[j + whilein_while + 1] == '-')
                                {
                                    whilein_while_lineer++;
                                }
                                whilein_while++;
                            }
                            if (whilein_while_lineer > 0 && whilein_while_log == 0 && whilein_while_us == 0)
                            {
                                printf("\n\n\t\tNotasyon : O(N^%d)\n\n\t\tYer Karmasikligi : %dn^%d+%d\n", whilein_while_lineer, sizeof(int), arraySize,algoritmaSize);
                            }
                            if (whilein_while_lineer == 0 && whilein_while_log > 0 && whilein_while_us == 0)
                            {
                                printf("\n\n\t\tNotasyon : O(logN^%d)\n\n\t\tYer Karmasikligi : %dn^%d+%d\n", whilein_while_log, sizeof(int), arraySize, algoritmaSize);
                            }
                            if (whilein_while_lineer == 0 && whilein_while_log == 0 && whilein_while_us > 0)
                            {
                                printf("\n\n\t\tNotasyon : O(%c^n)\n\n\t\tYer Karmasikligi : %dn^%d+%d\n", whilein_while_us, sizeof(int), arraySize, algoritmaSize);
                            }
                            if (whilein_while_lineer > 0 && whilein_while_log > 0 && whilein_while_us == 0)
                            {
                                printf("\n\n\t\tNotasyon : O(N^%d * logN^%d)\n\n\t\tYer Karmasikligi : %dn^%d+%d\n", whilein_while_lineer, whilein_while_log, sizeof(int), arraySize,algoritmaSize);
                            }
                            if (whilein_while_lineer > 0 && whilein_while_log > 0 && whilein_while_us == 0)
                            {
                                printf("\n\n\t\tNotasyon : O(N^%d * logN^%d)\n\n\t\tYer Karmasikligi : %dn^%d+%d\n", whilein_while_lineer, whilein_while_log, sizeof(int), arraySize, algoritmaSize);
                            }
                            if (whilein_while_lineer > 0 && whilein_while_log == 0 && whilein_while_us > 0)
                            {
                                printf("\n\n\t\tNotasyon : O(N^%d * %c^n)\n\n\t\tYer Karmasikligi : %dn^%d+%d\n", whilein_while_lineer, whilein_while_us, sizeof(int), arraySize,algoritmaSize);
                            }
                            if (whilein_while_lineer == 0 && whilein_while_log > 0 && whilein_while_us > 0)
                            {
                                printf("\n\n\t\tNotasyon : O(logN^%d * %c^n)\n\n\t\tYer Karmasikligi : %dn^%d+%d\n", whilein_while_log, whilein_while_us, sizeof(int), arraySize,algoritmaSize);
                            }
                            g++;
                            t++; //sonradan eklendi
                            y++; //sonradan eklendi
                        }
                    }
                    g++;
                    t++;
                }
            }
            else
                t++;
        }
    }

    int max_value = forIndexesLevels[0];
    int max_index = 0;
    for (int i = 0; i < forCount; i++)
    {
        if (max_value < forIndexesLevels[i])
        {
            max_value = forIndexesLevels[i];
            max_index = i;
        }
    }

    for (int i = 0; i < forCount; i++) // burada for'daki 2. noktalı virgülü diziye çekiyoruz.
    {
        for (int j = 0; j < semicolonCount; j++) // buraya j<15 değil semicolonsize kadar girilecek!
        {
            if (ilkparantez[i] < semiColonIndexes[j] && semiColonIndexes[j] < ilkKapananParantez[i])
            {
                inlinesemiColon[i] = semiColonIndexes[j];
                inlinesemicolonCount++;
            }
            else
                continue;
        }
    }

    int k = 0; // burada da koddaki bütün " ;i++) " şeklindeki kısımları diziye atıyoruz.
    if (forCount >= 1)
    {
        for (int i = max_index - 1; i < max_index + max_value; i++)
        {
            for (int j = 0; j < (ilkKapananParantez[i] - inlinesemiColon[i]) + 1; j++)
            {
                controllerOperations[k] = string[inlinesemiColon[i] + j];
                k++;
            }
        }
    }
    int whileLineerUs = 0;
    int whileLogUs = 0;
    int whileUsUs = 0;
    if (whileCount >= 1)
    {

        int n = 0;
        for (int i = 1; i <= whileCount; i++) // whiledan sonraki artış parametresi kontrolü
        {
            for (int j = 1; j <= openCurlyCount; j++)
            {
                if (openCurlyIndexes[j] > whileIndexes[i])
                {
                    while (string[openCurlyIndexes[j] + n] != '}')
                    {
                        if (string[openCurlyIndexes[j] + n] == '+' && string[openCurlyIndexes[j] + n + 1] == '=')
                            whileLineerUs++;
                        else if (string[openCurlyIndexes[j] + n] == '-' && string[openCurlyIndexes[j] + n + 1] == '=')
                            whileLineerUs++;
                        else if (string[openCurlyIndexes[j] + n] == '/' && string[openCurlyIndexes[j] + n + 1] == '=')
                            whileLogUs++;
                        else if (string[openCurlyIndexes[j] + n] == '*' && string[openCurlyIndexes[j] + n + 1] == '=')
                        {
                            if ((string[openCurlyIndexes[j] + n + 2] && string[openCurlyIndexes[j] + n + 3] == ' '))
                                whileUsUs = string[openCurlyIndexes[j] + n + 2];
                            else if ((string[openCurlyIndexes[j] + n + 2] == ' ' && string[openCurlyIndexes[j] + n + 3]))
                                whileUsUs = string[openCurlyIndexes[j] + n + 3];
                            else if ((string[openCurlyIndexes[j] + n + 2] && string[openCurlyIndexes[j] + n + 3] == ';'))
                                whileUsUs = string[openCurlyIndexes[j] + n + 2];
                            else if ((string[openCurlyIndexes[j] + n + 2] == ' ' && string[openCurlyIndexes[j] + n + 3]))
                                whileUsUs = string[openCurlyIndexes[j] + n + 3];
                            else if ((string[openCurlyIndexes[j] + n + 2] && string[openCurlyIndexes[j] + n + 3] == ')'))
                                whileUsUs = string[openCurlyIndexes[j] + n + 2];
                        }
                        else if (string[openCurlyIndexes[j] + n] == '+' && string[openCurlyIndexes[j] + n + 1] == '+')
                            whileLineerUs++;
                        else if (string[openCurlyIndexes[j] + n] == '-' && string[openCurlyIndexes[j] + n + 1] == '-')
                            whileLineerUs++;
                        n++;
                    }
                }
            }
        }
        // while zaman ve yer karmaşıklığı
        if (whileCount >= 1 && forCount == 0)
        {
            if (whileLineerUs > 0 && whileLogUs == 0 && whileUsUs == 0)
            {
                printf("\n\n\t\tNotasyon : O(N^%d)\n\t\tYer Karmasikligi : %d*n^%d+%d", whileLineerUs, sizeof(int), arraySize, algoritmaSize);
            }
            else if (whileLineerUs == 0 && whileLogUs > 0 && whileUsUs == 0)
            {
                printf("\n\n\t\tNotasyon : O(logN)^%d\n\t\tYer Karmasikligi : %d*n^%d+%d", whileLogUs, sizeof(int), arraySize,algoritmaSize);
            }
            else if (whileLineerUs == 0 && whileLogUs == 0 && whileUsUs > 0)
            {
                printf("\n\n\t\tNotasyon : O(%c^n)\n\t\tYer Karmasikligi : %d*n^%d+%d", whileUsUs, sizeof(int), arraySize,algoritmaSize);
            }
            else if (whileLineerUs > 0 && whileLogUs > 0 && whileUsUs == 0)
            {
                printf("\n\n\t\tNotasyon : O(N^%d*logN^%d)\n\t\tYer Karmasikligi : %d*n^%d+%d", whileLineerUs, whileLogUs, sizeof(int), arraySize, algoritmaSize);
            }
            else if (whileLineerUs > 0 && whileLogUs == 0 && whileUsUs > 0)
            {
                printf("\n\n\t\tNotasyon : O(N^%d*%c^n)\n\t\tYer Karmasikligi : %d*n^%d+%d", whileLineerUs, whileUsUs, sizeof(int), arraySize, algoritmaSize);
            }
            else if (whileLineerUs == 0 && whileLogUs > 0 && whileUsUs > 0)
            {
                printf("\n\n\t\tNotasyon : O(logN^%d*%c^n)\n\t\tYer Karmasikligi : %d*n^%d+%d", whileLogUs, whileUsUs, sizeof(int), arraySize, algoritmaSize);
            }
        }
    }

    int dowhileLineerUs = 0;
    int dowhileLogUs = 0;
    int dowhileUsUs = 0;
    if (doCount != 0)
    {
        int m = 0;
        for (int i = 1; i <= doCount; i++)
        {
            for (int j = 1; j <= openCurlyCount; j++)
            {
                if (openCurlyIndexes[j] > doIndex[i])
                {
                    while (string[openCurlyIndexes[j] + m] != '}' && string[openCurlyIndexes[j] + m + 1] != 'w')
                    {

                        if (string[openCurlyIndexes[j] + m] == '+' && string[openCurlyIndexes[j] + m + 1] == '=')
                        {
                            dowhileLineerUs++;
                        }
                        else if (string[openCurlyIndexes[j] + m] == '-' && string[openCurlyIndexes[j] + m + 1] == '=')
                        {
                            dowhileLineerUs++;
                        }
                        else if (string[openCurlyIndexes[j] + m] == '/' && string[openCurlyIndexes[j] + m + 1] == '=')
                        {

                            dowhileLogUs++;
                        }
                        else if (string[openCurlyIndexes[j] + m] == '*' && string[openCurlyIndexes[j] + m + 1] == '=')
                        {
                            if (string[openCurlyIndexes[j] + m + 2] && string[openCurlyIndexes[j] + m + 3] == ';')
                            {
                                dowhileUsUs = string[openCurlyIndexes[j] + m + 2];
                            }
                            else if (string[openCurlyIndexes[j] + m + 2] == ' ' && string[openCurlyIndexes[j] + m + 3])
                            {
                                dowhileUsUs = string[openCurlyIndexes[j] + m + 3];
                            }
                            else if (string[openCurlyIndexes[j] + m + 2] && string[openCurlyIndexes[j] + m + 3] == ' ')
                            {
                                dowhileUsUs = string[openCurlyIndexes[j] + m + 2];
                            }
                        }
                        else if (string[openCurlyIndexes[j] + m] == '+' && string[openCurlyIndexes[j] + m + 1] == '+')
                        {
                            dowhileLineerUs++;
                        }
                        else if (string[openCurlyIndexes[j] + m] == '-' && string[openCurlyIndexes[j] + m + 1] == '-')
                        {
                            dowhileLineerUs++;
                        }
                        m++;
                    }
                }
            }
        }

        if (dowhileLineerUs > 0 && dowhileLogUs == 0 && dowhileUsUs == 0)
        {
            printf("\n\t\tNotasyon : O(N^%d)\n\t\t Yer Karmasikligi : %d*n^%d+%d", dowhileLineerUs, sizeof(int), arraySize, algoritmaSize);
        }
        else if (dowhileLineerUs == 0 && dowhileLogUs > 0 && dowhileUsUs == 0)
        {
            printf("\n\t\tNotasyon : O(logN^%d)\n\t\t Yer Karmasikligi : %d*n^%d+%d", dowhileLogUs, sizeof(int), arraySize, algoritmaSize);
        }
        else if (dowhileLineerUs == 0 && dowhileLogUs == 0 && dowhileUsUs > 0)
        {
            printf("\n\t\tNotasyon : O(%c^n)\n\t\t Yer Karmasikligi : %d*n^%d+%d", dowhileUsUs, sizeof(int), arraySize,algoritmaSize);
        }
        else if (dowhileLineerUs > 0 && dowhileLogUs > 0 && dowhileUsUs == 0)
        {
            printf("\n\t\tNotasyon : O(N^%d*logN^%d)\n\t\t Yer Karmasikligi : %d*n^%d+%d", dowhileLineerUs, dowhileLogUs, sizeof(int), arraySize, algoritmaSize);
        }
        else if (dowhileLineerUs > 0 && dowhileLogUs == 0 && dowhileUsUs > 0)
        {
            printf("\n\t\tNotasyon : O(N^%d*%c^n)\n\t\t Yer Karmasikligi : %d*n^%d+%d", dowhileLineerUs, dowhileUsUs, sizeof(int), arraySize,algoritmaSize);
        }
        else if (dowhileLineerUs == 0 && dowhileLogUs > 0 && dowhileUsUs > 0)
        {
            printf("\n\t\tNotasyon : O(logN^%d*%c^n)\n\t\t Yer Karmasikligi : %d*n^%d+%d", dowhileLogUs, dowhileUsUs, sizeof(int), arraySize, algoritmaSize);
        }
    }
    printf("\n");

    int notasyon_log_us = 0;
    int notasyon_lineer_katsayi = 0;
    int notasyon_us_us = 0;
    if (forCount >= 1)
    {
        for (int i = 0; i < k; i++)
        {
            if (controllerOperations[i] == '+' && controllerOperations[i + 1] == '=')
                notasyon_lineer_katsayi++;
            else if (controllerOperations[i] == '-' && controllerOperations[i + 1] == '=')
                notasyon_lineer_katsayi++;
            else if (controllerOperations[i] == '/' && controllerOperations[i + 1] == '=')
                notasyon_log_us++;
            else if (controllerOperations[i] == '*' && controllerOperations[i + 1] == '=')
            {
                if (controllerOperations[i + 2] && controllerOperations[i + 3] == ' ')
                    notasyon_us_us = controllerOperations[i + 2];
                else if (controllerOperations[i + 2] == ' ' && controllerOperations[i + 3])
                    notasyon_us_us = controllerOperations[i + 3];
                else if (controllerOperations[i + 2] && controllerOperations[i + 3] == ')')
                    notasyon_us_us = controllerOperations[i + 2];
                else if (controllerOperations[i + 2] && controllerOperations[i + 3] == ' ')
                    notasyon_us_us = controllerOperations[i + 2];
            }
            else if (controllerOperations[i] == '+' && controllerOperations[i + 1] == '+')
                notasyon_lineer_katsayi++;
            else if (controllerOperations[i] == '-' && controllerOperations[i + 1] == '-')
                notasyon_lineer_katsayi++;
        }

        if (forCount >= 1 && whileCount == 0)
        {
            if (notasyon_lineer_katsayi > 0 && notasyon_log_us == 0 && notasyon_us_us == 0)
            {
                printf("\n\n\t\tNotasyon : O(N^%d)\n\n\t\tYer Karmasikligi : %d*n^%d+%d ", notasyon_lineer_katsayi, sizeof(int), arraySize, algoritmaSize);
            }
            else if (notasyon_lineer_katsayi == 0 && notasyon_log_us > 0 && notasyon_us_us == 0)
            {
                printf("\n\n\t\tNotasyon : O(logN^%d)\n\n\t\tYer Karmasikligi : %d*n^%d+%d ", notasyon_log_us, sizeof(int), arraySize,algoritmaSize);
            }
            else if (notasyon_lineer_katsayi == 0 && notasyon_log_us == 0 && notasyon_us_us > 0)
            {
                printf("\n\n\t\tNotasyon : O(%d^n)\n\n\t\tYer Karmasikligi : %d*n^%d+%d ", notasyon_us_us, sizeof(int), arraySize, algoritmaSize);
            }
            else if (notasyon_lineer_katsayi > 0 && notasyon_log_us > 0 && notasyon_us_us == 0)
            {
                printf("\n\n\t\tNotasyon : O(N^%d*logN^%d)\n\n\t\tYer Karmasikligi : %d*n^%d+%d ", notasyon_lineer_katsayi, notasyon_log_us, sizeof(int), arraySize, algoritmaSize);
            }
            else if (notasyon_lineer_katsayi > 0 && notasyon_log_us == 0 && notasyon_us_us > 0) // bakılacak
            {
                printf("\n\n\t\tNotasyon : O(%d^n*%c^n)\n\n\t\tYer Karmasikligi : %d*n^%d+%d ", notasyon_lineer_katsayi, notasyon_log_us, sizeof(int), arraySize, algoritmaSize);
            }
            else if (notasyon_lineer_katsayi == 0 && notasyon_log_us > 0 && notasyon_us_us > 0) // bakılacak
            {
                printf("\n\n\t\tNotasyon : O(logN^%d*%c^n)\n\n\t\tYer Karmasikligi : %d*n^%d+%d ", notasyon_log_us, notasyon_us_us, sizeof(int), arraySize, algoritmaSize);
            }
        }
    }

    if (foricindewhile == true)
    {
        if (forCount >= 1 && whileCount >= 1)
        {
            if (notasyon_lineer_katsayi > 0 && notasyon_log_us == 0 && notasyon_us_us == 0 && foricinde_while_lineer > 0 && foricinde_while_log == 0 && foricinde_while_us == 0)
                printf("\n\n\t\tNotasyon : O(N^%d*N^%d)\n\n\t\tYer Karmasikligi : %d*n^%d+%d\n\n", notasyon_lineer_katsayi, foricinde_while_lineer, sizeof(int), arraySize, algoritmaSize);

            else if (notasyon_lineer_katsayi == 0 && notasyon_log_us > 0 && notasyon_us_us == 0 && foricinde_while_lineer == 0 && foricinde_while_log > 0 && foricinde_while_us == 0)
                printf("\n\n\t\tNotasyon : O(logN^%d*logN^%d)\n\n\t\tYer Karmasikligi : %d*n^%d+%d\n\n", notasyon_log_us, foricinde_while_log, sizeof(int), arraySize, algoritmaSize);

            else if (notasyon_lineer_katsayi == 0 && notasyon_log_us == 0 && notasyon_us_us > 0 && foricinde_while_lineer == 0 && foricinde_while_log == 0 && foricinde_while_us > 0)
                printf("\n\n\t\tNotasyon : O(%c^n*%c^n)\n\n\t\tYer Karmasikligi : %d*n^%d+%d\n\n", notasyon_us_us, foricinde_while_us, sizeof(int), arraySize, algoritmaSize);

            else if (notasyon_lineer_katsayi > 0 && notasyon_log_us == 0 && notasyon_us_us == 0 && foricinde_while_lineer == 0 && foricinde_while_log > 0 && foricinde_while_us == 0)
                printf("\n\n\t\tNotasyon : O(N^%d*logN^%d)\n\n\t\tYer Karmasikligi : %d*n^%d+%d\n\n", notasyon_lineer_katsayi, foricinde_while_log, sizeof(int), arraySize, algoritmaSize);

            else if (notasyon_lineer_katsayi == 0 && notasyon_log_us > 0 && notasyon_us_us == 0 && foricinde_while_lineer > 0 && foricinde_while_log == 0 && foricinde_while_us == 0)
                printf("\n\n\t\tNotasyon : O(%c^n*N^%d)\n\n\t\tYer Karmasikligi : %d*n^%d+%d\n\n", notasyon_log_us, foricinde_while_lineer, sizeof(int), arraySize, algoritmaSize);

            else if (notasyon_lineer_katsayi > 0 && notasyon_log_us == 0 && notasyon_us_us == 0 && foricinde_while_lineer == 0 && foricinde_while_log == 0 && foricinde_while_us > 0)
                printf("\n\n\t\tNotasyon : O(N^%d*%c^n)\n\n\t\tYer Karmasikligi : %d*n^%d+%d\n\n", notasyon_lineer_katsayi, foricinde_while_us, sizeof(int), arraySize, algoritmaSize);

            else if (notasyon_lineer_katsayi == 0 && notasyon_log_us == 0 && notasyon_us_us > 0 && foricinde_while_lineer > 0 && foricinde_while_log == 0 && foricinde_while_us == 0)
                printf("\n\n\t\tNotasyon : O(%c^n*N^%d)\n\n\t\tYer Karmasikligi : %d*n^%d+%d\n\n", notasyon_us_us, foricinde_while_lineer, sizeof(int), arraySize, algoritmaSize);

            else if (notasyon_lineer_katsayi == 0 && notasyon_log_us > 0 && notasyon_us_us == 0 && foricinde_while_lineer == 0 && foricinde_while_log == 0 && foricinde_while_us > 0)
                printf("\n\n\t\tNotasyon : O(logN^%d*%c^n)\n\n\t\tYer Karmasikligi : %d*n^%d+%d\n\n", notasyon_lineer_katsayi, foricinde_while_us, sizeof(int), arraySize, algoritmaSize);

            else if (notasyon_lineer_katsayi == 0 && notasyon_log_us == 0 && notasyon_us_us > 0 && foricinde_while_lineer == 0 && foricinde_while_log > 0 && foricinde_while_us == 0)
                printf("\n\n\t\tNotasyon : O(%c^n*logN^%d)\n\n\t\tYer Karmasikligi : %d*n^%d+%d\n\n", notasyon_us_us, foricinde_while_log, sizeof(int), arraySize, algoritmaSize);
        }
    }
    //checkRecursive(string, mainIndex);
    int checkFlag = checkRecursive(string, mainIndex, intIndexes, semiColonIndexes, esittirIndexes);
    if (checkFlag != 0)
    {
        if (checkFlag == 1)
        {
            printf("\n\n\t\tNotasyon : O(N)\n\n\t\t");

            printf("Yer karmasikligi: n+%d", algoritmaSize);
        }
        else if (checkFlag == 2)
        {
            printf("\n\n\t\tNotasyon : O(logN)\n\n\t\t");
            printf("Yer karmasikligi: n+%d", algoritmaSize);
        }
        else
        {
            printf("\n\n\t\tNotasyon : O(%c^n)\n\n\t\t", ustelRecursive);
            printf("Yer karmasikligi: n+%d", algoritmaSize);
        }
    }
    if (string)
    {
        free(string);
    }

    double kodSuresi = 0.0;

    //system("cp code.txt code.c && gcc code.c");
    printf("\n\n\n\t\tText dosyasindaki kodun ciktisi: \n\t\t");
    printf("\n");

    clock_t basla = clock();
    //system("./a.out");

    clock_t bitir = clock();
    kodSuresi += (double)(bitir - basla) / CLOCKS_PER_SEC;
    printf("\n");

    printf("\n\t\tCode.c dosyasinin calisma suresi: %f saniye\n\n\n\n\n", kodSuresi);

    return 0;
}
