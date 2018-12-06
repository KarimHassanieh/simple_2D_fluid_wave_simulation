

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



struct wave {
  double x;
  double speed;
  double wavelength;
  double height;
  double number_of_points;

};
struct display{
//const array<double, double> )  union_pts;
std::vector<std::pair<double, double> > pts;
};

struct Comp {
  bool operator()(const std::pair<int, int> &a, const std::pair<int, int> &b) {
    if (a.first != b.first) {
      return a.first < b.first;
    }
    return a.second > b.second;
  }

};







wave update_motion(wave current_wave,double time_interval)

{
wave updated_wave;
  updated_wave.x=current_wave.x+time_interval*current_wave.speed;
  updated_wave.speed=current_wave.speed;
  //Boundary Condition
  if(updated_wave.x>1)
{
  updated_wave.speed=-updated_wave.speed;
  updated_wave.x=updated_wave.speed*time_interval+1;
}
if (updated_wave.x<0)
{
  updated_wave.speed=-updated_wave.speed;
  updated_wave.x=time_interval*updated_wave.speed;
}
current_wave.x=updated_wave.x;
current_wave.speed=updated_wave.speed;
return current_wave;
}

vector<std::pair<double, double> > accumlate_wave(wave _wave,display display )

{

double number_of_points=_wave.number_of_points;
double x=_wave.x;
double amplitude=_wave.height;
double wavelength=_wave.wavelength;

double quarterWavelenghth=wavelength/4;
vector<pair<double, double> > pts;
int start=(x-(quarterWavelenghth))*number_of_points;
int  end=((quarterWavelenghth)+x)*number_of_points;

for(int i=start;i<=end;i++)
{

double xpt_position = ((i + 0.5) / number_of_points -x);
double y_pos = amplitude*0.5*(cos(min(xpt_position* M_PI / quarterWavelenghth, M_PI)) + 1.0);
pts.push_back(std::make_pair(xpt_position+x,y_pos));
int iNew = i;
//if (i < 0) {iNew = -i - 1;}
//else if (i >= number_of_points) {iNew = 2 * number_of_points - i - 1;}
//(heightField)[iNew] += y_pos;
}
//display.pts=pts;
return pts;
}

int main (){
wave wave_1,wave_2;
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
wave_1.height=0.5;
wave_2.height=0.4;
//Number of Sampled points in wave
wave_1.number_of_points=80;
wave_2.number_of_points=80;


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
std::vector<std::pair<double, double> > pts_union;
display display;
//array<double, 80> heightField;
// Clear height field
//for (double y_pos : heightField) {y_pos = 0.0;}
pts_wave_1=accumlate_wave(wave_1,display);
pts_wave_2=accumlate_wave(wave_2,display);


//Comp comp_functor;
//std::sort(pts_wave_1.begin(), pts_wave_1.end(), comp_functor);
//std::sort(pts_wave_2.begin(), pts_wave_2.end(), comp_functor);


merge(pts_wave_2.begin(), pts_wave_2.end(), pts_wave_1.begin(), pts_wave_1.end(), std::back_inserter(pts_union));
gp << "set yrange [-0.5:1]\n";
gp << "set xrange [0:1]\n";
gp<< "set title 'Simulation Window' \n";
gp<< "set xlabel 'X Axis' \n";
gp<< "set ylabel 'Y Axis' \n";
//gp << "plot '-' with linespoints title 'Wave 1', "
//		<< "'-' with linespoints title 'Wave 2',"
gp<< "plot '-' with linespoints title 'Resultant Wave'\n";
//gp << "plot '-' binary" << gp.binFmt1d(display.union_pts, "array") << "with lines notitle\n";
//gp.sendBinary1d(display.union_pts);
//gp.send1d(pts_wave_1);
//gp.send1d(pts_wave_2);
gp.send1d(pts_union);
gp.flush();

usleep(1000);
}

  return 0;
}
