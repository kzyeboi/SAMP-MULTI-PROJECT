/*

	PROJECT:		mod_sa
	LICENSE:		See LICENSE in the top level directory
	COPYRIGHT:		Copyright we_sux, BlastHack

	mod_sa is available from https://github.com/BlastH1ckNet/mod_s0b1it_sa/

	mod_sa is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	mod_sa is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.
	
	You should have received a copy of the GNU General Public License
	along with mod_sa.  If not, see <http://www.gnu.org/licenses/>.

*/

#include "main.h"



bool OnSendRPC(int uniqueID, BitStream* parameters, PacketPriority priority, PacketReliability reliability, char orderingChannel, bool shiftTimestamp)
{
	if (set.netPatchAssoc[uniqueID][OUTCOMING_RPC] != nullptr && set.netPatchAssoc[uniqueID][OUTCOMING_RPC]->enabled)
		return false;

	return true;
}

bool OnSendPacket(BitStream* parameters, PacketPriority priority, PacketReliability reliability, char orderingChannel)
{

	uint8_t packetId;
	parameters->Read(packetId);
	if (set.netPatchAssoc[packetId][OUTCOMING_PACKET] != nullptr && set.netPatchAssoc[packetId][OUTCOMING_PACKET]->enabled)
		return false;

	return true;
}

bool OnReceivePacket(Packet* p)
{
	if (p->data == nullptr || p->length == 0)
		return true;
	
	if (set.netPatchAssoc[p->data[0]][INCOMING_PACKET] != nullptr && set.netPatchAssoc[p->data[0]][INCOMING_PACKET]->enabled)
		return false;

	return true;
}


float vect2_dist(float* point1, float* point2)
{
	return sqrt(pow(point1[0] - point2[0], 2) + pow(point1[1] - point2[1], 2));
}





