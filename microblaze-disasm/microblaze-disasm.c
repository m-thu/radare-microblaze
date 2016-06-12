#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <r_asm.h>
#include <r_lib.h>
#include <r_types.h>

enum INSTR_TYPE {
/* type a: three registers */
	TYPE_A,
	TYPE_A_CMP,
	TYPE_A_MUL,
	TYPE_A_BSRA_BSLL,
	TYPE_A_IDIV,
	TYPE_A_GETD_PUTD,
	TYPE_A_FLOAT,
	TYPE_A_PCMPBF,
	TYPE_A_PCMPEQ,
	TYPE_A_PCMPNE,
	TYPE_A_BRANCH,
	TYPE_A_BRANCH_COND,
/* type b: two registers, one 16 bit immediate */
	TYPE_B,
	TYPE_B_BSI,
	TYPE_B_GET_PUT,
	TYPE_B_SPR_MSR,
	TYPE_B_RT,
	TYPE_B_BRANCH,
	TYPE_B_BRANCH_COND,
/* mixed type */
	TYPE_MISC_1,
/* extends immediate value of next instructions to 32 bit */
	TYPE_IMM,
/* invalid instruction */
	TYPE_INVALID
};

struct microblaze_instr {
	const char *m;
	enum INSTR_TYPE type;
};

