------------------GROUP_16_ASSIGNMENT_2------------------
	Created by Blain Cribb and Jerry Yang

To get the program running:

	1. Open the QUARTUS folder
	2. Open Lab1.qpf
	3. Open device programmer and program the board
	4. Open NIOS with the workspace "D:\group_16"
	5. Run as a NIOS II device

SCCharts

Pacemaker.c is the main file.
system.h is our generated hardware header.
sccharts.c is the SCCharts auto-generated code.
sccharts.h is where we declare inputs and outputs for SCCharts.
timeouts.h is where we define timeout values.

On the board the four right-most LEDS (LED3 down to LED0) represent the following

	| APase | VPase | ASense | VSense |

To switch modes use SW0, down for mode 1 (LEDR0 off), up for mode 2 (LEDR0 on)

Mode Specifics:

	Mode 1: Use KEY1 and KEY0 to the atrium and ventricle events respectively
		Press KEY1 to start the Pacemaker
	
	Mode 2: Runs as expected