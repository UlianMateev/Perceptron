#include"funcs.h"

using std::vector;

//constants that can be modified as desired
#define HEIGHT 20  
#define WIDTH 20
#define SCALER 1
#define BIAS 10
#define SAMPLES 350 
#define TRAINING 800


int main()
{
    int train;
    int k = 0;
    char res;
    bool run;

    vector<vector<float>> grid(HEIGHT * SCALER, vector<float>(WIDTH * SCALER, 0.0f));
    vector<vector<float>> weights(HEIGHT * SCALER, vector<float>(WIDTH * SCALER, 0.0f));

    //Loop that trains the perceptron over and over again on the same randomly generared data
    for (int i = 0; i < TRAINING; i++) {

        train = Train(grid, weights);
        save_as_ppm(weights);
        if (train == 0) {
            k++;
            if (k == 10) {
                break;
            }
        }
    }
    //Ask the perceptron if you want
    std::cout << "Training finishted. Try the perceptron? (YES = y ; NO = n):";
    std::cin >> res;

    if (res == 'n') {
        exit(0);
    }
    else {
        system("cls");
        run = true;
    }

    int guess = 0;
    int wrong = 0;
    int right = 0;

    srand(69);

    //in this loop you can generate shapes for the perceptron to guess
    while (run) {

        std::cout << "What shape do you want the perceptron to guess? (RECTANGLE = r ; CIRCLE = c):";
        std::cin >> res;

        GridReset(grid);

        if (res == 'r') {

            guess++;
            RandomRect(grid);
            save_as_ppm(grid);

            if (forward(grid, weights) < BIAS) {

                std::cout << "Perceptron: It's a rectangle!\n";
                std::cout << "[INFO] CORRECT\n";
                right++;
            }
            else {

                std::cout << "Perceptron: It's a circle!\n";
                std::cout << "[INFO] WRONG\n";
                wrong++;
            }
            system("pause");
        }

        system("cls");

        if (res == 'c') {

            guess++;
            RandomCircle(grid);
            save_as_ppm(grid);

            if (forward(grid, weights) > BIAS) {

                std::cout << "Perceptron: It's a circle!\n";
                std::cout << "[INFO] CORRECT\n";
                right++;
            }
            else {

                std::cout << "Perceptron: It's a rectangle!\n";
                std::cout << "[INFO] WRONG\n";
                wrong++;
            }
            system("pause");
        }

        float p = GuessPercent(guess, wrong);

//Displaying how much times you have asked him and how many right and wrong guesses it had ass well as the percentage of them
        std::cout << "Guess #" << guess << " wrong #" << wrong << " right #" << right << std::endl;
        std::cout << "Perceptron is right: " << 100 - p << "%  " << p << "% wrong of the time" << std::endl;

        save_as_ppm(weights);

        system("pause");
        system("cls");
    }

    system("pause");
	return 0;
}