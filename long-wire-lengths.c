/*
 * Simple calculations of half wavelengths of ham bands.
 *
 * Mike Markowski AB3AP
 * Thu Jun 28 07:01:26 EDT 2012
 *
 * Updated by Matt M5MAT
 * 10:57 08/02/2021
 *
 *  Convert to metric
 *  Changed to UK band edges
 */

#include <stdio.h>

main() {
	printHalfwaves();
}

/*
 * Print ranges of half wavelengths for ecah ham band.
 */
printHalfwaves() {

//	rw(1810., 2000.);       /* 160m */
	rw(3500., 3800.);       /* 80m */
	rw(5258.5, 5406.5);     /* 60m */
	rw(7000., 7200.);       /* 40m */
	rw(10100., 10150.);     /* 30m */
	rw(14000., 14350.);     /* 20m */
	rw(18068., 18168.);     /* 17m */
	rw(21000., 21450.);     /* 15m */
	rw(24890., 24990.);     /* 12m */
	rw(28000., 29700.);     /* 10m */
	rw(50000., 52000.);     /* 6m */
}

/*
 * For a given frequency range, calculate the half wavelength range and print
 * it.  In addition, print up to 4th multiples of each range up to the length
 * of 160m half wavelength.
 *
 * Comments are also printed out, assuming that the output will saved to a file,
 * and that file used by gnuplot for plotting.
 */
rw(double min_kHz, double max_kHz) {
	
	double lambda0_m, lambda1_m;
	double loFreq_MHz = 3.5;
	double c = 300000000;
	double lambdaMax_m = c / ( loFreq_MHz * 1e6); /* Max wavelength in band. */
	int n;

	double qtr_m = c / ( loFreq_MHz * 1e6 ) / 4;
	printf("# %.3f to %.3f kHz, too short for %f MHz\n",
		min_kHz, max_kHz, loFreq_MHz);
	printf("%.3f 0\n%.3f 1\n%.3f 1\n%.3f 0\n\n",
		0., 0+(1e-3), qtr_m, qtr_m+(1e-3));
	
	n = 1; /* First multiple. */
	do {
		lambda0_m = n * c / (max_kHz * 1e3);
		lambda1_m = n * c / (min_kHz * 1e3);
		/* Print in format gnuplot expects. */
		printf("# %.3f to %.3f kHz, multiple %d\n",
			min_kHz, max_kHz, n);
		printf("%.3f 0\n%.3f 1\n%.3f 1\n%.3f 0\n\n",
			lambda0_m-(1e-3), lambda0_m,
			lambda1_m, lambda1_m+(1e-3));
		/* Prepare for next multiple. */
		n++;
	/* Change '5' in next line to max number of multiples to calculate. */
	} while (lambda1_m < lambdaMax_m && n < 5);
}
