/*
 * CS:APP Data Lab
 *
 * <Please put your name and userid here>
 *
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:

  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code
  must conform to the following style:

  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>

  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.


  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.
  4. Interprets integer expressions using the Data Lab 32-bit bit-vector
     model: results outside the signed range retain their low 32 bits.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 *
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce
 *      the correct answers.
 */


#endif
#include "bits.h"

// P1
/*
 * signMask - return a mask with only the most significant bit set (0x80000000)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int signMask(void) {
  return 1 << 31;
}

// P2
/*
 * bitXor - x^y using only ~ and &
 *   Example: bitXor(4, 5) = 1, bitXor(7, 7) = 0
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 2
 */
int bitXor(int x, int y) {
  /* x^y = (x|y) & ~(x&y) = ~(~x&~y) & ~(x&y) */
  return ~(~x & ~y) & ~(x & y);
}

// P3
/*
 * negativePart - return -x if x < 0, otherwise return 0
 *   Examples: negativePart(-10) = 10, negativePart(5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 3
 */
int negativePart(int x){
  /* mask is all ones when x < 0 (arithmetic shift), else 0 */
  int mask = x >> 31;
  return (~x + 1) & mask;
}


// P4
/*
 * copyByteWithin - copy byte src of x to byte dst, leaving all other bytes unchanged
 *   Bytes are numbered from 0 (least significant) to 3 (most significant).
 *   You can assume 0 <= src <= 3 and 0 <= dst <= 3.
 *   Example: copyByteWithin(0x11223344, 0, 2) = 0x11443344
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int copyByteWithin(int x, int src, int dst) {
  int byte = (x >> (src << 3)) & 0xFF;
  int mask = 0xFF << (dst << 3);
  return (x & ~mask) | (byte << (dst << 3));
}

// P5
/*
 * logicalShift - shift x to the right by n bits, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int logicalShift(int x, int n) {
  /* arithmetic shift, then clear the n sign-extension bits on the left */
  int mask = ~(((1 << 31) >> n) << 1);
  return (x >> n) & mask;
}

// P6
/*
 * swapNibblePairs - swap the low and high 4 bits within each byte of x
 *   Examples: swapNibblePairs(0xAB) = 0xBA
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 18
 *   Rating: 4
 */
int swapNibblePairs(int x) {
  int m = (0x0F << 8) | 0x0F;
  m = m | (m << 16); /* 0x0F0F0F0F */
  return ((x & m) << 4) | ((x >> 4) & m);
}

// P7
/*
 * secondLowestZeroBit - return a mask that marks the position of the second least significant 0 bit
 *   Examples: secondLowestZeroBit(0xFFFFFFFA) = 0x4, secondLowestZeroBit(0x7FFFFFFF) = 0
 *             secondLowestZeroBit(-1) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 4
 */
int secondLowestZeroBit(int x) {
  /* lowest zero bit of x is the lowest set bit of ~x: ~x & (x+1) */
  int low = ~x & (x + 1);
  /* set that bit to 1, then the next lowest zero bit is found the same way */
  int y = x | low;
  return ~y & (y + 1);
}

// P8
/*
 * oddParity - return the odd parity bit of x, that is,
 *      when the number of 1s in the binary representation of x is even, then the return 1, otherwise return 0.
 *   Examples: oddParity(5) = 1, oddParity(7) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 56
 *   Rating: 5
 */
int oddParity(int x) {
  /* fold all bits into bit 0 by xor */
  int t = x ^ (x >> 16);
  t = t ^ (t >> 8);
  t = t ^ (t >> 4);
  t = t ^ (t >> 2);
  t = t ^ (t >> 1);
  /* bit 0 is 1 when the number of 1s is odd; flip to answer "even" */
  return (t & 1) ^ 1;
}

// P9
/*
 * rotateRightBits - rotate x to right by n bits
 *   you can assume n >= 0
 *   Examples: rotateRightBits(0x12345678, 8) = 0x78123456
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 5
 */
