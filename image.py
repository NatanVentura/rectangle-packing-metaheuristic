import sys
import matplotlib.pyplot as plt
import matplotlib.patches as patches

def create_image(n, blocks, positions):
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

    # Display the image
    plt.show()

def main():
    # Read input values
    input_data = sys.stdin.read().splitlines()
    n = int(input_data[0])
    print(n)

    blocks = []
    positions = []

    for i in range(1, n+1):
        width, height = map(int, input_data[i].split())
        blocks.append((width, height))

    for i in range(n+1, 2*n+1):
        x, y = map(int, input_data[i].split())
        positions.append((x, y))

    # Create the image
    create_image(n, blocks, positions)

if __name__ == "__main__":
    main()