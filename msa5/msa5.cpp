// msa5.cpp : Defines the exported functions for the DLL application.
//

#include <stdafx.h>

#include "msa5.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef const u8 cu8;
typedef const u16 cu16;
typedef const u32 cu32;
typedef const u64 cu64;

typedef char s8;
typedef short s16;
typedef int s32;
typedef long long s64;
typedef const s8 cs8;
typedef const s16 cs16;
typedef const s32 cs32;
typedef const s64 cs64;

#include "c:\libsf\utils\sha1\sha1.h"

struct SMsa5x
{
	cs8*		name;

	union
	{
		u32			values[5];
		struct
		{
			u32		x;
			u32		y;
			u32		t;
			u32		u;
			u32		v;
		};
	};
 
	union
	{
		cs8*		shuffles[5];
		struct
		{
			cs8*	shuffle1;
			cs8*	shuffle2;
			cs8*	shuffle3;
			cs8*	shuffle4;
			cs8*	shuffle5;
		};
	};
};

SMsa5x algos[] =
{
	{	"MSA50", 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, "d40u75shPl3cmOn2TjBR9FvQ8aK61gie", "7h03p8atsmQCE2F9kV4li1D5ugbojNr6", "K6UhmF0vDEtagpSlR2ob94j3i158QNC7", "Ch4t725or163nbJe9SqLKmvF0iapDuG8", "TP9ISHcN8vK0FuMBE2Ql415jG3RDOa76" },
	{	"MSA51", 0x11011101, 0x10101010, 0x01010101, 0x11011011, 0x01101101, "oukr15ie632478LmcV0nbP9ShfaqTgjD", "T0Pufs1D2R3gHVMk4el5OqJ789n6abIC", "r8IuFcHqo56p1asmEg37J20kvbDTN9L4", "TfidP0e9Lk3AroN68gjc7QB5V124UsMh", "8peuQndhf2c9lgSt6O7br1M4JVK53a0i" },
	{	"MSA52", 0x22022202, 0x20202020, 0x02020202, 0x22022022, 0x02202202, "n1u856ob3IJsekd02f7Ma4vtGp9hQcrl", "iaOdKnj165muRsQ0T9gpVB438Ec2F7lh", "NvIkq5Tr3G842p1mLfcajb0o9H6U7DES", "D3jfqv08O71iS2l4NBK9UAcgReP5MH6t", "8loc4Tkv9p0UG6Ab17dSrNIH32jEm5Qf" },
	{	"MSA53", 0x33033303, 0x30303030, 0x03030303, 0x33033033, 0x03303303, "osclaq6jE9Bd7R31gv8k0hfIt4npUm52", "LqDfju5i9pgm7b4ethArO68k20Vsc13N", "da7r5q2n89gLj1mbSefiP4Th06U3VOKC", "Mec0vaS7jdBf93GUIrNk5qp8hO14t6L2", "5NdVLCF8qG39HOBum02TES7J14ikA6rp" },
	{	"MSA54", 0x44044404, 0x40404040, 0x04040404, 0x44044044, 0x04404404, "v5arl1QDGmie9chjt2UObS83K76pF0n4", "2LOvuCFsgT9806rMidq47KBj35eh1pNa", "ugB192PlD8cm3fRs0Netqok64iH5VA7J", "OvchLnq7kb9Ij86apt2e03G4U1Rm5fDs", "i29308t4N1CDSLH7QAPkjBUvMG5EFR6o" },
	{	"MSA55", 0x55055505, 0x50505050, 0x05050505, 0x55055055, 0x05505505, "1Gb2uMAi3cqpKn740DO9l8JVst5rF6He", "ciS9ru7F8Md20pj5hngAklEo6B4V31tq", "UDgkE3T827oM5PfcV9lh1iQSarN6BJ40", "2uBdfqjgIpN19Cao0vT347Ls8mekR6H5", "61T7SIL8Hu2FqC50A9RP3D4gBEnVojkM" },
	{	"MSA56", 0x66066606, 0x60606060, 0x06060606, 0x66066066, 0x06606606, "t3PjVmg80an1F7bqC6S52hULieRoD49k", "SqGK7jc9lbF8MHe203OI1UN5PvRTa46d", "pjkbdl17o2V6m09CAtHFrSu5g83EQN4I", "Loe1kn2FmjC75943SqtG8iAup6DV0BRh", "QElOF32jRG0AI9TDmC7P81kuHbN5v4S6" },
	{	"MSA57", 0x77077707, 0x70707070, 0x07070707, 0x77077077, 0x07707707, "sdkhba6uE8CFM3tVrG5q27n4jpol91i0", "f143c9LH60s7NokAmegbqi2upTrJV85D", "ClsvAfIgoD3t95u08E6nkh7p41RBM2JQ", "IHfsoL42k7U8g0r1NAD5V6JT39pQEBMC", "DFEsA6O9Qu120L7g54T8Ip3BMrVnCjhk" },
	{	"MSA58", 0x88088808, 0x80808080, 0x08080808, 0x88088088, 0x08808808, "9813ivosJtmcanH02rELd6u7BQ5gK4fp", "7gDr9A2TmVl6J0FqPo5b4I3u1schen8k", "0e78HMN6aq3pulr5Ks1gcf4bi9JVD2OT", "7lgfu2DjPNR9145ISCOqBt3ha06mvE8k", "iUE50qd17cH26oMlSgRV43TFJB9PK8nA" },
};

