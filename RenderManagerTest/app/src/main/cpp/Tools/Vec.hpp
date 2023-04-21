#include <math.h>
#include <vector>

#define PI 3.1415926

#ifndef VEC_HPP
#define VEC_HPP

namespace vec
{

    inline float distance(float x1, float y1, float x2, float y2){

        float result;

        return result;
    }

    template <typename T, const int w, const int h> class matNM;
    template <typename T, const int len> class vecN;

    template <typename T>
    inline T degrees(T angleInRadians)
    {
        return angleInRadians * static_cast<T>(180.0/M_PI);
    }

    template <typename T>
    inline T radians(T angleInDegrees)
    {
        return angleInDegrees * static_cast<T>(M_PI/180.0);
    }

    template <typename T>
    struct random
    {
        operator T ()
        {
            static unsigned int seed = 0x13371337;
            unsigned int res;
            unsigned int tmp;

            seed *= 16807;

            tmp = seed ^ (seed >> 4) ^ (seed << 15);

            res = (tmp >> 9) | 0x3F800000;

            return static_cast<T>(res);
        }
    };

    template<>
    struct random<float>
    {
        operator float()
        {
            static unsigned int seed = 0x13371337;
            float res;
            unsigned int tmp;

            seed *= 16807;

            tmp = seed ^ (seed >> 4) ^ (seed << 15);

            *((unsigned int *) &res) = (tmp >> 9) | 0x3F800000;

            return (res - 1.0f);
        }
    };

    template<>
    struct random<unsigned int>
    {
        operator unsigned int()
        {
            static unsigned int seed = 0x13371337;
            unsigned int res;
            unsigned int tmp;

            seed *= 16807;

            tmp = seed ^ (seed >> 4) ^ (seed << 15);

            res = (tmp >> 9) | 0x3F800000;

            return res;
        }
    };

    template <typename T, const int len>
    class vecN
    {
    public:
        typedef class vecN<T,len> my_type;
        typedef T element_type;
        inline vecN()
        {
        }

        inline vecN(const vecN& that)
        {
            assign(that);
        }

        inline vecN(T s)
        {
            int n;
            for (n = 0; n < len; n++)
            {
                data[n] = s;
            }
        }
        inline vecN& operator=(const vecN& that)
        {
            assign(that);
            return *this;
        }

        inline vecN& operator=(const T& that)
        {
            int n;
            for (n = 0; n < len; n++)
                data[n] = that;

            return *this;
        }

        inline vecN operator+(const vecN& that) const
        {
            my_type result;
            int n;
            for (n = 0; n < len; n++)
                result.data[n] = data[n] + that.data[n];
            return result;
        }

        inline vecN& operator+=(const vecN& that)
        {
            return (*this = *this + that);
        }

        inline vecN operator-() const
        {
            my_type result;
            int n;
            for (n = 0; n < len; n++)
                result.data[n] = -data[n];
            return result;
        }

        inline vecN operator-(const vecN& that) const
        {
            my_type result;
            int n;
            for (n = 0; n < len; n++)
                result.data[n] = data[n] - that.data[n];
            return result;
        }

        inline vecN& operator-=(const vecN& that)
        {
            return (*this = *this - that);
        }

        inline vecN operator*(const vecN& that) const
        {
            my_type result;
            int n;
            for (n = 0; n < len; n++)
                result.data[n] = data[n] * that.data[n];
            return result;
        }

        inline vecN& operator*=(const vecN& that)
        {
            return (*this = *this * that);
        }

        inline vecN operator*(const T& that) const
        {
            my_type result;
            int n;
            for (n = 0; n < len; n++)
                result.data[n] = data[n] * that;
            return result;
        }

        inline vecN& operator*=(const T& that)
        {
            assign(*this * that);

            return *this;
        }

        inline vecN operator/(const vecN& that) const
        {
            my_type result;
            int n;
            for (n = 0; n < len; n++)
                result.data[n] = data[n] / that.data[n];
            return result;
        }

        inline vecN& operator/=(const vecN& that)
        {
            assign(*this / that);

            return *this;
        }

