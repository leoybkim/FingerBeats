#include <iostream>
#include <string.h>
#include "../lib/Leap.h"
#include <thread>
#include <unistd.h>
#include <errno.h>
#include <fstream>

using namespace Leap;

const std::string stateNames[] = {"STATE_INVALID", "STATE_START", "STATE_UPDATE", "STATE_END"};
const std::string beatNames[] = {"closed-hi-hat", "kickA", "kickB", "open-hi-hat", "snare",
                                 "AWESOME", "BOING_", "CALC", "CALC2", "CASH_REG", "CONICAL",
                                 "SPRING_B", "TINK", "TWINGY", "UPPER", "VICTORY", "WATER_GL"
                                };
const int SWIPE_MAX = 14;
const int CIR_MAX = 32;
const int BEAT_SIZE = 17;

int beat_index = -1;
int swipe_ctr = 0;
int cir_ctr = 0;

// default beats
int cir_beat = 3;
int swipe_beat = 4;
int tap_beat = 0;

void sound(int index) {
    
    int pid = fork();
    if (pid == 0) {
        std::string file = "../wav/" + beatNames[index] + ".wav";
        execlp("afplay", "afplay", file.c_str(), NULL);
        std::cout << "Exec failed: " << strerror(errno) << std::endl;
        exit(-1);
    } else {
        wait(&pid);
    }
}

class SampleListener : public Listener {
    public:
    virtual void onConnect(const Controller&);
    virtual void onFrame(const Controller&);
};

void SampleListener::onConnect(const Controller& controller) {
    controller.enableGesture(Gesture::TYPE_CIRCLE);
    controller.enableGesture(Gesture::TYPE_KEY_TAP);
    //controller.enableGesture(Gesture::TYPE_SCREEN_TAP);
    controller.enableGesture(Gesture::TYPE_SWIPE);
}

void SampleListener::onFrame(const Controller& controller) {

    beat_index = -1; // initialize it to unvalid value
    Frame frame = controller.frame();

    // Get gestures
    const GestureList gestures = frame.gestures();
    for (int g = 0; g < gestures.count(); ++g) {
    Gesture gesture = gestures[g];

    switch (gesture.type()) {
      case Gesture::TYPE_CIRCLE:
      {

        cir_ctr++;
        if (cir_ctr == 3) {
            beat_index = cir_beat;
        } else if (cir_ctr > CIR_MAX) {
            cir_ctr = 0;
        }
        /*
        CircleGesture circle = gesture;
        std::string clockwiseness;

        if (circle.pointable().direction().angleTo(circle.normal()) <= PI/2) {
          clockwiseness = "clockwise";
        } else {
          clockwiseness = "counterclockwise";
        }

        
        // Calculate angle swept since last frame
        float sweptAngle = 0;
        if (circle.state() != Gesture::STATE_START) {
          CircleGesture previousUpdate = CircleGesture(controller.frame(1).gesture(circle.id()));
          sweptAngle = (circle.progress() - previousUpdate.progress()) * 2 * PI;
        }
        std::cout << std::string(2, ' ')
                  << "Circle id: " << gesture.id()
                  << ", state: " << stateNames[gesture.state()]
                  << ", progress: " << circle.progress()
                  << ", radius: " << circle.radius()
                  << ", angle " << sweptAngle * RAD_TO_DEG
                  <<  ", " << clockwiseness << std::endl;
        */
        break;
      }
      case Gesture::TYPE_SWIPE:
      {
        
        swipe_ctr++;
        if (swipe_ctr == 1) {
            beat_index = swipe_beat;
        } else if (swipe_ctr > SWIPE_MAX) {
            swipe_ctr = 0;
        }
        /*
        SwipeGesture swipe = gesture;
        std::cout << std::string(2, ' ')
          << "Swipe id: " << gesture.id()
          << ", state: " << stateNames[gesture.state()]
          << ", direction: " << swipe.direction()
          << ", speed: " << swipe.speed() << std::endl;
        */
        break;
      }
      case Gesture::TYPE_KEY_TAP:
      {
        beat_index = tap_beat;
        /*
        KeyTapGesture tap = gesture;
        std::cout << std::string(2, ' ')
          << "Key Tap id: " << gesture.id()
          << ", state: " << stateNames[gesture.state()]
          << ", position: " << tap.position()
          << ", direction: " << tap.direction()<< std::endl;
        */
        break;
      }
      case Gesture::TYPE_SCREEN_TAP:
      {
        /*
        ScreenTapGesture screentap = gesture;
        std::cout << std::string(2, ' ')
          << "Screen Tap id: " << gesture.id()
          << ", state: " << stateNames[gesture.state()]
          << ", position: " << screentap.position()
          << ", direction: " << screentap.direction()<< std::endl;
        */
        break;
      }
      default:
        std::cout << std::string(2, ' ')  << "Unknown gesture type." << std::endl;
        break;
    }
    if (beat_index != -1) {
        std::thread s1(sound, beat_index);
        s1.detach();
    }
  }
}

