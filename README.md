## Inspiration
Wouldn't it be great to pull out a *Ba Dum Tss* after a great pun you just made? What about the times your favourite tune is playing on radio? We thought it would be a fun project to build a mini air drum that we can whip out anytime to show off our rhythmicality.
<img src='https://i.imgur.com/zyKUmiz.gif' title='User Interface' width='' alt='User Interface' />

## What it does
*Finger Beats* uses Leap Motion, a USB peripheral device that can read average of 60 frames per seconds to calculate and track the motions of our fingers and hand gestures. Using the technology we were able to simulate common hand drumming motions to play our virtual air drum. Not only can you record your performance but you can also give a looper effect to mix and merge your recordings with multiple layer of samples.
<img src='https://i.imgur.com/VM0T8sw.gif' title='Leap Motion Visualizer' width='' alt='Video Leap Motion Visualizer' />

## How we built it
Our back-end stack is built with Python and C++ to integrate the Leap Motion SDK. Musicians can see the user interface built on JavaScript framework and control the drum, and the commands are communicated via Firebase.

## Challenges we ran into
It took us several tries to find the best testing environment using the Leap Motion. For instance, the Python API was significantly slower than that of C++. Many of the JS web libraries were out of date, causing unexpected behaviours on the DOM. It was one of the biggest let down since we wished to use the sensor from top to bottom in order to control our application but was faced with this difficulty.

## Accomplishments that we're proud of
As the project progressed we were faced with some faults in our ideas or unexpected technical challenges. However, we didn't give up the project entirely and pivoted our ideas as we moved on to bring the maximum potential. Being a team of only two, we also lacked some brain power compared to other groups, but we both felt that we had a strong teamwork to make it up.

## What we learned
We both got our hands dirty while trying some hacks to make things work within our time limit. One of few include some shady way of threading in our C++ back-end to override the Mac OSX's thread-safe environment. Few hours were "wasted" on debugging the LeapJS library that never got the see the light of day. But none the less, those hours spent taught us valuable lessons.

## What's next for Finger Beats
It would be nice to fully automate the process from start to end using the Leap Motion controller, and refine algorithms to read more customized hand gestures.
