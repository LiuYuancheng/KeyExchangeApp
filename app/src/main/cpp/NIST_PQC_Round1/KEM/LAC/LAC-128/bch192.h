uint16_t a_pow_tab[512] = {1,2,4,8,16,32,64,128,256,17,34,68,136,272,49,98,196,392,257,19,38,76,152,304,113,226,452,409,291,87,174,348,169,338,181,362,197,394,261,27,54,108,216,432,369,243,486,477,427,327,159,318,109,218,436,377,227,454,413,299,71,142,284,41,82,164,328,129,258,21,42,84,168,336,177,354,213,426,325,155,310,125,250,500,505,483,471,447,367,207,414,301,75,150,300,73,146,292,89,178,356,217,434,373,251,502,509,491,455,415,303,79,158,316,105,210,420,345,163,326,157,314,101,202,404,313,99,198,396,265,3,6,12,24,48,96,192,384,273,51,102,204,408,289,83,166,332,137,274,53,106,212,424,321,147,294,93,186,372,249,498,501,507,487,479,431,335,143,286,45,90,180,360,193,386,277,59,118,236,472,417,339,183,366,205,410,293,91,182,364,201,402,309,123,246,492,457,387,279,63,126,252,504,481,467,439,383,239,478,429,331,135,270,13,26,52,104,208,416,337,179,358,221,442,357,219,438,381,235,470,445,363,199,398,269,11,22,44,88,176,352,209,418,341,187,374,253,506,485,475,423,351,175,350,173,346,165,330,133,266,5,10,20,40,80,160,320,145,290,85,170,340,185,370,245,490,453,411,295,95,190,380,233,466,437,379,231,462,397,267,7,14,28,56,112,224,448,401,307,119,238,476,425,323,151,302,77,154,308,121,242,484,473,419,343,191,382,237,474,421,347,167,334,141,282,37,74,148,296,65,130,260,25,50,100,200,400,305,115,230,460,393,259,23,46,92,184,368,241,482,469,443,359,223,446,365,203,406,317,107,214,428,329,131,262,29,58,116,232,464,433,371,247,494,461,395,263,31,62,124,248,496,497,499,503,511,495,463,399,271,15,30,60,120,240,480,465,435,375,255,510,493,459,391,287,47,94,188,376,225,450,405,315,103,206,412,297,67,134,268,9,18,36,72,144,288,81,162,324,153,306,117,234,468,441,355,215,430,333,139,278,61,122,244,488,449,403,311,127,254,508,489,451,407,319,111,222,444,361,195,390,285,43,86,172,344,161,322,149,298,69,138,276,57,114,228,456,385,275,55,110,220,440,353,211,422,349,171,342,189,378,229,458,389,283,39,78,156,312,97,194,388,281,35,70,140,280,33,66,132,264,1};

uint16_t a_log_tab[512] = {0,0,1,130,2,260,131,290,3,420,261,235,132,213,291,390,4,9,421,19,262,69,236,343,133,332,214,39,292,365,391,377,5,507,10,503,422,325,20,495,263,63,70,462,237,169,344,405,134,14,333,139,215,149,40,479,293,473,366,176,392,441,378,199,6,329,508,417,11,470,504,60,423,95,326,92,21,306,496,111,264,426,64,144,71,269,463,29,238,98,170,187,345,156,406,279,135,499,15,126,334,122,140,413,216,114,150,359,41,52,480,455,294,24,474,338,367,431,177,299,393,309,442,193,379,81,200,448,7,67,330,363,509,258,418,211,12,147,471,439,505,323,61,167,424,267,96,154,327,468,93,304,22,429,307,79,497,120,112,50,265,466,427,118,65,256,145,321,72,32,270,487,464,254,30,252,239,74,99,220,171,34,188,182,346,272,157,244,407,489,280,315,136,173,500,459,16,36,127,232,335,190,123,356,141,184,414,89,217,241,115,484,151,76,360,436,42,101,53,225,481,222,456,353,295,409,25,56,475,491,339,286,368,282,432,228,178,317,300,207,394,348,310,45,443,274,194,372,380,159,82,104,201,246,449,399,8,18,68,342,331,38,364,376,510,129,259,289,419,234,212,389,13,138,148,478,472,175,440,198,506,502,324,494,62,461,168,404,425,143,268,28,97,186,155,278,328,416,469,59,94,91,305,110,23,337,430,298,308,192,80,447,498,125,121,412,113,358,51,454,266,153,467,303,428,78,119,49,66,362,257,210,146,438,322,166,73,219,33,181,271,243,488,314,465,117,255,320,31,486,253,251,240,483,75,435,100,224,221,352,172,458,35,231,189,355,183,88,347,44,273,371,158,103,245,398,408,55,490,285,281,227,316,206,137,477,174,197,501,493,460,403,17,341,37,375,128,288,233,388,336,297,191,446,124,411,357,453,142,27,185,277,415,58,90,109,218,180,242,313,116,319,485,250,152,302,77,48,361,209,437,165,43,370,102,397,54,284,226,205,482,434,223,351,457,230,354,87,296,445,410,452,26,276,57,108,476,196,492,402,340,374,287,387,369,396,283,204,433,350,229,86,179,312,318,249,301,47,208,164,395,203,349,85,311,248,46,163,444,451,275,107,195,401,373,386,381,382,160,383,83,161,105,384,202,84,247,162,450,106,400,385};

