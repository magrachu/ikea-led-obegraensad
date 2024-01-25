#pragma once

#include "PluginManager.h"

class vec2
{
  public:
  float x,y;
  vec2(){
    x=0.0;
    y=0.0;
  };
  vec2(float a) {
    x=a;
    y=a;
  };
  vec2(float a,float b) {
    x=a;
    y=b;
  };
  vec2 operator+(vec2 const& obj)
  {
    vec2 res;
    res.x=x+obj.x;
    res.y=y+obj.y;
    return res;
  };
  vec2 operator*(vec2 const& obj)
  {
    vec2 res;
    res.x=x*obj.x;
    res.y=y*obj.y;
    return res;
  };
  
};

class vec3
{
  public:
  float x,y,z;
  vec3(){
    x=0.0;
    y=0.0;
    z=0.0;
  };
  vec3(float a) {
    x=a;
    y=a;
    z=a;
  };
  vec3(float a,float b,float c) {
    x=a;
    y=b;
    z=c;
  };
  vec2 xy()
  {
    return vec2(x,y);
  }
  vec2 xx()
  {
    return vec2(x,x);
  }
  vec2 yy()
  {
    return vec2(y,y);
  }
  vec3 operator+(vec3 const& obj)
  {
    vec3 res;
    res.x=x+obj.x;
    res.y=y+obj.y;
    res.z=z+obj.z;
    return res;
  };
  vec3 operator-(vec3 const& obj)
  {
    vec3 res;
    res.x=x-obj.x;
    res.y=y-obj.y;
    res.z=z-obj.z;
    return res;
  };
  vec3 operator-(float const& a)
  {
    vec3 res;
    res.x=x-a;
    res.y=y-a;
    res.z=z-a;
    return res;
  };
  vec3 operator*(vec3 const& obj)
  {
    vec3 res;
    res.x=x*obj.x;
    res.y=y*obj.y;
    res.z=z*obj.z;
    return res;
  };
  
};

class vec4
{
  public:
  float x,y,z,w;
  vec4(){
    x=0.0;
    y=0.0;
    z=0.0;
    w=0.0;
  };
  vec4(float a) {
    x=a;
    y=a;
    z=a;
    w=a;
  };
  vec4(float a,float b,float c, float d) {
    x=a;
    y=b;
    z=c;
    w=d;
  };
  vec2 xy()
  {
    return vec2(x,y);
  }
  vec2 xx()
  {
    return vec2(x,x);
  }
  vec2 yy()
  {
    return vec2(y,y);
  }
  vec4 zzzz()
  {
    return vec4(z,z,z,z);
  }
  vec4 operator+(vec4 const& obj)
  {
    vec4 res;
    res.x=x+obj.x;
    res.y=y+obj.y;
    res.z=z+obj.z;
    res.w=w+obj.w;
    return res;
  };
  vec4 operator-(vec4 const& obj)
  {
    vec4 res;
    res.x=x-obj.x;
    res.y=y-obj.y;
    res.z=z-obj.z;
    res.w=w-obj.w;
    return res;
  };
  vec4 operator*(vec4 const& obj)
  {
    vec4 res;
    res.x=x*obj.x;
    res.y=y*obj.y;
    res.z=z*obj.z;
    res.w=w*obj.w;
    return res;
  };
  vec4 operator*(float const& a)
  {
    vec4 res;
    res.x=x*a;
    res.y=y*a;
    res.z=z*a;
    res.w=w*a;
    return res;
  };
  
};


vec4 permute(vec4 x);
vec4 taylorInvSqrt(vec4 r);
vec3 fade(vec3 t);
float cnoise(vec3 P);



class PerlinPlugin : public Plugin
{
private:
  const int numStars = 25;
  float noiseval=0.0;
  uint8_t brightness=0;

public:
  void setup() override;
  void loop() override;
  const char *getName() const override;
};
