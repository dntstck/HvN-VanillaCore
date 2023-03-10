#include <stdio.h>

void WriteVersion()
{
#ifndef __WIN32__
	FILE* fp = fopen("ver.txt", "w");

	if (fp)
	{
		fprintf(fp, "emulated game server revision: %s\n", __SVN_VERSION__);
		fclose(fp);
	}
#endif
}