uint32_t mod8_tab[3072] = {0,0,0,3099199131,2334129702,3841982464,3385723820,2636120683,788529152,1903430967,373292109,3388997632,723915202,2975857392,3137339392,2476480345,977274070,
1577058304,3806861934,746584219,2483027968,1515330805,2808088253,1895825408,1447830405,1656747489,1979711488,4009108766,3919580103,2466250752,2676107305,4288673674,1493172224,
657993394,1954548140,3154116608,2104111687,3554676497,3439329280,3318756572,1493168439,671088640,3030661611,1321209210,3791650816,203308912,3319788380,117440512,2895660810,
3313494978,3959422976,337789329,1314919908,150994944,1700154534,1482680745,3271557120,3723250237,3544192911,637534208,2277398216,1948258610,1459617792,1057247315,4282380052,
2986344448,1315986788,3909096281,2013265920,4140456959,1646259583,2634022912,4208223375,2814385699,2583691264,1114530324,752869381,2130706432,857370403,987765832,3036676096,
2342545848,2986336878,1342177280,3522327885,379577555,553648128,1766355926,2642418421,3288334336,406617825,2344609464,234881024,2693167226,10492062,3942645760,3783952526,
31467939,1023410176,1496354325,2332022661,3623878656,675578658,2629839816,301989888,2432599481,400545262,4143972352,3400309068,2965361491,2248146944,1914085335,1000353141,
1660944384,56791776,765448504,2835349504,3151533179,2793418526,1275068416,3083250443,1667226690,1258291200,259829136,3896517220,2919235584,2114494631,4269792809,1677721600,
3333596732,1969233935,2164260864,2631973577,3523225266,4026531840,609926226,1495259284,352321536,1429123429,1327506649,3741319168,3985946622,3292519167,973078528,1293078404,
3298804321,3506438144,4121479455,1333804103,872415232,2229060648,1505738762,4261412864,1013367475,3533717036,452984832,1714740806,1975531665,1778384896,3733903581,4276078263,
2399141888,2952451562,3907009274,1157627904,390124401,1677706460,2684354560,459205633,2787129216,2801795072,2749688474,759155110,1107296256,3532711853,989869547,2281701376,
1781195062,2954873805,1828716544,813235651,394251632,469762048,2294479704,2623550294,4177526784,4189517423,2321534747,855638016,1091367156,20984125,3590324224,2075072391,
2296360288,2667577344,3272937756,62935878,2046820352,2992708651,369078027,2952790016,182131376,2665500973,1426063360,1351157317,964712336,603979776,3895656670,2996808118,
3238002688,2571570665,2761971195,184549376,570231666,801090525,3992977408,769864706,3932182657,3909091328,2505650841,1635755687,201326592,3828170670,2000706282,3321888768,
1553414453,4234126540,587202560,113583552,1530897009,1375731712,3196003163,3491781719,3070230528,3473616492,3323961370,2097152000,2008099063,1291869756,2550136832,3610726541,
1302349474,1929379840,1871533590,3334453380,2516582400,519658273,3498067145,1543503872,2789432762,1537194735,3103784960,4228989263,4244618322,3355443200,1152075732,2011185780,
754974720,903826147,1642053177,3875536896,2372226168,3938467871,33554432,2172351240,790606659,83886080,968979859,2751483237,3758096384,1219852452,2990518568,704643072,
4027547199,958418702,3472883712,2858246858,2655013299,3187671040,317154385,358594453,1526726656,1670605158,56642520,2432696320,3676925949,2290071038,1946157056,2586156809,
2302641347,2717908992,580884882,35683045,1191182336,1407947941,337610408,2365587456,3947991614,2667608206,1744830464,2969800395,945847859,419430400,163154000,3011477525,
4227858432,2026734951,2772466776,905969664,3229058044,778011262,3539992576,3429481612,3951063330,3556769792,1960032791,1621069572,822083584,94877472,1990226761,4211081216,
3172839867,4257189231,503316480,3880758606,1524599762,1862270976,1609935829,3519051252,2315255808,780248802,3355412921,1073741824,2520490105,1289779103,2768240640,918411267,
1279291137,1308622848,2382880408,3344929063,2868903936,4285780911,3512757610,1627389952,1204409652,1518310220,2214592512,496748993,4246705649,4110417920,2770456410,1979739095,
268435456,3562390125,1614780314,3657433088,1827652854,3944769980,1056964608,1626471302,788503264,939524096,3628858653,2782946502,3707764736,2839539754,3017775243,385875968,
293992113,952133293,4060086272,1272441412,2678087696,2197815296,4084067551,348102198,1711276032,2182734312,41968251,2885681152,983820147,2308938845,1224736768,4150144783,
297753281,1040187392,1340352916,2594219239,3674210304,1049633955,2359253162,285212672,2250908216,125871756,4093640704,3698867917,2699075633,2231369728,1690450006,738156055,
1610612736,364262753,1036034650,2852126720,2903258106,3068091516,1325400064,2702314634,1929424672,1207959552,430443025,4162801926,2902458368,1759250214,3995118923,1728053248,
3496346045,1698648941,2181038080,2318671176,3261027792,4076863488,848174035,1228975094,369098752,1140463332,1602181051,3690987520,4215279743,3563104669,956301312,1539729413,
3569398019,3523215360,3816582814,1608470309,922746880,2450023337,1239462760,4244635648,716334386,3271511374,402653184,1893759431,1704938483,1761607680,3361374044,4001412565,
2348810240,3106828907,4173285784,1174405120,26506480,1939912638,2734686208,227167104,3061794018,2751463424,3039841563,1029749444,1090519040,3292807212,727664265,2332033024,
2097039031,2688596143,1845493760,648829506,119586322,520093696,2652265689,2352955444,4194304000,4016198126,2583739513,805306368,1473795957,287261279,3573547008,383035265,
274690914,50331648,2926485786,2604698948,3858759680,3743067181,2373939465,738197504,1738582710,106991407,3372220416,1039316547,2701166994,3087007744,2236133592,706705332,
1560281088,4097621487,1008765945,2533359616,1283898228,3074389471,1912602624,1083737092,1927317123,1962934272,4163011231,4194269349,2415919104,2304151464,4022371560,1509949440,
837585203,1692367566,3204448256,1807652294,3284106355,3456106496,3540292445,1218478677,721420288,2725289578,1587510808,3774873600,449485041,3581968446,67108864,3125600395,
3575683232,4009754624,49735184,1581213318,167772160,1937959719,1207999179,3221225472,3409505724,3273614573,620756992,2439704905,1686069840,1409286144,701560786,4016086134,
2969567232,1487207141,4183777339,2063597568,3760127102,1916837405,2650800128,3959472910,3080678721,2566914048,1421526421,1015059303,2080374784,634308770,717188906,3053453312,
2641677881,2711654668,1392508928,3341210316,113285041,570425344,2140984407,2380229015,3338665984,250141024,2615186906,218103808,3058884603,285174780,3892314112,2364618888,
2573268897,2701131776,877346323,310315399,1140850688,1161769764,71366090,2382364672,4253365695,2405370860,1795162112,2815895882,675220817,436207616,527249361,2736845687,
4278190080,1847141094,3038711610,889192448,3601015933,1040249116,3489660928,3669826317,4225696320,3607101440,1644633494,1891695718,838860800,326308001,1727987755,4160749568,
2882082362,3990945293,486539264,4053469903,1249966256,1811939328,1226902612,3248424598,2298478592,945095011,3617651419,1124073472,2163148792,1556022525,2785017856,543784834,
1545542755,1291845632,2563995929,3607159365,2818572288,3920065582,3242139144,1644167168,1360884405,1243668526,2264924160,189754944,3980453523,4127195136,3019204827,1717508277,
318767104,3263260140,1885398264,3640655872,2050712439,4219411166,1006632960,1982159879,1050732930,989855744,3466549916,3049199524,3724541952,3219871659,2743135209,335544320,
122769712,681514447,4043309056,1560497605,2415858546,2147483648,3854125918,81849684,1694498816,2496480873,316608793,2936012800,746012914,2579558207,1241513984,1836822534,
2558582274,2617245696,3586242205,329195556,2030043136,2763373482,94428265,3003121664,470793521,2394890831,1442840576,1180541380,702489842,654311424,4276594527,2730547924,
3254779904,2408819304,3036620441,134217728,925478131,1071700159,3976200192,993497987,4198444003,3925868544,2207094040,1897977285,251658240,4076443695,1730095496,3305111552,
1245945524,3959478190,536870912,269582913,1264636179,1358954496,2829812954,3229560629,3019898880,3655305709,3594572664,2113929216,1634045814,1566518622,2600468480,3252942604,
1577006528,1879048192,2035937687,3605056486,2499805184,137231520,3235854251,1593835520,2962750011,1270925709,3120562176,3938838222,3969961776,3405774848,1384112213,1740583190,
771751936,587984226,1904266587,3825205248,2612128761,4204737405,16777216,2544882825,1061208097,100663296,789959186,3026140679,3808428032,1583472421,2724250186,687865856,
3873167806,696204396,3422552064,3163145547,2384411345,3170893824,70501328,83936503,1476395008,1967640295,322910394,2449473536,3455961212,2552284828,1996488704,0,
0,0,1443256453,2824948644,2566914048,2886512907,1354929993,838860800,4195019150,4171488493,2868903936,3768804493,714789044,2164260864,3064282120,2197527312,
402653184,1286591878,2052605949,3003121664,447319299,3526954073,704643072,2046611329,3727318863,3875536896,804951812,1984632043,2113929216,3589308042,2397620230,3573547008,
2213946895,646546338,1275068416,2573183756,4105211899,1711276032,3478778761,1557251167,4278190080,894638599,2758940850,1409286144,1666531970,202593046,3439329280,4093222659,
3159670431,3456106496,2785003398,339080507,1459617792,1609903624,3969264086,4227858432,166950541,1157063282,1694498816,324729742,2530111019,1325400064,1163698955,1051665807,
3590324224,3210103429,3322739042,2097152000,3914338816,1852682950,3825205248,2315604098,1652482512,687865856,3691186183,3391072884,2952790016,638181769,851211929,452984832,
1880078604,2598190397,2181038080,1789277199,1222914404,2818572288,1017146506,3766844096,822083584,3333063940,405186093,2583691264,2427248001,2957503881,50331648,1598634140,
4088824601,2030043136,156196889,1540868285,3758096384,4081420695,2742293584,1258291200,2772685074,185950196,3523215360,3219807249,3643560877,4160749568,3924558996,1900877833,
1627389952,333901082,2314126564,3388997632,1172354463,563056448,1392508928,649459485,765254742,2650800128,1890824088,2247989234,117440512,2327397910,2103331615,2885681152,
3703512723,3577675963,889192448,3323368336,117837026,520093696,2417019669,2942781254,2248146944,1780097691,1472502699,754974720,1008499230,4289056783,3019898880,2897258399,
1340226950,3070230528,4206296858,3884152354,771751936,12326548,522234575,2231369728,1455050257,3074548075,469762048,1276363538,1702423858,905969664,437623703,3441010326,
2936012800,3760157209,901413499,67108864,3055102620,2648388063,2634022912,3578554398,2445828809,1342177280,2202677403,967387501,3372220416,2034293013,3238720896,1644167168,
793149840,1768668708,4211081216,904858771,3142759037,3506438144,1676235798,322173401,1207959552,2581839256,3952092468,3808428032,3487950109,1139895952,2046820352,3197268281,
3882681906,4060086272,3902024124,1326206358,1795162112,312393778,3081736571,3221225472,1150851255,533650143,1493172224,1580275124,3455571590,1929379840,137841969,1704369442,
3925868544,4064126143,2637513167,1090519040,2755394618,894700139,3623878656,3345923768,960977277,352321536,2439571005,2435191513,2348810240,1801588659,1770376756,654311424,
1029986102,3252979088,3187671040,667802165,333285833,2483027968,1909162672,3149709933,218103808,2344708926,1126112896,2785017856,3720819643,3950925092,1056964608,1298918970,
1530509485,1006632960,460175039,4082692873,2768240640,3781648177,201011172,234881024,3076589492,2744804416,2533359616,2915601079,1906534425,3170893824,4224635442,3653379005,
603979776,29637564,560070480,2399141888,1472357177,2298524916,369098752,882319803,2232674274,3674210304,1653700926,762489926,1107296256,2560331952,3587272875,3909091328,
3466446901,2108701455,1879048192,3560195382,2945005398,1509949440,2184322483,132676850,3271557120,2016998461,4283146271,1744830464,775859384,1462430651,4043309056,3789244837,
349930795,2332033024,3084718368,3166359183,301989888,1305999534,1142493794,3103784960,466722859,3967310278,536870912,24653096,1044469151,167772160,1467905453,2518687291,
2466250752,2910100515,1854128854,939524096,4218602662,3336735090,2701131776,2552727076,3404847716,1811939328,3458326177,1653641664,4110417920,875247407,2587053357,1577058304,
1647144874,844236425,3338665984,2021974697,3765111504,3976200192,780319276,1208631668,1946157056,3565704098,2963905945,3741319168,2190347047,415815229,1174405120,304273062,
2827959220,1157627904,1143246371,15626256,3690987520,3190712237,4165840125,1996488704,3894951720,1345120089,3992977408,4068586027,2182474496,3288334336,2760370862,712286372,
1560281088,1586299680,3537337417,4127195136,143350693,2058762221,1862270976,1809717543,1990550779,2717908992,1037582754,3737399135,989855744,3352471596,644346802,2415919104,
2446651561,2382805014,150994944,2340257194,1547678799,587202560,3715835183,4099866603,3120562176,661769377,217916166,285212672,1903662116,2761713826,2281701376,3315524840,
1170600515,16777216,2476260461,3986995687,2550136832,1771197923,352806154,855638016,1066667366,3177590446,2852126720,624787557,1868505847,2147483648,1933301984,3342756179,
419430400,2301702510,1067300286,2986344448,3744950763,2549939738,721420288,3160550249,2616175884,3858759680,3932451820,865003176,2130706432,275683938,3408738885,3556769792,
1181270759,1665954273,1291845632,1556172772,2977267128,1728053248,180819809,420754972,4261412864,4040031983,3786926833,1426063360,2798364266,1238802773,3422552064,912751595,
4187049180,3472883712,1616978798,1374685048,1442840576,2590755552,2840845205,4244635648,3429732965,20090929,1677721600,3603177318,3540753512,1308622848,2160216035,2070599628,
3607101440,2059972205,2210990881,2080374784,751761128,732446853,3841982464,1335604330,666571667,671088640,429780207,2413451319,2969567232,3818325345,2004452570,436207616,
3046202852,3742945150,2197815296,2939736295,220316455,2835349504,4181624930,2772469891,805306368,53764588,1575179374,2600468480,1429354857,4118945738,33554432,2597837940,
3061018970,2013265920,3436283121,504511230,3774873600,920350079,3870418451,1241513984,1625110010,1322298807,3539992576,2054469881,2632557038,4177526784,745726076,881388106,
1610612736,3598191090,3425384103,3405774848,2155762039,1682603267,1375731712,3811251189,1750674965,2667577344,3039644528,3224921521,100663296,1327997694,949729628,2902458368,
421657211,2432365304,872415232,59275128,1120140961,503316480,1435381757,3936531717,2264924160,2944714355,302082536,738197504,4186087158,3126862412,3036676096,1764639607,
170381253,3053453312,1059593202,2722530401,788529152,3307401852,1524979852,2214592512,2468653817,4068741928,486539264,2307729402,549265265,922746880,3750461311,2296141013,
2919235584,629249777,1887406136,83886080,1938280052,3625894812,2617245696,282234102,3557658762,1358954496,1188353139,2087508782,3355443200,3168681469,2228160451,1660944384,
3940050296,749620327,4194304000,4033996923,4271325246,3489660928,2792861950,1458965402,1224736768,1551718768,2924861303,3791650816,175833589,104111315,2063597568,2064422353,
2728981617,4076863488,755682644,180994005,1778384896,3607110874,4067058488,3238002688,2164685919,1510680732,1476395008,2611999068,2284987589,1912602624,3450448345,542338913,
3942645760,933445719,3639653260,1073741824,1638209746,1888614440,3640655872,49306192,2088938302,335544320,1425408725,3571703962,2365587456,2935810907,742407287,637534208,
4177179614,2216785875,3204448256,3797106397,1444445066,2499805184,3025495640,4269355054,201326592,1314885590,115010755,2801795072,408541011,2931533671,1040187392,2297760466,
519850734,1023410176,3740488279,3063742794,2751463424,620346329,1312742823,251658240,1929372508,3865024003,2516582400,1750494815,879139418,3154116608,1045444314,2617758206,
620756992,3294289748,1688472851,2382364672,2455537617,3435480759,385875968,4043949395,3235255713,3657433088,2802818518,1756847621,1124073472,1560638552,2417263336,3892314112,
184757469,947243340,1895825408,296395230,3930899733,1526726656,1202518363,1110281905,3254779904,3181777109,3129889372,1761607680,3953150032,317659640,4026531840,608546125,
1360951144,2315255808,1917056456,4185865420,318767104,2286492742,31252513,3087007744,3729736899,2847779717,553648128,3303459264,2072291292,184549376,2464190789,3555060856,
2449473536,1760196811,726020245,956301312,1055662158,2200402737,2684354560,1572430540,2402560039,1828716544,197081673,659907459,4093640704,4055225287,3757490030,1593835520,
2813561666,2006447306,3321888768,3172599361,2779707539,3959422976,3944505028,231715639,1962934272,286701386,4117524442,3724541952,1192292303,1561142398,1191182336,3619435086,
3981101559,1140850688,2176477899,1160479315,3707764736,2075165509,3179830974,1979711488,766958528,367596826,4009754624,924800707,3352303939,3305111552,1629032006,1873892071,
1543503872,2601773000,2534575626,4143972352,3440754509,1064551854,1845493760,2923494863,861968056,2734686208,4165379402,2600590620,973078528,38554820,1671561713,2432696320,
1414140993,3418573397,134217728,1323538754,435832332,570425344,417710535,2979728808,3137339392,3807324233,1228460357,268435456,3035197644,3780745953,2298478592,0,
0,0,864538443,9706144,3875536896,1729076886,19412289,3456106496,1418219997,29110241,687865856,3458153772,38824579,2617245696,4254659175,46428195,
2063597568,2836439994,58220482,1375731712,2593615089,65815906,3036676096,612662467,2411670305,3707764736,386118536,2401972609,973078528,1133240917,2392268384,318767104,
1879846174,2382562496,4093640704,3936043503,2381267362,1090519040,3642527396,2373671682,2785017856,2375343993,2361881827,2399141888,3188920370,2354277955,1744830464,1225324935,
528373315,3120562176,2056206028,535448803,1560281088,772237073,508977922,1946157056,494970970,516061602,2466250752,2266481835,489569472,637534208,3029339104,498738784,
3238002688,3759692349,470157697,3892314112,3550451062,479335201,251658240,1837925700,2428599650,1728053248,1577798159,2421516226,2147483648,176364498,2447984675,2835349504,
956617881,2440909443,1308622848,2744367208,2458982369,4211081216,2417260323,2449804609,469762048,3298567934,2478383776,889192448,4145801653,2469214208,3523215360,2450649870,
1056746631,1946157056,2710977605,1047049767,2466250752,4112412056,1070897606,3120562176,3331957459,1061192550,1560281088,1544474146,1017955844,3892314112,1871249769,1010359460,
251658240,989941940,1032123205,637534208,143040511,1024518629,3238002688,3063254989,2973992870,2835349504,2232565894,2983697670,1308622848,3516535131,2959848167,1728053248,
3793608208,2969544775,2147483648,2022355681,3004427557,889192448,1259175338,3012032389,3523215360,528821367,2990266468,4211081216,738386748,2997863108,469762048,3675851401,
562232004,3456106496,3902719426,555147364,687865856,3155596319,548065157,0,2408667988,540988709,3875536896,352728997,601002055,1375731712,646052078,591825639,
3036676096,1913235763,586851590,2617245696,1099851384,577683366,2063597568,4288509514,2923287013,318767104,3424303361,2930363205,4093640704,2559764700,2937447588,3707764736,
2870290327,2944531972,973078528,830622566,2892872550,2399141888,33915949,2902041030,1744830464,1452135920,2907016743,1090519040,1695161019,2916193415,2785017856,2627330183,
4142311208,218103808,2937991116,4134714760,3925868544,4220943889,4157510249,3271557120,3356602714,4149905609,603979776,1384570283,4105620907,2432696320,1627460320,4095923979,
1979711488,898188093,4120836330,1593835520,101616758,4111131210,3087007744,3088948292,2035911689,3489660928,2342146831,2043516585,922746880,3742499538,2020718920,503316480,
3969240473,2028315624,4177526784,1979883880,2064246410,1275068416,1166372387,2073951274,2868903936,286081022,2049037259,2181038080,579530933,2058733931,1694498816,3583056128,
3919114603,3070230528,3860256331,3909938123,1342177280,2996733846,3903898666,2030043136,2165917917,3894730378,2650800128,462300204,3955792872,721420288,671738727,3948708168,
3422552064,2088876730,3940593321,3841982464,1325823473,3933516809,33554432,4044711363,1713887818,1778384896,3264391816,1723056362,2365587456,2518350677,1729097483,2751463424,
2778543134,1738274219,1124073472,1057642735,1685565641,4127195136,210605988,1692641897,285212672,1476773497,1700758920,939524096,1803684146,1707843368,3741319168,243798921,
3357150127,2030043136,1024449730,3364753679,2650800128,1770491167,3375513326,3070230528,1509966420,3383108686,1342177280,3231133349,3393872172,3841982464,4077969902,3403578252,
33554432,2811801651,3412218989,721420288,2485092216,3421916877,3422552064,705457994,1202004110,2751463424,428580865,1194408494,1124073472,1292104156,1183651279,1778384896,
2122595991,1176047471,2365587456,3826471526,1173703181,939524096,3616841005,1164005549,3741319168,2199702768,1155366732,4127195136,2962949051,1145660908,285212672,1199630862,
3613679084,3271557120,1946625349,3622848332,603979776,546272408,3595331757,218103808,319339475,3604509197,3925868544,2308953890,3576969071,1593835520,3122141289,3584044495,
3087007744,4002433460,3558605358,2432696320,3709306623,3565688974,1979711488,1661245133,1490777805,503316480,1350785414,1481600109,4177526784,67831899,1509114764,3489660928,
931972880,1499945260,922746880,2904271841,1519066190,2181038080,2661049514,1511982830,1694498816,3390322039,1537419535,1275068416,4187224636,1530344367,2868903936,2173290388,
1725083766,4278190080,2987264223,1715907286,402653184,3867564290,1744471351,822083584,3573651017,1735303063,3590324224,1335294648,1686297333,1660944384,2081502707,1679212629,
2214592512,681141294,1705701300,2902458368,454994789,1698624788,1241513984,2769140567,3916274519,570425344,2525656092,3925443063,3305111552,3254920641,3896880662,3959422976,
4052085386,3906057398,184549376,1796376187,3946705364,3187671040,1486178608,3953781620,1493172224,203233517,3927295125,1879048192,1067112358,3934379573,2533359616,3363913235,
2041374261,1157627904,4211536216,2033777813,2717908992,2945360005,2021970804,2332033024,2617864142,2014366164,1811939328,111018815,2080148662,3640655872,890883188,2070451734,
1040187392,1636933033,2060761591,385875968,1377194722,2051056471,4026531840,3959767760,4128492820,2550136832,3749875099,4136097716,2130706432,2332744774,4147902549,1442840576,
3096253197,4155499253,2969567232,572162044,4098074519,67108864,295547063,4107779383,3808428032,1159061866,4117467862,3388997632,1989291553,4127164534,754974720,328742042,
1479417073,2332033024,538966993,1488586321,1811939328,1956096524,1493576112,1157627904,1192256839,1502753552,2717908992,3716614582,1518237298,385875968,3993028349,1525312722,
4026531840,3129513760,1532379955,3640655872,2299484267,1539463571,1040187392,924600409,3616618448,1442840576,77301522,3607440752,2969567232,1343477455,3602449041,2550136832,
1670650244,3593279537,2130706432,4177753461,3586219347,3388997632,3397696062,3579135987,754974720,2651646947,3572066322,67108864,2911577256,3564991154,3808428032,1519439133,
1196444338,822083584,1763115606,1204047890,3590324224,1033851787,1182302195,4278190080,236494016,1189897555,402653184,2492461105,1157636145,2902458368,2802335610,1167342225,
1241513984,4085280423,1143477616,1660944384,3221725676,1153175504,2214592512,2115285470,3371131283,3959422976,1301511829,3363535667,184549376,421211976,3385283794,570425344,
714924035,3377679986,3305111552,2953546994,3401517840,1879048192,2207007673,3391820208,2533359616,3607368292,3415686737,3187671040,3833847087,3405980913,1493172224,487597843,
2419332958,4060086272,781707352,2426408446,352321536,2048899461,2434540063,1006632960,1234728654,2441623743,3674210304,3540982335,2456059357,1845493760,3767063924,2465228669,
2298478592,3019932841,2471250076,2684354560,2273790946,2480427580,1191182336,966024144,529218687,788529152,169055387,522135263,3355443200,1587266886,514001214,3774873600,
1830554125,506925982,100663296,4153108220,500913916,3003121664,3289164215,491736156,1409286144,2424633450,485712829,2097152000,2734896929,476543261,2583691264,1410915988,
2404008221,1207959552,1738478047,2413714365,2936012800,857161730,2388816988,2248146944,9473865,2398514940,1627389952,2584208312,2367302558,3556769792,2843749619,2374906174,
855638016,4245191982,2352094943,436207616,3465523813,2359690367,4244635648,1889313367,16083516,2499805184,1125870876,6385820,1912602624,395525313,31285117,1526726656,
605352842,21579229,3154116608,3196297083,44368063,150994944,2365870128,36772383,3992977408,3649831405,59586046,3338665984,3926642342,51982174,536870912,2399261725,
2932390873,2248146944,3162905430,2925306233,1627389952,3893250699,2950729368,1207959552,3683222976,2943652920,2936012800,1092544817,2895696218,436207616,1922639482,2886519802,
4244635648,638678951,2914051099,3556769792,362199276,2904882875,855638016,2877663454,561484024,1526726656,2550294421,568560216,3154116608,3431609928,543139257,2499805184,
4279105795,550223641,1912602624,1704629746,589822587,3338665984,1444764345,598991067,536870912,43322212,571461434,150994944,823313455,580638106,3992977408,3322490266,
2981555610,1006632960,4119782097,2971858746,3674210304,2701570828,2963200219,4060086272,2457959495,2953495163,352321536,135663798,3018229529,2684354560,999415805,3010633145,
1191182336,1863945760,2999890520,1845493760,1553875307,2992285944,2298478592,3800912217,1040828091,3774873600,3507133970,1050532891,100663296,2239942607,1059189754,788529152,
3053781124,1068886362,3355443200,747793525,1012509752,2097152000,521511742,1020114584,2583691264,1268642531,1030855033,3003121664,2014985640,1038451673,1409286144,0,
0,0,3148450227,1186635467,452984832,3488159229,107660208,3539992576,1950391374,1087397243,3355443200,661138785,2278193479,1124073472,2629936338,3245401996,
1476395008,3900782748,2174794487,2415919104,1395175727,3340379196,2332033024,1322277571,261419662,2248146944,4118401904,1227779141,2634022912,2168016702,167653694,1426063360,
982566541,1329901557,1308622848,1773696930,2287897545,3305111552,3524394513,3471054082,3724541952,2790351455,2385791097,369098752,502852588,3364804274,218103808,2644555142,
522839325,201326592,638139445,1502837718,385875968,1380556923,423831213,3741319168,3923782088,1610201190,3288334336,3133708519,2565053530,1325400064,23138644,3730375313,
1409286144,1965133082,2659803114,2617245696,3465020585,3627270433,2264924160,3547393861,280827795,2315255808,1759078134,1443334488,2432696320,479853240,383243299,1493172224,
2804970251,1349339880,1107296256,4095263268,2541186772,3372220416,1337019287,3519934495,3523215360,1005705177,2434641252,436207616,2153274986,3618059183,16777216,2214292887,
3041670172,4244635648,944956452,4093029079,3858759680,1276278890,3005675436,771751936,4156289497,4120668519,889192448,2761113846,847662427,3187671040,523946309,1950143376,
2768240640,1803179275,887918315,1828716544,3503545528,1918242848,1979711488,3442161492,3134768786,2063597568,1988280039,4234303577,1610612736,46277289,3165783330,2818572288,
3110841114,4194868201,3003121664,3930266165,1024638933,939524096,1374327686,2074616094,587202560,631902152,997751909,3942645760,2651031163,2109924014,4026531840,509335569,
2858799361,4043309056,2784121250,3974057930,3925868544,3518156268,2886668977,570425344,1780171871,3937766522,956301312,959706480,766486598,2986344448,2191162563,1796552333,
2835349504,4141539469,734358518,1627389952,1299409214,1837102397,2046820352,1351320274,2784043919,1996488704,3944876897,3813391684,1811939328,2674038575,2744901695,2751463424,
617291420,3844177652,3204448256,2011410355,574315208,872415232,3427411456,1686225923,788529152,3087710798,609327480,3875536896,61027325,1659570099,4227858432,3209485748,
3783759391,520093696,82138119,2805795028,67108864,1889912905,3891090863,3422552064,3406578170,2706885476,3607101440,2552557781,1716383576,1543503872,596474214,553087379,
1191182336,1473111336,1613180136,2399141888,3966004379,647868963,2483027968,4053567351,3994248337,2566914048,1244991172,2829711962,2181038080,1047892618,3900286753,1241513984,
2245794617,2932029930,1358954496,3606358550,1775836630,3657433088,1834820517,795050781,3238002688,421380075,1874058854,150994944,2729719384,688472237,301989888,585918514,
4272845570,318767104,2571493761,3088379337,134217728,3976560079,4173639858,3221225472,1454175356,3195940473,3674210304,92554579,2036599365,1342177280,3190672608,1071551630,
1258291200,3396161710,2131675637,2197815296,1908726045,968120126,2550136832,1815884529,4047143308,2499805184,3616914242,3078627143,2382364672,2748655372,4149232188,1174405120,
410824383,2984959223,1560281088,1263804304,1995503819,3590324224,4043150883,810182144,3439329280,2226981485,1889155963,83886080,1058309086,908109232,503316480,1018671139,
1422631427,3791650816,2266904976,309411016,4177526784,4083066334,1386308019,822083584,1224158317,337379192,704643072,467639618,3540114244,2701131776,2692093169,2512078223,
3120562176,3560343743,3580565748,1912602624,1872691468,2479982143,1761607680,1919412960,1532973197,1677721600,3385746259,501599814,2130706432,3180265245,1563792189,3070230528,
103249582,462360054,2885681152,1427097473,3700763082,654311424,4003876402,2586818305,1006632960,2598818428,3674204794,4093640704,558848975,2621797553,4009754624,2702640549,
1273120542,3992977408,448695318,223926741,4110417920,1862144088,1300792494,1023410176,3579288043,187832933,637534208,2256480452,3425189465,2902458368,1037476215,2324865170,
3053453312,1234582841,3393388009,2113929216,4064261258,2365088546,1694498816,4022820710,1148630416,1744830464,1416550101,46934875,1929379840,539904667,1109161504,3137339392,
2609365800,78047467,2684354560,3366941191,3283930327,721420288,1929837492,2231783964,805306368,122054650,3319140199,4160749568,3169840713,2204930476,3808428032,3324231154,
1209061912,3674210304,2106209345,246041811,3221225472,164276239,1316622760,134217728,2992841148,146837347,318767104,3779825811,3487214431,2550136832,1524767008,2304783764,
2197815296,782402926,3383781615,1258291200,2500529373,2399860260,1342177280,2297685809,1199841430,1560281088,861564546,20889181,1174405120,1192948428,1106174758,2382364672,
4239620991,122977773,2499805184,2946222672,3226360273,503316480,338838499,2264188698,83886080,1618141101,3324287585,3439329280,3688584734,2157839530,3590324224,1535314036,
1463367429,3607101440,3760882119,293841358,3422552064,2489982345,1364456629,67108864,801346618,401173118,520093696,2095785237,3505606210,2483027968,3343035558,2521419913,
2399141888,3003265256,3600387570,1191182336,145471835,2418217785,1543503872,357782199,1487783307,1358954496,2935675652,504847168,1241513984,3669641034,1590101563,2181038080,
1628688121,410884336,2566914048,842760150,3748117708,301989888,2308109925,2581406215,150994944,4258425387,3641540476,3238002688,1182524312,2679628215,3657433088,1171837029,
4250723844,637534208,4268841430,3152443599,1023410176,2318517656,4214629812,4110417920,832064555,3180116863,3992977408,1655766276,2056691523,1694498816,3642324151,1009516936,
2113929216,2908350713,2096913651,3053453312,384852298,977715768,2902458368,185109158,4073198730,2684354560,2963342101,3027405377,3137339392,3303120731,4104312634,1929379840,
2135430888,2987936241,1744830464,744531911,1963093453,3808428032,2546544244,867758854,4160749568,3817452090,1936240253,805306368,1478507401,902967478,721420288,3631769059,
3799319321,704643072,1674701904,2765069778,822083584,395407390,3827286185,4177526784,2889415085,2728746594,3791650816,4279257218,1707047518,1761607680,1153024305,587588757,
1912602624,821648767,1674951150,3120562176,2337330380,628041509,2701131776,2527608608,3991007639,2885681152,755086995,2874896220,3070230528,1497443037,3951768103,2130706432,
3806897006,2905713900,1677721600,2982154817,1781237968,4009754624,174693362,747705883,4093640704,2116618172,1816218464,1006632960,3313536527,721147307,654311424,2037342278,
2845262855,3288334336,3267815925,4012759756,3741319168,3062265275,2952628151,385875968,221248520,3913750908,201326592,1577536807,777862464,2264924160,3853436052,1760011147,
2617245696,2448316634,674758384,1409286144,709349737,1854758971,1325400064,935279237,2785261193,1107296256,2350297910,3770230850,1493172224,4166397816,2691265849,2432696320,
1140827851,3872648178,2315255808,282531812,566874062,16777216,2877202007,1735610629,436207616,3745382937,664996990,3523215360,1687653290,1629065909,3372220416,3838825920,
3065946394,3355443200,1600543859,4026810321,3539992576,723959869,2966708906,452984832,2425309582,4134468705,0,3282565281,829741149,2332033024,2014212370,2010007190,
2415919104,206499164,924720109,1476395008,3085395183,1906607398,1124073472,2854194947,3106558868,1308622848,297141936,4287679839,1426063360,1710660350,3208679460,2634022912,
3730772813,4193914607,2248146944,2373427810,1054878419,218103808,920529873,2019210264,369098752,1117697951,948627811,3724541952,4181147180,2117105576,3305111552,4204006865,
484143131,956301312,1094550626,1516367568,570425344,897390636,447853483,3925868544,2396295583,1544236384,4043309056,3724288176,2601584988,2046820352,1716889859,3719010199,
1627389952,303379789,2642135788,2835349504,2847718654,3686880295,2986344448,3024377618,323977877,3204448256,267247265,1442126942,2751463424,2074952431,354763045,1811939328,
3221539676,1402986478,1996488704,2469165683,2491808722,4227858432,679867328,3527370009,3875536896,1556443022,2465151074,788529152,3882673725,3562383017,872415232,1731508311,
66229510,889192448,3701289444,1162349517,771751936,2833100202,93869750,3858759680,326378521,1126353021,4244635648,1079809334,2218323009,1979711488,4227144837,3263328906,
1828716544,2411036875,2186424305,2768240640,874252664,3303584058,3187671040,702866068,208037768,3003121664,2454547239,1255995715,2818572288,3859674985,168600632,1610612736,
1571061466,1287011059,2063597568,244109301,2343313103,4026531840,3039118918,3440803844,3942645760,3244677640,2378620287,587202560,2060211131,3413918644,939524096};

uint32_t ecc_buf[3];
uint32_t ecc_buf2[3];
unsigned int xi_tab[9] = {0,32,34,340,38,238,348,72,54};
unsigned int syn[16];
int cache[16];
struct bch_control ecc_bch={
.m = 9, 
.t = 8, 
.n = 511, 
.ecc_bytes = 9, 
.ecc_bits = 72, 
.a_pow_tab = a_pow_tab, 
.a_log_tab = a_log_tab, 
.mod8_tab = mod8_tab, 
.ecc_buf = ecc_buf, 
.ecc_buf2 = ecc_buf2, 
.xi_tab  = xi_tab,  
.syn = syn,  
.cache = cache, 
}; 
