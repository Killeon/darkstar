/*
===========================================================================

Copyright (c) 2010-2014 Darkstar Dev Teams

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see http://www.gnu.org/licenses/

This file is part of DarkStar-server source code.

===========================================================================
*/

#include "../common/socket.h"
#include <zmq.hpp>
#include "../common/cbasetypes.h"

class CBasicPacket;

namespace chat
{
	enum CHATTYPE
	{
		CHAT_TELL		= 1,
		CHAT_PARTY		= 2,
		CHAT_LINKSHELL	= 3,
		CHAT_YELL		= 4,
		CHAT_SERVMES	= 5,
		CHAT_PT_INVITE	= 6,
		CHAT_PT_RELOAD  = 7,
		CHAT_MSG_DIRECT = 8
	};

	extern zmq::context_t zContext;
	extern zmq::socket_t* zSocket;

	void init(const char* chatIp, uint16 chatPort);

	void listen();
	void parse(CHATTYPE type, zmq::message_t* extra, zmq::message_t* packet);
	void send(CHATTYPE type, void* data, size_t datalen, CBasicPacket* packet);
};