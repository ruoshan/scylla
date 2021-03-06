/*
 * Copyright 2015 ScyllaDB
 */

/*
 * This file is part of Scylla.
 *
 * Scylla is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Scylla is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Scylla.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <boost/asio/ip/address_v4.hpp>
#include <sys/socket.h>
#include "core/sstring.hh"
#include "core/future.hh"
#include "dns.hh"


namespace dns {

future<hostent> gethostbyname(sstring name) {
    hostent e = {name, {}, address_family::INET};
    host_addr a;
    if (name == "localhost") {
        a.in.s_addr = static_cast<in_addr_t>(boost::asio::ip::address_v4::loopback().to_ulong());
    } else {
        a.in.s_addr = static_cast<in_addr_t>(boost::asio::ip::address_v4::from_string(name).to_ulong());
    }
    e.addresses.push_back(std::move(a));
    return make_ready_future<hostent>(std::move(e));
}

}
