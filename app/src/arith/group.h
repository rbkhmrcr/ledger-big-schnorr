#ifndef CODA_GROUP
#define CODA_GROUP

#include <stdint.h>
#include <stdbool.h>
#include "field.h"

const fmnt6753 group_order =
  {1234, 1234, 1234, 1234,
    1234, 1234, 1234, 1234,
    1234, 1234, 1234, 1234};
const fmnt6753 coeff_a =
  {1234, 1234, 1234, 1234,
    1234, 1234, 1234, 1234,
    1234, 1234, 1234, 1234};
const fmnt6753 coeff_b =
  {1234, 1234, 1234, 1234,
    1234, 1234, 1234, 1234,
    1234, 1234, 1234, 1234};

typedef struct gmnt6753 {
  uint64_t X[12];
  uint64_t Y[12];
  uint64_t Z[12];
} gmnt6753;

// mnt6753 generator
//  .x = "3458420969484235708806261200128850544017070333833944116801482064540723268149235477762870414664917360605949659630933184751526227993647030875167687492714052872195770088225183259051403087906158701786758441889742618916006546636728",
//  .y = "27460508402331965149626600224382137254502975979168371111640924721589127725376473514838234361114855175488242007431439074223827742813911899817930728112297763448010814764117701403540298764970469500339646563344680868495474127850569"
const gmnt6753 gen = {
  .X = {1234, 1234, 1234, 1234,
    1234, 1234, 1234, 1234,
    1234, 1234, 1234, 1234},
  .Y = {1234, 1234, 1234, 1234,
    1234, 1234, 1234, 1234,
    1234, 1234, 1234, 1234},
  .Z = {1234, 1234, 1234, 1234,
    1234, 1234, 1234, 1234,
    1234, 1234, 1234, 1234},
};

void gmnt6753_add(gmnt6753 *r, gmnt6753 *p, gmnt6753 *q);
void gmnt6753_sub(gmnt6753 *r, gmnt6753 *p, gmnt6753 *q);
void gmnt6753_double(gmnt6753 *r, gmnt6753 *p);
void gmnt6753_scalar_mul(gmnt6753 *r, fmnt6753 *k, gmnt6753 *p);
bool gmnt6753_is_on_curve(gmnt6753 *p);

#endif // CODA_GROUP
