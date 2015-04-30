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
static int const geophone2=4; //23
static int const geophone3=6; //25
std::chrono::high_resolution_clock::time_point t1, t2, t3;
bool I1,I2,I3;
int loops1,loops2,loops3;
double d = .3;
double v = 110.37;
static int TIMES_TO_LEARN = 5;
static std::string dataFile = "ranges.txt";
	
	class MapPoint {
	
	double maxT1, maxT2, maxT3, minT1, minT2, minT3;
	std::string name;
	
	public:MapPoint(std::string name) {
		this->name = name;
		maxT1 = 0;
		maxT2 = 0;
		maxT3 = 0;
		minT1 = 0;
		minT2 = 0;
		minT3 = 0;
	}
	
	public:void updateTime(double t1, double t2, double t3) {
		if (maxT1 == 0) {
			maxT1 = t1;
			maxT2 = t2;
			maxT3 = t3;
			minT1 = t1;
			minT2 = t2;
			minT3 = t3;
		}
		else {
			if (t1 > maxT1) {
				maxT1 = t1;
			}
			if (t1 < minT1) {
				minT1 = t1;
			}
			if (t2 > maxT2) {
				maxT2 = t2;
			}
			if (t2 < minT2) {
				minT2 = t2;
			}
			if (t3 > maxT3) {
				maxT3 = t3;
			}
			if (t3 < minT3) {
				minT3 = t3;
			}		
		}
	}

	public:bool checkTimes(double t1, double t2, double t3) {
		bool fit1=false;
		bool fit2=false;
		bool fit3=false;
		if (t1 >= minT1 && t1 <= maxT1) {
			std::cout << "T1 Match " << name << std::endl;
			fit1 = true;
		}
		if (t2 >= minT2 && t2 <= maxT2) {
			std::cout << "T2 Match " << name << std::endl;
			fit2 = true;
		}
		if (t3 >= minT3 && t3 <= maxT3) {
			std::cout << "T3 Match " << name << std::endl;
			fit3 = true;
		}
		if (fit1 && fit2 && fit3) {
			return true;
		}
		return false;
	}
	
	public:void printValues() {
		std::cout << minT1 << " " << maxT1 << std::endl;
		std::cout << minT2 << " " << maxT2 << std::endl;
		std::cout << minT3 << " " << maxT3 << std::endl;
	}

	public:std::string getName() {
		return name;
	}

	public:void writeFile() {
		std::ofstream tofile;
		tofile.open(dataFile, std::ios::app);
		tofile << name << "\n";
		tofile << minT1 << "\n";
		tofile << maxT1 << "\n";
		tofile << minT2 << "\n";
		tofile << maxT2 << "\n";
		tofile << minT3 << "\n";
		tofile << maxT3 << "\n";
		tofile.close();
	}

	public:void readFile() {
		std::ifstream fromfile;
		fromfile.open(dataFile);
		std::string line;
		while (line != name) std::getline(fromfile,line);
		fromfile >> minT1 >> maxT1 >> minT2 >> maxT2 >> minT3 >> maxT3;
		fromfile.close();
	}
<<<<<<< HEAD
};
=======
}
>>>>>>> 5f43d6ddc43c8c9f8cb6e5075416df205425c039
 
        void storeTime1() {
                t1 = std::chrono::high_resolution_clock::now();
                I1=true;
        }
 
        void storeTime2() {
                t2 = std::chrono::high_resolution_clock::now();
                I2=true;
        }
       
        void storeTime3() {
                t3 = std::chrono::high_resolution_clock::now();
                I3=true;
        }
	
	void playSound(std::string s){
		if(s == "Harder"){
<<<<<<< HEAD
			system("sudo omxplayer -o local /home/pi/SeniorDesign/tmp/ECE449/Bell1.mp3 &> /dev/null");
			std::cout <<"Harder";
		}
		if(s == "Better"){
			system("sudo omxplayer -o local /home/pi/SeniorDesign/tmp/ECE449/Bell2.mp3 &> /dev/null");
			std::cout <<"Better";
		}
		if(s == "Faster"){
			system("sudo omxplayer -o local /home/pi/SeniorDesign/tmp/ECE449/Bell3.mp3 &> /dev/null");
			std::cout <<"Faster";
		}
		if(s == "Stronger"){
			system("sudo omxplayer -o local /home/pi/SeniorDesign/tmp/ECE449/Bell4.mp3 &> /dev/null");
=======
			system("sudo mpg321 --stereo -q /home/pi/SeniorDesign/tmp/ECE449/Bell1.mp3");
			std::cout <<"Harder";
		}
		if(s == "Better"){
			system("sudo mpg321 --stereo -q /home/pi/SeniorDesign/tmp/ECE449/Bell2.mp3");
			std::cout <<"Better";
		}
		if(s == "Faster"){
			system("sudo mpg321 --stereo -q /home/pi/SeniorDesign/tmp/ECE449/Bell3.mp3");
			std::cout <<"Faster";
		}
		if(s == "Stronger"){
			system("sudo mpg321 --stereo -q /home/pi/SeniorDesign/tmp/ECE449/Bell4.mp3");
>>>>>>> 5f43d6ddc43c8c9f8cb6e5075416df205425c039
			std::cout <<"Stronger";
		}
	}
 
        PI_THREAD (IT) {
		wiringPiISR(geophone1, INT_EDGE_RISING, storeTime1);
        };
 
        PI_THREAD (IT2) {
                wiringPiISR(geophone2, INT_EDGE_RISING, storeTime2);
        };
 
        PI_THREAD (IT3) {
                wiringPiISR(geophone3, INT_EDGE_RISING, storeTime3);
        };
 
        int main(int argc, const char* argv[]) {
        std::string response;
        std::string pausePoint;
		bool load = false;
		wiringPiSetup();
		pullUpDnControl(geophone1, PUD_DOWN);
		pullUpDnControl(geophone2, PUD_DOWN);
		pullUpDnControl(geophone3, PUD_DOWN);
		std::vector<MapPoint> locs;
		locs.push_back(MapPoint("Harder"));
		locs.push_back(MapPoint("Better"));
		locs.push_back(MapPoint("Faster"));
		locs.push_back(MapPoint("Stronger"));
		std::cout << "Read from file ? y/n :";
		std::cin >> response;
		if (response == "y") {
			load = true;
		}
                for (MapPoint &m : locs) {
			if (!load) {
				for (int i=0; i<TIMES_TO_LEARN; i++) {
					std::cout << "Currently waiting for: " << m.getName() << std::endl;
					std::cout << "Press Enter to continue" << std::endl;
					std::cin >> pausePoint;
					I1=false;
                	I2=false;
                	I3=false;
                	piThreadCreate(IT);
                	piThreadCreate(IT2);
                	piThreadCreate(IT3);
					wiringPiISR(geophone1, INT_EDGE_RISING, storeTime1);
					wiringPiISR(geophone2, INT_EDGE_RISING, storeTime2);
					wiringPiISR(geophone3, INT_EDGE_RISING, storeTime3);               
                	while (I1!=true || I2 != true || I3 != true) {
                        
                	}
 
                	auto nanos = std::chrono::duration_cast<std::chrono::nanoseconds>(t1 - t2);
 			 		auto nanos2 = std::chrono::duration_cast<std::chrono::nanoseconds>(t1 - t3);
					auto nanos3 = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t3);
                	double time1 = (double)nanos.count()/(double)1000000000;
					double time2 = (double)nanos2.count()/(double)1000000000;
					double time3 = (double)nanos3.count()/(double)1000000000;
					m.updateTime(time1, time2, time3);
					std::cout << time1 << " " << time2 << " " << time3 << std::endl;
					std::this_thread::sleep_for(std::chrono::milliseconds(500));
				}
			//m.writeFile();
			//int x;
			//std::cout << "Enter new File name";
			//std::cin >> x;
			}
			if (load) m.readFile();
			m.printValues();
		}
		while (true) {
			I1=false;
            I2=false;
            I3=false;
            loops1=0;
			loops2=0;
			loops3=0;
			piThreadCreate(IT);
            piThreadCreate(IT2);
            piThreadCreate(IT3);               
			wiringPiISR(geophone1, INT_EDGE_RISING, storeTime1);
			wiringPiISR(geophone2, INT_EDGE_RISING, storeTime2);
			wiringPiISR(geophone3, INT_EDGE_RISING, storeTime3);
            while (I1!=true || I2 != true || I3 != true) {
            	std::this_thread::sleep_for(std::chrono::milliseconds(100)); 
               	if (I1 == true) loops1++;
				if (I2 == true) loops2++;
				if (I3 == true) loops3++;
				if (loops1 > 10 || loops2 > 10 || loops3 > 10) break;
			}
            auto nanos = std::chrono::duration_cast<std::chrono::nanoseconds>(t1 - t2);
 			auto nanos2 = std::chrono::duration_cast<std::chrono::nanoseconds>(t1 - t3);
			auto nanos3 = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t3);
            double time1 = (double)nanos.count()/(double)1000000000;
			double time2 = (double)nanos2.count()/(double)1000000000;
			double time3 = (double)nanos3.count()/(double)1000000000;
			for (MapPoint m : locs) {
				if(m.checkTimes(time1, time2, time3)) std::thread(playSound, m.getName()).detach();
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
		}
	}
