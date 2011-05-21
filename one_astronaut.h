/* One Astronaut: one_astronaut.h
 *
 * Copyright (c) 2011 Michael Forney <mforney@mforney.org>
 *
 * This file is a part of One Astronaut.
 *
 * One Astronaut is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2, as published by
 * the Free Software Foundation.
 *
 * One Astronaut is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * One Astronaut.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef ONE_ASTRONAUT_ONE_ASTRONAUT_H
#define ONE_ASTRONAUT_ONE_ASTRONAUT_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>

extern ALLEGRO_DISPLAY * display;
extern ALLEGRO_EVENT_QUEUE * event_queue;
extern ALLEGRO_TIMER * fps_timer;
extern ALLEGRO_FONT * main_font;
extern bool running;
extern double fps;
typedef struct {
    bool a,d,s,w;
    bool space;
} KEYS;
extern KEYS keys;

/**
 * Perform all necessary initialization to run One Astronaut.
 */
void setup();

/**
 * Perform all necessary cleanup prior to exting One Astronaut.
 */
void cleanup();

/**
 * Run One Astronaut, entering the game loop.
 */
void run();

#endif

// vim: fdm=syntax fo=croql et sw=4 sts=4 ts=8

