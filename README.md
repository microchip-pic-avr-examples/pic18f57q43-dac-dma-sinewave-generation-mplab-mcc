
[![MCHP](images/microchip.png)](https://www.microchip.com)

# Sine Wave Generation using DAC and DMA of PIC18F57Q43 Microcontroller

This code example demonstrates how to generate a 100 Hz sine wave without CPU intervention using the built-in DAC and DMA peripherals of the PIC microcontroller. Some compatible PIC18F-Q43 family of MCUs are: PIC18F27Q43, PIC18F47Q43, PIC18F57Q43.

## Related Documentation

- [PIC18F57Q43 Data Sheet](https://www.microchip.com/DS40002147)
- [8-bit PIC MCU Peripheral Deep Dive](https://mu.microchip.com/8-bit-pic-mcu-peripheral-deep-dive-pub) (DAC Chapter)

## Objective

This application example highlights the usage of 8-bit buffered DAC and DMA peripherals of PIC18F57Q43 microcontroller to generate a sinusoidal waveform. This device has a DMA module which can be used for seamless and direct data transfers between different memory regions without intervention from the CPU. The signal is generated by continuously adjusting the output of a DAC to create an analog signal made of a series of discrete steps. The values of DAC input data register are loaded from look-up table stored in Program Flash Memory using DMA.

![block_diagram](images/block_diagram.jpg)

In this application, DAC is configured to use FVR as the positive reference and ground as the negative reference. The frequency of  sine wave is decided by the frequency of updating DAC DATA register and total number of points/samples in one cycle of the signal. The number of data samples per cycle of the sine wave is set as 250 and is stored in a look up table in program flash memory. This data is transferred to DAC data register using DMA which is hardware triggered by Timer 2 overflow interrupt occurring every 40 µs.

Therefore, frequency of signal,
`f = 1 / (Total no of samples per cycle * Timer 2 period) = 1/ (250 * 40µS) = 100 Hz.`

If we keep number of DAC samples in sine wave constant, then frequency of signal can be changed by changing Timer 2 period. DAC output is routed to pin RA2, and we can observe the output on logic analyzer/oscilloscope.

## Software Used

- MPLAB® X IDE [v6.00.0 or newer](https://www.microchip.com/mplab/mplab-x-ide)
- XC8 Compiler [v2.36.0 or newer](https://www.microchip.com/mplab/compilers)
- MPLAB® Code Configurator (MCC) [v5.1.0 or newer](https://www.microchip.com/mplab/mplab-code-configurator)
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

Refer [Software Used](https://github.com/microchip-pic-avr-examples/pic18f57q43-dac-dma-sinewave-generation-mplab-mcc#software-used) section to install required tools to recreate the project.

Additional Links: [MCC Melody Technical Reference](https://onlinedocs.microchip.com/v2/keyword-lookup?keyword=MCC.MELODY.INTRODUCTION&version=latest&redirect=true)

| Peripherals               | Configuration                                                                                                                                                                                                                                                                                                                                                                                                  | Usage                                                                         |
|---------------------------|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|-------------------------------------------------------------------------------|
|    Clock Control      |    Clock Control:<br>Clock source -   HFINTOSC<br>HF Internal Clock - 16MHz<br>Clock Divider   – 1                                                                                                                                                                                                                                                                                                         |    16 MHz System  clock                                                                     |
|    TMR2               |    Enable Timer<br>Control Mode - Roll over pulse<br>Start/Reset Option - Software Control<br>Clock Source - Fosc/4<br>Polarity - Rising edge<br>Prescaler - 1:32<br>Postscaler - 1:1<br>Time Period - 40µs<br>TMR Interrupt Enabled<br>                                                                                                                                                                   |    Used to hardware trigger DMA                                           |
|    DAC1               |    Enable DAC<br>DAC Positive reference selection - FVR<br>DAC Negative reference selection - VSS<br>DAC Output Enable Selection - DACOUT1 Enabled and DACOUT2 Disabled<br>   <br>                                                                                                                                                                                                                         |    Used to generate 100Hz sine wave<br>   <br>                            |
|    DMA                |    DMA:<br>DMA Dependency - DMA1<br>Source Address - 0x010000<br>Source Message Size - 250<br>Destination Region - SFR<br>Destination Module -  DAC1<br>Destination SFR - DAC1DATL<br>Destination Message Size – 1<br>   <br>DMA1:  <br>DMA Enabled<br>Source mode - Incremented<br>Source region - Program Flash<br>Destination mode - Unchanged<br>Abort Trigger - None<br>Start Trigger - TMR2<br>      |    Used for data transfer between LUT in PFM and DAC DATA <br>   <br>     |
|    FVR                |    FVR Enabled<br>FVR_buffer 2   - 2x                                                                                                                                                                                                                                                                                                                                                                      |    Positive   reference voltage to DAC                                    |                                                                                                                                                                                                                                                                                                                                                                                           


- **System Settings**

![system_settings](images/clock.png)
<br />

- **Add DAC, DMA, FVR and TMR2 peripherals**

![peripherals](images/peripherals.png)
<br />

- **DAC**

![dac](images/dac.png)
<br />

- **DMA**

1. DMA module loaded
2. Select DMA dependency as DMA1
3. Navigate to builder area
4. Launch DMA1
5. Configure all Options in DMA1
6. Click on DMA module and configure the settings
<br />

![dma1](images/dma1.png)
<br />

![dma2](images/dma2.png)
<br />

![dma3](images/dma3.png)
<br />

- **FVR**

![fvr](images/fvr.png)
<br />

- **TMR2**

![tmr2_1](images/tmr2.png)
<br />

- **Pin Grid View**

Verify DAC output on pin RA2

![pin_grid](images/pin_grid.png)
<br />

- **Pins**

Verify that pin RA2 is Analog

![pins](images/pins.png)
<br />

## Summary

The DAC and DMA peripherals of PIC18F57Q43 Microcontroller are used to generate a 100Hz frequency sine wave without the intervention of CPU.
