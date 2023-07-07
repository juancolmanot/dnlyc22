# ====================================================================
# Compiler info and paths
# ====================================================================

CC=gcc
OMP=-fopenmp
GDB=-g
MPATH=../../../cursos/modulosc/
HPATH= -I${MPATH}
CPATH= -L${MPATH}
FFTPATHH= -I../../../cursos/modulosc/fftw-3.3.10/api/
FFTPATHC= -L/usr/local/lib/
LDLIBS= -lgsl -lgslcblas -lm -lfftw3
OPTFLAGS=-O3 -Ofast -ffast-math -march=native -ftree-vectorize # -funroll-loops -ftree-loop-vectorize

# ====================================================================
# Compile flags
# ====================================================================
# Warning flags
flag_w01=-Wall -Wextra -Wconversion -pedantic -Wno-unused-parameter
# Vectorization flags
flag_v01=-fopt-info-vec -fopt-info-vec-missed -ftree-vectorizer-verbose=2
# Debugging flags
flag_d01=-g
# Optimization flags
flag_o01=-O3 -ftree-vectorize -ftree-loop-vectorize -funroll-loops
flag_o02=-march=native -Ofast -ffast-math

CFLAGS=${flag_o02} ${flag_w01} ${flag_v01}

# ====================================================================
# Compilation directories
# ====================================================================

MAIN=
HEADERS=
comma:=,
HEADERS_LIST:=$(subst  ,$(comma),$(HEADERS))
HEADERS_LIST:=$(subst $(comma), ,$(HEADERS))
HEADERS_O:=$(addprefix $(MPATH),$(HEADERS_LIST))
HEADERS_O:=$(addsuffix .o,$(HEADERS_O))
HEADERS_H:=$(addprefix $(MPATH),$(HEADERS_LIST))
HEADERS_H:=$(addsuffix .h,$(HEADERS_H))


# ====================================================================
# Generate executable
# ====================================================================
$(MAIN): $(MAIN).o $(HEADERS_O)
	@$(CC) $(CPATH) $(FFTPATHC) $^ -o $@ $(LDLIBS)

# ====================================================================
# Compile output main file
# ====================================================================
$(MAIN).o: $(MAIN).c $(HEADERS_H)
	@$(CC) $(CFLAGS) $(HPATH) $(FFTPATHH) $(OPTFLAGS) -c -o $@ $<

# ====================================================================
# Compile output module files
# ====================================================================
$(MPATH)%.o: $(MPATH)%.c $(MPATH)%.h
	@$(CC) $(CFLAGS) $(HPATH) $(FFTPATHH) $(OPTFLAGS) -c -o $@ $<


# ====================================================================
# Clean
# ====================================================================

clean:
	@rm -f ${MAIN} *.o
	@rm -f ${MPATH}*.o

.PHONY: clean all
