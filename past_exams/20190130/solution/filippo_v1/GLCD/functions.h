
#ifndef __FUNCTIONS_H 
#define __FUNCTIONS_H

#include "LPC17xx.h"
#include "GLCD.h"
#include "../timer/timer.h"
#include "stdlib.h"
#include "../music/music_play.h"
#include "../TouchPanel/TouchPanel.h"

void init_LCD(void);
void timer_tick(void);
void evalutateTouchScreen(Coordinate *display);
// uint8_t random_int_ranged(uint8_t lower, uint8_t upper, uint8_t exclude);

static uint8_t destination_x = 10;
static uint8_t destination_y = 30;
volatile static uint8_t current_x = 10;
volatile static uint8_t current_y = 30;
static uint8_t side = 1;

static uint16_t charm[6][20][24] = {
{
    { Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank },
    { Blank, Blank, Blank, Blank, Black, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Black, Black, Black, Blank, Blank, Blank, Blank, Blank },
    { Blank, Blank, Blank, Black, Red, Black, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Black, Orange, Orange, Orange, Black, Blank, Blank, Blank, Blank },
    { Blank, Blank, Black, Red, Red, Black, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Black, Orange, Orange, Orange, Orange, Orange, Black, Blank, Blank, Blank },
    { Blank, Blank, Black, Red, Red, Black, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Black, Orange, Orange, Orange, Orange, Orange, Black, Blank, Blank, Blank },
    { Blank, Black, Red, Red, Red, Red, Black, Blank, Blank, Blank, Blank, Blank, Blank, Black, Orange, Orange, Orange, Orange, Orange, Orange, Orange, Black, Blank, Blank },
    { Blank, Black, Red, Yellow, Red, Red, Black, Blank, Blank, Blank, Blank, Blank, Blank, Black, Orange, Orange, Black, Blank, Orange, Orange, Orange, Orange, Black, Blank },
    { Blank, Black, Red, Yellow, Yellow, Red, Black, Blank, Blank, Blank, Blank, Blank, Black, Orange, Orange, Orange, Black, Black, Orange, Orange, Orange, Orange, Black, Blank },
    { Blank, Blank, Black, Black, Yellow, Black, Blank, Blank, Blank, Blank, Blank, Blank, Black, Orange, Orange, Orange, Black, Black, Orange, Orange, Orange, Orange, Black, Blank },
    { Blank, Blank, Blank, Black, Orange, Black, Blank, Blank, Blank, Blank, Blank, Black, Orange, Orange, Orange, Orange, Orange, Orange, Orange, Orange, Orange, Black, Blank, Blank },
    { Blank, Blank, Blank, Black, Orange, Orange, Black, Blank, Blank, Blank, Black, Orange, Orange, Orange, Orange, Orange, Orange, Orange, Orange, Black, Black, Blank, Blank, Blank },
    { Blank, Blank, Blank, Blank, Black, Orange, Orange, Black, Black, Black, Black, Orange, Orange, Black, Orange, Orange, Black, Black, Black, Blank, Blank, Blank, Blank, Blank },
    { Blank, Blank, Blank, Blank, Black, Orange, Orange, Orange, Black, Orange, Orange, Orange, Orange, Orange, Black, Yellow, Yellow, Black, Blank, Blank, Blank, Blank, Blank, Blank },
    { Blank, Blank, Blank, Blank, Blank, Black, Orange, Orange, Black, Orange, Orange, Orange, Black, Black, Yellow, Yellow, Yellow, Black, Blank, Blank, Blank, Blank, Blank, Blank },
    { Blank, Blank, Blank, Blank, Blank, Blank, Black, Black, Black, Orange, Orange, Orange, Orange, Yellow, Yellow, Yellow, Black, Blank, Black, Blank, Blank, Blank, Blank, Blank },
    { Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Black, Black, Orange, Orange, Orange, Yellow, Yellow, Black, Black, Black, Blank, Blank, Blank, Blank, Blank, Blank },
    { Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Black, Black, Orange, Black, Black, Black, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank },
    { Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Black, Blank, Orange, Blank, Black, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank },
    { Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Black, Black, Black, Black, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank },
    { Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank }
},{
    { Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank },
    { Blank, Blank, Blank, Blank, Blank, Black, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Black, Black, Black, Blank, Blank, Blank, Blank, Blank, Blank, Blank },
    { Blank, Blank, Blank, Blank, Black, Yellow, Black, Blank, Blank, Blank, Blank, Blank, Blank, Black, Orange, Orange, Orange, Black, Blank, Blank, Blank, Blank, Blank, Blank },
    { Blank, Blank, Blank, Blank, Black, Red, Red, Black, Blank, Blank, Blank, Blank, Black, Orange, Orange, Orange, Orange, Orange, Black, Blank, Blank, Blank, Blank, Blank },
    { Blank, Blank, Blank, Blank, Black, Red, Red, Black, Blank, Blank, Blank, Blank, Black, Orange, Orange, Orange, Orange, Orange, Black, Blank, Blank, Blank, Blank, Blank },
    { Blank, Blank, Blank, Black, Red, Red, Red, Red, Black, Blank, Blank, Black, Orange, Orange, Orange, Orange, Orange, Orange, Orange, Black, Blank, Blank, Blank, Blank },
    { Blank, Blank, Blank, Black, Red, Red, Yellow, Red, Black, Blank, Blank, Black, Orange, Orange, Black, Black, Orange, Orange, Orange, Orange, Black, Blank, Blank, Blank },
    { Blank, Blank, Blank, Black, Red, Yellow, Yellow, Red, Black, Blank, Black, Orange, Orange, Orange, Blank, Black, Orange, Orange, Orange, Orange, Black, Blank, Blank, Blank },
    { Blank, Blank, Blank, Blank, Black, Yellow, Black, Black, Blank, Blank, Black, Orange, Orange, Orange, Black, Black, Orange, Orange, Orange, Orange, Black, Blank, Blank, Blank },
    { Blank, Blank, Blank, Blank, Black, Orange, Black, Blank, Blank, Blank, Orange, Orange, Orange, Orange, Orange, Orange, Orange, Orange, Orange, Black, Blank, Blank, Blank, Blank },
    { Blank, Blank, Blank, Blank, Black, Orange, Orange, Black, Blank, Black, Orange, Orange, Orange, Orange, Orange, Orange, Orange, Black, Black, Blank, Blank, Blank, Blank, Blank },
    { Blank, Blank, Blank, Blank, Blank, Black, Orange, Orange, Black, Black, Orange, Orange, Black, Orange, Orange, Black, Black, Black, Blank, Blank, Blank, Blank, Blank, Blank },
    { Blank, Blank, Blank, Blank, Blank, Black, Orange, Orange, Orange, Orange, Orange, Orange, Black, Orange, Yellow, Yellow, Black, Blank, Blank, Blank, Blank, Blank, Blank, Blank },
    { Blank, Blank, Blank, Blank, Blank, Blank, Black, Orange, Orange, Orange, Orange, Black, Black, Yellow, Yellow, Yellow, Black, Blank, Blank, Blank, Blank, Blank, Blank, Blank },
    { Blank, Blank, Blank, Blank, Blank, Blank, Blank, Black, Orange, Orange, Orange, Orange, Yellow, Yellow, Yellow, Yellow, Black, Blank, Blank, Blank, Blank, Blank, Blank, Blank },
    { Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Black, Orange, Orange, Orange, Yellow, Yellow, Yellow, Orange, Black, Blank, Blank, Blank, Blank, Blank, Blank, Blank },
    { Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Black, Black, Orange, Black, Black, Black, Yellow, Black, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank },
    { Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Black, Blank, Orange, Blank, Black, Black, Black, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank },
    { Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Black, Black, Black, Black, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank },
    { Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank }
}, {
    { Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank },
    { Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Black, Black, Black, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Black, Blank, Blank, Blank, Blank, Blank },
    { Blank, Blank, Blank, Blank, Blank, Blank, Blank, Black, Orange, Orange, Orange, Black, Blank, Blank, Blank, Blank, Blank, Black, Yellow, Black, Blank, Blank, Blank, Blank },
    { Blank, Blank, Blank, Blank, Blank, Blank, Black, Orange, Orange, Orange, Orange, Orange, Black, Blank, Blank, Blank, Black, Red, Red, Black, Blank, Blank, Blank, Blank },
    { Blank, Blank, Blank, Blank, Blank, Blank, Black, Orange, Orange, Orange, Orange, Orange, Black, Blank, Blank, Blank, Black, Red, Red, Black, Blank, Blank, Blank, Blank },
    { Blank, Blank, Blank, Blank, Blank, Black, Orange, Orange, Orange, Orange, Orange, Orange, Orange, Black, Blank, Black, Red, Red, Red, Red, Black, Blank, Blank, Blank },
    { Blank, Blank, Blank, Blank, Black, Orange, Orange, Orange, Orange, Black, Black, Orange, Orange, Black, Blank, Black, Red, Yellow, Red, Red, Black, Blank, Blank, Blank },
    { Blank, Blank, Blank, Blank, Black, Orange, Orange, Orange, Orange, Black, Black, Orange, Orange, Orange, Black, Black, Red, Yellow, Yellow, Red, Black, Blank, Blank, Blank },
    { Blank, Blank, Blank, Blank, Black, Orange, Orange, Orange, Orange, Blank, Black, Orange, Orange, Orange, Black, Blank, Black, Black, Yellow, Black, Blank, Blank, Blank, Blank },
    { Blank, Blank, Blank, Blank, Blank, Black, Orange, Orange, Orange, Orange, Orange, Orange, Orange, Orange, Orange, Blank, Blank, Black, Orange, Black, Blank, Blank, Blank, Blank },
    { Blank, Blank, Blank, Blank, Blank, Blank, Black, Black, Orange, Orange, Orange, Orange, Orange, Orange, Orange, Black, Blank, Orange, Orange, Black, Blank, Blank, Blank, Blank },
    { Blank, Blank, Blank, Blank, Blank, Blank, Blank, Black, Black, Black, Orange, Orange, Black, Orange, Orange, Black, Black, Orange, Orange, Black, Blank, Blank, Blank, Blank },
    { Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Black, Yellow, Yellow, Black, Orange, Orange, Orange, Orange, Orange, Orange, Orange, Black, Blank, Blank, Blank, Blank },
    { Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Black, Yellow, Yellow, Yellow, Black, Black, Orange, Orange, Orange, Orange, Black, Blank, Blank, Blank, Blank, Blank },
    { Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Black, Yellow, Yellow, Yellow, Yellow, Orange, Orange, Orange, Orange, Black, Blank, Blank, Blank, Blank, Blank, Blank },
    { Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Black, Blank, Yellow, Yellow, Yellow, Orange, Orange, Orange, Black, Blank, Blank, Blank, Blank, Blank, Blank, Blank },
    { Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Black, Yellow, Black, Black, Black, Orange, Black, Black, Blank, Blank, Blank, Blank, Blank, Blank, Blank },
    { Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Black, Black, Black, Blank, Orange, Blank, Black, Blank, Blank, Blank, Blank, Blank, Blank, Blank },
    { Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Black, Black, Black, Black, Blank, Blank, Blank, Blank, Blank, Blank, Blank },
    { Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank }
}, {
    { Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank },
    { Blank, Blank, Blank, Blank, Blank, Blank, Black, Black, Black, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Black, Blank, Blank, Blank, Blank },
    { Blank, Blank, Blank, Blank, Blank, Black, Orange, Orange, Orange, Black, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Black, Red, Black, Blank, Blank, Blank },
    { Blank, Blank, Blank, Blank, Black, Orange, Orange, Orange, Orange, Orange, Black, Blank, Blank, Blank, Blank, Blank, Blank, Black, Red, Red, Black, Blank, Blank, Blank },
    { Blank, Blank, Blank, Blank, Black, Orange, Orange, Orange, Orange, Orange, Black, Blank, Blank, Blank, Blank, Blank, Blank, Black, Red, Red, Black, Blank, Blank, Blank },
    { Blank, Blank, Blank, Black, Orange, Orange, Orange, Orange, Orange, Orange, Orange, Black, Blank, Blank, Blank, Blank, Black, Red, Red, Red, Red, Black, Blank, Blank },
    { Blank, Blank, Black, Orange, Orange, Orange, Orange, Black, Black, Orange, Orange, Black, Blank, Blank, Blank, Blank, Black, Red, Yellow, Red, Red, Black, Blank, Blank },
    { Blank, Blank, Black, Orange, Orange, Orange, Orange, Black, Blank, Orange, Orange, Orange, Black, Blank, Blank, Blank, Black, Red, Yellow, Yellow, Red, Black, Blank, Blank },
    { Blank, Blank, Black, Orange, Orange, Orange, Orange, Black, Black, Orange, Orange, Orange, Black, Blank, Blank, Blank, Blank, Black, Black, Yellow, Black, Blank, Blank, Blank },
    { Blank, Blank, Blank, Black, Orange, Orange, Orange, Orange, Orange, Orange, Orange, Orange, Orange, Black, Blank, Blank, Blank, Blank, Black, Orange, Black, Blank, Blank, Blank },
    { Blank, Blank, Blank, Blank, Black, Black, Orange, Orange, Orange, Orange, Orange, Orange, Orange, Orange, Black, Blank, Blank, Black, Orange, Orange, Black, Blank, Blank, Blank },
    { Blank, Blank, Blank, Blank, Blank, Blank, Black, Black, Black, Orange, Orange, Black, Orange, Orange, Black, Black, Black, Black, Orange, Orange, Black, Blank, Blank, Blank },
    { Blank, Blank, Blank, Blank, Blank, Blank, Blank, Black, Yellow, Yellow, Black, Orange, Orange, Orange, Orange, Orange, Black, Orange, Orange, Orange, Black, Blank, Blank, Blank },
    { Blank, Blank, Blank, Blank, Blank, Blank, Blank, Black, Yellow, Yellow, Yellow, Black, Black, Orange, Orange, Orange, Black, Orange, Orange, Black, Blank, Blank, Blank, Blank },
    { Blank, Blank, Blank, Blank, Blank, Blank, Black, Blank, Black, Yellow, Yellow, Yellow, Orange, Orange, Orange, Orange, Black, Black, Black, Blank, Blank, Blank, Blank, Blank },
    { Blank, Blank, Blank, Blank, Blank, Blank, Blank, Black, Black, Black, Yellow, Yellow, Orange, Orange, Orange, Black, Black, Blank, Blank, Blank, Blank, Blank, Blank, Blank },
    { Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Black, Black, Black, Orange, Black, Black, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank },
    { Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Black, Blank, Orange, Blank, Black, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank },
    { Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Black, Black, Black, Black, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank },
    { Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank, Blank }
}, {
    { White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White},
    { White, White, White, White, White, White, White, White, Black, Black, White, Black, Black, White, White, White, White, White, White, White, White, White, White, White},
    { White, White, White, White, Black, White, White, Black, Pink, Pink, Black, Pink, Pink, Black, White, White, Black, Black, Black, White, White, White, White, White},
    { White, White, White, Black, Red, Black, White, Black, Pink, Pink, Pink, Pink, Pink, Black, White, Black, Orange, Orange, Orange, Black, White, White, White, White},
    { White, White, Black, Red, Red, Black, White, White, Black, Pink, Pink, Pink, Black, White, Black, Orange, Orange, Orange, Orange, Orange, Black, White, White, White},
    { White, White, Black, Red, Red, Black, White, White, White, Black, Pink, Black, White, White, Black, Orange, Orange, Orange, Orange, Orange, Black, White, White, White},
    { White, Black, Red, Red, Red, Red, Black, White, White, White, Black, White, White, Black, Orange, Orange, Orange, Orange, Orange, Orange, Orange, Black, White, White},
    { White, Black, Red, Yellow, Red, Red, Black, White, White, White, White, White, White, Black, Orange, Orange, White, Black, Orange, Orange, Orange, Orange, Black, White},
    { White, Black, Red, Yellow, Yellow, Red, Black, White, White, White, White, White, Black, Orange, Orange, Orange, Black, Black, Orange, Orange, Orange, Orange, Black, White},
    { White, White, Black, Black, Yellow, Black, White, White, White, White, White, White, Black, Orange, Orange, Orange, Black, Black, Orange, Orange, Orange, Orange, Black, White},
    { White, White, White, Black, Orange, Black, White, White, White, White, White, Black, Orange, Orange, Orange, Orange, Orange, Orange, Orange, Orange, Orange, Black, White, White},
    { White, White, White, Black, Orange, Orange, Black, White, White, White, Black, Orange, Orange, Orange, Orange, Orange, Orange, Orange, Orange, Black, Black, White, White, White},
    { White, White, White, White, Black, Orange, Orange, Black, Black, Black, Black, Orange, Orange, Black, Orange, Orange, Black, Black, Black, White, White, White, White, White},
    { White, White, White, White, Black, Orange, Orange, Orange, Black, Orange, Orange, Orange, Orange, Orange, Black, Yellow, Yellow, Black, White, White, White, White, White, White},
    { White, White, White, White, White, Black, Orange, Orange, Black, Orange, Orange, Orange, Black, Black, Yellow, Yellow, Yellow, Black, White, White, White, White, White, White},
    { White, White, White, White, White, White, Black, Black, Black, Orange, Orange, Orange, Orange, Yellow, Yellow, Yellow, Black, White, Black, White, White, White, White, White},
    { White, White, White, White, White, White, White, White, Black, Black, Orange, Orange, Orange, Yellow, Yellow, Black, Black, Black, White, White, White, White, White, White},
    { White, White, White, White, White, White, White, White, White, Black, Black, Orange, Black, Black, Black, White, White, White, White, White, White, White, White, White},
    { White, White, White, White, White, White, White, White, White, Black, White, Orange, White, Black, White, White, White, White, White, White, White, White, White, White},
    { White, White, White, White, White, White, White, White, White, Black, Black, Black, Black, White, White, White, White, White, White, White, White, White, White, White}
}, {
    { White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White},
    { White, White, Red, Red, White, Red, Red, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White},
    { White, Red, Orange, Orange, Red, Orange, Orange, Red, White, White, White, Black, Black, Black, White, White, White, White, White, White, White, Black, White, White},
    { White, Red, Orange, Orange, Orange, Orange, Orange, Red, White, White, Black, Orange, Orange, Orange, Black, White, White, White, White, White, Black, Yellow, Black, White},
    { White, White, Red, Orange, Orange, Orange, Red, White, White, Black, Orange, Orange, Orange, Orange, Orange, Black, White, White, White, Black, Red, Red, Black, White},
    { White, White, White, Red, Orange, Red, White, White, White, Black, Orange, Orange, Orange, Orange, Orange, Black, White, White, White, Black, Red, Red, Black, White},
    { White, White, White, White, Red, White, White, White, Black, Orange, Orange, Orange, Orange, Orange, Orange, Orange, Black, White, Black, Red, Red, Red, Red, Black},
    { White, White, White, White, White, White, White, Black, Orange, Orange, Orange, Orange, Black, Black, Orange, Orange, Black, White, Black, Red, Yellow, Red, Red, Black},
    { White, White, White, White, White, White, White, Black, Orange, Orange, Orange, Orange, Black, Black, Orange, Orange, Orange, Black, Black, Red, Yellow, Yellow, Red, Black},
    { White, White, White, White, White, White, White, Black, Orange, Orange, Orange, Orange, White, Black, Orange, Orange, Orange, Black, White, Black, Black, Yellow, Black, White},
    { White, White, White, White, White, White, White, White, Black, Orange, Orange, Orange, Orange, Orange, Orange, Orange, Orange, Orange, White, White, Black, Orange, Black, White},
    { White, White, White, White, White, White, White, White, White, Black, Black, Orange, Orange, Orange, Orange, Orange, Orange, Orange, Black, White, Orange, Orange, Black, White},
    { White, White, White, Black, Black, White, Black, Black, White, White, Black, Black, Black, Orange, Orange, Black, Orange, Orange, Black, Black, Orange, Orange, Black, White},
    { White, White, Black, Pink, Pink, Black, Pink, Pink, Black, White, White, Black, Yellow, Yellow, Black, Orange, Orange, Orange, Orange, Orange, Orange, Orange, Black, White},
    { White, White, Black, Pink, Pink, Pink, Pink, Pink, Black, White, White, Black, Yellow, Yellow, Yellow, Black, Black, Orange, Orange, Orange, Orange, Black, White, White},
    { White, White, White, Black, Pink, Pink, Pink, Black, White, White, White, Black, Yellow, Yellow, Yellow, Yellow, Orange, Orange, Orange, Orange, Black, White, White, White},
    { White, White, White, White, Black, Pink, Black, White, White, White, White, Black, White, Yellow, Yellow, Yellow, Orange, Orange, Orange, Black, White, White, White, White},
    { White, White, White, White, White, Black, White, White, White, White, White, White, Black, Yellow, Black, Black, Black, Orange, Black, Black, White, White, White, White},
    { White, White, White, White, White, White, White, White, White, White, White, White, White, Black, Black, Black, White, Orange, White, Black, White, White, White, White},
    { White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, Black, Black, Black, Black, White, White, White, White}
}};

