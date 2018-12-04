// Copyright (c) 2018 Doyub Kim
//
// I am making my contributions/submissions to this project solely in my
// personal capacity and am not conveying any rights to any intellectual
// property of any third parties.

#include <algorithm>
#include <array>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <string>
#include <thread>
#include <jet/jet.h>
#include <iostream>





using namespace std;

struct wave {
  double x;
  double speed;
};
wave update_motion(wave current_wave,double time_interval)
{
  wave updated_wave;
  updated_wave.x=current_wave.x+time_interval*current_wave.speed;
  updated_wave.speed=current_wave.speed;

  //Boundary Condition
  if(updated_wave.x>1){
  updated_wave.speed=-updated_wave.speed;
  updated_wave.x=updated_wave.speed*time_interval+1;
}
if (updated_wave.x<0){
  updated_wave.speed=-updated_wave.speed;
  updated_wave.x=time_interval*updated_wave.speed;
}

  return updated_wave;
}

int main (){
wave wave_1,wave_2;
// Origin of Simulation
wave_1.x=0;
wave_2.x=1;
//Initial Wave  Speed
wave_1.speed=1;
wave_2.speed =-0.5;
// Delta T
double fps=100; //frame per second
double time_interval=1/fps;
int TOTAL_SIM=1000;

cout<<"Progress Done : ";
for (int i=0;i<=TOTAL_SIM;i++){
wave_1=update_motion(wave_1,time_interval);
//wave_2=update_motion(wave_2,time_interval);
cout<<"after updating "<<wave_1.x<<endl;
}
  return 0;
}
