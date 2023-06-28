import os
import subprocess
from datetime import datetime


# Compiler
CC = "g++"
CFLAGS = ["-Wall", "-Werror", "-Wfatal-errors"]

# Directories
SRCDIR = "src"
INCLUDEDIR = "include"

# Output
LOGFILE = ".\\bin\\build.log"
OUTFILE = ".\\bin\\bbf"

if __name__ == "__main__":

    # Begin creation of compile cmd
    cmd = [CC]

    # Compilation flags
    for flag in CFLAGS:
        cmd.append(flag)

    # Add all src files to compilation
    for src_f in os.listdir("src"):
        # Change to .c if it's a C project :P
        if src_f.endswith(".cpp"):
            cmd.append(f".\{SRCDIR}\{src_f}")

    # Include
    cmd.append("-I")
    cmd.append(f".\{INCLUDEDIR}")

    # Outfile
    cmd.append("-o")
    cmd.append(OUTFILE)

    # Call compiler
    print(f"\n{' '.join(cmd)}")

    with open(LOGFILE, "w") as f:
        # subprocess
        proc = subprocess.Popen(cmd, stdout=f, stderr=subprocess.PIPE)
        proc_err = proc.stderr.read().decode()
        proc.communicate()

        if proc.returncode == 0:
            print(f"Compiled succesfully into {OUTFILE}.exe\n")

        else:
            print(f"Compilation failed. Copied log to .\{LOGFILE}\n")
            f.write(
                f"{' '.join(cmd)}\n \
                {datetime.now()} Compilation failed\n\n \
                {proc_err}"
            )

# Please do note that this isn't meant to be valid for ALL projects, just mine, and as such might not work for you