static struct microblaze_instr instr[] = {
	/* 0x00 */ {"add r%i, r%i, r%i", TYPE_A},
	/* 0x01 */ {"rsub r%i, r%i, r%i", TYPE_A},
	/* 0x02 */ {"addc r%i, r%i, r%i", TYPE_A},
	/* 0x03 */ {"rsubc r%i, r%i, r%i", TYPE_A},
	/* 0x04 */ {"addk r%i, r%i, r%i", TYPE_A},
	/* 0x05 */ {"", TYPE_A_CMP},
		/* rsubk Rd, Ra, Rb */
		/* cmp Rd, Ra, Rb */
		/* cmpu Rd, Ra, Rb */
	/* 0x06 */ {"addkc r%i, r%i, r%i", TYPE_A},
	/* 0x07 */ {"rsubkc r%i, r%i, r%i", TYPE_A},
	/* 0x08 */ {"addi r%i, r%i, 0x%04x", TYPE_B},
	/* 0x09 */ {"rsubi r%i, r%i, 0x%04x", TYPE_B},
	/* 0x0a */ {"addic r%i, r%i, 0x%04x", TYPE_B},
	/* 0x0b */ {"rsubic r%i, r%i, 0x%04x", TYPE_B},
	/* 0x0c */ {"addik r%i, r%i, 0x%04x", TYPE_B},
	/* 0x0d */ {"rsubik r%i, r%i, 0x%04x", TYPE_B},
	/* 0x0e */ {"addikc r%i, r%i, 0x%04x", TYPE_B},
	/* 0x0f */ {"rsubikc r%i, r%i, 0x%04x", TYPE_B},
	/* 0x10 */ {"", TYPE_A_MUL},
		/* mul Rd, Ra, Rb */
		/* mulh Rd, Ra, Rb */
		/* mulhu Rd, Ra, Rb */
		/* mulhsu Rd, Ra, Rb */
	/* 0x11 */ {"", TYPE_A_BSRA_BSLL},
		/* bsra Rd, Ra, Rb */
		/* bsll Rd, Ra, Rb */
	/* 0x12 */ {"", TYPE_A_IDIV},
		/* idiv Rd, Ra, Rb */
		/* idivu Rd, Ra, Rb */
	/* 0x13 */ {"", TYPE_A_GETD_PUTD},
		/* [tnea]getd Rd, Rb */
		/* [tna]putd Ra, Rb */
		/* [tneca]getd Rd, Rb */
		/* [tnca]putd Ra, Rb */
	/* 0x14 */ {"", TYPE_INVALID},
	/* 0x15 */ {"", TYPE_INVALID},
	/* 0x16 */ {"", TYPE_A_FLOAT},
		/* fadd Rd, Ra, Rb */
		/* frsub Rd, Ra, Rb */
		/* fmul Rd, Ra, Rb */
		/* fdiv Rd, Ra, Rb */
		/* fcmp.un Rd, Ra, Rb */
		/* fcmp.lt Rd, Ra, Rb */
		/* fcmp.eq Rd, Ra, Rb */
		/* fcmp.le Rd, Ra, Rb */
		/* fcmp.gt Rd, Ra, Rb */
		/* fcmp.ne Rd, Ra, Rb */
		/* fcmp.ge Rd, Ra, Rb */
		/* flt Rd, Ra */
		/* fint Rd, Ra */
		/* fsqrt Rd, Ra */
	/* 0x17 */ {"", TYPE_INVALID},
	/* 0x18 */ {"muli r%i, r%i, 0x%04x", TYPE_B},
	/* 0x19 */ {"", TYPE_B_BSI},
		/* bsrli Rd, Ra, Imm5 */
		/* bsrai Rd, Ra, Imm5 */
		/* bslli Rd, Ra, Imm5 */
	/* 0x1a */ {"", TYPE_INVALID},
	/* 0x1b */ {"", TYPE_B_GET_PUT},
		/* [tnea]get Rd, FSLx */
		/* [tna]put Ra, FSLx */
		/* [tneca]get Rd, FSLx */
		/* [tnca]put Ra, FSLx */
	/* 0x1c */ {"", TYPE_INVALID},
	/* 0x1d */ {"", TYPE_INVALID},
	/* 0x1e */ {"", TYPE_INVALID},
	/* 0x1f */ {"", TYPE_INVALID},
	/* 0x20 */ {"", TYPE_A_PCMPBF},
		/* or Rd, Ra, Rb */
		/* pcmpbf Rd, Ra, Rb */
	/* 0x21 */ {"and r%i, r%i, r%i", TYPE_A},
	/* 0x22 */ {"", TYPE_A_PCMPEQ},
		/* xor Rd, Ra, Rb */
		/* pcmpeq Rd, Ra, Rb */
	/* 0x23 */ {"", TYPE_A_PCMPNE},
		/* andn Rd, Ra, Rb */
		/* pcmpne Rd, Ra, Rb */
	/* 0x24 */ {"", TYPE_MISC_1},
		/* sra Rd, Ra */
		/* src Rd, Ra */
		/* srl Rd, Ra */
		/* sext8 Rd, Ra */
		/* sext16 Rd, Ra */
		/* wic Ra, Rb */
		/* wdc Ra, Rb */
	/* 0x25 */ {"", TYPE_B_SPR_MSR},
		/* mts Sd, Ra */
		/* mfs Rd, Sa */
		/* msrclr Rd, Imm */
		/* msrset Rd, Imm */
	/* 0x26 */ {"", TYPE_A_BRANCH},
		/* br Rb */
		/* brd Rb */
		/* brld Rd, Rb */
		/* bra Rb */
		/* brad Rb */
		/* brald Rd, Rb */
		/* brk Rd, Rbk */
	/* 0x27 */ {"", TYPE_A_BRANCH_COND},
		/* beq Ra, Rb */
		/* bne Ra, Rb */
		/* blt Ra, Rb */
		/* ble Ra, Rb */
		/* bgt Ra, Rb */
		/* bge Ra, Rb */
		/* beqd Ra, Rb */
		/* bned Ra, Rb */
		/* bltd Ra, Rb */
		/* bled Ra, Rb */
		/* bgtd Ra, Rb */
		/* bged Ra, Rb */
	/* 0x28 */ {"ori r%i, r%i, 0x%04x", TYPE_B},
	/* 0x29 */ {"andi r%i, r%i, 0x%04x", TYPE_B},
	/* 0x2a */ {"xori r%i, r%i, 0x%04x", TYPE_B},
	/* 0x2b */ {"andni r%i, r%i, 0x%04x", TYPE_B},
	/* 0x2c */ {"", TYPE_IMM},
		/* imm Imm */
	/* 0x2d */ {"", TYPE_B_RT},
		/* rtsd Ra, Imm */
		/* rtid Ra, Imm */
		/* rtbd Ra, Imm */
		/* rted Ra, Imm */
	/* 0x2e */ {"", TYPE_B_BRANCH},
		/* bri Imm */
		/* brid Imm */
		/* brlid Rd, Imm */
		/* brai Imm */
		/* braid Imm */
		/* bralid Rd, Imm */
		/* brki Rd, Imm */
	/* 0x2f */ {"", TYPE_B_BRANCH_COND},
		/* beqi Ra, Imm */
		/* bnei Ra, Imm */
		/* blti Ra, Imm */
		/* blei Ra, Imm */
		/* bgti Ra, Imm */
		/* bgei Ra, Imm */
		/* beqid Ra, Imm */
		/* bneid Ra, Imm */
		/* bltid Ra, Imm */
		/* bleid Ra, Imm */
		/* bgtid Ra, Imm */
		/* bgeid Ra, Imm */
	/* 0x30 */ {"lbu r%i, r%i, r%i", TYPE_A},
	/* 0x31 */ {"lhu r%i, r%i, r%i", TYPE_A},
	/* 0x32 */ {"lw r%i, r%i, r%i", TYPE_A},
	/* 0x33 */ {"", TYPE_INVALID},
	/* 0x34 */ {"sb r%i, r%i, r%i", TYPE_A},
	/* 0x35 */ {"sh r%i, r%i, r%i", TYPE_A},
	/* 0x36 */ {"sw r%i, r%i, r%i", TYPE_A},
	/* 0x37 */ {"", TYPE_INVALID},
	/* 0x38 */ {"lbui r%i, r%i, 0x%04x", TYPE_B},
	/* 0x39 */ {"lhui r%i, r%i, 0x%04x", TYPE_B},
	/* 0x3a */ {"lwi r%i, r%i, 0x%04x", TYPE_B},
	/* 0x3b */ {"", TYPE_INVALID},
	/* 0x3c */ {"sbi r%i, r%i, 0x%04x", TYPE_B},
	/* 0x3d */ {"shi r%i, r%i, 0x%04x", TYPE_B},
	/* 0x3e */ {"swi r%i, r%i, 0x%04x", TYPE_B},
	/* 0x3f */ {"", TYPE_INVALID}
};

