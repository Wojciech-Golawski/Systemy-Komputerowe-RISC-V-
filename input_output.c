#include "input_output.h"

void output(char * file_name, uint8_t * data, int len)
{
    FILE * plik = fopen(file_name, "w");
    if(plik==NULL)                                                                   //obsluga sytuacji kiedy z jakiegos powodu nie udalo sie otworzyc pliku
    {
        char blad[] = "Sprawdz nazwe. Nie udalo sie otworzyc pliku: \"";
        char * komunikat;
        komunikat=malloc(sizeof(char)*(strlen(blad)+strlen(file_name)+2));
        strncpy(komunikat, blad, strlen(blad));
        strncpy(komunikat+strlen(blad), file_name, strlen(file_name));
        strncpy(komunikat+strlen(blad)+strlen(file_name), "\"\n", 2);
        printf("%s", komunikat);
        free(komunikat);
        exit(1);
    }
    else
    {
        int licznik=0;
        for(licznik=0; licznik<len; licznik++)
        {
            fprintf(plik, "%x ", data[licznik]);
        }
    }
}

void outputb(char * file_name, uint8_t * data, int len)
{
    FILE * plik = fopen(file_name, "w+b");
    if(plik==NULL)                                                                   //obsluga sytuacji kiedy z jakiegos powodu nie udalo sie otworzyc pliku
    {
        char blad[] = "Sprawdz nazwe. Nie udalo sie otworzyc pliku: \"";
        char * komunikat;
        komunikat=malloc(sizeof(char)*(strlen(blad)+strlen(file_name)+2));
        strncpy(komunikat, blad, strlen(blad));
        strncpy(komunikat+strlen(blad), file_name, strlen(file_name));
        strncpy(komunikat+strlen(blad)+strlen(file_name), "\"\n", 2);
        printf("%s", komunikat);
        free(komunikat);
        exit(1);
    }
    else
    {
        int licznik=0;
        for(licznik=0; licznik<len; licznik++)
        {
            fprintf(plik, "%c", data[licznik]);
        }
    }

}


uint8_t * inputb(char *file_name, int * len_ptr)
{
    int znak;
    FILE * plik = fopen(file_name, "r+b");
    if(plik==NULL)                                                                   //obsluga sytuacji kiedy z jakiegos powodu nie udalo sie otworzyc pliku
    {
        char blad[] = "Sprawdz nazwe. Nie udalo sie otworzyc pliku: \"";
        char * komunikat;
        komunikat=malloc(sizeof(char)*(strlen(blad)+strlen(file_name)+2));
        strncpy(komunikat, blad, strlen(blad));
        strncpy(komunikat+strlen(blad), file_name, strlen(file_name));
        strncpy(komunikat+strlen(blad)+strlen(file_name), "\"\n", 2);
        printf("%s", komunikat);
        free(komunikat);
        exit(1);
    }
    else                                                                            //sytuacja gdy udalo sie otworzyc plik ale jest on pusty
    {
        fpos_t poczatek_pliku;
        fgetpos(plik, &poczatek_pliku);
        if((znak=getc(plik))==EOF)
        {
            char blad[] = "Plik o nazwie: \"";
            char blad_1[]= " jest pusty\n";
            char * komunikat;
            komunikat=malloc(sizeof(char)*(strlen(blad)+strlen(file_name)+strlen(blad_1)+2));
            strncpy(komunikat, blad, strlen(blad));
            strncpy(komunikat+strlen(blad), file_name, strlen(file_name));
            strncpy(komunikat+strlen(blad)+strlen(file_name), "\"", 1);
            strncpy(komunikat+strlen(blad)+strlen(file_name)+1, blad_1, strlen(blad_1));
            printf("%s", komunikat);
            free(komunikat);
            exit(1);
        }
        else
        {
            fpos_t pos=poczatek_pliku;
            int licznik_znakow=0;
            while(znak!=EOF)
            {
                fsetpos(plik, &pos);
                putc(znak, plik);
                fgetpos(plik, &pos);
                licznik_znakow++;
                //printf("%d ", znak);
                //printf("%d\n", licznik_znakow);
                znak=getc(plik);
            }

            uint8_t *wyjscie;
            wyjscie=malloc(sizeof(char)*(--licznik_znakow));
            fsetpos(plik, &poczatek_pliku);
            int licznik;
            for(licznik=0; (licznik<licznik_znakow) && ((znak=fgetc(plik))!=EOF);)
            {
                    wyjscie[licznik]=znak;
                    licznik++;
            }
            *len_ptr=licznik_znakow;

            return wyjscie;
        }

    }
    fclose(plik);
    return NULL;
}


