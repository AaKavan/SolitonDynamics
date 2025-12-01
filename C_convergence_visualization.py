import numpy as np
import matplotlib.pyplot as plt

# Load the (h, deltaC) data
# Skip the header row
data = np.loadtxt("data_files/C_convergence.txt", skiprows=1)
h = data[:, 0]
deltaC = data[:, 1]

plt.figure(figsize=(8,6))
# Use latex for the delta symbol
plt.loglog(h, deltaC, 'o-', label=r'$\delta C(X=5)$')

# Add labels and the grid
plt.xlabel(r'$h$', fontsize=14)
plt.ylabel(r'$\delta C(X=5)$', fontsize=14)
plt.title(r'Convergence of $\delta C(X=5)$ with step size $h$', fontsize=16)
plt.grid(True, which="both", ls="--")
plt.tight_layout()

# We can fit a test straight line to estimate convergence order
