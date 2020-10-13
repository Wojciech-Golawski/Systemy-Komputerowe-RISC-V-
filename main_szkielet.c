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
    else if(3==argc)
    {
	/*
	*
	*  
	*/

    }
    else if(((4<argc) && (12>argc)) && argc%2)
    {
	/*
	*
	*  
	*/
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
