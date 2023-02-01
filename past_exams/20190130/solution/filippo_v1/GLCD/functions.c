
#include "functions.h"
#include "stdio.h"

extern uint8_t happiness;
extern uint8_t satiety;
extern uint8_t happiness_counter;
extern uint8_t satiety_counter;

extern uint8_t hr;
extern uint8_t min;
extern uint8_t sec;
extern uint8_t state;
extern uint8_t joystick_flag;

extern uint8_t menu_selection;
extern unsigned short volume;

uint8_t random_int_ranged(uint8_t lower, uint8_t upper, uint8_t exclude) {
	int possible_result = exclude;
	while(possible_result == exclude){
		possible_result = (rand() % (upper - lower + 1)) + lower;
	}
	return (uint8_t) possible_result;
}

void draw_rectangle(uint16_t Xpos, uint16_t Ypos, uint16_t h, uint16_t b, uint16_t color){
	LCD_DrawLine(Xpos, Ypos, Xpos+b, Ypos, color);
	LCD_DrawLine(Xpos, Ypos, Xpos, Ypos+h, color);
	LCD_DrawLine(Xpos, Ypos+h, Xpos+b, Ypos+h, color);
	LCD_DrawLine(Xpos+b, Ypos+h, Xpos+b, Ypos, color);
}

void draw_rectangle_color(uint16_t Xpos, uint16_t Ypos, uint16_t h, uint16_t b, uint16_t color){
	int i;
	
	for (i=0; i<h; i++){
		LCD_DrawLine(Xpos, Ypos+i, Xpos+b, Ypos+i, color);
	}
}

void draw_big_pixel(uint16_t Xpos, uint16_t Ypos, uint16_t color){
	uint16_t reference_x = Xpos * 5;
	uint16_t reference_y = Ypos * 5;
	int i;

	if (color == Blank)
	{
		return;
	}

	for (i=0; i<5; i++){
		LCD_DrawLine(reference_x, reference_y+i, reference_x+5, reference_y+i, color);
	}
}

void init_graphics(){
	LCD_Clear(White);
	draw_rectangle(2, 280, 38, 116, Black);
	draw_rectangle(122, 280, 38, 116, Black);
	GUI_Text(45, 290, (uint8_t *) "Meal", Black, White);
	GUI_Text(160, 290, (uint8_t *) "Snack", Black, White);
}

void draw_frame(uint16_t Xpos, uint16_t Ypos, uint8_t pos) {
	int x, y;
	
	for(y=0; y < 20; y++){
		for(x=0; x < 24; x++){
			draw_big_pixel(Xpos + x, Ypos + y, charm[pos][y][x]);
		}
	}
}

void clear_frame(uint16_t Xpos, uint16_t Ypos, uint8_t pos) {
	int x, y;
	
	for(y=0; y < 20; y++){
		for(x=0; x < 24; x++){
			if (charm[pos][y][x] != Blank) {
				draw_big_pixel(Xpos + x, Ypos + y, White);
			}
		}
	}
}

void draw_meal(uint16_t Xpos, uint16_t Ypos) {
	int x, y;
	
	for(y=0; y < 5; y++){
		for(x=0; x < 5; x++){
			draw_big_pixel(Xpos + x, Ypos + y, meal[y][x]);
		}
	}
}

void clear_meal(uint16_t Xpos, uint16_t Ypos) {
	int x, y;
	
	for(y=0; y < 5; y++){
		for(x=0; x < 5; x++){
			if (meal[y][x] != Blank) {
				draw_big_pixel(Xpos + x, Ypos + y, White);
			}
		}
	}
}

void draw_snack(uint16_t Xpos, uint16_t Ypos) {
	int x, y;
	
	for(y=0; y < 5; y++){
		for(x=0; x < 6; x++){
			draw_big_pixel(Xpos + x, Ypos + y, snack[y][x]);
		}
	}
}

void clear_snack(uint16_t Xpos, uint16_t Ypos) {
	int x, y;
	
	for(y=0; y < 5; y++){
		for(x=0; x < 6; x++){
			if (snack[y][x] != Blank) {
				draw_big_pixel(Xpos + x, Ypos + y, White);
			}
		}
	}
}

void draw_volume(void){
	int x, y, j;

	for(y=0; y < 18; y++){
		for(x=0; x < 10; x++){
			LCD_SetPoint(x + 5, y + 5, volume_base[y][x]);
		}
	}

	for (j=0; j < volume; j++) {
		for(y=0; y < 16; y++){
			for(x=0; x < 3; x++){
				LCD_SetPoint(x + 17 + (j*4), y + 6, volume_level[y][x]);
			}
		}
	}

	for (j=volume; j < 5; j++) {
		for(y=0; y < 16; y++){
			for(x=0; x < 3; x++){
				LCD_SetPoint(x + 17 + (j*4), y + 6, White);
			}
		}
	}
}

