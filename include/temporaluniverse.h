// Active Object Header
#ifndef temporaluniverse_h
#define temporaluniverse_h

#include "signals.h"

#define HOUR_TICKS BSP_TICKS_PER_SEC
#define DAY_TICKS HOUR_TICKS*24
#define WEEK_TICKS HOUR_TICKS*24*7
#define MONTH_TICKS HOUR_TICKS*24*30
#define YEAR_TICKS HOUR_TICKS*24*365

void TemporalUniverse_ctor(void);
extern QActive * const AO_TemporalUniverse;

#endif /* temporaluniverse_h */
        
