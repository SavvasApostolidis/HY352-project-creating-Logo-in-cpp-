API Definition
==============

### GUI Management

Initializes and sets up the main GUI elements (display, font, images etc.).

```cpp
int init_GUI();
```

Renders the turtle's moves on the GUI.

```cpp
void render_GUI();
```

Tears down the GUI and releases the memory allocated by the GUI elements.

```cpp
int destroy_GUI();
```


### Lifecycle Management

Freezes the execution for `s` seconds.

```cpp
void wait(unsigned s);
```


### Screen Customization

Sets the background color of the screen to the given RGB value.

```cpp
int set_screen_color(unsigned red, unsigned green, unsigned blue);
```


### Pen Handling

Sets the color of the pen to the given RGB value.

```cpp
int set_pen_color(unsigned red, unsigned green, unsigned blue);
```

Sets the thickness of the pen.

```cpp
int set_pen_thickness(float thickness);
```

Raises the pen, so that the turtle won't draw on any future move.

```cpp
void pen_up();
```

Lowers the pen, so that the turtle draws on any future move.

```cpp
void pen_down();
```


### Turtle Instructions

Moves the turtle `n` steps forward in the current direction without altering the turtle's posture.

```cpp
int turtle_mv_forward(float n);
```

Moves the turtle `n` steps backwards in the current direction without altering the turtle's posture.

```cpp
int turtle_mv_backward(float n);
```

Draws a label at the current position of the turtle.

```cpp
int turtle_draw_label(const char* text);
```

Draws a circle with radius `r` centered at `(x,y)`, where `x` and `y` are the current coordinates of the turtle.

Note that `(0,0)` is the top-left corner of the screen.

```cpp
int turtle_draw_circle(unsigned r);
```

Moves the turtle to the given `(x,y)` coordinates.

Note that `(0,0)` is the top-left corner of the screen.

```cpp
int turtle_go_to_position(unsigned x, unsigned y);
```

Moves the turtle to the center of the screen.

```cpp
int turtle_go_to_center();
```

Rotates the turtle by the given number of degrees.

Positive values rotate the turtle clockwise, while negative values rotate the turtle counterclockwise.

```cpp
int turtle_rotate(int degrees);
```


### Debug Information

Displays the given debug message on the screen.

```cpp
int show_debug_message(const char* message);
```


### Helper Macros

Defines the number of pi.

```cpp
PI
```

Converts the given number of degrees to radians.

```cpp
degreesToRadians(angleDegrees)
```

Converts the given number of radians to degrees.

```cpp
radiansToDegrees(angleRadians)
```
