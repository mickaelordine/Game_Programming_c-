*Exercise 5.1* <br>

Modify the background clear color so that it smoothly changes between colors. For example,
starting from black, smoothly change over several seconds to blue. Then select another color
(such as red) and smoothly change over several seconds to this other color. Think about how
you can use deltaTime in Game::Update to facilitate this smooth transition.

Solution:
- for the exercise 1 I applied a solution that calculate the difference between the current color and the target color, 
util the start color differ from the traget color we continue to add or subtract a small amount of value to the rgba values until
it reach it, when it reach all the target variables, we change the currentIndex for the vector and we start pointing to another target.


*Exercise 5.2* <br>
Modify the sprite vertices so that each vertex also has an RGB color associated with it. This is
known as a vertex color. Update the vertex shader to take the vertex color as an input and
pass it to the fragment shader. Then change the fragment shader so that rather than simply
drawing the color sampled from the texture, it averages the color between the vertex color
and texture color.

Solution:
- for the exercise 2 I 