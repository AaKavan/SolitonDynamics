import numpy as np
import matplotlib.pyplot as plt

# Load the data from the kdv_forward_solution.txt file
# skip the header row
data = np.loadtxt("kdv_forward_solution.txt", skiprows=1)

# Extract the columns
# These are the values for the [0, 20] region
X = data[:, 0]
f = data[:, 1]
fp = data[:, 2]
fpp = data[:, 3]
C = data[:, 4]
error = data[:, 5]

# Plot f(X)
# Add a title, labels, grid as well
plt.figure(figsize=(8,6))
plt.plot(X, f, label="f(X)")
plt.xlabel("X")
plt.ylabel("f(X)")
plt.title("Forward Soliton solution f(X) on [0, 20]")
plt.grid(True)
plt.tight_layout()
plt.savefig("f_forward.png", dpi=200)


# Plot C(X)
plt.figure(figsize=(8,6))
plt.plot(X, C, label="C(X)")
# Add the C0 line for reference 
plt.axhline(C[0], color='red', linestyle='--', label="C(0) reference")
plt.xlabel("X")
plt.ylabel("C(X)")
plt.title("Constant of Motion C(X)")
plt.grid(True)
plt.tight_layout()
plt.legend()
plt.savefig("C_of_X.png", dpi=200)

# Plot the error of C
plt.figure(figsize=(8,5))
plt.plot(X, error)
plt.yscale("log")
plt.xlabel("X")
plt.ylabel("Absolute Error |C - C0|") # Since C0 was 0
plt.title("Error in the Constant of Motion")
plt.grid(True, which="both")
plt.tight_layout()
plt.savefig("C_error.png", dpi=200)




# Since we showed that f(X) = f(-X), we can just reflect the forward solutions
# to get the backwards solutions as well.
# Note: I'll drop the first element (X=0) to avoid duplicates.
X_neg   = -X[1:][::-1]
f_neg   =  f[1:][::-1]
fp_neg  =  fp[1:][::-1]
fpp_neg = fpp[1:][::-1]

# now combine them to make the full [-20, 20] interval
X_full   = np.concatenate((X_neg, X))
f_full   = np.concatenate((f_neg, f))
fp_full  = np.concatenate((fp_neg, fp))
fpp_full = np.concatenate((fpp_neg, fpp))



# plot f(X) on [-20, 20]
plt.figure(figsize=(8,6))
plt.plot(X_full, f_full)
plt.xlabel("X")
plt.ylabel("f(X)")
plt.title("Full Soliton solution f(X) on [-20,20]")
plt.grid(True)
plt.tight_layout()
plt.savefig("plots/f_full_solution.png", dpi=200)