/*
*
* Matthew Pecko
* Prof. Vulis
* 11/21/2020
* CSc 210 limited x86 emulator
* 
* INFO:
* set OS = false if using g++ to compile. 
* Then run program as follows with .COM file in same directory as program: ./a.out sample.com
* 
* flags bit position 7 = CF
* flags bit position 6 = ZF
* 
* The registers printed in terminal are in hex
* 
*/

#define _CRT_SECURE_NO_DEPRECATE
#define OS true //true if using microsoft visual studio, false if using g++
#define MAXCODE 0x100000
#include <iostream>

typedef unsigned char byte;
typedef unsigned short word;

byte AL=0x00, AH = 0x00, BL = 0x00, BH = 0x00, CL = 0x00, CH = 0x00, DL = 0x00, DH = 0x00;
word AX = 0x0000, CX = 0x0000, DX = 0x0000, BX = 0x0000, SP = 0x0000, BP = 0x0000, SI = 0x0000, DI = 0x0000;
word flags = 0x0000, IP = 0x0000, ES = 0x0000, SS = 0x0000, DS = 0x0000, CS = 0x0000;

byte code[MAXCODE];
byte opcode = 0x00;

void cop(byte opcode);
void dumpRegisters();

//0x00FF = 255
word combine(byte low, byte hi)
{
	word combined = (hi << 8) | low;
	return combined;
}

// Assumes little endian
void printBits(size_t const size, void const* const ptr)
{
	unsigned char* b = (unsigned char*)ptr;
	unsigned char byte;
	int i, j;

	for (i = size - 1; i >= 0; i--) {
		for (j = 7; j >= 0; j--) {
			byte = (b[i] >> j) & 1;
			printf("%u", byte);
		}
	}
	puts("");
}

void addreg8(byte& reg8a, byte& reg8b) {
	if (reg8a > 0xFF - reg8b) {
		flags = flags | (1 << 6);
	}
	reg8a += reg8b;
	if(!reg8a) flags = flags | (1 << 5);
}

void addreg16(word& reg16a, word& reg16b, byte& reg8al, byte& reg8ah, byte& reg8bl, byte& reg8bh) {
	if (reg16a > 0xFFFF - reg16b) {
		flags = flags | (1 << 6);
	}
	reg16a += reg16b;
	reg8al = reg16a & 0xFF;
	reg8ah = reg16a >> 8 & 0xFF;
}

void addreg16s(word& reg16a, word& reg16b) {
	if (reg16a > 0xFFFF - reg16b) {
		flags = flags | (1 << 6);
	}
	reg16a += reg16b;
}

/*
* 
* 
* 00,01,02,03,04,05
10,11,12,13,14,15
70,71,72,73,74,75,76,77,78,79,7a,7b,7c,7d,7e,7f
80,81,83,84,85,86,87
88,89,8A,8B,8C,8D,8E,8F
91,92,93,94,95,96,97,98,99,9a,9c,9d,a0,a1,a2,a3,a4,a5,a6,a7
c6,c7
e2
* 
* 
* 
*/


