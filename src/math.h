/*
 * math.h
 *
 *  Created on: 19 févr. 2015
 *      Author: jfellus
 */

#ifndef AGML_MATH_H_
#define AGML_MATH_H_

#include <stdlib.h>
#include <limits.h>

inline float randf() {return (float)rand()/INT_MAX;}
inline float randf(float min, float max) { return randf()*(max-min) + min; }



#endif /* AGML_MATH_H_ */
