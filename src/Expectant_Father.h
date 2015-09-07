#include <pebble.h>

#ifdef PBL_PLATFORM_BASALT
 	#define TOP_OFFSET 				16
	#define GColorRed 				(GColor8){.argb=GColorRedARGB8}
#else
	#define TOP_OFFSET 				0
	#define GColorRed 				GColorBlack
#endif
	
#define KEY_WIFE_NAME				0
#define KEY_BABY_NAME				1
#define KEY_CONCEP_YEAR				2
#define KEY_CONCEP_MON				3
#define KEY_CONCEP_DAY				4
	
#define PKEY_WIFE 					0
#define PKEY_BABY					1
#define PKEY_CONCEP_YEAR 			2
#define PKEY_CONCEP_MON				3
#define PKEY_CONCEP_DAY				4

#define DEFAULT_WIFE				"My Wife"
#define DEFAULT_BABY		 		"the baby"
#define DEFAULT_CONCEP_YEAR 		2015
#define DEFAULT_CONCEP_MON			05
#define DEFAULT_CONCEP_DAY			24

	
static void update(void);
void replacetxt(char str[], char* buffer) ;