.PHONY: clean All

All:
	@echo "----------Building project:[ Sensor - Debug ]----------"
	@"$(MAKE)" -f  "Sensor.mk"
clean:
	@echo "----------Cleaning project:[ Sensor - Debug ]----------"
	@"$(MAKE)" -f  "Sensor.mk" clean
