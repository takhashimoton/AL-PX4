/****************************************************************************
 *
 *   Copyright (c) 2020-2021 PX4 Development Team. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name PX4 nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

#include <stdint.h>

static constexpr float SAMPLING_RES = 10;
static constexpr float SAMPLING_MIN_LAT = -90;
static constexpr float SAMPLING_MAX_LAT = 90;
static constexpr float SAMPLING_MIN_LON = -180;
static constexpr float SAMPLING_MAX_LON = 180;

static constexpr int LAT_DIM = 19;
static constexpr int LON_DIM = 37;


// *INDENT-OFF*
// Magnetic declination data in radians * 10^-4
// Model: WMM-2020,
// Version: 0.5.1.11,
// Date: 2021.6083,
static constexpr const int16_t declination_table[19][37] {
	//    LONGITUDE:   -180,  -170,  -160,  -150,  -140,  -130,  -120,  -110,  -100,   -90,   -80,   -70,   -60,   -50,   -40,   -30,   -20,   -10,     0,    10,    20,    30,    40,    50,    60,    70,    80,    90,   100,   110,   120,   130,   140,   150,   160,   170,   180,
	/* LAT: -90 */ {  26010, 24265, 22520, 20774, 19029, 17284, 15538, 13793, 12048, 10302,  8557,  6812,  5067,  3321,  1576,  -169, -1915, -3660, -5405, -7150, -8896,-10641,-12386,-14132,-15877,-17622,-19368,-21113,-22858,-24604,-26349,-28095,-29840, 31247, 29501, 27756, 26010, },
	/* LAT: -80 */ {  22579, 20444, 18502, 16725, 15083, 13544, 12079, 10667,  9292,  7941,  6609,  5290,  3980,  2676,  1368,    50, -1290, -2661, -4069, -5518, -7011, -8545,-10121,-11738,-13401,-15117,-16901,-18771,-20752,-22869,-25141,-27575,-30144, 30046, 27424, 24914, 22579, },
	/* LAT: -70 */ {  14969, 13572, 12449, 11490, 10625,  9796,  8956,  8071,  7120,  6101,  5031,  3937,  2850,  1794,   770,  -240, -1276, -2378, -3575, -4870, -6246, -7672, -9117,-10557,-11982,-13396,-14823,-16306,-17924,-19828,-22333,-26109, 30805, 24185, 19627, 16842, 14969, },
	/* LAT: -60 */ {   8387,  8148,  7874,  7606,  7358,  7109,  6805,  6377,  5765,  4948,  3950,  2838,  1716,   683,  -205,  -967, -1697, -2515, -3510, -4698, -6020, -7385, -8703, -9913,-10979,-11880,-12598,-13094,-13266,-12816,-10726, -3584,  4799,  7586,  8376,  8514,  8387, },
	/* LAT: -50 */ {   5459,  5498,  5447,  5363,  5294,  5261,  5230,  5107,  4768,  4110,  3104,  1834,   491,  -697, -1580, -2155, -2558, -2995, -3667, -4664, -5894, -7164, -8304, -9210, -9815,-10063, -9879, -9130, -7630, -5275, -2375,   372,  2480,  3904,  4778,  5253,  5459, },
	/* LAT: -40 */ {   3935,  4030,  4041,  4001,  3946,  3915,  3923,  3915,  3746,  3218,  2203,   767,  -799, -2124, -3002, -3467, -3662, -3727, -3886, -4431, -5385, -6453, -7341, -7890, -8009, -7646, -6769, -5390, -3676, -1968,  -504,   718,  1760,  2622,  3276,  3704,  3935, },
	/* LAT: -30 */ {   2967,  3054,  3089,  3080,  3027,  2952,  2895,  2863,  2739,  2268,  1244,  -267, -1876, -3142, -3897, -4256, -4348, -4153, -3722, -3476, -3808, -4543, -5247, -5610, -5500, -4926, -3974, -2766, -1549,  -597,    85,   686,  1307,  1905,  2411,  2770,  2967, },
	/* LAT: -20 */ {   2325,  2372,  2395,  2403,  2366,  2276,  2172,  2098,  1954,  1465,   421, -1058, -2541, -3616, -4166, -4298, -4109, -3565, -2710, -1897, -1594, -1930, -2578, -3057, -3106, -2757, -2126, -1307,  -522,   -26,   241,   544,   982,  1454,  1871,  2174,  2325, },
	/* LAT: -10 */ {   1931,  1926,  1911,  1914,  1892,  1812,  1707,  1620,  1436,   892,  -160, -1532, -2811, -3656, -3943, -3733, -3169, -2393, -1547,  -784,  -305,  -322,  -783, -1292, -1514, -1430, -1120,  -618,  -115,   132,   186,   348,   715,  1146,  1533,  1815,  1931, },
	/* LAT:   0 */ {   1718,  1686,  1636,  1633,  1628,  1564,  1466,  1357,  1105,   488,  -546, -1772, -2834, -3437, -3456, -2971, -2209, -1426,  -769,  -229,   190,   312,    43,  -374,  -634,  -693,  -594,  -331,   -36,    58,     3,    94,   431,   865,  1278,  1593,  1718, },
	/* LAT:  10 */ {   1585,  1594,  1557,  1578,  1609,  1565,  1450,  1269,   896,   180,  -839, -1917, -2754, -3110, -2922, -2327, -1553,  -837,  -316,    68,   396,   551,   397,    76,  -162,  -271,  -292,  -208,  -100,  -137,  -272,  -243,    54,   501,   976,  1378,  1585, },
	/* LAT:  20 */ {   1407,  1556,  1620,  1716,  1806,  1790,  1642,  1345,   802,   -53, -1097, -2055, -2664, -2787, -2471, -1876, -1166,  -513,   -47,   266,   527,   677,   592,   350,   148,    30,   -57,  -117,  -193,  -380,  -613,  -671,  -441,     0,   537,  1052,  1407, },
	/* LAT:  30 */ {   1113,  1481,  1742,  1968,  2130,  2144,  1961,  1543,   817,  -213, -1335, -2222, -2650, -2599, -2207, -1631,  -977,  -356,   111,   421,   655,   805,   789,   642,   491,   367,   215,    10,  -268,  -639, -1007, -1168, -1012,  -590,   -16,   592,  1113, },
	/* LAT:  40 */ {    765,  1352,  1846,  2239,  2488,  2533,  2320,  1790,   879,  -352, -1599, -2479, -2811, -2667, -2225, -1634,  -981,  -349,   165,   533,   807,  1010,  1108,  1100,  1024,   877,   614,   211,  -321,  -926, -1448, -1696, -1583, -1169,  -571,   104,   765, },
	/* LAT:  50 */ {    485,  1234,  1914,  2470,  2835,  2941,  2711,  2057,   912,  -594, -2030, -2957, -3261, -3073, -2585, -1939, -1229,  -528,    91,   601,  1023,  1382,  1667,  1841,  1863,  1680,  1244,   545,  -341, -1243, -1927, -2220, -2100, -1659, -1020,  -283,   485, },
	/* LAT:  60 */ {    305,  1160,  1966,  2659,  3159,  3368,  3149,  2331,   803, -1177, -2912, -3902, -4157, -3896, -3322, -2575, -1746,  -902,   -90,   665,  1361,  1995,  2542,  2943,  3110,  2932,  2307,  1204,  -202, -1526, -2404, -2721, -2558, -2060, -1360,  -551,   305, },
	/* LAT:  70 */ {     98,  1039,  1938,  2736,  3347,  3635,  3370,  2209,   -80, -2842, -4809, -5628, -5626, -5133, -4355, -3414, -2383, -1312,  -233,   831,  1860,  2829,  3701,  4414,  4869,  4913,  4322,  2874,   700, -1409, -2717, -3168, -3009, -2472, -1714,  -836,    98, },
	/* LAT:  80 */ {   -513,   413,  1269,  1964,  2346,  2142,   874, -1894, -5244, -7372, -8081, -7911, -7253, -6315, -5208, -3997, -2722, -1409,   -79,  1253,  2571,  3855,  5084,  6224,  7221,  7982,  8330,  7905,  6045,  2400, -1140, -2878, -3268, -2955, -2285, -1437,  -513, },
	/* LAT:  90 */ { -30191,-28446,-26700,-24955,-23210,-21464,-19719,-17973,-16228,-14483,-12738,-10992, -9247, -7502, -5757, -4012, -2267,  -521,  1224,  2969,  4714,  6459,  8205,  9950, 11695, 13441, 15186, 16931, 18677, 20422, 22168, 23913, 25659, 27404, 29150, 30895,-30191, },
};

