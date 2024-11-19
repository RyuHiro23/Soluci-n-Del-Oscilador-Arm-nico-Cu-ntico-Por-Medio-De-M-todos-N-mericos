CC = gcc
CFLAGS = -Wall -O2 -lm
TARGET = numerov
PYTHON_SCRIPT = graf.py
UNAME_S := $(shell uname -s)

all: $(TARGET)

$(TARGET): numerov.c
ifeq ($(UNAME_S), Linux)
	$(CC) $(CFLAGS) -o $(TARGET) numerov.c -lgsl -lgslcblas
else
	$(CC) $(CFLAGS) -o $(TARGET).exe numerov.c
endif

clean:
	rm -f $(TARGET) $(TARGET).exe *.o results.csv grafica.png

install:
ifeq ($(UNAME_S), Linux)
	@echo "Instalando dependencias para Linux..."
	@if [ -f /etc/debian_version ]; then \
		sudo apt-get update && sudo apt-get install -y libgsl-dev python3 python3-pip; \
	elif [ -f /etc/fedora-release ]; then \
		sudo dnf install -y gsl-devel python3 python3-pip; \
	else \
		echo "Sistema Linux no soportado para instalación automática."; \
		exit 1; \
	fi
	@pip3 install pandas matplotlib
else
	@echo "Instalando dependencias para Windows..."
	@pip install pandas matplotlib
endif

run: $(TARGET)
ifeq ($(UNAME_S), Linux)
	@echo "Ejecutando el archivo C..."
	./$(TARGET)
	@echo "Ejecutando el script Python..."
	python3 $(PYTHON_SCRIPT)
else
	@echo "Ejecutando el archivo C..."
	$(TARGET).exe
	@echo "Ejecutando el script Python..."
	python $(PYTHON_SCRIPT)
endif
