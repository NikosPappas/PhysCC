import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import os

# Configuration - Must match your C++ N value
GRID_SIZE = 512
CSV_FILE = "data_2d.csv"

def animate_simulation():
    if not os.path.exists(CSV_FILE):
        print(f"❌ Error: {CSV_FILE} not found. Run ./reaction_sim first!")
        return

    print(f"📂 Loading {CSV_FILE}... (this may take a few seconds)")
    
    # Each row is a snapshot of the N*N grid
    try:
        # Using fast iterator for large files
        data = np.loadtxt(CSV_FILE, delimiter=",")
        
        # Reshape: (Number of snapshots, N, N)
        snapshots = data.reshape(-1, GRID_SIZE, GRID_SIZE)
        print(f"✅ Loaded {len(snapshots)} snapshots.")
    except Exception as e:
        print(f"❌ Error reshaping data: {e}")
        return

    fig, ax = plt.subplots(figsize=(8, 8))
    
    # Initialize the plot with the first frame
    # 'inferno' is great for heat/concentration maps
    im = ax.imshow(snapshots[0], cmap='inferno', interpolation='gaussian', origin='lower')
    plt.colorbar(im, label='Concentration (u)')
    ax.set_title("PhysCC 2D Reaction-Diffusion Pattern")

    def update(frame):
        im.set_array(snapshots[frame])
        return [im]

    # Create animation
    ani = animation.FuncAnimation(fig, update, frames=len(snapshots), 
                                   interval=100, blit=True)

    print("🚀 Displaying animation...")
    plt.show()

if __name__ == "__main__":
    animate_simulation()