        inline vecN operator/(const T& that) const
        {
            my_type result;
            int n;
            for (n = 0; n < len; n++)
                result.data[n] = data[n] / that;
            return result;
        }

        inline vecN& operator/=(const T& that)
        {
            assign(*this / that);
            return *this;
        }

        inline T& operator[](int n) { return data[n]; }
        inline const T& operator[](int n) const { return data[n]; }

        inline static int size(void) { return len; }

        inline operator const T* () const { return &data[0]; }

        static inline vecN random()
        {
            vecN result;
            int i;

            for (i = 0; i < len; i++)
            {
                result[i] = vec::random<T>();
            }
            return result;
        }

    protected:
        T data[len];

        inline void assign(const vecN& that)
        {
            int n;
            for (n = 0; n < len; n++)
                data[n] = that.data[n];
        }
    };

    template <typename T>
    class Tvec2 : public vecN<T,2>
    {
    public:
        typedef vecN<T,2> base;

        inline Tvec2() {}
        inline Tvec2(const base& v) : base(v) {}

        inline Tvec2(T x, T y)
        {
            base::data[0] = x;
            base::data[1] = y;
        }
    };

    template <typename T>
    class Tvec3 : public vecN<T,3>
    {
    public:
        typedef vecN<T,3> base;

        inline Tvec3() {}

        inline Tvec3(const base& v) : base(v) {}

        inline Tvec3(T x, T y, T z)
        {
            base::data[0] = x;
            base::data[1] = y;
            base::data[2] = z;
        }

        inline Tvec3(const Tvec2<T>& v, T z)
        {
            base::data[0] = v[0];
            base::data[1] = v[1];
            base::data[2] = z;
        }

        inline Tvec3(T x, const Tvec2<T>& v)
        {
            base::data[0] = x;
            base::data[1] = v[0];
            base::data[2] = v[1];
        }
    };

    template <typename T>
    class Tvec4 : public vecN<T,4>
    {
    public:
        typedef vecN<T,4> base;

        inline Tvec4() {}

        inline Tvec4(const base& v) : base(v) {}

        inline Tvec4(T x, T y, T z, T w)
        {
            base::data[0] = x;
            base::data[1] = y;
            base::data[2] = z;
            base::data[3] = w;
        }

        inline Tvec4(const Tvec2<T>& v, T z, T w)
        {
            base::data[0] = v[0];
            base::data[1] = v[1];
            base::data[2] = z;
            base::data[3] = w;
        }

        inline Tvec4(T x, const Tvec2<T>& v, T w)
        {
            base::data[0] = x;
            base::data[1] = v[0];
            base::data[2] = v[1];
            base::data[3] = w;
        }

        inline Tvec4(T x, T y, const Tvec2<T>& v)
        {
            base::data[0] = x;
            base::data[1] = y;
            base::data[2] = v[0];
            base::data[3] = v[1];
        }

        inline Tvec4(const Tvec2<T>& u, const Tvec2<T>& v)
        {
            base::data[0] = u[0];
            base::data[1] = u[1];
            base::data[2] = v[0];
            base::data[3] = v[1];
        }

        inline Tvec4(const Tvec3<T>& v, T w)
        {
            base::data[0] = v[0];
            base::data[1] = v[1];
            base::data[2] = v[2];
            base::data[3] = w;
        }
        inline Tvec4(T x, const Tvec3<T>& v)
        {
            base::data[0] = x;
            base::data[1] = v[0];
            base::data[2] = v[1];
            base::data[3] = v[2];
        }
    };
    typedef vecN<float, 1> vec1;
    typedef vecN<int, 1> ivec1;
    typedef vecN<unsigned int, 1> uvec1;
    typedef vecN<double, 1> dvec1;

    typedef Tvec2<float> vec2;
    typedef Tvec2<int> ivec2;
    typedef Tvec2<unsigned int> uvec2;
    typedef Tvec2<double> dvec2;

