#ifndef _GLOBAL_H
#define _GLOBAL_H

#define UNUSED(X)  (void)(X)
#define SWAP16(X, Y) { uint16_t _temp = (X); (X) = (Y); (Y) = _temp; }
#define SWAP32(X, Y) { uint32_t _temp = (X); (X) = (Y); (Y) = _temp; }

#endif
