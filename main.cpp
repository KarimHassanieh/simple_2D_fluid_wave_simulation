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
#include "gnuplot-iostream.h"



using namespace std;

const size_t kBuffersize=80;

struct wave {
  double x;
  double speed;
  double wavelength;
  double max_height;

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

std::vector<std::pair<double, double> > accumlate_wave(wave _wave , array <double, kBuffersize> heightFeild)

{
std::vector<std::pair<double, double> > pts;
  return pts;
}

int main (){
wave wave_1,wave_2;

//Array for wave y position
array <double, kBuffersize> heightFeild;
// Origin of Simulation
wave_1.x=0;
wave_2.x=1;
//Initial Wave  Speed
wave_1.speed=1;
wave_2.speed =-0.5;
//Wavelength
wave_1.wavelength=0.8;
wave_2.wavelength=1.2;
//Max max_height
wave_1.max_height=0.5;
wave_2.max_height=0.4;
// Delta T
double fps=100; //frame per second
double time_interval=1/fps;

//visualize updated_wave
Gnuplot gp;
cout << "Press Ctrl-C to quit Simulation Window." << std::endl;

while(1) {
wave_1=update_motion(wave_1,time_interval);
wave_2=update_motion(wave_2,time_interval);

// You can also use a separate container for each column, like so:
std::vector<std::pair<double, double> > pts_wave_1;
std::vector<std::pair<double, double> > pts_wave_2;
pts_wave_1.push_back(std::make_pair(wave_1.x,0));
pts_wave_2.push_back(std::make_pair(wave_2.x,0));


//pts_wave_1= accumlate_wave(wave_1,heightFeild);
//pts_wave_2=accumlate_wave(wave_2,heightFeild);




gp << "set yrange [-0.5:1]\n";
gp << "set xrange [0:1]\n";
gp<< "set title 'Simulation Window' \n";
gp<< "set xlabel 'X Axis' \n";
gp<< "set ylabel 'Y Axis' \n";
gp << "plot '-' with linespoints title 'Wave 1', "
		<< "'-' with linespoints title 'Wave 2'\n";;
gp.send1d(pts_wave_1);
gp.send1d(pts_wave_2);
gp.flush();

usleep(1000);
}

  return 0;
}