    typedef Tvec3<float> vec3;
    typedef Tvec3<int> ivec3;
    typedef Tvec3<unsigned int> uvec3;
    typedef Tvec3<double> dvec3;

    typedef Tvec4<float> vec4;
    typedef Tvec4<int> ivec4;
    typedef Tvec4<unsigned int> uvec4;
    typedef Tvec4<double> dvec4;

    template <typename T, int n>
    static inline const vecN<T,n> operator * (T x, const vecN<T,n>& v)
    {
        return v * x;
    }

    template <typename T>
    static inline const Tvec2<T> operator / (T x, const Tvec2<T>& v)
    {
        return Tvec2<T>(x / v[0], x / v[1]);
    }

    template <typename T>
    static inline const Tvec3<T> operator / (T x, const Tvec3<T>& v)
    {
        return Tvec3<T>(x / v[0], x / v[1], x / v[2]);
    }

    template <typename T>
    static inline const Tvec4<T> operator / (T x, const Tvec4<T>& v)
    {
        return Tvec4<T>(x / v[0], x / v[1], x / v[2], x / v[3]);
    }

    template <typename T, int len>
    static inline T dot(const vecN<T,len>& a, const vecN<T,len>& b)
    {
        int n;
        T total = T(0);
        for (n = 0; n < len; n++)
        {
            total += a[n] * b[n];
        }
        return total;
    }

    template <typename T>
    static inline vecN<T,3> cross(const vecN<T,3>& a, const vecN<T,3>& b)
    {
        return Tvec3<T>(a[1] * b[2] - b[1] * a[2],
                        a[2] * b[0] - b[2] * a[0],
                        a[0] * b[1] - b[0] * a[1]);
    }

    template <typename T, int len>
    static inline T length(const vecN<T,len>& v)
    {
        T result(0);

        for (int i = 0; i < v.size(); ++i)
        {
            result += v[i] * v[i];
        }

        return (T)sqrt(result);
    }

    template <typename T, int len>
    static inline vecN<T,len> normalize(const vecN<T,len>& v)
    {
        return v / length(v);
    }

    template <typename T, int len>
    static inline T distance(const vecN<T,len>& a, const vecN<T,len>& b)
    {
        return length(b - a);
    }

    template <typename T, int len>
    static inline T angle(const vecN<T,len>& a, const vecN<T,len>& b)
    {
        return acos(dot(a, b));
    }

    template <typename T, const int w, const int h>
    class matNM
    {
    public:
        typedef class matNM<T,w,h> my_type;
        typedef class vecN<T,h> vector_type;
        inline matNM()
        {
        }

        inline matNM(const matNM& that)
        {
            assign(that);
        }
        explicit inline matNM(T f)
        {
            for (int n = 0; n < w; n++)
            {
                data[n] = f;
            }
        }

        inline matNM(const vector_type& v)
        {
            for (int n = 0; n < w; n++)
            {
                data[n] = v;
            }
        }

        inline matNM& operator=(const my_type& that)
        {
            assign(that);
            return *this;
        }

        inline matNM operator+(const my_type& that) const
        {
            my_type result;
            int n;
            for (n = 0; n < w; n++)
                result.data[n] = data[n] + that.data[n];
            return result;
        }

        inline my_type& operator+=(const my_type& that)
        {
            return (*this = *this + that);
        }

        inline my_type operator-(const my_type& that) const
        {
            my_type result;
            int n;
            for (n = 0; n < w; n++)
                result.data[n] = data[n] - that.data[n];
            return result;
        }

        inline my_type& operator-=(const my_type& that)
        {
            return (*this = *this - that);
        }

        inline my_type operator*(const T& that) const
        {
            my_type result;
            int n;
            for (n = 0; n < w; n++)
                result.data[n] = data[n] * that;
            return result;
        }

        inline my_type& operator*=(const T& that)
        {
            int n;
            for (n = 0; n < w; n++)
                data[n] = data[n] * that;
            return *this;
        }
        inline my_type operator*(const my_type& that) const
        {
            my_type result(0);

            for (int j = 0; j < w; j++)
            {
                for (int i = 0; i < h; i++)
                {
                    T sum(0);

                    for (int n = 0; n < w; n++)
                    {
                        sum += data[n][i] * that[j][n];
                    }

                    result[j][i] = sum;
                }
            }

            return result;
        }

