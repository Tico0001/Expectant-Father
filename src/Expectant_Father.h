#include <pebble.h>

#ifdef PBL_PLATFORM_BASALT
 	#define TOP_OFFSET 16
#else
	#define TOP_OFFSET 0
#endif
	
#define KEY_COLOR_RED     0
#define KEY_COLOR_GREEN   1
#define KEY_COLOR_BLUE    2
#define KEY_HIGH_CONTRAST 3