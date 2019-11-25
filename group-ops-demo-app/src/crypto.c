#include "os.h"
#include "cx.h"
#include "crypto.h"
#include "poseidon.h"

#define MNT6 1
#define MNT4 0

#if MNT6
 // mnt6753 params
static const field field_modulus = {
    0x00, 0x01, 0xc4, 0xc6, 0x2d, 0x92, 0xc4, 0x11, 0x10, 0x22, 0x90, 0x22,
    0xee, 0xe2, 0xcd, 0xad, 0xb7, 0xf9, 0x97, 0x50, 0x5b, 0x8f, 0xaf, 0xed,
    0x5e, 0xb7, 0xe8, 0xf9, 0x6c, 0x97, 0xd8, 0x73, 0x07, 0xfd, 0xb9, 0x25,
    0xe8, 0xa0, 0xed, 0x8d, 0x99, 0xd1, 0x24, 0xd9, 0xa1, 0x5a, 0xf7, 0x9d,
    0xb2, 0x6c, 0x5c, 0x28, 0xc8, 0x59, 0xa9, 0x9b, 0x3e, 0xeb, 0xca, 0x94,
    0x29, 0x21, 0x26, 0x36, 0xb9, 0xdf, 0xf9, 0x76, 0x34, 0x99, 0x3a, 0xa4,
    0xd6, 0xc3, 0x81, 0xbc, 0x3f, 0x00, 0x57, 0x97, 0x4e, 0xa0, 0x99, 0x17,
    0x0f, 0xa1, 0x3a, 0x4f, 0xd9, 0x07, 0x76, 0xe2, 0x40, 0x00, 0x00, 0x01};

static const field group_coeff_a = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0b};

static const field group_coeff_b = {
    0x00, 0x00, 0x7d, 0xa2, 0x85, 0xe7, 0x08, 0x63, 0xc7, 0x9d, 0x56, 0x44,
    0x62, 0x37, 0xce, 0x2e, 0x14, 0x68, 0xd1, 0x4a, 0xe9, 0xbb, 0x64, 0xb2,
    0xbb, 0x01, 0xb1, 0x0e, 0x60, 0xa5, 0xd5, 0xdf, 0xe0, 0xa2, 0x57, 0x14,
    0xb7, 0x98, 0x59, 0x93, 0xf6, 0x2f, 0x03, 0xb2, 0x2a, 0x9a, 0x3c, 0x73,
    0x7a, 0x1a, 0x1e, 0x0f, 0xcf, 0x2c, 0x43, 0xd7, 0xbf, 0x84, 0x79, 0x57,
    0xc3, 0x4c, 0xca, 0x1e, 0x35, 0x85, 0xf9, 0xa8, 0x0a, 0x95, 0xf4, 0x01,
    0x86, 0x7c, 0x4e, 0x80, 0xf4, 0x74, 0x7f, 0xde, 0x5a, 0xba, 0x75, 0x05,
    0xba, 0x6f, 0xcf, 0x24, 0x85, 0x54, 0x0b, 0x13, 0xdf, 0xc8, 0x46, 0x8a};

// mnt6753 generator
//  .x =
//  "345842096948423570880626120012885054401707033383394411680148206454072326814
//  9235477762870414664917360605949659630933184751526227993647030875167687492714
//  052872195770088225183259051403087906158701786758441889742618916006546636728",
//  .y =
//  "274605084023319651496266002243821372545029759791683711116409247215891277253
//  7647351483823436111485517548824200743143907422382774281391189981793072811229
//  7763448010814764117701403540298764970469500339646563344680868495474127850569"