void iMsa5xx			(SMsa5x* output, SMsa5x* seed, u8* data, s32 dataLength, int continuation);
void iMsa5xx_swizzle	(s32 lnBit, u8 bitOp, u32* value, u8 bitsIn);




// This is an example of an exported function.
extern "C"
MSA5_API u32 msa5_compute(s8* data, s32 dataLength, u32 algorithm, u32* x, u32* y, u32* t, u32* u, u32* v, s8* x8, s8* y8, s8* t8, s8* _u8, s8* v8, int continuation)
{
	SMsa5x		computed = { };

	computed.x = *x;
	computed.y = *y;
	computed.t = *t;
	computed.u = *u;
	computed.v = *v;

	iMsa5xx(&computed, &algos[algorithm % 9], (u8*)data, dataLength, continuation);

	*x = computed.x;
	*y = computed.y;
	*t = computed.t;
	*u = computed.u;
	*v = computed.v;

	sprintf( x8, "%08x", computed.x);
	sprintf( y8, "%08x", computed.y);
	sprintf( t8, "%08x", computed.t);
	sprintf(_u8, "%08x", computed.u);
	sprintf( v8, "%08x", computed.v);

	return computed.x ^ computed.y ^ computed.t ^ computed.u ^ computed.v;
}

extern "C"
MSA5_API u32 msa5_sha1(u8* data, u32 dataLength, u32* x, u32* y, u32* t, u32* u, u32* v, s8* x8, s8* y8, s8* t8, s8* _u8, s8* v8)
{
	SMsa5x		computed = { };

	union
	{
		u32		sha1_dwords[5];
		u8		sha1[20];
	};

	sha1_dwords[0] = *x;
	sha1_dwords[1] = *y;
	sha1_dwords[2] = *t;
	sha1_dwords[3] = *u;
	sha1_dwords[4] = *v;

	sha1_computeSha1(data, dataLength, sha1);

	*x = sha1_dwords[0];
	*y = sha1_dwords[1];
	*t = sha1_dwords[2];
	*u = sha1_dwords[3];
	*v = sha1_dwords[4];

	sprintf( x8, "%08x", *x);
	sprintf( y8, "%08x", *y);
	sprintf( t8, "%08x", *t);
	sprintf(_u8, "%08x", *u);
	sprintf( v8, "%08x", *v);

	return computed.x ^ computed.y ^ computed.t ^ computed.u ^ computed.v;
}

