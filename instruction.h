
#ifndef STDINT_U
#define STDINT_U
	#include <stdint.h>
#endif //STDINT_U

#ifndef INSTRUCTION_SET
	#define INSTRUCTION_SET

	#define PC_INC 4 //minimalny skok w pamięci

	#define MASK_OPCODE(word) 	(((word)&0x0000007f))
	#define MASK_RD(word) 		(((word)&0x00000f80)>>7)
	#define MASK_RS1(word) 		(((word)&0x000f8000)>>15)
	#define MASK_RS2(word) 		(((word)&0x01f00000)>>20)
	#define MASK_FUNC3(word) 	(((word)&0x00007000)>>12)

	
	#define OPCODE_LUI 0x37
	//void instr_lui(uint32_t * pc,uint32_t * reg_tab,uint32_t imm,uint8_t rd)
	void instr_lui(uint32_t * pc,uint32_t * reg_tab,uint32_t  word);

	#define OPCODE_AUIPC 0x17
	//void instr_auipc(uint32_t * pc,uint32_t * reg_tab,uint32_t imm,uint8_t rd)
	void instr_auipc(uint32_t * pc,uint32_t * reg_tab,uint32_t  word);

	#define OPCODE_JAL 0x6f
	//void instr_jal(uint32_t * pc,uint32_t * reg_tab, uint32_t immp,uint8_t rd)
	void instr_jal(uint32_t * pc,uint32_t * reg_tab,uint32_t  word);

	#define OPCODE_JALR 0x67
	#define OPCODE_JALR_FUNC3 0x00
	//void instr_jalr(uint32_t * pc,uint32_t * reg_tab, uint32_t imms,uint8_t rd,uint8_t rs1)
	void instr_jalr(uint32_t * pc,uint32_t * reg_tab,uint32_t  word);

	#define OPCODE_BGEU 0x63
	#define OPCODE_BGEU_FUNC3 0x07
	//void instr_bgeu(uint32_t * pc,uint32_t * reg_tab, uint32_t immf,uint32_t imm,uint8_t rs1, uint8_t rs2)//immf ->imm [12|10:5]
	void instr_bgeu(uint32_t * pc,uint32_t * reg_tab,uint32_t  word);//immf ->imm [12|10:5]


	#define OPCODE_SW 0x23
	#define OPCODE_SW_FUNC3 0x02
	//void instr_sw(uint32_t * pc,uint32_t * reg_tab,uint32_t immf,uint32_t imm,uint8_t, rs1 uint8_t rs2)
	void instr_sw(uint32_t * pc,uint32_t * reg_tab,uint32_t  word);



	#define OPCODE_SB 0x23
	#define OPCODE_SB_FUNC3 0x00
	//void instr_sb(uint32_t * pc,uint32_t * reg_tab, uint32_t immf,uint32_t imm,uint8_t, rs1 uint8_t rs2)
	void instr_sb(uint32_t * pc,uint32_t * reg_tab,uint32_t  word);

	 
	#define OPCODE_ADDI 0x13
	#define OPCODE_ADDI_FUNC3 0x00
	//void instr_addi(uint32_t * pc,uint32_t * reg_tab,uint32_t imm,uint8_t rd, uint8_t rs1)
	void instr_addi(uint32_t * pc,uint32_t * reg_tab,uint32_t  word);


	#define OPCODE_SRAI 0x13
	#define OPCODE_SRAI_FUNC3 0x05
	//void instr_srai(uint32_t * pc,uint32_t * reg_tab,)
	void instr_srai(uint32_t * pc,uint32_t * reg_tab,uint32_t  word);


	#define OPCODE_LW 0x03
	#define OPCODE_LW_FUNC3 0x02 
	//void instr_lw(uint32_t * pc,uint32_t * reg_tab, uint32_t imm,uint8_t rd, uint8_t rs1)
	void instr_lw(uint32_t * pc,uint32_t * reg_tab,uint32_t  word);

	#define OPCODE_ANDI 0x13
	#define OPCODE_ANDI_FUNC3 0x07
	//void instr_andi(uint32_t * pc,uint32_t * reg_tab, uint32_t imm,uint8_t rd, uint8_t rs1)
	void instr_andi(uint32_t * pc,uint32_t * reg_tab,uint32_t  word);



	//void instr_(uint32_t * pc,uint32_t * reg_tab,)
	//uint8_t loadb(uint8_t * mptr, uint32_t pos);
	/*uint8_t loadw(uint8_t * mptr, uint32_t pos);
	void storeb(uint8_t * mptr, uint32_t pos,uint8_t val);
	void storew(uint8_t * mptr, uint32_t pos,uint32_t val);*/
//uint32_t load_word(uint32_t addr);
//void store_word(uint32_t addr,uint32_t word);
//void store_byte(uint32_t addr,uint8_t word);




	/* obowiązkowe
	 * sw
	 * sb
	 * lui 		.
	 * jal		.
	 * auipc	.
	 * addi
	 * srai
	 * lw
	 * jalr		.
	 * bgeu
	 * andi
	 * 
	 * */

#endif //INSTRUCTION_SET
