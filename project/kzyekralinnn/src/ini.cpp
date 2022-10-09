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

	

struct settings			set;

struct key_alias key_alias[] =
{
	{ VK_LBUTTON, "lbutton" },
	{ VK_RBUTTON, "rbutton" },
	{ VK_MBUTTON, "mbutton" },
	{ VK_XBUTTON1, "mouse_4" },
	{ VK_XBUTTON2, "mouse_5" },
	{ VK_BACK, "backspace" },
	{ VK_TAB, "tab" },
	{ VK_RETURN, "return" },
	{ VK_LSHIFT, "lshift" },
	{ VK_RSHIFT, "rshift" },
	{ VK_LCONTROL, "lctrl" },
	{ VK_RCONTROL, "rctrl" },
	{ VK_LMENU, "lalt" },
	{ VK_RMENU, "ralt" },
	{ VK_SPACE, "space" },
	{ VK_PRIOR, "pageup" },
	{ VK_NEXT, "pagedn" },
	{ VK_END, "end" },
	{ VK_HOME, "home" },
	{ VK_LEFT, "left" },
	{ VK_UP, "up" },
	{ VK_RIGHT, "right" },
	{ VK_DOWN, "down" },
	{ VK_INSERT, "insert" },
	{ VK_DELETE, "delete" },
	{ VK_PAUSE, "pause" },
	{ VK_NUMPAD0, "np0" },
	{ VK_NUMPAD1, "np1" },
	{ VK_NUMPAD2, "np2" },
	{ VK_NUMPAD3, "np3" },
	{ VK_NUMPAD4, "np4" },
	{ VK_NUMPAD5, "np5" },
	{ VK_NUMPAD6, "np6" },
	{ VK_NUMPAD7, "np7" },
	{ VK_NUMPAD8, "np8" },
	{ VK_NUMPAD9, "np9" },
	{ VK_MULTIPLY, "multiply" },
	{ VK_ADD, "add" },
	{ VK_SEPARATOR, "separator" },
	{ VK_SUBTRACT, "subtract" },
	{ VK_DECIMAL, "decimal" },
	{ VK_DIVIDE, "divide" },
	{ VK_F1, "f1" },
	{ VK_F2, "f2" },
	{ VK_F3, "f3" },
	{ VK_F4, "f4" },
	{ VK_F5, "f5" },
	{ VK_F6, "f6" },
	{ VK_F7, "f7" },
	{ VK_F8, "f8" },
	{ VK_F9, "f9" },
	{ VK_F10, "f10" },
	{ VK_F11, "f11" },
	{ VK_F12, "f12" },
	{ VK_F13, "f13" },
	{ VK_F14, "f14" },
	{ VK_F15, "f15" },
	{ VK_F16, "f16" },
	{ VK_F17, "f17" },
	{ VK_F18, "f18" },
	{ VK_F19, "f19" },
	{ VK_F20, "f20" },
	{ VK_F21, "f21" },
	{ VK_F22, "f22" },
	{ VK_F23, "f23" },
	{ VK_F24, "f24" },
	{ VK_OEM_PLUS, "oem_plus" },
	{ VK_OEM_COMMA, "oem_comma" },
	{ VK_OEM_MINUS, "oem_minus" },
	{ VK_OEM_PERIOD, "oem_period" },
	{ VK_OEM_1, "oem_1" },
	{ VK_OEM_2, "oem_2" },
	{ VK_OEM_3, "oem_3" },
	{ VK_OEM_4, "oem_4" },
	{ VK_OEM_5, "oem_5" },
	{ VK_OEM_6, "oem_6" },
	{ VK_OEM_7, "oem_7" },
	{ VK_OEM_8, "oem_8" },
	{ -1, NULL }
};

struct ini_entry* ini_entry;
int				ini_entry_count;

const char* ini_entry_name(const struct ini_entry* ent, int idx)
{
	static char str[64];

	if (ent->size == 1)
		return ent->name;

	if (idx == -1)
		snprintf(str, sizeof(str), "%s[]", ent->name);
	else
		snprintf(str, sizeof(str), "%s[%d]", ent->name, idx);

	return str;
}

