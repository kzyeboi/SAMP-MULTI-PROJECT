#include "main.h"



//Color Codes
#define AliceBlue D3DCOLOR_ARGB ( 255, 240, 248, 255 )
#define AntiqueWhite D3DCOLOR_ARGB ( 255, 250, 235, 215 )
#define Aquamarine D3DCOLOR_ARGB ( 255, 127, 255, 212 )
#define Azure D3DCOLOR_ARGB ( 255, 240, 255, 255 )
#define Beige D3DCOLOR_ARGB ( 255, 245, 245, 220 )
#define Bisque D3DCOLOR_ARGB ( 255, 255, 228, 196 )
#define Black D3DCOLOR_ARGB ( 255, 0, 0, 0 )
#define BlanchedAlmond D3DCOLOR_ARGB ( 255, 255, 235, 205 )
#define Mavi D3DCOLOR_ARGB ( 255, 0, 0, 255 )
#define BlueViolet D3DCOLOR_ARGB ( 255, 138, 43, 226 )
#define Brown D3DCOLOR_ARGB ( 255, 165, 42, 42 )
#define Burlywood D3DCOLOR_ARGB ( 255, 222, 184, 135 )
#define CadetBlue D3DCOLOR_ARGB ( 255, 95, 158, 160 )
#define Chartreuse D3DCOLOR_ARGB ( 255, 127, 255, 0 )
#define Chocolate D3DCOLOR_ARGB ( 255, 210, 105, 30 )
#define Coral D3DCOLOR_ARGB ( 255, 255, 127, 80 )
#define CornflowerBlue D3DCOLOR_ARGB ( 255, 100, 149, 237 )
#define Cornsilk D3DCOLOR_ARGB ( 255, 255, 248, 220 )
#define Cyan D3DCOLOR_ARGB ( 255, 0, 255, 255 )
#define DarkGoldenrod D3DCOLOR_ARGB ( 255, 184, 134, 11 )
#define DarkGreen D3DCOLOR_ARGB ( 255, 0, 100, 0 )
#define DarkKhaki D3DCOLOR_ARGB ( 255, 189 183 107 )
#define DarkOliveGreen D3DCOLOR_ARGB ( 255, 85, 107, 47 )
#define DarkOrange D3DCOLOR_ARGB ( 255, 255, 140, 0 )
#define DarkOrchid D3DCOLOR_ARGB ( 255, 153, 50, 204 )
#define DarkSalmon D3DCOLOR_ARGB ( 255, 233, 150, 122 )
#define DarkSeaGreen D3DCOLOR_ARGB ( 255, 143, 188, 143 )
#define DarkSlateBlue D3DCOLOR_ARGB ( 255, 72, 61, 139 )
#define DarkSlateGray D3DCOLOR_ARGB ( 255, 47, 79, 79 )
#define DarkTurquoise D3DCOLOR_ARGB ( 255, 0, 206, 209 )
#define DarkViolet D3DCOLOR_ARGB ( 255, 148, 0, 211 )
#define DeepPink D3DCOLOR_ARGB ( 255, 255, 20, 147 )
#define DeepSkyBlue D3DCOLOR_ARGB ( 255, 0, 191, 255 )
#define DimGray D3DCOLOR_ARGB ( 255, 105, 105, 105 )
#define DodgerBlue D3DCOLOR_ARGB ( 255, 30, 144, 255 )
#define Firebrick D3DCOLOR_ARGB ( 255, 178, 34, 34 )
#define FloralWhite D3DCOLOR_ARGB ( 255, 255, 250, 240 )
#define ForestGreen D3DCOLOR_ARGB ( 255, 34 139  34 )
#define Gainsboro D3DCOLOR_ARGB ( 255, 220, 220, 220 )
#define GhostWhite D3DCOLOR_ARGB ( 255, 248, 248, 255 )
#define Gold D3DCOLOR_ARGB ( 255, 255, 215, 0 )
#define Goldenrod D3DCOLOR_ARGB ( 255, 218, 165, 32 )
#define Gray D3DCOLOR_ARGB ( 255, 192, 192, 192 )
#define Grey D3DCOLOR_ARGB ( 255, 192, 192, 192 )
#define YES?L D3DCOLOR_ARGB ( 255, 0, 255, 0 )
#define GreenYellow D3DCOLOR_ARGB ( 255, 173, 255, 47 )
#define Honeydew D3DCOLOR_ARGB ( 255, 240, 255, 240 )
#define HotPink D3DCOLOR_ARGB ( 255, 255, 105, 180 )
#define IndianRed D3DCOLOR_ARGB ( 255, 205  92  92 )
#define Ivory D3DCOLOR_ARGB ( 255, 255, 255, 240 )
#define Khaki D3DCOLOR_ARGB ( 255, 240 230 140 )
#define Lavender D3DCOLOR_ARGB ( 255, 230, 230, 250 )
#define LavenderBlush D3DCOLOR_ARGB ( 255, 255, 240, 245 )
#define LawnGreen D3DCOLOR_ARGB ( 255, 124, 252,   0 )
#define LemonChiffon D3DCOLOR_ARGB ( 255, 255, 250, 205 )
#define LightBlue D3DCOLOR_ARGB ( 255, 173, 216, 230 )
#define LightCoral D3DCOLOR_ARGB ( 255, 240, 128, 128 )
#define LightCyan D3DCOLOR_ARGB ( 255, 224, 255, 255 )
#define LightGoldenrod D3DCOLOR_ARGB ( 255, 238, 221, 130 )
#define LightGoldenrodYellow D3DCOLOR_ARGB ( 255, 250 250 210 )
#define LightGray D3DCOLOR_ARGB ( 255, 211, 211, 211 )
#define LightPink D3DCOLOR_ARGB ( 255, 255, 182, 193 )
#define LightSalmon D3DCOLOR_ARGB ( 255, 255, 160, 122 )
#define LightSeaGreen D3DCOLOR_ARGB ( 255, 32, 178, 170 )
#define LightSkyBlue D3DCOLOR_ARGB ( 255, 135, 206, 250 )
#define LightSlateBlue D3DCOLOR_ARGB ( 255, 132, 112, 255 )
#define LightSlateGray D3DCOLOR_ARGB ( 255, 119, 136, 153 )
#define LightSteelBlue D3DCOLOR_ARGB ( 255, 176, 196, 222 )
#define LightYellow D3DCOLOR_ARGB ( 255, 255, 255, 224 )
#define LimeGreen D3DCOLOR_ARGB ( 255, 50 205  50 )
#define Linen D3DCOLOR_ARGB ( 255, 250, 240, 230 )
#define Magenta D3DCOLOR_ARGB ( 255, 255, 0, 255 )
#define MaroonD3DCOLOR_ARGB ( 255, 176, 48, 96 )
#define MediumAquamarine D3DCOLOR_ARGB ( 255, 102, 205, 170 )
#define MediumBlue D3DCOLOR_ARGB ( 255, 0, 0, 205 )
#define MediumOrchid D3DCOLOR_ARGB ( 255, 186, 85, 211 )
#define MediumPurple D3DCOLOR_ARGB ( 255, 147, 112, 219 )
#define MediumSeaGreen D3DCOLOR_ARGB ( 255, 60, 179, 113 )
#define MediumSlateBlue D3DCOLOR_ARGB ( 255, 123, 104, 238 )
#define MediumSpringGreen D3DCOLOR_ARGB ( 255, 0, 250, 154 )
#define MediumTurquoise D3DCOLOR_ARGB ( 255, 72, 209, 204 )
#define MediumVioletRed D3DCOLOR_ARGB ( 255, 199, 21, 133 )
#define MidnightBlue D3DCOLOR_ARGB ( 255, 25, 25, 112 )
#define MintCream D3DCOLOR_ARGB ( 255, 245, 255, 250 )
#define MistyRose D3DCOLOR_ARGB ( 255, 255, 228, 225 )
#define Moccasin D3DCOLOR_ARGB ( 255, 255, 228, 181 )
#define NavajoWhite D3DCOLOR_ARGB ( 255, 255, 222, 173 )
#define Navy D3DCOLOR_ARGB ( 255, 0, 0, 128 )
#define OldLace D3DCOLOR_ARGB ( 255, 253, 245, 230 )
#define OliveDrab D3DCOLOR_ARGB ( 255, 107 142  35 )
#define Orange D3DCOLOR_ARGB ( 255, 255, 165, 0 )
#define OrangeRed D3DCOLOR_ARGB ( 255, 255, 69, 0 )
#define Orchid D3DCOLOR_ARGB ( 255, 218, 112, 214 )
#define PaleGoldenrod D3DCOLOR_ARGB ( 255, 238 232 170 )
#define PaleGreen D3DCOLOR_ARGB ( 255, 152, 251, 152 )
#define PaleTurquoise D3DCOLOR_ARGB ( 255, 175, 238, 238 )
#define PaleVioletRed D3DCOLOR_ARGB ( 255, 219, 112, 147 )
#define PapayaWhip D3DCOLOR_ARGB ( 255, 255, 239, 213 )
#define PeachPuff D3DCOLOR_ARGB ( 255, 255, 218, 185 )