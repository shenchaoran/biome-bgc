/* 
output_init.c
Reads output control information from initialization file

*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
Biome-BGC version 4.2 (final release)
See copyright.txt for Copyright information

Revisions from version 4.1.2:
Seperated init scanning and outputfile opening.
This function now opens output files. Output controls
are now read from output_ctrl.c

Revisions from version 4.1.1:
Fixed error in ascii output file that incorrectly gave the 
units for annual precipitation as cm/year - the real units are mm/yr.
*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
*/

#include "pointbgc.h"

int output_init(output_struct* output)
{
  int ok = 1;
  extern char *currentFN, *outputFN;
  currentFN = outputFN;
	/* open outfiles if specified */
	if (ok && output->dodaily)
	{
		strcpy(output->dayout.name,output->outprefix);
		strcat(output->dayout.name,".daily.ascii");
		if (file_open(&(output->dayout),'w'))
		{
			bgc_printf(BV_ERROR, "Error opening daily outfile (%s) in output_ctrl()\n",output->dayout.name);
			ok=0;
		}
		else
		{
			bgc_printf(BV_WARN, "Opened binary daily output file in write mode\n");
		}
	}
	
	if (ok && output->domonavg)
	{
		strcpy(output->monavgout.name,output->outprefix);
		strcat(output->monavgout.name,".monthly-avg.ascii");
		if (file_open(&(output->monavgout),'w'))
		{
			bgc_printf(BV_ERROR, "Error opening monthly average outfile (%s) in output_ctrl()\n",output->monavgout.name);
			ok=0;
		}
	}
	if (ok && output->doannavg)
	{
		strcpy(output->annavgout.name,output->outprefix);
		strcat(output->annavgout.name,".annual-avg.ascii");
		if (file_open(&(output->annavgout),'w'))
		{
			bgc_printf(BV_ERROR, "Error opening annual average outfile (%s) in output_ctrl()\n",output->annavgout.name);
			ok=0;
		}
	}
	if (ok && output->doannual)
	{
		strcpy(output->annout.name,output->outprefix);
		strcat(output->annout.name,".annual.ascii");
		if (file_open(&(output->annout),'w'))
		{
			bgc_printf(BV_ERROR, "Error opening annual outfile (%s) in output_ctrl()\n",output->annout.name);
			ok=0;
		}
	}
	
	/* Yeah, we need make this not happen on spinup */
	/* Spinngo is going to make this look like doodoo */
	if (ok && output->bgc_ascii && output->doannual)
	{
		/* simple text output */
		strcpy(output->anntext.name,output->outprefix);
		strcat(output->anntext.name,".summary.ascii");
		if (file_open(&(output->anntext),'o'))
		{
			bgc_printf(BV_ERROR, "Error opening annual text file (%s) in output_ctrl()\n",output->anntext.name);
			ok=0;
		}
		/* write the header info for simple text file */
		fprintf(output->anntext.ptr,"Annual summary output from Biome-BGC version %s\n",VERS);
		fprintf(output->anntext.ptr,"ann PRCP = annual total precipitation (mm/yr)\n");
		fprintf(output->anntext.ptr,"ann Tavg = annual average air temperature (deg C)\n");
		fprintf(output->anntext.ptr,"max LAI = annual maximum value of projected leaf area index (m2/m2)\n");
		fprintf(output->anntext.ptr,"ann ET = annual total evapotranspiration (mm/yr)\n");
		fprintf(output->anntext.ptr,"ann OF = annual total outflow (mm/yr)\n");
		fprintf(output->anntext.ptr,"ann NPP = annual total net primary production (gC/m2/yr)\n");
		fprintf(output->anntext.ptr,"ann NPB = annual total net biome production (gC/m2/yr)\n\n");
		fprintf(output->anntext.ptr,"%6s%10s%10s%10s%10s%10s%10s%10s\n","year","ann PRCP","ann Tavg",
			"max LAI","ann ET","ann OF","ann NPP","ann NBP");

	}
	return (!ok);
}