int parse_int(const char* str)
{
	return strtol(str, NULL, 0);
}

int key_lookup(const char* name)
{
	if (name[0] && !name[1])
	{
		if (name[0] >= 'a' && name[0] <= 'z')
			return 'A' + (name[0] - 'a');
		if (name[0] >= '0' && name[0] <= '9')
			return name[0];
	}

	if (name[0] == '&')
		return parse_int(name + 1);

	int i = 0;
	while (key_alias[i].name != NULL)
	{
		if (strcmp(key_alias[i].name, name) == 0)
			return key_alias[i].key;
		i++;
	}

	Log("Unknown key: %s", name);

	return -1;
}

struct ini_entry_data* ini_register_data(struct ini_entry* ent, void* data, const char* def)
{
	struct ini_entry_data* d;
	void* tmp;

	ent->size++;
	tmp = realloc(ent->data, ent->size * sizeof(struct ini_entry_data));
	if (tmp == NULL)
		goto out;
	ent->data = (struct ini_entry_data*)tmp;

	d = &ent->data[ent->size - 1];
	d->count = 0;
	d->data = data;
	d->def = _strdup(def);

	return d;
out:;
	ent->size--;
	return NULL;
}

struct ini_entry* ini_register_entry(const char* name, int type)
{
	struct ini_entry* ent = NULL;
	void* tmp;

	ini_entry_count++;

	tmp = realloc(ini_entry, ini_entry_count * sizeof(struct ini_entry));
	if (tmp == NULL)
		goto out;
	ini_entry = (struct ini_entry*)tmp;

	ent = &ini_entry[ini_entry_count - 1];

	ent->name = _strdup(name);
	ent->type = type;
	ent->size = 0;
	ent->data = NULL;

	return ent;

out:;
	ini_entry_count--;
	return NULL;
}


void ini_init ( void )
{
	

	struct ini_entry	*ent;
	int					i;


}



