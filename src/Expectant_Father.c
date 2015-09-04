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
#ifdef PBL_PLATFORM_BASALT
	static StatusBarLayer *s_status_bar;
#endif
	
//conception date
char* wife = "          ";
char* baby = "          ";
int year_concep = DEFAULT_CONCEP_YEAR;
int month_concep = DEFAULT_CONCEP_MON;
int day_concep = DEFAULT_CONCEP_DAY;

Window *window;

TextLayer *wifeLayer;
TextLayer *weekLayer;
TextLayer *babyLayer;
TextLayer *compLayer;
TextLayer *fruitLayer;

//starting at 4 weeks
char* comparisons[] = {
  "  size of a ", 
  "  size of a ",
  "  size of a ",
  "  size of a ",
  "  size of a ", 
  "  size of a ", 
  "  size of a ",
  "  size of a ",
  "  size of a ",
  "  size of a ",
  "  size of a ",
  "  size of a ",
  "  size of a ",
  "  size of a ",
  "  size of a ",
  "  size of an ",
  "  size of an ",
  "  weight of a ",
  "  length of a ",
  "  length of a ",
  "  length of a ",//20
  "  weight of a ",
  "  weight of a ",
  "  weight of a ",
  "  length of an ",
  "  weight of a ",
  "  length of a ",
  "  weight of a ",
  "  weight of a ",
  "  weight of a ",
  "  weight of a ",
  "  weight of a ",
  "  weight of a ",
  "  weight of a ",
  "  weight of a ",
  "  weight of a ",
  "  weight of a ",
  "  length of a ",
  "  length of a ",
  "  weight of a ",
  "  size of a "
};

char* fruits[] = {
  "    dot",
  "    dot", 
  "    dot", 
  "    dot", 
  "    poppy seed",
  "   sesame seed",
  "    lentil",
  "    blueberry",
  "    bean",
  "    grape",
  "    kumquat",
  "    fig",
  "    lime",
  "    shrimp",
  "    lemon",
  "    apple",
  "    avocado",
  "    turnip",
  "    bell pepper",
  "    mango",
  "    Banana",//20
  "    Pomegranate",
  "    Papaya",
  "    Grapefruit",
  "    Ear of Corn",
  "    Cauliflower",
  "    Lettuce",
  "    Rutabaga",
  "    Eggplant",
  "    Butternut",
  "    Cucumber",
  "    Pineapple",
  "    Jicama",
  "    Durian",
  "    Cantaloupe",
  "    Honeydew",
  "    Big Coconut",
  "    Leek",
  "    Rhubarb",
  "Mini Watermelon",
  "    Small Pumpkin"
};

//******************************************************************************
//
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
//
//******************************************************************************
static void inbox_dropped_callback(AppMessageResult reason, void *context)
{
	APP_LOG(APP_LOG_LEVEL_ERROR, "Message dropped!");
}

//******************************************************************************
//
//******************************************************************************
void itoa2(int num, char* buffer) 
{
    const char digits[10] = "0123456789";
    if(num > 99)
	{
        buffer[0] = '9';
        buffer[1] = '9';
        return;
    }
	else if(num > 9) 
	{
        buffer[0] = digits[num / 10];
    }
	else
	{
        buffer[0] = '0';
    }
    buffer[1] = digits[num % 10];
}

