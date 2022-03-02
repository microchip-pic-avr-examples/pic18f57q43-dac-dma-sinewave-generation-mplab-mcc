
[![MCHP](images/microchip.png)](https://www.microchip.com)

# Sine Wave Generation using DAC and DMA of PIC18F57Q43 Microcontroller

## Related Documentation

- [PIC18F57Q43 Data Sheet](https://www.microchip.com/DS40002147F)
- [8-bit PIC MCU Peripheral Deep Dive - DAC Chapter](https://mu.microchip.com)

## Objective

This application example highlights the usage of 8-bit buffered DAC and DMA peripherals of PIC18F57Q43 microcontroller to generate a sinusoidal waveform. This device has a DMA module which can be used for seamless and direct data transfers between different memory regions without intervention from the CPU. The signal is generated by continuously adjusting the output of a DAC to create an analog signal made of a series of discrete steps. The values of DAC input data register are loaded from look-up table stored in Program Flash Memory using DMA.

![block_diagram](images/block_diagram.jpg)

In this application, DAC is configured to use FVR as the positive reference and ground as the negative reference. The frequency of  sine wave is decided by the frequency of updating DAC DATA register and total number of points/samples in one cycle of the signal. The number of data samples per cycle of the sine wave is set as 250 and is stored in a look up table in program flash memory. This data is transferred to DAC data register using DMA which is hardware triggered by Timer 2 overflow interrupt occurring every 40 µs. 

Therefore, frequency of signal, 
f = 1 / (Total no of samples per cycle * Timer 2 period) = 1/ (250 * 40µS) = 100 Hz. 

If we keep number of DAC samples in sine wave constant, then frequency of signal can be changed by changing Timer 2 period. DAC output is routed to pin RA2, and we can observe the output on logic analyzer/oscilloscope.

## Software Used

- MPLAB® X IDE [v6.00.0 or newer](https://www.microchip.com/mplab/mplab-x-ide)
- XC8 Compiler [v2.35.0 or newer](https://www.microchip.com/mplab/compilers)
- MPLAB® Code Configurator (MCC) [v5.1.0 or newer](https://www.microchip.com/mplab/mplab-code-configurator)
- MPLAB® Code Configurator (MCC) Device Libraries PIC10 / PIC12 / PIC16 / PIC18 MCUs [v5.7.0 or newer](https://www.microchip.com/mplab/mplab-code-configurator)
- Microchip PIC18F-Q series Device Support [v1.13.211 or newer](https://packs.download.microchip.com/)

## Hardware Used

- [PIC18F57Q43 Curiosity Nano Evaluation Kit](https://www.microchip.com/en-us/development-tool/DM164150)
- Logic analyzer/Oscilloscope

## Hardware Setup

![Connection_diagram](images/connection_diagram.jpg)

This demo is implemented using PIC18F57Q43 Curiosity Nano Evaluation Kit. The sine wave generated on pin RA2 is observed on a logic analyzer/oscilloscope. Connect pin RA2 to analog channel of logic analyzer. Connect GND of CNANO to respective channel GND.

## Demo Operation

After the hardware connections are complete and firmware is programmed, you can observe the waveforms. The required measurement parameters such as frequency and period are added in the waveforms. A sine wave of 100 Hz frequency is generated using DAC and DMA.

![waveform_result](images/waveform_result.png)

## Peripheral Configuration

This section explains how to configure the peripherals using MPLAB X IDE with MCC plugin for recreation of the project. 

Refer Software Used section to install required tools to recreate the project.

Additional Links: [MCC Melody Technical Reference](https://onlinedocs.microchip.com/v2/keyword-lookup?keyword=MCC.MELODY.INTRODUCTION&version=latest&redirect=true)

| Peripherals               | Configuration                                                                                                                                                                                                                                                                                                                                                                                                  | Usage                                                                         |
|---------------------------|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|-------------------------------------------------------------------------------|
|    <br>System Settings    |    <br>Clock Control:<br>Clock source -   HFINTOSC<br>HF Internal Clock - 16MHz<br>Clock Divider   – 1                                                                                                                                                                                                                                                                                                         |    <br>16 MHz System  clock                                                                     |
|    <br>TMR2               |    <br>Enable Timer<br>Control Mode - Roll over pulse<br>Start/Reset Option - Software Control<br>Clock Source - Fosc/4<br>Polarity - Rising edge<br>Prescaler - 1:32<br>Postscaler - 1:1<br>Time Period - 40µs<br>TMR Interrupt Enabled<br>                                                                                                                                                                   |    <br>Used to hardware trigger DMA                                           |
|    <br>DAC1               |    <br>Enable DAC<br>DAC Positive reference selection - FVR<br>DAC Negative reference selection - VSS<br>DAC Output Enable Selection - DACOUT1 Enabled and DACOUT2 Disabled<br>   <br>                                                                                                                                                                                                                         |    <br>Used to generate 100Hz sine wave<br>   <br>                            |
|    <br>DMA                |    <br>DMA:<br>DMA Dependency - DMA1<br>Source Address - 0x010000<br>Source Message Size - 250<br>Destination Region - SFR<br>Destination Module -  DAC1<br>Destination SFR - DAC1DATL<br>Destination Message Size – 1<br>   <br>DMA1:  <br>DMA Enabled<br>Source mode - Incremented<br>Source region - Program Flash<br>Destination mode - Unchanged<br>Abort Trigger - None<br>Start Trigger - TMR2<br>      |    <br>Used for data transfer between LUT in PFM and DAC DATA <br>   <br>     |
|    <br>FVR                |    <br>FVR Enabled<br>FVR_buffer 2   - 2x                                                                                                                                                                                                                                                                                                                                                                      |    <br>Positive   reference voltage to DAC                                    |                                                                                                                                                                                                                                                                                                                                                                                           


- **System Settings**


![system_settings](images/system_settings.png)


- **Add DAC, DMA, FVR and TMR2 peripherals**


![peripherals](images/peripherals.png)


- **DAC**


![dac](images/dac.jpg)


- **DMA**

1. DMA module loaded 
2. Select DMA dependency as DMA1
3. Navigate to builder area 
4. Launch DMA1 
5. Configure all Options in DMA1
6. Click on DMA module and configure the settings


![dma1](images/dma1.jpg)


![dma2](images/dma2.jpg)


![dma3](images/dma3.jpg)


- **FVR**


![fvr](images/fvr.png)


- **TMR2**


![tmr2_1](images/tmr2_1.jpg)

![tmr2_2](images/tmr2_2.jpg)


- **Pin Grid View**


![pin_grid](images/pin_grid.png)


- **Pins**

Verify DAC output on pin RA2

![pins](images/pins.jpg)


## Summary

The DAC and DMA peripherals of PIC18F57Q43 Microcontroller are used to generate a 100Hz frequency sine wave without the intervention of CPU.