void iMsa5xx(SMsa5x* output, SMsa5x* seed, u8* data, s32 dataLength, int continuation)
{
	u8		c, thisChar;
	s32		lnI, lnOp, lnBit;
	u32		xt, yt, tt, ut, vt, xx;

	if (!continuation)
	{
		output->x = seed->x;
		output->y = seed->y;
		output->t = seed->t;
		output->u = seed->u;
		output->v = seed->v;
	}

	for (lnI = 0; lnI < dataLength; ++lnI)
	{
		thisChar = data[lnI];

		for (lnOp = 0; lnOp < sizeof(seed->values) / sizeof(seed->values[0]); ++lnOp)
		{
			for (lnBit = 0; lnBit < 32; ++lnBit)
			{
				c = seed->shuffles[lnOp][lnBit];
				iMsa5xx_swizzle(lnBit, c, &output->values[lnOp], thisChar);
			}
		}

		// Inter-word mixing
		for (lnOp = 0; lnOp < 5; ++lnOp)
		{
			output->values[lnOp] += output->values[(lnOp + 1) % 5];
		}

		// Bit rotations
		for (lnOp = 0; lnOp < 5; ++lnOp)
		{
			s32 rot = (lnOp * 7 + 3) % 32;
			u32 val = output->values[lnOp];
			output->values[lnOp] = (val << rot) | (val >> (32 - rot));
		}

		// Add adjacent values together
		xt = output->x + output->y + ((u32)thisChar);
		yt = output->y + output->t + ((u32)thisChar << 6);
		tt = output->t + output->u + ((u32)thisChar << 12);
		ut = output->u + output->v + ((u32)thisChar << 18);
		vt = output->v + output->x + ((u32)thisChar << 24);

		// Non-linear mixing with addition and bitwise
		xx = xt + output->x;
		xx += (xx << 3);
		xx ^= (xx >> 11);
		xx += (xx << 15);
		xt = xx;

		xx = yt + output->y;
		xx += (xx << 3);
		xx ^= (xx >> 11);
		xx += (xx << 15);
		yt = xx;

		xx = tt + output->t;
		xx += (xx << 3);
		xx ^= (xx >> 11);
		xx += (xx << 15);
		tt = xx;

		xx = ut + output->u;
		xx += (xx << 3);
		xx ^= (xx >> 11);
		xx += (xx << 15);
		ut = xx;

		xx = vt + output->v;
		xx += (xx << 3);
		xx ^= (xx >> 11);
		xx += (xx << 15);
		vt = xx;

		// Swizzle the values
		output->x = vt;		// V -> X
		output->y = ut;		// U -> Y
		output->t = yt;		// Y -> T
		output->u = xt;		// X -> U
		output->v = tt;		// T -> V
	}
}

void iMsa5xx_swizzle(s32 lnBit, u8 bitOp, u32* value, u8 bitsIn)
{
	u32		lnBitNowMask, lnXor1, lnXor2, lnBitInMask, lnBitInValue;

	lnBitNowMask  = (1 << lnBit);

	if (bitOp >= '0' && bitOp <= '9')
	{
		lnBitInMask  = (1 << (bitOp - '0'));
		lnBitInValue = (*value & lnBitInMask);

	} else if (bitOp >= 'a' && bitOp <= 'v') {
		lnBitInMask  = (1 << (bitOp - 'a' + 10));
		lnBitInValue = (*value & lnBitInMask);

	} else if (bitOp >= 'A' && bitOp <= 'V') {
		lnBitInMask  = (1 << (bitOp - 'A' + 10));
		lnBitInValue = ((*value & lnBitInMask) ? 0 : 1);

	} else {
		// Invalid op
		return;
	}

	lnXor1 = ((((u32)~bitsIn & 0xff) & 0xf0) << 24) |  ((u32)bitsIn          << 20) | (((u32)~bitsIn & 0xff) << 12) |  ((u32)bitsIn          <<  4) | (u32)(((u32)~bitsIn & 0xff) & 0x0f);
	lnXor2 =                                          (((u32)~bitsIn & 0xff) << 24) |   ((u32)bitsIn         << 16) | (((u32)~bitsIn & 0xff) <<  8) |         (u32)bitsIn;

	// Process
	*value	&= ~lnBitNowMask;
	*value	|= ((lnBitInValue) ? lnBitNowMask : 0);
	*value	^= lnXor1;
	*value	^= (lnXor1 | ~lnXor2);
}