        inline my_type& operator*=(const my_type& that)
        {
            return (*this = *this * that);
        }

        inline vector_type& operator[](int n) { return data[n]; }
        inline const vector_type& operator[](int n) const { return data[n]; }
        inline operator T*() { return &data[0][0]; }
        inline operator const T*() const { return &data[0][0]; }

        inline matNM<T,h,w> transpose(void) const
        {
            matNM<T,h,w> result;
            int x, y;

            for (y = 0; y < w; y++)
            {
                for (x = 0; x < h; x++)
                {
                    result[x][y] = data[y][x];
                }
            }

            return result;
        }

        static inline my_type identity()
        {
            my_type result(0);

            for (int i = 0; i < w; i++)
            {
                result[i][i] = 1;
            }

            return result;
        }

        static inline int width(void) { return w; }
        static inline int height(void) { return h; }

    protected:

        vecN<T,h> data[w];

        inline void assign(const matNM& that)
        {
            int n;
            for (n = 0; n < w; n++)
                data[n] = that.data[n];
        }
    };

    template <typename T>
    class Tmat4 : public matNM<T,4,4>
    {
    public:
        typedef matNM<T,4,4> base;
        typedef Tmat4<T> my_type;

        inline Tmat4() {}
        inline Tmat4(const my_type& that) : base(that) {}
        inline Tmat4(const base& that) : base(that) {}
        inline Tmat4(const vecN<T,4>& v) : base(v) {}
        inline Tmat4(const vecN<T,4>& v0,
                     const vecN<T,4>& v1,
                     const vecN<T,4>& v2,
                     const vecN<T,4>& v3)
        {
            base::data[0] = v0;
            base::data[1] = v1;
            base::data[2] = v2;
            base::data[3] = v3;
        }
    };

    typedef Tmat4<float> mat4;
    typedef Tmat4<int> imat4;
    typedef Tmat4<unsigned int> umat4;
    typedef Tmat4<double> dmat4;

    template <typename T>
    class Tmat2 : public matNM<T,2,2>
    {
    public:
        typedef matNM<T,2,2> base;
        typedef Tmat2<T> my_type;

        inline Tmat2() {}
        inline Tmat2(const my_type& that) : base(that) {}
        inline Tmat2(const base& that) : base(that) {}
        inline Tmat2(const vecN<T,2>& v) : base(v) {}
        inline Tmat2(const vecN<T,2>& v0,
                     const vecN<T,2>& v1)
        {
            base::data[0] = v0;
            base::data[1] = v1;
        }
    };

    typedef Tmat2<float> mat2;

    static inline mat4 frustum(float left, float right, float bottom, float top, float n, float f)
    {
        mat4 result(mat4::identity());

        if ((right == left) ||
            (top == bottom) ||
            (n == f) ||
            (n < 0.0) ||
            (f < 0.0))
            return result;

        result[0][0] = (2.0f * n) / (right - left);
        result[1][1] = (2.0f * n) / (top - bottom);

        result[2][0] = (right + left) / (right - left);
        result[2][1] = (top + bottom) / (top - bottom);
        result[2][2] = -(f + n) / (f - n);
        result[2][3]= -1.0f;

        result[3][2] = -(2.0f * f * n) / (f - n);
        result[3][3] =  0.0f;

        return result;
    }

    static inline mat4 perspective(float fovy, float aspect, float n, float f)
    {
        float q = 1.0f / tan(radians(0.5f * fovy));
        float A = q / aspect;
        float B = (n + f) / (n - f);
        float C = (2.0f * n * f) / (n - f);

        mat4 result;

        result[0] = vec4(A, 0.0f, 0.0f, 0.0f);
        result[1] = vec4(0.0f, q, 0.0f, 0.0f);
        result[2] = vec4(0.0f, 0.0f, B, -1.0f);
        result[3] = vec4(0.0f, 0.0f, C, 0.0f);

        return result;
    }

