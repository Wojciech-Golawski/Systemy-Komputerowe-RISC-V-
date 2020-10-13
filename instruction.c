#include "instruction.h"
#include "param.h"
	void instr_lui(uint32_t * pc,uint32_t * reg_tab,uint32_t  word)
	{//ładuje bity [31:12] do rd
		LOG("lui");
		(*pc)+=PC_INC;
		//LOG("lui2");
		if(MASK_RD(word)!=0)//rejestru #0 nie można zmieniać to zawsze zero
		{
			//LOG("lui3");
			//printf("\e[32m%d\e[39m\n",MASK_RD(word));
			*(reg_tab+MASK_RD(word))=(word&0xfffff000);
			//LOG("lui4");
			
		}
	}

	void instr_auipc(uint32_t * pc,uint32_t * reg_tab,uint32_t  word)
	{
		LOG("auipc");
		
		(*pc)+=PC_INC;
		if(MASK_RD(word)!=0)//rejestru #0 nie można zmieniać to zawsze zero
		{
			*(reg_tab+MASK_RD(word))=(*pc)+(word&0xfffff000);
		}
	}

	void instr_jal(uint32_t * pc,uint32_t * reg_tab,uint32_t  word)
	{
		LOG("jal");
		
		//zapisuje do rd (pc+PC_INC)
		//dodaje wartość ofsetu [20:1] do pc
		if(MASK_RD(word)!=0)//rejestru #0 nie można zmieniać to zawsze zero
		{
			*(reg_tab+MASK_RD(word))=(*pc)+PC_INC;
		}
		//(*pc)=((word&0x80000000)>>11)|((word&0x7fe00000)>>20)|((word&0x00100000)>>9)|((word&0x000ff000)>>11);
		int32_t offs=0;
		if(word&0x80000000)
		{
			offs=0xfff00000;
		}
		offs|=((word&0x7fe00000)>>20)|((word&0x00100000)>>9)|((word&0x000ff000)>>11);
		(*pc)+=offs;
	}

	void instr_jalr(uint32_t * pc,uint32_t * reg_tab,uint32_t  word)
	{//zapisuje adres pc+PC_INC do rd
		//do pc zapisuje zawartość rs1 z dodanym signed int_12 ignorując ostatni bit
		LOG("jalr");
		
		if(MASK_RD(word)!=0)//rejestru #0 nie można zmieniać to zawsze zero
		{
			*(reg_tab+MASK_RD(word))=(*pc)+PC_INC;
		}
		int32_t offs=0;
		if(word&0x80000000)
		{
			offs=0xfffff800;
		}
		offs|=(word&0x7ff00000)>>20;
		(*pc)=(((*(reg_tab+MASK_RS1(word)))+offs)&0xfffffffe);//ignorowanie ostatniego bitu
		
	}

	void instr_bgeu(uint32_t * pc,uint32_t * reg_tab,uint32_t  word)//immf ->imm [12|10:5]
	{
		LOG("bgeu");
		
		(*pc)+=PC_INC;
		uint32_t offs=((word&0x80000000)>>19)|((word&0x7e000000)>>20)|((word&0x00000f00)>>7)|((word&0x00000080)<<4);
		if((*(reg_tab+MASK_RS1(word)))>(*(reg_tab+MASK_RS2(word))))
		{
			(*pc)+=offs;
		}
		else
		{
			(*pc)+=PC_INC;
		}
	}
	void instr_sw(uint32_t * pc,uint32_t * reg_tab,uint32_t  word)
	{//załaduj całe słowo do pamięci
		LOG("sw");
		
		int32_t offs=0;
		if(word&0x80000000)
		{
			offs=0xfffff800;
		}
		offs|=(word&0x7e000000)>>20;
		offs|=MASK_RD(word);//to jest na tych samych bitach co rd
		uint32_t datpoz =(*(reg_tab+MASK_RS1(word))+offs)%MEM_SIZE;
		//trochę nie eleganckie ale proste
		if(IS_BIG_ENDIAN)
		{
			all_ptr[datpoz+0]=(uint8_t)((*(reg_tab+MASK_RS2(word))&0xff000000)>>24);
			all_ptr[datpoz+1]=(uint8_t)((*(reg_tab+MASK_RS2(word))&0x00ff0000)>>16);
			all_ptr[datpoz+2]=(uint8_t)((*(reg_tab+MASK_RS2(word))&0x0000ff00)>>8);
			all_ptr[datpoz+3]=(uint8_t)((*(reg_tab+MASK_RS2(word))&0x000000ff));
		}
		else
		{
			all_ptr[datpoz+3]=(uint8_t)((*(reg_tab+MASK_RS2(word))&0xff000000)>>24);
			all_ptr[datpoz+2]=(uint8_t)((*(reg_tab+MASK_RS2(word))&0x00ff0000)>>16);
			all_ptr[datpoz+1]=(uint8_t)((*(reg_tab+MASK_RS2(word))&0x0000ff00)>>8);
			all_ptr[datpoz+0]=(uint8_t)((*(reg_tab+MASK_RS2(word))&0x000000ff));
		}
		(*pc)+=PC_INC;
	}


	void instr_sb(uint32_t * pc,uint32_t * reg_tab,uint32_t  word)
	{//załaduj bajt do pamięci
		LOG("sb");
		
		int32_t offs=0;
		if(word&0x80000000)
		{
			offs=0xfffff800;
		}
		offs|=(word&0x7e000000)>>20;
		offs|=MASK_RD(word);//to jest na tych samych bitach co rd
		uint32_t datpoz =(*(reg_tab+MASK_RS1(word))+offs)%MEM_SIZE;
		//trochę nie eleganckie ale proste
		all_ptr[datpoz]=(uint8_t)(*(reg_tab+MASK_RS2(word))&0x000000ff);
		(*pc)+=PC_INC;
	}

	void instr_addi(uint32_t * pc,uint32_t * reg_tab,uint32_t  word)
	{// dodaje imm[11:0] (word[31:20]) do rs1 i zapisuje do rd
		LOG("addi");
		
		(*pc)+=PC_INC;
		uint64_t war=(uint64_t)(*(reg_tab+MASK_RS1(word)));
		war+=((word&0xfff00000)>>20);
		*(reg_tab+MASK_RD(word))=(uint32_t)(war&0x00000000ffffffff);;
	}

	void instr_srai(uint32_t * pc,uint32_t * reg_tab,uint32_t  word)
	{
		LOG("srai");
		
		(*pc)+=PC_INC;
		uint32_t tmp=*(reg_tab+MASK_RS1(word));
		for(int i=0;i<((word&0x01f00000)>>20);i++)
		{
			tmp=(tmp&0x8000000)|((tmp&0xfffffffe)>>1);
		}
		*(reg_tab+MASK_RD(word))=tmp;//spr
	}


	void instr_lw(uint32_t * pc,uint32_t * reg_tab,uint32_t  word)
	{//ładuje z adresu pc+offset do rd 
		LOG("lw");
		
		int32_t offs=0;
		if(word&0x80000000)
		{
			offs=0xfffff800;
		}
		offs|=(word&0x7ff00000)>>20;
		uint32_t addr=(*(reg_tab+MASK_RS1(word))+offs)%MEM_SIZE;
		
		uint32_t tmp=0;//wartość[addr]
		if(IS_BIG_ENDIAN)
		{
			tmp|=((uint32_t)all_ptr[addr+0])<<24;
			tmp|=((uint32_t)all_ptr[addr+1])<<16;
			tmp|=((uint32_t)all_ptr[addr+2])<<8;
			tmp|=((uint32_t)all_ptr[addr+3]);
		}
		else
		{
			tmp|=((uint32_t)all_ptr[addr+3])<<24;
			tmp|=((uint32_t)all_ptr[addr+2])<<16;
			tmp|=((uint32_t)all_ptr[addr+1])<<8;
			tmp|=((uint32_t)all_ptr[addr+0]);
		}
		*(reg_tab+MASK_RD(word))=tmp;
		
		(*pc)+=PC_INC;
	}

	void instr_andi(uint32_t * pc,uint32_t * reg_tab,uint32_t  word)
	{
		LOG("andi");
		
		(*pc)+=PC_INC;
		int32_t offs=0;
		if(word&0x80000000)
		{
			offs=0xfffff800;
		}
		offs|=(word&0x7ff00000)>>20;
		*(reg_tab+MASK_RD(word))=(*(reg_tab+MASK_RS1(word)))&offs;
		
	}


