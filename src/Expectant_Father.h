#include <pebble.h>

#ifdef PBL_PLATFORM_BASALT
 	#define TOP_OFFSET 				16
#else
	#define TOP_OFFSET 				0
#endif
	
// JS KEYs
#define KEY_WIFE_NAME				0
#define KEY_BABY_NAME				1
#define KEY_CONCEP_YEAR				2
#define KEY_CONCEP_MON				3
#define KEY_CONCEP_DAY				4
	
// Persistent Storage KEYS
#define PKEY_WIFE 					0
#define PKEY_BABY					1
#define PKEY_CONCEP_YEAR 			2
#define PKEY_CONCEP_MON				3
#define PKEY_CONCEP_DAY				4

// Default values
#define DEFAULT_WIFE				"My Wife"
#define DEFAULT_BABY		 		"the baby"
#define DEFAULT_CONCEP_YEAR 		2015
#define DEFAULT_CONCEP_MON			04
#define DEFAULT_CONCEP_DAY			24

	
static void update(void);
