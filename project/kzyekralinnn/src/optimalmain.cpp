#include "main.h"



void traceLastFunc(const char* szFunc)
{


}

void Log(const char* fmt, ...)
{


}

static int init(void)
{

	
	if (GetModuleFileName(g_hDllModule, g_szWorkingDirectory, sizeof(g_szWorkingDirectory) - 32) != 0)
	{
		if (strrchr(g_szWorkingDirectory, '\\') != NULL)
			*strrchr(g_szWorkingDirectory, '\\') = 0;
		else
			strcpy(g_szWorkingDirectory, ".");
	}
	else
	{
		strcpy(g_szWorkingDirectory, ".");
	}
	
#pragma warning( disable : 4127 )
	if (sizeof(struct vehicle_info) != 2584 || sizeof(struct actor_info) != 1988)
	{
		return 0;
	}

	ini_load();
	getSamp();

	return 1;
}



void __stdcall mainloop()
{
	// get actual d3d9.dll and proxy original D3D9Device
	g_hOrigDll = GetModuleHandle("d3d9.dll");
	if (g_hOrigDll == NULL || g_hOrigDll == INVALID_HANDLE_VALUE)
		return;

	static bool initialize = false;
	if (initialize)
		return;
	initialize = true;



	if (init()) {
		pDirect3D9 = new proxyIDirect3D9(*(IDirect3D9**)0xC97C20);
		*(IDirect3D9**)0xC97C20 = pDirect3D9;
		pPresentParam = *(D3DPRESENT_PARAMETERS*)0xC9C040;
		*(IDirect3DDevice9**)0xC97C28 = new proxyIDirect3DDevice9(*(IDirect3DDevice9**)0xC97C28);
	}



}