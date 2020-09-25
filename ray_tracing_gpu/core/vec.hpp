#ifndef CV_RTGPU_VEC_HPP
#define CV_RTGPU_VEC_HPP

#include <vector>
#include <cmath>

using namespace std;

template<typename T, int n>
struct vec
{
	T data[n];

	template <typename... Ts>
	vec(Ts... vals)
		:data{vals...}
	{
		
	}

	T operator[](int i) const { return data[i];}
	T& operator[](int i) { return data[i];}

	vec operator-() const
	{
		vec rst;
		for(int i = 0; i < n; i++)
		{
			rst[i] = -data[i];
		}
		return rst;
	}
	inline vec operator-(const vec& v) const
	{
		vec rst;
		for(int i = 0; i < n; i++)
		{
			rst[i] = data[i] - v[i];
		}
		return rst;
	}
	inline vec operator+(const vec& v) const
	{
		vec rst;
		for(int i = 0; i < n; i++)
		{
			rst[i] = data[i] + v[i];
		}
		return rst;
	}
	inline vec operator*(const vec& v) const
	{
		vec rst;
		for(int i = 0; i < n; i++)
		{
			rst[i] = data[i] * v[i];
		}
		return rst;
	}
	inline vec operator/(const vec& v) const
	{
		vec rst;
		for(int i = 0; i < n; i++)
		{
			rst[i] = data[i] / v[i];
		}
		return rst;
	}
	inline vec operator-(const T& v) const
	{
		vec rst;
		for(int i = 0; i < n; i++)
		{
			rst[i] = data[i] - v;
		}
		return rst;
	}
	inline vec operator+(const T& v) const
	{
		vec rst;
		for(int i = 0; i < n; i++)
		{
			rst[i] = data[i] + v;
		}
		return rst;
	}
	inline vec operator*(const T& v) const
	{
		vec rst;
		for(int i = 0; i < n; i++)
		{
			rst[i] = data[i] * v;
		}
		return rst;
	}
	inline vec operator/(const T& v) const
	{
		vec rst;
		for(int i = 0; i < n; i++)
		{
			rst[i] = data[i] / v;
		}
		return rst;
	}
	vec& operator+=(const vec& v)
	{
		for(int i = 0; i < n; i++)
		{
			data[i] += v[i];
		}
		return *this;
	}
	vec& operator-=(const vec& v)
	{
		for(int i = 0; i < n; i++)
		{
			data[i] -= v[i];
		}
		return *this;
	}
	vec& operator*=(const vec& v)
	{
		for(int i = 0; i < n; i++)
		{
			data[i] *= v[i];
		}
		return *this;
	}
	vec& operator/=(const vec& v)
	{
		for(int i = 0; i < n; i++)
		{
			data[i] /= v[i];
		}
		return *this;
	}
	vec& operator+=(const T& v)
	{
		for(int i = 0; i < n; i++)
		{
			data[i] += v;
		}
		return *this;
	}
	vec& operator-=(const T& v)
	{
		for(int i = 0; i < n; i++)
		{
			data[i] -= v;
		}
		return *this;
	}
	vec& operator*=(const T& v)
	{
		for(int i = 0; i < n; i++)
		{
			data[i] *= v;
		}
		return *this;
	}
	vec& operator/=(const T& v)
	{
		for(int i = 0; i < n; i++)
		{
			data[i] /= v;
		}
		return *this;
	}

	T square()
	{
		T sum = 0;
		for(int i = 0; i < n; i++)
		{
			sum += data[i] * data[i];
		}
		return sum;
	}
	T length()
	{
		return sqrt(square());
	}
	vec normalize()
	{
		return *this / length();
	}
};

template<typename T, int n>
inline T dot(const vec<T, n>& v1, const vec<T, n>& v2)
{
	T sum = 0;
	for(int i = 0; i < n; i++)
	{
		sum += v1[i] * v2[i];
	}
	return sum;
}

template<typename T, int n>
inline vec<T, n> operator*(const T& t, const vec<T, n>& v)
{
	vec<T, n> rst;
	for(int i = 0; i < n; i++)
	{
		rst[i] = v[i] * t;
	}
	return rst;
}

template<int n>
inline vec<float, n> operator*(const double& t, const vec<float, n>& v)
{
	vec<float, n> rst;
	for(int i = 0; i < n; i++)
	{
		rst[i] = v[i] * t;
	}
	return rst;
}

struct rgb : vec<short, 3>
{
	template <typename... Ts>
	rgb(Ts... vals) : vec<short, 3>(vals...) {}
	rgb()
	{
		data[0] = 0;
		data[1] = 0;
		data[2] = 0;
	}
	rgb(vec<short, 3>&& val)
	{
		copy(val.data, val.data + 3, this->data);
	}
	short& r() { return data[0];}
	short& g() { return data[1];}
	short& b() { return data[2];}
};

