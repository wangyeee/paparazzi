#include "peripherals/mag3110.h"
#include "mcu_periph/sys_time.h"
#include "std.h"

#define Int16FromBuf(_buf,_idx) ((int16_t)((_buf[_idx]<<8) | _buf[_idx+1]))

static void mag3110_i2c_tx_reg(struct Mag3110 *mag, uint8_t reg, uint8_t val)
{
  mag->i2c_trans.type = I2CTransTx;
  mag->i2c_trans.buf[0] = reg;
  mag->i2c_trans.buf[1] = val;
  mag->i2c_trans.len_r = 0;
  mag->i2c_trans.len_w = 2;
  i2c_submit(mag->i2c_p, &(mag->i2c_trans));
}

void mag3110_init(struct Mag3110 *mag, struct i2c_periph *i2c_p, uint8_t addr) {
  /* set i2c_peripheral */
  mag->i2c_p = i2c_p;
  /* set i2c address */
  mag->i2c_trans.slave_addr = addr;
  mag->i2c_trans.status = I2CTransDone;
  mag->initialized = 0;
}

void mag3110_start_configure(struct Mag3110 *mag) {
  mag3110_i2c_tx_reg(mag, 0x11, 0x80);
  mag3110_i2c_tx_reg(mag, 0x10, 0x01);
  mag->initialized = 1;
}

void mag3110_read(struct Mag3110 *mag) {
  if (mag->initialized && mag->i2c_trans.status == I2CTransDone) {
    mag->i2c_trans.buf[0] = 0x01;
    mag->i2c_trans.type = I2CTransTxRx;
    mag->i2c_trans.len_r = 6;
    mag->i2c_trans.len_w = 1;
    i2c_submit(mag->i2c_p, &(mag->i2c_trans));
  }
}

void mag3110_event(struct Mag3110 *mag) {
  if (mag->initialized) {
    if (mag->i2c_trans.status == I2CTransFailed) {
      mag->i2c_trans.status = I2CTransDone;
    } else if (mag->i2c_trans.status == I2CTransSuccess) {
      mag->data.vect.x = Int16FromBuf(mag->i2c_trans.buf, 0);
      mag->data.vect.y = Int16FromBuf(mag->i2c_trans.buf, 2);
      mag->data.vect.z = Int16FromBuf(mag->i2c_trans.buf, 4);
      mag->data_available = true;
      mag->i2c_trans.status = I2CTransDone;
    }
  } else if (mag->initialized == 0) { // Configuring but not yet initialized
    if (mag->i2c_trans.status == I2CTransSuccess || mag->i2c_trans.status == I2CTransDone) {
      mag->i2c_trans.status = I2CTransDone;
      mag3110_start_configure(mag);
    }
    if (mag->i2c_trans.status == I2CTransFailed) {
      mag->initialized = 0;
      mag->i2c_trans.status = I2CTransDone;
      mag3110_start_configure(mag);
    }
  }
}
