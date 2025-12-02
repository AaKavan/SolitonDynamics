import numpy as np
import matplotlib.pyplot as plt

# Load the data from the f_self_convergence.txt file
data = np.loadtxt("data_files/f_self_convergence.txt", skiprows=1)

h = data[:, 0]
f5 = data[:, 1]

# h2 = step size for N=800, which is the second to last value
h2 = h[-2]

# h3 = step size for N = 1600, which is the last value
h3 = h[-1]

# Same thing for the f
f2 = f5[-2]     
f3 = f5[-1]   

# Calculate the self convergence ratio
# Compare with the highest resolution f(h3)
# Only go up to the third to last term because we compare with h2 and h3
R_num = (f5[:-2] - f3) / (f2 - f3)

# RK4 expected ratio
n = 4
R_expected = ((h[:-2] / h3)**n - 1) / (2**n - 1)

# Now we can plot these
# As always, add the labels and legends and etc. 
plt.figure(figsize=(8,6))
# Everything to the h2 term gets plotted
plt.plot(h[:-2], R_num, 'o-', label="Numerical Ratio")
plt.plot(h[:-2], R_expected, 's--', label="Expected Ratio (RK4)")
plt.xlabel("h", fontsize=14)
plt.ylabel("Self Convergence Ratio R(h)", fontsize=14)
plt.title("Self Convergence Test for f(5)", fontsize=16)
plt.grid(True, ls="--")
plt.legend(fontsize=12)
plt.tight_layout()
plt.savefig("plots/self_convergence_f5.png", dpi=200)
