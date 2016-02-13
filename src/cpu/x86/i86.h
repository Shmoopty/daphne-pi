/*
 * i86.h
 *
 * This file is part of DAPHNE, a laserdisc arcade game emulator
 *
 * DAPHNE is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * DAPHNE is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/****************************************************************************/
/*            real mode i286 emulator by Fabrice Frances                    */
/*           (initial work based on David Hedley's pcemu)                   */
/*                                                                          */
/****************************************************************************/
#ifndef __I86_H_
#define __I86_H_

#include "../mamewrap.h"

#define USE_I86	1


/* compile with V20,V30,V33 when configured (HAS_V20,...) */
//#define INCLUDE_V20

#define I86_NMI_INT_VECTOR 2

typedef enum { ES, CS, SS, DS } SREGS;
typedef enum { 
	AX,
	CX, 
	DX, 
	BX, 
	SP, 
	BP, 
	SI, 
	DI } WREGS;

#ifndef FALSE
#define FALSE 0
#define TRUE 1
#endif

#ifdef LSB_FIRST
typedef enum { AL,AH,CL,CH,DL,DH,BL,BH,SPL,SPH,BPL,BPH,SIL,SIH,DIL,DIH } BREGS;
#else
typedef enum { AH,AL,CH,CL,DH,DL,BH,BL,SPH,SPL,BPH,BPL,SIH,SIL,DIH,DIL } BREGS;
#endif

/* parameter x = result, y = source 1, z = source 2 */

#define SetTF(x)			(I.TF = (x))
#define SetIF(x)			(I.IF = (x))
#define SetDF(x)			(I.DirVal = (x) ? -1 : 1)

#define SetOFW_Add(x,y,z)	(I.OverVal = ((x) ^ (y)) & ((x) ^ (z)) & 0x8000)
#define SetOFB_Add(x,y,z)	(I.OverVal = ((x) ^ (y)) & ((x) ^ (z)) & 0x80)
#define SetOFW_Sub(x,y,z)	(I.OverVal = ((z) ^ (y)) & ((z) ^ (x)) & 0x8000)
#define SetOFB_Sub(x,y,z)	(I.OverVal = ((z) ^ (y)) & ((z) ^ (x)) & 0x80)

#define SetCFB(x)			(I.CarryVal = (x) & 0x100)
#define SetCFW(x)			(I.CarryVal = (x) & 0x10000)
#define SetAF(x,y,z)		(I.AuxVal = ((x) ^ ((y) ^ (z))) & 0x10)
#define SetSF(x)			(I.SignVal = (x))
#define SetZF(x)			(I.ZeroVal = (x))
#define SetPF(x)			(I.ParityVal = (x))

#define SetSZPF_Byte(x) 	(I.ParityVal = I.SignVal = I.ZeroVal = (INT8)(x))
#define SetSZPF_Word(x) 	(I.ParityVal = I.SignVal = I.ZeroVal = (INT16)(x))

#define ADDB(dst,src) { unsigned res=dst+src; SetCFB(res); SetOFB_Add(res,src,dst); SetAF(res,src,dst); SetSZPF_Byte(res); dst=(BYTE)res; }
#define ADDW(dst,src) { unsigned res=dst+src; SetCFW(res); SetOFW_Add(res,src,dst); SetAF(res,src,dst); SetSZPF_Word(res); dst=(WORD)res; }

#define SUBB(dst,src) { unsigned res=dst-src; SetCFB(res); SetOFB_Sub(res,src,dst); SetAF(res,src,dst); SetSZPF_Byte(res); dst=(BYTE)res; }
#define SUBW(dst,src) { unsigned res=dst-src; SetCFW(res); SetOFW_Sub(res,src,dst); SetAF(res,src,dst); SetSZPF_Word(res); dst=(WORD)res; }

#define ORB(dst,src) 		dst |= src; I.CarryVal = I.OverVal = I.AuxVal = 0; SetSZPF_Byte(dst)
#define ORW(dst,src) 		dst |= src; I.CarryVal = I.OverVal = I.AuxVal = 0; SetSZPF_Word(dst)

