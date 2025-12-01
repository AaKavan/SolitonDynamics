# Phys305 - Term Project
# Python file for plotting the phi values

import numpy as np
import matplotlib.pyplot as plt

# Time values that we had
t_values = [0, 1, 2, 3, 4, 5]

# Initalize the plot
plt.figure(figsize=(10, 6))

for t in t_values:
    # Load the file
    file = f"data_files/phi_t{t}.txt"
    data = np.loadtxt(file)

    x = data[:, 0]
    phi = data[:, 1]

    plt.plot(x, phi, label=f"t = {t}")


# Now add the labels, legends, etc
plt.xlabel("x", fontsize=14)
# Matplotlib support latex, so we can use that for phi
plt.ylabel(r"$\phi(x,t)$", fontsize=14)
plt.title(r"Evolution of $\phi(x,t) = f(x-t)$ for $t = 0,1,2,3,4,5$", fontsize=16)
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.savefig("plots/phi_time_evolution.png", dpi=200)