int iGTAPatchesCount = 0, iSAMPPatchesCount = 0, iNetPatchesCount = 0, iServersCount = 0;
void ini_entry_parse_type(struct ini_entry* ent, int idx, const char* val)
{
	struct ini_entry_data* ent_data = ent->data + idx;
	struct str_split* split = str_split(val, "\t ");
	int						ok = 0, i;

	if (split == NULL)
	{
		Log("Out of memory");
		return;
	}

	if (split->argc <= 0)
	{
		Log("Missing value for %s", ini_entry_name(ent, idx));
		return;
	}

	switch (ent->type)
	{
	case TYPE_KEY:
		if (split->argc != 1)
			goto wrong_argc;

		if (key_lookup(split->argv[0]) == -1)
		{
			Log("Invalid key name '%s' in %s", split->argv[0], ini_entry_name(ent, idx));
			break;
		}

		*(int*)ent_data->data = key_lookup(split->argv[0]);

		ok = 1;
		break;

	case TYPE_BOOL:
		if (split->argc != 1)
			goto wrong_argc;
		if (_stricmp(split->argv[0], "true") == 0)
			*(int*)ent_data->data = 1;
		else if (_stricmp(split->argv[0], "false") == 0)
			*(int*)ent_data->data = 0;
		else
		{
			Log("Invalid value '%s' in %s", split->argv[0], ini_entry_name(ent, idx));
			break;
		}

		ok = 1;
		break;

	case TYPE_INT:
		if (split->argc != 1)
			goto wrong_argc;
		*(int*)ent_data->data = parse_int(split->argv[0]);
		ok = 1;
		break;

	case TYPE_FLOAT:
		if (split->argc != 1)
			goto wrong_argc;
		*(float*)ent_data->data = (float)atof(val);
		ok = 1;
		break;

	case TYPE_VECTOR:
	{
		float	v[3];

		if (split->argc != 3)
			goto wrong_argc;

		for (i = 0; i < 3; i++)
			v[i] = (float)atof(split->argv[i]);
		vect3_normalize(v, (float*)ent_data->data);

		/* some math functions require 4d vectors.. but we never use the 4th value
		so just set it to 0.0 */
		((float*)ent_data->data)[3] = 0.0f;
		ok = 1;
	}
	break;

	case TYPE_COORD:
	{
		struct settings_coord* coord = (struct settings_coord*)ent_data->data;
		float					v[3];

		if (split->argc != 4)
			goto wrong_argc;

		for (i = 0; i < 3; i++)
			v[i] = (float)atof(split->argv[i]);

		vect3_copy(v, coord->pos);
		coord->interior_id = parse_int(split->argv[3]);
		ok = 1;
	}
	break;

	case TYPE_STRING:
		if (split->argc != 1)
			goto wrong_argc;
		strlcpy((char*)ent_data->data, split->argv[0], INI_STRLEN_MAX);
		ok = 1;
		break;

	case TYPE_WEAPON:
	{
		const struct weapon_entry* weapon = gta_weapon_get_by_name(split->argv[0]);

		if (split->argc != 1)
			goto wrong_argc;

		if (weapon == NULL || strlen(split->argv[0]) == 0)
		{
			if (strlen(split->argv[0]) > 0)
				Log("Unknown weapon '%s' in %s", split->argv[0], ini_entry_name(ent, idx));
			break;
		}

		*(struct weapon_entry**)ent_data->data = (struct weapon_entry*)weapon;
		ok = 1;
	}
	break;
	case TYPE_DWORD:
		if (split->argc != 1)
			goto wrong_argc;
		*(DWORD*)ent_data->data = parse_int(split->argv[0]);
		ok = 1;
		break;
	case TYPE_KEYCOMBO:
	{
		if (split->argc < 1 || split->argc > INI_KEYCOMBO_MAX)
			goto wrong_argc;

		keycombo* kc = (keycombo*)ent_data->data;
		kc->count = 0;
		for (i = 0; i < split->argc; ++i)
		{
			int key = key_lookup(split->argv[i]);
			if (key == -1)
			{
				Log("Invalid key name '%s' in %s", split->argv[i], ini_entry_name(ent, idx));
				break;
			}
			kc->key[i] = key;
			++kc->count;
		}
		ok = 1;
		break;
	}

	default:
		Log("BUG: %s has invalid data type", ini_entry_name(ent, idx));
	}

	str_split_free(split);

	if (ok)
		ent_data->count++;

	return;

wrong_argc:;
	Log("Wrong number of arguments (%d) for %s", split->argc, ini_entry_name(ent, idx));
	str_split_free(split);
}

void ini_entry_parse(struct ini_entry* ent, int idx, const char* val)
{
	if (ent->size <= 0)
	{
		Log("BUG: %s has no data entries", ini_entry_name(ent, idx));
		return;
	}

	if (ent->size > 1)
	{
		/* array */
		if (idx == -1)
		{
			/* foo[], find first unused data entry */
			for (idx = 0; idx < ent->size; idx++)
			{
				if (ent->data[idx].count == 0)
					break;
			}
		}

		if (idx >= ent->size)
			Log("Array index for %s out of bounds", ini_entry_name(ent, idx));
		else
		{
			ini_entry_parse_type(ent, idx, val);
		}
	}
	else
	{
		if (idx != -1)
			Log("Setting %s is not an array", ini_entry_name(ent, idx));
		else
			ini_entry_parse_type(ent, 0, val);
	}
}

