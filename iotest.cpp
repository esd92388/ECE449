#include <chrono>
#include <iostream>
#include <cstdlib>
#include <thread>
#include <math.h>
#include <vector>
#include <fstream>
extern "C" {
#include <wiringPi.h>
}
 
static int const geophone1=1; //18
static int const geophone2=3; //27
static int const geophone3=6; //25
std::chrono::high_resolution_clock::time_point t1, t2, t3;
bool I1,I2,I3;
int loops1,loops2,loops3;
double d = .3;
double v = 110.37;
static int TIMES_TO_LEARN = 5;
static std::string dataFile = "ranges.txt";

int main(int argc, const char* argv[]) {
               
		wiringPiSetup()
		pullUpDnControl(geophone1, PUD_DOWN);
		pullUpDnControl(geophone2, PUD_DOWN);
		pullUpDnControl(geophone3, PUD_DOWN); 
		std::cout << "This is an IO Test press button to verify IO port:";    
		if 
               
        }
