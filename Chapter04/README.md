 Exercise 4.1 <br>
 Given this chapter’s game project code, update either the Enemy or Tower class (or both!) to 
use an AI state machine. First, consider which behaviors the AI should have and design the state 
machine graph. Next, use the provided AIComponent and AIState base classes to implement 
these behaviors.

Solution: <br>
Enemy -> for the enemy i have implement 3 states <br>
1. Moving
2. Turbo
3. Rest

if the plane pass on turbo mode after a random amount of time than need to rest a little bit.

Turret -> for the turret i have implement 4 states <br>
1. idle
2. shoot
3. overdrive
4. reload

when a turret shoot there is a little percent of change that it pass on overdrive mode and shoot a lot amount of bullet,
when the ammo are finished it needs to reload for a shot time