static uint16_t volume_base[18][10] = {
    { White, White, White, White, White, White, White, White, White, Black},
    { White, White, White, White, White, White, White, White, Black, Black},
    { White, White, White, White, White, White, Black, Black, Black, Black},
    { White, White, White, Black, Black, Black, Black, Black, Black, Black},
    { Black, Black, Black, Black, Black, Black, Black, Black, Black, Black},
    { Black, Black, Black, Black, Black, Black, Black, Black, Black, Black},
    { Black, Black, Black, Black, Black, Black, Black, Black, Black, Black},
    { Black, Black, Black, Black, Black, Black, Black, Black, Black, Black},
    { Black, Black, Black, Black, Black, Black, Black, Black, Black, Black},
    { Black, Black, Black, Black, Black, Black, Black, Black, Black, Black},
    { Black, Black, Black, Black, Black, Black, Black, Black, Black, Black},
    { Black, Black, Black, Black, Black, Black, Black, Black, Black, Black},
    { Black, Black, Black, Black, Black, Black, Black, Black, Black, Black},
    { Black, Black, Black, Black, Black, Black, Black, Black, Black, Black},
    { White, White, White, Black, Black, Black, Black, Black, Black, Black},
    { White, White, White, White, White, White, Black, Black, Black, Black},
    { White, White, White, White, White, White, White, White, Black, Black},
    { White, White, White, White, White, White, White, White, White, Black}
};

