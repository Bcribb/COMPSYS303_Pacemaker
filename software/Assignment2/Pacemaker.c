#include <stdio.h>
#include <system.h>
#include <altera_avalon_pio_regs.h>
#include <sys/alt_alarm.h>
#include <sys/alt_irq.h>
#include <fcntl.h>
#include "scchart.h"
#include "timeouts.h"

//------Defines--------
int cycle = 0;
int LRITO_set = 0;
int PVARPTO_set = 0;
int URITO_set = 0;
int AEITO_set = 0;
int AVITO_set = 0;
int VRPTO_set = 0;

//------BUTTONS--------
int buttons = 0;
void init_buttons_pio(void);
void button_isr(void* context, alt_u32 id);
int setASense = 0;
int setVSense = 0;

//------LEDS-----------
unsigned int ledOn[4] = {0, 0, 0, 0};
unsigned int ledCounts[4] = {0, 0, 0, 0};

//------TIMERS---------
static alt_alarm URITIMER;
static alt_alarm LRITIMER;
static alt_alarm AEITIMER;
static alt_alarm AVITIMER;
static alt_alarm PVARPTIMER;
static alt_alarm VRPTIMER;

alt_u32 URI_isr(void* context);
alt_u32 LRI_isr(void* context);
alt_u32 AEI_isr(void* context);
alt_u32 AVI_isr(void* context);
alt_u32 PVARP_isr(void* context);
alt_u32 VRP_isr(void* context);

//------Functions------------
void handle_timers(void);
void handle_leds(void);

//------UART-----------------
FILE * uartFile;
int fileDesc;
int sendA, sendV;

//------SWITCH---------------
int switch0;
int prevSwitch;

/* DESCRIPTION: Initialize the interrupts for all buttons
 * PARAMETER:   none
 * RETURNS:     none
 */
void init_buttons_pio(void)
{
	// Create the buttons context
	void* context_going_to_be_passed = (void*) &buttons;

	// Clear and mask
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(KEYS_BASE, 0);
	IOWR_ALTERA_AVALON_PIO_IRQ_MASK(KEYS_BASE, 0x7);

	// Start the buttons for interrupts
	alt_irq_register(KEYS_IRQ, context_going_to_be_passed, button_isr);
}



/* DESCRIPTION: Handles the Atrial and ventricle button interrupt
 * PARAMETER:   context - opaque reference to user data
 *              id - hardware interrupt number for the device
 * RETURNS:     none
 */
void button_isr(void* context, alt_u32 id)
{
	// NOTE:
	// Cast context to volatile to avoid unwanted compiler optimization.
	// Store the value in the Button's edge capture register in *context
	volatile int* value = (volatile int*)context;

	// Read buttons values then clear
	(*value) = IORD_ALTERA_AVALON_PIO_EDGE_CAP(KEYS_BASE);
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(KEYS_BASE, 0);
	printf("button: %i\n", *value);

	if (*value & 0b1) {
		// Then the right button is pushed (Ventricle)
		setVSense = 1;
		//VSense = 1;
		if(ledOn[1] == 0) {
			ledOn[3] = 1;
			ledCounts[3] = 0;
		}
	}
	if (*value & 0b10) {
		// Then the 2nd right button is pushed (Atrium)
		setASense = 1;
		//ASense = 1;
		if(ledOn[0] == 0) {
			ledOn[2] = 1;
			ledCounts[2] = 0;
		}
	}
}



/* DESCRIPTION: Handles how long each LED should be on for
 * PARAMETER:   none
 * RETURNS:     none
 */