void menu () {
    std::cout << "menu" << std::endl;
    std::cout << "options:" << std::endl;
    std::cout << "1 for recording 10 seconds" << std::endl;
    std::cout << "2 for replay latest beats" << std::endl;
    std::cout << "3 for a magic merge" << std::endl;
    std::cout << "4 for playing the merged beats" << std::endl;
    std::cout << "5 choose your own beats options!" << std::endl;
    std::cout << "-1 for exit" << std::endl; 
}

int main (int argc, char** argv) {
    int response = 0;
    int file_ctr = 0;

    SampleListener lisenter;
    Controller controller;

    while (1) {
        std::string file_pre = "../wav/beats";
        std::string file_name = "";
        std::string record_cmd = "sox -b 32 -e unsigned-integer -r 96k -c 2 -d --clobber --buffer $((96000*2*10)) ";
        std::string play_cmd = "play ";
        std::string mix_cmd = "sox --combine mix";

        //menu();
        //std::cin >> response;

        std::ifstream inFile;
        inFile.open("/Users/chenyihan/Desktop/FingerBeats/src/test.txt");
        if (!inFile) response = -2;

        inFile >> response;

        if (response == 1) {

            file_ctr++;

            file_name = file_pre + (char) (file_ctr + '0') + ".wav";
            controller.addListener(lisenter);
            record_cmd += file_name + " trim 0 10";

            // record for 10 secs
            system(record_cmd.c_str());
            controller.removeListener(lisenter);

        } else if (response == 2) {
            file_name = file_pre + (char) (file_ctr + '0') + ".wav";
            play_cmd += file_name; 
            system(play_cmd.c_str());
        } else if (response == 3) {
            if (file_ctr > 1) {
                for (int i = 1; i <= file_ctr; i++) {
                    mix_cmd += " " + file_pre + (char)('0' + i) + ".wav";
                }
                mix_cmd += " ../wav/mixed.wav";
                std::cout << mix_cmd << std::endl;
                system(mix_cmd.c_str());
            } else {
                std::cout << ">1 file needed" <<std::endl;
            }
        } else if (response == 4) {
            play_cmd += "../wav/mixed.wav";
            for (int i = 0; i < 3; i++) {
                system(play_cmd.c_str());
            }
        } else if (response == 5) {
            while (1) {
                play_cmd = "play ";
                for (int i = 0; i < BEAT_SIZE; i++) {
                    std::cout << i << ": " << beatNames[i] << std::endl;
                }
                std::cout << "explore the sound by type index! (enter -1 to go next)" << std::endl;
                int choice;
                std::cin >> choice; // doesn't provide error handling - just assume users are smart
                if (choice == -1) {
                    break;
                }
                play_cmd += "../wav/" + beatNames[choice] + ".wav";
                system(play_cmd.c_str());
            }

            std::cout << "beat for circular motion: ";
            std::cin >> cir_beat;

            std::cout << "beat for swipe motion: ";
            std::cin >> swipe_beat;

            std::cout << "beat for tap motion: ";
            std::cin >> tap_beat;
        }
        else if (response == -2) {
            // blind: do nothing
        } else {
            std::cout << "invalide input" << std::endl; 
            break;
        }
        inFile.close();
    }
    std::cout << "Thanks for using!" << std::endl;

    return 0;
}