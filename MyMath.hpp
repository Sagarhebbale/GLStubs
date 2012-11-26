//
//  MyMath.hpp
//  CamCap
//
//  Created by Aditya Vijayakumar on 16/01/12.
//  Copyright (c) 2012 moveablecode. All rights reserved.
//

#ifndef __MY_MATH__
#define __MY_MATH__

#import <math.h>

#define PI_OVER_360 (3.14/360)

typedef struct Vector3D
{
    float x, y, z, w;
}Vector3D;

typedef struct ColorRGBA
{
    float r, g, b, a;
}ColorRGBA;

typedef struct Matrix
{
    float a[16];
}Matrix;

static inline float DegToRad(float deg)
{
    return deg * 0.017453;
}

static inline float RadToDeg(float rad)
{
    float ret = rad * 57.29577;
    
    ret = (int)ret % 360;
    
    return ret;
}

static inline float PLUS(float a)
{
    return a>0 ? a : -a;
}

static inline Vector3D makeVector(float x, float y, float z)
{
    Vector3D ret;
    
    ret.x = x;
    ret.y = y;
    ret.z = z;
    ret.w = 1;
    
    return ret;
}

static inline float euclideanDistance(Vector3D a, Vector3D b)
{
    float x = a.x-b.x;
    float y = a.y-b.y;
    float z = a.z-b.z;
    
    return sqrtf(x*x+y*y+z*z);
}

static inline Vector3D normalizeVector(Vector3D a)
{
    Vector3D ret;
    Vector3D zero;
    
    zero.x = zero.y = zero.z = 0;
    
    float distance = euclideanDistance(zero, a);
    
    ret.x = a.x / distance;
    ret.y = a.y / distance;
    ret.z = a.z / distance;
    
    return ret;
}

static inline Vector3D addVectors(Vector3D a, Vector3D b)
{
    Vector3D ret;
    
    ret.x = a.x + b.x;
    ret.y = a.y + b.y;
    ret.z = a.z + b.z;
    
    return ret;
}

static inline Vector3D subVectors(Vector3D a, Vector3D b)
{
    Vector3D ret;
    
    ret.x = a.x - b.x;
    ret.y = a.y - b.y;
    ret.z = a.z - b.z;
    
    return ret;
}

static inline float dot(Vector3D a, Vector3D b)
{
    return a.x*b.x+a.y*b.y+a.z*b.z;
}

static inline Vector3D cross(Vector3D a, Vector3D b)
{
    Vector3D ret;
    
    ret.x = (a.y*b.z-a.z*b.y);
    ret.y = -(a.x*b.z-a.z*b.x);
    ret.z = (a.x*b.y-a.y*b.x);
    
    return ret;
}

static inline Matrix mul(const Matrix *aa, const Matrix *bb)
{
    Matrix ret;
    
    const float *a = &(aa->a[0]);
    const float *b = &(bb->a[0]);
    
    ret.a[0] = a[0]*b[0] + a[4]*b[1] + a[8]*b[2] + a[12]*b[3]; 	
    ret.a[4] = a[0]*b[4] + a[4]*b[5] + a[8]*b[6] + a[12]*b[7]; 	
    ret.a[8] = a[0]*b[8] + a[4]*b[9] + a[8]*b[10] + a[12]*b[11]; 	
    ret.a[12]= a[0]*b[12] + a[4]*b[13] + a[8]*b[14] + a[12]*b[15];
    ret.a[1] = a[1]*b[0] + a[5]*b[1] + a[9]*b[2] + a[13]*b[3]; 	
    ret.a[5] = a[1]*b[4] + a[5]*b[5] + a[9]*b[6] + a[13]*b[7]; 	
    ret.a[9] = a[1]*b[8] + a[5]*b[9] + a[9]*b[10] + a[13]*b[11]; 	
    ret.a[13]= a[1]*b[12] + a[5]*b[13] + a[9]*b[14] + a[13]*b[15];
    ret.a[2] = a[2]*b[0] + a[6]*b[1] + a[10]*b[2] + a[14]*b[3]; 	
    ret.a[6] = a[2]*b[4] + a[6]*b[5] + a[10]*b[6] + a[14]*b[7]; 	
    ret.a[10]= a[2]*b[8] + a[6]*b[9] + a[10]*b[10] + a[14]*b[11];   
    ret.a[14]= a[2]*b[12] + a[6]*b[13] + a[10]*b[14] + a[14]*b[15];
    ret.a[3] = a[3]*b[0] + a[7]*b[1] + a[11]*b[2] + a[15]*b[3]; 	
    ret.a[7] = a[3]*b[4] + a[7]*b[5] + a[11]*b[6] + a[15]*b[7]; 	
    ret.a[11]= a[3]*b[8] + a[7]*b[9] + a[11]*b[10] + a[15]*b[11];	
    ret.a[15]= a[3]*b[12] + a[7]*b[13] + a[11]*b[14] + a[15]*b[15];
    
    return ret;
}

static inline Matrix add(const Matrix *aa, const Matrix *bb)
{
    Matrix ret;
    int i;
    
    const float *a = &(aa->a[0]);
    const float *b = &(bb->a[0]);
    
    for(i=0; i<16; i++)
        ret.a[i] = a[i] + b[i];
    
    return ret;
}

