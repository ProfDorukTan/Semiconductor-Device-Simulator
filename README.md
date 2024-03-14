# SemiconductorDeviceSimulator-DTA

This is a simple simulator for semiconductor devices. It is based on the drift-diffusion model and is implemented in Python. The simulator is designed to be easy to use and to be easily extendable. The simulator is designed to be used in a teaching environment, but it can also be used for research purposes.

## Problems
### Commmit 14 March 2024
1. **Issue 1:** File IO.
	- Currently, when the application is closed the MOSFETs are saved to a file, however, the functionality does not work correctly.
	- Possible problem might be due to saving the type of MOSFET (N/P) as an int rather than a character.
	- Upon start application preloads all existing mosfets from json file, this is not working correctly. Furthermore, when the application is closed, the parameters are overwritten with wrong values.
	- Steps to reproduce:
		- Run the application
		- Add a MOSFET
		- Close the application
		- Run the application again
		- The MOSFET should be loaded from the file, but it can not be properly simulated

2. **Issue 2:** Level 3 simulation results in x-y mismatch
	- The number of x values does not match number of y values, so graph can not be created.
	- Steps to reproduce:
		- Run the application
		- Add a MOSFET
		- Change the simulation level to 3
		- The graph should not be created
	- Since the last graph created is shown as popup, an image is still appears as a result of the simulation, but it is not correct.



