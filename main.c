
#include "input_output.h"
#include "param.h"
#include "instruction.h"


int processor_step(uint32_t * pc,uint32_t * reg_tab,uint32_t word);
int processor_const_work(uint32_t * pc,uint32_t * reg_tab);


uint8_t * all_ptr=NULL;

void code_codeb(char ** parametr, uint8_t ** kod_maszynowy, int * dlugosc_kodu_maszynowego);
void din_dinb(char ** parametr, int liczba_parametrow, uint8_t ** dane_wejsciowe, int * dlugosc_danych_wejsciowych);
void regin_reginb(char ** parametr, int liczba_parametrow, uint8_t ** rejestr, int * dlugosc_rejestru, uint32_t * pc);
void regout_regoutb(char ** parametr, int liczba_parametrow, uint8_t ** rejestr, int dlugosc_rejestru, uint32_t pc);
void dout_doutb(char ** parametr, int liczba_parametrow, uint8_t ** dane_wyjsciowe, int dlugosc_danych_wyjsciowych);

uint32_t uzupelnij_gl_pc(uint8_t najstarszy, uint8_t starszy, uint8_t mlodszy, uint8_t najmlodszy);
void wklej_gl_pc(uint32_t pc, uint8_t ** rejestr);

int main(int argc, char * argv[])
{
    uint8_t * machine_code;
    int machine_code_len=0;

    uint8_t * m_data_in;
    int m_data_in_len=0;

    uint8_t * gl_reg_tab;
    int gl_reg_tab_len=0;
    uint32_t gl_pc=0;

    uint8_t * m_data_out;
    int m_data_out_len=0;


    if(argc<3)
    {
        printf("Nie wystarczajaca liczba danych do poprawnej symulacji\n");
        exit(1);
    }
    /*else if(3==argc)
    {
        code_codeb(argv, &machine_code, &machine_code_len);
    }*/
    else if(((2<argc) && (12>argc)) && argc%2)
    {
        code_codeb(argv, &machine_code, &machine_code_len);                     //obsluga parametrow -code   oraz -codeb
        din_dinb(argv, argc, &m_data_in, &m_data_in_len);                       //obsluga parametrow -din    oraz -dinb
        regin_reginb(argv, argc, &gl_reg_tab, &gl_reg_tab_len, &gl_pc);         //obsluga parametrow -regin  oraz -reginb
        /*oznaczone miejsce na twoja inwencje tworcza
        */
        all_ptr=(uint8_t *)(calloc(sizeof(uint8_t),MEM_SIZE));
        //printf("%p\n",all_ptr);//za chwilę usunąć
        if(machine_code_len>SIZE_CODE)
        {
			machine_code_len=SIZE_CODE;
		}
		memcpy((all_ptr+ADDR_CODE),machine_code,machine_code_len);
		//printf("l60 po memcpy code\n");//za chwilę usunąć
		if(m_data_in_len>SIZE_DATA_IN)
        {
			m_data_in_len=SIZE_DATA_IN;
		}
		
		memcpy((all_ptr+ADDR_DATA_IN),m_data_in,m_data_in_len);
		//printf("l60 po memcpy data\n");//za chwilę usunąć
        uint32_t tab[32]={0};
        memcpy(tab,gl_reg_tab,128);
        //processor_const_work((uint32_t *)(&gl_pc),(uint32_t *)(&gl_reg_tab));
        processor_const_work((uint32_t *)(&gl_pc),(uint32_t *)(tab));
        
        //printf("%d\n",argc);
       // printf("l60 po constwork\n");//za chwilę usunąć
        
        /*
        */
        uint8_t * tab2=calloc(sizeof(uint8_t),128);
        memcpy(tab2,tab,128);
        printf("a\n");
        //regout_regoutb(argv, argc, &gl_reg_tab, gl_reg_tab_len, gl_pc);
        regout_regoutb(argv, argc, (uint8_t **)(&tab2), 128, gl_pc);
         printf("l60 po regoutb\n");//za chwilę usunąć
        dout_doutb(argv, argc, &m_data_out, m_data_out_len);
        printf("l60 po dout\n");//za chwilę usunąć
        //free(all_ptr);
    }
    else if(12<argc)
    {
        printf("Nie przyjmuje wiecej niz 11 parametrow, sprawdz czy nie zdublowales czegos\n");
    }
    else
    {
        printf("Po kazdym parametrze musisz podac nazwe pliku w ktorym sa dane\n");
    }

    return 0;
}