void ini_load(void)
{
	static int	first_load = 1;
	char		filename[512];
	char		line[512], line_copy[4096], * opt, * str, * val;
	FILE* fd;
	int			len, i, j, match;
	int			array_idx;

	/* init & load defaults */
	if (first_load)
	{
		memset(&set, 0, sizeof(set));
		ini_init();

		/* read defaults */
		for (i = 0; i < ini_entry_count; i++)
		{
			for (j = 0; j < ini_entry[i].size; j++)
			{
				ini_entry_parse(&ini_entry[i], -1, ini_entry[i].data[j].def);
			}
		}
	}

	for (i = 0; i < ini_entry_count; i++)
	{
		for (j = 0; j < ini_entry[i].size; j++)
		{
			ini_entry[i].data[j].count = 0;
		}
	}

	snprintf(filename, sizeof(filename), "%s\\" "%s", g_szWorkingDirectory, INI_FILE);

	

	fd = fopen(filename, "r");
	if (fd == NULL)
	{
		Log("Could not open %s, using default (or previous) settings.", filename);
		return;
	}
	/*                                                                                 */
	/*                                                                                 */

	strcpy(line_copy, "");
	while ((fgets(line, sizeof(line), fd) != NULL))
	{
		len = (int)strlen(line);

		/* strip trailing newlines, spaces, and tabs */
		while (len > 0 && strchr("\t\n\r ", line[len - 1]))
			line[--len] = 0;

		/* skip comments and empty lines */
		if (line[0] == '#' || line[0] == ';' || line[0] == 0)
			continue;

		if (len > 0 && line[len - 1] == '\\')
		{
			line[len - 1] = ' ';
			strlcat(line_copy, line, sizeof(line_copy));
			continue;
		}

		strlcat(line_copy, line, sizeof(line_copy));

		str = line_copy;
		array_idx = -1;

		/* strip leading spaces */
		LTRIM(str);

		/* extract setting name
		 foo[123] = bar
		 ^^^ */
		while
			(
				(*str >= '0' && *str <= '9')
				|| (*str >= 'A' && *str <= 'Z')
				|| (*str >= 'a' && *str <= 'z')
				|| *str == '_'
				|| *str == '-'
				)
		{
			str++;
		}

		/* parse array index
		 foo[123] = bar
			^^^^ */
		if (*str == '[')
		{
			*str++ = 0;
			LTRIM(str);
			if (*str != ']')	/* foo[] uses the next free array index; leave array_idx set to -1 */
			{
				array_idx = parse_int(str);
				if (array_idx < 0)
				{
					Log("Parse error: %s (Negative array index)", line);
					goto parse_continue;
				}

				if ((str = strchr(str, ']')) == NULL)
				{
					Log("Parse error: %s (missing ']')", line);
					goto parse_continue;
				}
			}

			/* we're at the ']' here */
			str++;
		}

		/* find start of value
		 foo[123] = bar
				 ^^ */
		if (*str == '=')
		{
			*str = 0;
		}
		else
		{
			*str++ = 0;
			LTRIM(str);
			if (*str != '=')
			{
				Log("Parse error: %s (expected '=')", line);
				goto parse_continue;
			}
		}

		/* we're at the '=' here */
		opt = line_copy;
		val = str + 1;

		match = 0;

		for (i = 0; i < ini_entry_count; i++)
		{
			struct ini_entry* ent = &ini_entry[i];

			if (strcmp(opt, ent->name) != 0)
				continue;

			ini_entry_parse(ent, array_idx, val);
			match = 1;

			break;
		}

		if (!match)
			Log("Unknown setting '%s'", opt);

	parse_continue:;
		strcpy(line_copy, "");
	}

	fclose(fd);

	for (i = 0; i < ini_entry_count; i++)
	{
		struct ini_entry* ent = &ini_entry[i];
		int					isset = 0;

		for (j = 0; j < ent->size; j++)
		{
			if (ent->data[j].count == 0)
				continue;

			if (ent->data[j].count > 1)
			{
				Log("Warning: setting '%s' was set multiple times in the .ini file", ini_entry_name(ent, j));
			}

			isset = 1;
		}

		if (!isset)
			Log("Warning: setting '%s%s' was not present in the .ini file", ent->name, (ent->size > 1) ? "[]" : "");
	}

	first_load = 0;

}




void ini_reload(void)
{
	ini_load();
}

