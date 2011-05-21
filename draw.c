/* One Astronaut: draw.c
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

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

#include "draw.h"
#include "one_astronaut.h"

void draw()
{
    char fps_string[64];

    al_clear_to_color(al_map_rgb(0, 0, 0));

    sprintf(fps_string, "%.2f fps", fps);
    al_draw_text(main_font, al_map_rgb(0xff, 0xff, 0xff),
        al_get_display_width(display), 0,
        ALLEGRO_ALIGN_RIGHT, fps_string);

    al_flip_display();
}

// vim: fdm=syntax fo=croql et sw=4 sts=4 ts=8