void code_codeb(char ** parametr, uint8_t ** kod_maszynowy, int * dlugosc_kodu_maszynowego)
{
     if(!strncmp("-codeb", parametr[1], strlen("-codeb")))
        {
            printf("Podano \"-codeb\"\n");
            *kod_maszynowy=inputb(parametr[2], dlugosc_kodu_maszynowego);
            /*int licznik=0;
            for(licznik=0; licznik< *dlugosc_kodu_maszynowego; licznik++)
            {
                printf("%d\n", (*kod_maszynowy)[licznik]);
            }*/
        }
        else if(!strncmp("-code", parametr[1], strlen("-code")))
        {
            printf("Podano \"-code\"\n");
            *kod_maszynowy=input(parametr[2], dlugosc_kodu_maszynowego);
            /*int licznik=0;
            for(licznik=0; licznik< *dlugosc_kodu_maszynowego; licznik++)
            {
                printf("%d\n", (*kod_maszynowy)[licznik]);
            }*/
        }
        else
        {
            printf("Brak pliku z kodem maszynowym procesora, sprawdz parametry \"-code\" lub \"-codeb\"\n");
            exit(1);
        }
}

void din_dinb(char ** parametr, int liczba_parametrow, uint8_t ** dane_wejsciowe, int * dlugosc_danych_wejsciowych)
{
    int licznik_1=0, czy_wyswietlic_blad=1;
    for(licznik_1=3; licznik_1<liczba_parametrow; licznik_1=licznik_1+2)
    {
        if(!strncmp("-dinb", parametr[licznik_1], strlen("-dinb")))
        {
            printf("Podano \"-dinb\"\n");
            *dane_wejsciowe=inputb(parametr[licznik_1+1], dlugosc_danych_wejsciowych);
            /*int licznik=0;
            for(licznik=0; licznik< *dlugosc_danych_wejsciowych; licznik++)
            {
                printf("%d\n", (*dane_wejsciowe)[licznik]);
            }*/
            czy_wyswietlic_blad=0;
        }
        else if(!strncmp("-din", parametr[licznik_1], strlen("-din")))
        {
            printf("Podano \"-din\"\n");
            *dane_wejsciowe=input(parametr[licznik_1+1], dlugosc_danych_wejsciowych);
            /*int licznik=0;
            for(licznik=0; licznik< *dlugosc_danych_wejsciowych; licznik++)
            {
                printf("%d\n", (*dane_wejsciowe)[licznik]);
            }*/
            czy_wyswietlic_blad=0;
        }
    }
    if((licznik_1>=liczba_parametrow) && czy_wyswietlic_blad)
    {
        printf("Brak pliku z danymi dla procesora, sprawdz parametry \"-din\" lub \"-dinb\"\n");
    }
}

