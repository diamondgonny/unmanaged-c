#ifndef MACROS_H
#define MACROS_H

#define MAX(x, y) (((x) > (y)) ? (x) : (y))

#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#define ABS(x) (((x) >= (0)) ? (x) : -(x))

#define RANGE(curr, min, max) for (curr = min; curr <= max; curr++) \

#define RANGE_DESC(curr, max, min) for (curr = max; curr >= min; curr--) \

#define SET(ary, start, count, value)   { \
                                        int set_i; \
                                        for (set_i = start; set_i < start + count; set_i++) \
                                        *(ary + set_i) = value; \
                                        } \
                                        if(1) 1\

#endif /* MACROS_H */
