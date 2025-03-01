/**
 * DMA1 Generated Driver File.
 * 
 * @file dma1.c
 * 
 * @ingroup  dma1
 * 
 * @brief This file contains the API implementations for the DMA1 driver.
 *
 * @version DMA1 Driver Version 2.12.1
 */ 

/*
� [2025] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/

 /**
   Section: Included Files
 */

#include <xc.h>
#include "../dma1.h"

/**
  Section: DMA1 APIs
*/

void DMA1_Initialize(void)
{   
    
    //DMA Instance Selection : 0x0
    DMASELECT = 0x0;
    //Source Address : 0x0
    DMAnSSA = 0x0;
    //Destination Address : (uint16_t) &DAC1DATL
    DMAnDSA = (uint16_t) &DAC1DATL;
    //SSTP not cleared; SMODE incremented; SMR Program Flash; DSTP not cleared; DMODE unchanged; 
    DMAnCON1 = 0xA;
    //Source Message Size : 250
    DMAnSSZ = 250;
    //Destination Message Size : 1
    DMAnDSZ = 1;
    //Start Trigger : SIRQ TMR2; 
    DMAnSIRQ = 0x1B;
    //Abort Trigger : AIRQ None; 
    DMAnAIRQ = 0x0;
	
    // Clear Destination Count Interrupt Flag bit
    PIR2bits.DMA1DCNTIF = 0; 
    // Clear Source Count Interrupt Flag bit
    PIR2bits.DMA1SCNTIF = 0; 
    // Clear Abort Interrupt Flag bit
    PIR2bits.DMA1AIF = 0; 
    // Clear Overrun Interrupt Flag bit
    PIR2bits.DMA1ORIF =0; 
    
    PIE2bits.DMA1DCNTIE = 0;
    PIE2bits.DMA1SCNTIE = 0;
    PIE2bits.DMA1AIE = 0;
    PIE2bits.DMA1ORIE = 0;
	
    //AIRQEN disabled; DGO not in progress; SIRQEN disabled; EN enabled; 
    DMAnCON0 = 0x80;
	 
}

void DMA1_Enable(void)
{
    DMASELECT = 0x0;
    DMAnCON0bits.EN = 0x1;
}

void DMA1_Disable(void)
{
    DMASELECT = 0x0;
    DMAnCON0bits.EN = 0x0;
}

void DMA1_SourceRegionSelect(uint8_t region)
{
    DMASELECT = 0x0;
	DMAnCON1bits.SMR  = region;
}

void DMA1_SourceAddressSet(uint24_t address)
{
    DMASELECT = 0x0;
	DMAnSSA = address;
}

uint24_t DMA1_SourceAddressGet(void)
{
    DMASELECT = 0x0;
    return DMAnSSA;
}

void DMA1_DestinationAddressSet(uint16_t address)
{
    DMASELECT = 0x0;
	DMAnDSA = address;
}

uint16_t DMA1_DestinationAddressGet(void)
{
    DMASELECT = 0x0;
    return DMAnDSA;
}

void DMA1_SourceSizeSet(uint16_t size)
{
    DMASELECT = 0x0;
	DMAnSSZ= size;
}

uint16_t DMA1_SourceSizeGet(void)
{
    DMASELECT = 0x0;
    return DMAnSSZ;
}

void DMA1_DestinationSizeSet(uint16_t size)
{                     
    DMASELECT = 0x0;
	DMAnDSZ= size;
}

uint16_t DMA1_DestinationSizeGet(void)
{                     
    DMASELECT = 0x0;
    return DMAnDSZ;
}

uint24_t DMA1_SourcePointerGet(void)
{
    DMASELECT = 0x0;
	return DMAnSPTR;
}

uint16_t DMA1_DestinationPointerGet(void)
{
    DMASELECT = 0x0;
	return DMAnDPTR;
}

uint16_t DMA1_SourceCountGet(void)
{
    DMASELECT = 0x0;
    return DMAnSCNT;
}

uint16_t DMA1_DestinationCountGet(void)
{                     
    DMASELECT = 0x0;
    return DMAnDCNT;
}

void DMA1_StartTriggerSet(uint8_t sirq)
{
    DMASELECT = 0x0;
	DMAnSIRQ = sirq;
}

void DMA1_AbortTriggerSet(uint8_t airq)
{
    DMASELECT = 0x0;
	DMAnAIRQ = airq;
}

void DMA1_TransferStart(void)
{
    DMASELECT = 0x0;
	DMAnCON0bits.DGO = 1;
}

void DMA1_TransferWithTriggerStart(void)
{
    DMASELECT = 0x0;
	DMAnCON0bits.SIRQEN = 1;
}

void DMA1_TransferStop(void)
{
    DMASELECT = 0x0;
	DMAnCON0bits.SIRQEN = 0; 
	DMAnCON0bits.DGO = 0;
}

void DMA1_DMAPrioritySet(uint8_t priority)
{
    uint8_t GIESaveState = INTCON0bits.GIE;
    INTCON0bits.GIE = 0;
	PRLOCK = 0x55;
	PRLOCK = 0xAA;
	PRLOCKbits.PRLOCKED = 0;
	DMA1PR = priority;
	PRLOCK = 0x55;
	PRLOCK = 0xAA;
	PRLOCKbits.PRLOCKED = 1;
    INTCON0bits.GIE = GIESaveState;
}

/**
 End of File
*/