void cop(byte opcode) {
	switch (opcode) {
	case 0x02:
		//add reg8,reg8
		opcode = code[IP++];
		switch (opcode) {
		case 0xC0:
			//add al,al
			addreg8(AL, AL);
			break;
		case 0xC1:
			//add al,cl
			addreg8(AL, CL);
			break;
		case 0xC2:
			//add al,dl
			addreg8(AL, DL);
			break;
		case 0xC3:
			//add al,bl
			addreg8(AL, BL);
			break;
		case 0xC4:
			//add al,ah
			addreg8(AL, AH);
			break;
		case 0xC5:
			//add al,ch
			addreg8(AL, CH);
			break;
		case 0xC6:
			//add al,dh
			addreg8(AL, DH);
			break;
		case 0xC7:
			//add al,bh
			addreg8(AL, BH);
			break;
		case 0xC8:
			//add cl,al
			addreg8(CL, AL);
			break;
		case 0xC9:
			//add cl,cl
			addreg8(CL, CL);
			break;
		case 0xCA:
			//add cl,dl
			addreg8(CL, DL);
			break;
		case 0xCB:
			//add cl,bl
			addreg8(CL, BL);
			break;
		case 0xCC:
			//add cl,ah
			addreg8(CL, AH);
			break;
		case 0xCD:
			//add cl,ch
			addreg8(CL, CH);
			break;
		case 0xCE:
			//add cl,dh
			addreg8(CL, DH);
			break;
		case 0xCF:
			//add cl,bh
			addreg8(CL, BH);
			break;
		case 0xD0:
			//add dl,al
			addreg8(DL, AL);
			break;
		case 0xD1:
			//add dl,cl
			addreg8(DL, CL);
			break;
		case 0xD2:
			//add dl,dl
			addreg8(DL, DL);
			break;
		case 0xD3:
			//add dl,bl
			addreg8(DL, BL);
			break;
		case 0xD4:
			//add dl,ah
			addreg8(DL, AH);
			break;
		case 0xD5:
			//add dl,ch
			addreg8(DL, CH);
			break;
		case 0xD6:
			//add dl,dh
			addreg8(DL, DH);
			break;
		case 0xD7:
			//add dl,bh
			addreg8(DL, BH);
			break;
		case 0xD8:
			//add bl,al
			addreg8(BL, AL);
			break;
		case 0xD9:
			//add bl,cl
			addreg8(BL, CL);
			break;
		case 0xDA:
			//add bl,dl
			addreg8(BL, DL);
			break;
		case 0xDB:
			//add bl,bl
			addreg8(BL, BL);
			break;
		case 0xDC:
			//add bl,ah
			addreg8(BL, AH);
			break;
		case 0xDD:
			//add bl,ch
			addreg8(BL, CH);
			break;
		case 0xDE:
			//add bl,dh
			addreg8(BL, DH);
			break;
		case 0xDF:
			//add bl,bh
			addreg8(BL, BH);
			break;
		case 0xE0:
			//add ah,al
			addreg8(AH, AL);
			break;
		case 0xE1:
			//add ah,cl
			addreg8(AH, CL);
			break;
		case 0xE2:
			//add ah,dl
			addreg8(AH, DL);
			break;
		case 0xE3:
			//add ah,bl
			addreg8(AH, BL);
			break;
		case 0xE4:
			//add ah,ah
			addreg8(AH, AH);
			break;
		case 0xE5:
			//add ah,ch
			addreg8(AH, CH);
			break;
		case 0xE6:
			//add ah,dh
			addreg8(AH, CH);
			break;
		case 0xE7:
			//add ah,bh
			addreg8(AH, BH);
			break;
		case 0xE8:
			//add ch,al
			addreg8(CH, AL);
			break;
		case 0xE9:
			//add ch,cl
			addreg8(CH, CL);
			break;
		case 0xEA:
			//add ch,dl
			addreg8(CH, DL);
			break;
		case 0xEB:
			//add ch,bl
			addreg8(CH, BL);
			break;
		case 0xEC:
			//add ch,ah
			addreg8(CH, AH);
			break;
		case 0xED:
			//add ch,ch
			addreg8(CH, CH);
			break;
		case 0xEE:
			//add ch,dh
			addreg8(CH, DH);
			break;
		case 0xEF:
			//add ch,bh
			addreg8(CH, BH);
			break;
		case 0xF0:
			//add dh,al
			addreg8(DH, AL);
			break;
		case 0xF1:
			//add dh,cl
			addreg8(DH, CL);
			break;
		case 0xF2:
			//add dh,dl
			addreg8(DH, DL);
			break;
		case 0xF3:
			//add dh,bl
			addreg8(DH, BL);
			break;
		case 0xF4:
			//add dh,ah
			addreg8(DH, AH);
			break;
		case 0xF5:
			//add dh,ch
			addreg8(DH, CH);
			break;
		case 0xF6:
			//add dh,dh
			addreg8(DH, AH);
			break;
		case 0xF7:
			//add dh,bh
			addreg8(DH, BH);
			break;
		case 0xF8:
			//add bh,al
			addreg8(BH, AL);
			break;
		case 0xF9:
			//add bh,cl
			addreg8(BH, CL);
			break;
		case 0xFA:
			//add bh,dl
			addreg8(BH, DL);
			break;
		case 0xFB:
			//add bh,bl
			addreg8(BH, BL);
			break;
		case 0xFC:
			//add bh,ah
			addreg8(BH, AH);
			break;
		case 0xFD:
			//add bh,ch
			addreg8(BH, CH);
			break;
		case 0xFE:
			//add bh,dh
			addreg8(BH, DH);
			break;
		case 0xFF:
			//add bh,bh
			addreg8(BH, BH);
			break;
		}
		break;
	case 0x03:
		//add reg16,reg16
		opcode = code[IP++];
		switch (opcode) {
		case 0xC0:
			//add ax,ax
			addreg16(AX, AX, AL, AH, AL, AH);
			break;
		case 0xC1:
			//add ax,cx
			addreg16(AX, CX, AL, AH, CL, CH);
			break;
		case 0xC2:
			//add ax,dx
			addreg16(AX, DX, AL, AH, DL, DH);
			break;
		case 0xC3:
			//add ax,bx
			addreg16(AX, BX, AL, AH, BL, BH);
			break;
		case 0xC4:
			//add ax,sp
			addreg16(AX, SP, AL, AH, AL, AH);
			break;
		case 0xC5:
			//add ax,bp
			addreg16(AX, BP, AL, AH, AL, AH);
			break;
		case 0xC6:
			//add ax,si
			addreg16(AX, SI, AL, AH, AL, AH);
			break;
		case 0xC7:
			//add ax,di
			addreg16(AX, DI, AL, AH, AL, AH);
			break;
		case 0xC8:
			//add cx,ax
			addreg16(CX, AX, CL, CH, AL, AH);
			break;
		case 0xC9:
			//add cx,cx
			addreg16(CX, CX, CL, CH, CL, CH);
			break;
		case 0xCA:
			//add cx,dx
			addreg16(CX, DX, CL, CH, DL, DH);
			break;
		case 0xCB:
			//add cx,bx
			addreg16(CX, BX, CL, CH, BL, BH);
			break;
		case 0xCC:
			//add cx,sp
			addreg16(CX, SP, CL, CH, CL, CH);
			break;
		case 0xCD:
			//add cx,bp
			addreg16(CX, BP, CL, CH, CL, CH);
			break;
		case 0xCE:
			//add cx,si
			addreg16(CX, SI, CL, CH, CL, CH);
			break;
		case 0xCF:
			//add cx,di
			addreg16(CX, DI, CL, CH, CL, CH);
			break;
		case 0xD0:
			//add dx,ax
			addreg16(DX, AX, DL, DH, AL, AH);
			break;
		case 0xD1:
			//add dx,cx
			addreg16(DX, CX, DL, DH, CL, CH);
			break;
		case 0xD2:
			//add dx,dx
			addreg16(DX, DX, DL, DH, DL, DH);
			break;
		case 0xD3:
			//add dx,bx
			addreg16(DX, BX, DL, DH, BL, BH);
			break;
		case 0xD4:
			//add dx,sp
			addreg16(DX, SP, DL, DH, DL, DH);
			break;
		case 0xD5:
			//add dx,bp
			addreg16(DX, BP, DL, DH, DL, DH);
			break;
		case 0xD6:
			//add dx,si
			addreg16(DX, SI, DL, DH, DL, DH);
			break;
		case 0xD7:
			//add dx,di
			addreg16(DX, DI, DL, DH, DL, DH);
			break;
		case 0xD8:
			//add bx,ax
			addreg16(BX, AX, BL, BH, AL, AH);
			break;
		case 0xD9:
			//add bx,cx
			addreg16(BX, CX, BL, BH, CL, CH);
			break;
		case 0xDA:
			//add bx,dx
			addreg16(BX, DX, BL, BH, DL, DH);
			break;
		case 0xDB:
			//add bx,bx
			addreg16(BX, BX, BL, BH, BL, BH);
			break;
		case 0xDC:
			//add bx,sp
			addreg16(BX, SP, BL, BH, BL, BH);
			break;
		case 0xDD:
			//add bx,bp
			addreg16(BX, BP, BL, BH, BL, BH);
			break;
		case 0xDE:
			//add bx,si
			addreg16(BX, SI, BL, BH, BL, BH);
			break;
		case 0xDF:
			//add bx,di
			addreg16(BX, DI, BL, BH, BL, BH);
			break;
		case 0xE0:
			//add sp,ax
			addreg16s(SP, AX);
			break;
		case 0xE1:
			//add sp,cx
			addreg16s(SP, CX);
			break;
		case 0xE2:
			//add sp,dx
			addreg16s(SP, DX);
			break;
		case 0xE3:
			//add sp,bx
			addreg16s(SP, BX);
			break;
		case 0xE4:
			//add sp,sp
			addreg16s(SP, SP);
			break;
		case 0xE5:
			//add sp,bp
			addreg16s(SP, BP);
			break;
		case 0xE6:
			//add sp,si
			addreg16s(SP, SI);
			break;
		case 0xE7:
			//add sp,di
			addreg16s(SP, DI);
			break;
		case 0xE8:
			//add bp,ax
			addreg16s(BP, AX);
			break;
		case 0xE9:
			//add bp,cx
			addreg16s(BP, CX);
			break;
		case 0xEA:
			//add bp,dx
			addreg16s(BP, DX);
			break;
		case 0xEB:
			//add bp,bx
			addreg16s(BP, BX);
			break;
		case 0xEC:
			//add bp,sp
			addreg16s(BP, SP);
			break;
		case 0xED:
			//add bp,bp
			addreg16s(BP, BP);
			break;
		case 0xEE:
			//add bp,si
			addreg16s(BP, SI);
			break;
		case 0xEF:
			//add bp,di
			addreg16s(BP, DI);
			break;
		case 0xF0:
			//add si,ax
			addreg16s(SI, AX);
			break;
		case 0xF1:
			//add si,cx
			addreg16s(SI, CX);
			break;
		case 0xF2:
			//add si,dx
			addreg16s(SI, DX);
			break;
		case 0xF3:
			//add si,bx
			addreg16s(SI, BX);
			break;
		case 0xF4:
			//add si,sp
			addreg16s(SI, SP);
			break;
		case 0xF5:
			//add si,bp
			addreg16s(SI, BP);
			break;
		case 0xF6:
			//add si,si
			addreg16s(SI, SI);
			break;
		case 0xF7:
			//add si,di
			addreg16s(SI, DI);
			break;
		case 0xF8:
			//add di,ax
			addreg16s(DI, AX);
			break;
		case 0xF9:
			//add di,cx
			addreg16s(DI, CX);
			break;
		case 0xFA:
			//add di,dx
			addreg16s(DI, DX);
			break;
		case 0xFB:
			//add di,bx
			addreg16s(DI, BX);
			break;
		case 0xFC:
			//add di,sp
			addreg16s(DI, SP);
			break;
		case 0xFD:
			//add di,bp
			addreg16s(DI, BP);
			break;
		case 0xFE:
			//add di,si
			addreg16s(DI, SI);
			break;
		case 0xFF:
			//add di,di
			addreg16s(DI, DI);
			break;
		}
		break;
	case 0x04:
		//add al,imm8
		opcode = code[IP++];
		if (AL > 0xFF - opcode) {
			flags = flags | (1 << 6);
		}
		AL += opcode;
		if(!AL) flags = flags | (1 << 5);
		break;
	case 0x05:
		//add AX,imm16
		opcode = code[IP++];
		if (AX > 0xFFFF - opcode) {
			flags = flags | (1 << 6);
		}
		AL += opcode;
		opcode = code[IP++];
		AH += opcode; 
		AX = combine(AL, AH);
		break;
	case 0x81:
		//add reg16,imm16
		opcode = code[IP++];
		switch (opcode) {
		case 0xC1:
			//add cx,imm16
			opcode = code[IP++];
			CL = opcode;
			opcode = code[IP++];
			CH = opcode;
			if (CX > 0xFFFF - combine(CL, CH)) {
				flags = flags | (1 << 6);
			}
			CX += combine(CL, CH);
			break;
		case 0xC2:
			//add dx,imm16
			opcode = code[IP++];
			DL = opcode;
			opcode = code[IP++];
			DH = opcode;
			if (DX > 0xFFFF - combine(DL, DH)) {
				flags = flags | (1 << 6);
			}
			DX += combine(DL, DH);
			break;
		case 0xC3:
			//add bx,imm16
			opcode = code[IP++];
			BL = opcode;
			opcode = code[IP++];
			BH = opcode;
			if (BX > 0xFFFF - combine(BL,BH)) {
				flags = flags | (1 << 6);
			}
			BX += combine(BL,BH);
			break;
		case 0xC4:
			//add sp,imm16
			opcode = code[IP++];
			if (SP > 0xFFFF - combine(opcode, code[IP++])) {
				flags = flags | (1 << 6);
			}
			SP += combine(opcode, code[IP--]);
			break;
		case 0xC5:
			//add bp,imm16
			opcode = code[IP++];
			if (BP > 0xFFFF - combine(opcode, code[IP++])) {
				flags = flags | (1 << 6);
			}
			BP += combine(opcode, code[IP--]);
			break;
		case 0xC6:
			//add si,imm16
			opcode = code[IP++];
			if (SI > 0xFFFF - combine(opcode, code[IP++])) {
				flags = flags | (1 << 6);
			}
			SI += combine(opcode, code[IP--]);
			break;
		case 0xC7:
			//add di,imm16
			opcode = code[IP++];
			if (DI > 0xFFFF - combine(opcode, code[IP++])) {
				flags = flags | (1 << 6);
			}
			DI += combine(opcode, code[IP--]);
			break;
		}
		break;
	case 0xB0:
		//mov AL,imm8
		opcode = code[IP++];
		AL = opcode;
		break;
	case 0xB1:
		//mov CL,imm8
		opcode = code[IP++];
		CL = opcode;
		break;
	case 0xB2:
		//mov DL,imm8
		opcode = code[IP++];
		DL = opcode;
		break;
	case 0xB3:
		//mov BL,imm8
		opcode = code[IP++];
		BL = opcode;
		break;
	case 0xB4:
		//mov AH,imm8
		opcode = code[IP++];
		AH = opcode;
		break;
	case 0xB5:
		//mov CH,imm8
		opcode = code[IP++];
		CH = opcode;
		break;
	case 0xB6:
		//mov DH,imm8
		opcode = code[IP++];
		DH = opcode;
		break;
	case 0xB7:
		//mov BH,imm8
		opcode = code[IP++];
		BH = opcode;
		break;
	case 0xB8:
		//mov AX,imm16
		opcode = code[IP++];
		AL = opcode;
		opcode = code[IP++];
		AH = opcode;
		AX = combine(AL, AH);
		break;
	case 0xB9:
		//mov CX,imm16
		opcode = code[IP++];
		CL = opcode;
		opcode = code[IP++];
		CH = opcode;
		CX = combine(CL, CH);
		break;
	case 0xBA:
		//mov DX,imm16
		opcode = code[IP++];
		DL = opcode;
		opcode = code[IP++];
		DH = opcode;
		DX = combine(DL, DH);
		break;
	case 0xBB:
		//mov BX,imm16
		opcode = code[IP++];
		BL = opcode;
		opcode = code[IP++];
		BH = opcode;
		BX = combine(BL, BH);
		break;
	case 0xBC:
		//mov SP,imm16
		opcode = code[IP++];
		SP = combine(opcode, code[IP++]);
		break;
	case 0xBD:
		//mov BP,imm16
		opcode = code[IP++];
		BP = combine(opcode, code[IP++]);
		break;
	case 0xBE:
		//mov SI,imm16
		opcode = code[IP++];
		SI = combine(opcode, code[IP++]);
		break;
	case 0xBF:
		//mov DI,imm16
		opcode = code[IP++];
		DI = combine(opcode, code[IP++]);
		break;
	}
}

