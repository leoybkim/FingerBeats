import sys
sys.path.insert(0, "../lib")
import Leap
from Leap import CircleGesture, KeyTapGesture, ScreenTapGesture, SwipeGesture
from time import time, sleep
from subprocess import call


# Used for initial connection
class SampleListener(Leap.Listener):

    def on_connect(self, controller):
        print "Connected"
        # controller.enable_gesture(Leap.Gesture.TYPE_SWIPE);
        # controller.enable_gesture(Leap.Gesture.TYPE_CIRCLE);
        # controller.enable_gesture(Leap.Gesture.TYPE_KEY_TAP);
        # controller.enable_gesture(Leap.Gesture.TYPE_SCREEN_TAP);

        self.snare = 'snare.wav'
        self.kick = 'kickA.wav'
        self.closed_hi_hat = 'closed-hi-hat.wav'
        self.open_hi_hat = 'open-hi-hat.wav'

    def on_frame(self, controller):
        frame = controller.frame()

        for hand in frame.hands:
            pos = hand.palm_position
            vel = hand.palm_velocity
            id = hand.id
            # print('Pos: ' + str(pos) + ' Vel: ' + str(vel) + ' ID: ' + str(id))
            # print('pos.x: ' + str(pos.x) + ' pos.y: ' + str(pos.y) + ' pos.z: ' + str(pos.z)) # dist dist !dist
            # print('vel.x: ' + str(vel.x) + ' vel.y: ' + str(vel.y) + ' pos.z: ' + str(vel.z))

            # print(hand)
            print ("Frame id: %d, timestamp: %d, hands: %d, fingers: %d, tools: %d, gestures: %d" % (
              frame.id, frame.timestamp, len(frame.hands), len(frame.fingers), len(frame.tools), len(frame.gestures())))

            if vel.x < -150:
                print('kick')
                call(['aplay', self.kick])

            if vel.x > 150:
                print('snare')
                call(['aplay', self.snare])

            if vel.y > 150:
                print('closed hi-hat')
                call(['aplay', self.closed_hi_hat])

            if vel.y < -150:
                print('open hi-hat')
                call(['aplay', self.open_hi_hat])

            sleep(0.1)

def main():
    global screen_size

    listener = SampleListener()
    controller = Leap.Controller()
    controller.add_listener(listener)


    # Keep this process running until Enter is pressed
    print "Press Enter to quit..."
    try:
        # sleep(0.5)
        while True:
            sleep(0.1)

    except KeyboardInterrupt:
        pass
    finally:
        # Remove the sample listener when done
        controller.remove_listener(listener)

if __name__ == "__main__":
    main()
