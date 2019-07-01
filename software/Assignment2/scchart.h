/*
 * scchart.h
 *
 *  Created on: 16/09/2018
 *      Author: bcri429
 */

#ifndef SCCHART_H_
#define SCCHART_H_

// Functions
void reset();
void tick();

// Timeouts
extern char LRITO;
extern char PVARPTO;
extern char URITO;
extern char AEITO;
extern char AVITO;
extern char VRPTO;

// Signals
extern char LRI_start;
extern char LRI_stop;
extern char PVARP_start;
extern char PVARP_stop;
extern char URI_start;
extern char URI_stop;
extern char AEI_start;
extern char AEI_stop;
extern char AVI_start;
extern char AVI_stop;
extern char VRP_start;
extern char VRP_stop;

// Inputs
extern char VSense;
extern char ASense;
extern char ERROR;


// Outputs
extern char VPase;
extern char APase;


#endif /* SCCHART_H_ */
