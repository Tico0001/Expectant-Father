/*
The watch face only tells you how far along your wife is in the pregnancy in terms of weeks. 
And the size of the baby compared to a fruit. 
This is my first watch face and my first program in C. The code could be better.
I couldn't get mktime() to work so I had to come up with a different way to subtract dates.
You need to enter the approximate conception date and recompile. 
You can also modify the code to enter the name of your wife and future baby.
*/
#include <pebble.h>
#include "Expectant_Father.h"

/*** GLOBALS ***/

// If basalt, create status bar layer
#ifdef PBL_COLOR
	static StatusBarLayer *s_status_bar;
#endif
	
char* wife = "wife_text";
char* baby = "baby_text";
int year_concep;
int month_concep;
int day_concep;

Window *window;
TextLayer *backColorLayer;

TextLayer *wifeLayer;
TextLayer *pregLayer;
TextLayer *weekLayer;
TextLayer *babyLayer;
TextLayer *compLayer;
TextLayer *fruitLayer;

// List of comparisons
char* comparisons[] = {
	"size of a", 			//0
	"size of a",
	"size of a",
	"size of a",
	"size of a", 
	"size of a", 
	"size of a",
	"size of a",
	"size of a",
	"size of a",
	"size of a",			//10
	"size of a",
	"size of a",
	"size of a",
	"size of a",
	"size of an",
	"size of an",
	"weight of a",
	"length of a",
	"length of a",
	"length of a",			//20
	"weight of a",
	"weight of a",
	"weight of a",
	"length of an",
	"weight of a",
	"length of a",
	"weight of a",
	"weight of a",
	"weight of a",
	"weight of a",			//30
	"weight of a",
	"weight of a",
	"weight of a",
	"weight of a",
	"weight of a",
	"weight of a",
	"length of a",
	"length of a",
	"weight of a",
	"size of a"			//40
};

// List of fruits to compare to
char* fruits[] = {
	"dot",				//0
	"dot",
	"dot",
	"dot",
	"Poppy seed",
	"Sesame seed",
	"Lentil",
	"Blueberry",
	"Bean",
	"Grape",
	"Kumquat",			//10
	"Fig",
	"Lime",
	"Shrimp",
	"Lemon",
	"Apple",
	"Avocado",
	"turnip",
	"Bell pepper",
	"Mango",
	"Banana",			//20
	"Pomegranate",
	"Papaya",
	"Grapefruit",
	"Ear of Corn",
	"Cauliflower",
	"Lettuce",
	"Rutabaga",
	"Eggplant",
	"Butternut",
	"Cucumber",			//30
	"Pineapple",
	"Jicama",
	"Durian",
	"Cantaloupe",
	"Honeydew",
	"Big Coconut",
	"Leek",
	"Rhubarb",
	"Mini Watermelon",
	"Small Pumpkin"		//40
};

GColor colors[41];