void regin_reginb(char ** parametr, int liczba_parametrow, uint8_t ** rejestr, int * dlugosc_rejestru, uint32_t * pc)
{
    int licznik_1=0, czy_wykonywano=0;
    for(licznik_1=3; licznik_1<liczba_parametrow; licznik_1=licznik_1+2)
    {
        if(!strncmp("-reginb", parametr[licznik_1], strlen("-reginb")))
            {
                 printf("Podano \"-reginb\"\n");
                *rejestr=inputb(parametr[licznik_1+1], dlugosc_rejestru);
                int licznik=0;
                /*for(licznik=0; licznik< *dlugosc_rejestru; licznik++)
                {
                    printf("%d\n", (*rejestr)[licznik]);
                }*/
                if(*dlugosc_rejestru<128)
                {
                    uint8_t * bufor_rejestru=0;
                    bufor_rejestru=malloc(sizeof(uint8_t)*128);        // jesli rejstr jest krotszy niz 128 bajtow to poprawiamy wielkosc tablicy i wypelniamy 0 do 128 bajtow
                    for(licznik=0; licznik<128; licznik++)
                    {
                        bufor_rejestru[licznik]=0;
                    }
                    for(licznik=0; licznik< *dlugosc_rejestru; licznik++)               //przepisanie podanych danych do tablicy o poprawionej wielkosci
                    {
                        bufor_rejestru[licznik]=(*rejestr)[licznik];
                    }
                    *pc=uzupelnij_gl_pc(bufor_rejestru[0], bufor_rejestru[1], bufor_rejestru[2], bufor_rejestru[3]);        //wynciecie pierwszych 4 bajtow do zmiennej gl_pc
                    bufor_rejestru[0]=0;
                    bufor_rejestru[1]=0;
                    bufor_rejestru[2]=0;
                    bufor_rejestru[3]=0;
                    free(*rejestr);
                    *rejestr=bufor_rejestru;
                    *dlugosc_rejestru=128;
                    printf("Dlugosc tablicy < 128 bajtow, poprawiono dlugosc i wypelniono zerami\n");
                }
                else
                {
                    *pc=uzupelnij_gl_pc((*rejestr)[0],  (*rejestr)[0],  (*rejestr)[0],  (*rejestr)[0]);        //wynciecie pierwszych 4 bajtow do zmiennej gl_pc
                    (*rejestr)[0]=0;
                    (*rejestr)[1]=0;
                    (*rejestr)[2]=0;
                    (*rejestr)[3]=0;
                }
                czy_wykonywano=1;
            }
            else if(!strncmp("-regin", parametr[licznik_1], strlen("-regin")))
            {
                printf("Podano \"-regin\"\n");
                *rejestr=input(parametr[licznik_1+1], dlugosc_rejestru);
                int licznik=0;
                /*for(licznik=0; licznik< *dlugosc_rejestru; licznik++)
                {
                    printf("%d\n", (*rejestr)[licznik]);
                }*/
                if(*dlugosc_rejestru<128)
                {
                    uint8_t * bufor_rejestru=0;
                    bufor_rejestru=malloc(sizeof(uint8_t)*(size_t)128);        // jesli rejstr jest krotszy niz 128 bajtow to poprawiamy wielkosc tablicy i wypelniamy 0 do 128 bajtow
                    for(licznik=0; licznik<128; licznik++)
                    {
                        bufor_rejestru[licznik]=0;
                    }
                    for(licznik=0; licznik< *dlugosc_rejestru; licznik++)               //przepisanie podanych danych do tablicy o poprawionej wielkosci
                    {
                        bufor_rejestru[licznik]=(*rejestr)[licznik];
                    }
                    *pc=uzupelnij_gl_pc(bufor_rejestru[0], bufor_rejestru[1], bufor_rejestru[2], bufor_rejestru[3]);        //wynciecie pierwszych 4 bajtow do zmiennej gl_pc
                    bufor_rejestru[0]=0;
                    bufor_rejestru[1]=0;
                    bufor_rejestru[2]=0;
                    bufor_rejestru[3]=0;
                    free(*rejestr);
                    *rejestr=bufor_rejestru;
                    *dlugosc_rejestru=128;
                    printf("Dlugosc tablicy < 128 bajtow, poprawiono dlugosc i wypelniono zerami\n");
                }
                else
                {
                    *pc=uzupelnij_gl_pc((*rejestr)[0],  (*rejestr)[0],  (*rejestr)[0],  (*rejestr)[0]);        //wynciecie pierwszych 4 bajtow do zmiennej gl_pc
                    (*rejestr)[0]=0;
                    (*rejestr)[1]=0;
                    (*rejestr)[2]=0;
                    (*rejestr)[3]=0;
                }
                czy_wykonywano=1;
            }
            else
            {
                if(!czy_wykonywano)
                {
                int licznik=0;
                uint8_t * bufor_rejestru=0;
                bufor_rejestru=malloc(sizeof(uint8_t)*128);        // jesli rejstr jest krotszy niz 128 bajtow to poprawiamy wielkosc tablicy i wypelniamy 0 do 128 bajtow
                for(licznik=0; licznik<128; licznik++)
                {
                    bufor_rejestru[licznik]=0;
                }                                                  //Tutaj bez warringu ale trzeba zaalokowac 128 bajtowa tablice wypelniona 0 oraz gl_pc=0
                *pc=0;
                *rejestr=bufor_rejestru;
                *dlugosc_rejestru=128;
                }
            }
    }
}

