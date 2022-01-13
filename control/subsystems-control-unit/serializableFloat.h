#ifndef SERIALIZABLE_FLOAT_H
#define SERIALIZABLE_FLOAT_H

union SerializableFloat {
  float number;
  uint8_t bynary[4];
};

#endif