int rotateRightBits(int x, int n) {
  /* take n modulo 32 so shift amounts stay in 0..31 */
  int m = n & 31;
  /* the right part must be a logical shift: clear the m sign bits */
  int r = (x >> m) & ~(((1 << 31) >> m) << 1);
  /* left part shifts by (32-m)%32, computed as (-m) & 31 */
  return r | (x << ((~m + 1) & 31));
}

// P10
/*
 * roundEvenPow2 - round nonnegative x to the nearest multiple of 2^n.
 *   If x is exactly halfway between two multiples, choose the multiple whose
 *   quotient by 2^n is even.
 *   You can assume 0 <= x <= 0x3fffffff and 1 <= n <= 16.
 *   Examples: roundEvenPow2(10, 2) = 8, roundEvenPow2(14, 2) = 16
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 5
 */
int roundEvenPow2(int x, int n) {
  /* adding half-1 plus the parity of the quotient makes a carry appear
     exactly when the remainder is > half, or == half and quotient is odd */
  int q = x >> n;
  int half = 1 << (n + ~0);
  int t = x + half + (q & 1) + ~0;
  return (t >> n) << n;
}

// P11
/*
 * midpointTowardFirst - return the exact mathematical midpoint (x+y)/2
 *   without overflow. If the exact midpoint lies halfway between two
 *   integers, choose the adjacent integer that is closer to the first
 *   argument x.
 *   Examples: midpointTowardFirst(4, 7) = 5,
 *             midpointTowardFirst(7, 4) = 6
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 32
 *   Rating: 5
 */
int midpointTowardFirst(int x, int y) {
  /* x+y = 2*(x&y) + (x^y), so floor((x+y)/2) = (x&y) + ((x^y)>>1) */
  int xy = x ^ y;
  int base = (x & y) + (xy >> 1);
  /* when x+y is odd the midpoint is *.5: bump up iff x > y */
  int sx = x >> 31;
  int sy = y >> 31;
  int d = x + ~y + 1;
  int same = ~(sx ^ sy);
  /* overflow-safe x > y */
  int gt = (same & !(d >> 31)) | ((sx ^ sy) & !sx);
  int odd = xy & 1;
  return base + (odd & gt);
}


// P12
/*
 * isBetweenEitherOrder - return 1 when x lies in the inclusive interval whose
 *   endpoints are a and b. The endpoints may be given in either order.
 *   Example: isBetweenEitherOrder(5, 8, 3) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 48
 *   Rating: 7
 */
int isBetweenEitherOrder(int x, int a, int b) {
  /* overflow-safe signed comparisons: if signs differ, the sign bit of the
     operand decides; otherwise the difference is exact */
  int sx = x >> 31;
  int sa = a >> 31;
  int sb = b >> 31;
  int da = x + ~a + 1;
  int db = x + ~b + 1;
  int sda = da >> 31;
  int sdb = db >> 31;
  int xsa = sx ^ sa;
  int xsb = sx ^ sb;
  int lta = (xsa & sx) | (~xsa & sda); /* x < a */
  int ltb = (xsb & sx) | (~xsb & sdb); /* x < b */
  int gta = !lta & !!da;               /* x > a */
  int gtb = !ltb & !!db;               /* x > b */
  /* x >= min(a,b)  and  x <= max(a,b) */
  return (!lta | !ltb) & (!gta | !gtb);
}

// P13
/*
 * mul5Sat - return x*5, and if x*5 overflow, change the result to
 * INT_MAX(0x7fffffff) or INT_MIN(0x80000000) correspondingly
 *   Examples: mul5Sat(1) = 0x5, mul5Sat(0x40000000) = 0x7fffffff
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 30
 *   Rating: 7
 */
int mul5Sat(int x) {
  int t = (x << 2) + x;
  /* P = ceil(2^31/5) = 0x1999999A: 5x overflows iff |x| >= P */
  int P = (0x19 << 24) | (0x99 << 16) | (0x99 << 8) | 0x9A;
  /* |x| = (x + (x>>31)) ^ (x>>31), exact for the whole int range */
  int mx = (x + (x >> 31)) ^ (x >> 31);
  int over = !((mx + ~P + 1) >> 31);
  /* saturation value: INT_MAX for x >= 0, INT_MIN for x < 0 */
  int s = ~(1 << 31) + ((x >> 31) & 1);
  /* over == 1: keep s; over == 0: keep t */
  return ((~over + 1) & s) | ((over + ~0) & t);
}

