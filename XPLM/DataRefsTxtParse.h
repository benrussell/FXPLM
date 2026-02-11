/*
 * FXPLM - A re-impl of the X-Plane XPLM layer.
 * Copyright (C) 2024-2026 Ben Russell - br@x-plugins.com
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <https://www.gnu.org/licenses/>.
 */

//
// Created by br on 11/06/25.
//

#ifndef DATAREFSTXTPARSE_H
#define DATAREFSTXTPARSE_H


#include <vector>
#include <string>


struct DataRefsTxtLine {
    std::string name;
    std::string type;
    std::string writable;
    std::string units;
    std::string comment;
};


class DataRefsTxtParse {
public:
    std::vector<DataRefsTxtLine> m_recs;

    void load_and_filter_drefs(const std::string& filename);

	explicit DataRefsTxtParse(const char* filename);
};


#endif //DATAREFSTXTPARSE_H
