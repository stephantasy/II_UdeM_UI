.PHONY: clean All

All:
	@echo "----------Building project:[ II_UdeM - Release ]----------"
	@"$(MAKE)" -f  "II_UdeM.mk"
clean:
	@echo "----------Cleaning project:[ II_UdeM - Release ]----------"
	@"$(MAKE)" -f  "II_UdeM.mk" clean
