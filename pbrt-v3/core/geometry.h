#ifndef CV_PBRT_CORE_GEOMETRY_H
#define CV_PBRT_CORE_GEOMETRY_H

#include <pbrt.h>

namespace pbrt
{

template<typename T>
inline bool isNaN(const T x)
{
	return std::isnan(x);
}
template<>
inline bool isNaN(const int x)
{
	return false;
}

template<typename T, uint n>
class vec
{
private:

	T data[n];

public:

	template <typename... Ts>
	vec(Ts... vals)
		:data{vals...}
	{
		
	}

	T operator[](int i) const { return data[i];}
	T& operator[](int i) { return data[i];}

};

class vec3f : vec<float, 3>
{
	template <typename... Ts>
	vec3f(Ts... vals) : vec<float, 3>(vals...) {}
	vec3f()
	{
		data[0] = 0;
		data[1] = 0;
		data[2] = 0;
	}
	vec3f(vec<T, 3>&& val)
	{
		copy(val.data, val.data + 3, data);
	}
	T& x() { return data[0];}
	T& y() { return data[1];}
	T& z() { return data[2];}
}

}

#endif