import sys
import matplotlib.pyplot as plt
import matplotlib.patches as patches

def create_image(n, blocks, positions, title):
    # Create a figure and axis for plotting
    fig, ax = plt.subplots()

    # Add blocks to the plot
    for i in range(n):
        width, height = blocks[i]
        x, y = positions[i]
        rect = patches.Rectangle((x, y), width, height, linewidth=1, edgecolor='black', facecolor='blue', alpha=0.5)
        ax.add_patch(rect)

    # Set the limits of the plot
    ax.set_xlim(0, max(pos[0] + blk[0] for pos, blk in zip(positions, blocks)) + 10)
    ax.set_ylim(0, max(pos[1] + blk[1] for pos, blk in zip(positions, blocks)) + 10)
    ax.set_aspect('equal')

    # Show the grid for better visualization
    ax.grid(visible=True, linestyle='--', linewidth=0.5)

    # Set the title
    ax.set_title(title)

    # Display the image
    plt.show()

def parse_input(input_data):
    blocks = []
    positions = []
    reading_blocks = False
    reading_positions = False
    genetic_blocks = []
    genetic_positions = []

    for line in input_data:
        if line.startswith("Dimensions:"):
            reading_blocks = True
            reading_positions = False
            continue
        elif line.startswith("Coordinates:"):
            reading_blocks = False
            reading_positions = True
            continue
        elif line.startswith("With Genetic Algorithm:"):
            break

        if reading_blocks:
            width, height = map(int, line.split())
            blocks.append((width, height))
        elif reading_positions:
            x, y = map(int, line.split())
            positions.append((x, y))

    reading_blocks = False
    reading_positions = False

    for line in input_data[input_data.index("With Genetic Algorithm:"):]:
        if line.startswith("Dimensions:"):
            reading_blocks = True
            reading_positions = False
            continue
        elif line.startswith("Coordinates:"):
            reading_blocks = False
            reading_positions = True
            continue

        if reading_blocks:
            width, height = map(int, line.split())
            genetic_blocks.append((width, height))
        elif reading_positions:
            x, y = map(int, line.split())
            genetic_positions.append((x, y))

    return blocks, positions, genetic_blocks, genetic_positions

def main():
    # Read input file
    input_files = [
        "resultado/ami33.yal.txt",
        "resultado/ami49.yal.txt",
        "resultado/apte.yal.txt",
        "resultado/hp.yal.txt",
        "resultado/xerox.yal.txt"
    ]
    
    for input_file in input_files:
        with open(input_file, 'r') as file:
            input_data = file.read().splitlines()

        blocks, positions, genetic_blocks, genetic_positions = parse_input(input_data)
        n = len(blocks)
        genetic_n = len(genetic_blocks)
        print(n)

        # Create the images
        create_image(n, blocks, positions, "Without Genetic Algorithm")
        create_image(genetic_n, genetic_blocks, genetic_positions, "With Genetic Algorithm")

if __name__ == "__main__":
    main()