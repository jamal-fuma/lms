/*
 * Copyright (C) 2015 Emeric Poupon
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

#ifndef _DB_ARTIST_HPP_
#define _DB_ARTIST_HPP_

#include <string>
#include <vector>

#include <Wt/Dbo/Dbo>
#include <Wt/Dbo/QueryModel>

#include "SearchFilter.hpp"

namespace Database
{

class Track;
class Cluster;
class Release;

class Artist : public Wt::Dbo::Dbo<Artist>
{
	public:

		typedef Wt::Dbo::ptr<Artist> pointer;
		typedef Wt::Dbo::dbo_traits<Artist>::IdType id_type;

		Artist() {}
		Artist(const std::string& name, const std::string& MBID = "");

		// Accessors
		static pointer			getByMBID(Wt::Dbo::Session& session, const std::string& MBID);
		static pointer			getById(Wt::Dbo::Session& session, id_type id);
		static std::vector<pointer>	getByName(Wt::Dbo::Session& session, const std::string& name);
		static std::vector<pointer> 	getByFilter(Wt::Dbo::Session& session,
								const std::set<id_type>& clusters,		// at least one track that belongs to  these clusters
								const std::vector<std::string> keywords,	// name must match all of these keywords
								int offset,
								int size,
								bool& moreExpected);

		static std::vector<pointer>	getAll(Wt::Dbo::Session& session, int offset = -1, int size = -1);
		static std::vector<pointer>	getAllOrphans(Wt::Dbo::Session& session); // No track related

		// Accessors
		std::string getName(void) const { return _name; }
		std::string getMBID(void) const { return _MBID; }

		// Get the releases that have at least one track for this artist + belongs to optonal cluster filters
		std::vector<Wt::Dbo::ptr<Release>>	getReleases(const std::set<id_type>& clusterIds = std::set<id_type>()) const;

		void setMBID(std::string mbid) { _MBID = mbid; }

		// Create
		static pointer create(Wt::Dbo::Session& session, const std::string& name, const std::string& MBID = "");


		template<class Action>
			void persist(Action& a)
			{
				Wt::Dbo::field(a, _name, "name");
				Wt::Dbo::field(a, _MBID, "mbid");

				Wt::Dbo::hasMany(a, _tracks, Wt::Dbo::ManyToOne, "artist");
			}

	private:

		static const std::size_t _maxNameLength = 128;

		std::string _name;
		std::string _MBID;	// Musicbrainz Identifier

		Wt::Dbo::collection<Wt::Dbo::ptr<Track>> _tracks; // Tracks of this artist
};

} // namespace Database

#endif