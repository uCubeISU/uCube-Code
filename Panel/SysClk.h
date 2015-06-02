/*
 * SysClk.h
 *
 *  Created on: Jun 1, 2015
 *      Author: vens
 */

#ifndef SYSCLK_H_
#define SYSCLK_H_

typedef void SysClkCallback(unsigned char source);

void SysClkRegisterCallback(unsigned char source, SysClkCallback callback);

#endif /* SYSCLK_H_ */