void evaluate_monster(){
	static uint8_t scaling_x = 1;
	static uint8_t scaling_y = 1;

	draw_volume();
	
	if(state == 0 && destination_x == current_x && destination_y == current_y) {
		// little guy arrived at destination
		// generate new destination if state 0
		destination_x = random_int_ranged(1, 27, current_x);
		destination_y = random_int_ranged(16, 37, current_y);
	}

	// clear old charmander
	clear_frame(current_x, current_y, side - 1);

	// scaling/speed x
	if ( abs(destination_x - current_x) < 3 ) {
		scaling_x = 1;
	} else {
		scaling_x = 3;
	}

	// scaling/speed y
	if ( abs(destination_y - current_y) < 3 ) {
		scaling_y = 1;
	} else {
		scaling_y = 3;
	}
	
	// movement x
	if(current_x > destination_x){
		current_x = current_x - scaling_x;
		side = random_int_ranged(3,4, side);
	} else if(current_x == destination_x) {
		// do nothing
	} else {
		current_x = current_x + scaling_x;
		side = random_int_ranged(1,2, side);
	}
	
	// movement y
	if(current_y > destination_y){
		current_y = current_y - scaling_y;
	} else if(current_y == destination_y) {
		// do nothing
	} else {
		current_y = current_y + scaling_y;
	}

	// draw new charmander
	draw_frame(current_x, current_y, side - 1);

	// debug
	// draw_big_pixel(destination_x, destination_y, Green);
	// draw_big_pixel(1, 16, Blue);
	// draw_big_pixel(27, 16, Blue);
	// draw_big_pixel(1, 37, Blue);
	// draw_big_pixel(27, 37, Blue);
}

void cuddle_monster(uint8_t at){
	clear_frame(current_x, current_y, side - 1);
	
	side = at;

	// draw new charmander
	draw_frame(current_x, current_y, at);
}


void refresh_menu(uint8_t menu_selection, uint8_t reset){
	// static uint8_t last_menu = 5;
	
	if (!reset) {
		// if (menu_selection != last_menu) {
			// last_menu = menu_selection;
			if (menu_selection == 0) {
				LCD_DrawLine(5, 283, 5, 315, Red);
				LCD_DrawLine(6, 284, 6, 315, Red);
				LCD_DrawLine(5, 315, 115, 315, Red);
				LCD_DrawLine(5, 314, 115, 314, Red);
				LCD_DrawLine(115, 283, 115, 315, Red);
				LCD_DrawLine(114, 284, 114, 315, Red);
				
				LCD_DrawLine(125, 283, 125, 315, White);
				LCD_DrawLine(126, 284, 126, 315, White);
				LCD_DrawLine(125, 315, 235, 315, White);
				LCD_DrawLine(125, 314, 235, 314, White);
				LCD_DrawLine(235, 283, 235, 315, White);
				LCD_DrawLine(234, 284, 234, 315, White);
			}
		
			if (menu_selection == 1) {
				LCD_DrawLine(125, 283, 125, 315, Red);
				LCD_DrawLine(126, 284, 126, 315, Red);
				LCD_DrawLine(125, 315, 235, 315, Red);
				LCD_DrawLine(125, 314, 235, 314, Red);
				LCD_DrawLine(235, 283, 235, 315, Red);
				LCD_DrawLine(234, 284, 234, 315, Red);

				LCD_DrawLine(5, 283, 5, 315, White);
				LCD_DrawLine(6, 284, 6, 315, White);
				LCD_DrawLine(5, 315, 115, 315, White);
				LCD_DrawLine(5, 314, 115, 314, White);
				LCD_DrawLine(115, 283, 115, 315, White);
				LCD_DrawLine(114, 284, 114, 315, White);
			}
		// }
	} else{
		draw_rectangle_color(0, 280, 60, 240, White);
		draw_rectangle(2, 280, 38, 236, Red);
		draw_rectangle(3, 281, 36, 234, Red);
		GUI_Text(100, 290, (uint8_t *) "Reset", Red, White);
	}
}

void refresh_age(void){
	char time_in_char[64] = "";
	sprintf(time_in_char, "Age: %02d : %02d : %02d", hr, min, sec);
	GUI_Text(60, 10, (uint8_t *) time_in_char, Black, White);
}

void refresh_bars(){
	int i = 0;
	
	draw_rectangle_color(33, 47, 30, 70, Black);
	draw_rectangle_color(140, 47, 30, 70, Black);
	
	for(i = 0; i < happiness; i++) {
		uint8_t x_start = 35 + (i*14);
		draw_rectangle_color(x_start, 49, 26, 10, White);
	}
	
	for(i = 0; i < satiety; i++) {
		uint8_t x_start = 142 + (i*14);
		draw_rectangle_color(x_start, 49, 26, 10, White);
	}
	
	GUI_Text(30, 30, (uint8_t *) "Happiness", Black, White);
	GUI_Text(150, 30, (uint8_t *) "Satiety", Black, White);
	
}

