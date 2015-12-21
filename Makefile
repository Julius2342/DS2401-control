
LIBRARY_PATH = ~/Documents/Arduino/libraries/
LIBRARY_NAME = DS2401-control

help:
	+echo "Available commands:"
	+echo ""
	+echo "make create-zip		will create $(LIBRARY_NAME).zip to be added to Arduino IDE"
	+echo ""
	+echo "make install		installs library to $(LIBRARY_PATH)"
	+echo ""

create-zip:
	cd .. && zip -r $(LIBRARY_NAME).zip $(LIBRARY_NAME) -x *.git* && cd $(LIBRARY_NAME)

install:
	mkdir -p $(LIBRARY_PATH)/$(LIBRARY_NAME)
	install *.h $(LIBRARY_PATH)/$(LIBRARY_NAME)
	install *.cpp $(LIBRARY_PATH)/$(LIBRARY_NAME)

	mkdir -p $(LIBRARY_PATH)/$(LIBRARY_NAME)/examples/Simple
	install examples/Simple/Simple.pde $(LIBRARY_PATH)/$(LIBRARY_NAME)/examples/Simple

