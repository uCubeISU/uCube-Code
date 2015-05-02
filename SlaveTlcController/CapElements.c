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
 * @file CapElements.c
 * @author Sprog
 * @date Nov 8, 2014
 * @copyright GNU Public License v3
 * @brief
 * @details
 */
#include "../../CapSens/structure.h"

//9 Element Structure

const struct Element element_25 = {
	.inputPxselRegister = (uint8_t *)&P2SEL,
	.inputPxsel2Register = (uint8_t *)&P2SEL2,
	.inputBits = BIT0,
	.maxResponse = 400,
	.threshold = 50
};

const struct Element element_24 = {
	.inputPxselRegister = (uint8_t *)&P2SEL,
	.inputPxsel2Register = (uint8_t *)&P2SEL2,
	.inputBits = BIT1,
	.maxResponse = 400,
	.threshold = 50
};

const struct Element element_23 = {
	.inputPxselRegister = (uint8_t *)&P2SEL,
	.inputPxsel2Register = (uint8_t *)&P2SEL2,
	.inputBits = BIT2,
	.maxResponse = 400,
	.threshold = 50
};

const struct Element element_17 = {
	.inputPxselRegister = (uint8_t *)&P3SEL,
	.inputPxsel2Register = (uint8_t *)&P3SEL2,
	.inputBits = BIT2,
	.maxResponse = 400,
	.threshold = 50
};

const struct Element element_18 = {
	.inputPxselRegister = (uint8_t *)&P3SEL,
	.inputPxsel2Register = (uint8_t *)&P3SEL2,
	.inputBits = BIT3,
	.maxResponse = 400,
	.threshold = 50
};

const struct Element element_22 = {
	.inputPxselRegister = (uint8_t *)&P3SEL,
	.inputPxsel2Register = (uint8_t *)&P3SEL2,
	.inputBits = BIT4,
	.maxResponse = 400,
	.threshold = 50
};

const struct Element element_21 = {
	.inputPxselRegister = (uint8_t *)&P2SEL,
	.inputPxsel2Register = (uint8_t *)&P2SEL2,
	.inputBits = BIT3,
	.maxResponse = 400,
	.threshold = 50
};

const struct Element element_11 = {
	.inputPxselRegister = (uint8_t *)&P3SEL,
	.inputPxsel2Register = (uint8_t *)&P3SEL2,
	.inputBits = BIT0,
	.maxResponse = 400,
	.threshold = 50
};

const struct Element element_16 = {
	.inputPxselRegister = (uint8_t *)&P2SEL,
	.inputPxsel2Register = (uint8_t *)&P2SEL2,
	.inputBits = BIT5,
	.maxResponse = 400,
	.threshold = 50
};


const struct Sensor sensor_0 =
{
	.halDefinition = RO_PINOSC_TA0_WDTp,
	.numElements = 9,
	.baseOffset = 0,
	// Pointer to elements
	.arrayPtr[0] = &element_11,  // point to first element
	.arrayPtr[1] = &element_16,
	.arrayPtr[2] = &element_17,
	.arrayPtr[3] = &element_18,
	.arrayPtr[4] = &element_21,
	.arrayPtr[5] = &element_22,
	.arrayPtr[6] = &element_23,
	.arrayPtr[7] = &element_24,
	.arrayPtr[8] = &element_25,
	// Timer Information
	.measGateSource= GATE_WDTp_SMCLK, // 0->SMCLK, 1-> ACLK
	.accumulationCycles= WDTp_GATE_8192 //512
};


