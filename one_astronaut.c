/* One Astronaut: one_astronaut.c
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

#include "one_astronaut.h"
#include "events.h"

ALLEGRO_DISPLAY * display;
ALLEGRO_EVENT_QUEUE * event_queue;
ALLEGRO_TIMER * fps_timer;
ALLEGRO_FONT * main_font;
bool running = true;
double fps = 0;

static int target_fps = 60;

void setup()
{
    al_set_app_name("one_astronaut");
    al_set_org_name("one_astronaut");

    al_init();
    al_init_font_addon();
    al_init_image_addon();
    al_init_ttf_addon();

    main_font = al_load_font("data/fonts/TerminusBold-4.34.ttf", 24, 0);

    event_queue = al_create_event_queue();
    display = al_create_display(800, 600);
    fps_timer = al_create_timer(ALLEGRO_BPS_TO_SECS(target_fps));

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(fps_timer));
}

void cleanup()
{
    al_destroy_timer(fps_timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
}

void run()
{
    ALLEGRO_EVENT event;
    double time;

    time = al_get_time();
    al_start_timer(fps_timer);

    while (running)
    {
        al_wait_for_event(event_queue, &event);

        double new_time = al_get_time();
        fps = 1.0 / (new_time - time);
        time = new_time;

        handle_event(&event);
    }

    al_stop_timer(fps_timer);
}

// vim: fdm=syntax fo=croql et sw=4 sts=4 ts=8

