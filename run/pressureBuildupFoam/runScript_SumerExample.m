cd SumerExample_b
system('./Allclean')
system('blockMesh > log.blockMesh')
system('setFields')
system('biotFoam > log.biotFoam ')
system ('cp -r 13.7/cv ../SumerExample_p/0/')
system ('cp -r 13.7/tauXZPrime2Mean ../SumerExample_p/0/')
cd ../SumerExample_p
system('blockMesh > log.blockMesh')
system('setSet < batch.setSet')
system('setsToZones -noFlipMap')
system('pressureBuildupFoam > log.pressureBuildupFoam ')
post_criteria
