/*
 * Copyright (C) 2016 Emeric Poupon
 *
 * This file is part of LMS.
 *
 * LMS is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * LMS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with LMS.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <boost/filesystem/path.hpp>

#include "database/Types.hpp"
#include "FeatureExtractor.hpp"

namespace Feature {

class Store
{
	public:
		Store(const Store&) = delete;
		Store& operator=(const Store&) = delete;

		static Store& instance();

		bool	exists(Wt::Dbo::Session& session, Database::Track::id_type trackId, std::string type);
		bool	get(Wt::Dbo::Session& session, Database::Track::id_type trackId, std::string type, Type& feature);

		bool	set(Wt::Dbo::Session& session, Database::Track::id_type trackId, std::string type, const Type& feature);

		void reload();
	private:
		Store();

		boost::filesystem::path	_storePath;
};

} // namespace CoverArt
