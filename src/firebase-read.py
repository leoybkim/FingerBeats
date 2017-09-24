from firebase import firebase
import os

FIREBASE_URL = "https://fingerbeats-a2bf3.firebaseio.com/"

# Main
if __name__ == '__main__':
    fb = firebase.FirebaseApplication(FIREBASE_URL, None) # Create a reference to the Firebase Application

    result = fb.get('', 'input') # Get data from firebase
    if result is None:
        F = open("test.txt", 'w')
        F.write(str(-2))         # error signal for Cpp
        F.close()
    else :
        for k in result.keys():
            F = open("test.txt", 'w')
            F.write(str(result[k]['option']))
            F.close()
            try:
                fb.delete(str('/input/'+k), 'option')
            except:
                print('Error occured while updating firebase')
