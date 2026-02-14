import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

def visualize_results(filename="simulation_results.csv"):
    print(f"Loading {filename}...")
    # Read the CSV (assuming no header, comma-separated)
    try:
        data = pd.read_csv(filename, header=None).values
    except Exception as e:
        print(f"Error reading file: {e}")
        return

    plt.figure(figsize=(10, 8))
    
    # Plotting the density |psi|^2
    # We use 'magma' or 'viridis' as they are perceptually uniform
    img = plt.imshow(data, cmap='magma', origin='lower', extent=[0, 512, 0, 512])
    
    # Add a colorbar to show probability magnitude
    cbar = plt.colorbar(img)
    cbar.set_label('Probability Density $|\psi|^2$', rotation=270, labelpad=15)

    # Annotate the Barrier
    plt.axvspan(250, 265, color='white', alpha=0.3, label='Potential Barrier')
    
    plt.title("PhysCC Quantum Tunneling: Probability Density Distribution")
    plt.xlabel("X Grid Index")
    plt.ylabel("Y Grid Index")
    plt.legend(loc='upper right')
    
    print("Displaying plot...")
    plt.show()

if __name__ == "__main__":
    visualize_results()