struct rgbf : vec<float, 3>
{
	template <typename... Ts>
	rgbf(Ts... vals) : vec<float, 3>(vals...) {}
	rgbf()
	{
		data[0] = 0.0;
		data[1] = 0.0;
		data[2] = 0.0;
	}
	rgbf(vec<float, 3>&& val)
	{
		copy(val.data, val.data + 3, this->data);
	}
	float& r() { return data[0];}
	float& g() { return data[1];}
	float& b() { return data[2];}

	static rgbf random()
	{
		return rgbf(random_float(), random_float(), random_float());
	}
	static rgbf random(float min, float max)
	{
		return rgbf(random_float(min, max), random_float(min, max), random_float(min, max));
	}
};

struct bgr : vec<short, 3>
{
	template <typename... Ts>
	bgr(Ts... vals) : vec<short, 3>(vals...) {}
	bgr()
	{
		data[0] = 0;
		data[1] = 0;
		data[2] = 0;
	}
	bgr(vec<short, 3>&& val)
	{
		copy(val.data, val.data + 3, this->data);
	}
	short& b() { return data[0];}
	short& g() { return data[1];}
	short& r() { return data[2];}
};

struct yuv : vec<short, 3>
{
	template <typename... Ts>
	yuv(Ts... vals) : vec<short, 3>(vals...) {}
	yuv()
	{
		data[0] = 0;
		data[1] = 0;
		data[2] = 0;
	}
	yuv(vec<short, 3>&& val)
	{
		copy(val.data, val.data + 3, this->data);
	}
	short& y() { return data[0];}
	short& u() { return data[1];}
	short& v() { return data[2];}
};

template<typename T>
struct vec2 : vec<T, 2>
{
	template <typename... Ts>
	vec2(Ts... vals) : vec<T, 2>(vals...) {}
	vec2()
	{
		data[0] = 0;
		data[1] = 0;
	}
	vec2(vec<T, 2>&& val)
	{
		copy(val.data, val.data + 2, this->data);
	}
	T& x() { return this->data[0];}
	T& y() { return this->data[1];}
};

template<typename T>
struct vec3 : vec<T, 3>
{
	template <typename... Ts>
	vec3(Ts... vals) : vec<T, 3>(vals...) {}
	vec3()
	{
		data[0] = 0;
		data[1] = 0;
		data[2] = 0;
	}
	vec3(vec<T, 3>&& val)
	{2
		copy(val.data, val.data + 3, this->data);
	}
	T& x() { return this->data[0];}
	T& y() { return this->data[1];}
	T& z() { return this->data[2];}
};

template<typename T>
inline vec3<T> cross(const vec3<T>& u, const vec3<T>& v)
{
	return vec3<T>(
			u.data[1] * v.data[2] - u.data[2] * v.data[1],
			u.data[2] * v.data[0] - u.data[0] * v.data[2],
			u.data[0] * v.data[1] - u.data[1] * v.data[0]
		);
}

using vec3f = vec3<float>;

inline static vec3f random3f()
{
	return vec3f(random_float(), random_float(), random_float());
}

inline static vec3f random3f(float min, float max)
{
	return vec3f(random_float(min, max), random_float(min, max), random_float(min, max));
}

vec3f random3f_in_unit_sphere()
{
	while (true) {
		auto p = random3f(-1,1);
		if (p.square() >= 1) continue;
		return p;
	}
}

vec3f random3f_unit_vector() //True Lambertian Reflection
{
	auto a = random_float(0, 2*pi);
	auto z = random_float(-1, 1);
	auto r = sqrt(1 - z*z);
	return vec3f(r*cos(a), r*sin(a), z);
}

vec3f random_in_unit_disk()
{
	while (true) {
		auto p = vec3f(random_float(-1,1), random_float(-1,1), 0);
		if (p.square() >= 1) continue;
		return p;
	}
}

vec3f reflect(const vec3f& v, const vec3f& n)
{
    return v - 2*dot(v,n)*n;
}

vec3f refract(const vec3f& uv, const vec3f& n, float etai_over_etat)
{
	auto cos_theta = dot(-uv, n);
	vec3f r_out_perp =  etai_over_etat * (uv + cos_theta*n);
	vec3f r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.square())) * n;
	return r_out_perp + r_out_parallel;
}

template<typename T>
struct vec4 : vec<T, 4>
{
	template <typename... Ts>
	vec4(Ts... vals) : vec<T, 4>(vals...) {}
	vec4(vec<T, 4>&& val)
	{
		copy(val.data, val.data + 4, this->data);
	}
	T& x() { return this->data[0];}
	T& y() { return this->data[1];}
	T& z() { return this->data[2];}
	T& w() { return this->data[3];}
};

#endif