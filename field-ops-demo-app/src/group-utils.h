#ifndef CODA_GROUP_UTILS
#define CODA_GROUP_UTILS

#include "field.h"

// scalar length in uint64_t
#define scalar6753_uint64 12
// scalar length in bytes
#define scalar6753_BYTES 96
// scalar length in bits
#define scalar6753_BITS 753

// FIXME? pointer? or not? not?
typedef unsigned char const scalar6753[96];

// fmnt6753 = unsigned char const
typedef struct gmnt6753 {
  fmnt6753 X;
  fmnt6753 Y;
  fmnt6753 Z;
} gmnt6753;

#define gmnt6753_size_BYTES 288

static fmnt6753 gmnt6753_coeff_a = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0b};

static fmnt6753 gmnt6753_coeff_b = {
    0x00, 0x00, 0x7d, 0xa2, 0x85, 0xe7, 0x08, 0x63, 0xc7, 0x9d, 0x56, 0x44,
    0x62, 0x37, 0xce, 0x2e, 0x14, 0x68, 0xd1, 0x4a, 0xe9, 0xbb, 0x64, 0xb2,
    0xbb, 0x01, 0xb1, 0x0e, 0x60, 0xa5, 0xd5, 0xdf, 0xe0, 0xa2, 0x57, 0x14,
    0xb7, 0x98, 0x59, 0x93, 0xf6, 0x2f, 0x03, 0xb2, 0x2a, 0x9a, 0x3c, 0x73,
    0x7a, 0x1a, 0x1e, 0x0f, 0xcf, 0x2c, 0x43, 0xd7, 0xbf, 0x84, 0x79, 0x57,
    0xc3, 0x4c, 0xca, 0x1e, 0x35, 0x85, 0xf9, 0xa8, 0x0a, 0x95, 0xf4, 0x01,
    0x86, 0x7c, 0x4e, 0x80, 0xf4, 0x74, 0x7f, 0xde, 0x5a, 0xba, 0x75, 0x05,
    0xba, 0x6f, 0xcf, 0x24, 0x85, 0x54, 0x0b, 0x13, 0xdf, 0xc8, 0x46, 0x8a};

static const struct gmnt6753 gmnt6753_zero = {
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};


// mnt6753 generator
//  .x =
//  "3458420969484235708806261200128850544017070333833944116801482064540723268149235477762870414664917360605949659630933184751526227993647030875167687492714052872195770088225183259051403087906158701786758441889742618916006546636728",
//  .y =
//  "27460508402331965149626600224382137254502975979168371111640924721589127725376473514838234361114855175488242007431439074223827742813911899817930728112297763448010814764117701403540298764970469500339646563344680868495474127850569"

static const struct gmnt6753 gmnt6753_one = {
    {0x00, 0x00, 0xb0, 0xd6, 0xe1, 0x41, 0x83, 0x6d, 0x26, 0x1d, 0xbe, 0x17,
     0x95, 0x97, 0x58, 0xb3, 0x3a, 0x19, 0x98, 0x71, 0x26, 0xcb, 0x80, 0x8d,
     0xfa, 0x41, 0x18, 0x54, 0xcf, 0x0a, 0x44, 0xc0, 0xf4, 0x96, 0x2e, 0xca,
     0x2a, 0x21, 0x3f, 0xfe, 0xaa, 0x77, 0x0d, 0xad, 0x44, 0xf5, 0x9f, 0x26,
     0x0a, 0xc6, 0x4c, 0x9f, 0xcb, 0x46, 0xda, 0x65, 0xcb, 0xc9, 0xee, 0xbe,
     0x1c, 0xe9, 0xb8, 0x3f, 0x91, 0xa6, 0x4b, 0x68, 0x51, 0x06, 0xd5, 0xf1,
     0xe4, 0xa0, 0x5d, 0xdf, 0xae, 0x9b, 0x2e, 0x1a, 0x56, 0x7e, 0x0e, 0x74,
     0xc1, 0xb7, 0xff, 0x94, 0xcc, 0x3f, 0x36, 0x1f, 0xb1, 0xf0, 0x64, 0xaa},
    {0x00, 0x00, 0x30, 0xbd, 0x0d, 0xcb, 0x53, 0xb8, 0x5b, 0xd0, 0x13, 0x04,
     0x30, 0x29, 0x43, 0x89, 0x66, 0xff, 0xec, 0x94, 0x38, 0x15, 0x0a, 0xd0,
     0x6f, 0x59, 0xb4, 0xcc, 0x8d, 0xda, 0x8b, 0xff, 0x0f, 0xe5, 0xd3, 0xf4,
     0xf6, 0x3e, 0x46, 0xac, 0x91, 0x57, 0x6d, 0x1b, 0x4a, 0x15, 0x07, 0x67,
     0x74, 0xfe, 0xb5, 0x1b, 0xa7, 0x30, 0xf8, 0x3f, 0xc9, 0xeb, 0x56, 0xe9,
     0xbc, 0xc9, 0x23, 0x3e, 0x03, 0x15, 0x77, 0xa7, 0x44, 0xc3, 0x36, 0xe1,
     0xed, 0xff, 0x55, 0x13, 0xbf, 0x5c, 0x9a, 0x4d, 0x23, 0x4b, 0xcc, 0x4a,
     0xd6, 0xd9, 0xf1, 0xb3, 0xfd, 0xf0, 0x0e, 0x16, 0x44, 0x6a, 0x82, 0x68},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01}};

bool gmnt6753_is_zero(gmnt6753 *p);
bool gmnt6753_is_on_curve(gmnt6753 *p);
void gmnt6753_copy(gmnt6753 *r, gmnt6753 *p);
void scalar6753_add(scalar6753 c, scalar6753 a, scalar6753 b);
void scalar6753_mul(scalar6753 c, scalar6753 a, scalar6753 b);

#endif // CODA_GROUP_UTILS
