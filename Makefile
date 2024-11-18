
CC = gcc
CFLAGS = -Wall -O2 -lm


TARGET = numerov


install:
	@echo "Instalando dependencias..."
	@if [ -f /etc/debian_version ]; then \
		sudo apt-get update && sudo apt-get install -y libgsl-dev; \
	elif [ -f /etc/fedora-release ]; then \
		sudo dnf install -y gsl-devel; \
	else \
		echo "Sistema no soportado para instalación automática."; \
		exit 1; \
	fi


all: $(TARGET)


$(TARGET): numerov.c
	$(CC) $(CFLAGS) -o $(TARGET) numerov.c -lgsl -lgslcblas


clean:
	rm -f $(TARGET) *.o results.csv


run: $(TARGET)
	./$(TARGET)


install: 
	$(MAKE) install