void handle_leds(void) {

	// If the pacemaker is pasing, we should turn on leds
	if(VPase == 1) {
		ledOn[1] = 1;
		VPase = 0;
		// Flagged so we only send the V once
		sendV = 1;
	}
	if(APase == 1) {
		ledOn[0] = 1;
		APase = 0;
		// Flagged so we only send the A once
		sendA = 1;
	}


	// If our rightmost LED is on, we count to 1000 then turn it off
	if(ledOn[3] == 1) {
		IOWR_ALTERA_AVALON_PIO_DATA(LEDS_GREEN_BASE, IORD_ALTERA_AVALON_PIO_DATA(LEDS_GREEN_BASE) | 1);
		if(ledCounts[3] == 500) {
			IOWR_ALTERA_AVALON_PIO_DATA(LEDS_GREEN_BASE, IORD_ALTERA_AVALON_PIO_DATA(LEDS_GREEN_BASE) & ~1);
			ledCounts[3] = 0;
			ledOn[3] = 0;
		} else {
			ledCounts[3]++;
		}
	}

	// If our 2nd from right LED is on, we count to 1000 then turn it off
	if(ledOn[2] == 1) {
		IOWR_ALTERA_AVALON_PIO_DATA(LEDS_GREEN_BASE, IORD_ALTERA_AVALON_PIO_DATA(LEDS_GREEN_BASE) | 2);
		if(ledCounts[2] == 500) {
			ledCounts[2] = 0;
			IOWR_ALTERA_AVALON_PIO_DATA(LEDS_GREEN_BASE, IORD_ALTERA_AVALON_PIO_DATA(LEDS_GREEN_BASE) & ~2);
			ledOn[2] = 0;
		} else {
			ledCounts[2]++;
		}
	}

	// If our third from right LED is on, we count to 1000 then turn it off
	if(ledOn[1] == 1) {
		IOWR_ALTERA_AVALON_PIO_DATA(LEDS_GREEN_BASE, IORD_ALTERA_AVALON_PIO_DATA(LEDS_GREEN_BASE) | 4);
		if(ledCounts[1] == 500) {
			ledCounts[1] = 0;
			IOWR_ALTERA_AVALON_PIO_DATA(LEDS_GREEN_BASE, IORD_ALTERA_AVALON_PIO_DATA(LEDS_GREEN_BASE) & ~4);
			ledOn[1] = 0;
		} else {
			ledCounts[1]++;
		}
	}

	// If our fourth form right LED is on count to 1000 then turn it off
	if(ledOn[0] == 1) {
		IOWR_ALTERA_AVALON_PIO_DATA(LEDS_GREEN_BASE, IORD_ALTERA_AVALON_PIO_DATA(LEDS_GREEN_BASE) | 8);
		if(ledCounts[0] == 500) {
			ledCounts[0] = 0;
			IOWR_ALTERA_AVALON_PIO_DATA(LEDS_GREEN_BASE, IORD_ALTERA_AVALON_PIO_DATA(LEDS_GREEN_BASE) & ~8);
			ledOn[0] = 0;
		} else {
			ledCounts[0]++;
		}
	}
}


/* DESCRIPTION: Handles of turning on and off the timers
 * PARAMETER:   none
 * RETURNS:     none
 */
void handle_timers(void) {
	// AVI
	if(AVI_stop) {
		printf("%d: ", cycle);
		printf("STOPPING AVI\n");
		alt_alarm_stop(&AVITIMER);
	}
	if(AVI_start) {
		printf("%d: ", cycle);
		printf("start avi\n");
		void* timerContext = (void*) &AVITO;
		alt_alarm_start(&AVITIMER, AVI_VALUE, AVI_isr, timerContext);
	}

	// PVARP
	if(PVARP_stop) {
		printf("%d: ", cycle);
		printf("STOPPING PVARP\n");
		alt_alarm_stop(&PVARPTIMER);
	}
	if(PVARP_start) {
		printf("%d: ", cycle);
		printf("starting pvarp\n");
		void* timerContext = (void*) &PVARPTO;
		alt_alarm_start(&PVARPTIMER, PVARP_VALUE, PVARP_isr, timerContext);
	}

	// VRP
	if(VRP_stop) {
		printf("%d: ", cycle);
		printf("STOPPING VRP\n");
		alt_alarm_stop(&VRPTIMER);
	}
	if(VRP_start) {
		printf("%d: ", cycle);
		printf("starting vrp\n");
		void* timerContext = (void*) &VRPTO;
		alt_alarm_start(&VRPTIMER, VRP_VALUE, VRP_isr, timerContext);
	}

	// AEI
	if(AEI_stop) {
		printf("%d: ", cycle);
		printf("STOPPING AEI\n");
		alt_alarm_stop(&AEITIMER);
	}
	if(AEI_start) {
		printf("%d: ", cycle);
		printf("starting AEI\n");
		void* timerContext = (void*) &AEITO;
		alt_alarm_start(&AEITIMER, AEI_VALUE, AEI_isr, timerContext);
	}

	// URI
	if(URI_stop) {
		printf("%d: ", cycle);
		printf("STOPPING URI\n");
		alt_alarm_stop(&URITIMER);
	}
	if(URI_start) {
		printf("%d: ", cycle);
		printf("starting uri\n");
		void* timerContext = (void*) &URITO;
		alt_alarm_start(&URITIMER, URI_VALUE, URI_isr, timerContext);
	}

	// LRI
	if(LRI_stop) {
		printf("%d: ", cycle);
		printf("STOPPING LRI\n");
		alt_alarm_stop(&LRITIMER);
	}
	if(LRI_start) {
		printf("%d: ", cycle);
		printf("starting lri\n");
		void* timerContext = (void*) &LRITO;
		alt_alarm_start(&LRITIMER, LRI_VALUE, LRI_isr, timerContext);
	}

}

/* DESCRIPTION: Handles the different ISRs, sets timeout for each to 1
 * PARAMETER:   context
 * RETURNS:     return the time for the next timer
 */
alt_u32 LRI_isr(void* context) {
	printf("%d: ", cycle);
	printf("LRI TIMESOUT\n");
	LRITO_set = 1;
	// Return 0 so we don't instantly start again
	return 0;
}

alt_u32 URI_isr(void* context) {
	printf("%d: ", cycle);
	printf("URI TIMESOUT\n");
	URITO_set = 1;
	// Return 0 so we don't instantly start again
	return 0;
}