static const group group_one = {
    {0x00, 0x00, 0x25, 0x5f, 0x8e, 0x87, 0x6e, 0x83, 0x11, 0x47, 0x41, 0x2c,
     0xfb, 0x10, 0x02, 0x28, 0x4f, 0x30, 0x33, 0x80, 0x88, 0x13, 0x1c, 0x24,
     0x37, 0xe8, 0x84, 0xc4, 0x99, 0x7f, 0xd1, 0xdc, 0xb4, 0x09, 0x36, 0x7d,
     0x0c, 0x0d, 0x5f, 0xc5, 0xe8, 0x18, 0x77, 0x1b, 0x93, 0x1f, 0x1d, 0x5b,
     0xdd, 0x06, 0x9c, 0xe5, 0xe3, 0xc5, 0x7b, 0x6d, 0xf1, 0x20, 0xce, 0xe3,
     0xcd, 0x9d, 0x86, 0x7e, 0x66, 0xd1, 0x1a, 0xcb, 0xf7, 0xda, 0x60, 0x89,
     0x5b, 0x8b, 0x3d, 0x9d, 0x44, 0x2c, 0x4c, 0x41, 0x23, 0x32, 0x9a, 0x6f,
     0xef, 0xa9, 0xa1, 0xf3, 0xf7, 0xa1, 0xfb, 0xd9, 0x3a, 0x7b, 0xff, 0xb8},
    {0x00, 0x01, 0x28, 0xc0, 0x2f, 0xff, 0x6e, 0x2e, 0xb3, 0xfc, 0xa7, 0x0d,
     0xc1, 0x06, 0x3b, 0xac, 0x34, 0x55, 0x18, 0x01, 0x20, 0x2a, 0x35, 0x85,
     0xbd, 0xd6, 0xd7, 0x72, 0x2c, 0x6c, 0x07, 0xd7, 0x87, 0x3b, 0xb0, 0x2d,
     0x4c, 0x7a, 0x18, 0xed, 0x9c, 0x4b, 0xd3, 0xc7, 0xed, 0x0f, 0xfb, 0x31,
     0xc5, 0x7e, 0x61, 0x0d, 0xc7, 0xa5, 0x93, 0xcc, 0xe5, 0xa7, 0x92, 0xe9,
     0x4d, 0x00, 0x20, 0xc3, 0x35, 0xb7, 0x4d, 0x99, 0x92, 0xf5, 0xcb, 0xf4,
     0xb2, 0xcc, 0x4c, 0x42, 0xef, 0xf9, 0xa5, 0xa6, 0xc4, 0x52, 0x1d, 0xf9,
     0x85, 0x56, 0x87, 0x13, 0x9f, 0x0c, 0x51, 0x75, 0x4c, 0x0c, 0xcc, 0x49}};

static const scalar group_order = {
    0x00, 0x01, 0xc4, 0xc6, 0x2d, 0x92, 0xc4, 0x11, 0x10, 0x22, 0x90, 0x22,
    0xee, 0xe2, 0xcd, 0xad, 0xb7, 0xf9, 0x97, 0x50, 0x5b, 0x8f, 0xaf, 0xed,
    0x5e, 0xb7, 0xe8, 0xf9, 0x6c, 0x97, 0xd8, 0x73, 0x07, 0xfd, 0xb9, 0x25,
    0xe8, 0xa0, 0xed, 0x8d, 0x99, 0xd1, 0x24, 0xd9, 0xa1, 0x5a, 0xf7, 0x9d,
    0xb1, 0x17, 0xe7, 0x76, 0xf2, 0x18, 0x05, 0x9d, 0xb8, 0x0f, 0x0d, 0xa5,
    0xcb, 0x53, 0x7e, 0x38, 0x68, 0x5a, 0xcc, 0xe9, 0x76, 0x72, 0x54, 0xa4,
    0x63, 0x88, 0x10, 0x71, 0x9a, 0xc4, 0x25, 0xf0, 0xe3, 0x9d, 0x54, 0x52,
    0x2c, 0xdd, 0x11, 0x9f, 0x5e, 0x90, 0x63, 0xde, 0x24, 0x5e, 0x80, 0x01};

#endif // MNT6

