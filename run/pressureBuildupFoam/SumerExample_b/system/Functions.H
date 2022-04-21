functions
(

	Profiles
	{
		type                   sets;
		functionObjectLibs     ("libsampling.so");
		setFormat              raw;
		interpolationScheme    cellPoint;
		outputControl          outputTime;
		sets
		(
			Profile1
			{
				type        uniform;
				axis        z;
				start       (87 0 0);
				end         (87 0 -1);
				nPoints     100;
			}
			Profile2
			{
				type        uniform;
				axis        z;
				start       (84 0 0);
				end         (84 0 -1);
				nPoints     50;
			}
	
		);
		
		fields
		(
			 p
			 tauXZ
			 
		);
	}

	fieldAverage
	{
		type                   fieldAverage;
		functionObjectLibs     ("libfieldFunctionObjects.so");
		setFormat              raw;
		outputControl          outputTime;
		fields
		(

		tauXZ 
 		 {
			 mean 	 yes;
			 prime2Mean 	 yes;
			 base 	 time;
		} 
		);
	}
);

