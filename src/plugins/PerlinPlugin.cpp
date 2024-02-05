#include "plugins/PerlinPlugin.h"
#include "math.h"

float mix(float x,float y,float a){
  return x*(1.0-a)+y*a;
}
vec2 mix(vec2 x,vec2 y,float a){
  return vec2(mix(x.x,y.x,a),mix(x.y,y.y,a));

}
vec4 mix(vec4 x,vec4 y,float a){
  return vec4(mix(x.x,y.x,a),mix(x.y,y.y,a),mix(x.z,y.z,a),mix(x.w,y.w,a));

}



float step(float edge, float x) {
  float v;
  (x<edge) ? v= 0.0 : v= 1.0;
  return v;
} 

vec4 step(float edge, vec4 x){
  return vec4(step(edge,x.x),step(edge,x.y),step(edge,x.z),step(edge,x.w));
}


vec4 step(vec4 edge, vec4 x){
  return vec4(step(edge.x,x.x),step(edge.y,x.y),step(edge.z,x.z),step(edge.w,x.w));
}


vec4 abs(vec4 v){
  return vec4(abs(v.x),abs(v.y),abs(v.z),abs(v.w));
} 

float dot(vec3 a,vec3 b){
  return (a.x*b.x)+(a.y*b.y)+(a.z*b.z);
}

vec4 floor(vec4 v){
  return vec4(floor(v.x),floor(v.y),floor(v.z),floor(v.w));
}
vec3 floor(vec3 v){
  return vec3(floor(v.x),floor(v.y),floor(v.z));
}
vec4 fmod(vec4 v,float m){
  return vec4(fmod(v.x,m),fmod(v.y,m),fmod(v.z,m),fmod(v.w,m));
}
vec3 fmod(vec3 v,float m){
  return vec3(fmod(v.x,m),fmod(v.y,m),fmod(v.z,m));
}
vec4 fract(vec4 v){
  return v-floor(v);
}
vec3 fract(vec3 v){
  return v-floor(v);
}



vec4 permute(vec4 x)
{
  vec4 y;
  y=fmod(x*((x*34.0)+vec4(1.0)), 289.0);
  return y;
  }
vec4 taylorInvSqrt(vec4 r)
{
  vec4 y;
   y= (r*-0.85373472095314)+1.79284291400159;

  return y;
  }
vec3 fade(vec3 t) 
{
  vec3 y;
  y=t*t*t*(t*(t*6.0-vec3(15.0))+vec3(10.0));

  return y;
  }





float cnoise(vec3 P){
  vec3 Pi0 = floor(P); // Integer part for indexing
  vec3 Pi1 = Pi0 + vec3(1.0); // Integer part + 1
  Pi0 = fmod(Pi0, 289.0);
  Pi1 = fmod(Pi1, 289.0);
  vec3 Pf0 = fract(P); // Fractional part for interpolation
  vec3 Pf1 = Pf0 - vec3(1.0); // Fractional part - 1.0
  vec4 ix = vec4(Pi0.x, Pi1.x, Pi0.x, Pi1.x);
  vec4 iy = vec4(Pi0.y,Pi0.y, Pi1.y, Pi1.y);
  vec4 iz0 = vec4(Pi0.z, Pi0.z,Pi0.z,Pi0.z);
  vec4 iz1 = vec4(Pi1.z, Pi1.z,Pi1.z,Pi1.z);

  vec4 ixy = permute(permute(ix) + iy);
  vec4 ixy0 = permute(ixy + iz0);
  vec4 ixy1 = permute(ixy + iz1);

  vec4 gx0 = ixy0 * 0.1428571428571429;
  vec4 gy0 = fract(floor(gx0) * 0.1428571428571429) - vec4(0.5);
  gx0 = fract(gx0);
  vec4 gz0 = vec4(0.5) - abs(gx0) - abs(gy0);
  vec4 sz0 = step(gz0, vec4(0.0));
  gx0 = gx0 - sz0 * (step(0.0, gx0) - 0.5);
  gy0 = gy0 - sz0 * (step(0.0, gy0) - 0.5);

  vec4 gx1 = ixy1  * 0.1428571428571429;
  vec4 gy1 = fract(floor(gx1)  * 0.1428571428571429) - vec4(0.5);
  gx1 = fract(gx1);
  vec4 gz1 = vec4(0.5) - abs(gx1) - abs(gy1);
  vec4 sz1 = step(gz1, vec4(0.0));
  gx1 =  gx1 - sz1 * (step(0.0, gx1) - vec4(0.5));
  gy1 = gy1 - sz1 * (step(0.0, gy1) - vec4(0.5));

  vec3 g000 = vec3(gx0.x,gy0.x,gz0.x);
  vec3 g100 = vec3(gx0.y,gy0.y,gz0.y);
  vec3 g010 = vec3(gx0.z,gy0.z,gz0.z);
  vec3 g110 = vec3(gx0.w,gy0.w,gz0.w);
  vec3 g001 = vec3(gx1.x,gy1.x,gz1.x);
  vec3 g101 = vec3(gx1.y,gy1.y,gz1.y);
  vec3 g011 = vec3(gx1.z,gy1.z,gz1.z);
  vec3 g111 = vec3(gx1.w,gy1.w,gz1.w);

  vec4 norm0 = taylorInvSqrt(vec4(dot(g000, g000), dot(g010, g010), dot(g100, g100), dot(g110, g110)));
  g000 = g000*norm0.x;
  g010 = g010*norm0.y;
  g100 = g100*norm0.z;
  g110 = g110*norm0.w;
  vec4 norm1 = taylorInvSqrt(vec4(dot(g001, g001), dot(g011, g011), dot(g101, g101), dot(g111, g111)));
  g001 = g001*norm1.x;
  g011 = g011*norm1.y;
  g101 = g101*norm1.z;
  g111 = g111*norm1.w;

  float n000 = dot(g000, Pf0);
  float n100 = dot(g100, vec3(Pf1.x, Pf0.y,Pf0.z));
  float n010 = dot(g010, vec3(Pf0.x, Pf1.y, Pf0.z));
  float n110 = dot(g110, vec3(Pf1.x,Pf1.y, Pf0.z));
  float n001 = dot(g001, vec3(Pf0.x,Pf0.y, Pf1.z));
  float n101 = dot(g101, vec3(Pf1.x, Pf0.y, Pf1.z));
  float n011 = dot(g011, vec3(Pf0.x, Pf1.y,Pf1.z));
  float n111 = dot(g111, Pf1);

  vec3 fade_xyz = fade(Pf0);
  vec4 n_z = mix(vec4(n000, n100, n010, n110), vec4(n001, n101, n011, n111), fade_xyz.z);
  vec2 n_yz = mix(vec2(n_z.x,n_z.y),vec2(n_z.z,n_z.w), fade_xyz.y);
  float n_xyz = mix(n_yz.x, n_yz.y, fade_xyz.x); 
  return 2.2 * n_xyz;
}

