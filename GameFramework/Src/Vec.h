// Vec.h

#pragma once

float radianToDegree(float _fRad);
float degreeToRadian(float _fDeg);

struct Vec
{
public:
    float x;
    float y;

    Vec()
        : x(0.f)
        , y(0.f)
    {}

    Vec(float _x, float _y)
        : x(_x)
        , y(_y)
    {}

    Vec(int _x, int _y)
        : x((float)_x)
        , y((float)_y)
    {}

    ~Vec()
    {}

    const Vec& operator = (const Vec& _v)
    {
        x = _v.x;
        y = _v.y;
        return *this;
    }

    const Vec& operator = (const POINT& _pt)
    {
        x = (float)_pt.x;
        y = (float)_pt.y;
        return *this;
    }

    // +
    Vec operator + (const Vec& _v) const
    {
        Vec res;
        res.x = x + _v.x;
        res.y = y + _v.y;
        return res;
    }

    Vec operator + (const POINT& _pt) const
    {
        Vec res;
        res.x = x + _pt.x;
        res.y = y + _pt.y;
        return res;
    }

    Vec operator + (float _f) const
    {
        Vec res;
        res.x = x + _f;
        res.y = y + _f;
        return res;
    }

    Vec operator + (int _n) const
    {
        Vec res;
        res.x = x + (float)_n;
        res.y = y + (float)_n;
        return res;
    }

    const Vec& operator += (const Vec& _v)
    {
        x = x + _v.x;
        y = y + _v.y;
        return *this;
    }

    const Vec& operator += (const POINT& _pt)
    {
        x = x + _pt.x;
        y = y + _pt.y;
        return *this;
    }

    const Vec& operator += (float _f)
    {
        x = x + _f;
        y = y + _f;
        return *this;
    }

    const Vec& operator += (int _n)
    {
        x = x + _n;
        y = y + _n;
        return *this;
    }

    // -
    Vec operator - (const Vec& _v) const
    {
        Vec res;
        res.x = x - _v.x;
        res.y = y - _v.y;
        return res;
    }

    Vec operator - (const POINT& _pt) const
    {
        Vec res;
        res.x = x - _pt.x;
        res.y = y - _pt.y;
        return res;
    }

    Vec operator - (float _f) const
    {
        Vec res;
        res.x = x - _f;
        res.y = y - _f;
        return res;
    }

    Vec operator - (int _n) const
    {
        Vec res;
        res.x = x - (float)_n;
        res.y = y - (float)_n;
        return res;
    }

    const Vec& operator -= (const Vec& _v)
    {
        x = x - _v.x;
        y = y - _v.y;
        return *this;
    }

    const Vec& operator -= (const POINT& _pt)
    {
        x = x - _pt.x;
        y = y - _pt.y;
        return *this;
    }

    const Vec& operator -= (float _f)
    {
        x = x - _f;
        y = y - _f;
        return *this;
    }

    const Vec& operator -= (int _n)
    {
        x = x - _n;
        y = y - _n;
        return *this;
    }

    // *
    Vec operator * (const Vec& _v) const
    {
        Vec res;
        res.x = x * _v.x;
        res.y = y * _v.y;
        return res;
    }

    Vec operator * (const POINT& _pt) const
    {
        Vec res;
        res.x = x * _pt.x;
        res.y = y * _pt.y;
        return res;
    }

    Vec operator * (float _f) const
    {
        Vec res;
        res.x = x * _f;
        res.y = y * _f;
        return res;
    }

    Vec operator * (int _n) const
    {
        Vec res;
        res.x = x * (float)_n;
        res.y = y * (float)_n;
        return res;
    }

    const Vec& operator *= (const Vec& _v)
    {
        x = x * _v.x;
        y = y * _v.y;
        return *this;
    }

    const Vec& operator *= (const POINT& _pt)
    {
        x = x * _pt.x;
        y = y * _pt.y;
        return *this;
    }

    const Vec& operator *= (float _f)
    {
        x = x * _f;
        y = y * _f;
        return *this;
    }

    const Vec& operator *= (int _n)
    {
        x = x * _n;
        y = y * _n;
        return *this;
    }

    // /
    Vec operator / (const Vec& _v) const
    {
        assert(!(0.f == _v.x || 0.f == _v.y));
        Vec res;
        res.x = x / _v.x;
        res.y = y / _v.y;
        return res;
    }

    Vec operator / (const POINT& _pt) const
    {
        assert(!(0.f == _pt.x || 0.f == _pt.y));
        Vec res;
        res.x = x / _pt.x;
        res.y = y / _pt.y;
        return res;
    }

    Vec operator / (float _f) const
    {
        assert(0.f != _f);
        Vec res;
        res.x = x / _f;
        res.y = y / _f;
        return res;
    }

    Vec operator / (int _n) const
    {
        assert(0.f != _n);
        Vec res;
        res.x = x / (float)_n;
        res.y = y / (float)_n;
        return res;
    }

    const Vec& operator /= (const Vec& _v)
    {
        assert(!(0.f == _v.x || 0.f == _v.y));
        x = x / _v.x;
        y = y / _v.y;
        return *this;
    }

    const Vec& operator /= (const POINT& _pt)
    {
        assert(!(0.f == _pt.x || 0.f == _pt.y));
        x = x / _pt.x;
        y = y / _pt.y;
        return *this;
    }

    const Vec& operator /= (float _f)
    {
        assert(0.f != _f);
        x = x / _f;
        y = y / _f;
        return *this;
    }

    const Vec& operator /= (int _n)
    {
        assert(0.f != _n);
        x = x / _n;
        y = y / _n;
        return *this;
    }

    float length() const
    {
        return sqrtf(x * x + y * y);
    }

    void normalize()
    {
        float thisLength = length();
        if (0 != thisLength)
        {
            x /= thisLength;
            y /= thisLength;
        }
    }

};

float distance(const Vec& _vSrc, const Vec& _vDes);
float getAngle(const Vec& _vSrc, const Vec& _vDes);