static inline Matrix unitMatrix()
{
    Matrix ret;
    
    ret.a[0] =1; 	ret.a[4] =0; 	ret.a[8] =0; 	ret.a[12] =0;
    ret.a[1] =0; 	ret.a[5] =1; 	ret.a[9] =0; 	ret.a[13] =0;
    ret.a[2] =0; 	ret.a[6] =0; 	ret.a[10] =1;   ret.a[14] =0;
    ret.a[3] =0; 	ret.a[7] =0; 	ret.a[11] =0;	ret.a[15] =1;
    
    return ret;
}

static inline Matrix scale(Vector3D v)
{
    Matrix ret = unitMatrix();
    
    ret.a[0] = v.x;
    ret.a[5] = v.y;
    ret.a[10] = v.z;
    
    return ret;
}

static inline Matrix view(Vector3D eyePos, Vector3D lookAt, Vector3D up)
{
    const Vector3D zaxis = normalizeVector(subVectors(eyePos, lookAt));
    const Vector3D xaxis = normalizeVector(cross(up, zaxis));
    const Vector3D yaxis = cross(zaxis, xaxis);
    Matrix ret;
    
    ret.a[0] = xaxis.x;
    ret.a[4] = yaxis.x;
    ret.a[8] = zaxis.x;
    ret.a[1] = xaxis.y;
    ret.a[5] = yaxis.y;
    ret.a[9] = zaxis.y;
    ret.a[2] = xaxis.z;
    ret.a[6] = yaxis.z;
    ret.a[10] = zaxis.z;
    ret.a[3] = -dot(xaxis, eyePos);
    ret.a[7] = -dot(yaxis, eyePos);
    ret.a[11] = -dot(zaxis, eyePos);
    
    return ret;
}

static inline Matrix persProjection(float degreeFOV, float aspectRatio, float near, float far)
{
    Matrix ret = unitMatrix();
    const float f = atanf(degreeFOV/2);
    
    ret.a[0] = f/aspectRatio;
    ret.a[5] = f;
    ret.a[10] = (far+near)/(near-far);
    ret.a[11] = -1;
    ret.a[14] = 2*(near*far)/(near-far);
    ret.a[15] = 0;
    
    return ret;
}

static inline Matrix orthoProjection(float top, float left, float bottom, float right, float far, float near)
{
    Matrix ret = unitMatrix();
    
    ret.a[0] = 2/(right-left);
    ret.a[5] = 2/(top-bottom);
    ret.a[10] = -2/(far-near);
    ret.a[12] = -(right+left)/(right-left);
    ret.a[13] = -(top+bottom)/(top-bottom);
    ret.a[14] = -(far+near)/(far-near);
    
    return ret;
}

static inline Matrix translate(Vector3D v)
{
    Matrix ret = unitMatrix();
    
    ret.a[12] = v.x;
    ret.a[13] = v.y;
    ret.a[14] = v.z;
    
    return ret;
}

static inline Matrix rotateX(float degrees)
{
    Matrix ret = unitMatrix();
    float radians = DegToRad(degrees);
    
    ret.a[5] = cosf(radians);
    ret.a[9] = -sinf(radians);
    ret.a[6] = sinf(radians);
    ret.a[10] = cosf(radians);
    
    return ret;
}

static inline Matrix rotateY(float degrees)
{
    Matrix ret = unitMatrix();
    float radians = DegToRad(degrees);
    
    ret.a[0] = cosf(radians);
    ret.a[8] = sinf(radians);
    ret.a[2] = -sinf(radians);
    ret.a[10] = cosf(radians);
    
    return ret;
}

static inline Matrix rotateZ(float degrees)
{
    Matrix ret = unitMatrix();
    float radians = DegToRad(degrees);
    
    ret.a[0] = cosf(radians);
    ret.a[4] = -sinf(radians);
    ret.a[1] = sinf(radians);
    ret.a[5] = cosf(radians);
    
    return ret;
}

static inline ColorRGBA makeColorRGBA(float r, float g, float b, float a)
{
    ColorRGBA ret;
    
    ret.r = r;
    ret.g = g;
    ret.b = b;
    ret.a = a;
    
    return ret;
}

static inline float colorDiff(ColorRGBA a, ColorRGBA b)
{
    float ret = 0;
    
    ret += PLUS(a.r-b.r);
    ret += PLUS(a.g-b.g);
    ret += PLUS(a.b-b.b);
    
    return ret;
}

static inline ColorRGBA makeColorRGB(float r, float g, float b)
{
    return makeColorRGBA(r, g, b, 1.0f);
}

static inline ColorRGBA colorFrom4Byte(const GLubyte *data)
{
    ColorRGBA ret;
    
    ret.r = data[0]/255.0;
    ret.g = data[1]/255.0;
    ret.b = data[2]/255.0;
    ret.a = data[3]/255.0;
    
    return ret;
}

static inline bool floatEquals(float a, float b, float error)
{
    return (a + error > b) && (b + error > a);
}

#endif