// Magnetic inclination data in radians * 10^-4
// Model: WMM-2020,
// Version: 0.5.1.11,
// Date: 2021.6083,
static constexpr const int16_t inclination_table[19][37] {
	//    LONGITUDE:   -180,  -170,  -160,  -150,  -140,  -130,  -120,  -110,  -100,   -90,   -80,   -70,   -60,   -50,   -40,   -30,   -20,   -10,     0,    10,    20,    30,    40,    50,    60,    70,    80,    90,   100,   110,   120,   130,   140,   150,   160,   170,   180,
	/* LAT: -90 */ { -12577,-12577,-12577,-12577,-12577,-12577,-12577,-12577,-12577,-12577,-12577,-12577,-12577,-12577,-12577,-12577,-12577,-12577,-12577,-12577,-12577,-12577,-12577,-12577,-12577,-12577,-12577,-12577,-12577,-12577,-12577,-12577,-12577,-12577,-12577,-12577,-12577, },
	/* LAT: -80 */ { -13664,-13530,-13370,-13189,-12995,-12793,-12589,-12388,-12197,-12020,-11863,-11729,-11618,-11532,-11468,-11427,-11407,-11410,-11437,-11492,-11575,-11689,-11833,-12007,-12204,-12421,-12650,-12883,-13111,-13324,-13511,-13661,-13766,-13818,-13816,-13762,-13664, },
	/* LAT: -70 */ { -14114,-13795,-13476,-13152,-12820,-12476,-12120,-11762,-11418,-11108,-10854,-10669,-10556,-10503,-10489,-10494,-10503,-10513,-10538,-10594,-10702,-10875,-11120,-11432,-11804,-12220,-12668,-13131,-13598,-14050,-14469,-14816,-15008,-14957,-14727,-14429,-14114, },
	/* LAT: -60 */ { -13523,-13171,-12833,-12500,-12157,-11784,-11369,-10913,-10445,-10012, -9679, -9500, -9494, -9629, -9834,-10030,-10160,-10208,-10199,-10186,-10233,-10388,-10673,-11078,-11574,-12128,-12713,-13309,-13897,-14459,-14955,-15246,-15075,-14693,-14288,-13895,-13523, },
	/* LAT: -50 */ { -12498,-12157,-11827,-11505,-11182,-10835,-10436, -9964, -9433, -8909, -8514, -8382, -8577, -9034, -9598,-10115,-10482,-10654,-10633,-10486,-10344,-10344,-10558,-10967,-11505,-12096,-12682,-13223,-13670,-13970,-14079,-14007,-13804,-13521,-13193,-12846,-12498, },
	/* LAT: -40 */ { -11240,-10894,-10548,-10204, -9864, -9526, -9164, -8737, -8215, -7647, -7215, -7162, -7611, -8429, -9352,-10186,-10852,-11297,-11450,-11295,-10958,-10681,-10663,-10936,-11392,-11897,-12345,-12671,-12833,-12839,-12749,-12611,-12430,-12198,-11912,-11585,-11240, },
	/* LAT: -30 */ {  -9601, -9226, -8850, -8461, -8069, -7692, -7334, -6940, -6426, -5813, -5353, -5420, -6173, -7367, -8619, -9720,-10641,-11361,-11775,-11782,-11421,-10914,-10572,-10562,-10808,-11129,-11389,-11508,-11448,-11272,-11096,-10958,-10810,-10602,-10320, -9976, -9601, },
	/* LAT: -20 */ {  -7370, -6936, -6524, -6098, -5653, -5222, -4828, -4411, -3842, -3154, -2696, -2936, -4024, -5626, -7257, -8637, -9714,-10501,-10954,-11003,-10652,-10044, -9482, -9230, -9274, -9435, -9579, -9601, -9431, -9158, -8961, -8869, -8760, -8550, -8233, -7823, -7370, },
	/* LAT: -10 */ {  -4412, -3886, -3440, -3006, -2549, -2097, -1680, -1219,  -587,   122,   496,    91, -1214, -3120, -5099, -6723, -7836, -8485, -8762, -8710, -8312, -7636, -6972, -6620, -6577, -6669, -6789, -6815, -6629, -6332, -6173, -6174, -6126, -5905, -5522, -4998, -4412, },
	/* LAT:   0 */ {   -903,  -291,   166,   564,   982,  1399,  1793,  2244,  2837,  3422,  3636,  3160,  1885,   -12, -2059, -3726, -4755, -5199, -5268, -5105, -4675, -3968, -3263, -2886, -2824, -2895, -3022, -3097, -2968, -2731, -2671, -2804, -2856, -2664, -2240, -1615,  -903, },
	/* LAT:  10 */ {   2565,  3180,  3607,  3944,  4298,  4666,  5021,  5416,  5876,  6254,  6300,  5825,  4759,  3204,  1512,   124,  -699,  -961,  -878,  -648,  -244,   387,  1020,  1360,  1422,  1374,  1272,  1180,  1224,  1330,  1260,  1004,   823,   900,  1252,  1849,  2565, },
	/* LAT:  20 */ {   5418,  5939,  6313,  6606,  6919,  7263,  7609,  7962,  8303,  8509,  8429,  7976,  7150,  6060,  4933,  4016,  3476,  3346,  3489,  3728,  4054,  4515,  4974,  5231,  5285,  5264,  5214,  5157,  5148,  5132,  4964,  4639,  4349,  4264,  4435,  4854,  5418, },
	/* LAT:  30 */ {   7569,  7939,  8254,  8535,  8844,  9192,  9552,  9897, 10179, 10298, 10158,  9743,  9118,  8409,  7746,  7230,  6932,  6883,  7020,  7228,  7472,  7768,  8056,  8229,  8285,  8295,  8295,  8286,  8266,  8186,  7969,  7621,  7270,  7052,  7036,  7228,  7569, },
	/* LAT:  40 */ {   9266,  9485,  9741, 10026, 10353, 10715, 11085, 11427, 11683, 11769, 11623, 11266, 10793, 10319,  9921,  9635,  9482,  9473,  9580,  9739,  9912, 10094, 10265, 10390, 10467, 10525, 10578, 10611, 10597, 10490, 10251,  9904,  9539,  9255,  9112,  9124,  9266, },
	/* LAT:  50 */ {  10801, 10923, 11125, 11395, 11719, 12075, 12431, 12750, 12974, 13036, 12898, 12601, 12236, 11889, 11612, 11423, 11327, 11321, 11385, 11485, 11597, 11712, 11827, 11943, 12060, 12181, 12293, 12366, 12359, 12237, 11994, 11668, 11329, 11044, 10854, 10774, 10801, },
	/* LAT:  60 */ {  12318, 12393, 12545, 12764, 13036, 13338, 13642, 13909, 14086, 14115, 13979, 13729, 13438, 13166, 12944, 12786, 12693, 12660, 12674, 12720, 12787, 12871, 12975, 13106, 13265, 13439, 13604, 13714, 13723, 13605, 13382, 13104, 12825, 12587, 12417, 12326, 12318, },
	/* LAT:  70 */ {  13759, 13803, 13900, 14044, 14225, 14431, 14640, 14822, 14927, 14905, 14765, 14562, 14343, 14138, 13964, 13828, 13733, 13677, 13657, 13669, 13710, 13781, 13883, 14019, 14185, 14371, 14555, 14697, 14745, 14676, 14515, 14317, 14122, 13957, 13837, 13770, 13759, },
	/* LAT:  80 */ {  15001, 15015, 15054, 15115, 15193, 15280, 15360, 15405, 15384, 15301, 15186, 15060, 14936, 14822, 14722, 14639, 14577, 14536, 14517, 14520, 14546, 14595, 14666, 14758, 14869, 14995, 15130, 15262, 15369, 15414, 15378, 15294, 15200, 15116, 15053, 15014, 15001, },
	/* LAT:  90 */ {  15392, 15392, 15392, 15392, 15392, 15392, 15392, 15392, 15392, 15392, 15392, 15392, 15392, 15392, 15392, 15392, 15392, 15392, 15392, 15392, 15392, 15392, 15392, 15392, 15392, 15392, 15392, 15392, 15392, 15392, 15392, 15392, 15392, 15392, 15392, 15392, 15392, },
};

