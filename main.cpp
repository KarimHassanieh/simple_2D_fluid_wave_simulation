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
#include <pangolin/pangolin.h>



using namespace std;

const size_t Buffersize=80;

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

int accumlate_wave(wave current_wave , array <double, Buffersize> heightFeild)

{

  return 0;
}


int visualize (wave wave_1,wave wave_2, double time_interval)
{
  // Create OpenGL window in single line
 pangolin::CreateWindowAndBind("Simulation Window",640,480);
 // Data logger object
 pangolin::DataLog log;
 // Optionally add named labels
 std::vector<std::string> labels;
labels.push_back(std::string("Wave 1"));
labels.push_back(std::string("Wave 2"));
log.SetLabels(labels);
// OpenGL 'view' of data. We might have many views of the same data.
//pangolin::Plotter plotter(&log,0, 1, -1, 1, 30, 0.5 );
const float tinc = 0.01f;
// pangolin::Plotter plotter(&log,0,600,-1,1,30, float ticky=0.5 );
pangolin::Plotter plotter(&log,0.0f,4.0f*(float)M_PI/tinc,-2.0f,2.0f,(float)M_PI/(4.0f*tinc),0.5f);

  // Add some sample annotations to the plot
  plotter.AddMarker(pangolin::Marker::Vertical,   -1000, pangolin::Marker::LessThan, pangolin::Colour::Blue().WithAlpha(0.2f) );
  plotter.AddMarker(pangolin::Marker::Vertical,   100, pangolin::Marker::GreaterThan, pangolin::Colour::Red().WithAlpha(0.2f) );
  plotter.AddMarker(pangolin::Marker::Vertical,    10, pangolin::Marker::Equal, pangolin::Colour::Green().WithAlpha(0.2f) );
// Add some sample annotations to the plot
pangolin::DisplayBase().AddDisplay(plotter);
  // Default hooks for exiting (Esc) and fullscreen (tab).
  while(!pangolin::ShouldQuit())
  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    wave_1=update_motion(wave_1,time_interval);
    wave_2=update_motion(wave_2,time_interval);
     log.Log(wave_1.x,wave_2.x);
    // Render graph, Swap frames and Process Events
    pangolin::FinishFrame();
  }





  return 0;
}





int main (){
wave wave_1,wave_2;

//Array for wave y position
array <double, Buffersize> heightFeild;
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
visualize(wave_1,wave_2,time_interval);
  return 0;
}