#define ANDB(dst,src) 		dst &= src; I.CarryVal = I.OverVal = I.AuxVal = 0; SetSZPF_Byte(dst)
#define ANDW(dst,src) 		dst &= src; I.CarryVal = I.OverVal = I.AuxVal = 0; SetSZPF_Word(dst)

#define XORB(dst,src) 		dst ^= src; I.CarryVal = I.OverVal = I.AuxVal = 0; SetSZPF_Byte(dst)
#define XORW(dst,src) 		dst ^= src; I.CarryVal = I.OverVal = I.AuxVal = 0; SetSZPF_Word(dst)

#define CF					(I.CarryVal != 0)
#define SF					(I.SignVal < 0)
#define ZF					(I.ZeroVal == 0)
#define PF					parity_table[I.ParityVal]
#define I86_AF					(I.AuxVal != 0)
#define OF					(I.OverVal != 0)
#define DF					(I.DirVal < 0)

/************************************************************************/

#define SegBase(Seg) 			(I.sregs[Seg] << 4)

#define DefaultBase(Seg) 		((seg_prefix && (Seg == DS || Seg == SS)) ? prefix_base : I.base[Seg])

#define GetMemB(Seg,Off)		(cpu_readmem20((DefaultBase(Seg) + (Off)) & AMASK))
#define GetMemW(Seg,Off)		((WORD)GetMemB(Seg, Off) + (WORD)(GetMemB(Seg, (Off) + 1) << 8))
#define PutMemB(Seg,Off,x)		cpu_writemem20((DefaultBase(Seg) + (Off)) & AMASK, (x))
#define PutMemW(Seg,Off,x)		{ PutMemB(Seg, Off, (x) & 0xff); PutMemB(Seg, (Off) + 1, ((x) >> 8) & 0xff); }

#define PEEKBYTE(ea) 			(cpu_readmem20((ea) & AMASK))
#define ReadByte(ea) 			(cpu_readmem20((ea) & AMASK))
#define ReadWord(ea)			(cpu_readmem20((ea) & AMASK) + (cpu_readmem20(((ea) + 1) & AMASK) << 8))
#define WriteByte(ea,val)		cpu_writemem20((ea) & AMASK, val);
#define WriteWord(ea,val)		{ cpu_writemem20((ea) & AMASK, (val) & 0xff); cpu_writemem20(((ea) + 1) & AMASK, ((val) >> 8) & 0xff); }

#define read_port(port) 		cpu_readport16(port)
#define write_port(port,val) 	cpu_writeport16(port,val)

#define FETCH					(cpu_readop_arg(I.pc++))
#define FETCHOP					(cpu_readop(I.pc++))
#define PEEKOP(addr)			(cpu_readop(addr))
#define FETCHWORD(var) 			{ var = cpu_readop_arg(I.pc); var += (cpu_readop_arg(I.pc + 1) << 8); I.pc += 2; }
#define CHANGE_PC(addr)			change_pc20(addr)
#define PUSH(val)				{ I.regs.w[SP] -= 2; WriteWord(((I.base[SS] + I.regs.w[SP]) & AMASK), val); }
#define POP(var)				{ var = ReadWord(((I.base[SS] + I.regs.w[SP]) & AMASK)); I.regs.w[SP] += 2; }

/************************************************************************/

#define CompressFlags() (WORD)(CF | (PF << 2) | (I86_AF << 4) | (ZF << 6) \
				| (SF << 7) | (I.TF << 8) | (I.IF << 9) \
				| (DF << 10) | (OF << 11))

#define ExpandFlags(f) \
{ \
	  I.CarryVal = (f) & 1; \
	  I.ParityVal = !((f) & 4); \
	  I.AuxVal = (f) & 16; \
	  I.ZeroVal = !((f) & 64); \
	  I.SignVal = ((f) & 128) ? -1 : 0; \
	  I.TF = ((f) & 256) >> 8; \
	  I.IF = ((f) & 512) >> 9; \
	  I.DirVal = ((f) & 1024) ? -1 : 1; \
	  I.OverVal = (f) & 2048; \
}
#endif

