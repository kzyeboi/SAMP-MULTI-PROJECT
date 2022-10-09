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
#define INI_STRLEN_MAX		64	/* including null */
#define INI_PATCHES_MAX		96
#define INI_SAMPPATCHES_MAX 128 /*64*/
#define INI_NETPATCHES_MAX	1024
#define INI_SERVERS_MAX		64
#define INI_CHATMSGS_MAX	64
#define INI_GUI_MAX			8
#define INI_KEYCOMBO_MAX	8


struct settings_coord
{
	float	pos[3];
	int		interior_id;
	int		iMenuID;
};


struct keycombo
{
	unsigned int count;
	uint8_t key[INI_KEYCOMBO_MAX];
};



struct settings
{

	stNetPatch				netPatch[INI_NETPATCHES_MAX];
	stNetPatch				*netPatchAssoc[RAKNET_MAX_PACKET][4];
};


///////////////////////////////////////////////
extern struct settings	set;

#define LTRIM( str ) \
	while ( *(str) == '\t' || *(str) == ' ' ) \
		( str )++

struct key_alias
{
	int		key;
	char* name;
};
struct ini_entry_data
{
	int			count;				/* number of times it has been set */
	void* data;				/* teh value */
	const char* def;				/* default */
};

struct ini_entry
{
	const char* name;
	int						type;
	int						size;	/* number of data items (1 for non-arrays) */
	struct ini_entry_data* data;	/* size # of ini_entry_data */
};

extern struct ini_entry* ini_entry;
extern int				ini_entry_count;

void					ini_load ( void );
void					ini_reload ( void );
const char*             ini_entry_name(const struct ini_entry* ent, int idx);
int                     parse_int(const char* str);
void                    ini_entry_parse_type(struct ini_entry* ent, int idx, const char* val);
void                    ini_entry_parse(struct ini_entry* ent, int idx, const char* val);
struct ini_entry*       ini_register_entry(const char* name, int type);
struct ini_entry_data* ini_register_data(struct ini_entry* ent, void* data, const char* def);
