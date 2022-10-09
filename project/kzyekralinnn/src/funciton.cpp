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


struct pool					*pool_actor;
struct pool					*pool_vehicle;

static struct func_state	__func_stateX;
struct func_state			*func_stateX = nullptr;


// the main daddyo
int			m_InitStages = 0;
void main_hook ( HWND wnd )
{

	// install keyhook
	keyhook_maybe_install( wnd );

	/* initialize state */
	if ( func_stateX == nullptr )
	{
		// set default cheat_state variables
		func_stateX = &__func_stateX;

	}	


	func_stateX->state = CHEAT_STATE_NONE;

	/* setup & refresh actor pool */
	pool_actor = *(struct pool **)ACTOR_POOL_POINTER;
	if ( pool_actor == nullptr || pool_actor->start == nullptr || pool_actor->size <= 0 )
		return;

	/* setup & refresh vehicle pool */
	pool_vehicle = *(struct pool **)VEHICLE_POOL_POINTER;
	if ( pool_vehicle == nullptr || pool_vehicle->start == nullptr || pool_vehicle->size <= 0 )
		return;

	//////////////////////////////////////////


	struct actor_info	*actor_info;
	struct vehicle_info *vehicle_info;
	actor_info = actor_info_get( ACTOR_SELF, ACTOR_ALIVE );
	vehicle_info = vehicle_info_get( VEHICLE_SELF, 0 );

		
	if ( vehicle_info == nullptr && actor_info == nullptr )
	{
		
	}
	else
	{
		if ( vehicle_info == nullptr )
		{
			func_stateX->state = CHEAT_STATE_ACTOR;
		}
		else
		{
			func_stateX->state = CHEAT_STATE_VEHICLE;
		}

		if ( m_InitStages == 0 )
		{

			pGameInterface = new CGameSA();
			pPools = pGameInterface->GetPools();

			pPedSelf = pGameInterface->GetPools()->AddPed( (DWORD *)actor_info );
			pPedSelfSA = pPedSelf->GetPedInterface();

			m_InitStages++;
		}
	}

	if (g_SAMP && g_renderSAMP_initSAMPstructs)
	{
		sampMainUpdate();
		
	}

out: ;
	if ( gta_menu_active() )
		keyhook_clear_states();
	else
		keyhook_run();
}

