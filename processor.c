
#ifndef STDINT_U
#define STDINT_U
	#include <stdint.h>
#endif //STDINT_U
#include "instruction.h"
#include "param.h"

int processor_step(uint32_t * pc,uint32_t * reg_tab,uint32_t word)
{
	*reg_tab=0; //rejestr 0 równy zero //dodatkowe zabezpieczenie zapewne nie potrzebne
	uint32_t opcode=MASK_OPCODE(word);
	uint32_t fun3=MASK_FUNC3(word);
	if(opcode==OPCODE_LUI)
	{instr_lui(pc,reg_tab,word);
		return 0;}
	if(opcode==OPCODE_AUIPC)
	{instr_auipc(pc,reg_tab,word);return 0;}
	if(opcode==OPCODE_JAL)
	{instr_jal(pc,reg_tab,word);return 0;}
	if(opcode==OPCODE_JALR && fun3==OPCODE_JALR_FUNC3)
	{instr_jalr(pc,reg_tab,word);return 0;}
	if(opcode==OPCODE_BGEU && fun3==OPCODE_BGEU_FUNC3 )
	{instr_bgeu(pc,reg_tab,word);return 0;}
	if(opcode==OPCODE_SW && fun3==OPCODE_SW_FUNC3 )
	{instr_sw(pc,reg_tab,word);return 0;}
	if(opcode==OPCODE_SB && fun3==OPCODE_SB_FUNC3 )
	{instr_sb(pc,reg_tab,word);return 0;}
	if(opcode==OPCODE_ADDI && fun3==OPCODE_ADDI_FUNC3 )
	{instr_addi(pc,reg_tab,word);return 0;}
	if(opcode==OPCODE_SRAI && fun3==OPCODE_SRAI_FUNC3)
	{instr_srai(pc,reg_tab,word);return 0;}
	if(opcode==OPCODE_LW && fun3==OPCODE_LW_FUNC3 )
	{instr_lw(pc,reg_tab,word);return 0;}
	if(opcode==OPCODE_ANDI && fun3==OPCODE_ANDI_FUNC3 )
	{instr_andi(pc,reg_tab,word);return 0;}
	if(word==0){return 1;}
	LOG("n/a")
	return 2;

	//print błąd lub koniec programu

	//pobiera adres licznika programui go modyfikuje
	//pobiera tablicę rejestrów i ją modyfikuje
	//pobiera słowo maszynowe i je przetwarza
	
	//switch case opcode
}
/*
	uint32_t * code, 		int code_len,
	uint32_t * data_in,		int data_in_len,
	uint32_t ** data_out, 	int * data_out_len
	uint32_t * reg_in,		uint32_t ** reg_out*/

int processor_const_work(uint32_t * pc,uint32_t * reg_tab)
{
	//printf("pcw");
	uint32_t word;
	for(int i=0;i<MAX_IT_COUNT;i++)
	{
		uint32_t addr=(*pc);
		if (addr>MEM_SIZE)
		{
			printf("Naruszenie ochrony pamięci emulatora\n zadeklaruj więcej pamięci w pliku \"param.h\"");
			return 4;
		}
		word=0;
		if(IS_BIG_ENDIAN)
		{
			word|=((uint32_t)(all_ptr[addr]))<<24;
			word|=((uint32_t)(all_ptr[addr+1]))<<16;
			word|=((uint32_t)(all_ptr[addr+2]))<<8;
			word|=((uint32_t)(all_ptr[addr+3]));
		}
		else
		{
			word|=((uint32_t)(all_ptr[addr+3]))<<24;
			word|=((uint32_t)(all_ptr[addr+2]))<<16;
			word|=((uint32_t)(all_ptr[addr+1]))<<8;
			word|=((uint32_t)(all_ptr[addr]));
		}
		
		printf("%d, %d\n",(*pc),i);
		switch(processor_step(pc,reg_tab,word))
		{
			case 0:break;
				
			case 1:printf("EOF\n"); return 1;
				
			case 2:printf("nierozpoznana instrukcja\n"); return 2;
				
			default:printf("nieznany błąd krytyczny\n"); return 3;
				
		}
	}
	printf("zbyt wiele wywołań:\nalbo program wpadł w nieskończoną pętlę albo w pliku \"param.h\" jest ustawiony za niski limit wywołań\n");
	//data_out,data_out_len,reg_out wskaźniki na pozycję do której mają być zapisane informacje o danych
	
	//for 10^6 processor_step
	return 4;
}