//******************************************************************************
// init_colors
//******************************************************************************
void init_colors(void)
{
	colors[0]	=	GColorWhite;	
	colors[1]	=	GColorWhite; 	
	colors[2]	=	GColorWhite; 	
	colors[3]	=	GColorWhite; 	
	colors[4]	=	GColorWhite;	
	colors[5]	=	COLOR_FALLBACK(GColorWindsorTan, GColorWhite);	
	colors[6]	=	COLOR_FALLBACK(GColorWindsorTan, GColorWhite);	
	colors[7]	=	COLOR_FALLBACK(GColorIndigo, GColorWhite);	
	colors[8]	=	COLOR_FALLBACK(GColorWindsorTan, GColorWhite);	
	colors[9]	=	COLOR_FALLBACK(GColorBulgarianRose, GColorWhite);	
	colors[10]	=	COLOR_FALLBACK(GColorChromeYellow, GColorWhite);	
	colors[11]	=	COLOR_FALLBACK(GColorLimerick, GColorWhite);	
	colors[12]	=	COLOR_FALLBACK(GColorIslamicGreen, GColorWhite);	
	colors[13]	=	COLOR_FALLBACK(GColorMelon, GColorWhite);	
	colors[14]	=	COLOR_FALLBACK(GColorYellow, GColorWhite);	
	colors[15]	=	COLOR_FALLBACK(GColorRed, GColorWhite);	
	colors[16]	=	COLOR_FALLBACK(GColorJaegerGreen, GColorWhite);	
	colors[17]	=	COLOR_FALLBACK(GColorPurpureus, GColorWhite);	
	colors[18]	=	COLOR_FALLBACK(GColorDarkCandyAppleRed, GColorWhite);	
	colors[19]	=	COLOR_FALLBACK(GColorRajah, GColorWhite);	
	colors[20]	=	COLOR_FALLBACK(GColorYellow, GColorWhite);	
	colors[21]	=	COLOR_FALLBACK(GColorDarkCandyAppleRed, GColorWhite);	
	colors[22]	=	COLOR_FALLBACK(GColorYellow, GColorWhite);	
	colors[23]	=	COLOR_FALLBACK(GColorFolly, GColorWhite);	
	colors[24]	=	COLOR_FALLBACK(GColorIcterine, GColorWhite);	
	colors[25]	=	GColorWhite;	
	colors[26]	=	COLOR_FALLBACK(GColorKellyGreen, GColorWhite);	
	colors[27]	=	COLOR_FALLBACK(GColorPastelYellow, GColorWhite);	
	colors[28]	=	COLOR_FALLBACK(GColorPurple, GColorWhite);	
	colors[29]	=	COLOR_FALLBACK(GColorPastelYellow, GColorWhite);	
	colors[30]	=	COLOR_FALLBACK(GColorDarkGreen, GColorWhite);	
	colors[31]	=	COLOR_FALLBACK(GColorPastelYellow, GColorWhite);	
	colors[32]	=	COLOR_FALLBACK(GColorPastelYellow, GColorWhite);	
	colors[33]	=	COLOR_FALLBACK(GColorBrightGreen, GColorWhite);	
	colors[34]	=	COLOR_FALLBACK(GColorRajah, GColorWhite);	
	colors[35]	=	COLOR_FALLBACK(GColorMintGreen, GColorWhite);	
	colors[36]	=	GColorWhite;	
	colors[37]	=	COLOR_FALLBACK(GColorGreen, GColorWhite);	
	colors[38]	=	COLOR_FALLBACK(GColorRed, GColorWhite);	
	colors[39]	=	COLOR_FALLBACK(GColorIslamicGreen, GColorWhite);	
	colors[40]	=	COLOR_FALLBACK(GColorOrange, GColorWhite);			//40
}

//******************************************************************************
// inbox_received_callback
//******************************************************************************
static void inbox_received_callback(DictionaryIterator *iterator, void *context)
{
	//test
	APP_LOG(APP_LOG_LEVEL_DEBUG, "Message received!");
	
	// Get the first pair
	Tuple *t = dict_read_first(iterator);
	
	// Process all pairs present
	while (t != NULL) 
	{
		// Process this pair's key
		switch (t->key) 
		{
			case KEY_WIFE_NAME:
				wife = t->value->cstring;
				break;
			case KEY_BABY_NAME:
				baby = t->value->cstring;
				break;
			case KEY_CONCEP_YEAR:
				year_concep = t->value->uint16;
				break;
			case KEY_CONCEP_MON:
				month_concep = t->value->uint16;
				break;
			case KEY_CONCEP_DAY:
				day_concep = t->value->uint16;
				break;
			
		}

		// Get next pair, if any
		t = dict_read_next(iterator);
	}
	
	update();
}

//******************************************************************************
// inbox_dropped_callback
//******************************************************************************
static void inbox_dropped_callback(AppMessageResult reason, void *context)
{
	APP_LOG(APP_LOG_LEVEL_ERROR, "Message dropped!");
}

