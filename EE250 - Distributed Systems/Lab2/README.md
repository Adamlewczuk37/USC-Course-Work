# Lab 2
[Fork](https://docs.github.com/en/get-started/quickstart/fork-a-repo) this repo and clone it to your machine to get started!

## Team Member
- Adam Lewczuk - github: Adamlewczuk37

## Lab Question Answers

Answer for Question 1: 
The reliability made it so that there was a 50% chance of the packet failing to reach the terminal. This occurred because if the system sent a lost packet, UDP would fail to send which would leave a blank space.

Answer for Question 2: 
While the reliability at first was unaffected, each packet was sent at a slower and slower rate until they stopped sending altogether. The reliability remained largely unaffected because TCP was typically able to catch if a packet failed to send and tried to resend it until it showed up on the other end.

Answer for Question 3: 
The speed after the command appeared to have slowed down exponentially. This occurred because if the system failed to send a packet, TCP would check if it actually sent (causing delays) and attempt to resend the packet which backed the system up even more. The more packets being sent which could potentially fail, the more the system got delayed.