    static inline mat4 ortho(float left, float right, float bottom, float top, float n, float f)
    {
        return mat4( vec4(2.0f / (right - left), 0.0f, 0.0f, 0.0f),
                     vec4(0.0f, 2.0f / (top - bottom), 0.0f, 0.0f),
                     vec4(0.0f, 0.0f, 2.0f / (n - f), 0.0f),
                     vec4((left + right) / (left - right), (bottom + top) / (bottom - top), (n + f) / (f - n), 1.0f) );
    }

    template <typename T>
    static inline Tmat4<T> translate(T x, T y, T z)
    {
        return Tmat4<T>(Tvec4<T>(1.0f, 0.0f, 0.0f, 0.0f),
                        Tvec4<T>(0.0f, 1.0f, 0.0f, 0.0f),
                        Tvec4<T>(0.0f, 0.0f, 1.0f, 0.0f),
                        Tvec4<T>(x, y, z, 1.0f));
    }

    template <typename T>
    static inline Tmat4<T> translate(const vecN<T,3>& v)
    {
        return translate(v[0], v[1], v[2]);
    }

    template <typename T>
    static inline Tmat4<T> lookat(const vecN<T,3>& eye, const vecN<T,3>& center, const vecN<T,3>& up)
    {
        const Tvec3<T> f = normalize(center - eye);
        const Tvec3<T> upN = normalize(up);
        const Tvec3<T> s = cross(f, upN);
        const Tvec3<T> u = cross(s, f);
        const Tmat4<T> M = Tmat4<T>(Tvec4<T>(s[0], u[0], -f[0], T(0)),
                                    Tvec4<T>(s[1], u[1], -f[1], T(0)),
                                    Tvec4<T>(s[2], u[2], -f[2], T(0)),
                                    Tvec4<T>(T(0), T(0), T(0), T(1)));

        return M * translate<T>(-eye);
    }

    template <typename T>
    static inline Tmat4<T> scale(T x, T y, T z)
    {
        return Tmat4<T>(Tvec4<T>(x, 0.0f, 0.0f, 0.0f),
                        Tvec4<T>(0.0f, y, 0.0f, 0.0f),
                        Tvec4<T>(0.0f, 0.0f, z, 0.0f),
                        Tvec4<T>(0.0f, 0.0f, 0.0f, 1.0f));
    }

    template <typename T>
    static inline Tmat4<T> scale(const Tvec3<T>& v)
    {
        return scale(v[0], v[1], v[2]);
    }

    template <typename T>
    static inline Tmat4<T> scale(T x)
    {
        return Tmat4<T>(Tvec4<T>(x, 0.0f, 0.0f, 0.0f),
                        Tvec4<T>(0.0f, x, 0.0f, 0.0f),
                        Tvec4<T>(0.0f, 0.0f, x, 0.0f),
                        Tvec4<T>(0.0f, 0.0f, 0.0f, 1.0f));
    }

    template <typename T>
    static inline Tmat4<T> rotate(T angle, T x, T y, T z)
    {
        Tmat4<T> result;

        const T x2 = x * x;
        const T y2 = y * y;
        const T z2 = z * z;
        float rads = float(angle) * 0.0174532925f;
        const float c = cosf(rads);
        const float s = sinf(rads);
        const float omc = 1.0f - c;

        result[0] = Tvec4<T>(T(x2 * omc + c), T(y * x * omc + z * s), T(x * z * omc - y * s), T(0));
        result[1] = Tvec4<T>(T(x * y * omc - z * s), T(y2 * omc + c), T(y * z * omc + x * s), T(0));
        result[2] = Tvec4<T>(T(x * z * omc + y * s), T(y * z * omc - x * s), T(z2 * omc + c), T(0));
        result[3] = Tvec4<T>(T(0), T(0), T(0), T(1));

        return result;
    }

    template <typename T>
    static inline Tmat4<T> rotate(T angle, const vecN<T,3>& v)
    {
        return rotate<T>(angle, v[0], v[1], v[2]);
    }

