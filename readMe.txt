%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                              %
% Residual Liquefaction                                                        %
% Author:                                                                      %
% Organization:                                                                %
% Last Modified Date: 30-09-2021                                               %
% 				                                                %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


Software Required
========================
- foam-extend-4.1


Features
========================
This submission includes two solvers i) biotFoam and ii) pressureBuildupFoam, as well as examples  to validate each solvers.
In addition, two boundaries conditions are included: i) propagatingPressureWave and ii) tractionDisplacement

biotFoam
~~~~~~~~

biotFoam is a freely available OpenFoam package developed by Roenby [1].  It is transient segregated finite-volume solver of the Biot equations for linear-elastic, small-strain deformation of a solid skeleton, coupled with pore water flow and pressure governed by Darcy's law.

pressureBuildupFoam
~~~~~~~~~~~~~~~~~~~
pressureBuildupFoam is an incremental development on biotFoam. It adds an additional equation to solve for the pore pressure buildup. Also, the liquefaction criteria is implemented in this solver to predict the onset of liquefaction. 


propagaringPressureWave
~~~~~~~~~~~~~~~~~~~~~~~
propagaringPressureWave is a boundary condition from the biotFoam package to simulate the effect of waves on the seabed by means of the pressure due to the progressive waves acting at the mudline.

tractionDisplacement
~~~~~~~~~~~~~~~~~~~~

tractionDisplacemnt is also a boundary condition from biotFoam package, which contains a fixed displacement gradient boundary due to fixed traction, which is a very common boundary condition for stress analysis problem.


File structure
========================

Structure
~~~~~~~~~~~~~
	-src
		-boundaries
		        -propagatingPressureWave
		        -tractionDsiplacemnet   
		       
		-solvers
		        -biotFoam
		        -pressureBuildupFoam   
	-run
		-biotFoam
			-Hsu_and_Jeng
               -pressureBuilupFoam
			-SummerExample_b
			-SummerExample_p
			-stoneColumn_b
			-stoneColumn_p


-src directory contains all the solvers and boundaries
     + solvers are compiled just by typying 'wmake' in each of  the solvers directory
     +  boundaries are compiled just by typing 'wmake' in boundaries directory  
      
-run directory contains numerical examples to validate the above mentioned two solvers and an application  for pressureBuildupFoam
     + Hsu_and_Jeng case is run just by running Allrun script and then the results can be compared to  
       analytical solutions by running Comaprison.m file
     + In pressureBuildupFoam directory, the subscript 'b' indicates that biotFoam has to be solved and 'p'
       indicates pressureBuildupFoam has to be solved.
     + There are scripts runScript_stoneColumn.m and runScript_SumerExample.m which runs the two different 
       example under pressureBuildupFoam
     + Note that for the examples in pressureBuildupFoam directory, biotFoam need to be solved first
       to calculate shear stress and later pressureBuildupFoam to calculate accumulated pore pressure 
       and residual liquefaction   
        
     


[1] J. Roenby, Openfoam library for soil mechanics, https://github.com/roenby/soilFoam, 2013.

