cd SumerBookExample4_b
system('./Allclean')
system('./Allrun')
system ('cp -r 13.7/cv ../stoneColumn_p/0/')
system ('cp -r 13.7/tauXZPrime2Mean ../stoneColumn_p/0/')
cd ../SumerBookExample4_p
system('./Allclean')
system('./Allrun')
comaparison