//******************************************************************************
//
//******************************************************************************
void replacetxt(char str[], char* buffer) 
{
    for (unsigned int i = 0; i < strlen(str); i++)
    {
		buffer[i] = str[i];
    }
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
//
//******************************************************************************
static void update()
{
// 	// Alternative text update
// 	static char s_body_text[18];
// 	snprintf(s_body_text, sizeof(s_body_text), "%u Bottles", s_num_drinks);
// 	text_layer_set_text(s_body_layer, s_body_text);
	
	static char wifeText[] = "My wife is    weeks pregnant.";
	static char weekText[] = "XX";
	static char babyText[] = "  The baby is the"; 
// 	static char compText[] = "              ";
// 	static char fruitText[] = "                 ";
	static char compText[14];
	static char fruitText[17];

	int weeks = get_weeks();

	itoa2(get_weeks(), &weekText[0]);
	
// 	replacetxt(comparisons[weeks],&compText[0]);
// 	replacetxt(fruits[weeks],&fruitText[0]);
	snprintf(compText, sizeof(compText), "%s", comparisons[weeks]);
	snprintf(fruitText, sizeof(fruitText), "%s", fruits[weeks]);

	text_layer_set_text(wifeLayer,wifeText);
	text_layer_set_text(weekLayer,weekText);
	text_layer_set_text(babyLayer,babyText);
	text_layer_set_text(compLayer,compText);
	text_layer_set_text(fruitLayer,fruitText);
}

//******************************************************************************
//
//******************************************************************************
static void tick_handler(struct tm *tick_time, TimeUnits units_changed) 
{
	update();
}

//******************************************************************************
//
//******************************************************************************
static void main_window_load(Window *window)
{ 
	// If Basalt, add status bar with time
	#ifdef PBL_PLATFORM_BASALT
		Layer *window_layer = window_get_root_layer(window);
		// Set up the status bar last to ensure it is on top of other Layers
		s_status_bar = status_bar_layer_create();
		layer_add_child(window_layer, status_bar_layer_get_layer(s_status_bar));
	#endif
	
	// Set background color
	window_set_background_color(window, GColorWhite);

	// Init the text layer used to show the weeks
	weekLayer = text_layer_create(GRect(85, TOP_OFFSET, 144-20 /* width */, 168-54 /* height */));
	text_layer_set_text_color(weekLayer, GColorRed);
	text_layer_set_background_color(weekLayer, GColorClear);
	text_layer_set_font(weekLayer, fonts_get_system_font(FONT_KEY_BITHAM_34_MEDIUM_NUMBERS));

	// Init the text layer used to show the wife
	wifeLayer = text_layer_create(GRect(5, 10 + TOP_OFFSET, 144-20 /* width */, 168-54 /* height */));
	text_layer_set_text_color(wifeLayer, GColorBlack);
	text_layer_set_background_color(wifeLayer, GColorClear);
	text_layer_set_font(wifeLayer, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));

	// Init the text layer used to show the baby
	babyLayer = text_layer_create(GRect(0, 70 + TOP_OFFSET, 144 /* width */, 168-54 /* height */));
	text_layer_set_text_color(babyLayer, GColorWhite);
	text_layer_set_background_color(babyLayer, GColorBlack);
	text_layer_set_font(babyLayer, fonts_get_system_font(FONT_KEY_GOTHIC_24));
	text_layer_set_text_alignment(babyLayer, GTextAlignmentCenter);

	// Init the text layer used to show the comparison
	compLayer = text_layer_create(GRect(0, 97 + TOP_OFFSET, 144 /* width */, 168-54 /* height */));
	text_layer_set_text_color(compLayer, GColorWhite);
	text_layer_set_background_color(compLayer, GColorBlack);
	text_layer_set_font(compLayer, fonts_get_system_font(FONT_KEY_GOTHIC_24));
	text_layer_set_text_alignment(compLayer, GTextAlignmentCenter);

	// Init the text layer used to show the fruit
	fruitLayer = text_layer_create(GRect(0, 125 + TOP_OFFSET, 144 /* width */, 168-54 /* height */));
	text_layer_set_text_color(fruitLayer, GColorWhite);
	text_layer_set_background_color(fruitLayer, GColorBlack);
	text_layer_set_font(fruitLayer, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
	text_layer_set_text_alignment(fruitLayer, GTextAlignmentCenter);
	
	// Add it as a child layer to the Window's root layer
	layer_add_child(window_get_root_layer(window), text_layer_get_layer(wifeLayer));
	layer_add_child(window_get_root_layer(window), text_layer_get_layer(weekLayer));
	layer_add_child(window_get_root_layer(window), text_layer_get_layer(babyLayer));
	layer_add_child(window_get_root_layer(window), text_layer_get_layer(compLayer));
	layer_add_child(window_get_root_layer(window), text_layer_get_layer(fruitLayer));
}

//******************************************************************************
//
//******************************************************************************
static void main_window_unload(Window *window) 
{
	//Destroy TextLayers
	text_layer_destroy(wifeLayer);
	text_layer_destroy(weekLayer);
	text_layer_destroy(babyLayer);
	text_layer_destroy(compLayer);
	text_layer_destroy(fruitLayer);
}

//******************************************************************************
//
//******************************************************************************
static void init() 
{
	// Test
	APP_LOG(APP_LOG_LEVEL_DEBUG, "Initializing...");
	
	// Persistent storage
	// Get the date from persistent storage for use if it exists, otherwise use the default
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
	
	update();
	
	// Register with TickTimerService
	tick_timer_service_subscribe(HOUR_UNIT, tick_handler);

}

//******************************************************************************
//
//******************************************************************************
static void deinit() 
{
	// Persistent Storage
	// Save the date into persistent storage on app exit
	persist_write_int(PKEY_CONCEP_YEAR, year_concep);
	persist_write_int(PKEY_CONCEP_MON, month_concep);
	persist_write_int(PKEY_CONCEP_DAY, day_concep);
	
	// Destroy Window
	window_destroy(window);
}

//******************************************************************************
//
//******************************************************************************
int main(void) 
{
  init();
  app_event_loop();
  deinit();
}