uint8_t * input(char * file_name, int * len_ptr)
{
    char znak;
    FILE * plik = fopen(file_name, "r+");
    if(plik==NULL)                                                              //obsluga sytuacji kiedy z jakiegos powodu nie udalo sie otworzyc pliku
    {
        char blad[] = "Sprawdz nazwe. Nie udalo sie otworzyc pliku: \"";
        char * komunikat;
        komunikat=malloc(sizeof(char)*(strlen(blad)+strlen(file_name)+2));
        strncpy(komunikat, blad, strlen(blad));
        strncpy(komunikat+strlen(blad), file_name, strlen(file_name));
        strncpy(komunikat+strlen(blad)+strlen(file_name), "\"\n", 2);
        printf("%s", komunikat);
        free(komunikat);
        exit(1);
    }
    else                                                                         //sytuacja gdy udalo sie otworzyc plik ale jest on pusty
    {
        fpos_t poczatek_pliku;
        fgetpos(plik, &poczatek_pliku);
        if((znak=getc(plik))==EOF)
        {
            char blad[] = "Plik o nazwie: \"";
            char blad_1[]= " jest pusty\n";
            char * komunikat;
            komunikat=malloc(sizeof(char)*(strlen(blad)+strlen(file_name)+strlen(blad_1)+2));
            strncpy(komunikat, blad, strlen(blad));
            strncpy(komunikat+strlen(blad), file_name, strlen(file_name));
            strncpy(komunikat+strlen(blad)+strlen(file_name), "\"", 1);
            strncpy(komunikat+strlen(blad)+strlen(file_name)+1, blad_1, strlen(blad_1));
            printf("%s", komunikat);
            free(komunikat);
            exit(1);
        }
        else
        {
            fpos_t pos=poczatek_pliku;
            int wszystkie_znaki=0;
            int licznik_znakow=0;
            while(znak!=EOF)
            {
                fsetpos(plik, &pos);
                putc(znak, plik);
                fgetpos(plik, &pos);
                if(isdigit(znak))
                {
                    licznik_znakow++;
                }
                else
                {
                    znak=toupper(znak);
                    switch(znak)
                    {
                        case 'A':
                        case 'B':
                        case 'C':
                        case 'D':
                        case 'E':
                        case 'F': licznik_znakow++;
                    }
                }
                wszystkie_znaki++;
                znak=getc(plik);
            }
            char *bufor;
            bufor=malloc(sizeof(char)*licznik_znakow);
            fsetpos(plik, &poczatek_pliku);
            int licznik;
            for(licznik=0; (licznik<wszystkie_znaki) && ((znak=fgetc(plik))!=EOF);)
            {
                if(isdigit(znak))
                {
                    bufor[licznik]=znak;
                    licznik++;
                }
                else
                {
                    znak=toupper(znak);
                    switch(znak)
                    {
                        case 'A':
                        case 'B':
                        case 'C':
                        case 'D':
                        case 'E':
                        case 'F': bufor[licznik]=znak;
                                licznik++;

                    }
                }

            }
            uint8_t * wyjscie;
            wyjscie = malloc(sizeof(char)*(licznik_znakow/2));

            int licznik_wyjscia=0;
            licznik=0;
            while(licznik<licznik_znakow)
            {
                wyjscie[licznik_wyjscia++]=zamiana_2x_char_na_hex(bufor[licznik], bufor[licznik+1]);
                licznik=licznik+2;
            }
            free(bufor);
            *len_ptr=licznik/2;
            return wyjscie;
        }
    }

    fclose(plik);

    return NULL;
}


uint8_t zamiana_2x_char_na_hex(uint8_t starszy, uint8_t mlodszy)
{
    uint8_t wynik=0;

    if((starszy>>4)==0x03)
    {
        wynik=(starszy<<4);
    }
    else
    {
        if((starszy&0b00001111)>0x01)
        {
            wynik=(starszy|0b00001000)+0x01;
            wynik=(wynik<<4);
        }
        else
        {
            wynik=0x0A;
            wynik=(wynik<<4);
        }
    }

    if((mlodszy>>4)==0x03)
    {
        wynik=(wynik & 0b11110000) | (mlodszy & 0b00001111);
    }
    else
    {
        if((mlodszy&0b00001111)>0x01)
        {
            wynik=(wynik & 0b11110000) | (((mlodszy & 0b00001111) | 0b00001000)+0x01);
        }
        else
        {
            wynik=(wynik & 0b11110000) | (0x0A & 0b00001111);
        }
    }

    return wynik;
}
