/*
 *
 *  Value ranges header for diagnostics for garden.
 *  Copyright (C) 2012 Joshua Schell (joshua.g.schell@gmail.com)
 *
 *  garden is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  garden is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with garden.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef BOUNDS_H_INCLUDED
#define BOUNDS_H_INCLUDED

/* Nutrient Bounds */

/* Values range from 0-10, with 0
   being low, 10 being high, and
   5 being normal.                */

const int NutrientLower = 3;
const int NutrientUpper = 7;

/* Water Level Bounds */

/* Values range from 0-5, with
   0 being empty and 5 being
   full.                       */

const int LevelLower = 1;

/* NB! pH levels use the actual pH scale,
       therefore no constants are required. */

#endif