//******************************************************************************
//convert date to y_day
//******************************************************************************
long day_year(int d, int m, int y)
{
	m = (m + 9) % 12; 
	y = y - m/10; 
	return 365*y + y/4 - y/100 + y/400 + (m*306 + 5)/10 + ( d - 1 );
}


//******************************************************************************
// Weeks since conception date
//******************************************************************************
long get_weeks() 
{
	time_t temp = time(NULL); 
	struct tm *tick_time = localtime(&temp);

	long diff_days;
	
	diff_days = day_year(tick_time->tm_mday, tick_time->tm_mon + 1, tick_time->tm_year + 1900) - day_year(day_concep, month_concep, year_concep);

    return diff_days/7;
	
}

//******************************************************************************
// update: updates text layers
//******************************************************************************
static void update()
{
	// Initialize text buffers
	static char wifeText[30];
	static char weekText[4];
	static char pregText[16];
	static char babyText[20];
	static char compText[14];
	static char fruitText[17];
	

	// Get week of pregnancy
	int weeks = get_weeks();
	APP_LOG(APP_LOG_LEVEL_DEBUG, "Weeks: %d", weeks);
	
	// Assign text to text buffers depending on value of weeks
	// If weeks is negative set it to 0
	if(weeks < 0)
	{
		APP_LOG(APP_LOG_LEVEL_DEBUG, "Entered week < 0 IF");
		snprintf(wifeText, sizeof(wifeText), "%s is", wife);
		snprintf(weekText, sizeof(weekText), "not");
		snprintf(pregText, sizeof(pregText), "pregnant yet!");
		snprintf(babyText, sizeof(babyText), "And %s is", baby);
		snprintf(compText, sizeof(compText), "only a");
		snprintf(fruitText, sizeof(fruitText), "sweet dream");
		
		text_layer_set_text_color(fruitLayer, COLOR_FALLBACK(GColorRichBrilliantLavender, GColorWhite));
	}
	// if weeks is more than 40
	else if(weeks > 41)
	{
		APP_LOG(APP_LOG_LEVEL_DEBUG, "Entered week > 40 IF");
		snprintf(wifeText, sizeof(wifeText), "%s is", wife);
		snprintf(weekText, sizeof(weekText), "no");
		snprintf(pregText, sizeof(pregText), "longer pregnant!");
		snprintf(babyText, sizeof(babyText), "And %s is", baby);
		snprintf(compText, sizeof(compText), "about");
		snprintf(fruitText, sizeof(fruitText), "%d weeks old", weeks - 40);
		
		text_layer_set_text_color(fruitLayer, COLOR_FALLBACK(GColorRed, GColorWhite));
	}
	// If weeks is a "normal" value
	else
	{
		APP_LOG(APP_LOG_LEVEL_DEBUG, "Entered week normal IF");
		snprintf(wifeText, sizeof(wifeText), "%s is", wife);
		snprintf(weekText, sizeof(weekText), "%02d", weeks);
		snprintf(pregText, sizeof(pregText), "weeks pregnant");
		snprintf(babyText, sizeof(babyText), "And %s is the", baby);
		snprintf(compText, sizeof(compText), "%s", comparisons[weeks]);
		snprintf(fruitText, sizeof(fruitText), "%s", fruits[weeks]);
		
		text_layer_set_text_color(fruitLayer, colors[weeks]);
	}


	// Set text for pebble layer
	text_layer_set_text(pregLayer,pregText);
	text_layer_set_text(wifeLayer,wifeText);
	text_layer_set_text(weekLayer,weekText);
	text_layer_set_text(babyLayer,babyText);
	text_layer_set_text(compLayer,compText);
	text_layer_set_text(fruitLayer,fruitText);
}

//******************************************************************************
// tick_handler
//******************************************************************************
static void tick_handler(struct tm *tick_time, TimeUnits units_changed) 
{
	update();
}

