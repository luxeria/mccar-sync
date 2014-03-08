/*
 * hardware.c
 *
 *  Created on: Mar 7, 2014
 *      Author: daniw
 */

#include "platform.h"
#include "hardware.h"

/**
 * Initialize clock module, ports and modules
 * @author daniw
 */
void hardware_lowlevel_init(void) 
{
    //### Clock system ###
    /*
     * After startup the clock system is in FEI mode. To change to PEE mode the 
     * clock system has to be changed in the following order: 
     * FEI -> FBE -> BLPE -> PBE -> PEE 
     */
    //--- FEI -> FBE ---
    // Start external crystal oszillator
    MCGC2 = MCGC2_RANGE_MASK | MCGC2_HGO_MASK | MCGC2_EREFS_MASK | MCGC2_ERCLKEN_MASK;
    // Wait for crystal oscillator to be ready
    while(!MCGSC_OSCINIT);
    // Block interrupts
    DisableInterrupts;
    // Select external clock source for MCGOUT 
    // divide by 128 for fll
    MCGC1 = MCGC1_CLKS1_MASK | MCGC1_RDIV_MASK;
    // Wait until clock source for reference clock has changed
    while(MCGSC_IREFST);
    // Wait until MCGOUT has changed to external reference clock
    while(MCGSC_CLKST != 2);
    //--- FBE -> BLPE ---
    // Enter BLPE mode (start PLL, stop FLL)
    MCGC2_LP = 1;
    // Interrupts can now be re-enabled
    /* EnableInterrupts */
    // Divide external clock by 4
    MCGC1_RDIV = 2; 
    // Prepare PLL  and set multiplier to 24 to achieve 48 MHz
    MCGC3_PLLS = 1;
    MCGC3_VDIV = 6;
    // Wait until PLLS has PLL as clock source
    while(!MCGSC_PLLST);
    //--- BLPE -> PBE ---
    // Switch to PBE mode
    MCGC2_LP = 0;
    // Wait until PLL has locked
    while(!MCGSC_LOCK);
    //--- PBE -> PEE ---
    // Select PLL output as system clock source
    MCGC1_CLKS = 0;
    // Wait until MCGSC is selected
    while(MCGSC_CLKST != 3);
    // MCGOUT is now configured for a frequency of 48 MHz
    // The bus frequency is 24 MHz

    //### I/O Ports ###
    //--- PortA ---
    PTADD = PTADD_INIT;     // Init port direction register of portA
    PTAD  = PTAD_INIT;      // Init port data register of portA
    PTAPE = PTAPE_INIT;     // Init pullup enable register of portA
    PTASE = PTASE_INIT;     // Init slew rate control register of portA
    PTADS = PTADS_INIT;     // Init output drive strength register of portA

    //--- PortB ---
    PTBDD = PTBDD_INIT;     // Init port direction register of portB
    PTBD  = PTBD_INIT;      // Init port data register of portB
    PTBPE = PTBPE_INIT;     // Init pullup enable register of portB
    PTBSE = PTBSE_INIT;     // Init slew rate control register of portB
    PTBDS = PTBDS_INIT;     // Init output drive strength register of portB

    //--- PortC ---
    PTCDD = PTCDD_INIT;     // Init port direction register of portC
    PTCD  = PTCD_INIT;      // Init port data register of portC
    PTCPE = PTCPE_INIT;     // Init pullup enable register of portC
    PTCSE = PTCSE_INIT;     // Init slew rate control register of portC
    PTCDS = PTCDS_INIT;     // Init output drive strength register of portC

    //--- PortD ---
    PTDDD = PTDDD_INIT;     // Init port direction register of portD
    PTDD  = PTDD_INIT;      // Init port data register of portD
    PTDPE = PTDPE_INIT;     // Init pullup enable register of portD
    PTDSE = PTDSE_INIT;     // Init slew rate control register of portD
    PTDDS = PTDDS_INIT;     // Init output drive strength register of portD

    //--- PortE ---
    PTEDD = PTEDD_INIT;     // Init port direction register of portE
    PTED  = PTED_INIT;      // Init port data register of portE
    PTEPE = PTEPE_INIT;     // Init pullup enable register of portE
    PTESE = PTESE_INIT;     // Init slew rate control register of portE
    PTEDS = PTEDS_INIT;     // Init output drive strength register of portE

    //--- PortF ---
    PTFDD = PTFDD_INIT;     // Init port direction register of portF
    PTFD  = PTFD_INIT;      // Init port data register of portF
    PTFPE = PTFPE_INIT;     // Init pullup enable register of portF
    PTFSE = PTFSE_INIT;     // Init slew rate control register of portF
    PTFDS = PTFDS_INIT;     // Init output drive strength register of portF

    //--- PortG ---
    PTGDD = PTGDD_INIT;     // Init port direction register of portG
    PTGD  = PTGD_INIT;      // Init port data register of portG
    PTGPE = PTGPE_INIT;     // Init pullup enable register of portG
    PTGSE = PTGSE_INIT;     // Init slew rate control register of portG
    PTGDS = PTGDS_INIT;     // Init output drive strength register of portG
}