#if MNT4
// mnt4753 params
static const field field_modulus = {
    0x00, 0x01, 0xc4, 0xc6, 0x2d, 0x92, 0xc4, 0x11, 0x10, 0x22, 0x90, 0x22,
    0xee, 0xe2, 0xcd, 0xad, 0xb7, 0xf9, 0x97, 0x50, 0x5b, 0x8f, 0xaf, 0xed,
    0x5e, 0xb7, 0xe8, 0xf9, 0x6c, 0x97, 0xd8, 0x73, 0x07, 0xfd, 0xb9, 0x25,
    0xe8, 0xa0, 0xed, 0x8d, 0x99, 0xd1, 0x24, 0xd9, 0xa1, 0x5a, 0xf7, 0x9d,
    0xb1, 0x17, 0xe7, 0x76, 0xf2, 0x18, 0x05, 0x9d, 0xb8, 0x0f, 0x0d, 0xa5,
    0xcb, 0x53, 0x7e, 0x38, 0x68, 0x5a, 0xcc, 0xe9, 0x76, 0x72, 0x54, 0xa4,
    0x63, 0x88, 0x10, 0x71, 0x9a, 0xc4, 0x25, 0xf0, 0xe3, 0x9d, 0x54, 0x52,
    0x2c, 0xdd, 0x11, 0x9f, 0x5e, 0x90, 0x63, 0xde, 0x24, 0x5e, 0x80, 0x01};

static const field group_coeff_a = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02};

static const field group_coeff_b = {
    0x00, 0x01, 0x37, 0x36, 0x84, 0xa8, 0xc9, 0xdc, 0xae, 0x7a, 0x01, 0x6a,
    0xc5, 0xd7, 0x74, 0x8d, 0x33, 0x13, 0xcd, 0x8e, 0x39, 0x05, 0x1c, 0x59,
    0x65, 0x60, 0x83, 0x5d, 0xf0, 0xc9, 0xe5, 0x0a, 0x5b, 0x59, 0xb8, 0x82,
    0xa9, 0x2c, 0x78, 0xdc, 0x53, 0x7e, 0x51, 0xa1, 0x67, 0x03, 0xec, 0x98,
    0x55, 0xc7, 0x7f, 0xc3, 0xd8, 0xbb, 0x21, 0xc8, 0xd6, 0x8b, 0xb8, 0xcf,
    0xb9, 0xdb, 0x4b, 0x8c, 0x8f, 0xba, 0x77, 0x31, 0x11, 0xc3, 0x6c, 0x8b,
    0x1b, 0x4e, 0x8f, 0x1e, 0xce, 0x94, 0x0e, 0xf9, 0xea, 0xad, 0x26, 0x54,
    0x58, 0xe0, 0x63, 0x72, 0x00, 0x9c, 0x9a, 0x04, 0x91, 0x67, 0x8e, 0xf4};

// mnt4753 generator
//  .x = 7790163481385331313124631546957228376128961350185262705123068027727518350362064426002432450801002268747950550964579198552865939244360469674540925037890082678099826733417900510086646711680891516503232107232083181010099241949569
//  .y = 6913648190367314284606685101150155872986263667483624713540251048208073654617802840433842931301128643140890502238233930290161632176167186761333725658542781350626799660920481723757654531036893265359076440986158843531053720994648