float limit(float low, float val, float high){
  if (val < low){
    return low;
  }
  if (val > high) {
    return high;
  }
  return val;
}

float currentTime_old;

void PerlinPlugin::setup()
{
  Screen.clear();
  // run tests
  currentTime_old = millis()*0.001;
  float testval[5] = {0,0.1,0.5,1.0,2.0};
  float goalval[5]= {0,0.4499,9.0,35.0,138.0};

  Serial.println("run some tests");
  Serial.println("test permute:");
  for(int i=0;i<5;i++){
    Serial.printf("testval= %f, result= %f, expected %f\n",testval[i],permute(vec4(testval[i])).x,goalval[i]);

  }

  float testval2[5] = {0,0.1,1.0,2.0,10.0};
  float goalval2[5]= {1.792842,1.707469,0.939107,0.085373,-6.744504};
Serial.println("test taylorInvSqrt:");
  for(int i=0;i<5;i++){
    Serial.printf("testval= %f, result= %f, expected %f\n",testval2[i],taylorInvSqrt(vec4(testval[i])).x,goalval2[i]);

  }

  float testval3[8] = {0,0.1,0.2,0.5,0.6,1.0,1.5,10.5};
  float goalval3[8]= {0.0,0.008559,0.057919,0.5,0.682559,1.0,3.375,595019.25};
Serial.println("test fade:");
  for(int i=0;i<8;i++){
    Serial.printf("testval= %f, result= %f, expected %f\n",testval3[i],fade(vec3(testval3[i])).x,goalval3[i]);

  }
  const int numVal4=3;
  vec3 testval4[numVal4] = {vec3(0.1),vec3(0.2),vec3(0.5)};
  float goalval4[numVal4]= {-0.190088,-0.417861,-0.625376};
  Serial.println("test cnoise:");
  for(int i=0;i<numVal4;i++){
    Serial.printf("testval= %f, result= %f, expected %f\n",testval4[i],cnoise(testval4[i]),goalval4[i]);

  }

const int numVal5=3;
  vec4 testval5[numVal5] = {vec4(5.2),vec4(10.9),vec4(-10.4)};
  float goalval5[numVal5]= {0.2,0.9,0.6};
  Serial.println("test fract:");
  for(int i=0;i<numVal5;i++){
    Serial.printf("testval= %f, result= %f, expected %f\n",testval5[i].x,fract(testval5[i]).x,goalval5[i]);

  }


  const int numVal6=10;
  vec3 testval6[numVal6] = {vec3(10.1,9.9,0.0),vec3(10.1,9.9,1.0),vec3(10.1,9.9,2.0),vec3(10.1,9.9,3.0),vec3(10.1,9.9,4.0),vec3(0.2,9.5,0.5),vec3(0.2,9.5,1.5),vec3(0.2,9.5,2.5),vec3(0.2,9.5,3.5),vec3(0.2,9.5,4.5),};
  float goalval6[numVal6]= {0.0899,0.015091,0.103821,0.169510,0.121684,0.202738,-0.259893,0.140048,-0.193751,0.153087};
  Serial.println("test cnoise:");
  for(int i=0;i<numVal6;i++){
    Serial.printf("testval= %f, result= %f, expected %f\n",testval6[i].z,cnoise(testval6[i]),goalval6[i]);

  }

}

//#define debug
void PerlinPlugin::loop()
{
  #ifdef debug
    Serial.println("perlinpattern");
  #endif
  
  float currentTime = 2*millis()*0.001;
  for(int x=0; x<COLS;x++){
    
    for(int y=0; y<ROWS;y++){
      noiseval=(cnoise(vec3(x*0.25,y*0.4,currentTime*0.1))+1.0)*0.5;

      const float lim=1.0;
      #ifdef debug
    Serial.printf("%.2f, ",noiseval);
  #endif
      noiseval=limit(0.0,noiseval-0.2,1.0);
      brightness=min(noiseval*noiseval,lim)*255;
       Screen.setPixel(x, y, 1, brightness);




    }
    currentTime = millis()*0.001;
    //Serial.printf(": %f\n",currentTime-currentTime_old);
    currentTime_old= currentTime;
    // delay(1);
    #ifdef debug
    Serial.printf(": %d\n",x);
  #endif
    
  }
  #ifdef debug
    delay(1000);
  #endif

  
  
}

const char *PerlinPlugin::getName() const
{
  return "PerlinNoise";
}
