
struct allreg
{
	uint32_t reg[32];

};

#define OPCODE_MASK 0x0000007f
#define RS1_MASK 	0x000f8000
#define RS2_MASK 	0x01f00000
#define RD_MASK 	0x00000f80


#define ASM_LUI_OPCODE
#define ASM_ADDI_OPCODE
