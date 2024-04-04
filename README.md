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

2. **Issue 2:** P-Channel equations are not working correctly.
	- The equations for the P-Channel are not working correctly. The equations are not implemented correctly.
	- Steps to reproduce:
		- Run the application
		- Add a P-Channel MOSFET
		- The simulation should not work correctly
	

	
3. **NOTES**
	- Program should be dumbproof
	- Flowchart for the program

3. ASK LESZEK
	- Field effect mobility can not be measured before MOS manufacture, so in the model we will use majority carrier mobility. For N-type, electron mobility and for P-type, hole mobility.
	- In threshold voltage equation, I have defined work function, bandgap, fermi potential, electron affinity all in eV, but the output is V?