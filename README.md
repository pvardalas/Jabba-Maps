# Travelling Salesman Problem


### Author

- **Panagiotis Vardalas**

## Overview

This C program calculates the optimal route between cities based on data provided in a text file.

## Usage

```sh
gcc -o jabbamaps jabbamaps.c
./jabbamaps <file>
```

Where:

- ``<file>``: A text file containing city connections in the format ``CityA-CityB: Distance``.

## Example:

### Given a file routes.txt with the following content:
```yml
CityA-CityB: 50
CityA-CityC: 70
CityA-CityD: 55
CityB-CityC: 60
CityB-CityD: 75
CityC-CityD: 40
```
### Run the program:

```sh
./jabbamaps routes.txt
```

### Output:

The program calculates the minimum distance required to visit all cities once and outputs the route. For the example above:
```sh
We will visit the cities in the following order:
CityA -(55)-> CityB -(40)-> CityC -(60)-> CityD
Total cost: 150
```
## How It Works

- **Input Parsing:** Reads city connection data from the specified file.
- **Optimal Route Calculation:** Utilizes a brute-force with backtracking method to evaluate all possible routes. This ensures that each city is visited exactly once and then calculates the total distance for each route and identifies the one with the minimum distance.