static int disassemble(RAsm *a, RAsmOp *op, const ut8 *buf, int len)
{
	uint32_t pc, tmp;
	uint32_t i;
	uint8_t opcode;
	uint8_t Rd, Ra, Rb;
	uint16_t Imm;
	uint16_t sec;

	/* get current program counter */
	pc = a->pc;

	/* convert big endian instruction word to little endian,
	 * bit 0: MSB, bit 31: LSB */
	/*i = buf[0]<<24 | buf[1]<<16 | buf[2]<<8 | buf[3];*/
	i = buf[3]<<24 | buf[2]<<16 | buf[1]<<8 | buf[0];
	/* all instructions are 32 bits wide */
	op->size = 4;

	/* extract primary opcode bit[0:5] */
	opcode = i>>26 & 0x3f;
	/* "secondary opcode", TYPE_A instructions */
	sec = i & 0x7ff;

	/* extract operands */
	Rd = i>>21 & 0x1f;
	Ra = i>>16 & 0x1f;
	Rb = i>>11 & 0x1f;
	Imm = i & 0xffff;

	switch (instr[opcode].type) {
	case TYPE_INVALID:
		return 0;

	case TYPE_A:
		snprintf(op->buf_asm, R_ASM_BUFSIZE, instr[opcode].m,
		         Rd, Ra, Rb);
		return 4;

	case TYPE_B:
		snprintf(op->buf_asm, R_ASM_BUFSIZE, instr[opcode].m,
		         Rd, Ra, Imm);
		return 4;

	case TYPE_A_CMP:
		switch (sec) {
		case 0x000:
			snprintf(op->buf_asm, R_ASM_BUFSIZE, "rsubk r%i, r%i, r%i",
			         Rd, Ra, Rb);
			return 4;

		case 0x001:
			snprintf(op->buf_asm, R_ASM_BUFSIZE, "cmp r%i, r%i, r%i",
			         Rd, Ra, Rb);
			return 4;

		case 0x003:
			snprintf(op->buf_asm, R_ASM_BUFSIZE, "cmpu r%i, r%i, r%i",
			         Rd, Ra, Rb);
			return 4;

		default:
			return 0;
		}

	case TYPE_A_MUL:
		switch (sec) {
		case 0x000:
			snprintf(op->buf_asm, R_ASM_BUFSIZE, "mul r%i, r%i, r%i",
			        Rd, Ra, Rb);
			return 4;

		case 0x001:
			snprintf(op->buf_asm, R_ASM_BUFSIZE, "mulh r%i, r%i, r%i",
			         Rd, Ra, Rb);
			return 4;

		case 0x003:
			snprintf(op->buf_asm, R_ASM_BUFSIZE, "mulhu r%i, r%i, r%i",
			         Rd, Ra, Rb);
			return 4;

		case 0x002:
			snprintf(op->buf_asm, R_ASM_BUFSIZE, "mulhsu r%i, r%i, r%i",
			         Rd, Ra, Rb);
			return 4;

		default:
			return 0;
		}

	case TYPE_A_BSRA_BSLL:
		switch (sec) {
		case 0x200:
			snprintf(op->buf_asm, R_ASM_BUFSIZE, "bsra r%i, r%i, r%i",
			         Rd, Ra, Rb);
			return 4;

		case 0x400:
			snprintf(op->buf_asm, R_ASM_BUFSIZE, "bsll r%i, r%i, r%i",
			         Rd, Ra, Rb);
			return 4;

		default:
			return 0;
		}

	case TYPE_A_IDIV:
		switch (sec) {
		case 0x000:
			snprintf(op->buf_asm, R_ASM_BUFSIZE, "idiv r%i, r%i, r%i",
			         Rd, Ra, Rb);
			return 4;

		case 0x002:
			snprintf(op->buf_asm, R_ASM_BUFSIZE, "idivu r%i, r%i, r%i",
			         Rd, Ra, Rb);
			return 4;

		default:
			return 0;
		}

	case TYPE_A_GETD_PUTD:
		if (Ra == 0x00 && Rd) {
			/* [tneca]getd */
			snprintf(op->buf_asm, R_ASM_BUFSIZE, "%s%s%s%s%sgetd r%i, r%i",
			         sec & (1<<7) ? "t" : "",
			         sec & (1<<9) ? "n" : "",
			         sec & (1<<5) ? "e" : "",
			         sec & (1<<8) ? "c" : "",
			         sec & (1<<6) ? "a" : "",
			         Rd, Rb);
			return 4;
		} else if (Rd == 0x00) {
			/* [tnca]putd */
			snprintf(op->buf_asm, R_ASM_BUFSIZE, "%s%s%s%sputd r%i",
			         sec & (1<<7) ? "t" : "",
			         sec & (1<<9) ? "n" : "",
			         sec & (1<<8) ? "c" : "",
			         sec & (1<<6) ? "a" : "",
				 Rb);
			return 4;
		}
		break;

	case TYPE_A_FLOAT:
		switch (sec) {
		case 0x000:
			snprintf(op->buf_asm, R_ASM_BUFSIZE, "fadd r%i, r%i, r%i",
			         Rd, Ra, Rb);
			return 4;

		case 0x080:
			snprintf(op->buf_asm, R_ASM_BUFSIZE, "frsub r%i, r%i, r%i",
			         Rd, Ra, Rb);
			return 4;

		case 0x100:
			snprintf(op->buf_asm, R_ASM_BUFSIZE, "fmul r%i, r%i, r%i",
			         Rd, Ra, Rb);
			return 4;

		case 0x180:
			snprintf(op->buf_asm, R_ASM_BUFSIZE, "fdiv r%i, r%i, r%i",
			         Rd, Ra, Rb);
			return 4;

		case 0x200:
			snprintf(op->buf_asm, R_ASM_BUFSIZE, "fmcmp.un r%i, r%i, r%i",
			         Rd, Ra, Rb);
			return 4;

		case 0x210:
			snprintf(op->buf_asm, R_ASM_BUFSIZE, "fcmp.lt r%i, r%i, r%i",
			         Rd, Ra, Rb);
			return 4;

		case 0x220:
			snprintf(op->buf_asm, R_ASM_BUFSIZE, "fcmp.eq r%i, r%i, r%i",
			         Rd, Ra, Rb);
			return 4;

		case 0x230:
			snprintf(op->buf_asm, R_ASM_BUFSIZE, "fcmp.le r%i, r%i, r%i",
			         Rd, Ra, Rb);
			return 4;

		case 0x240:
			snprintf(op->buf_asm, R_ASM_BUFSIZE, "fcmp.gt r%i, r%i, r%i",
			         Rd, Ra, Rb);
			return 4;

		case 0x250:
			snprintf(op->buf_asm, R_ASM_BUFSIZE, "fcmp.ne r%i, r%i, r%i",
			         Rd, Ra, Rb);
			return 4;

		case 0x260:
			snprintf(op->buf_asm, R_ASM_BUFSIZE, "fcmp.ge r%i, r%i, r%i",
			         Rd, Ra, Rb);
			return 4;

		case 0x280:
			snprintf(op->buf_asm, R_ASM_BUFSIZE, "flt r%i, r%i",
			         Rd, Ra);
			return 4;

		case 0x300:
			snprintf(op->buf_asm, R_ASM_BUFSIZE, "fint r%i, r%i",
			         Rd, Ra);
			return 4;

		case 0x380:
			snprintf(op->buf_asm, R_ASM_BUFSIZE, "fsqrt r%i, r%i",
			         Rd, Ra);
			return 4;

		default:
			return 0;
		}

	case TYPE_B_BSI:
		switch (sec>>5 & 0x7ff) {
		case 0x000:
			snprintf(op->buf_asm, R_ASM_BUFSIZE, "bsrli r%i, r%i, 0x%02x",
			         Rd, Ra, sec & 0x1f);
			return 4;

		case 0x010:
			snprintf(op->buf_asm, R_ASM_BUFSIZE, "bsrai r%i, r%i, 0x%02x",
			         Rd, Ra, sec & 0x1f);
			return 4;

		case 0x020:
			snprintf(op->buf_asm, R_ASM_BUFSIZE, "bslli r%i, r%i, 0x%02x",
			         Rd, Ra, sec & 0x1f);
			return 4;

		default:
			return 0;
		}

	case TYPE_B_GET_PUT:
		if (Ra == 0x00 && Rd) {
			/* get */
			snprintf(op->buf_asm, R_ASM_BUFSIZE, "%s%s%s%s%sget r%i, rfsl%i",
			         Imm & (1<<12) ? "t" : "",
			         Imm & (1<<14) ? "n" : "",
			         Imm & (1<<10) ? "e" : "",
			         Imm & (1<<13) ? "c" : "",
			         Imm & (1<<11) ? "a" : "",
			         Rd, Imm & 0xf);
			return 4;
		} else if (Rd == 0x00) {
			/* put */
			snprintf(op->buf_asm, R_ASM_BUFSIZE, "%s%s%s%sput rfsl%i",
			         Imm & (1<<12) ? "t" : "",
			         Imm & (1<<14) ? "n" : "",
			         Imm & (1<<13) ? "c" : "",
				 Imm & (1<<11) ? "a" : "",
				 Imm & 0xf);
			return 4;
		}
		break;

	case TYPE_A_PCMPBF:
		switch (sec) {
		case 0x000:
			snprintf(op->buf_asm, R_ASM_BUFSIZE, "or r%i, r%i, r%i",
			         Rd, Ra, Rb);
			return 4;

		case 0x400:
			snprintf(op->buf_asm, R_ASM_BUFSIZE, "pcmpbf r%i, r%i, r%i",
			         Rd, Ra, Rb);
			return 4;

		default:
			return 0;
		}

	case TYPE_A_PCMPEQ:
		switch (sec) {
		case 0x000:
			snprintf(op->buf_asm, R_ASM_BUFSIZE, "xor r%i, r%i, r%i",
			         Rd, Ra, Rb);
			return 4;

		case 0x400:
			snprintf(op->buf_asm, R_ASM_BUFSIZE, "pcmpeq r%i, r%i, r%i",
			         Rd, Ra, Rb);
			return 4;

		default:
			return 0;
		}

	case TYPE_A_PCMPNE:
		switch (sec) {
		case 0x000:
			snprintf(op->buf_asm, R_ASM_BUFSIZE, "andn r%i, r%i, r%i",
			         Rd, Ra, Rb);
			return 4;

		case 0x400:
			snprintf(op->buf_asm, R_ASM_BUFSIZE, "pcmpne r%i, r%i, r%i",
			         Rd, Ra, Rb);
			return 4;

		default:
			return 0;
		}

	case TYPE_MISC_1:
		switch (sec) {
		case 0x001:
			snprintf(op->buf_asm, R_ASM_BUFSIZE, "sra r%i, r%i",
			         Rd, Ra);
			return 4;

		case 0x021:
			snprintf(op->buf_asm, R_ASM_BUFSIZE, "src r%i, r%i",
			         Rd, Ra);
			return 4;

		case 0x041:
			snprintf(op->buf_asm, R_ASM_BUFSIZE, "srl r%i, r%i",
			         Rd, Ra);
			return 4;

		case 0x060:
			snprintf(op->buf_asm, R_ASM_BUFSIZE, "sext8 r%i, r%i",
			         Rd, Ra);
			return 4;

		case 0x061:
			snprintf(op->buf_asm, R_ASM_BUFSIZE, "sext16 r%i, r%i",
			         Rd, Ra);
			return 4;

		case 0x068:
			snprintf(op->buf_asm, R_ASM_BUFSIZE, "wic r%i, r%i",
			         Ra, Rb);
			return 4;

		case 0x064:
			snprintf(op->buf_asm, R_ASM_BUFSIZE, "wdc r%i, r%i",
			         Ra, Rb);
			return 4;

		default:
			return 0;
		}

	case TYPE_B_SPR_MSR:
		if ((Imm>>14 & 0x3) == 0x3) {
			/* mts */
			snprintf(op->buf_asm, R_ASM_BUFSIZE, "mts 0x%04x, r%i",
			         Imm & 0x3fff, Ra);
			return 4;
		} else if ((Imm>>14 & 0x3) == 0x2) {
			/* mfs */
			snprintf(op->buf_asm, R_ASM_BUFSIZE, "mfs r%i, 0x%04x",
			         Rd, Imm & 0x3fff);
			return 4;
		} else if ((Imm>>14 & 0x3) == 0x0) {
			if (Ra == 0x11) {
				/* msrclr */
				snprintf(op->buf_asm, R_ASM_BUFSIZE, "msrclr r%i, 0x%04x",
				         Rd, Imm & 0x3fff);
				return 4;
			} else if (Ra == 0x10) {
				/* msrset */
				snprintf(op->buf_asm, R_ASM_BUFSIZE, "msrset r%i, 0x%04x",
				         Rd, Imm & 0x3fff);
				return 4;
			}
		}
		break;

	case TYPE_A_BRANCH:
		switch (Ra) {
		case 0x00:
			snprintf(op->buf_asm, R_ASM_BUFSIZE, "br r%i", Rb);
			return 4;

		case 0x10:
			snprintf(op->buf_asm, R_ASM_BUFSIZE, "brd r%i", Rb);
			return 4;

		case 0x14:
			snprintf(op->buf_asm, R_ASM_BUFSIZE, "brld r%i, r%i",
			         Rd, Rb);
			return 4;

		case 0x08:
			snprintf(op->buf_asm, R_ASM_BUFSIZE, "bra r%i", Rb);
			return 4;

		case 0x18:
			snprintf(op->buf_asm, R_ASM_BUFSIZE, "brad r%i", Rb);
			return 4;

		case 0x1c:
			snprintf(op->buf_asm, R_ASM_BUFSIZE, "brald r%i, r%i",
			         Rd, Rb);
			return 4;

		case 0x0c:
			snprintf(op->buf_asm, R_ASM_BUFSIZE, "brk r%i, r%i",
			         Rd, Rb);
			return 4;

		default:
			return 0;
		}

	case TYPE_A_BRANCH_COND:
		switch (Rd) {
		case 0x00:
			snprintf(op->buf_asm, R_ASM_BUFSIZE, "beq r%i, r%i",
			         Ra, Rb);
			return 4;

		case 0x01:
			snprintf(op->buf_asm, R_ASM_BUFSIZE, "bne r%i, r%i",
			         Ra, Rb);
			return 4;

		case 0x02:
			snprintf(op->buf_asm, R_ASM_BUFSIZE, "blt r%i, r%i",
			         Ra, Rb);
			return 4;

		case 0x03:
			snprintf(op->buf_asm, R_ASM_BUFSIZE, "ble r%i, r%i",
			         Ra, Rb);
			return 4;

		case 0x04:
			snprintf(op->buf_asm, R_ASM_BUFSIZE, "bgt r%i, r%i",
			         Ra, Rb);
			return 4;

		case 0x05:
			snprintf(op->buf_asm, R_ASM_BUFSIZE, "bge r%i, r%i",
			         Ra, Rb);
			return 4;

		case 0x10:
			snprintf(op->buf_asm, R_ASM_BUFSIZE, "beqd r%i, r%i",
			         Ra, Rb);
			return 4;

		case 0x11:
			snprintf(op->buf_asm, R_ASM_BUFSIZE, "bned r%i, r%i",
			         Ra, Rb);
			return 4;

		case 0x12:
			snprintf(op->buf_asm, R_ASM_BUFSIZE, "bltd r%i, r%i",
			         Ra, Rb);
			return 4;

		case 0x13:
			snprintf(op->buf_asm, R_ASM_BUFSIZE, "bled r%i, r%i",
			         Ra, Rb);
			return 4;

		case 0x14:
			snprintf(op->buf_asm, R_ASM_BUFSIZE, "bgtd r%i, r%i",
			         Ra, Rb);
			return 4;

		case 0x15:
			snprintf(op->buf_asm, R_ASM_BUFSIZE, "bged r%i, r%i",
			         Ra, Rb);
			return 4;

		default:
			return 0;
		}

	case TYPE_IMM:
		snprintf(op->buf_asm, R_ASM_BUFSIZE, "imm 0x%04x", Imm);
		return 4;

	case TYPE_B_RT:
		switch (Rd) {
		case 0x10:
			snprintf(op->buf_asm, R_ASM_BUFSIZE, "rtsd r%i, 0x%04x",
			         Ra, Imm);
			return 4;

		case 0x11:
			snprintf(op->buf_asm, R_ASM_BUFSIZE, "rtid r%i, 0x%04x",
			         Ra, Imm);
			return 4;

		case 0x12:
			snprintf(op->buf_asm, R_ASM_BUFSIZE, "rtbd r%i, 0x%04x",
			         Ra, Imm);
			return 4;

		case 0x14:
			snprintf(op->buf_asm, R_ASM_BUFSIZE, "rted r%i, 0x%04x",
			         Ra, Imm);
			return 4;

		default:
			return 0;
		}

	case TYPE_B_BRANCH:
		tmp = Imm;
		if (tmp & 0x8000)
			tmp |= 0xffff0000;
		pc = pc + (int32_t)tmp;

		switch (Ra) {
		case 0x00:
			snprintf(op->buf_asm, R_ASM_BUFSIZE, "bri 0x%08x", pc);
			return 4;

		case 0x10:
			snprintf(op->buf_asm, R_ASM_BUFSIZE, "brid 0x%08x", pc);
			return 4;

		case 0x14:
			snprintf(op->buf_asm, R_ASM_BUFSIZE, "brlid r%i, 0x%08x",
			         Rd, pc);
			return 4;

		case 0x08:
			snprintf(op->buf_asm, R_ASM_BUFSIZE, "brai 0x%08x", tmp);
			return 4;

		case 0x18:
			snprintf(op->buf_asm, R_ASM_BUFSIZE, "braid 0x%08x", tmp);
			return 4;

		case 0x1c:
			snprintf(op->buf_asm, R_ASM_BUFSIZE, "bralid r%i, 0x%08x",
			         Rd, tmp);
			return 4;

		case 0x0c:
			snprintf(op->buf_asm, R_ASM_BUFSIZE, "brki r%i, 0x%08x",
			         Rd, tmp);
			return 4;

		default:
			return 0;
		}

	case TYPE_B_BRANCH_COND:
		tmp = Imm;
		if (tmp & 0x8000)
			tmp |= 0xffff0000;
		pc = pc + (int32_t)tmp;

		switch (Rd) {
		case 0x00:
			snprintf(op->buf_asm, R_ASM_BUFSIZE, "beqi r%i, 0x%08x",
			         Ra, pc);
			return 4;

		case 0x01:
			snprintf(op->buf_asm, R_ASM_BUFSIZE, "bnei r%i, 0x%08x",
			         Ra, pc);
			return 4;

		case 0x02:
			snprintf(op->buf_asm, R_ASM_BUFSIZE, "blti r%i, 0x%08x",
			         Ra, pc);
			return 4;

		case 0x03:
			snprintf(op->buf_asm, R_ASM_BUFSIZE, "blei r%i, 0x%08x",
			         Ra, pc);
			return 4;

		case 0x04:
			snprintf(op->buf_asm, R_ASM_BUFSIZE, "bgti r%i, 0x%08x",
			         Ra, pc);
			return 4;

		case 0x05:
			snprintf(op->buf_asm, R_ASM_BUFSIZE, "bgei r%i, 0x%08x",
			         Ra, pc);
			return 4;

		case 0x10:
			snprintf(op->buf_asm, R_ASM_BUFSIZE, "beqid r%i, 0x%08x",
			         Ra, pc);
			return 4;

		case 0x11:
			snprintf(op->buf_asm, R_ASM_BUFSIZE, "bneid r%i, 0x%08x",
			         Ra, pc);
			return 4;

		case 0x12:
			snprintf(op->buf_asm, R_ASM_BUFSIZE, "bltid r%i, 0x%08x",
			         Ra, pc);
			return 4;

		case 0x13:
			snprintf(op->buf_asm, R_ASM_BUFSIZE, "bleid r%i, 0x%08x",
			         Ra, pc);
			return 4;

		case 0x14:
			snprintf(op->buf_asm, R_ASM_BUFSIZE, "bgtid r%i, 0x%08x",
			         Ra, pc);
			return 4;

		case 0x15:
			snprintf(op->buf_asm, R_ASM_BUFSIZE, "bgeid r%i, 0x%08x",
			         Ra, pc);
			return 4;

		default:
			return 0;
		}
	}

	return 0;
}

RAsmPlugin r_asm_plugin_microblaze = {
	.name = "microblaze",
	.arch = "microblaze",
	.license = "MIT License",
	.bits = 32,
	.desc = "MicroBlaze plugin",
	.disassemble = &disassemble,
	.init = NULL,
	.fini = NULL,
	.modify = NULL,
	.assemble = NULL
};

#ifndef CORELIB
struct r_lib_struct_t radare_plugin = {
	.type = R_LIB_TYPE_ASM,
	.data = &r_asm_plugin_microblaze
};
#endif
