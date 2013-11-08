/*****************************************************************************
 *
 * This file is part of Mapnik (c++ mapping toolkit)
 *
 * Copyright (C) 2011 Artem Pavlenko
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 *****************************************************************************/

#ifndef MAPNIK_LINE_SYMBOLIZER_HPP
#define MAPNIK_LINE_SYMBOLIZER_HPP

// mapnik
#include <mapnik/color.hpp>
#include <mapnik/config.hpp>
#include <mapnik/stroke.hpp>
#include <mapnik/symbolizer.hpp>
#include <mapnik/enumeration.hpp>

namespace mapnik
{

enum line_rasterizer_enum {
    RASTERIZER_FULL,           // agg::renderer_scanline_aa_solid
    RASTERIZER_FAST,           // agg::rasterizer_outline_aa, twice as fast but only good for thin lines
    line_rasterizer_enum_MAX
};

DEFINE_ENUM( line_rasterizer_e, line_rasterizer_enum );

struct MAPNIK_DECL line_symbolizer : public symbolizer_base {};

}

#endif // MAPNIK_LINE_SYMBOLIZER_HPP