// P14
/*
 * classifyAdd3 - classify the exact mathematical sum x+y+z.
 *   Return 1 if the sum is greater than INT_MAX, -1 if it is less than
 *   INT_MIN, and 0 otherwise. You may not use a wider integer type.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 52
 *   Rating: 7
 */
int classifyAdd3(int x, int y, int z) {
  /* exact S = s2 + (o1 + o2) * 2^32, where o1, o2 are the two add overflows */
  int s1 = x + y;
  int s2 = s1 + z;
  int ss1 = s1 >> 31;
  int o1p = !(x >> 31) & !(y >> 31) & ss1;
  int o1n = (x >> 31) & (y >> 31) & !ss1;
  int o1 = o1p + ~o1n + 1;
  int ss2 = s2 >> 31;
  int o2p = !ss1 & !(z >> 31) & ss2;
  int o2n = ss1 & (z >> 31) & !ss2;
  int o2 = o2p + ~o2n + 1;
  int tot = o1 + o2;
  return (tot >> 31) | !!tot;
}

// P15
/*
 * floatScaleThreeHalves - Return bit-level equivalent of expression f*3/2 for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   Use round-to-nearest-even. Preserve the sign of both +0 and -0.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 60
 *   Rating: 7
 */
unsigned floatScaleThreeHalves(unsigned uf) {
  unsigned s = uf & 0x80000000u;
  unsigned e = (uf >> 23) & 0xFF;
  unsigned f = uf & 0x7FFFFF;
  if (e == 0xFF) return uf; /* NaN and infinity stay unchanged */
  if (e == 0) {
    /* denormal or zero: value = f * 2^-149, result = round(3f/2) * 2^-149 */
    unsigned m = (f << 1) + f;
    unsigned g = (m >> 1) + ((m & 1) & ((m >> 1) & 1));
    /* if g reaches 2^23 the result becomes the smallest normal number */
    if (g >= 0x800000) return s | 0x00800000u | (g - 0x800000u);
    return s | g;
  }
  /* normal: value = (2^23+f) * 2^(e-150), result = round(3*(2^23+f)/2) * 2^(e-150) */
  unsigned m = ((0x800000u | f) << 1) + (0x800000u | f);
  unsigned g = (m >> 1) + ((m & 1) & ((m >> 1) & 1));
  if (g >= 0x1000000u) {
    /* normalize: value = (g/2) * 2^(e-149); if g is odd, g/2 lies exactly
       halfway and must be rounded to even as well */
    unsigned e2 = e + 1;
    if (e2 == 0xFF) return s | 0x7F800000u; /* overflow to infinity */
    g = (g >> 1) + ((g & 1u) & ((g >> 1) & 1u));
    return s | (e2 << 23) | (g - 0x800000u);
  }
  return s | (e << 23) | (g - 0x800000u);
}

// P16
/*
 * floatRoundEven - round the floating-point value represented by uf to the
 *   nearest integer, with halfway cases rounded to the even integer. Return
 *   the bit-level representation of that integer as a single-precision float.
 *   If rounding produces zero, preserve the input sign; thus a negative
 *   value that rounds to zero returns -0. When uf is NaN or infinity,
 *   return uf unchanged.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 65
 *   Rating: 10
 */