// Magnetic strength data in milli-Gauss * 10
// Model: WMM-2020,
// Version: 0.5.1.11,
// Date: 2021.6083,
static constexpr const int16_t strength_table[19][37] {
	//    LONGITUDE:  -180, -170, -160, -150, -140, -130, -120, -110, -100,  -90,  -80,  -70,  -60,  -50,  -40,  -30,  -20,  -10,    0,   10,   20,   30,   40,   50,   60,   70,   80,   90,  100,  110,  120,  130,  140,  150,  160,  170,  180,
	/* LAT: -90 */ {  5457, 5457, 5457, 5457, 5457, 5457, 5457, 5457, 5457, 5457, 5457, 5457, 5457, 5457, 5457, 5457, 5457, 5457, 5457, 5457, 5457, 5457, 5457, 5457, 5457, 5457, 5457, 5457, 5457, 5457, 5457, 5457, 5457, 5457, 5457, 5457, 5457, },
	/* LAT: -80 */ {  6063, 6000, 5922, 5830, 5728, 5616, 5499, 5377, 5255, 5135, 5020, 4915, 4821, 4741, 4678, 4633, 4608, 4605, 4626, 4672, 4742, 4835, 4949, 5081, 5224, 5374, 5523, 5666, 5797, 5911, 6004, 6073, 6118, 6138, 6134, 6109, 6063, },
	/* LAT: -70 */ {  6308, 6176, 6026, 5862, 5684, 5493, 5288, 5073, 4854, 4638, 4435, 4252, 4094, 3963, 3858, 3781, 3734, 3721, 3749, 3824, 3951, 4130, 4357, 4624, 4918, 5225, 5529, 5812, 6062, 6267, 6418, 6515, 6557, 6550, 6502, 6418, 6308, },
	/* LAT: -60 */ {  6192, 6002, 5801, 5594, 5376, 5141, 4885, 4607, 4314, 4024, 3757, 3528, 3348, 3213, 3114, 3040, 2990, 2969, 2994, 3083, 3250, 3500, 3825, 4209, 4631, 5065, 5486, 5870, 6195, 6445, 6609, 6689, 6692, 6630, 6517, 6367, 6192, },
	/* LAT: -50 */ {  5848, 5620, 5389, 5159, 4928, 4683, 4413, 4110, 3781, 3449, 3146, 2905, 2742, 2650, 2602, 2568, 2535, 2509, 2514, 2585, 2756, 3043, 3436, 3905, 4411, 4917, 5393, 5812, 6152, 6394, 6534, 6576, 6534, 6425, 6264, 6067, 5848, },
	/* LAT: -40 */ {  5396, 5152, 4908, 4669, 4436, 4199, 3945, 3661, 3347, 3021, 2721, 2497, 2379, 2352, 2371, 2394, 2400, 2389, 2377, 2405, 2532, 2802, 3215, 3726, 4272, 4797, 5266, 5656, 5949, 6137, 6227, 6230, 6162, 6032, 5851, 5634, 5396, },
	/* LAT: -30 */ {  4880, 4641, 4403, 4169, 3944, 3725, 3507, 3276, 3021, 2745, 2487, 2303, 2231, 2254, 2321, 2393, 2460, 2512, 2536, 2549, 2613, 2806, 3162, 3646, 4177, 4675, 5096, 5416, 5620, 5720, 5748, 5721, 5642, 5511, 5332, 5116, 4880, },
	/* LAT: -20 */ {  4322, 4111, 3903, 3699, 3503, 3321, 3153, 2990, 2813, 2616, 2425, 2290, 2246, 2286, 2375, 2486, 2614, 2744, 2836, 2874, 2898, 2989, 3223, 3602, 4051, 4478, 4830, 5068, 5175, 5183, 5153, 5106, 5024, 4897, 4731, 4534, 4322, },
	/* LAT: -10 */ {  3791, 3631, 3479, 3333, 3198, 3078, 2975, 2884, 2788, 2675, 2553, 2453, 2404, 2425, 2509, 2637, 2793, 2953, 3080, 3145, 3160, 3184, 3303, 3551, 3874, 4196, 4463, 4628, 4666, 4614, 4547, 4483, 4394, 4269, 4120, 3957, 3791, },
	/* LAT:   0 */ {  3412, 3320, 3237, 3165, 3110, 3072, 3047, 3030, 3007, 2960, 2882, 2787, 2704, 2669, 2708, 2809, 2941, 3077, 3194, 3271, 3303, 3324, 3396, 3550, 3757, 3970, 4151, 4259, 4267, 4200, 4112, 4019, 3907, 3776, 3642, 3519, 3412, },
	/* LAT:  10 */ {  3283, 3253, 3233, 3230, 3255, 3303, 3360, 3415, 3452, 3443, 3375, 3260, 3132, 3034, 3004, 3043, 3123, 3221, 3321, 3407, 3471, 3533, 3619, 3736, 3870, 4007, 4126, 4198, 4202, 4141, 4032, 3889, 3728, 3569, 3434, 3338, 3283, },
	/* LAT:  20 */ {  3400, 3404, 3431, 3486, 3579, 3701, 3831, 3950, 4032, 4045, 3972, 3830, 3662, 3520, 3440, 3426, 3459, 3531, 3626, 3723, 3813, 3911, 4021, 4132, 4240, 4350, 4451, 4518, 4530, 4473, 4337, 4136, 3909, 3700, 3538, 3438, 3400, },
	/* LAT:  30 */ {  3723, 3732, 3788, 3889, 4033, 4205, 4382, 4539, 4649, 4676, 4603, 4447, 4256, 4089, 3981, 3932, 3934, 3983, 4068, 4166, 4262, 4367, 4483, 4600, 4720, 4845, 4964, 5051, 5079, 5023, 4868, 4630, 4356, 4102, 3904, 3776, 3723, },
	/* LAT:  40 */ {  4222, 4223, 4290, 4416, 4584, 4773, 4957, 5114, 5219, 5245, 5176, 5027, 4838, 4661, 4531, 4453, 4425, 4445, 4504, 4582, 4668, 4764, 4879, 5012, 5162, 5323, 5474, 5585, 5625, 5573, 5419, 5182, 4908, 4649, 4438, 4294, 4222, },
	/* LAT:  50 */ {  4832, 4827, 4886, 4998, 5146, 5306, 5456, 5577, 5650, 5659, 5594, 5466, 5302, 5136, 4997, 4898, 4842, 4828, 4852, 4901, 4969, 5059, 5177, 5327, 5502, 5686, 5853, 5972, 6018, 5976, 5846, 5650, 5425, 5208, 5028, 4900, 4832, },
	/* LAT:  60 */ {  5392, 5382, 5413, 5478, 5565, 5660, 5747, 5812, 5844, 5834, 5779, 5683, 5562, 5432, 5312, 5215, 5147, 5112, 5109, 5136, 5192, 5277, 5395, 5541, 5708, 5876, 6025, 6130, 6176, 6154, 6072, 5946, 5798, 5655, 5533, 5443, 5392, },
	/* LAT:  70 */ {  5726, 5708, 5707, 5721, 5744, 5770, 5794, 5807, 5806, 5785, 5745, 5687, 5615, 5538, 5464, 5399, 5350, 5322, 5317, 5336, 5380, 5449, 5541, 5649, 5766, 5881, 5981, 6055, 6095, 6098, 6069, 6016, 5948, 5878, 5813, 5761, 5726, },
	/* LAT:  80 */ {  5789, 5772, 5758, 5747, 5737, 5728, 5718, 5706, 5691, 5672, 5649, 5623, 5596, 5568, 5543, 5522, 5508, 5502, 5507, 5522, 5547, 5582, 5625, 5673, 5722, 5771, 5813, 5848, 5873, 5886, 5888, 5882, 5868, 5849, 5829, 5808, 5789, },
	/* LAT:  90 */ {  5680, 5680, 5680, 5680, 5680, 5680, 5680, 5680, 5680, 5680, 5680, 5680, 5680, 5680, 5680, 5680, 5680, 5680, 5680, 5680, 5680, 5680, 5680, 5680, 5680, 5680, 5680, 5680, 5680, 5680, 5680, 5680, 5680, 5680, 5680, 5680, 5680, },
};
