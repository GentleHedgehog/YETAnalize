#ifndef YETFILLER_H
#define YETFILLER_H

#include "yetanalizer.h"

void fillAnalizerWithYetInfo(YetAnalizer &analizer)
{
    analizer.registerTypeWithValue("СТО", "001", 0.31 );
    analizer.registerTypeWithValue("СТО", "002", 0.5  );
    analizer.registerTypeWithValue("СТО", "003", 0.96 );
    analizer.registerTypeWithValue("СТО", "004", 0.35 );
    analizer.registerTypeWithValue("СТО", "005", 0.61 );
    analizer.registerTypeWithValue("СТО", "006", 0.76 );
    analizer.registerTypeWithValue("СТО", "015", 0.5  );
    analizer.registerTypeWithValue("СТО", "022", 0.87 );


    analizer.registerTypeWithValue("СТТ", "005",    1.68 );
    analizer.registerTypeWithValue("СТТ", "006",    1.18 );
    analizer.registerTypeWithValue("СТТ", "017",	0.42 );
    analizer.registerTypeWithValue("СТТ", "020",	1    );
    analizer.registerTypeWithValue("СТТ", "022",	0.7  );
    analizer.registerTypeWithValue("СТТ", "025",	1    );
    analizer.registerTypeWithValue("СТТ", "026",	0.53 );
    analizer.registerTypeWithValue("СТТ", "027",	0.95 );
    analizer.registerTypeWithValue("СТТ", "028",	1.35 );
    analizer.registerTypeWithValue("СТТ", "029",	0.5  );
    analizer.registerTypeWithValue("СТТ", "030",	1.15 );
    analizer.registerTypeWithValue("СТТ", "031",	2    );
    analizer.registerTypeWithValue("СТТ", "033",	1.25 );
    analizer.registerTypeWithValue("СТТ", "034",	1.25 );
    analizer.registerTypeWithValue("СТТ", "035",	0.25 );
    analizer.registerTypeWithValue("СТТ", "036",	0.48 );
    analizer.registerTypeWithValue("СТТ", "037",	1.16 );
    analizer.registerTypeWithValue("СТТ", "038",	0.21 );
    analizer.registerTypeWithValue("СТТ", "039",	0.46 );
    analizer.registerTypeWithValue("СТТ", "041",	0.32 );
    analizer.registerTypeWithValue("СТТ", "044",	0.92 );
    analizer.registerTypeWithValue("СТТ", "045",	1.71 );
    analizer.registerTypeWithValue("СТТ", "046",	0.5  );
    analizer.registerTypeWithValue("СТТ", "048",	2    );
    analizer.registerTypeWithValue("СТТ", "049",	1    );
    analizer.registerTypeWithValue("СТТ", "051",	2    );
    analizer.registerTypeWithValue("СТТ", "053",	0.03 );
    analizer.registerTypeWithValue("СТТ", "061",	1.7  );
}

#endif // YETFILLER_H
