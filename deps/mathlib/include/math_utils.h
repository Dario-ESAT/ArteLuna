// @author Enrique Gil <gilte@esat-alumni.com>
// @file math_utils header implementation

#ifndef __MATHUTILS_H__
#define __MATHUTILS_H__ 1

namespace mathlib {

	inline float Clamp(float value, float minVal, float maxVal){
		if(value > maxVal) {
			return maxVal;
		}

		if(value < minVal) {
			return minVal;
		}

		return value;
	}
	
}

#endif