static uint16_t volume_level[16][3] = {
    { Black, Black, White},
    { White, Black, Black},
    { White, Black, Black},
    { White, Black, Black},
    { White, Black, Black},
    { White, Black, Black},
    { White, Black, Black},
    { White, Black, Black},
    { White, Black, Black},
    { White, Black, Black},
    { White, Black, Black},
    { White, Black, Black},
    { White, Black, Black},
    { White, Black, Black},
    { White, Black, Black},
    { Black, Black, White}
};

static uint16_t meal[5][5] = {
    {Blank, Brown, Brown, Brown, Blank },
    {Brown, Brown, Yellow, Brown, Brown },
    {Blank, Cyan, Cyan, Cyan, Blank },
    {Brown, Brown, Brown, Brown, Brown },
    {Blank, Brown, Brown, Brown, Blank }
};

static uint16_t snack[5][6] = {
    {Blank, Blank, Black, Black, Blank, Blank },
    {Blank, Black, Brown, Brown, Black, Blank },
    {Black, Brown, Black, Brown, Brown, Black },
    {Blank, Black, Brown, Brown, Black, Blank },
    {Blank, Blank, Black, Black, Blank, Blank },
};

typedef enum stateType {
    StateNormal = 0,
    StateEatingMeal = 1,
    StateEatingSnack = 2,
    StateGoingMeal = 3,
    StateGoingSnack = 4,
    StateGoingOffpoint = 5,
    StateLeft = 6,
    StateCuddle1 = 7,
    StateCuddle2 = 8,
    StateRestart = 9
} STATETYPE;



    // 0 is normal
    // 1 eating meal
    // 2 eating snack
    // 3 going to meal
    // 4 going to snack
    // 5 going to offpoint
    // 6 left
    // 9 restart

#endif
