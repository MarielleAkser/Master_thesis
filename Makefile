.PHONY: B1 B2

all:
	@echo "Choose B1 or B2"

B1:
	cd B1 && docker build -t b1_out .
	# --------------------------------------- #
	# Open a new terminal window and open ssh #
	# --------------------------------------- #
	docker run --rm -i -p 55555:22 -t b1_out bash -l

B2: 
	cd B2 && docker build -t b2_out .
	# --------------------------------------- #
	# Open a new terminal window and open ssh #
	# --------------------------------------- #
	docker run --rm -i -p 55555:22 -t b2_out bash -l

compile:
	cd B1 && docker build -t b1_out .
	cd B2 && docker build -t b2_out .
