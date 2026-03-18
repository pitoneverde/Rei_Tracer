#!/usr/bin/env python3
import random
import sys

def random_float(low, high):
    return random.uniform(low, high)

def random_int(low, high):
    return random.randint(low, high)

def main():
    if len(sys.argv) != 2:
        print(f"Usage: {sys.argv[0]} <number_of_spheres>")
        sys.exit(1)
    
    n = int(sys.argv[1])
    # Seed for reproducibility (optional)
    random.seed(42)
    
    # print("# Randomly generated spheres")
    for _ in range(n):
        x = random_float(-20.0, 20.0)
        y = random_float(-20.0, 20.0)
        z = random_float(-20.0, 20.0)
        diameter = random_float(1.0, 10.0)
        r = random_int(0, 255)
        g = random_int(0, 255)
        b = random_int(0, 255)
        print(f"sp {x:.2f},{y:.2f},{z:.2f} {diameter:.2f} {r},{g},{b}")

if __name__ == "__main__":
    main()