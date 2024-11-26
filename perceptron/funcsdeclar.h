#pragma once
#include<vector>
using std::vector;

//function that the resets the values of the grid (no pixels drawn)
void GridReset(vector<vector<float>>& grid);

//function that displays the grid with coresponding numbers for pixels
void GridDisplay(vector<vector<float>>& grid);

//function that draws the rectangle
void RectDraw(vector<vector<float>>& grid, int rx, int ry, int w, int h);

//function that draws a random rectangle
void RandomRect(vector<vector<float>>& grid); 

//function that draws the circle
void CircDraw(vector<vector<float>>& grid, int cx, int cy, int r);

//function that draws a random circle
void RandomCircle(vector<vector<float>>& grid);

//forward method 
float forward(vector<vector<float>>& grid, vector<vector<float>>& weights);

//addition of weights if the perceptron does not activate the neuron when it should 
void AddWeights(vector<vector<float>>& grid, vector<vector<float>>& weights);

//subtraction of weights if the perceptron activates the neuron when it should not
void SubtractWeights(vector<vector<float>>& grid, vector<vector<float>>& weights);

//function that trains the network as many times as wanted
int Train(vector<vector<float>>& grid, vector<vector<float>>& weights);

//function that calculates the percentage of right and correct guesses after training
float GuessPercent(int guess, int wrong);

//function that saves images that show the shapes or the weights(shows how it is learning)
void save_as_ppm(vector<vector<float>>& input);