# Chaos Game Fractal Generator

A C++ simulation of the **Chaos Game** using the **SFML 3.0** library. This project generates Sierpinski-style fractals by plotting thousands of points based on a set of user-defined vertices and mathematical ratios.

## Features

* **Dynamic Polygon Support:** Generate fractals for triangles, squares, and polygons up to 10 sides.
* **SFML 3.0 Implementation:** Updated syntax for modern SFML, including `sf::VideoMode` updates and `openFromFile` font handling.
* **Interactive UI:**
    * Select number of sides via keyboard (3-9, 0 for 10).
    * Place vertices and seed points using mouse clicks.
    * Real-time point generation (250 points per frame).
* **State Management:** Double-tap `ESC` to stop simulation and return to the main menu.

<img width="559" height="415" alt="Screenshot 2026-05-02 at 5 36 37 PM" src="https://github.com/user-attachments/assets/962b40a9-93cf-47b6-8611-84bb5afc607a" />

## Extra Credit Features

* **Higher-Order Polygons:** Support for Pentagons through Decagons.
* **Mathematical Precision:** Implemented specific ratios for each polygon:
    * **Triangle/Square:** 0.5
    * **Pentagon:** 0.618
    * **Hexagon:** 0.667
    * **Decagon:** 0.764
* **Advanced Constraints:** For polygons with 4 or more sides, the algorithm prevents the same vertex from being chosen twice in a row, ensuring the fractal structure emerges correctly.
* **Dynamic Vertex Shapes:** Vertex markers change their point count to match the selected polygon type (e.g., pentagon vertices appear as pentagons).
* Example (pentagon):

<img width="651" height="457" alt="Screenshot 2026-05-02 at 5 37 05 PM" src="https://github.com/user-attachments/assets/66d23940-cbb3-479d-aca2-0d579b7ba0fb" />

## How to Build and Run

### Prerequisites
* MacOS (I used this!) or Linux
* SFML 3.0+ installed (`brew install sfml` on Mac)
* `g++` compiler and `make`
