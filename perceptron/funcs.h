#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include<cmath>

using std::vector;
 
#define HEIGHT 20
#define WIDTH 20
#define SCALER 1
#define BIAS 10
#define SAMPLES 350 
#define TRAINING 800

typedef vector<vector<float>> VVf;
  
const std::string filename = "NN.ppm";

void GridReset(vector<vector<float>>& grid) {

    for (int y = 0; y < HEIGHT * SCALER; y++) {
        for (int x = 0; x < WIDTH * SCALER; x++) {
            grid[y][x] = 0.0f;
        }
    }
}


void GridDisplay(vector<vector<float>>& grid) {

    std::cout << "\n\nNew grid\n";

    for (int y = 0; y < HEIGHT * SCALER; y++) {
        for (int x = 0; x < WIDTH * SCALER; x++) {
            std::cout << grid[y][x] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}


void RectDraw(vector<vector<float>>& grid, int rx, int ry, int w, int h) {
   
    for (int i = ry; i < ry + h && i < HEIGHT * SCALER; i++) {
        for (int j = rx; j < rx + w && j < WIDTH * SCALER; j++) {
            if (i >= 0 && j >= 0) {
                grid[i][j] = 1.0f;  

            }
        }
    }
}


void RandomRect(vector<vector<float>>& grid) {

    int x, y, w, h;

    GridReset(grid);

    x = rand() % ((WIDTH * SCALER) - 1);
    y = rand() % ((HEIGHT * SCALER) - 1);
    w = 2 + rand() % ((WIDTH * SCALER) - x);
    h = 2 + rand() % ((HEIGHT * SCALER) - y);

    RectDraw(grid, x, y, w, h);
}


void CircDraw(vector<vector<float>>& grid, int cx, int cy, int r) {

    for (int y = cy - r; y <= cy + r; y++) {
        for (int x = cx - r; x <= cx + r; x++) {

            int dx = x - cx;
            int dy = y - cy;

            if (dx * dx + dy * dy <= r * r) { 

                if (y >= 0 && y < HEIGHT * SCALER && x >= 0 && x < WIDTH * SCALER) {
                    grid[y][x] = 1.0f;
                     
                }
            }
        }
    }
}


void RandomCircle(vector<vector<float>>& grid) {

    int r, cy, cx;

    GridReset(grid);

    r = rand() % (WIDTH / 4);
    if (r < 2) r = 1;
    cx = rand() % ((WIDTH * SCALER) - r * 2) + r;
    cy = rand() % ((HEIGHT * SCALER) - r * 2) + r;

    CircDraw(grid, cx, cy, r);
}


float forward(vector<vector<float>>& grid, vector<vector<float>>& weights) {

    float output = 0.0f;

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            output += grid[y][x] * weights[y][x];
        }
    }

    return output;
}


void AddWeights(vector<vector<float>>& grid, vector<vector<float>>& weights) {

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            weights[y][x] += grid[y][x];
        }
    }
}


void SubtractWeights(vector<vector<float>>& grid, vector<vector<float>>& weights) {

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            weights[y][x] -= grid[y][x];
        }
    }
}


int Train(vector<vector<float>>& grid, vector<vector<float>>& weights) {

    int adj = 0;

    srand(69);

    for (int i = 0; i < SAMPLES; i++) { //generates samples and at the end of the loop it generates the same samples
        
        RandomRect(grid);

        if (forward(grid, weights) > BIAS) {

            SubtractWeights(grid, weights);
            adj++;
        }

        RandomCircle(grid);

        if (forward(grid, weights) < BIAS) {

            AddWeights(grid, weights);
            adj++;
        }
    }

    std::cout << "Adjusted " << adj << " times\n";

    return adj;
}


float GuessPercent(int guess, int wrong) {

    float x = 0.0f; 

    return x = (100 * wrong) / guess; 
}


void save_as_ppm(vector<vector<float>>& input) {
 
    float min = std::numeric_limits<float>::max();
    float max = std::numeric_limits<float>::min();

    for (int y = 0; y < HEIGHT * SCALER; y++) {
        for (int x = 0; x < WIDTH * SCALER; x++) { 

            if (input[y][x] < min) min = input[y][x];
            if (input[y][x] > max) max = input[y][x];
        }
    }

    std::ofstream outputFile(filename, std::ios::binary);

    if (outputFile.is_open()) {
         
        outputFile << "P6\n";
        outputFile << WIDTH * SCALER << " " << HEIGHT * SCALER << "\n";
        outputFile << "255\n";


        for (int y = 0; y < HEIGHT * SCALER; ++y) {
            for (int x = 0; x < WIDTH * SCALER; ++x) {

                float s = (input[y][x] - min) / (max - min);

                unsigned char pixel[3] = {
                    static_cast<unsigned char>(floorf(255 * (1.0f - s))),
                    static_cast<unsigned char>(floorf(s * 255)),
                    0   
                };

                outputFile.write(reinterpret_cast<char*>(pixel), 3);
            }
        }

        outputFile.close();
    }
}