alt_u32 AVI_isr(void* context) {
	VPase = 0;
	printf("%d: ", cycle);
	printf("AVI TIMESOUT\n");
	AVITO_set = 1;
	// Return 0 so we don't instantly start again
	return 0;
}

alt_u32 AEI_isr(void* context) {
	printf("%d: ", cycle);
	printf("AEI TIMESOUT\n");
	AEITO_set = 1;
	// Return 0 so we don't instantly start again
	return 0;
}

alt_u32 PVARP_isr(void* context) {
	printf("%d: ", cycle);
	printf("PVARP TIMESOUT\n");
	PVARPTO_set = 1;
	// Return 0 so we don't instantly start again
	return 0;
}

alt_u32 VRP_isr(void* context) {
	printf("%d: ", cycle);
	printf("VRP TIMESOUT\n");
	VRPTO_set = 1;
	// Return 0 so we don't instantly start again
	return 0;
}

/* DESCRIPTION: Handles the logic specific to mode one
 * PARAMETER:   N/A
 * RETURNS:     N/A
 */
void modeOne(void) {
	// Masking buttons to turn them on
	IOWR_ALTERA_AVALON_PIO_IRQ_MASK(KEYS_BASE, 0x7);
	// Setting red led off
	IOWR_ALTERA_AVALON_PIO_DATA(LEDS_RED_BASE, IORD_ALTERA_AVALON_PIO_DATA(LEDS_RED_BASE) & ~(0b1));
}

/* DESCRIPTION: Handles the logic specific to mode two
 * PARAMETER:   N/A
 * RETURNS:     N/A
 */
void modeTwo(void) {
	// Mask buttons to turn them off
	IOWR_ALTERA_AVALON_PIO_IRQ_MASK(KEYS_BASE, 0x0);
	// Turn on the red LED
	IOWR_ALTERA_AVALON_PIO_DATA(LEDS_RED_BASE, IORD_ALTERA_AVALON_PIO_DATA(LEDS_RED_BASE) | (0b1));

	// Non-blocking read for UART
	char buffer[10];
	buffer[0] = 0;
	if(uartFile != NULL) {
		// Read has been configured to not block
		read(fileDesc, buffer, 1);
		//If we have received a value
		if(buffer[0] > 0) {
			// If we received an A, set ASense and turn on LED
			if(buffer[0] == 'A') {
				setASense = 1;
				if(ledOn[0] == 0) {
					ledOn[2] = 1;
					ledCounts[2] = 0;
				}
			// If we received a V, set VSense and turn on LED
			} else if (buffer[0] == 'V') {
				setVSense = 1;
				if(ledOn[1] == 0) {
					ledOn[3] = 1;
					ledCounts[3] = 0;
				}

			}
		}
	}
}

int main(void) {
	printf("Main Starts\n");

	// Open the UART as read / write
	uartFile = fopen(UART_NAME, "r+");

	// Open the UART in a non-blocking mode
	fileDesc = open(UART_NAME, O_RDWR | O_NONBLOCK | O_NOCTTY);

	// Initialise program
	reset();
	init_buttons_pio();

	while(1) {

		// Read the mode value
		prevSwitch = switch0;
		switch0 = IORD_ALTERA_AVALON_PIO_DATA(SWITCHES_BASE);

		// Depending on switch call the specific function
		if(switch0 & 0b1) {
			modeTwo();
		} else {
			modeOne();
		}

		// If we have set these values, tell SCCharts code
		if(setASense) {
			ASense = 1;
			setASense = 0;
		} else {
			ASense = 0;
		}
		if(setVSense) {
			VSense = 1;
			setVSense = 0;
		} else {
			VSense = 0;
		}

		// Set the timeouts before tick so we don't interrupt it
		if(LRITO_set) {
			LRITO = 1;
			LRITO_set = 0;
		} else {
			LRITO = 0;
		}

		if(URITO_set) {
			URITO = 1;
			URITO_set = 0;
		} else {
			URITO = 0;
		}

		if(VRPTO_set) {
			VRPTO = 1;
			VRPTO_set = 0;
		} else {
			VRPTO = 0;
		}

		if(AEITO_set) {
			AEITO = 1;
			AEITO_set = 0;
		} else {
			AEITO = 0;
		}

		if(AVITO_set) {
			AVITO = 1;
			AVITO_set = 0;
		} else {
			AVITO = 0;
		}

		if(PVARPTO_set) {
			PVARPTO = 1;
			PVARPTO_set = 0;
		} else {
			PVARPTO = 0;
		}

		// Tick the SCChart code
		tick();

		// Turn on or off LEDS as needed
		handle_leds();

		// If we have pace atrium, send A character to the PC
		if(sendA == 1) {
			fprintf(uartFile, "A\n");
			sendA = 0;
		}

		// If we have pace ventricle, send V character to the PC
		if(sendV == 1) {
			fprintf(uartFile, "V\n");
			sendV = 0;
		}

		// Turn on or off timers as needed
		handle_timers();

		// Go through one cycle of the sccharts program
		cycle++;

		// Reset VSense and ASense to 0.
		VSense, ASense = 0;
	}
	fclose(uartFile);
	return 0;
}