static const group group_one = {
  {0x00, 0x00, 0x54, 0x2f, 0x1d, 0xad, 0x45, 0x0b, 0xb7, 0x6a, 0x02, 0xd8,
   0x6d, 0xaa, 0xff, 0xba, 0xeb, 0x69, 0x99, 0x5e, 0xb9, 0xef, 0xa5, 0x54,
   0x64, 0x44, 0xd4, 0x0c, 0x82, 0xd6, 0xa2, 0x71, 0xf1, 0xa4, 0x38, 0x62,
   0x6d, 0x1e, 0xf7, 0x81, 0xd1, 0xde, 0x4f, 0xfb, 0x1f, 0x80, 0x6b, 0x31,
   0x4c, 0x5a, 0xd3, 0x46, 0x3d, 0x98, 0xa4, 0xea, 0x00, 0x9d, 0x57, 0xaa,
   0xd9, 0x71, 0x6f, 0x70, 0x88, 0x85, 0xfe, 0xff, 0x33, 0x8d, 0xd7, 0x3a,
   0x5a, 0x7e, 0xee, 0xcf, 0xbc, 0xe7, 0xcf, 0x95, 0xd3, 0xc2, 0xab, 0x23,
   0xbe, 0x1c, 0x24, 0x74, 0x0a, 0xf0, 0xfd, 0xeb, 0x3b, 0x7f, 0x19, 0x81},
  {0x00, 0x00, 0x4a, 0xb6, 0x47, 0x35, 0x26, 0xe2, 0x57, 0xb1, 0x75, 0xae,
   0x94, 0xde, 0xb9, 0xe1, 0x0a, 0xba, 0x4b, 0xa7, 0x2f, 0x7f, 0xdd, 0xcd,
   0xea, 0x19, 0xcb, 0x10, 0xb2, 0xbf, 0x61, 0xf3, 0x7a, 0xe2, 0xc4, 0x56,
   0xee, 0x55, 0x99, 0xdd, 0x7c, 0x3d, 0xfa, 0x41, 0x00, 0x28, 0x48, 0x33,
   0x11, 0x5a, 0xec, 0x5d, 0xea, 0x57, 0xef, 0x53, 0xee, 0x29, 0x15, 0x7b,
   0xdf, 0x1b, 0x74, 0x1a, 0xeb, 0xd4, 0x23, 0x03, 0x6d, 0xb8, 0xfb, 0x99,
   0x0a, 0x34, 0x24, 0x49, 0xca, 0xeb, 0x92, 0xfa, 0x6b, 0x03, 0x1e, 0xa9,
   0x9c, 0xff, 0x05, 0xe0, 0x5e, 0xc3, 0xbe, 0x2e, 0x4a, 0x05, 0x03, 0x58}};

static const scalar group_order = {
    0x00, 0x01, 0xc4, 0xc6, 0x2d, 0x92, 0xc4, 0x11, 0x10, 0x22, 0x90, 0x22,
    0xee, 0xe2, 0xcd, 0xad, 0xb7, 0xf9, 0x97, 0x50, 0x5b, 0x8f, 0xaf, 0xed,
    0x5e, 0xb7, 0xe8, 0xf9, 0x6c, 0x97, 0xd8, 0x73, 0x07, 0xfd, 0xb9, 0x25,
    0xe8, 0xa0, 0xed, 0x8d, 0x99, 0xd1, 0x24, 0xd9, 0xa1, 0x5a, 0xf7, 0x9d,
    0xb2, 0x6c, 0x5c, 0x28, 0xc8, 0x59, 0xa9, 0x9b, 0x3e, 0xeb, 0xca, 0x94,
    0x29, 0x21, 0x26, 0x36, 0xb9, 0xdf, 0xf9, 0x76, 0x34, 0x99, 0x3a, 0xa4,
    0xd6, 0xc3, 0x81, 0xbc, 0x3f, 0x00, 0x57, 0x97, 0x4e, 0xa0, 0x99, 0x17,
    0x0f, 0xa1, 0x3a, 0x4f, 0xd9, 0x07, 0x76, 0xe2, 0x40, 0x00, 0x00, 0x01};

#endif // MNT4


// common
static const field field_zero = {0};
static const scalar scalar_zero = {0};
static const group group_zero = {{0}, {0}};

void field_add(field c, const field a, const field b) {
  cx_math_addm(c, a, b, field_modulus, field_bytes);
}

void field_sub(field c, const field a, const field b) {
  cx_math_subm(c, a, b, field_modulus, field_bytes);
}

void field_mul(field c, const field a, const field b) {
  cx_math_multm(c, a, b, field_modulus, field_bytes);
}

void field_sq(field c, const field a) {
  cx_math_multm(c, a, a, field_modulus, field_bytes);
}

void field_inv(field c, const field a) {
  cx_math_invprimem(c, a, field_modulus, field_bytes);
}

void field_negate(field c, const field a) {
  cx_math_subm(c, field_modulus, a, field_modulus, field_bytes);
}

// c = a^e mod m
// cx_math_powm(result_pointer, a, e, len_e, m, len(result)  (which is also len(a) and len(m)) )
void field_pow(field c, const field a, const field e) {
  cx_math_powm(c, a, e, 1, field_modulus, field_bytes);
}

