/*****************************************************************************
 *
 * This file is part of Mapnik (c++ mapping toolkit)
 *
 * Copyright (C) 2012 Artem Pavlenko
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
#ifndef MAPNIK_TEXT_LAYOUT_HPP
#define MAPNIK_TEXT_LAYOUT_HPP

//mapnik
#include <mapnik/text/itemizer.hpp>
#include <mapnik/font_engine_freetype.hpp>
#include <mapnik/text/glyph_info.hpp>
#include <mapnik/text/char_properties_ptr.hpp>

//stl
#include <vector>
#include <list>
#include <map>

//boost
#include <boost/shared_ptr.hpp>

namespace mapnik
{
/** This class stores all glyphs of a line in left to right order.
 *
 * It can be used for rendering but no text processing (like line breaking)
 * should be done!
 */
class text_line
{
public:
    text_line(unsigned first_char, unsigned last_char);

    typedef std::vector<glyph_info> glyph_vector;
    typedef glyph_vector::const_iterator const_iterator;
    /** Get glyph vector. */
    glyph_vector const& glyphs() const { return glyphs_; }
    /** Append glyph. */
    void add_glyph(glyph_info const& glyph, double scale_factor_);

    /** Preallocate memory. */
    void reserve(glyph_vector::size_type length);
    /** Iterator to first glyph. */
    const_iterator begin() const;
    /** Iterator beyond last glyph. */
    const_iterator end() const;

    /** Width of all glyphs including character spacing. */
    double width() const { return width_; }
    /** Real line height. For first line: max_char_height(), for all others: line_height(). */
    double height() const;

    /** Height of the tallest glyph in this line. */
    double max_char_height() const { return max_char_height_; }
    /** Called for each font/style to update the maximum height of this line. */
    void update_max_char_height(double max_char_height);
    /** Line height including line spacing. */
    double line_height() const { return line_height_; }

    /** Is this object is the first line of a multi-line text?
      * Used to exclude linespacing from first line's height. */
    void set_first_line(bool first_line);

    /** Index of first UTF-16 char. */
    unsigned first_char() const;
    /** Index of last UTF-16 char. */
    unsigned last_char() const;

    /** Number of glyphs. */
    unsigned size() const;
private:
    glyph_vector glyphs_;
    double line_height_; //Includes line spacing (returned by freetype)
    double max_char_height_; //Height of 'X' character of the largest font in this run. //TODO: Initialize this!
    double width_;
    unsigned first_char_;
    unsigned last_char_;
    bool first_line_;
};

class text_layout
{
public:
    typedef std::vector<text_line> line_vector;
    typedef line_vector::const_iterator const_iterator;
    text_layout(face_manager_freetype & font_manager, double scale_factor);

    /** Adds a new text part. Call this function repeatedly to build the complete text. */
    void add_text(mapnik::value_unicode_string const& str, char_properties_ptr format);

    /** Returns the complete text stored in this layout.*/
    UnicodeString const& text() const;

    /** Processes the text into a list of glyphs, performing RTL/LTR handling, shaping and line breaking. */
    void layout(double wrap_width, unsigned text_ratio, bool wrap_before);

    /** Clear all data stored in this object. The object's state is the same as directly after construction. */
    void clear();

    // Height of all lines together (in pixels).
    inline double height() const { return height_; }
    // Width of the longest line (in pixels).
    inline double width() const { return width_ ; }

    // Line iterator.
    inline const_iterator begin() const { return lines_.begin(); }
    inline const_iterator end() const { return lines_.end(); }

    // Number of lines.
    inline std::size_t num_lines() const { return lines_.size(); }

    // Width of a certain glyph cluster (in pixels).
    inline double cluster_width(unsigned cluster) const
    {
        std::map<unsigned, double>::const_iterator width_itr = width_map_.find(cluster);
        if (width_itr != width_map_.end()) return width_itr->second;
        return 0;
    }

    // Returns the number of glyphs so memory can be preallocated.
    inline unsigned glyphs_count() const { return glyphs_count_;}

private:
    void break_line(text_line & line, double wrap_width, unsigned text_ratio, bool wrap_before);
    void shape_text(text_line & line);
    void add_line(text_line & line);
    void clear_cluster_widths(unsigned first, unsigned last);

    //input
    face_manager_freetype &font_manager_;
    double scale_factor_;

    //processing
    text_itemizer itemizer_;
    // Maps char index (UTF-16) to width. If multiple glyphs map to the same char the sum of all widths is used
    // note: this probably isn't the best solution. it would be better to have an object for each cluster, but
    // it needs to be implemented with no overhead.
    std::map<unsigned, double> width_map_;
    double width_;
    double height_;
    unsigned glyphs_count_;

    //output
    line_vector lines_;
};
}

#endif // TEXT_LAYOUT_HPP
