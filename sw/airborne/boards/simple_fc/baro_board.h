/*
 * board specific functions for the simple_fc board
 */

#ifndef BOARDS_SIMPLE_FC_H
#define BOARDS_SIMPLE_FC_H

// only for printing the baro type during compilation
#ifndef BARO_BOARD
#define BARO_BOARD BARO_MS5611_I2C
#endif

extern void baro_event(void);
#define BaroEvent baro_event

#endif /* BOARDS_SIMPLE_FC_H */