unsigned int field_eq(const field a, const field b) {
  return (os_memcmp(a, b, field_bytes) == 0);
}

void scalar_add(scalar c, const scalar a, const scalar b) {
  cx_math_addm(c, a, b, group_order, scalar_bytes);
}

void scalar_sub(scalar c, const scalar a, const scalar b) {
  cx_math_subm(c, a, b, group_order, scalar_bytes);
}

void scalar_mul(scalar c, const scalar a, const scalar b) {
  cx_math_multm(c, a, b, group_order, scalar_bytes);
}

void scalar_sq(scalar c, const scalar a) {
  cx_math_multm(c, a, a, group_order, scalar_bytes);
}

// c = a^e mod m
// cx_math_powm(result_pointer, a, e, len_e, m, len(result)  (which is also len(a) and len(m)) )
void scalar_pow(scalar c, const scalar a, const scalar e) {
  cx_math_powm(c, a, e, 1, group_order, scalar_bytes);
}

unsigned int scalar_eq(const scalar a, const scalar b) {
  return (os_memcmp(a, b, scalar_bytes) == 0);
}


unsigned int is_zero(const group *p) {
  return (os_memcmp(p->x, field_zero, field_bytes) == 0 &&
      os_memcmp(p->y, field_zero, field_bytes) == 0);
}

unsigned int is_on_curve(const group *p) {
  if (is_zero(p)) {
    return 1;
  }

  field t0, t1, t2;
  field_mul(t0, p->y, p->y);                // y^2
  field_mul(t1, p->x, p->x);                // x^2
  field_add(t2, t1, group_coeff_a);         // x^2 + a
  field_mul(t1, t2, p->x);                  // x^3 + ax
  field_add(t2, t1, group_coeff_b);         // x^3 + ax + b

  return (os_memcmp(t0, t1, field_bytes) == 0);
}

void group_double(group *r, const group *p) {

  if (is_zero(p)) {
    *r = group_zero;
    return;
  }

  field t1, t2;
  field_mul(r->y, p->x, p->x);              // xp^2
  field_add(t1, r->y, r->y);                // 2xp^2
  field_add(t2, r->y, t1);                  // 3xp^2
  field_add(r->y, t2, group_coeff_a);       // 3xp^2 + a
  field_add(t1, p->y, p->y);                // 2yp
  field_inv(t2, t1);                        // 1/2yp
  field_mul(t1, r->y, t2);                  // (3xp^2 + a)/2yp

  field_mul(r->y, t1, t1);                  // lambda^2
  field_sub(t2, r->y, p->x);                // lambda^2 - xp
  field_sub(r->x, t2, p->x);                // lambda^2 - xp - xp

  field_sub(r->y, p->x, r->x);              // xp - xr
  field_mul(t2, t1, r->y);                  // lambda(xp - xr)
  field_sub(r->y, t2, p->y);                // lambda(xp - xr) - yp
}

void group_add(group *r, const group *p, const group *q) {

  if (is_zero(p)) {
    *r = *q;
    return;
  }
  if (is_zero(q)) {
    *r = *p;
    return;
  }

  field temp;
  field_mul(temp, p->x, q->x);
  if (field_eq(temp, field_zero)) {
    // if pxqx == 0, either p = q -> p + q = 2p
    if (field_eq(p->y, q->y)) {
      group_double(r, p);
      return;
    } else {
      // or p = -q -> p + q = 0
      *r = group_zero;
      return;
    }
  }

  field t1, t2;
  field_sub(r->y, q->x, p->x);              // xq - xp
  field_sub(t1, q->y, p->y);                // yq - yp
  field_inv(t2, r->y);                      // 1 / (xq - xp)
  field_mul(r->y, t1, t2);                  // (yq - yp)/(xq - xp)

  field_mul(t1, r->y, r->y);                // lambda^2
  field_sub(t2, t1, p->x);                  // lambda^2 - xp
  field_sub(r->x, t2, q->x);                // lambda^2 - xp - xq

  field_sub(t1, p->x, r->x);                // xp - xr
  field_mul(t2, r->y, t1);                  // lambda(xp - xr)
  field_sub(r->y, t2, p->y);                // lambda(xp - xr) - yp
}