    template <typename T>
    static inline Tmat4<T> rotate(T angle_x, T angle_y, T angle_z)
    {
        return rotate(angle_z, 0.0f, 0.0f, 1.0f) *
               rotate(angle_y, 0.0f, 1.0f, 0.0f) *
               rotate(angle_x, 1.0f, 0.0f, 0.0f);
    }

#ifdef min
#undef min
#endif

    template <typename T>
    static inline T min(T a, T b)
    {
        return a < b ? a : b;
    }

#ifdef max
#undef max
#endif

    template <typename T>
    static inline T max(T a, T b)
    {
        return a >= b ? a : b;
    }

    template <typename T, const int N>
    static inline vecN<T,N> min(const vecN<T,N>& x, const vecN<T,N>& y)
    {
        vecN<T,N> t;
        int n;

        for (n = 0; n < N; n++)
        {
            t[n] = min(x[n], y[n]);
        }

        return t;
    }

    template <typename T, const int N>
    static inline vecN<T,N> max(const vecN<T,N>& x, const vecN<T,N>& y)
    {
        vecN<T,N> t;
        int n;

        for (n = 0; n < N; n++)
        {
            t[n] = max<T>(x[n], y[n]);
        }

        return t;
    }

    template <typename T, const int N>
    static inline vecN<T,N> clamp(const vecN<T,N>& x, const vecN<T,N>& minVal, const vecN<T,N>& maxVal)
    {
        return min<T>(max<T>(x, minVal), maxVal);
    }

    template <typename T, const int N>
    static inline vecN<T,N> smoothstep(const vecN<T,N>& edge0, const vecN<T,N>& edge1, const vecN<T,N>& x)
    {
        vecN<T,N> t;
        t = clamp((x - edge0) / (edge1 - edge0), vecN<T,N>(T(0)), vecN<T,N>(T(1)));
        return t * t * (vecN<T,N>(T(3)) - vecN<T,N>(T(2)) * t);
    }

    template <typename T, const int S>
    static inline vecN<T,S> reflect(const vecN<T,S>& I, const vecN<T,S>& N)
    {
        return I - 2 * dot(N, I) * N;
    }

    template <typename T, const int S>
    static inline vecN<T,S> refract(const vecN<T,S>& I, const vecN<T,S>& N, T eta)
    {
        T d = dot(N, I);
        T k = T(1) - eta * eta * (T(1) - d * d);
        if (k < 0.0)
        {
            return vecN<T,N>(0);
        }
        else
        {
            return eta * I - (eta * d + sqrt(k)) * N;
        }
    }

    template <typename T, const int N, const int M>
    static inline matNM<T,N,M> matrixCompMult(const matNM<T,N,M>& x, const matNM<T,N,M>& y)
    {
        matNM<T,N,M> result;
        int i, j;

        for (j = 0; j < M; ++j)
        {
            for (i = 0; i < N; ++i)
            {
                result[i][j] = x[i][j] * y[i][j];
            }
        }

        return result;
    }

    template <typename T, const int N, const int M>
    static inline vecN<T,N> operator*(const vecN<T,M>& vec, const matNM<T,N,M>& mat)
    {
        int n, m;
        vecN<T,N> result(T(0));

        for (m = 0; m < M; m++)
        {
            for (n = 0; n < N; n++)
            {
                result[n] += vec[m] * mat[n][m];
            }
        }

        return result;
    }

    template <typename T, const int N>
    static inline vecN<T,N> operator/(const T s, const vecN<T,N>& v)
    {
        int n;
        vecN<T,N> result;

        for (n = 0; n < N; n++)
        {
            result[n] = s / v[n];
        }

        return result;
    }

    template <typename T>
    static inline T mix(const T& A, const T& B, typename T::element_type t)
    {
        return B + t * (B - A);
    }

    template <typename T>
    static inline T mix(const T& A, const T& B, const T& t)
    {
        return B + t * (B - A);
    }

};


#endif //VEC_HPP
