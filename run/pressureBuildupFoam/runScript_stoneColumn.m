cd stoneColumn_b
system('./Allclean')
system('blockMesh > log.blockMesh')
system('setSet < batch.setSet')
system('setsToZones -noFlipMap')
system('setFields ')
system('biotFoam > log.biotFoam ')
system ('cp -r 13.7/cv ../stoneColumn_p/0/')
system ('cp -r 13.7/tauXZPrime2Mean ../stoneColumn_p/0/')
cd ../stoneColumn_p
system('blockMesh > log.blockMesh')
system('setSet < batch.setSet')
system('setsToZones -noFlipMap')
system('pressureBuildupFoam > log.pressureBuildupFoam ')
comparison