void group_scalar_mul(group *r, const scalar k, const group *p) {

  if (is_zero(p)) {
    *r = group_zero;
    return;
  }
  if (scalar_eq(k, scalar_zero)) {
    *r = group_zero;
    return;
  }

  group q = group_zero;
  // 96 bytes = 8 * 96 = 768. we want 753, 768 - 753 = 15 bits
  // which means we have an offset of 15 bits
   for (unsigned int i = scalar_offset; i < scalar_bits; i++) {
    unsigned int di = k[i/8] & (1 << (7 - (i % 8)));
    group q0;
    group_double(&q0, &q);
    q = q0;
    if (di != 0) {
      group q1;
      group_add(&q1, &q, p);
      q = q1;
    }
  }
  *r = q;
  return;
}


// ledger uses:
// - bip 39 to generate and interpret the master seed, which
//   produces the 24 words shown on the device at startup.
// - bip 32 for hd key derivation (using the child key derivation function)
// - bip 44 for hd account derivation (so e.g. btc and coda keys don't clash)

void generate_keypair(group *pub_key, scalar priv_key) {

  // unsigned char private_key_data[64];
  unsigned int bip32_path[5];

  bip32_path[0] = 44     | 0x80000000;
  bip32_path[1] = 49370  | 0x80000000;
  bip32_path[2] = 0      | 0x80000000;
  bip32_path[3] = 0;
  bip32_path[4] = 0;

  os_perso_derive_node_bip32(CX_CURVE_256K1, bip32_path,
                             sizeof(bip32_path) / sizeof(bip32_path[0]),
                             priv_key,
                             priv_key + 32); //last entry is chainvalue
  os_perso_derive_node_bip32(CX_CURVE_256K1, bip32_path,
                             sizeof(bip32_path) / sizeof(bip32_path[0]),
                             priv_key + 64,
                             NULL); //last entry is chainvalue

  group_scalar_mul(pub_key, priv_key, &group_one);
  // os_memset(priv_key, 0, sizeof(priv_key));
}

void generate_pubkey(group *pub_key, const scalar priv_key) {
  group_scalar_mul(pub_key, priv_key, &group_one);
}

inline unsigned int is_odd(const field y) {
  return (y[field_bytes - 1] & 1);
}

void poseidon_4in(scalar out, const scalar in1, const scalar in2, const scalar in3, const scalar in4) {
    state pos = {{0}, {0}, {0}};
    scalar tmp[sponge_size - 1];

    os_memcpy(tmp[0], in1, scalar_bytes);
    os_memcpy(tmp[1], in2, scalar_bytes);
    poseidon(pos, tmp);
    os_memcpy(tmp[0], in3, scalar_bytes);
    os_memcpy(tmp[1], in4, scalar_bytes);
    poseidon(pos, tmp);
    poseidon_digest(pos, out);
}

void sign(signature *sig, const group *public_key, const scalar private_key, const scalar msg) {
  group r;
  union tmp {
      scalar s;
      scalar k_prime;
  } tmp;

  poseidon_4in(tmp.k_prime, msg, public_key->x, public_key->y, private_key);  // k = hash(m || pk || sk)
  group_scalar_mul(&r, tmp.k_prime, &group_one);                              // r = k*g
  os_memcpy(sig->rx, r.x, field_bytes);
  //os_memcpy(sig->rx, tmp.k_prime, field_bytes);
  if (is_odd(r.y)) {
    field_negate(r.y, tmp.k_prime);                                           // if ry is odd, k = - k'
  } else {
    os_memcpy(r.y, tmp.k_prime, scalar_bytes);                                // if ry is even, k = k'
  }

  poseidon_4in(sig->s, msg, sig->rx, public_key->x, public_key->y);           // e = hash(xr || pk || m)
  scalar_mul(tmp.s, sig->s, private_key);                                     // e*sk
  scalar_add(sig->s, r.y, tmp.s);                                             // k + e*sk
  return;
}
