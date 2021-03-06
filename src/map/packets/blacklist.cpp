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

#include "../../common/socket.h"

#include "blacklist.h"
#include "../entities/charentity.h"

CBlacklistPacket::CBlacklistPacket(uint32 accid, const int8* targetName, int8 action)
{
	this->type = 0x42;
	this->size = 0x0E;

	switch (action)
	{
	case 0x00: // Added successfully..
	case 0x01: // Removed successfully..
		WBUFL(data, 0x04 - 4) = accid;
		WBUFB(data, 0x18 - 4) = action;
		memcpy(data + 0x08 - 4, targetName, strlen(targetName));
		break;

	case 0x02: // Command error..
		WBUFL(data, 0x04 - 4) = 0x00000000;
		WBUFB(data, 0x18 - 4) = action;
		break;
	}
}