unsigned floatRoundEven(unsigned uf) {
  unsigned s = uf & 0x80000000u;
  unsigned e = (uf >> 23) & 0xFF;
  unsigned f = uf & 0x7FFFFF;
  if (e >= 0xFF) return uf;   /* NaN or infinity */
  if (e >= 150) return uf;    /* |value| >= 2^23: already an integer */
  if (e < 127) {
    /* |value| < 1: only (0.5, 1) rounds to 1, everything else to 0 */
    if (e == 126 && f != 0) return s | 0x3F800000u;
    return s;
  }
  /* 127 <= e <= 149: value = m * 2^(-shift); round m's low shift bits to
     nearest even, then put the rounded significand back in place */
  int shift = 150 - e;
  unsigned m = 0x800000u | f;
  unsigned r = m >> shift;
  unsigned rem = m & ((1u << shift) - 1u);
  unsigned half = 1u << (shift - 1);
  unsigned up = (rem > half) || (rem == half && (r & 1u));
  unsigned sig = (r << shift) + (up << shift);
  unsigned e2 = e;
  if (sig >= 0x1000000u) { sig = sig >> 1; e2 = e2 + 1; }
  return s | (e2 << 23) | (sig - 0x800000u);
}

// P17
/*
 * float_i2f - Return bit-level equivalent of expression (float) x.
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 40
 *   Rating: 10
 */
unsigned float_i2f(int x) {
  unsigned s;
  int m;
  int e;
  int t;
  int rest;
  int shift;
  int r;
  int rem;
  int half;
  int up;
  unsigned frac;
  if (x == 0) return 0;
  if (x == (1 << 31)) return 0xCF000000u; /* INT_MIN = -2^31 = -1.0 * 2^31 */
  s = x & (1 << 31);
  if (x < 0) m = -x; else m = x;
  /* e = floor(log2(m)), m = 2^e + rest */
  e = 0;
  t = m;
  while (t > 1) { t = t >> 1; e = e + 1; }
  rest = m - (1 << e);
  if (e <= 23) {
    /* exact: frac = rest * 2^(23-e) */
    frac = rest << (23 - e);
  } else {
    /* round rest to 23 bits, round-to-nearest-even */
    shift = e - 23;
    r = rest >> shift;
    rem = rest & ((1 << shift) - 1);
    half = 1 << (shift - 1);
    up = (rem > half) || (rem == half && (r & 1));
    frac = r + up;
    if (frac >= 0x800000u) { frac = 0; e = e + 1; }
  }
  return s | ((e + 127) << 23) | frac;
}



// P18
/*
 * bitCount - return count of number of 1's in the binary representation of x
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 10
 */
int bitCount(int x) {
  /* masks built by replication */
  int m3 = (0x0F << 8) | 0x0F;
  m3 = m3 | (m3 << 16);      /* 0x0F0F0F0F */
  int m2 = m3 ^ (m3 << 2);   /* 0x33333333 */
  int m1 = m2 ^ (m2 << 1);   /* 0x55555555 */
  x = x + ~((x >> 1) & m1) + 1;          /* sum of bits in each pair */
  x = (x & m2) + ((x >> 2) & m2);        /* sum of pairs in each nibble */
  x = (x + (x >> 4)) & m3;               /* sum of nibbles in each byte */
  x = x + (x >> 8);                      /* sum of bytes in each half */
  x = x + (x >> 16);                     /* total in low byte */
  return x & 0x3F;
}

// P19
/*
 * bitReverse - Reverse bits in an 32-bit integer
 *   Examples: bitReverse(0x80000004) = 0x20000001
 *             bitReverse(0x7FFFFFFF) = 0xFFFFFFFE
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 34
 *   Rating: 10
 */
int bitReverse(int x)
{
  int m3 = (0x0F << 8) | 0x0F;
  m3 = m3 | (m3 << 16);      /* 0x0F0F0F0F */
  int m2 = m3 ^ (m3 << 2);   /* 0x33333333 */
  int m1 = m2 ^ (m2 << 1);   /* 0x55555555 */
  int m4 = 0xFF << 8;        /* 0x0000FF00 */
  /* swap adjacent bits, then pairs, then nibbles */
  x = ((x >> 1) & m1) | ((x & m1) << 1);
  x = ((x >> 2) & m2) | ((x & m2) << 2);
  x = ((x >> 4) & m3) | ((x & m3) << 4);
  /* reverse the byte order: b0b1b2b3 -> b3b2b1b0 */
  return (x << 24) | ((x >> 8) & m4) | ((x & m4) << 8) | ((x >> 24) & 0xFF);
}