uint32_t uzupelnij_gl_pc(uint8_t najstarszy, uint8_t starszy, uint8_t mlodszy, uint8_t najmlodszy)
{
    uint32_t robocza_zmienna=0;

    robocza_zmienna=((najstarszy<<24) | (starszy<<16) | (mlodszy<<8) | (najmlodszy));

    return robocza_zmienna;
}

void regout_regoutb(char ** parametr, int liczba_parametrow, uint8_t ** rejestr, int dlugosc_rejestru, uint32_t pc)
{
	// printf("regoutb 1\n");//za chwilę usunąć
    int licznik_1=0;
    for(licznik_1=3; licznik_1<liczba_parametrow; licznik_1=licznik_1+2)
    {
		/*
		printf("regoutb 2\n");//za chwilę usunąć
		strncmp("-regout", parametr[licznik_1], strlen("-regout"));
		printf("regoutb 2a\n");//za chwilę usunąć
		printf("%d\n",licznik_1);
		printf("%d\n",liczba_parametrow);
		
		printf("0, %s\n",parametr[0]);
		printf("1, %s\n",parametr[1]);
		printf("2, %s\n",parametr[2]);
		printf("3, %s\n",parametr[3]);
		//*/
        if(!strncmp("-regoutb", parametr[licznik_1], strlen("-regoutb")))
            {
                printf("Podano \"-regoutb\"\n");
                //printf("regoutb 3\n");//za chwilę usunąć
                wklej_gl_pc(pc, rejestr);
                //printf("regoutb 4\n");//za chwilę usunąć
                /*int licznik=0;
                for(licznik=0; licznik< dlugosc_rejestru; licznik++)
                {
                    printf("%d ", (*rejestr)[licznik]);
                }*/
                outputb(parametr[licznik_1+1], *rejestr, dlugosc_rejestru);
                //printf("regoutb 5\n");//za chwilę usunąć
            }
            else if(!strncmp("-regout", parametr[licznik_1], strlen("-regout")))
            {
				//printf("regoutb 6\n");//za chwilę usunąć
                printf("Podano \"-regout\"\n");
                wklej_gl_pc(pc, rejestr);
                /*int licznik=0;
                for(licznik=0; licznik< dlugosc_rejestru; licznik++)
                {
                    printf("%d ", (*rejestr)[licznik]);
                }*/
                //printf("regoutb 7\n");//za chwilę usunąć
                output(parametr[licznik_1+1], *rejestr, dlugosc_rejestru);
            }
            //printf("regoutb 8\n");//za chwilę usunąć
    }
}

void wklej_gl_pc(uint32_t pc, uint8_t ** rejestr)
{
    (*rejestr)[0]=(uint8_t)pc>>24;
    (*rejestr)[1]=(uint8_t)(pc & 0b00000000111111110000000000000000)>>16;
    (*rejestr)[2]=(uint8_t)(pc & 0b00000000000000001111111100000000)>>8;
    (*rejestr)[3]=(uint8_t)(pc & 0b00000000000000000000000011111111);
}

void dout_doutb(char ** parametr, int liczba_parametrow, uint8_t ** dane_wyjsciowe, int dlugosc_danych_wyjsciowych)
{
    int licznik_1=0;
    for(licznik_1=3; licznik_1<liczba_parametrow; licznik_1=licznik_1+2)
    {
        if(!strncmp("-doutb", parametr[licznik_1], strlen("--doutb")))
            {
                printf("Podano \"-doutb\"\n");
                /*int licznik=0;
                for(licznik=0; licznik< dlugosc_danych_wyjsciowych; licznik++)
                {
                    printf("%d ", (*dane_wyjsciowe)[licznik]);
                }*/
                outputb(parametr[licznik_1+1], *dane_wyjsciowe, dlugosc_danych_wyjsciowych);
            }
            else if(!strncmp("-dout", parametr[licznik_1], strlen("--dout")))
            {
                printf("Podano \"-dout\"\n");
                /*int licznik=0;
                for(licznik=0; licznik< dlugosc_danych_wyjsciowych; licznik++)
                {
                    printf("%d ", (*dane_wyjsciowe)[licznik]);
                }*/
                output(parametr[licznik_1+1], *dane_wyjsciowe, dlugosc_danych_wyjsciowych);
            }
    }
}
