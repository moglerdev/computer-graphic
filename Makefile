# Makefile to download and extract GLM and FreeGLUT (Windows specific)

GLM_URL = https://github.com/g-truc/glm/releases/download/1.0.1/glm-1.0.1-light.zip
GLM_ZIP = glm-1.0.1-light.zip
GLM_FOLDER = glm

FREEGLUT_URL_WINDOWS = https://www.transmissionzero.co.uk/files/software/development/GLUT/freeglut-MSVC.zip
FREEGLUT_ZIP = freeglut-MSVC.zip
FREEGLUT_FOLDER = freeglut

# Default target to download and unpack GLM and FreeGLUT (Windows specific)
all: glm freeglut clean-zip

# Target to handle GLM downloading and unpacking (works for Windows and other systems)
glm: $(GLM_ZIP)
ifeq ($(OS),Windows_NT)
	@echo "Extracting GLM..."
	@echo "Windows detected, using unzip tool to extract GLM."
	powershell -Command "Expand-Archive -Path $(GLM_ZIP) -DestinationPath $(GLM_FOLDER)"
else
	@echo "Extracting GLM..."
	unzip $(GLM_ZIP) -d glm
endif

# Download and unpack FreeGLUT for Windows
freeglut:
ifeq ($(OS),Windows_NT)
	@echo "Downloading FreeGLUT for Windows from $(FREEGLUT_URL_WINDOWS)..."
	curl -L $(FREEGLUT_URL_WINDOWS) -o $(FREEGLUT_ZIP)
	@echo "Extracting FreeGLUT..."
	@powershell -Command "Expand-Archive -Path $(FREEGLUT_ZIP) -DestinationPath $(FREEGLUT_FOLDER)"
else
	@echo "FreeGLUT download for Windows is only available on Windows OS."
endif

# Download GLM ZIP file
$(GLM_ZIP):
	@echo "Downloading GLM from $(GLM_URL)..."
	curl -L $(GLM_URL) -o $(GLM_ZIP)

clean-zip:
	@echo "Cleaning up downloaded files..."
	rm -f $(GLM_ZIP) $(FREEGLUT_ZIP)

# Clean up target to remove downloaded files and extracted folders
clean:
	@echo "Cleaning up..."
	rm -rf $(GLM_ZIP) $(GLM_FOLDER) $(FREEGLUT_ZIP) $(FREEGLUT_FOLDER)
