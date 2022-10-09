#include "main.h"









D3DCOLOR RandomColorz()
{
	return D3DCOLOR_ARGB(255, rand() % 256, rand() % 256, rand() % 256);;
}



bool IsVehicleStreamed(uint16_t vehicleID)
{

	if (g_Vehicles->iIsListed[vehicleID] != 1)
		return false;
	if (g_Vehicles->pSAMP_Vehicle[vehicleID] == NULL)
		return false;
	if (g_Vehicles->pSAMP_Vehicle[vehicleID]->pGTA_Vehicle == NULL)
		return false;
	return true;
}

DWORD rainbow()
{

	static float x = 0, y = 0;
	static float r = 1, g = 1, b = 1;

	if (y >= 0.0f && y < 255.0f) {
		r = 255.0f;
		g = 0.0f;
		b = x;
	}
	else if (y >= 255.0f && y < 510.0f) {
		r = 255.0f - x;
		g = 0.0f;
		b = 255.0f;
	}
	else if (y >= 510.0f && y < 765.0f) {
		r = 0.0f;
		g = x;
		b = 255.0f;
	}
	else if (y >= 765.0f && y < 1020.0f) {
		r = 0.0f;
		g = 255.0f;
		b = 255.0f - x;
	}
	else if (y >= 1020.0f && y < 1275.0f) {
		r = x;
		g = 255.0f;
		b = 0.0f;
	}
	else if (y >= 1275.0f && y < 1530.0f) {
		r = 255.0f;
		g = 255.0f - x;
		b = 0.0f;
	}
	// ini set.rainbowdelay
	x += 0.450f;//SECOND: 0.450f First:0.0100f; //
	if (x >= 255.0f)
		x = 0.0f;

	y += 0.450f;//0.0100f; //increase this value to switch colors faster
	if (y > 1530.0f)
		y = 0.0f;


	return D3DCOLOR_ARGB(255, (int)r, (int)g, (int)b);
}

bool IsPlayerConnected(uint16_t playerID)
{
	if (playerID == g_Players->sLocalPlayerID)
		return false;
	if (g_Players == NULL)
		return false;
	if (g_Players->iIsListed[playerID] != 1)
		return false;
	if (g_Players->pRemotePlayer[playerID] == NULL)
		return false;
	return true;
}

float random_float(float a, float b)
{
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
	
	
}

int random_int(int a, int b)
{
	int random = ((int)rand()) / (int)RAND_MAX;
	int diff = b - a;
	int r = random * diff;
	return a + r;


}

float CalculateDamage(void)
{
	WORD gun = g_Players->pLocalPlayer->byteCurrentWeapon;
	float dmg = 0.0f;
	if (gun == 30 || gun == 31) dmg = 9.90000057220458984375f;



	if (gun == 24 || gun == 38) dmg = 46.200000762939453125f;
	if (gun == 22 || gun == 29) dmg = 8.25f;
	if (gun == 23) dmg = 13.200000762939453125f;
	if (gun == 28 || gun == 32) dmg = 6.6000003814697265625f;

	if (gun == 33) dmg = 24.7500019073486328125f;
	if (gun == 34) dmg = 41.25f;
	if (gun == 25 || gun == 26)
	{
		int shotrandom = rand() % 8 + 1;
		switch (shotrandom)
		{
		case 1:
			dmg = 26.4000015258789f;
			break;
		case 2:
			dmg = 29.70000171661377f;
			break;
		case 3:
			dmg = 33.00000190734863f;
			break;
		case 4:
			dmg = 36.30000209808349f;
			break;
		case 5:
			dmg = 39.60000228881836f;
			break;
		case 6:
			dmg = 42.90000247955322f;
			break;
		case 7:
			dmg = 46.20000267028808f;
			break;
		case 8:
			dmg = 49.50000286102295f;
			break;
		}
	}
	if (gun == 27)
	{
		int shotrandom2 = rand() % 4 + 1;
		switch (shotrandom2)
		{
		case 1:
			dmg = 24.75000143051147f;
			break;
		case 2:
			dmg = 29.70000171661376f;
			break;
		case 3:
			dmg = 34.65000200271606f;
			break;
		case 4:
			dmg = 39.60000228881835f;
			break;
		}
	}
	return dmg;
}

bool IsPlayerStreamed(uint16_t playerID)
{
	if (g_Players == NULL)
		return false;
	if (g_Players->iIsListed[playerID] != 1)
		return false;
	if (g_Players->pRemotePlayer[playerID] == NULL)
		return false;
	if (g_Players->pRemotePlayer[playerID]->pPlayerData == NULL)
		return false;
	if (g_Players->pRemotePlayer[playerID]->pPlayerData->pSAMP_Actor == NULL)
		return false;
	return true;
}

bool IsPlayerShot(int playerID)
{
	if (g_Players->pRemotePlayer[playerID]->pPlayerData->onFootData.stSampKeys.keys_secondaryFire__shoot)
		return true;
	if (g_Players->pRemotePlayer[playerID]->pPlayerData->passengerData.stSampKeys.keys_secondaryFire__shoot)
		return true;
	return false;
}


void sampMainUpdate(void)
{


	if (isBadPtr_writeAny(g_SAMP->pPools, sizeof(stSAMPPools)))
	{
		g_Vehicles = NULL;
		g_Players = NULL;
	}
	else if (g_Vehicles != g_SAMP->pPools->pVehicle || g_Players != g_SAMP->pPools->pPlayer)
	{
		if (isBadPtr_writeAny(g_SAMP->pPools->pVehicle, sizeof(stVehiclePool)))
			g_Vehicles = NULL;
		else
			g_Vehicles = g_SAMP->pPools->pVehicle;
		if (isBadPtr_writeAny(g_SAMP->pPools->pPlayer, sizeof(stPlayerPool)))
			g_Players = NULL;
		else
			g_Players = g_SAMP->pPools->pPlayer;
	}

	// update GTA to SAMP translation structures
	update_translateGTASAMP_vehiclePool();
	update_translateGTASAMP_pedPool();

	static int	iSAMPHooksInstalled;
	if (!iSAMPHooksInstalled)
	{
		installSAMPHooks();
		iSAMPHooksInstalled = 1;
	}



}




