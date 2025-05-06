/*EXERCISE FOR CHAPTER 3*/


RIPRENDI DALL'ESERCIZIO 3,1 PUNTO 3!

-  Exercise 3.1
1. Given the vectors =2,4 a and =3,5 b , and the scalar value =2 s , calculate the following:
   (a) + a b
   (b) ⋅ s a
   (c) ⋅ ab
2. Given the triangle in Figure 3.16 and the following points:
   =−
   =
   =
   1,1
   2, 4
   3,3
   A
   B
   C
   Calculate the θ using the vector operations discussed in this chapter.
   88
   CHAPTER 3 VECTORS AND BASIC PHYSICS
   Figure 3.16 Triangle for problem 2 of Exercise 3.1
3.
Suppose a 2D game features an arrow that points from the player to the next objective.
When the game first begins, the arrow points down the x-axis
The player’s initial position is at ( )
4,0 .
You create a new object at the position ( )
5,6 .
1, 0 .
a. What is the unit vector from the player’s initial position to the new waypoint?
b. Calculate the angle of rotation between the initial arrow direction and the vector
calculated in part (a).
c. Calculate the vector perpendicular to the plane created by the initial arrow direction
and the vector calculated in part (a).

- Exercise 3.2

Currently, the ship does not collide against asteroids in the chapter game project. Add collision
for the ship. To do so, you first need to create a CollisionComponent in Ship and specify
a radius. Next, in Ship::UpdateActor, you need to test against the collision of all asteroids
(much the way the laser does). If the ship collides with an asteroid, force it to reset in the center
of the screen with a rotation of zero.
As an extra feature, make it so the ship disappears for a second or two after colliding with an
asteroid. The ship should then reappear in the center after this delay.

- Exercise 3.3

Modify MoveComponent so that it uses Newtonian physics. Specifically, change it to have a
mass, a sum of forces, and a velocity as member variables. Then in Update, change the code for
forward movement so it instead calculates an acceleration from the forces, a velocity from the
acceleration, and a position from the velocity.
EXERCISES
89
Then, you need some method to set forces on the component. One approach is to add an
AddForce function that takes in a Vector2 and adds that to the sum of forces variable. You
can additionally clear the sum of forces on every frame after calculating acceleration. This way,
for an impulse you just call AddForce once. And for a constant force, you simply call AddForce
for that force on every frame.
Finally, change InputComponent, Asteroid, and Ship so that they work correctly with this
new MoveComponent that supports Newtonian physics.