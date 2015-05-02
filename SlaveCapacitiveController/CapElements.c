/*
 *     uCube is a motion controlled interactive LED cube.
 *     Copyright (C) 2014  Jeramie Vens
 *
 *     This program is free software: you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation, either version 3 of the License, or
 *     (at your option) any later version.
 *
 *     This program is distributed in the hope that it will be useful,
 *     but WITHOUT ANY WARRANTY; without even the implied warranty of
 *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *     GNU General Public License for more details.
 *
 *     You should have received a copy of the GNU General Public License
 *     along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
/**
 * @addtogroup CapacitiveTouch
 * @{
 * @file 16Element.c
 * @author Sprog
 * @date Nov 8, 2014
 * @copyright GNU Public License v3
 * @brief
 * @details
 */
#include "../../CapSens/structure.h"

//9 Element Structure

const struct Element element_1 = {
	.inputPxselRegister = (uint8_t *)&P2SEL,
	.inputPxsel2Register = (uint8_t *)&P2SEL2,
	.inputBits = BIT4,
	.maxResponse = 400,
	.threshold = 50
};

const struct Element element_2 = {
	.inputPxselRegister = (uint8_t *)&P2SEL,
	.inputPxsel2Register = (uint8_t *)&P2SEL2,
	.inputBits = BIT5,
	.maxResponse = 400,
	.threshold = 50
};

const struct Element element_3 = {
	.inputPxselRegister = (uint8_t *)&P3SEL,
	.inputPxsel2Register = (uint8_t *)&P3SEL2,
	.inputBits = BIT5,
	.maxResponse = 400,
	.threshold = 50
};

const struct Element element_4 = {
	.inputPxselRegister = (uint8_t *)&P3SEL,
	.inputPxsel2Register = (uint8_t *)&P3SEL2,
	.inputBits = BIT6,
	.maxResponse = 400,
	.threshold = 50
};

const struct Element element_5 = {
	.inputPxselRegister = (uint8_t *)&P3SEL,
	.inputPxsel2Register = (uint8_t *)&P3SEL2,
	.inputBits = BIT7,
	.maxResponse = 400,
	.threshold = 50
};

const struct Element element_6 = {
	.inputPxselRegister = (uint8_t *)&P2SEL,
	.inputPxsel2Register = (uint8_t *)&P2SEL2,
	.inputBits = BIT3,
	.maxResponse = 400,
	.threshold = 50
};

const struct Element element_7 = {
	.inputPxselRegister = (uint8_t *)&P3SEL,
	.inputPxsel2Register = (uint8_t *)&P3SEL2,
	.inputBits = BIT4,
	.maxResponse = 400,
	.threshold = 50
};

const struct Element element_8 = {
	.inputPxselRegister = (uint8_t *)&P3SEL,
	.inputPxsel2Register = (uint8_t *)&P3SEL2,
	.inputBits = BIT3,
	.maxResponse = 400,
	.threshold = 50
};

const struct Element element_9 = {
	.inputPxselRegister = (uint8_t *)&P1SEL,
	.inputPxsel2Register = (uint8_t *)&P1SEL2,
	.inputBits = BIT0,
	.maxResponse = 400,
	.threshold = 50
};

const struct Element element_10 = {
	.inputPxselRegister = (uint8_t *)&P1SEL,
	.inputPxsel2Register = (uint8_t *)&P1SEL2,
	.inputBits = BIT3,
	.maxResponse = 400,
	.threshold = 50
};

const struct Element element_12 = {
	.inputPxselRegister = (uint8_t *)&P3SEL,
	.inputPxsel2Register = (uint8_t *)&P3SEL2,
	.inputBits = BIT2,
	.maxResponse = 400,
	.threshold = 50
};

const struct Element element_13 = {
	.inputPxselRegister = (uint8_t *)&P2SEL,
	.inputPxsel2Register = (uint8_t *)&P2SEL2,
	.inputBits = BIT0,
	.maxResponse = 400,
	.threshold = 50
};

const struct Element element_14 = {
	.inputPxselRegister = (uint8_t *)&P3SEL,
	.inputPxsel2Register = (uint8_t *)&P3SEL2,
	.inputBits = BIT0,
	.maxResponse = 400,
	.threshold = 50
};

const struct Element element_15 = {
	.inputPxselRegister = (uint8_t *)&P3SEL,
	.inputPxsel2Register = (uint8_t *)&P3SEL2,
	.inputBits = BIT1,
	.maxResponse = 400,
	.threshold = 50
};

const struct Element element_19 = {
	.inputPxselRegister = (uint8_t *)&P2SEL,
	.inputPxsel2Register = (uint8_t *)&P2SEL2,
	.inputBits = BIT2,
	.maxResponse = 400,
	.threshold = 50
};

const struct Element element_20 = {
	.inputPxselRegister = (uint8_t *)&P2SEL,
	.inputPxsel2Register = (uint8_t *)&P2SEL2,
	.inputBits = BIT1,
	.maxResponse = 400,
	.threshold = 50
};


const struct Sensor sensor_1 =
{
	.halDefinition = RO_PINOSC_TA0_WDTp,
	.numElements = 16,
	.baseOffset = 0,
	// Pointer to elements
	.arrayPtr[0] = &element_1,  // point to first element
	.arrayPtr[1] = &element_2,
	.arrayPtr[2] = &element_3,
	.arrayPtr[3] = &element_4,
	.arrayPtr[4] = &element_5,
	.arrayPtr[5] = &element_6,
	.arrayPtr[6] = &element_7,
	.arrayPtr[7] = &element_8,
	.arrayPtr[8] = &element_9,
	.arrayPtr[9] = &element_10,
	.arrayPtr[10] = &element_12,
	.arrayPtr[11] = &element_13,
	.arrayPtr[12] = &element_14,
	.arrayPtr[13] = &element_15,
	.arrayPtr[14] = &element_19,
	.arrayPtr[15] = &element_20,
	// Timer Information
	.measGateSource= GATE_WDTp_SMCLK, // 0->SMCLK, 1-> ACLK
	.accumulationCycles= WDTp_GATE_8192 //512
};

/// @}
