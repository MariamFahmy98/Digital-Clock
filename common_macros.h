/*
 * common_macros.h
 *
 *  Created on: Oct 4, 2019
 *      Author: marim
 */

#ifndef COMMON_MACROS_H_
#define COMMON_MACROS_H_


#define SET_BIT(REG,BIT) (REG|=(1<<BIT))
#define CLEAR_BIT(REG,BIT) (REG &= ~(1<<BIT))
#define TOGGLE_BIT(REG,BIT) (REG ^= (1<<BIT))
#define ROR(REG,BIT_NUM) (REG= (REG>>BIT_NUM) | (REG<<(sizeof(REG)*8)-BIT_NUM))
#define ROL(REG,BIT_NUM) (REG= (REG<<BIT_NUM) | (REG>>(sizeof(REG)*8)-BIT_NUM))

#define BIT_IS_SET(REG,BTT) (REG & (1<<BIT))
#define BIT_IS_CLEAR(REG,BIT) (!(REG & (1<<BIT)))


#endif /* COMMON_MACROS_H_ */
