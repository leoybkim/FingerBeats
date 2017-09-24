from firebase import firebase
import os

FIREBASE_URL = "https://fingerbeats-a2bf3.firebaseio.com/"

# Main
if __name__ == '__main__':
    fb = firebase.FirebaseApplication(FIREBASE_URL, None) # Create a reference to the Firebase Application

    while 1:
        result = fb.get('', "input") # Get data from firebase
        print(result)
        F = open("test.txt", 'w')
        F.write(str(result))
        F.close()