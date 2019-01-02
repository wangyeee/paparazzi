#ifndef MAG3110_H
#define MAG3110_H

#include "std.h"
#include "mcu_periph/i2c.h"
#include "math/pprz_algebra_int.h"

struct Mag3110 {
  struct i2c_periph *i2c_p;
  struct i2c_transaction i2c_trans;
  bool initialized;                 ///< config done flag

  volatile bool data_available;     ///< data ready flag
  union {
    struct Int16Vect3 vect;           ///< data vector in mag coordinate system
    int16_t value[3];                 ///< data values accessible by channel index
  } data;
};

// Functions
extern void mag3110_init(struct Mag3110 *mag, struct i2c_periph *i2c_p, uint8_t addr);
extern void mag3110_start_configure(struct Mag3110 *mag);
extern void mag3110_read(struct Mag3110 *mag);
extern void mag3110_event(struct Mag3110 *mag);

/// convenience function: read or start configuration if not already initialized
static inline void mag3110_periodic(struct Mag3110 *mag)
{
  if (mag->initialized) {
    mag3110_read(mag);
  } else {
    mag3110_start_configure(mag);
  }
}

#endif /* MAG3110_H */