int main(int argc, char* argv[]) {
	FILE* f;
	if (OS) {
		f = fopen("C:\\csc210\\SAMPLE.COM", "rb");
		if (!f) {
			printf("fopen could not read this file in 'rb' mode");
			return -1;
		}
	}
	else {
		if (argc < 2) {
			printf("Compile like this: g++ Emulator.cpp\n");
			printf("Pass the path to the .com file if in same directory like this: ./a.out SAMPLE2.com\n");
			return -1;
		}
		f = fopen(argv[1], "rb");
		if (!f) {
			printf("fopen could not read this file in 'rb' mode");
			return -1;
		}
	}
	fread(code, 1, MAXCODE, f);
	fclose(f);

	IP = 0;
	flags = 0x00000000;
	while (1) {
		opcode = code[IP++];
		switch (opcode) {
		case 0x0f:
			//legacy lock
			opcode = code[IP++];
			switch (opcode) {
			case 0x04:
				//shld reg16,reg16,imm8/reg32,reg32,imm8 SF,ZF,CF,PF/OF,AF ?
				//shld mem16,reg16,imm8/mem32,reg32,imm8 SF,ZF,CF,PF/OF,AF ?
				break;
			case 0x05:
				//shld reg16,reg16,CL/reg32,reg32,CL SF,ZF,CF,PF/OF,AF ?
				//shld mem16,reg16,CL/mem32,reg32,CL SF,ZF,CF,PF/OF,AF ?
				break;
			case 0x80:
				//jo rel32
				break;
			case 0x81:
				//jno rel32
				break;
			case 0x82:
				//jb rel32
				//jnae
				//jc rel32
				break;
			case 0x83:
				//jae rel32
				//jnb
				//jnc rel32
				break;
			case 0x84:
				//je rel32
				//jz
				break;
			case 0x85:
				//jne rel32
				//knz
				break;
			case 0x86:
				//jbe rel32
				//jna
				break;
			case 0x87:
				//ja rel32
				//jnbe
				break;
			case 0x88:
				//js rel32
				break;
			case 0x89:
				//jns rel32
				break;
			case 0x8A:
				//jp rel32
				//jpe
				break;
			case 0x8B:
				//jnp rel32
				//jpo
				break;
			case 0x8C:
				//jl rel32
				//jnge
				break;
			case 0x8D:
				//jge rel32
				//jnl
				break;
			case 0x8E:
				//jle rel32
				//jng
				break;
			case 0x8F:
				//jg rel32
				//jnle
				break;
			case 0xA0:
				//push FS
				break;
			case 0xA1:
				//pop FS
				break;
			case 0xA8:
				//push GS
				break;
			case 0xA9:
				//pop GS
				break;
			case 0xAC:
				//shrd reg16, reg16, imm8 / reg32, reg32, imm8 SF,ZF,CF,PF/OF,AF ?
				//shrd mem16, reg16, imm8 / mem32, reg32, imm8 SF,ZF,CF,PF/OF,AF ?
				break;
			case 0xAD:
				//shrd reg16, reg16, CL / reg32, reg32, CL SF,ZF,CF,PF/OF,AF ?
				//shrd mem16, reg16, CL / mem32, reg32, CL SF,ZF,CF,PF/OF,AF ?
				break;
			case 0xAF:
				//imul reg16, reg16 / reg32, reg32 OF,CF/SF,ZF,PF,AF,?
				//imul reg16, mem16 / reg32, mem32 OF,CF/SF,ZF,PF,AF,?
				break;
			case 0xB6:
				//movzx reg16, reg8 / reg32, re8
				//movzx reg16, mem8 / reg32, mem8
				break;
			case 0xB7:
				//movzx reg32, reg16
				//movzx reg32, mem16
				break;
			case 0xBE:
				//movsx reg16, re8 / reg32, reg8
				//movsx reg16, mem8 / reg32, mem8
				break;
			case 0xBF:
				//movsx reg32, reg16
				//movsx reg32, mem16
				break;
			}
			break;
		case 0xf2:
			//repne/repnz
			break;
		case 0xf3:
			//repe/repz
			break;
		case 0xcd:
			opcode = code[IP++];
			printf("\nRead byte 0xCD followed by terminator byte: %02X\nexiting . . .\n", opcode);
			if (opcode == 0x20) return 0;
		default:
			cop(opcode);
			break;
		}
		dumpRegisters();
	}
	return 0;
}

void dumpRegisters() {
	printf("\n\nIP AFTER INSTRUCTION: %d %10s OPCODE: %02X\n", IP, " ", opcode);
	printf("AL=%02X \t AH=%02X \t AX=%04X \n", AL, AH, AX);
	printf("CL=%02X \t CH=%02X \t CX=%04X \n", CL, CH, CX);
	printf("DL=%02X \t DH=%02X \t DX=%04X \n", DL, DH, DX);
	printf("BL=%02X \t BH=%02X \t BX=%04X \n", BL, BH, BX);
	printf("SP=%04X \t BP=%04X \t SI=%04X \t DI=%04X \n", SP, BP, SI, DI);
	printf("FLAGS: "); printBits(sizeof(flags), &flags);
}
