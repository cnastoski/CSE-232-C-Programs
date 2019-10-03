#include<string>
using std::string;
#include<vector>
#include<sstream>
using std::ostringstream;
#include<cmath>

#include<iomanip>
using std::setprecision;
#include<iostream>
using std::fixed;

#include "proj08_ball.h"
#include "proj08_twod.h"


/*
Chris Nastoski
11/3/17
Section 012
Project 08

This Program introduces the basics of classes and structures in c++. It utilizes
them to tackle a fundamental physics problem in gaming and many other physics
intensive projects.This class represents a 2-dimensional ball, and calculates collisions
between two balls or a ball and a wall.


*/


//constructor of a custom ball
Ball::Ball(double m, TwoD pos, TwoD speed, double r){
  mass = m;//mass
  coords = pos;//position
  velocity = speed;//velocity
  radius = r;//radius
}

//converts the ball's dimensions to a string to be printed
string Ball::to_string(){
  ostringstream oss;
  oss<<fixed<<setprecision(2);
  oss<<mass<<", "<<coords.to_string()<<", "
  <<velocity.to_string()<<", "<<radius;

  return oss.str();
}

//returns a boolean pertaining to whether the ball is in contact with another
//ball or not
bool Ball::contact_ball(Ball b2){
  double radii_sum = this->radius +b2.radius;//adds the two radii together
  double distance;
  distance = sqrt(pow(coords.x-b2.coords.x,2)+pow(coords.y-b2.coords.y,2));
  //calculates distance between them
  if(distance<=radii_sum){
    return true;//distance must be greater than radii_sum to not be in contact
  }
  else{
    return false;
  }//of else
}//of function

//returns a boolean pertaining to whether the ball is in contact with a wall
bool Ball::contact_wall(long xdim, long ydim){
    if((coords.x+radius>=xdim) || (coords.y+radius>=ydim)){
      return true;//if ball in in contact with the dimension maximums
    }
    if((coords.x-radius<=0) || (coords.y-radius<=0)){
      return true;//if ball is in contact with dimension minimums
    }
    else{
      return false;
    }

}

//takes in a TwoD vector and updates the velocity of the ball if the ball is in
//contact with a wall
TwoD Ball::update_velocity_wall(long xdim, long ydim){
  TwoD collision_velocity;
  double xvel = velocity.x,yvel = velocity.y;//x and y components of velocity
  if((coords.x+radius>=xdim) || (coords.x-radius<=0)){
    return collision_velocity = {-xvel,yvel};
    //if the ball is in contact with the two sides of the wall, just flip the
    //x co-ordinates
  }
  else if((coords.y+radius>=ydim) || (coords.y-radius<=0)){
    return collision_velocity = {xvel,-yvel};
    //if the ball is in contact with the top or bottom wall, just flips the
    //y co-ordinates
  }

  else{
    return collision_velocity = {xvel,yvel};
    //ball is not in contact with a wall
  }

}

//takes in a twoD vector representing velocity, and returns the change in velocity
//after coming in contact with another ball
//Utilizes the vector function to calculate the change in velocity
TwoD Ball::update_velocity_ball(Ball b){
  TwoD velocity_prime;
  double mass_part = (2*b.mass/(mass+b.mass));//first part of the vector equation
  //2*m2/(m1+m2)
  double dot_part = (velocity.diff(b.velocity)).dot_product(coords.diff(b.coords))
  /(coords.diff(b.coords)).magnitude_squared();
  //(v1-v1)dot(x1-x2)/||x1-x2||^2
  TwoD second_part = (coords.diff(b.coords)).mult(mass_part*dot_part);
  //v2 = (x1-x2)*dot_part*mass_part
  velocity_prime = velocity.diff(second_part);
  //v' = v1 - v2
  return velocity_prime;


}
