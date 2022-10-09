/*

	PROJECT:		mod_sa
	LICENSE:		See LICENSE in the top level directory
	COPYRIGHT:		Copyright we_sux, BlastHack

	mod_sa is available from https://github.com/BlastHackNet/mod_
	_sa/

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





HINSTANCE	     g_hOrigDll = NULL;
HMODULE			 g_hDllModule = NULL;
char			 g_szWorkingDirectory[MAX_PATH];

uint32_t		 g_dwSAMP_Addr = NULL;


CGameSA*         pGameInterface = NULL;
CPools*          pPools = NULL;
CPed*            pPedSelf = NULL;
CPedSAInterface* pPedSelfSA = NULL;




BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	static CCallHook* mhook;
	switch (ul_reason_for_call) {
	case DLL_PROCESS_ATTACH:
	{
		mhook = new CCallHook((void*)0x00748DA3, eSafeCall(sc_registers | sc_flags), 6);
		mhook->enable(mainloop);
		DisableThreadLibraryCalls(hModule);
		g_hDllModule = hModule;
		break;
	}
	}
	return true;
}