//******************************************************************************
// main_window_load
//******************************************************************************
static void main_window_load(Window *window)
{ 
	
	Layer *window_layer = window_get_root_layer(window);
	GRect bounds = layer_get_bounds(window_layer);
	
	// Set background color
	window_set_background_color(window, GColorBlack);
	backColorLayer = text_layer_create(GRect(0, 0, bounds.size.w, bounds.size.h/2));
	text_layer_set_background_color(backColorLayer, GColorWhite);
	
	// Init the text layer used to show the wife
	wifeLayer = text_layer_create(GRect(10, 10 + TOP_OFFSET, bounds.size.w/2 /* width */, bounds.size.h/5 /* height */));
	text_layer_set_text_color(wifeLayer, GColorBlack);
	text_layer_set_background_color(wifeLayer, GColorClear);
	text_layer_set_font(wifeLayer, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
	text_layer_set_text_alignment(wifeLayer, GTextAlignmentRight);

	// Init the text layer used to show the weeks
	weekLayer = text_layer_create(GRect(bounds.size.w/2 + bounds.size.w/9, 5 + TOP_OFFSET, bounds.size.w /* width */, bounds.size.h/4 /*height */));
	text_layer_set_text_color(weekLayer, COLOR_FALLBACK(GColorRed, GColorBlack));
	text_layer_set_background_color(weekLayer, GColorClear);
	text_layer_set_font(weekLayer, fonts_get_system_font(FONT_KEY_BITHAM_30_BLACK));
	text_layer_set_text_alignment(weekLayer, GTextAlignmentLeft);
		
	// Init the text layer used to show "weeks pregnant"
	pregLayer = text_layer_create(GRect(0, 35 + TOP_OFFSET, bounds.size.w /* width */, bounds.size.h/5 /* height */));
	text_layer_set_text_color(pregLayer, GColorBlack);
	text_layer_set_background_color(pregLayer, GColorClear);
	text_layer_set_font(pregLayer, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
	text_layer_set_text_alignment(pregLayer, GTextAlignmentCenter);
				
	// Init the text layer used to show the baby
	babyLayer = text_layer_create(GRect(0, 65 + TOP_OFFSET, bounds.size.w /* width */, bounds.size.h/5 /* height */));
	text_layer_set_text_color(babyLayer, GColorWhite);
	text_layer_set_background_color(babyLayer, GColorBlack);
	text_layer_set_font(babyLayer, fonts_get_system_font(FONT_KEY_GOTHIC_24));
	text_layer_set_text_alignment(babyLayer, GTextAlignmentCenter);

	// Init the text layer used to show the comparison
	compLayer = text_layer_create(GRect(0, 90 + TOP_OFFSET, bounds.size.w /* width */, bounds.size.h/5 /* height */));
	text_layer_set_text_color(compLayer, GColorWhite);
	text_layer_set_background_color(compLayer, GColorBlack);
	text_layer_set_font(compLayer, fonts_get_system_font(FONT_KEY_GOTHIC_24));
	text_layer_set_text_alignment(compLayer, GTextAlignmentCenter);

	// Init the text layer used to show the fruit
	fruitLayer = text_layer_create(GRect(0, 120 + TOP_OFFSET, bounds.size.w /* width */, bounds.size.h/5 /* height */));
	text_layer_set_text_color(fruitLayer, GColorWhite);
	text_layer_set_background_color(fruitLayer, GColorBlack);
	text_layer_set_font(fruitLayer, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
	text_layer_set_text_alignment(fruitLayer, GTextAlignmentCenter);
	
	// Add it as a child layer to the Window's root layer
	layer_add_child(window_get_root_layer(window), text_layer_get_layer(backColorLayer));
	layer_add_child(window_get_root_layer(window), text_layer_get_layer(wifeLayer));
	layer_add_child(window_get_root_layer(window), text_layer_get_layer(pregLayer));
	layer_add_child(window_get_root_layer(window), text_layer_get_layer(weekLayer));
	layer_add_child(window_get_root_layer(window), text_layer_get_layer(babyLayer));
	layer_add_child(window_get_root_layer(window), text_layer_get_layer(compLayer));
	layer_add_child(window_get_root_layer(window), text_layer_get_layer(fruitLayer));
	
	// Add status bar with time
	#ifdef PBL_COLOR
		// Set up the status bar last to ensure it is on top of other Layers
		s_status_bar = status_bar_layer_create();
		layer_add_child(window_layer, status_bar_layer_get_layer(s_status_bar));
	#endif
	
	// Add status bar with time and battery
	#ifdef PBL_BW
		 window_set_fullscreen(window, false);
	#endif
}

//******************************************************************************
// main_window_unload
//******************************************************************************
static void main_window_unload(Window *window) 
{
	//Destroy TextLayers
	text_layer_destroy(wifeLayer);
	text_layer_destroy(pregLayer);
	text_layer_destroy(weekLayer);
	text_layer_destroy(babyLayer);
	text_layer_destroy(compLayer);
	text_layer_destroy(fruitLayer);
	
	#ifdef PBL_PLATFORM_BASALT
		status_bar_layer_destroy(s_status_bar);
	#endif
}

//******************************************************************************
// init
//******************************************************************************
static void init() 
{
	// Test
	APP_LOG(APP_LOG_LEVEL_DEBUG, "Initializing...");
	
	// Persistent Storage read
	if(persist_exists(PKEY_WIFE))
		persist_read_string(PKEY_WIFE, wife, 10);
	else
		wife = DEFAULT_WIFE;
	
	if(persist_exists(PKEY_BABY))
		persist_read_string(PKEY_BABY, baby, 10);
	else
		baby = DEFAULT_BABY;
		
  	year_concep = persist_exists(PKEY_CONCEP_YEAR) ? persist_read_int(PKEY_CONCEP_YEAR) : DEFAULT_CONCEP_YEAR;
	month_concep = persist_exists(PKEY_CONCEP_MON) ? persist_read_int(PKEY_CONCEP_MON) : DEFAULT_CONCEP_MON;
	day_concep = persist_exists(PKEY_CONCEP_DAY) ? persist_read_int(PKEY_CONCEP_DAY) : DEFAULT_CONCEP_DAY;
	
	// Register callbacks
	app_message_register_inbox_received(inbox_received_callback);
	app_message_register_inbox_dropped(inbox_dropped_callback);
	app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());
	
	// Creat main window
	window = window_create();
	
 	// Set handlers to manage the elements inside the Window
  	window_set_window_handlers(window, (WindowHandlers)
	{
    	.load = main_window_load,
    	.unload = main_window_unload
  	});
	
	// Show the Window on the watch, with animated=true
	window_stack_push(window, true);
	
	init_colors();
	
	// Update text layers
	update();
	
	// Register with TickTimerService
	tick_timer_service_subscribe(HOUR_UNIT, tick_handler);
	
	// Test
	APP_LOG(APP_LOG_LEVEL_DEBUG, "Initialized!");
}

//******************************************************************************
// deinit
//******************************************************************************
static void deinit() 
{
	// Persistent Storage
	// Save the date into persistent storage on app exit
	persist_write_string(PKEY_WIFE, wife);
	persist_write_string(PKEY_BABY, baby);
	persist_write_int(PKEY_CONCEP_YEAR, year_concep);
	persist_write_int(PKEY_CONCEP_MON, month_concep);
	persist_write_int(PKEY_CONCEP_DAY, day_concep);
		
	// Destroy Window
	window_destroy(window);
	
	// Test
	APP_LOG(APP_LOG_LEVEL_DEBUG, "Deinitialized!");
}

//******************************************************************************
// main
//******************************************************************************
int main(void) 
{
  init();
  app_event_loop();
  deinit();
}