/*
void iMsa5xx(SMsa5x* output, SMsa5x* seed, u8* data, s32 dataLength, int continuation)
{
	u8		c, thisChar;
	s32		lnI, lnOp, lnBit;
	u32		xt, yt, tt, ut, vt;

	if (!continuation)
	{
		output->x = seed->x;
		output->y = seed->y;
		output->t = seed->t;
		output->u = seed->u;
		output->v = seed->v;
	}

	for (lnI = 0; lnI < dataLength; ++lnI)
	{
		thisChar = data[lnI];

		for (lnOp = 0; lnOp < sizeof(seed->values) / sizeof(seed->values[0]); ++lnOp)
		{
			for (lnBit = 0; lnBit < 32; ++lnBit)
			{
				c = seed->shuffles[lnOp][lnBit];
				iMsa5xx_swizzle(lnBit, c, &output->values[lnOp], thisChar);
			}
		}

		// Add adjacent values together
		xt = output->x + output->y + ((u32)thisChar);
		yt = output->y + output->t + ((u32)thisChar << 6);
		tt = output->t + output->u + ((u32)thisChar << 12);
		ut = output->u + output->v + ((u32)thisChar << 18);
		vt = output->v + output->x + ((u32)thisChar << 24);

		// Swizzle the values
		xt = (xt + output->x) * (u32)0x9e3779b9;
		yt = (yt + output->y) * (u32)0x3779b99e;
		tt = (tt + output->t) * (u32)0x79b99e37;
		ut = (ut + output->u) * (u32)0x9b99e377;
		vt = (vt + output->v) * (u32)0xb99e3779;

		output->x = vt;		// V -> X
		output->y = ut;		// U -> Y
		output->t = yt;		// Y -> T
		output->u = xt;		// X -> U
		output->v = tt;		// T -> V
	}
}

// lnValue = the bit we're working with
// lnMask  = the mask to access the bit
void iMsa5xx_swizzle(s32 lnBit, u8 bitOp, u32* value, u8 bitsIn)
{
	u32		lnBitNowMask, lnXor1, lnXor2, lnBitInMask, lnBitInValue;

	// Get this bit of the current value
	lnBitNowMask  = (1 << lnBit);
	// Right now, lnBitValue is the flag if the lnBit is set or not

	// Based on our input character, extract out the source location to populate into this bit
	if (bitOp >= '0' && bitOp <= '9')
	{
		// We're XORing the input bit into this position
		lnBitInMask  = (1 << (bitOp - '0'));
		lnBitInValue = (*value & lnBitInMask);

	} else if (bitOp >= 'a' && bitOp <= 'v') {
		// It's a normal op
		lnBitInMask  = (1 << (bitOp - 'a' + 10));
		lnBitInValue = (*value & lnBitInMask);

	} else if (bitOp >= 'A' && bitOp <= 'V') {
		// It's an OR if lnBit is even, or XOR if lnBit is odd
		lnBitInMask  = (1 << (bitOp - 'A' + 10));
		lnBitInValue = ((*value & lnBitInMask) ? 0 : 1);

	} else {
		// Invalid op
		return;
	}

 	lnXor1 = ((((u32)~bitsIn & 0xff) & 0xf0) << 24) |  ((u32)bitsIn          << 20) | (((u32)~bitsIn & 0xff) << 12) |  ((u32)bitsIn          <<  4) | (u32)(((u32)~bitsIn & 0xff) & 0x0f);
 	lnXor2 =                                          (((u32)~bitsIn & 0xff) << 24) |   ((u32)bitsIn         << 16) | (((u32)~bitsIn & 0xff) <<  8) |         (u32)bitsIn;

	// Process
	*value	&= ~lnBitNowMask;
	*value	|= ((lnBitInValue) ? lnBitNowMask : 0);
 	*value	^= lnXor1;
 	*value	^= (lnXor1 | ~lnXor2);
}
*/

#include "c:\libsf\utils\sha1\sha1.cpp"