uint8_t check_arrived(void) {
	if (current_y == destination_y && current_x == destination_x) {
		return 1;
	} else {
		return 0;
	}
}

void check_state(void){
	// 0 is normal
	// 1 eating meal
	// 2 eating snack
	// 3 going to meal
	// 4 going to snack
	// 5 going to offpoint
	// 6 left
	// 9 restart

	if (state == StateEatingMeal || state == StateEatingSnack) {
		state = StateNormal;
		clear_meal(4, 45);
		clear_snack(35, 45);
		joystick_flag = 0;
	}

	if (state == StateGoingMeal && check_arrived()) {
		state = StateEatingMeal;
	}
	
	if (state == StateGoingSnack && check_arrived()) {
		state = StateEatingSnack;
	}

	if (state == StateGoingOffpoint && check_arrived()) {
		state = StateLeft;
	}
	
	// if we lost him we lost him
	if ((happiness == 0 || satiety == 0) && state == StateNormal){
		state = StateGoingOffpoint;
	}

	if (joystick_flag == 1 && state == StateNormal) {
		state = StateGoingMeal;
	}

	if (joystick_flag == 2 && state == StateNormal) {
		state = StateGoingSnack;
	}
}

void process_state(void) {
	if (state == StateNormal) {
		sec++;
	
		happiness_counter++;
		satiety_counter++;
	
		if (sec == 60){
			min++;
			sec = 0;
		}
	
		if (min == 60){
			hr++;
			min = 0;
		}
	
		if (happiness_counter > 4){
			happiness--;
			happiness_counter = 0;
		}
		
		if (satiety_counter > 4){
			satiety--;
			satiety_counter = 0;
		}

		refresh_age();
		refresh_menu(menu_selection, 0);
		refresh_bars();
		evaluate_monster();
	}
	
	if (state == StateEatingMeal){
		if (satiety < 5) {
			satiety++;	
		}
		satiety_counter = 0;
		refresh_bars();
		evaluate_monster();
		draw_meal(4, 45);
		play(PlayTypeFood);
	}
	
	if (state == StateEatingSnack){
		if (happiness < 5) {
			happiness++;
		}
		happiness_counter = 0;
		refresh_bars();
		evaluate_monster();
		draw_snack(35, 45);
		play(PlayTypeFood);
	}
	
	if (state == StateGoingMeal){
		destination_x = 2;
		destination_y = 36;
		evaluate_monster();
		draw_meal(4, 45);
	}
	
	if (state == StateGoingSnack){
		destination_x = 26;
		destination_y = 36;
		evaluate_monster();
		draw_snack(35, 45);
	}
	
	if (state == StateGoingOffpoint){
		destination_x = 50;
		destination_y = 32;
		evaluate_monster();
	}
	
	if (state == StateLeft){
		disable_timer(0);
		GUI_Text(60, 140, (uint8_t*) "Hey, I LEFT!", Black, White);
		refresh_menu(menu_selection, 1);
		refresh_age();
		play(PlayTypeLeave);
	}
	
	if (state == StateCuddle2) {
		sec++;
	
		satiety_counter++;
	
		if (sec == 60){
			min++;
			sec = 0;
		}
	
		if (min == 60){
			hr++;
			min = 0;
		}

		refresh_age();
		cuddle_monster(5);
		
		if (happiness < 5) {
			happiness++;
		}
		happiness_counter = 0;
		
		state = StateNormal;
	}
	
	if (state == StateCuddle1) {
		sec++;
	
		happiness_counter++;
		satiety_counter++;
	
		if (sec == 60){
			min++;
			sec = 0;
		}
	
		if (min == 60){
			hr++;
			min = 0;
		}

		refresh_age();
		cuddle_monster(4);
		play(PlayTypeCuddle);
		state = StateCuddle2;
	}

	if (state == StateRestart) {
		destination_x = 10;
		destination_y = 30;
		current_x = 10;
		current_y = 30;
		happiness = 5;
		satiety = 5;
		sec = 0;
		min = 0;
		hr = 0;
		happiness_counter = 0;
		satiety_counter = 0;
		joystick_flag = 0;
		init_graphics();
		refresh_age();
		refresh_menu(menu_selection, 0);
		refresh_bars();
		evaluate_monster();
		state = StateNormal;
	}
}

void timer_tick(void){
	check_state();
	process_state();
}

void init_LCD(void)
{
	LCD_Initialization();
	srand(42);
}

void evalutateTouchScreen(Coordinate *display) {
	if (display->x > (current_x*5) && display->x < (current_x*5 + (24*5)) && display->y > (current_y * 5) && display->y < (current_y*5 + (20*5))) {
		state = StateCuddle1;
	}
	display->x = 0;
	display->y = 0;
}
