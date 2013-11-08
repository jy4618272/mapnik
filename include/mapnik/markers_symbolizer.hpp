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

#ifndef MAPNIK_MARKERS_SYMBOLIZER_HPP
#define MAPNIK_MARKERS_SYMBOLIZER_HPP

//mapnik
#include <mapnik/color.hpp>
#include <mapnik/config.hpp>
#include <mapnik/stroke.hpp>
#include <mapnik/symbolizer.hpp>
#include <mapnik/enumeration.hpp>
#include <mapnik/expression.hpp>
#include <mapnik/path_expression.hpp>

// boost
#include <boost/optional.hpp>

namespace mapnik {

// TODO - consider merging with text_symbolizer label_placement_e
enum marker_placement_enum {
    MARKER_POINT_PLACEMENT,
    MARKER_INTERIOR_PLACEMENT,
    MARKER_LINE_PLACEMENT,
    marker_placement_enum_MAX
};

DEFINE_ENUM( marker_placement_e, marker_placement_enum );

enum marker_multi_policy_enum {
    MARKER_EACH_MULTI, // each component in a multi gets its marker
    MARKER_WHOLE_MULTI, // consider all components of a multi as a whole
    MARKER_LARGEST_MULTI, // only the largest component of a multi gets a marker
    marker_multi_policy_enum_MAX
};

DEFINE_ENUM( marker_multi_policy_e, marker_multi_policy_enum );

struct MAPNIK_DECL markers_symbolizer : symbolizer_base {};

}

#endif // MAPNIK_MARKERS_SYMBOLIZER_HPP
